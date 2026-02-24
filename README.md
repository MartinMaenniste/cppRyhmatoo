# Kirjeldus
See grupitöö on kloon teadatuntud mängust *Minesweeper*, kasutades loogikaks C++ programmeerimiskeelt ning SFML teeki graafika jaoks.<br />
NB! Projekt on veel arendamisjärgus. Võib esineda vigu mängu jooksmisel ning lubatud funktsionaalsused ei pruugi veel eksisteerida!<br />

# Funktsionaalsused
 - Saab valida mängulaua suuruse (kõrguse ja laiuse eraldi)
 - Saab valida, mitu protsenti ruutudest on pommid
 - Saab valida terminali ja graafilise liidese vahel

# Projekti ülesehitus
 .<br />
 ├─ Pildid<br />
 │    └─ *.png - Kõik pildifailid mängulaua ruutude jaoks.<br />
 ├─ main.cpp - Loob mängu objekti ja alustab mängutsüklit.<br />
 ├─ Minesweeper.cpp<br />
 ├─ Minesweeper.h - Mängu loogika.<br />
 ├─ Makefile - Kompileerib mängu ja teeb jooksutatava faili *rungame* (muutmise ja kasutamise juhend allpool).<br />
 └─ README.md

# Mängu kasutamise juhend
## Linux
Üldise info SFML projekti kasutamise kohta leiab ametlikust vikist (https://www.sfml-dev.org/tutorials/3.0/getting-started/linux/#compiling-an-sfml-program) <br />
Mängule on loodud ka *Makefile*, et automaatselt kompileerida ja linkida.<br />
```shell
make
./rungame
```
#### Mängu jooksutamiseks on vaja järgmisi pakette:<br />
 - SFML, versioon 3 (lihtsaim on kasutada enda süsteemi paketihaldurit)<br />
 - C++ keele kompilaator (Vaikimisi kasutatakse g++, endale sobiva kompilaatori kasutamiseks muuta failis "Makefile" muutujat "COMPILER")<br />
 - make (käsk ei pruugi kõikide süsteemidega kaasa tulla)<br />
<br />
#### Näidis programmi kasutamisest:<br />
```shell
git clone https://github.com/MartinMaenniste/cppRyhmatoo.git
cd cppRyhmatoo

make
./rungame
```<br />
## Windows
Programmi pole veel Windows operatsioonisüsteemi peal testitud!<br />
Üldised tingimused programmi kasutamiseks on samad, mis Linux'i puhul - SFML 3 ja C++ kompilaator. Sõltuvalt, kas programmi kasutada läbi mõne konkreetse IDE või *make* funktsionaalsuse, on vaja programm erinevalt sätestada.<br />
Visual Studio puhul on aitab ametlik vikileht - https://www.sfml-dev.org/tutorials/3.0/getting-started/visual-studio/<br />
Kasutades CMake'i, võib abiks olla - https://www.sfml-dev.org/tutorials/3.0/getting-started/cmake/
