#pragma once
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <iterator>
#include <iostream>
#include <SFML/Graphics.hpp>

class Minesweeper {
private:
	sf::Texture pomm;
	sf::Texture avamata;
	sf::Texture tuhi;
	sf::Texture lipp;
	sf::Texture one;
	sf::Texture two;
	sf::Texture three;
	sf::Texture four;
	sf::Texture five;
	sf::Texture six;
	sf::Texture seven;
	sf::Texture eight;

	std::map<char, sf::Texture> charTekstuuriks;

	bool mangOnLabi, oliKaotus;
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
	void laeTekstuurid(std::string);
	bool koikRuududAvatud();
public:
	Minesweeper(int, int, std::string);
	void koostaManguala(int);
	void kuvaMangulaud(sf::RenderWindow&);
	void kuvaVoiduEkraan(sf::RenderWindow&);
	void kuvaKaotusEkraan(sf::RenderWindow&);
	bool teeKaik(int, int, bool); //Tagastab true, kui sellist k�iku sai teha, false, kui see ei ole lubatud k�ik (prindib meetodi sees v�lja, miks ei ole lubatud)
								  // boolean kirjeldab, kas m�ngija tahab panna antud ruudule lippu v�i seda avada - true, kui tahab panna lippu, false, kui tahab seda avada
	void handleEvent(sf::Event&, const sf::Vector2u&);
	bool kasMangOnLabi();
	bool kasOliKaotus();
};