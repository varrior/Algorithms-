#include<iostream>
#include<time.h>
#include<cstdlib>
#include<iomanip>

using namespace std;

/*				SZUKANIE NAJWI�KSZEJ SUMY W WEKTORZE METOD� LINIOW�

	Poni�szy program s�u�y do obliczenia maksymalnej sumy kolejnych liczb w podprzedziale wektora.
	Program g��wny generuje tablic� z wybran� liczb� element�w w przedziale liczbowym od -1000 do 1000.
	Program g��wny wywo�uje trzy funkcje zwracaj�ce ten sam wynik, jednak z r�n� z�o�ono�ci� obliczeniow�.

		- linear_sum - wykonuje algorytm w czasie liniowym O(n);
		- linearithmic_sum - wykonuje algorytm w czasie n*logn, z�o��no�� obliczeniowa O(n*logn)
		- quadratic_sum - wykonuje algorytm w kwadratowej z�o�ono�ci obliczeniowej O(n^2);

	Funkcje zwracaj� maksymaln� sum� podci�gu w tablicy oraz numery indeks�w (z wyj�tkiem algorytmu drugiego) element�w pocz�tkowego i ko�cowego podci�gu. 
	Funkcja pomocnicza max() zwraca wi�ksz� z dw�ch podanych warto�ci parametr�w.
*/


int max(int a1, int a2) {
	if (a1 >= a2) return a1;
	return a2;
}

void linear_sum(int *T, int n) {
	int maxsofar = 0;				//Najwi�ksza szukana suma
	int maxhere = 0;				//Warto�� i-tego kroku
	int j = 0;						//Indeks pocz�tka przedzai�u
	int k = 0;						//Indeks ko�ca przedzia�u
	int maxvalue = 0;				//Najwi�ksza suma w poprzednim kroku
	int lastnewindex = 0;			//Warto�� i -1 kroku

	for (int i = 0; i < n; i++) {
		maxhere = max(maxhere + T[i], 0);
		maxsofar = max(maxsofar, maxhere);
		
		if (maxhere == 0) {
			lastnewindex = i + 1;
		}
		if (maxsofar > maxvalue) { 
			j = lastnewindex;
			k = i; 
		}
		maxvalue = maxsofar;
	}
	cout << endl << "Najwieksza suma w podprzedziale: " << maxsofar << endl;
	cout << "Indeks poczatku podprzedzialu: " << j << endl;
	cout << "Indeks konca podprzedzialu: " << k << endl;	
}
int linearithmic_sum(int l, int r, int *T) {

	int m;
	int lmax;
	int rmax;
	int sum;
	int total_sum;

	if (l > r) {
		return 0; 
	}
	if (l == r) {
		return T[l];
	}

	m = ceil((l + r) / 2);
	lmax = sum = 0;

	for (int i = m; i >= l; i--) {
		sum += T[i];
		lmax = max(lmax, sum);
	}
	rmax = sum = 0;

	for (int i = m + 1; i <= r; i++) {
		sum += T[i];
		rmax = max(rmax, sum);
	}

	return max(max(lmax + rmax, linearithmic_sum(l, m, T)), linearithmic_sum(m + 1, r, T));
}

void quadratic_sum(int *T, int n) {
	int k = 0;
	int l = 0;
	int maxsofar = 0; 
	int maxvalue = 0;
	int sum;

	for (int i = 0; i < n; i++) {
		sum = 0;
		for (int j = i; j < n; j++) {
			sum += T[j];
			maxsofar = max(maxsofar, sum);
			if (maxsofar > maxvalue) {
				l = j;
				k = i;
			}
			maxvalue = maxsofar;
		}
	}
	cout << endl << "Najwieksza suma w podprzedziale dla algorytmu kwadratrowego: " << maxsofar << endl;
	cout << "Indeks poczatku podprzedzialu: " << k << endl;
	cout << "Indeks konca podprzedzialu: " << l << endl;
}
int main() {
	
	int* T;								//Losowwo generowana tablica warto�ci z przedzia�u -1000 do 1000
	int n;								//Liczna element�w w tablicy
	float start, stop, sum_time;		//Zmienne s�u�ace do wyznaczenia czasu pracy algorytmu

	cout << "Podaj liczbe elementow w tablicy: " << endl;
	cin >> n;

	T = new int[n];

	srand(time(NULL));

	//Przypisanie indeksom tablicy liczb pseudolosowych z zakresu -1000 do 1000
	for (int i = 0; i < n; i++) {
		T[i] = rand() % 2001 - 1000;
	}
	//Je�eli tablica zawiera nie wi�cej ni� 100 element�w, wypisz tak� tablic� w konsoli
	if (n <= 100){
		cout << "Wygenerowano nastepujacy ciag liczb: [";
		for (int i = 0; i < n; i++) {
			if (i < n - 1) {
				cout << T[i] << ", ";
			}
			else {
				cout << T[i] << "]" << endl;
			}
		}
	}

	start = clock();
	linear_sum(T,n);
	stop = clock();
	sum_time = (stop - start) / CLOCKS_PER_SEC;
	cout << "Czas pracy algorytmu liniowego: " << setprecision(10) << sum_time << endl<<endl;

	start = clock();
	int total_sum = linearithmic_sum(0, n - 1, T);
	cout << endl << "Najwieksza suma w podprzedziale dla algotytmu liniowo-logarytmicznego: " << total_sum << endl;
	stop = clock();
	sum_time = (stop - start) / CLOCKS_PER_SEC;
	cout << "Czas pracy algorytmu liniowo-logarytmicznego: " << setprecision(10) << sum_time << endl;

	start = clock();
	quadratic_sum(T, n);
	stop = clock();
	sum_time = (stop - start) / CLOCKS_PER_SEC;
	cout << "Czas pracy algorytmu kwadratowego: " << setprecision(10) << sum_time << endl << endl;

	delete[] T;

	return 0;
}