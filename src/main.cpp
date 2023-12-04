#include <main.hpp>

constexpr int WIERZCHOLEK_MAX = 500000;
int tablica[500][500];
int ILOSC_WIERZCHOLKOW = 0;
int GESTOSC = 0;
std::vector<long long> TABLICA_WIERZCHOLKOW(WIERZCHOLEK_MAX + 5);
std::vector<std::vector<std::pair<long long, long long>>> graf;
std::priority_queue<std::pair<long long, long long>> kolejka;


void wygenerujGraf(const std::string &nazwa_pliku)
{
    std::ofstream plik(nazwa_pliku);
    plik << ILOSC_WIERZCHOLKOW << " " << GESTOSC << std::endl;

    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<> dist(0, ILOSC_WIERZCHOLKOW - 1);

    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < GESTOSC; i++)
    {
        int a = dist(rng);
        int b = dist(rng);
        if (a != b)
            edges.emplace_back(a, b);
    }
    std::shuffle(edges.begin(), edges.end(), rng);
    for (const auto &[a, b] : edges)
    {
        int waga = dist(rng) + 1;
        plik << a << " " << b << " " << waga << std::endl;
    }
    plik.close();
}

int main()
{
    int wybor;
    std::string nazwa_pliku;

    while (true)
    {
        std::cout << "1. Wygeneruj graf" << std::endl;
        std::cout << "2. Wczytaj graf i wyswietl go" << std::endl;
        std::cout << "3. Sredni czas dla 100 powtorzen" << std::endl;
        std::cin >> wybor;

        switch (wybor)
        {
        case 1:
            std::cout << "Podaj ilosc elementow grafu: " << std::endl;
            std::cin >> ILOSC_WIERZCHOLKOW;
            std::cout << "Podaj gestosc grafu (0-100%): " << std::endl;
            std::cin >> GESTOSC;
            std::cout << "Podaj nazwe pliku: " << std::endl;
            std::cin >> nazwa_pliku;
            wygenerujGraf(nazwa_pliku);
            std::cout << "Graf zostal wygenerowany" << std::endl;
            break;

        case 2:
            std::cout << "Podaj nazwe pliku: " << std::endl;
            std::cin >> nazwa_pliku;
            wczytajDane_L(nazwa_pliku);
            wczytajDane_M(nazwa_pliku);
            std::cout << "Pomyslnie wczytano dane z pliku\n"
                      << std::endl;
            wypiszGraf_L();
            wypiszGraf_M();
            break;

        case 3:
            int s;
            std::cout << "Podaj nazwe pliku: " << std::endl;
            std::cin >> nazwa_pliku;
            std::cout << "Podaj ilosc wierzcholkow: " << std::endl;
            std::cin >> ILOSC_WIERZCHOLKOW;
            std::cout << "Podaj gestosc grafu (0-100%): " << std::endl;
            std::cin >> GESTOSC;
            std::cout << "Podaj wierzcholek poczatkowy: " << std::endl;
            std::cin >> s;

            double M = 0.0, L = 0.0;
            for (int i = 0; i < 100; i++)
            {
                wygenerujGraf(nazwa_pliku);

                auto start_time = std::chrono::high_resolution_clock::now();
                Dijkstra_L(s);
                auto end_time = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> duration_ms = end_time - start_time;
                L += duration_ms.count();

                start_time = std::chrono::high_resolution_clock::now();
                Dijkstra_M(s);
                end_time = std::chrono::high_resolution_clock::now();
                duration_ms = end_time - start_time;
                double czasM = duration_ms.count();
                M += czasM;
            }

            std::cout << "Czas reprezentacji listowej: " << L / 100.0 << "ms" << std::endl;
            std::cout << "Czas reprezentacji macierzowej: " << M / 100.0 << "ms" << std::endl;
            break;
        }
    }
    return 0;
}