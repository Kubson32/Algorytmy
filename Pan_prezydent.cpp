#include<iostream>
#include<numeric>
#include<vector>
#include<algorithm>

using namespace std;

typedef  pair<int, int> vec;

struct Disjoinset
{
    int* rodzic, * ranga;
    int n;

    Disjoinset(int n)
    {

        this->n = n;
        rodzic = new int[n + 1];
        ranga = new int[n + 1];

        for (int i = 0; i <= n; i++)
        {
            ranga[i] = 0;

            rodzic[i] = i;
        }
    }

    int find(int u)
    {
        if (u != rodzic[u])
            rodzic[u] = find(rodzic[u]);
        return rodzic[u];
    }

    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        if (ranga[x] > ranga[y])
            rodzic[y] = x;
        else
            rodzic[x] = y;

        if (ranga[x] == ranga[y])
            ranga[y]++;
    }
};

struct Graf
{
    int wierz, kr;
    vector< pair <int, vec> > kraw;

    Graf(int wierz, int kr)
    {
        this->wierz = wierz;
        this->kr = kr;
    }

    void dodaj(int u, int v, int w)
    {
        kraw.push_back({ w, {u, v} });
    }
    vector <int> kruskal();
};

vector <int> Graf::kruskal()
{
    sort(kraw.begin(), kraw.end());

    Disjoinset ds(wierz);

    vector< pair<int, vec> >::iterator it;
    vector <int> w;

    for (it = kraw.begin(); it != kraw.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v)
        {
            cout << "Miedzy: " << u << " i " << v << endl;

            w.push_back(it->first);

            ds.merge(set_u, set_v);
        }
    }

    return w;
}

int superdroga(vector<int> droga, int K)
{
    int waga = 0;

    for_each(droga.begin(), droga.end(), [&](int n)
        {
            waga += n;
        });

    int N = droga.size();

    if (waga > K)
    {
        sort(droga.begin(), droga.end());
        droga[N - 1] = 1;
        return superdroga(droga, K);
    }

    else
    {
        return waga;
    }
}

int main()
{
    int miasta;
    int drogi;
    int K;
    int u, w, x; //u,w - miasta; x - koszt utrzymania drogi
    int liczba_sd = 0;
    int waga = 0;

    vector <int> suma;

    cout << "Witaj w grze Pan Prezydent!" << endl << endl;

    cout << "Podaj liczbe miast, drog je laczacych oraz maksymalny koszt utrzymania:" << endl;

    cin >> miasta >> drogi >> K;

    Graf gra(miasta, drogi);

    for (int i = 0; i < drogi; i++)
    {
        cout << "Podaj 2 miasta oraz koszt utrzymania drogi miedzy nimi:" << endl;
        cin >> u >> w >> x;
        gra.dodaj(u, w, x);
    }

    cout << "Wybrane drogi:" << endl;

    suma = gra.kruskal();

    cout << "Koszt utrzymania po zamianie drog na superdrogi:" << endl;

    for_each(suma.begin(), suma.end(), [&](int x)
        {
            waga += x;
        });

    if (waga > K)
    {
        liczba_sd++;
        cout << superdroga(suma, K) << endl;
        cout << "Liczba superdrog:" << liczba_sd << endl;
    }

    cout << endl << "Zdobyles osiagniecie Wielki Administrator!" << endl;

    return 0;
}