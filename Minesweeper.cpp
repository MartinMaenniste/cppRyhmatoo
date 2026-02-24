#include "Minesweeper.h"
#include <filesystem>
#include <fstream>

//Abimeetodid, hetkel lihtsalt k�ige ees
int loendaPommid(size_t ruuduIndeks, std::vector<bool> pommid, size_t pommidSize, int reaPikkus) {
	//Leiab indeksi �mber asuvad pommid - k�ik on �ks pikk j�rjend, vaja kontrollida maatriksi m�ttes tema �mber olemist

	int loendur{ 0 };

	size_t kontrollitavIndeks{ ruuduIndeks - reaPikkus - 1 }; //Algv��rtustame ruudust �lesse, vasakule
	// Unsigned int l�heb negatiivselt out of bounds puhul oma maxvalue peale, seega kontrollin alati, et on suurem.
	// - kuna meie m�ngulaua m��tmete korrutis peaks alati olema v�iksem kui unsigned int max value, ei tohiks probleeme tekkida
	if (kontrollitavIndeks < pommid.size()) { //Kui ei ole out of bounds
		if (pommid.at(kontrollitavIndeks)) loendur++; //Kui seal on pomm, suurendan loendurit
	}
	kontrollitavIndeks++; //Liigun �he v�rra paremale ehk ruudust otse �les
	if (kontrollitavIndeks < pommid.size()) {
		if (pommid.at(kontrollitavIndeks)) loendur++;
	}
	kontrollitavIndeks++; //Liigun �he v�rra paremale ehk ruudust �les paremale
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

Minesweeper::Minesweeper(std::string pildid) {
	srand(static_cast<unsigned int> (time(0)));

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
		pommid.insert(rand() % (korgus*laius)); //T�idan kuni on piisavalt pomme
	}

	//N��d lisan pommide vektorisse pommid ja t�hjad kohad
	auto eiLeitudIteraator = pommid.end();
	for (int indeks = 0; indeks < this->vektoritePikkus; indeks++) {
		//find tagastab iteraatori otsitavale indeksile hulgas, kui see on end(), siis ei leitud
		this->pommid.push_back(pommid.find(indeks) != eiLeitudIteraator);
	}
}
void Minesweeper::koostaRuudud() {
	//Igale ruudule v��rtustada loendaPommid() v��rtus antud indeksil
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if(this->pommid.at(i)) this->ruudud.push_back(-1); //Kui on pomm, siis praegu paneme -1, pole otseselt vaja, aga nii selgem
		else this->ruudud.push_back(loendaPommid(i, this->pommid, this->vektoritePikkus, this->laius)); //Kui pommi ei ole, loendame �mberringsed pommid ja seame selle v��rtuseks
	}
}
void Minesweeper::koostaMangijaLaud() {
	for (size_t i = 0; i < this->ruudud.size(); i++) {
		this->mangijaLaud.push_back('?');
	}
}
void Minesweeper::reedaMangulaud() {
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if (this->pommid.at(i)) this->mangijaLaud.at(i) = 'X';
		else if (this->ruudud.at(i) == 0) this->mangijaLaud.at(i) = ' ';
		else this->mangijaLaud.at(i) = '0' + this->ruudud.at(i);
	}
}
void Minesweeper::avaTuhjadRuudud(size_t indeks) { // Rekursiivselt avab k�ik ruudud, mis on valitud ruudu k�rval, vastavalt valitud suunale
	if (indeks > vektoritePikkus) return; //Kui j�uti liikumisega vektorist v�lja, siis see haru l�petada
	//	Peaks avama ka numberruudud tühjade ruutude ümber!!
	if (ruudud.at(indeks) != 0) return; //Kui j�uti ruuduni, mida ei peaks avama, siis see haru l�petab t��
	if (mangijaLaud.at(indeks) != '?') return; //Kui ruut on juba avatud, siis see haru l�petab t��, et v�ltida ts�klite moodustumist ja l�putut rekursiooni

	mangijaLaud.at(indeks) = '0' + ruudud.at(indeks); //V��rtustamine

	//Rekursiivselt v�lja kutsumine - paremale, vasakule, alla, �les liikumine
	
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

	fail = pildid + file_seperator + "yks.png";
	if (!this->one.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "kaks.png";
	if (!this->two.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "kolm.png";
	if (!this->three.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "neli.png";
	if (!this->four.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "viis.png";
	if (!this->five.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "kuus.png";
	if (!this->six.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "seitse.png";
	if (!this->seven.loadFromFile(fail)) throw fail;

	fail = pildid + file_seperator + "kaheksa.png";
	if (!this->eight.loadFromFile(fail)) throw fail;

	this->charTekstuuriks['?'] = this->avamata;
	this->charTekstuuriks[' '] = this->tuhi;
	this->charTekstuuriks['!'] = this->lipp;
	this->charTekstuuriks['X'] = this->pomm;
	this->charTekstuuriks['-'] = this->pomm; //ruudud vektoris on pomm -1
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
	//Kui m�ng on juba l�bi, siis rohkem ruute ei saa avada
	if (this->mangOnLabi) return true;

	//Kontrollin, kas leidub veel avamata ruute
	// - mangijaLaud vektoris on avamata ruut '?'
	size_t leitudLippe{ 0 };

	for (auto iter = this->mangijaLaud.begin(), lopp = mangijaLaud.end(); iter != lopp; iter++) {
		if (*iter == '?') return false;
		if (*iter == '!') leitudLippe++; //Loendame leitud lipud kokku
	}
	//Kui k�ik ruudud on "avatud" - ehk avamata ruute pole, siis kontrollida, kas lippe on �ige arv
	size_t lippe{ 0 };
	//Loendame kokku, mitu pommi peaks olema
	for (auto iter = this->pommid.begin(), lopp = pommid.end(); iter != lopp; iter++) {
		if (*iter) lippe++;
	}
	//kui loendatud lippe ei ole sama palju kui pomme, siis midagi valesti ja ei saa olla m�ng l�bi
	if (leitudLippe != lippe) return false;
	return true;
}

//K�ik muudatused, mis on vahepeal tehtud, on salvestatud m�ngijaLaud muutujasse, v�tan sealt info ja kuvan ekraanile
void Minesweeper::kuvaMangulaud(sf::RenderWindow& window) {
	//Kuna akna suurust saab muuta, siis vaja v�lja arvutada �he ruudu suurus, et alati oleks n�ha tervet m�ngulauda
	sf::Vector2u size = window.getSize();
	float ruuduLaius = (float)size.x / (float)this->laius;
	float ruuduKorgus = (float)size.y / (float)this->korgus;

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
		sf::RectangleShape ruut = sf::RectangleShape(sf::Vector2f(ruuduLaius, ruuduKorgus));
		ruut.setPosition(sf::Vector2f((float)veeruIndeks*ruuduLaius, (float)reaIndeks*ruuduKorgus));//(float)veeruIndeks*ruuduLaius, (float)reaIndeks*ruuduKorgus);

		sf::Texture& kuvatavTekstuur = this->charTekstuuriks[this->mangijaLaud.at(vektoriIndeks)];
		ruut.setTexture(&kuvatavTekstuur);

		window.draw(ruut);

		veeruIndeks++;
	}

	//M�ngulaua kuvamise ajaks on k�ik tehtud, saab kontrollida, kas k�ik ruudud on avatud - ehk kas m�ngja on v�itnud
	if (koikRuududAvatud() && !this->mangOnLabi) {
		this->mangOnLabi = true;
		this->oliKaotus = false;
	}
}
void Minesweeper::kuvaVoiduEkraan(sf::RenderWindow& window) {
	std::cout << "Sa v�itsid! Vali uue m�ngulaua andmed:\n";
}
void Minesweeper::kuvaKaotusEkraan(sf::RenderWindow& window) {
	this->reedaMangulaud();
	window.clear();
	this->kuvaMangulaud(window);
	window.display();
	std::cout << "Kaotasid :( Vali uue m�ngulaua andmed:\n";
}
void Minesweeper::koostaManguala(int protsent) {
	this->koostaPommid(protsent);
	this->koostaRuudud();
	this->koostaMangijaLaud();
}

//Funktsioon muudab m�ngija lauda, alles kuvaMangulaud n�itab uuendusi ekraanile
bool Minesweeper::teeKaik(int rida, int veerg, bool kasLipp) {
	if (rida < 0 || rida >= this->korgus || veerg < 0 || veerg >= this->laius) {
		std::cout << "Valitud käik ei ole mängulaua sees!\n";
		return false;
	}
	size_t indeks = rida * this->laius + veerg;
	if (this->mangijaLaud.at(indeks) == '!') {
		if (!kasLipp) {
			std::cout << "Lipuga ruutu ei saa avada! (v�ta enne lipp �ra)\n";
			return false;
		}
		//Kui tegi uuesti lipu panemise k�igu, siis v�tame lipu �ra
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
void Minesweeper::handleEvent(const sf::RenderWindow& aken, const sf::Mouse::Button& event) {
	bool kasLipp = event == sf::Mouse::Button::Right; // event.mouseButton.button == sf::Mouse::Right;
	int xKoordinaat = sf::Mouse::getPosition(aken).x; //event.mouseButton.x;
	int yKoordinaat = sf::Mouse::getPosition(aken).y; //event.mouseButton.y;

	//Koordinaat ümber teha mängulaua koordinaadiks
	xKoordinaat /= aken.getSize().x / this->laius;
	yKoordinaat /= aken.getSize().y / this->korgus;

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
	this->mangOnLabi = false;

	int k{ 0 };
	int l{ 0 };
	while (true) {
		std::cout << "Vali mängulaua kõrgus: ";
		
		std::cin >> k;
		//Kuna fixed ekraani suurus, siis ei saa olla negatiivne arv (ega 0) ega suurem kui ekraani laius
		if (k <= 0 || k > 640) continue;

		std::cout << "Vali mängulaua laius: ";
		
		std::cin >> l;
		//Samamoodi, ei saa olla suurem kui ekraani k�rgus ega negatiivne ega null
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
		mituPommi = (this->korgus * this->laius * protsent) / 100;
		//Kui pomme pole (v�i on neg. arv) v�i kui k�ik on pommid, siis ei luba seda, laseme uuesti sisestada
		if (mituPommi <= 0 || mituPommi == this->vektoritePikkus) continue;

		break;
	}

	this->pommid.clear();
	this->ruudud.clear();
	this->mangijaLaud.clear();

	this->koostaManguala(protsent);
}