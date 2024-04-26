#include "Minesweeper.h"

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

Minesweeper::Minesweeper(int k, int l) {
	this->korgus = k;
	this->laius = l;
	this->vektoritePikkus = k*l;
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
	std::cout << "Pommid (kasutaja ei n�e seda):\n";
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if (i % this->laius == 0)
		{
			std::cout << std::endl;
		}
		std::cout << this->pommid.at(i) << " ";
	}
	std::cout << "\n\n";
}
void Minesweeper::koostaRuudud() {
	//Igale ruudule v��rtustada loendaPommid() v��rtus antud indeksil
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if(this->pommid.at(i)) this->ruudud.push_back(-1); //Kui on pomm, siis praegu paneme -1, pole otseselt vaja, aga nii selgem
		else this->ruudud.push_back(loendaPommid(i, this->pommid, this->vektoritePikkus, this->laius)); //Kui pommi ei ole, loendame �mberringsed pommid ja seame selle v��rtuseks
	}

	// Testimiseks v�ljastan, hiljem �ra v�tta
	std::cout << "Ruudud (kasutaja ei n�e seda):\n";
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if (i % this->laius == 0)
		{
			std::cout << std::endl;
		}
		if (this->ruudud.at(i) >= 0) std::cout << " "; //Lisat�hik kui ei ole negatiivne, et saaks paremini aru
		std::cout << this->ruudud.at(i) << " ";
	}
	std::cout << "\n\n";
}
void Minesweeper::koostaMangijaLaud() {
	for (size_t i = 0; i < this->ruudud.size(); i++) {
		this->mangijaLaud.push_back('?');
	}
}
void Minesweeper::prindiMangulaud() {
	for (size_t i = 0; i < this->vektoritePikkus; i++) {
		if (i % this->laius == 0) std::cout << std::endl;
		std::cout << this->mangijaLaud.at(i) << ' ';
	}
}
void Minesweeper::koostaManguala(int protsent) {
	this->koostaPommid(protsent);
	this->koostaRuudud();
	this->koostaMangijaLaud();
}