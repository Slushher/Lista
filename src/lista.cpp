void dodajKrawedz_L(int u, int v, int wt)
{
    if (u >= 0 && v >= 0 && u < ILOSC_WIERZCHOLKOW && v < ILOSC_WIERZCHOLKOW)
    {
        graf[u].emplace_back(std::make_pair(v, wt));
        graf[v].emplace_back(std::make_pair(u, wt));
    }
    else
    {
        std::cout << "Zly wierzcholek krawedzi"
                  << "\n";
    }
}
void wczytajDane_L(std::string nazwa_pliku)
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
    int KRAWEDZ = 0, WIERZCHOLEK1 = 0, WAGA = 0, WIERZCHOLEK2 = 0;
    plik >> ILOSC_WIERZCHOLKOW;
    plik >> GESTOSC;
    KRAWEDZ = (ILOSC_WIERZCHOLKOW * GESTOSC / 100);
    std::cout<<KRAWEDZ<<"\n";
    graf.clear();
    graf.resize(ILOSC_WIERZCHOLKOW);
    for (int i = 0; i < KRAWEDZ; i++)
    {
        plik >> WIERZCHOLEK1;
        plik >> WIERZCHOLEK2;
        plik >> WAGA;
        dodajKrawedz_L(WIERZCHOLEK1, WIERZCHOLEK2, WAGA);
    }
    plik.close();
}

void wypiszGraf_L()
{
    int v = 0, waga = 0;
    for (int u = 0; u < ILOSC_WIERZCHOLKOW; u++)
    {
        std::cout << u << "--> \n";
        for (auto it = graf[u].begin(); it != graf[u].end(); it++)
        {
            v = it->first;
            waga = it->second;
            std::cout << "\t" << v << " = " << waga << "\n";
        }
    }
    std::cout << "\n";
}

void Dijkstra_L(int WIERZCHOLEK_POCZATKOWY)
{
    std::vector<bool> odwiedziny(WIERZCHOLEK_MAX + 5);
    for (int i = 0; i < WIERZCHOLEK_MAX; i++)
    {
        odwiedziny[i] = false;
        TABLICA_WIERZCHOLKOW[i] = INT_MAX;
    }

    TABLICA_WIERZCHOLKOW[WIERZCHOLEK_POCZATKOWY] = 0;
    kolejka.push({0, WIERZCHOLEK_POCZATKOWY});

    while (!kolejka.empty())
    {
        if (kolejka.top().second >= 0 && kolejka.top().second < graf.size())
        {
            int x = kolejka.top().second;
            kolejka.pop();

            if (!odwiedziny[x])
            {
                odwiedziny[x] = true;

                for (int i = 0; i < graf[x].size(); i++)
                {
                    int v = graf[x][i].first;
                    int waga = graf[x][i].second;

                    if (TABLICA_WIERZCHOLKOW[v] > TABLICA_WIERZCHOLKOW[x] + waga)
                    {
                        TABLICA_WIERZCHOLKOW[v] = TABLICA_WIERZCHOLKOW[x] + waga;
                        kolejka.push({-TABLICA_WIERZCHOLKOW[v], v});
                    }
                }
            }
        }
        else
        {
            kolejka.pop();
        }
    }
}
