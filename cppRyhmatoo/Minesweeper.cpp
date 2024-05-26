#include "Minesweeper.h"
#include <filesystem>
#include <fstream>

//Abimeetodid, hetkel lihtsalt kõige ees
int loendaPommid(size_t ruuduIndeks, std::vector<bool> pommid, size_t pommidSize, int reaPikkus) {
	//Leiab indeksi ümber asuvad pommid - kõik on üks pikk järjend, vaja kontrollida maatriksi mõttes tema ümber olemist

	int loendur{ 0 };

	size_t kontrollitavIndeks{ ruuduIndeks - reaPikkus - 1 }; //Algväärtustame ruudust ülesse, vasakule
	// Unsigned int läheb negatiivselt out of bounds puhul oma maxvalue peale, seega kontrollin alati, et on suurem.
	// - kuna meie mängulaua mõõtmete korrutis peaks alati olema väiksem kui unsigned int max value, ei tohiks probleeme tekkida
	if (kontrollitavIndeks < pommid.size()) { //Kui ei ole out of bounds
		if (pommid.at(kontrollitavIndeks)) loendur++; //Kui seal on pomm, suurendan loendurit
	}
	kontrollitavIndeks++; //Liigun ühe võrra paremale ehk ruudust otse üles
	if (kontrollitavIndeks < pommid.size()) {
		if (pommid.at(kontrollitavIndeks)) loendur++;
	}
	kontrollitavIndeks++; //Liigun ühe võrra paremale ehk ruudust üles paremale
	if (kontrollitavIndeks < pommid.size()) {
		if (pommid.at(kontrollitavIndeks)) loendur++;
	}
	kontrollitavIndeks = ruuduIndeks - 1; //ruudust vasakul
	if (kontrollitavIndeks < pommid.size()) {
		if (pommid.at(kontrollitavIndeks)) loendur++;
	}
	kontrollitavIndeks = ruuduIndeks + 1; //ruudust paremal
	if (kontrollitavIndeks < pommid.size()) {
		if (pommid.at(kontrollitavIndeks)) loendur++;
	}
	kontrollitavIndeks = ruuduIndeks + reaPikkus - 1; //ruudust all, vasakul
	if (kontrollitavIndeks < pommid.size()) {
		if (pommid.at(kontrollitavIndeks)) loendur++;
	}
	kontrollitavIndeks++; //ruudust otse all
	if (kontrollitavIndeks < pommid.size()) {
		if (pommid.at(kontrollitavIndeks)) loendur++;
	}
	kontrollitavIndeks++; //ruudust all, paremal
	if (kontrollitavIndeks < pommid.size()) {
		if (pommid.at(kontrollitavIndeks)) loendur++;
	}

	return loendur;
}

Minesweeper::Minesweeper(int k, int l, std::string pildid) {
	srand(static_cast<unsigned int> (time(0)));

	this->mangOnLabi = false;

	this->kusiManguLauaAndmed();

	try {
		this->laeTekstuurid(pildid);
	}
	catch (std::string s) {
		throw s;
	}
}
void Minesweeper::koostaPommid(int protsent) {
	//Hulga sisse panen millistel indeksitel on pommid
	int mituPommi{(korgus*laius*protsent)/100};
	std::set<int> pommid;
	while (pommid.size() != mituPommi)
	{
		pommid.insert(rand() % (korgus*laius)); //Täidan kuni on piisavalt pomme
	}

	//Nüüd lisan pommide vektorisse pommid ja tühjad kohad
	auto eiLeitudIteraator = pommid.end();
	for (int indeks = 0; indeks < this->vektoritePikkus; indeks++) {
		//find tagastab iteraatori otsitavale indeksile hulgas, kui see on end(), siis ei leitud
		this->pommid.push_back(pommid.find(indeks) != eiLeitudIteraator);
	}
}
void Minesweeper::koostaRuudud() {
	//Igale ruudule väärtustada loendaPommid() väärtus antud indeksil
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if(this->pommid.at(i)) this->ruudud.push_back(-1); //Kui on pomm, siis praegu paneme -1, pole otseselt vaja, aga nii selgem
		else this->ruudud.push_back(loendaPommid(i, this->pommid, this->vektoritePikkus, this->laius)); //Kui pommi ei ole, loendame ümberringsed pommid ja seame selle väärtuseks
	}
}
void Minesweeper::koostaMangijaLaud() {
	for (size_t i = 0; i < this->ruudud.size(); i++) {
		this->mangijaLaud.push_back('?');
	}
}
void Minesweeper::reedaMangulaud() {
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if (i % this->laius == 0) std::cout << "\n";
		if (this->pommid.at(i)) this->mangijaLaud.at(i) = 'X';
		else if (this->ruudud.at(i) == 0) this->mangijaLaud.at(i) = ' ';
		else this->mangijaLaud.at(i) = this->ruudud.at(i);
	}
}
void Minesweeper::avaTuhjadRuudud(size_t indeks) { // Rekursiivselt avab kõik ruudud, mis on valitud ruudu kõrval, vastavalt valitud suunale
	if (indeks > vektoritePikkus) return; //Kui jõuti liikumisega vektorist välja, siis see haru lõpetada
	if (ruudud.at(indeks) != 0) return; //Kui jõuti ruuduni, mida ei peaks avama, siis see haru lõpetab töö
	if (mangijaLaud.at(indeks) != '?') return; //Kui ruut on juba avatud, siis see haru lõpetab töö, et vältida tsüklite moodustumist ja lõputut rekursiooni

	mangijaLaud.at(indeks) = '0' + ruudud.at(indeks); //Väärtustamine

	//Rekursiivselt välja kutsumine - paremale, vasakule, alla, üles liikumine
	
	avaTuhjadRuudud(indeks+1);
	avaTuhjadRuudud(indeks-1);
	avaTuhjadRuudud(indeks+laius);
	avaTuhjadRuudud(indeks-laius);
}
void Minesweeper::laeTekstuurid(std::string pildid) {
	
	const char file_seperator = std::filesystem::path::preferred_separator;

	std::string fail = pildid + file_seperator + "lipp.png";
	if (!this->lipp.loadFromFile(fail)) throw fail;
	
	fail = pildid + file_seperator + "pomm.png";
	if (!this->pomm.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "tuhi.png";
	if (!this->tuhi.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "avamata.png";
	if (!this->avamata.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "one.png";
	if (!this->one.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "two.png";
	if (!this->two.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "three.png";
	if (!this->three.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "four.png";
	if (!this->four.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "five.png";
	if (!this->five.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "six.png";
	if (!this->six.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "seven.png";
	if (!this->seven.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "eight.png";
	if (!this->eight.loadFromFile(fail)) throw fail;
	
	this->charTekstuuriks['?'] = this->avamata;
	this->charTekstuuriks[' '] = this->tuhi;
	this->charTekstuuriks['!'] = this->lipp;
	this->charTekstuuriks['X'] = this->pomm;
	this->charTekstuuriks['1'] = this->one;
	this->charTekstuuriks['2'] = this->two;
	this->charTekstuuriks['3'] = this->three;
	this->charTekstuuriks['4'] = this->four;
	this->charTekstuuriks['5'] = this->five;
	this->charTekstuuriks['6'] = this->six;
	this->charTekstuuriks['7'] = this->seven;
	this->charTekstuuriks['8'] = this->eight;
}
bool Minesweeper::koikRuududAvatud() {
	//Kui mäng on juba läbi, siis rohkem ruute ei saa avada
	if (this->mangOnLabi) return true;

	//Kontrollin, kas leidub veel avamata ruute
	// - mangijaLaud vektoris on avamata ruut '?'
	for (auto iter = this->mangijaLaud.begin(), lopp = mangijaLaud.end(); iter != lopp; iter++) {
		if (*iter == '?') return false;
	}
	return true;
}

//Kõik muudatused, mis on vahepeal tehtud, on salvestatud mängijaLaud muutujasse, võtan sealt info ja kuvan ekraanile
void Minesweeper::kuvaMangulaud(sf::RenderWindow& window) {
	//Kuna akna suurust saab muuta, siis vaja välja arvutada ühe ruudu suurus, et alati oleks näha tervet mängulauda
	sf::Vector2u size = window.getSize();
	float ruuduLaius = (float)size.x / (float)this->laius;
	float ruuduKorgus = (float)size.y / (float)this->korgus;

	std::cout << "ruutL: " << ruuduLaius << " windowx: " << size.x << "  ";
	std::cout << "ruutK: " << ruuduKorgus << " windowy: " << size.y << "\n";

	//koordinaadid, kuhu kuvada
	int reaIndeks{ 0 };
	int veeruIndeks{ 0 };
	for (size_t vektoriIndeks = 0; vektoriIndeks < this->vektoritePikkus; vektoriIndeks++) {
		//Uue rea alustamine
		if (vektoriIndeks % this->laius == 0 && vektoriIndeks != 0) {
			reaIndeks++;
			veeruIndeks = 0;
		}
		//Mängulaua vektori abil saada õige tekstuur, mida kuvada
		sf::RectangleShape ruut(sf::Vector2f(ruuduLaius, ruuduKorgus));
		ruut.setPosition((float)veeruIndeks*ruuduLaius, (float)reaIndeks*ruuduKorgus);

		sf::Texture& kuvatavTekstuur = this->charTekstuuriks[this->mangijaLaud.at(vektoriIndeks)];
		ruut.setTexture(&kuvatavTekstuur);

		window.draw(ruut);

		veeruIndeks++;
	}

	//Mängulaua kuvamise ajaks on käik tehtud, saab kontrollida, kas kõik ruudud on avatud - ehk kas mängja on võitnud
	if (koikRuududAvatud() && !this->mangOnLabi) {
		this->mangOnLabi = true;
		this->oliKaotus = false;
	}
}
void Minesweeper::kuvaVoiduEkraan(sf::RenderWindow& window) {
	this->reedaMangulaud();
	this->kuvaMangulaud(window);

}
void Minesweeper::kuvaKaotusEkraan(sf::RenderWindow& window) {
	std::cout << "Kaotuse ekraani sees!\n";
}
void Minesweeper::koostaManguala(int protsent) {
	this->koostaPommid(protsent);
	this->koostaRuudud();
	this->koostaMangijaLaud();
}

//Funktsioon muudab mängija lauda, alles kuvaMangulaud näitab uuendusi ekraanile
bool Minesweeper::teeKaik(int rida, int veerg, bool kasLipp) {
	if (rida < 0 || rida >= this->korgus || veerg < 0 || veerg >= this->laius) {
		std::cout << "Valitud käik ei ole mängulaua sees!\n";
		return false;
	}
	size_t indeks = rida * this->laius + veerg;
	if (this->mangijaLaud.at(indeks) == '!') {
		if (!kasLipp) {
			std::cout << "Lipuga ruutu ei saa avada! (võta enne lipp ära)\n";
			return false;
		}
		//Kui tegi uuesti lipu panemise käigu, siis võtame lipu ära
		mangijaLaud[indeks] = '?';
		return true;
	}
	if (kasLipp) this->mangijaLaud.at(indeks) = '!';
	else {
		if (indeks < this->pommid.size() && this->pommid.at(indeks)) {
			this->mangOnLabi = true;
			this->oliKaotus = true;
			std::cout << "Avasid pommi!\n";
		}
		else {
			if (ruudud.at(indeks) == 0) avaTuhjadRuudud(indeks);
			else this->mangijaLaud.at(indeks) = '0' + this->ruudud.at(indeks); //avaTuhjadRuudud juba avab selle ruudu enda ka
		}
	}
	return true;
}
void Minesweeper::handleEvent(sf::Event& event, const sf::Vector2u& aknaSuurus) {
	bool kasLipp = event.mouseButton.button == sf::Mouse::Right;
	int xKoordinaat = event.mouseButton.x;
	int yKoordinaat = event.mouseButton.y;
	std::cout << "mousex" << xKoordinaat << " mousey " << yKoordinaat << std::endl;

	//Koordinaat ümber teha mängulaua koordinaadiks
	xKoordinaat /= aknaSuurus.x / this->laius;
	yKoordinaat /= aknaSuurus.y / this->korgus;
	std::cout << "aknalaius " << aknaSuurus.x << " this.laius " << this->laius << " aknakorgus " << aknaSuurus.y << " this.korgus " << this->korgus << std::endl;
	std::cout << "loppx " << xKoordinaat << " loppy " << yKoordinaat << std::endl;

	//teeKaik funktsioon ootab rida enne veergu
	teeKaik(yKoordinaat, xKoordinaat, kasLipp);
}
bool Minesweeper::kasMangOnLabi() {
	return this->mangOnLabi;
}
bool Minesweeper::kasOliKaotus() {
	return this->oliKaotus;
}
void Minesweeper::kusiManguLauaAndmed() {
	int k{ 0 };
	int l{ 0 };
	while (true) {
		std::cout << "Vali mängulaua kõrgus: ";
		
		std::cin >> k;
		//Kuna fixed ekraani suurus, siis ei saa olla negatiivne arv (ega 0) ega suurem kui ekraani laius
		if (k <= 0 || k > 640) continue;

		std::cout << "Vali mängulaua laius: ";
		
		std::cin >> l;
		//Samamoodi, ei saa olla suurem kui ekraani kõrgus ega negatiivne ega null
		if (l <= 0 || l > 480) continue;

		this->korgus = k;
		this->laius = l;
		break;
	}

	this->vektoritePikkus = korgus * laius;

	int protsent{ 0 }, mituPommi{ 0 };
	while (true) {
		std::cout << "Mitu protsenti ruutudest võiksid olla pommid: ";
	
		std::cin >> protsent;

		//Arvutamine, mitu pommi sellise protsendiga oleks
		mituPommi = (this->korgus * this->laius * protsent) / 100 ;
		//Kui pomme pole (või on neg. arv) või kui kõik on pommid, siis ei luba seda, laseme uuesti sisestada
		if (mituPommi <= 0 || mituPommi == this->vektoritePikkus) continue;

		break;
	}

	this->koostaManguala(protsent);
}