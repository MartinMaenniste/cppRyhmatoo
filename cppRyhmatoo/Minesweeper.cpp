#include "Minesweeper.h"
#include <Windows.h>

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

Minesweeper::Minesweeper(int k, int l, std::string pildid) {
	srand(static_cast<unsigned int> (time(0)));

	this->korgus = k;
	this->laius = l;
	this->vektoritePikkus = k*l;
	this->mangOnLabi = false;

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

	//  Testimiseks v�ljastan, hiljem �ra v�tta
	/*std::cout << "Pommid (kasutaja ei n�e seda):\n";
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if (i % this->laius == 0)
		{
			std::cout << std::endl;
		}
		std::cout << this->pommid.at(i) << " ";
	}
	std::cout << "\n\n";*/
}
void Minesweeper::koostaRuudud() {
	//Igale ruudule v��rtustada loendaPommid() v��rtus antud indeksil
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if(this->pommid.at(i)) this->ruudud.push_back(-1); //Kui on pomm, siis praegu paneme -1, pole otseselt vaja, aga nii selgem
		else this->ruudud.push_back(loendaPommid(i, this->pommid, this->vektoritePikkus, this->laius)); //Kui pommi ei ole, loendame �mberringsed pommid ja seame selle v��rtuseks
	}

	// Testimiseks v�ljastan, hiljem �ra v�tta
	/*std::cout << "Ruudud (kasutaja ei n�e seda):\n";
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if (i % this->laius == 0)
		{
			std::cout << std::endl;
		}
		if (this->ruudud.at(i) >= 0) std::cout << " "; //Lisat�hik kui ei ole negatiivne, et saaks paremini aru
		std::cout << this->ruudud.at(i) << " ";
	}
	std::cout << "\n\n";*/
}
void Minesweeper::koostaMangijaLaud() {
	for (size_t i = 0; i < this->ruudud.size(); i++) {
		this->mangijaLaud.push_back('?');
	}
}
void Minesweeper::reedaMangulaud() {
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if (i % this->laius == 0) std::cout << "\n";
		if (this->pommid.at(i)) std::cout << "X ";
		else std::cout << this->ruudud.at(i) << " ";
	}
}
void Minesweeper::avaTuhjadRuudud(size_t indeks) { // Rekursiivselt avab k�ik ruudud, mis on valitud ruudu k�rval, vastavalt valitud suunale
	if (indeks > vektoritePikkus) return; //Kui j�uti liikumisega vektorist v�lja, siis see haru l�petada
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

#if defined(_WIN32) || defined(_WIN64)
	const std::string file_seperator = "\\";
#else
	const std::string file_seperator = "/";
#endif
	
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
}
void Minesweeper::prindiMangulaud() {
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if (i % this->laius == 0) std::cout << std::endl;
		std::cout << this->mangijaLaud.at(i) << ' ';
	}
	std::cout << "\n";
}
void Minesweeper::kuvaMangulaud(sf::RenderWindow& window) {
	//Kuna akna suurust saab muuta, siis vaja v�lja arvutada �he ruudu suurus, et alati oleks n�ha tervet m�ngulauda
	 sf::Vector2u size = window.getSize();
	 float ruuduLaius = size.x / this->laius;
	 float ruuduKorgus = size.y / this->korgus;

	 //koordinaadid, kuhu kuvada
	 int reaIndeks{ 0 };
	 int veeruIndeks{ 0 };
	 for (size_t vektoriIndeks = 0; vektoriIndeks < this->vektoritePikkus; vektoriIndeks++) {
		 //Uue rea alustamine
		 if (vektoriIndeks % this->laius == 0 && vektoriIndeks != 0) {
			 reaIndeks++;
			 veeruIndeks = 0;
		 }
		 sf::RectangleShape ruut(sf::Vector2f(ruuduLaius, ruuduKorgus));
		 ruut.setPosition((float)veeruIndeks*ruuduLaius, (float)reaIndeks*ruuduKorgus);
		 window.draw(ruut);

		 veeruIndeks++;
	 }
}
void Minesweeper::koostaManguala(int protsent) {
	this->koostaPommid(protsent);
	this->koostaRuudud();
	this->koostaMangijaLaud();
}
bool Minesweeper::teeKaik(int rida, int veerg, bool kasLipp) {
	if (rida < 0 || rida >= this->korgus || veerg < 0 || veerg >= this->laius) {
		std::cout << "Valitud k�ik ei ole m�ngulaua sees!\n";
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
		if (this->pommid.at(indeks)) {
			this->mangOnLabi = true;
			std::cout << "Avasid pommi!\n";
			this->reedaMangulaud();
		}
		else {
			if (ruudud.at(indeks) == 0) avaTuhjadRuudud(indeks);
			else this->mangijaLaud.at(indeks) = '0' + this->ruudud.at(indeks); //avaTuhjadRuudud juba avab selle ruudu enda ka
		}
	}
	return true;
}
void Minesweeper::handleEvent(sf::Event& event) {

}
bool Minesweeper::kasMangOnLabi() {
	return this->mangOnLabi;
}