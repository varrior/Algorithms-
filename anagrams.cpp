#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include<time.h>
#include<iomanip>

using namespace std;

/*			WYSZUKIWANIE ANAGRAMÓW W S£OWNIKU JÊZYKA POLSKIEGO

Program g³ówny wywo³uje funckjê sort_dict(), która wykonuje nastêpuj¹ce operacje:
	- wczytuje s³ownik z pliku z kodowaniem znaków ANSI
	- w pêtli wczytuje ka¿d¹ liniê z pliku, sortuje znaki w wyrazie oraz dodaje do tablicy (wektora) string sk³¹daj¹cy siê z wyrazu posortowanego i pocz¹tkowego
	- za pomoc¹ algorytmu sortowania szybkiego ca³a tablica stringów jest sortowana
	- za pomoc¹ pêtli elementy w tablicy s¹ obinane, grupowane i zapisywane w pliku
Dodatkowo program oblicza czas wykonania ca³ego algorytmy
*/

void quicksort(int l, int r, vector<string> &T) {

	int i;			//Indeks pierwszego elementu tablicy
	int j;			//Indeks ostatniego elementu tablicy
	int k;			//Indeks œrodkowego elementu
	string p;		//Element w œroku tablicy
	string t;		//Dodatkowa zmienna do trzymania wartoœci

	i = l;
	j = r;
	k = ceil((l + r) / 2);
	p = T[k];

	//Podzia³ tablicy na dwie wzglêdem elementu rozdzielaj¹cego
	do {
		while (T[i] < p)
			i++;
		while (T[j] > p)
			j--;
		if (i <= j) {
			t = T[i];
			T[i] = T[j];
			T[j] = t;

			i++;
			j--;
		}
	} while (i <= j);
	//Sortowanie pocz¹tkowej i koñcowej czêœci tablicy
	if (l < j) quicksort(l, j, T);
	if (r > i) quicksort(i, r, T);
}

int sort_str(char s1, char s2) {
	return (s1<s2);
}

void sort_dict() {
	ifstream file("slownik/ANSI.txt");						//Plik wczytywany
	ofstream out_file("slownik/sortowany_slownik.txt");		//Plik wynikowy z anagramami
	string str;
	string old_str;
	vector<string> vec;
	int j = 0;

	while (getline(file, str)) {
		old_str = str;
		sort(str.begin(), str.end(), sort_str);
		vec.push_back(str + " " + old_str);
	}

	quicksort(0, vec.size() - 1, vec);
	
	for (int i = 0; i < vec.size()-1; i++) {
		if (vec[i].substr(0, vec[i].find(" ")) == vec[i + 1].substr(0, vec[i + 1].find(" "))) {
			out_file << vec[i].substr(vec[i].find(" ") + 1) << " ";
			j++;
		}
		else if (j > 0) { 
			out_file << vec[i].substr(vec[i].find(" ") + 1) << "\n";
			j = 0;
		}
	}
}

int main() {
	float start, stop, sort_time;

	start = clock();
	sort_dict();
	stop = clock();
	sort_time = (stop - start) / CLOCKS_PER_SEC;
	cout << setprecision(7) << sort_time << endl;

	return 0;
}