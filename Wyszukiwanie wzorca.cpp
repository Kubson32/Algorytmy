#include <iostream>
#include <string>

using namespace std;

int KnuttMorrisPratt(string s, string w)
{
    int* PI;
    PI = new int[w.length()];


    for (int i = 0; i < w.length(); i++)
        PI[i] = 0;

    int b = -1;
    PI[0] = -1;


    for (int i = 1; i < w.length(); i++)
    {
        while ((b > -1) && w[b] != w[i - 1]) b = PI[b];
        ++b;
        if (i == w.length() || (w[i] != w[b])) PI[i] = b;
        else PI[i] = PI[b];
    }

    int pos = -1;
    b = 0;

    for (int i = 0; i < s.length(); i++)
    {
        while ((b > -1) && (w[b] != s[i])) b = PI[b];
        if (++b == w.length())
        {
            while (pos < i - b + 1)
                pos++;
            b = PI[b];
        }
    }

    return pos;
}

int main()
{
    int sz, wys;
    cout << "Wypisz szerokosc tablicy i wysokosc tablicy:" << endl;
    cin >> sz;
    cin >> wys;

    string* right = new string[wys];
    string* left = new string[wys];
    string* up = new string[sz];
    string* down = new string[sz];
    char litery;

    cout << "Wpisz litery:" << endl;

    for (int i = 0; i < wys; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            cin >> litery;
            right[i].push_back(litery);
        }
        for (int j = sz - 1; j >= 0; j--)
            left[i].push_back(right[i][j]);
    }

    for (int i = 0; i < wys; i++)
    {
        for (int j = 0; j < sz; j++)
            down[j].push_back(right[i][j]);
    }
    for (int i = 0; i < sz; i++)
    {
        for (int j = wys - 1; j >= 0; j--)
            up[i].push_back(down[i][j]);
    }


    cout << endl << "Wpisz szukany wzorzec:" << endl;
    string wzor;
    cin >> wzor;
    int pos, y;
    string s;

    for (int i = 0; i < wys; i++)
    {
        pos = 0;
        y = 0;
        s = right[i];
        while (pos != -1)
        {
            pos = KnuttMorrisPratt(s, wzor);
            if (pos != -1)
            {
                cout <<endl<< "Wzorzec na prawo od pozycji: " << pos + 1 + y<< "," << i + 1 << endl;
                s.erase(0, pos + 1);
                y += pos + 1;
            }
        }
    }

    for (int i = 0; i < wys; i++)
    {
        pos = 0;
        y = 0;
        s = left[i];
        while (pos != -1)
        {
            pos = KnuttMorrisPratt(s, wzor);
            if (pos != -1)
            {
                cout << endl<<"Wzorzec na lewo od pozycji:" << i + 1 << "," << pos + 1 + y << endl;
                s.erase(0, pos + 1);
                y += pos + 1;
            }
        }
    }

    for (int i = 0; i < sz; i++)
    {
        pos = 0;
        y = 0;
        s = up[i];
        while (pos != -1)
        {
            pos = KnuttMorrisPratt(s, wzor);
            if (pos != -1)
            {
                cout <<endl<< "Wzorzec w gore od pozycji:"<< pos+1+y << "," << i+1 << endl;
                s.erase(0, pos + 1);
                y += pos + 1;
            }
        }
    }

    for (int i = 0; i < sz; i++)
    {
        pos = 0;
        y = 0;
        s = down[i];
        while (pos != -1)
        {
            pos = KnuttMorrisPratt(s, wzor);
            if (pos != -1)
            {
                cout <<endl<< "Wzorzec w dol od pozycji:" << i + 1 << "," << pos + 1 + y << endl;
                s.erase(0, pos + 1);
                y += pos + 1;
            }
        }
    }

    return 0;
}