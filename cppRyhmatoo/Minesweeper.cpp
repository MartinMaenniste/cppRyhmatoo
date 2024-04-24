#include "Minesweeper.h"

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
		pommid.insert(rand() % (korgus*laius)); //T�idan kuni on piisavalt pomme
	}

	//N��d lisan pommide vektorisse pommid ja t�hjad kohad
	size_t pikkus = this->korgus * this->laius;
	auto eiLeitudIteraator = pommid.end();
	for (int indeks = 0; indeks < pikkus; indeks++) {
		//find tagastab iteraatori otsitavale indeksile hulgas, kui see on end(), siis ei leitud
		if (pommid.find(indeks) == eiLeitudIteraator) this->pommid.push_back(false);
		else this->pommid.push_back(true);
	}

	//  Testimiseks, et t��tab, hiljem �ra v�tta
	pikkus = 0;
	for (auto iter = this->pommid.begin(), lopp = this->pommid.end(); iter != lopp; iter++, pikkus++) {
		if (pikkus % this->laius == 0)
		{
			std::cout << std::endl;
		}
		std::cout << *iter << " ";
	}
}
void Minesweeper::koostaRuudud() {
	//Igale ruudule v��rtustada loendaPommid() v��rtus antud indeksil
}
int loendaPommid(int indeks) {
	//Leiab indeksi �mber asuvad pommid - k�ik on �ks pikk j�rjend, vaja kontrollida maatriksi m�ttes tema �mber olemist
	return 0;
}