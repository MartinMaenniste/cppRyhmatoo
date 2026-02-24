#include "Minesweeper.h"


int main() {

	std::unique_ptr<Minesweeper> ms;
	try {
		ms = std::make_unique<Minesweeper>("Pildid"); // Constructor takes directory with pictures.
	}												// When a specific picture fails to load, filename is thrown as error.
	catch (std::string s) {
		std::cout << "Pildifailist " << s << " sisselugemine ebaõnnestus!\n";
		return 0;
	}

	sf::RenderWindow window(sf::VideoMode({640, 480}), "Minesweeper", sf::Style::Default);//, sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);

	sf::View view;
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) // Mouseevent instead!!
				ms->handleEvent(window, mouseButton->button);
			if (const auto* resized = event->getIf<sf::Event::Resized>())
			{
        		sf::FloatRect visibleArea(
                {0.f, 0.f},
                {static_cast<float>(resized->size.x),
                static_cast<float>(resized->size.y)}
            	);

            	view = sf::View(visibleArea);
            	window.setView(view);
    		}
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
	// Esialgne versioon - terminalis
	int valitudRida, valitudVeerg;
	bool lipuPanek, korrektneSisend{false};
	char valik;
	
	while (!ms->kasMangOnLabi())
	{
		ms->prindiMangulaud();
		korrektneSisend = false;

		//Tuleks kontrollida iga v��rtuse puhul veel, et sisestati �ige andmet��p - errorite kinnip��dmisega ilmselt
		
		std::cout << "Vali rida: ";
		std::cin >> valitudRida;
		std::cout << "Vali veerg: ";
		std::cin >> valitudVeerg;
		while (!korrektneSisend) {
			std::cout << "Vali kas panna lipp v�i avada see m�ngulaua ruut (l - pane lipp, a - ava ruut): ";
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