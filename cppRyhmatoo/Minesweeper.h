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
	//Maatriksid on �he pika jadana
	std::vector<bool> pommid; //Pommide asetused
	std::vector<int> ruudud; //M�ngulaua numbrite/t�hjade kohtade asetused, arvutatakse pommid vektori p�hjal
							 // -1 on pomm ise (vaja t�hjade ruutude avamise kontrolliks)
	std::vector<char> mangijaLaud; //M�ngulaud, mida m�ngija n�eb -
								   // '?' on koht, mida m�ngija pole veel avanud
								   // ' ' on t�hi koht (pole �htegi pommi k�rval) 
								   // '!' on m�ngija asetatud lipp 
								   // 'n' on konkreetne number, mis �tleb, mitu pommi on �mberringi 
								   // 'X' on pomm - kui m�ngija avas pommi, n�idatakse kogu m�ngulauda ja m�ng l�ppeb
	void koostaPommid(int);
	void koostaRuudud();
	void koostaMangijaLaud();
	void reedaMangulaud();
	void avaTuhjadRuudud(size_t);
public:
	Minesweeper(int, int);

	void koostaManguala(int);
	void prindiMangulaud();
	bool teeKaik(int, int, bool); //Tagastab true, kui sellist k�iku sai teha, false, kui see ei ole lubatud k�ik (prindib meetodi sees v�lja, miks ei ole lubatud)
								  // boolean kirjeldab, kas m�ngija tahab panna antud ruudule lippu v�i seda avada - true, kui tahab panna lippu, false, kui tahab seda avada
	bool kasMangOnLabi();
};