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
	//Maatriksid on ühe pika jadana
	std::vector<bool> pommid; //Pommide asetused
	std::vector<int> ruudud; //Mängulaua numbrite/tühjade kohtade asetused, arvutatakse pommid vektori põhjal
							 // -1 on pomm ise (pole vaja, sest kontrollitakse pommi asetust kõigepealt, aga igaks juhuks, et oleks selgem)
	std::vector<char> mangijaLaud; //Mängulaud, mida mängija näeb - 
								   // ' ' on tühi koht (pole ühtegi pommi kõrval) 
								   // '!' on mängija asetatud lipp 
								   // 'n' on konkreetne number, mis ütleb, mitu pommi on ümberringi 
								   // 'X' on pomm - kui mängija avas pommi, näidatakse kogu mängulauda ja mäng lõppeb

public:
	Minesweeper(int, int);

	void koostaPommid(int);
	void koostaRuudud();
	void koostaMangijaLaud();


};