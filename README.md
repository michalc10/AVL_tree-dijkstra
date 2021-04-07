# AVL_tree + dijkstra 

!!!! napisany w C++ !!!!


Program służy do tworzenia drzew avl, oraz do obliczania najkrótszych ścieżek za pomocą algorytmu Dijksta.
Został on stworzony do gromadzenia adresów IPv4, oraz obliczania najlepszej ścieżki, do przesłania danych.

W pierwszej lini jest liczba całkowita mówiąca ile będzie zdarzeń do wykonania
W następnych zdarzenia.

W pliku projekt.cpp w int main należy wpisać plik tekstowy wcześnie przygotowany
np:
plik.open("plik.txt");

Zdarzenia:
-DK x - dodawanie adresu IP do drzewa AVL
-UK x - usówanie adresu IP z drzewa AVL
-WK x - odnajdowanie adresu IP w drzewie AVL
-LK y - zwraca liczbę adresów IP w danej podsieci
-WY   - zrwaca drzewo AVL w formie graficznej
-DP x1 x2 l - dodanie połączenia między adresami IP
-UP x1 x2 - usunięcia połaćzenia między adresami IP
-NP x1 x2 -wypisanie najlepszego połączenia podsieci między adresami IP

gdzie x, x1, x2 to adres IP np. 208.80.152.2 (typ: string)
      y         to podsieć  np. 208.80.152   (typ: string)
      l         to szerokość pasma mieżone w M i G np. 10G / 100M (typ: string)
