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
	size_t pikkus = this->korgus * this->laius;
	auto eiLeitudIteraator = pommid.end();
	for (int indeks = 0; indeks < pikkus; indeks++) {
		//find tagastab iteraatori otsitavale indeksile hulgas, kui see on end(), siis ei leitud
		if (pommid.find(indeks) == eiLeitudIteraator) this->pommid.push_back(false);
		else this->pommid.push_back(true);
	}

	//  Testimiseks väljastan, hiljem ära võtta
	pikkus = 0;
	for (auto iter = this->pommid.begin(), lopp = this->pommid.end(); iter != lopp; iter++, pikkus++) {
		if (pikkus % this->laius == 0)
		{
			std::cout << std::endl;
		}
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
}
void Minesweeper::koostaRuudud() {
	//Igale ruudule väärtustada loendaPommid() väärtus antud indeksil
	size_t pikkus = this->pommid.size();
	for (size_t i = 0; i < pikkus; i++) {
		if(this->pommid.at(i)) this->ruudud.push_back(-1); //Kui on pomm, siis praegu paneme -1, pole otseselt vaja, aga nii selgem
		else this->ruudud.push_back(loendaPommid(i, this->pommid, pikkus, this->laius)); //Kui pommi ei ole, loendame ümberringsed pommid ja seame selle väärtuseks
	}

	// Testimiseks väljastan, hiljem ära võtta
	for (auto iter = this->ruudud.begin(), lopp = this->ruudud.end(); iter != lopp; iter++, pikkus++) {
		if (pikkus % this->laius == 0)
		{
			std::cout << std::endl;
		}
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
}