#include "Minesweeper.h"

int main() {
	srand(static_cast<unsigned int> (time(0)));

	std::cout << "Vali mängulaua kõrgus: ";
	int korgus;
	std::cin >> korgus;

	std::cout << "Vali mängulaua laius: ";
	int laius;
	std::cin >> laius;

	std::unique_ptr<Minesweeper> ms = std::make_unique<Minesweeper>(korgus, laius);

	std::cout << "Mitu protsenti ruutudest võiksid olla pommid: ";
	int protsent;
	std::cin >> protsent;

	ms->koostaPommid(protsent);

	return 0;
}