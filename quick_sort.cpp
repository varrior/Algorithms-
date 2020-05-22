#include<iostream>
#include<cmath>
#include<cstdlib>
#include<iomanip>
#include<time.h>
#include<string>
using namespace std;

/*
																	SORTOWANIE SZYBKIE

	Program g��wny wywo�uje pi�� r�nych implementacji algorytmu sortowania szybkiego oraz oblicza czas wykonania ka�dego z nich wraz z liczb� wykonanych rekurencji. Dla ka�dej funkcji program g��wny tworzy oddzieln� tablic� z wybran� liczb� element�w losowych lub posortowanych.

		- quicksort() - podstawowy algorytm sortuj�cy ze skrajnym(lewym) elementem podzia�owym;
		- quicksort_middle() - podstawowy algorytm sortuj�cy ze �rodkowym elementem podzia�owym;
		- quicksort_middle_while() - algorytm sortuj�cy ze �rokowym elementem podzia�owym z wykorzystaniem konstrukcji p�tli do-while;
		- quicksort_tail() - algorytm ograniczj�cy liczb� wywo�a� rekurencyjnych tzw. tail call elimination, ze skrajnym elementem podzia�owym
		- quicksort_insertion() - po��czenie dw�ch idei sortowania, sortowania szybkiego ze �rodkowym elementem podzia�owym i sortowania przez wstawianie dla ma�ych tablic.

		WNIOSKI: Dla tablic nieposortowanych efektywno�� czsowa algorytm�w jest zbli�ona do siebie, natomiast dla tablic ju� posortowanych, b�d� cz�ciowo posortowanych jedynie algorytmy ze �rodkowym elementem podzia�owym wykazuj� si� bardzo dobr� efetywno�ci� czasow�, pozosta�e algorytmy dla takich danych s� bezu�yteczne, poniewa� czas sortowania jest nieaceptowalnie d�ugi.
		
		- quicksort_insertion() - jest to algorytm najbardziej efektywny (dla du�ych tablic >5000000, czas wykonania sortowania jest pond 2-krotnie szybszy) z przedstawionych poni�ej, czas wykonywania algorytmu jest najkr�tszy oraz zu�ywa najmniejsz� ilo�� pami�ci ze wzgl�du na ponad 4-krotnie (dla tablic >5000000) mniej wywo�a� rekurencyjnych. Warto zwr�ci� uwag�, �e efektywno�� tego rozwi�znia polega na po��czeniu szybkiego sortowania z elementem �rokowym jako piwot oraz sortwania przez wstawianie, kt�re dla ma�ych tablic jest efektywniejszym rozwi�zaniem. Wyb�r elementu skrajnego jako piwot daje du�o gorsze wyiki, zar�wno w odniesieniu do czasu jak i liczby wywo�a� rekurencyjnych. 

		UWAGA: Dla tablic z mniejsz� ilo�ci� element�w (niesortowanych) r�nice mi�dzy algorytmami b�d� si� zminiejsza� i ka�dy b�dzie r�wnie efektywny, natomiast wraz ze wzrostem wielko�ci tablicy r�nica mi�dzy hybrydowym algorytmem (quicksort_insertion) a reszt� b�dzie coraz wi�ksza.
*/

void quicksort(int l, int r, double* T, int& counter) {

	int p;					//Element �rodkowy tzw. piwot
	int j;					//Zmienna inkrementowana
	int t;					//Dodatkowa zmienna do trzymania warto�ci

	counter++;

	p = T[l];
	j = l;
	//Podzia� tablicy na dwie wzgl�dem elementu rozdzielaj�cego
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
	//Sortowanie pocz�tkowej i ko�cowej cz�ci tablicy
	if (l < r) {
		quicksort(l, j - 1, T, counter);
		quicksort(j + 1, r, T, counter);
	}
}

void quicksort_middle(int l, int r, double* T, int& counter) {

	int j;				//Zmienna inkrementowana
	int i;				//Indeks �rodka tablicy
	int p;				//Element w �rodku tablicy
	int t;				//Dodatkowa zmienna do trzymania warto�ci

	counter++;

	j = l;
	i = ceil((l + r) / 2);
	p = T[i];

	T[i] = T[r];
	//Podzia� tablicy na dwie wzgl�dem elementu rozdzielaj�cego
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
	//Sortowanie pocz�tkowej i ko�cowej cz�ci tablicy
	if (l < j - 1) quicksort_middle(l, j - 1, T, counter);
	if (j + 1 < r) quicksort_middle(j + 1, r, T, counter);
}

void quicksort_middle_while(int l, int r, double* T, int& counter) {

	int i;			//Indeks pierwszego elementu tablicy
	int j;			//Indeks ostatniego elementu tablicy
	int k;			//Indeks �rodkowego elementu
	int p;			//Element w �roku tablicy
	int t;			//Dodatkowa zmienna do trzymania warto�ci
	
	counter++;

	i = l;
	j = r;
	k = ceil((l + r) / 2);
	p = T[k];

	//Podzia� tablicy na dwie wzgl�dem elementu rozdzielaj�cego
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
	//Sortowanie pocz�tkowej i ko�cowej cz�ci tablicy
	if (l < j) quicksort_middle_while(l, j, T, counter);
	if (r > i) quicksort_middle_while(i, r, T, counter);
}

void quicksort_tail(int l, int r, double* T, int& counter) {

	int p;			//Element w �roku tablicy
	int j;			//Indeks pocz�tka tablicy
	int t;			//Dodatkowa zmienna do trzymania warto�ci

	counter++;

	//Podzia� tablicy na dwie wzgl�dem elementu rozdzielaj�cego
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
		//Sortowanie pocz�tkowej i ko�cowej cz�ci tablicy
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
	int val;		//Element tablicy w cz�ci sortowania przez wstawianie
	int j;		
	int low;		//Indeks pocz�tka tablicy
	int high;		//Indeks ostatniego elementu tablicy
	int tmp;		//Zmienna pomocnicza
	int pivot;		//Element podzia�owy
	
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

	int x;					//Liczba element�w w tablicy
	string y;				//Wyb�r tablicy
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

	//Niezale�ne tablice do posortowania dla poszczeg�lnych metod
	double* T = new double[x];
	double* Ta = new double[x];
	double* Tab = new double[x];
	double* Tabl = new double[x];
	double* Tabli = new double[x];

	srand((double)time(NULL));

	//Przypisanie warto�ci do indeks�w tablic
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

