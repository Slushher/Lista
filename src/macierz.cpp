#include <macierz.hpp>

void Macierz::wypiszGraf()
{
    for (int i = 0; i < ILOSC_WIERZCHOLKOW; i++)
    {
        for (int j = 0; j < ILOSC_WIERZCHOLKOW; j++)
        {
            if (j == 0)
            {
                std::cout << "|";
            }
            if (tablica[i][j] == INT_MAX)
            {
                std::cout << " INF ";
            }
            else
            {
                std::cout << " " << tablica[i][j] << " ";
            }
            if (j == ILOSC_WIERZCHOLKOW - 1)
            {
                std::cout << "|" << std::endl;
            }
        }
    }
}

void Macierz::dodajKrawedz(int x, int y, int z)
{
    tablica[x][y] = z;
}


void Macierz::Dijkstra(int WIERZCHOLEK_POCZATKOWY)
{
    std::vector<int> dystans(ILOSC_WIERZCHOLKOW);
    std::vector<bool> SPT(ILOSC_WIERZCHOLKOW);
    dystans[WIERZCHOLEK_POCZATKOWY] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> kolejka_priotetytowa;
    kolejka_priotetytowa.push({0, WIERZCHOLEK_POCZATKOWY});

    while (!kolejka_priotetytowa.empty())
    {
        int u = kolejka_priotetytowa.top().second;
        kolejka_priotetytowa.pop();

        if (SPT[u])
            continue;
        SPT[u] = true;

        for (int v = 0; v < ILOSC_WIERZCHOLKOW; ++v)
        {
            if (!SPT[v] && tablica[u][v] != 0 && dystans[u] != std::numeric_limits<int>::max() &&
                dystans[u] + tablica[u][v] < dystans[v])
            {
                dystans[v] = dystans[u] + tablica[u][v];
                kolejka_priotetytowa.push({dystans[v], v});
            }
        }
    }
}

void Macierz::wczytajDane_M(std::string nazwa_pliku)
{
    std::ifstream plik(nazwa_pliku);
    if (!plik.good())
    {
        std::cout << "Zla nazwa pliku." << std::endl;
        return;
    }
    if (!plik.is_open())
    {
        std::cout << "Nie udalo sie otworzyc pliku." << std::endl;
        return;
    }
    int KRAWEDZ = 0, ILOSC_WIERZCHOLKOW2 = 0, waga = 0, ILOSC_WIERZCHOLKOW1 = 0;
    plik >> ILOSC_WIERZCHOLKOW;
    plik >> GESTOSC;
    KRAWEDZ = (ILOSC_WIERZCHOLKOW * (ILOSC_WIERZCHOLKOW - 1)) / 2;
    std::cout<<KRAWEDZ<<"\n";
    for (int i = 0; i < KRAWEDZ; i++)
    {
        plik >> ILOSC_WIERZCHOLKOW1;
        plik >> ILOSC_WIERZCHOLKOW2;
        plik >> waga;

        if (ILOSC_WIERZCHOLKOW1 >= 0 && ILOSC_WIERZCHOLKOW1 < ILOSC_WIERZCHOLKOW &&
            ILOSC_WIERZCHOLKOW2 >= 0 && ILOSC_WIERZCHOLKOW2 < ILOSC_WIERZCHOLKOW)
        {
            dodajKrawedz_M(ILOSC_WIERZCHOLKOW1, ILOSC_WIERZCHOLKOW2, waga);
        }
        else
        {
            std::cout << "Zle indeksy wiercholkow" << std::endl;
        }
    }
    plik.close();
}