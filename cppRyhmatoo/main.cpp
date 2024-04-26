#include "Minesweeper.h"

int main() {
	srand(static_cast<unsigned int> (time(0)));

	std::cout << "Vali m�ngulaua k�rgus: ";
	int korgus;
	std::cin >> korgus;

	std::cout << "Vali m�ngulaua laius: ";
	int laius;
	std::cin >> laius;

	std::unique_ptr<Minesweeper> ms = std::make_unique<Minesweeper>(korgus, laius);

	std::cout << "Mitu protsenti ruutudest v�iksid olla pommid: ";
	int protsent;
	std::cin >> protsent;

	ms->koostaManguala(protsent);

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
	}

	return 0;
}