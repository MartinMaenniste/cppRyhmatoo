#include "Minesweeper.h"


int main() {

	std::unique_ptr<Minesweeper> ms;
	try {
		ms = std::make_unique<Minesweeper>("Images");
	}
	catch (std::string s) {
		std::cout << "Pildifailist " << s << " sisselugemine ebaõnnestus!\n";
		return 0;
	}

	sf::RenderWindow window(sf::VideoMode(640, 640), "Minesweeper");
	window.setFramerateLimit(30);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased)
				ms->handleEvent(event, window.getSize());
		}

		window.clear();
		ms->kuvaMangulaud(window);
		window.display();

		if (ms->kasMangOnLabi()) {
			if (ms->kasOliKaotus()) ms->kuvaKaotusEkraan(window);
			else ms->kuvaVoiduEkraan(window);
			ms->kusiManguLauaAndmed();
		}
	}
	/*
	int valitudRida, valitudVeerg;
	bool lipuPanek, korrektneSisend{false};
	char valik;
	
	while (!ms->kasMangOnLabi())
	{
		ms->prindiMangulaud();
		korrektneSisend = false;

		//Tuleks kontrollida iga väärtuse puhul veel, et sisestati õige andmetüüp - errorite kinnipüüdmisega ilmselt
		
		std::cout << "Vali rida: ";
		std::cin >> valitudRida;
		std::cout << "Vali veerg: ";
		std::cin >> valitudVeerg;
		while (!korrektneSisend) {
			std::cout << "Vali kas panna lipp või avada see mängulaua ruut (l - pane lipp, a - ava ruut): ";
			std::cin >> valik;
			if (valik == 'l') {
				lipuPanek = true;
				korrektneSisend = true;
			}
			else if (valik == 'a') {
				lipuPanek = false;
				korrektneSisend = true;
			}
		}
		ms->teeKaik(valitudRida, valitudVeerg, lipuPanek);
	}*/

	return 0;
}