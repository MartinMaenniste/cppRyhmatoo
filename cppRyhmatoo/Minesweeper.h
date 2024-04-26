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
	//Maatriksid on �he pika jadana
	std::vector<bool> pommid; //Pommide asetused
	std::vector<int> ruudud; //M�ngulaua numbrite/t�hjade kohtade asetused, arvutatakse pommid vektori p�hjal
							 // -1 on pomm ise (pole vaja, sest kontrollitakse pommi asetust k�igepealt, aga igaks juhuks, et oleks selgem)
	std::vector<char> mangijaLaud; //M�ngulaud, mida m�ngija n�eb -
								   // '?' on koht, mida m�ngija pole veel avanud
								   // ' ' on t�hi koht (pole �htegi pommi k�rval) 
								   // '!' on m�ngija asetatud lipp 
								   // 'n' on konkreetne number, mis �tleb, mitu pommi on �mberringi 
								   // 'X' on pomm - kui m�ngija avas pommi, n�idatakse kogu m�ngulauda ja m�ng l�ppeb
	void koostaPommid(int);
	void koostaRuudud();
	void koostaMangijaLaud();
public:
	Minesweeper(int, int);

	void koostaManguala(int);
	void prindiMangulaud();
};