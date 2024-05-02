#pragma once
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <iterator>
#include<iostream>

class Minesweeper {
private:
	bool mangOnLabi;
	int korgus;
	int laius;
	size_t vektoritePikkus;
	//Maatriksid on ühe pika jadana
	std::vector<bool> pommid; //Pommide asetused
	std::vector<int> ruudud; //Mängulaua numbrite/tühjade kohtade asetused, arvutatakse pommid vektori põhjal
							 // -1 on pomm ise (vaja tühjade ruutude avamise kontrolliks)
	std::vector<char> mangijaLaud; //Mängulaud, mida mängija näeb -
								   // '?' on koht, mida mängija pole veel avanud
								   // ' ' on tühi koht (pole ühtegi pommi kõrval) 
								   // '!' on mängija asetatud lipp 
								   // 'n' on konkreetne number, mis ütleb, mitu pommi on ümberringi 
								   // 'X' on pomm - kui mängija avas pommi, näidatakse kogu mängulauda ja mäng lõppeb
	void koostaPommid(int);
	void koostaRuudud();
	void koostaMangijaLaud();
	void reedaMangulaud();
	void avaTuhjadRuudud(size_t);
public:
	Minesweeper(int, int);

	void koostaManguala(int);
	void prindiMangulaud();
	bool teeKaik(int, int, bool); //Tagastab true, kui sellist käiku sai teha, false, kui see ei ole lubatud käik (prindib meetodi sees välja, miks ei ole lubatud)
								  // boolean kirjeldab, kas mängija tahab panna antud ruudule lippu või seda avada - true, kui tahab panna lippu, false, kui tahab seda avada
	bool kasMangOnLabi();
};