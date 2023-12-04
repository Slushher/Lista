#pragma once

#include <vector>
#include <string>
#include <iostream>

class Macierz{
public:
    void wypiszGraf();
    void dodajKrawedzs(int x, int y, int z);
    void Dijkstra(int WIERZCHOLEK_POCZATKOWY);
    void wczytajDane(std::string nazwa_pliku);
};