#include<iostream>
#include<cmath>
#include<cstdlib>
#include<iomanip>
#include<time.h>
#include<string>
using namespace std;

/*
																	SORTOWANIE SZYBKIE

	Program g³ówny wywo³uje piêæ ró¿nych implementacji algorytmu sortowania szybkiego oraz oblicza czas wykonania ka¿dego z nich wraz z liczb¹ wykonanych rekurencji. Dla ka¿dej funkcji program g³ówny tworzy oddzieln¹ tablicê z wybran¹ liczb¹ elementów losowych lub posortowanych.

		- quicksort() - podstawowy algorytm sortuj¹cy ze skrajnym(lewym) elementem podzia³owym;
		- quicksort_middle() - podstawowy algorytm sortuj¹cy ze œrodkowym elementem podzia³owym;
		- quicksort_middle_while() - algorytm sortuj¹cy ze œrokowym elementem podzia³owym z wykorzystaniem konstrukcji pêtli do-while;
		- quicksort_tail() - algorytm ograniczj¹cy liczbê wywo³añ rekurencyjnych tzw. tail call elimination, ze skrajnym elementem podzia³owym
		- quicksort_insertion() - po³¹czenie dwóch idei sortowania, sortowania szybkiego ze œrodkowym elementem podzia³owym i sortowania przez wstawianie dla ma³ych tablic.

		WNIOSKI: Dla tablic nieposortowanych efektywnoœæ czsowa algorytmów jest zbli¿ona do siebie, natomiast dla tablic ju¿ posortowanych, b¹dŸ czêœciowo posortowanych jedynie algorytmy ze œrodkowym elementem podzia³owym wykazuj¹ siê bardzo dobr¹ efetywnoœci¹ czasow¹, pozosta³e algorytmy dla takich danych s¹ bezu¿yteczne, poniewa¿ czas sortowania jest nieaceptowalnie d³ugi.
		
		- quicksort_insertion() - jest to algorytm najbardziej efektywny (dla du¿ych tablic >5000000, czas wykonania sortowania jest pond 2-krotnie szybszy) z przedstawionych poni¿ej, czas wykonywania algorytmu jest najkrótszy oraz zu¿ywa najmniejsz¹ iloœæ pamiêci ze wzglêdu na ponad 4-krotnie (dla tablic >5000000) mniej wywo³añ rekurencyjnych. Warto zwróciæ uwagê, ¿e efektywnoœæ tego rozwi¹znia polega na po³¹czeniu szybkiego sortowania z elementem œrokowym jako piwot oraz sortwania przez wstawianie, które dla ma³ych tablic jest efektywniejszym rozwi¹zaniem. Wybór elementu skrajnego jako piwot daje du¿o gorsze wyiki, zarówno w odniesieniu do czasu jak i liczby wywo³añ rekurencyjnych. 

		UWAGA: Dla tablic z mniejsz¹ iloœci¹ elementów (niesortowanych) ró¿nice miêdzy algorytmami bêd¹ siê zminiejszaæ i ka¿dy bêdzie równie efektywny, natomiast wraz ze wzrostem wielkoœci tablicy ró¿nica miêdzy hybrydowym algorytmem (quicksort_insertion) a reszt¹ bêdzie coraz wiêksza.
*/

void quicksort(int l, int r, double* T, int& counter) {

	int p;					//Element œrodkowy tzw. piwot
	int j;					//Zmienna inkrementowana
	int t;					//Dodatkowa zmienna do trzymania wartoœci

	counter++;

	p = T[l];
	j = l;
	//Podzia³ tablicy na dwie wzglêdem elementu rozdzielaj¹cego
	for (int i = l + 1; i <= r; i++) {
		if (T[i] < p) {
			j++;
			t = T[j];
			T[j] = T[i];
			T[i] = t;
		}
	}
	T[l] = T[j];
	T[j] = p;
	//Sortowanie pocz¹tkowej i koñcowej czêœci tablicy
	if (l < r) {
		quicksort(l, j - 1, T, counter);
		quicksort(j + 1, r, T, counter);
	}
}

void quicksort_middle(int l, int r, double* T, int& counter) {

	int j;				//Zmienna inkrementowana
	int i;				//Indeks œrodka tablicy
	int p;				//Element w œrodku tablicy
	int t;				//Dodatkowa zmienna do trzymania wartoœci

	counter++;

	j = l;
	i = ceil((l + r) / 2);
	p = T[i];

	T[i] = T[r];
	//Podzia³ tablicy na dwie wzglêdem elementu rozdzielaj¹cego
	for (i = l; i < r; i++) {
		if (T[i] < p) {
			t = T[j];
			T[j] = T[i];
			T[i] = t;
			j++;
		}
	}
	T[r] = T[j];
	T[j] = p;
	//Sortowanie pocz¹tkowej i koñcowej czêœci tablicy
	if (l < j - 1) quicksort_middle(l, j - 1, T, counter);
	if (j + 1 < r) quicksort_middle(j + 1, r, T, counter);
}

void quicksort_middle_while(int l, int r, double* T, int& counter) {

	int i;			//Indeks pierwszego elementu tablicy
	int j;			//Indeks ostatniego elementu tablicy
	int k;			//Indeks œrodkowego elementu
	int p;			//Element w œroku tablicy
	int t;			//Dodatkowa zmienna do trzymania wartoœci
	
	counter++;

	i = l;
	j = r;
	k = ceil((l + r) / 2);
	p = T[k];

	//Podzia³ tablicy na dwie wzglêdem elementu rozdzielaj¹cego
	do{
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
	if (l < j) quicksort_middle_while(l, j, T, counter);
	if (r > i) quicksort_middle_while(i, r, T, counter);
}

void quicksort_tail(int l, int r, double* T, int& counter) {

	int p;			//Element w œroku tablicy
	int j;			//Indeks pocz¹tka tablicy
	int t;			//Dodatkowa zmienna do trzymania wartoœci

	counter++;

	//Podzia³ tablicy na dwie wzglêdem elementu rozdzielaj¹cego
	while (l < r) {
		p = T[l];
		j = l;

		for (int i = l + 1; i <= r; i++) {
			if (T[i] < p) {
				j++;
				t = T[j];
				T[j] = T[i];
				T[i] = t;
			}
		}
		T[l] = T[j];
		T[j] = p;
		//Sortowanie pocz¹tkowej i koñcowej czêœci tablicy
		if ((j - l) < (r - j)) {
			quicksort_tail(l, j - 1, T, counter);
			l = j + 1;
		}
		else {
			quicksort_tail(j + 1, r, T, counter);
			r = j - 1;
		}
	}
}

void quicksort_insertion(int l, int r, double* T, int& counter) {
	int val;		//Element tablicy w czêœci sortowania przez wstawianie
	int j;		
	int low;		//Indeks pocz¹tka tablicy
	int high;		//Indeks ostatniego elementu tablicy
	int tmp;		//Zmienna pomocnicza
	int pivot;		//Element podzia³owy
	
	counter++;

	while (l < r)
	{
		if (r - l < 10)
		{
			for (int i = l + 1; i <= r; i++)
			{
				val = T[i];
				j = i;
				while (j > l && T[j - 1] > val)
				{
					T[j] = T[j - 1];
					j--;
				}
				T[j] = val;
			}
			break;
		}
		else
		{
			low = l;
			high = r;
			tmp;
			pivot = T[(l + r) / 2];

			while (low <= high) {
				while (T[low] < pivot) {
					low++;
				}
				while (T[high] > pivot) {
					high--; 
				}
				if (low <= high) {
					tmp = T[low];
					T[low] = T[high];
					T[high] = tmp;
					low++;
					high--;
				}
			};
			if (l < high) {
				quicksort_insertion(l, high,T,counter);
				l = high + 2;
			}
			if (low < r) {
				quicksort_insertion(low, r,T,counter);
				r = low;
			}
		}
	}
}

int main() {

	int x;					//Liczba elementów w tablicy
	string y;				//Wybór tablicy
	bool z;					//Inicjalizacja tablicy posortowanej lub losowej
	bool correct;			//Poprawnie wprowadzone dane
	int counter;			//Liczba wykonanych rekurencji

	do {
		cout << "Czy elementy tablicy maja byc losowe czy posortowane?: [L/P]" << endl;
		cin >> y;
		if (y == "L" || y == "l") {
			z = false;
			correct = true;
		}
		else if (y == "P" || y == "p") {
			z = true; 
			correct = true;
		}
		else {
			cout << "Dokonales blednego wyboru! Sproboj ponownie." << endl;
			correct = false;
		}
	} while (!correct);

	cout << "Podaj wielkosc tablicy: ";
	cin >> x;
	cout << endl << endl;
	//Zmienne potrzebne do obliczenia czasu sortowania
	float start, stop, sort_time;

	//Niezale¿ne tablice do posortowania dla poszczególnych metod
	double* T = new double[x];
	double* Ta = new double[x];
	double* Tab = new double[x];
	double* Tabl = new double[x];
	double* Tabli = new double[x];

	srand((double)time(NULL));

	//Przypisanie wartoœci do indeksów tablic
	for (int i = 0; i < x; i++) {
		T[i] = Ta[i] = Tab[i] = Tabl[i] = Tabli[i] = z?i:rand()%(x*3);
	}

	start = clock();
	counter = 0;
	quicksort(0, x - 1, T, counter);
	stop = clock();
	sort_time = (stop - start) / CLOCKS_PER_SEC;
	cout << "Czas sortowania dla algorytmu z lewym skrajnym elementem rozdzielajacym (quicksort): "<< endl << setprecision(5) << sort_time << endl << "Liczba wywolan rekurencyjnych: " << endl << counter << endl << endl;

	start = clock();
	counter = 0;
	quicksort_middle(0, x - 1, Ta, counter);
	stop = clock();
	sort_time = (stop - start) / CLOCKS_PER_SEC;
	cout << "Czas sortowania dla algorytmu ze srodkowym elementem rozdzielajacym (quicksort_middle): " << endl << setprecision(5) << sort_time << endl << "Liczba wywolan rekurencyjnych: " << endl << counter << endl << endl;

	start = clock();
	counter = 0;
	quicksort_middle_while(0, x - 1, Tab, counter);
	stop = clock();
	sort_time = (stop - start) / CLOCKS_PER_SEC;
	cout << "Czas sortowania dla algorytmu ze srodkowym elementem rozdzielajacym, z wykorzystaniem petli while (quicksort_middle_while): " << endl << setprecision(5) << sort_time << endl << "Liczba wywolan rekurencyjnych: " << endl << counter << endl << endl;

	start = clock();
	counter = 0;
	quicksort_tail(0, x - 1, Tabl, counter);
	stop = clock();
	sort_time = (stop - start) / CLOCKS_PER_SEC;
	cout << "Czas sortowania dla algorytmu z rozwijaniem funkcji w petli (quicksort_tail): " << endl << setprecision(5) << sort_time << endl << "Liczba wywolan rekurencyjnych: " << endl << counter << endl << endl;
	start = clock();
	counter = 0;
	quicksort_insertion(0, x - 1, Tabli, counter);
	stop = clock();
	sort_time = (stop - start) / CLOCKS_PER_SEC;
	cout << "Czas sortowania dla algorytmu hybrydowego (elementy sortowania przez wstawianie): " << endl << setprecision(5) << sort_time << endl << "Liczba wywolan rekurencyjnych: " << endl << counter << endl<<endl;
	
	delete[] T, Ta, Tab, Tabli;

	return 0;
}

