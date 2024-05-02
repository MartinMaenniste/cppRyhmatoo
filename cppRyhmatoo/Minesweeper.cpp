#include "Minesweeper.h"

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

Minesweeper::Minesweeper(int k, int l) {
	this->korgus = k;
	this->laius = l;
	this->vektoritePikkus = k*l;
	this->mangOnLabi = false;
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

	//  Testimiseks väljastan, hiljem ära võtta
	/*std::cout << "Pommid (kasutaja ei näe seda):\n";
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
	//Igale ruudule väärtustada loendaPommid() väärtus antud indeksil
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if(this->pommid.at(i)) this->ruudud.push_back(-1); //Kui on pomm, siis praegu paneme -1, pole otseselt vaja, aga nii selgem
		else this->ruudud.push_back(loendaPommid(i, this->pommid, this->vektoritePikkus, this->laius)); //Kui pommi ei ole, loendame ümberringsed pommid ja seame selle väärtuseks
	}

	// Testimiseks väljastan, hiljem ära võtta
	/*std::cout << "Ruudud (kasutaja ei näe seda):\n";
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if (i % this->laius == 0)
		{
			std::cout << std::endl;
		}
		if (this->ruudud.at(i) >= 0) std::cout << " "; //Lisatühik kui ei ole negatiivne, et saaks paremini aru
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
void Minesweeper::prindiMangulaud() {
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if (i % this->laius == 0) std::cout << std::endl;
		std::cout << this->mangijaLaud.at(i) << ' ';
	}
	std::cout << "\n";
}
void Minesweeper::koostaManguala(int protsent) {
	this->koostaPommid(protsent);
	this->koostaRuudud();
	this->koostaMangijaLaud();
}
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
bool Minesweeper::kasMangOnLabi() {
	return this->mangOnLabi;
}