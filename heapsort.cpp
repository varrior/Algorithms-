#include<iostream>
#include<cmath>
#include<time.h>
#include<iomanip>
using namespace std;

/*											SORTOWANIE PRZEZ KOPCOWANIE

Sortowanie metod¹ kopcowania. W programie g³ównym tworzona jest nieposortowana tablica z wykorzystaniem liczb pseudolosowych. Dodatkowo w pêtlach wywo³ywane s¹ dwie funkcje:
	- wstawNaKoniec - powiêksza pomocnicz¹ tablicê A i element T[i] i porz¹dkuje kopiec funckj¹ doDory();
	- usunMin - usuwa najmniejszy element z tablicy A i zapisuje go na miejscu T[i] i porz¹dkuje kopiec funckj¹ naDol().

Dodatkowo program wyœwietla tablicê nieposortowan¹, tablicê posortowan¹ oraz czas wykonania algorytmu
*/


void doGory(int *A, int na) {
	int s = na;					//Pocz¹tkowy indeks potomka
	int parent;					//Indeks rodzica
	int tmp;					//Zmienna pomocnicza
	while (true) {
		if (s == 0) {
			break;
		}
		parent = floor(s - 1) / 2;
		if (A[s] >= A[parent]) {
			break;
		}
		tmp = A[parent];
		A[parent] = A[s];
		A[s] = tmp;

		 s = parent;
	}
}
void wstawNaKoniec(int* A, int e, int s) {
	A[s] = e;
	doGory(A, s);
}
void naDol(int* A, int na) {
	int parent = 0;				//Pocz¹tkowy indeks rodzica
	int right;					//Indeks prawego potomka
	int left;					//Indeks lewego potomka
	int tmp;					//Zmienna pomocnicza
	while (true) {
		left = 2 * parent +1;
		if (left > na) {
			break;
		}		
		right = 2 * parent + 2;
		if (right <= na && A[right] < A[left]) {
			left = right;
		}
		if (A[parent] <= A[left]) {
			break;
		}
		tmp = A[parent];
		A[parent] = A[left];
		A[left] = tmp;

		parent = left;
	}
}
void usunMin(int* A, int& e, int s) {
	e = A[0];
	A[0] = A[s];
	naDol(A, s);
}
int main() {
	int n;
	int* T;
	int* A;
	float start, stop, sort_time;
	cout << "Sortowanie elementow w tablicy metoda kopcowania" << endl <<endl;
	cout << "Podaj liczbe elementow w tablicy: " << endl;
	cin >> n;
	cout << endl;
	T = new int[n];
	A = new int[n];

	srand((double)time(NULL));

	for (int i = 0; i < n; i++) {
		T[i] = rand() % 50;
	}

	int na = 0;
	cout << "Tablica nieposortowana: [";
	for (int i = 0; i < n; i++) {
		if (i < n - 1) {
			cout << T[i]<<", ";
		}
		else {
			cout << T[i]<<"]" << endl;
		}
	}
	start = clock();
	for (int i = 0; i < n; i++) {
		wstawNaKoniec(A, T[i], na++);
	}
	na = n-1;
	for (int i = 0; i < n; i++) {
		usunMin(A, T[i], na--);
	}
	stop = clock();

	cout << "Tablica posortowana: [";
	for (int i = 0; i < n; i++) {
		if (i < n - 1) {
			cout << T[i] << ", ";
		}
		else {
			cout << T[i] << "]" << endl;
		}
	}
	cout << endl << "Czas wykonania sortowania: " << setprecision(7) <<(stop - start) / CLOCKS_PER_SEC << endl;
	delete[] T;
	delete[] A;
	return 0;
}