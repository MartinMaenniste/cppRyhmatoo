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

	ms->koostaPommid(protsent);

	return 0;
}