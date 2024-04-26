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
	int korgus;
	int laius;
	size_t vektoritePikkus;
	//Maatriksid on ühe pika jadana
	std::vector<bool> pommid; //Pommide asetused
	std::vector<int> ruudud; //Mängulaua numbrite/tühjade kohtade asetused, arvutatakse pommid vektori põhjal
							 // -1 on pomm ise (pole vaja, sest kontrollitakse pommi asetust kõigepealt, aga igaks juhuks, et oleks selgem)
	std::vector<char> mangijaLaud; //Mängulaud, mida mängija näeb -
								   // '?' on koht, mida mängija pole veel avanud
								   // ' ' on tühi koht (pole ühtegi pommi kõrval) 
								   // '!' on mängija asetatud lipp 
								   // 'n' on konkreetne number, mis ütleb, mitu pommi on ümberringi 
								   // 'X' on pomm - kui mängija avas pommi, näidatakse kogu mängulauda ja mäng lõppeb
	void koostaPommid(int);
	void koostaRuudud();
	void koostaMangijaLaud();
public:
	Minesweeper(int, int);

	void koostaManguala(int);
	void prindiMangulaud();
};