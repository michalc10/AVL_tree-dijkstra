#include <bits/stdc++.h>

using namespace std;

struct Wezel
{
	unsigned int lAdresIP;
	int waga = 0;
	Wezel* lewy = NULL;
	Wezel* prawy = NULL;
	Wezel* gora = NULL;
};


string zamiana2(unsigned int a)
{
	string x,x1, x2, x3;
	int a2 = 0;
	bool pom = 0;
	while (a != 0)
	{
		if (pom == 1)
		{
			x = '.' + x;
		}
		pom = 1;

		a2 = a % 256;
		a /= 256;

		x1 = "0";
		x2 = "0";
		if (a2 >= 100)
		{
			x1 = a2 / 100 + '0';
			a2 %= 100;
		}
		if (a2 >= 10)
		{
			x2 = a2 / 10 + '0';
			a2 %= 10;
		}
		x3 = a2 + '0';
		if(x1 =="0" && x2=="0")
            x = x3 + x;
        else if(x1 == "0")
            x = x2 + x3 + x;
        else
            x = x1 + x2 + x3 + x;
	}
	return x;
}
unsigned int zamiana(string a)
{
	unsigned int x = 0;
	a = '.' + a;
	int pom = 0, pot = 1, pot10, i = a.length();

	while (i > 0)
	{
		i--;
		pom = 0;
		pot10 = 1;
		while (a[i] != '.')
		{
			pom += (pot10 * (a[i--] - '0'));
			pot10 *= 10;
		}
		x += pot * pom;
		pot *= 256;

	}

	return x;
}


string spacja = "|   ";
void rysuj(Wezel* baza, int x = 0)
{

	if (baza == NULL && x == 0)
		cout << "Brak adresow IP";
	else
	{
		for (int i = 0; i < x; i++)
			cout << spacja;
		cout << zamiana2(baza->lAdresIP) << endl;
		x++;
		if (baza->prawy != NULL)
			rysuj(baza->prawy, x);
		else
		{
			for (int i = 0; i < x; i++)
				cout << spacja;
			cout << "NULL" << endl;
		}

		if (baza->lewy != NULL)
			rysuj(baza->lewy, x);
		else
		{
			for (int i = 0; i < x; i++)
				cout << spacja;
			cout << "NULL" << endl;
		}
	}
	return;
}
////////////////////////////////////////////////////////////////////////////////////// AVL TREE //////////////////////////////////////////////////////////////////////////////////////
int podSiec(Wezel* aktualny, unsigned int podsiec)
{

	if (aktualny == NULL)
		return 0;
	unsigned int akt = aktualny->lAdresIP / 256;
	int licz = 0;
	if (akt == podsiec)
		licz++;
	if (aktualny->prawy != NULL)
	{
		if (podsiec >= akt)
			licz += podSiec(aktualny->prawy, podsiec);
	}
	if (aktualny->lewy != NULL)
	{
		if (podsiec <= akt)
			licz += podSiec(aktualny->lewy, podsiec);
	}
	return licz;
}


void RR(Wezel* aktualny, Wezel** baza)
{
	Wezel* pom = new Wezel;
	pom->gora = aktualny->gora;
	pom->prawy = aktualny->prawy;
	pom->lewy = aktualny->lewy;

	aktualny->lewy = pom->lewy->prawy;
	if (aktualny->lewy != NULL)
		aktualny->lewy->gora = aktualny;
	aktualny->gora = pom->lewy;
	aktualny->gora->prawy = aktualny;
	aktualny = aktualny->gora;
	aktualny->gora = pom->gora;
	if (aktualny->gora == NULL)
	{
		(*baza) = aktualny;
	}
	else
	{
		if (aktualny->gora->prawy == aktualny->prawy)
			aktualny->gora->prawy = aktualny;
		else
			aktualny->gora->lewy = aktualny;
	}

	if (aktualny->waga == 0)
	{
		aktualny->waga = -1;
		aktualny->prawy->waga = 1;
	}
	else
	{
		aktualny->waga = 0;
		aktualny->prawy->waga = 0;
	}


	delete pom;
}

void LR(Wezel* aktualny, Wezel** baza)
{

	Wezel* pom = new Wezel;
	aktualny = aktualny->lewy->prawy;
	pom->gora = aktualny->gora;
	pom->prawy = aktualny->prawy;
	pom->lewy = aktualny->lewy;

	aktualny->lewy = pom->gora;
	aktualny->prawy = pom->gora->gora;

	aktualny->gora = pom->gora->gora->gora;
	if (aktualny->gora == NULL)
	{
		(*baza) = aktualny;
	}
	else
	{
		if (aktualny->gora->prawy == aktualny->prawy)
			aktualny->gora->prawy = aktualny;
		else
			aktualny->gora->lewy = aktualny;
	}


	aktualny->lewy->prawy = pom->lewy;
	aktualny->prawy->lewy = pom->prawy;

	aktualny->lewy->gora = aktualny;
	aktualny->prawy->gora = aktualny;

	if (aktualny->lewy->prawy != NULL)
		aktualny->lewy->prawy->gora = aktualny->lewy;
	if (aktualny->prawy->lewy != NULL)
		aktualny->prawy->lewy->gora = aktualny->prawy;

	delete pom;

	if (aktualny->waga == -1)
	{
		aktualny->lewy->waga = 1;
		aktualny->prawy->waga = 0;
	}
	else if (aktualny->waga == 1)
	{
		aktualny->lewy->waga = 0;
		aktualny->prawy->waga = -1;
	}
	else
	{
		aktualny->lewy->waga = 0;
		aktualny->prawy->waga = 0;
	}
	aktualny->waga = 0;
}

void LL(Wezel* aktualny, Wezel** baza)
{
	Wezel* pom = new Wezel;
	pom->gora = aktualny->gora;
	pom->prawy = aktualny->prawy;
	pom->lewy = aktualny->lewy;

	aktualny->prawy = pom->prawy->lewy;
	if (aktualny->prawy != NULL)
		aktualny->prawy->gora = aktualny;
	aktualny->gora = pom->prawy;
	aktualny->gora->lewy = aktualny;
	aktualny = aktualny->gora;
	aktualny->gora = pom->gora;
	if (aktualny->gora == NULL)
	{
		(*baza) = aktualny;
	}
	else
	{
		if (aktualny->gora->prawy == aktualny->lewy)
			aktualny->gora->prawy = aktualny;
		else
			aktualny->gora->lewy = aktualny;
	}

	if (aktualny->waga == 0)
	{
		aktualny->waga = 1;
		aktualny->lewy->waga = -1;
	}
	else
	{
		aktualny->waga = 0;
		aktualny->lewy->waga = 0;
	}
	delete pom;
}

void RL(Wezel* aktualny, Wezel** baza)
{
	Wezel* pom = new Wezel;
	aktualny = aktualny->prawy->lewy;
	pom->gora = aktualny->gora;
	pom->prawy = aktualny->prawy;
	pom->lewy = aktualny->lewy;

	aktualny->lewy = pom->gora->gora;
	aktualny->prawy = pom->gora;

	aktualny->gora = pom->gora->gora->gora;
	if (aktualny->gora == NULL)
	{
		(*baza) = aktualny;
	}
	else
	{
		if (aktualny->gora->prawy == aktualny->lewy)
			aktualny->gora->prawy = aktualny;
		else
			aktualny->gora->lewy = aktualny;
	}


	aktualny->lewy->prawy = pom->lewy;
	aktualny->prawy->lewy = pom->prawy;

	aktualny->lewy->gora = aktualny;
	aktualny->prawy->gora = aktualny;

	if (aktualny->lewy->prawy != NULL)
		aktualny->lewy->prawy->gora = aktualny->lewy;
	if (aktualny->prawy->lewy != NULL)
		aktualny->prawy->lewy->gora = aktualny->prawy;


	delete pom;

	if (aktualny->waga == -1)
	{
		aktualny->lewy->waga = 1;
		aktualny->prawy->waga = 0;
	}
	else if (aktualny->waga == 1)
	{
		aktualny->lewy->waga = 0;
		aktualny->prawy->waga = -1;
	}
	else
	{
		aktualny->lewy->waga = 0;
		aktualny->prawy->waga = 0;
	}
	aktualny->waga = 0;

}

void popraw_wagi(Wezel* aktualny, Wezel** baza)
{

	while (aktualny->gora != NULL)
	{
		if (aktualny->gora->lewy != NULL)
		{
			if (aktualny->gora->lewy->lAdresIP == aktualny->lAdresIP)
			{
				aktualny->gora->waga += 1;
			}
			else
			{
				aktualny->gora->waga -= 1;
			}
		}
		else
		{
			aktualny->gora->waga -= 1;
		}

		aktualny = aktualny->gora;

		if (aktualny->waga == 0)
			return;


		if (aktualny->waga == 2)
		{
			if (aktualny->lewy->waga == 1)
			{
				RR(aktualny, &(*baza));
			}
			else
			{
				LR(aktualny, &(*baza));
			}
			return;
		}
		if (aktualny->waga == -2)
		{
			if (aktualny->prawy->waga == -1)
			{
				LL(aktualny, &(*baza));
			}
			else
			{
				RL(aktualny, &(*baza));
			}
			return;
		}
	}
}

void dodaj(Wezel** baza, Wezel* nowy)
{
	Wezel* pom = (*baza);

	while (pom != NULL)
	{
		if (pom->lAdresIP == nowy->lAdresIP)
			return;


		if (pom->lAdresIP < nowy->lAdresIP)
		{
			if (pom->prawy != NULL)
				pom = pom->prawy;
			else
			{
				pom->prawy = nowy;
				nowy->gora = pom;
				popraw_wagi(nowy, &(*baza));
				return;
			}
		}
		else
		{
			if (pom->lewy != NULL)
				pom = pom->lewy;
			else
			{
				pom->lewy = nowy;
				nowy->gora = pom;
				popraw_wagi(nowy, &(*baza));
				return;
			}
		}
	}
	(*baza) = nowy;
	return;


}

Wezel* znajdz(Wezel* pom, unsigned int adresIP)
{
	if (pom != NULL)
		while (adresIP != pom->lAdresIP)
		{
			if (pom->lAdresIP < adresIP)
			{
				if (pom->prawy != NULL)
					pom = pom->prawy;
				else
					return NULL;
			}
			else
			{
				if (pom->lewy != NULL)
					pom = pom->lewy;
				else
					return NULL;
			}
		}
	return pom;

}

void popraw_wagi_usun(Wezel* aktualny, Wezel** baza)
{
	int x = 0;
	while (aktualny->gora != NULL)
	{

		if (x == 1)
		{
			if (aktualny->gora->lewy != NULL)
			{
				if (aktualny->gora->lewy->lAdresIP == aktualny->lAdresIP)
				{
					aktualny->gora->waga -= 1;
				}
				else
				{
					aktualny->gora->waga += 1;
				}
			}
			else
			{
				aktualny->gora->waga += 1;
			}


			aktualny = aktualny->gora;
		}
		x = 1;


		if (aktualny->waga == 2)
		{
			if (aktualny->lewy->waga == 1 || aktualny->lewy->waga == 0)
			{
				RR(aktualny, &(*baza));
			}
			else
			{
				LR(aktualny, &(*baza));

			}
			aktualny = aktualny->gora;
		}
		else if (aktualny->waga == -2)
		{
			if (aktualny->prawy->waga == -1 || aktualny->prawy->waga == 0)
			{
				LL(aktualny, &(*baza));
			}
			else
			{
				RL(aktualny, &(*baza));
			}
			aktualny = aktualny->gora;
		}

		if (aktualny->waga == 1 || aktualny->waga == -1)
			return;
	}
}

void usunIP(Wezel** baza, unsigned int adresIP)
{
	int y = 0;
	Wezel* usun = znajdz(*baza, adresIP);
	if (usun == NULL)
	{
		//cout<<"Brak danego adresu w bazie danych"<<endl;
		return;
	}

	for (int i = 1; i <= 1; i++)
	{
		if (usun->prawy == NULL && usun->lewy == NULL)
		{
			if (usun->gora != NULL)
			{
				if (usun->gora->lewy == usun)
				{
					usun->gora->waga -= 1;
					usun->gora->lewy = NULL;
				}

				else
				{
					usun->gora->waga += 1;
					usun->gora->prawy = NULL;
				}
				popraw_wagi_usun(usun->gora, &(*baza));
			}
			else
				*baza = NULL;

		}
		else if (usun->prawy == NULL)
		{
			usun->lewy->gora = usun->gora;

			if (usun->gora != NULL)
			{

				if (usun->gora->lewy == usun)
				{
					usun->gora->waga -= 1;
					usun->gora->lewy = usun->lewy;
				}
				else
				{
					usun->gora->waga += 1;
					usun->gora->prawy = usun->lewy;
				}

				popraw_wagi_usun(usun->gora, &(*baza));
			}
			else
			{
				*baza = usun->lewy;
			}

		}
		else if (usun->lewy == NULL)
		{
			usun->prawy->gora = usun->gora;

			if (usun->gora != NULL)
			{

				if (usun->gora->prawy == usun)
				{
					usun->gora->waga += 1;
					usun->gora->prawy = usun->prawy;
				}
				else
				{
					usun->gora->waga -= 1;
					usun->gora->lewy = usun->prawy;
				}

				popraw_wagi_usun(usun->gora, &(*baza));
			}
			else
			{
				*baza = usun->prawy;
			}

		}
		else
		{
			i--;
			Wezel* pom = usun;
			usun = usun->prawy;
			while (usun->lewy != NULL)
				usun = usun->lewy;

			pom->lAdresIP = usun->lAdresIP;
		}
	}
	delete usun;
}

void usun_tree(Wezel* aktualny)
{
	if (aktualny != NULL)
	{
		if (aktualny->prawy != NULL)
			usun_tree(aktualny->prawy);
		if (aktualny->lewy != NULL)
			usun_tree(aktualny->lewy);
		delete aktualny;
	}

}

////////////////////////////////////////////////////////////////////////////////////// GRAFY //////////////////////////////////////////////////////////////////////////////////////
int odleglosc[16778000];
bool odwiedzone[16778000];
vector <pair<unsigned int, unsigned int> > graf[16778000];
struct SortowanieMalejaceSciezek
{
	bool operator ()(const pair<unsigned int, unsigned int>& p1, const pair<unsigned int, unsigned int>& p2)
	{
		if (p1.second > p2.second)return true;
		return false;
	}
};
priority_queue < pair<unsigned int, unsigned int>, vector < pair< unsigned int, unsigned int> >, SortowanieMalejaceSciezek > kolejkaPriorytetowa;

bool ist_podsiec(Wezel* pom, int podsiec)
{
	int x;
	while (pom != NULL)
	{
		x = pom->lAdresIP / 256;
		if (x == podsiec)
			return true;
		else if (x < podsiec)
			pom = pom->prawy;
		else
			pom = pom->lewy;
	}
	return false;
}


void dijkstra(unsigned int poczatek, unsigned int koniec)
{
	pair<unsigned int, unsigned int> para = make_pair(poczatek, 0);
	unsigned int wierzcholek, aktualny, waga, aktualny_waga, suma;

	for (int i = 0; i <= 16777215; i++)
	{
		if (!graf[i].empty())
		{
			odleglosc[i] = UINT_MAX;
			odwiedzone[i] = false;
		}
		else
			odwiedzone[i] = true;
	}
	kolejkaPriorytetowa.push(para);
	odleglosc[poczatek] = 0;


	while (!kolejkaPriorytetowa.empty())
	{
		while (odwiedzone[kolejkaPriorytetowa.top().first] == true)
			kolejkaPriorytetowa.pop();
		if (kolejkaPriorytetowa.empty())
			break;

		wierzcholek = kolejkaPriorytetowa.top().first;
		waga = kolejkaPriorytetowa.top().second;
		if (wierzcholek == koniec)
		{
			cout << waga << endl;
			return;
		}

		odwiedzone[wierzcholek] = true;
		kolejkaPriorytetowa.pop();

		for (int i = 0; i < graf[wierzcholek].size(); i++)
		{
			aktualny = graf[wierzcholek][i].first;  //wierzcho³ek sasiada
			if (odwiedzone[aktualny] == false)
			{
				aktualny_waga = graf[wierzcholek][i].second;
				suma = waga + aktualny_waga;
				if (suma < odleglosc[aktualny])
				{
					pair<unsigned int, unsigned int> para = make_pair(aktualny, suma);
					kolejkaPriorytetowa.push(para);
					odleglosc[aktualny] = suma;
				}
			}
		}
	}
	cout << "NIE" << endl;
}

int main()
{

	ifstream plik;
	plik.open("C:\\Users\\micha\\Desktop\\studia\\semestr3\\ASD\\Projekt\\pom.txt");

	if (!plik.good())
		return false;

	Wezel* baza = NULL;
	int n ,k;
	unsigned int adres, adres1, adres2, dlugosc;
	string a, b, c;

	plik >> n;
	for (int i = 0; i < n; i++)
	{
		plik >> a;
		if (a == "DK")
		{
			plik >> a;
			Wezel* nowy = new Wezel;
			nowy->lAdresIP = zamiana(a);
			dodaj(&baza, nowy);

		}
		else if (a == "UK")
		{
			plik >> a;
			usunIP(&baza, zamiana(a));
		}
		else if (a == "WK")
		{
			plik >> a;
			Wezel* wez = znajdz(baza, zamiana(a));
			if (wez == NULL)
				cout << "NIE" << endl;
			else
				cout << "TAK" << endl;


		}
		else if (a == "LK")
		{
			plik >> a;
			int wynik = podSiec(baza, zamiana(a));
			cout << wynik << endl;

		}
		else if (a == "WY")
		{
			rysuj(baza);
		}
		else if (a == "DP")
		{

			plik >> a >> b  >> c;

			dlugosc = 0;
			for (int i = 0; i < c.length()-1; i++)
			{
				dlugosc *= 10;
				dlugosc += (c[i] - '0');
			}
			if (c[c.length() - 1] == 'G')
				dlugosc = 100 / dlugosc;
			else
				dlugosc = 100000 / dlugosc;

			adres1 = zamiana(a);
			adres2 = zamiana(b);
			if(ist_podsiec(baza, adres1) == true &&  ist_podsiec(baza, adres2) == true)
			{
				pair<unsigned int, unsigned int> polaczenie = make_pair(adres2, dlugosc);
				pair<unsigned int, unsigned int> polaczenie2 = make_pair(adres1, dlugosc);
				graf[adres1].push_back(polaczenie);
				graf[adres2].push_back(polaczenie2);
			}
		}
		else if (a == "UP")
		{
			plik >> a >> b;
			adres1 = zamiana(a);
			adres2 = zamiana(b);
			for (int i = 0; i < graf[adres1].size(); i++)
			{
				if (graf[adres1][i].first == adres2)
				{
					graf[adres1].erase(graf[adres1].begin() + i);
					break;
				}
			}
			for (int i = 0; i < graf[adres2].size(); i++)
			{
				if (graf[adres2][i].first == adres1)
				{
					graf[adres2].erase(graf[adres2].begin() + i);
					break;
				}
			}
		}
		else if (a == "NP")
		{
			plik >> a >> b;

			adres1 = zamiana(a);
			adres2 = zamiana(b);
			Wezel* pom1 = znajdz(baza, adres1);
			Wezel* pom2 = znajdz(baza, adres2);
			if (pom1 !=NULL && pom2 != NULL)
			{
				dijkstra(adres1/256, adres2/256);
			}
			else
			{
				cout << "NIE" << endl;
			}
			while (!kolejkaPriorytetowa.empty())
				kolejkaPriorytetowa.pop();
		}

	}
	usun_tree(baza);
	plik.close();
}
