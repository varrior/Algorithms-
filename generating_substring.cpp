#include<iostream>
#include<cmath>
#include<time.h>
#include<cstdlib>

using namespace std;

/*							GENEROWANIE PODCI�G�W METOD� TESTU LOSOWEGO

	Program zwraca m-elementow� posortowan� list� z�o�on� z losowych liczb z przedzia�u od 1 do n; 
		- choose_numbers() - za pomoc� testu losowego z przedzia�u liczb od 1 do n funkcja zwraca m posortowanych liczb
*/
float* choose_numbers(float m, float n) {

	float p;				//Prawdopodobie�stwo wylosowania kolejnej liczby;
	float r;				//Liczba losowa z przedzia�u [0,1);
	float choose = m;
	float remain = n;
	float* T = new float[m];
	
	int j = 0; 

	srand((float)time(NULL));

	for (int i = 1; i <= n; i++) {
		p = choose / remain;
		r = ((float)rand() / RAND_MAX);

		if (r < p) {
			T[j] = i;
			j++;
			choose -= 1;
		}
		remain -= 1;
	}
	return T;
}

int main() {

	float m; //Liczba losowych element�w w posortowanej li�cie
	float n; //G�rna granica zakresu niepowtarzaj�cych si� liczb 1,,,,,n

	cout << "Podaj zakres liczb od 1 do n. Podaj liczbe n:  " << endl;
	cin >> n;
	cout << "Podaj liczbe elementow w generowanym podciagu: " << endl;
	cin >> m;

	float* T = choose_numbers(m, n);

	cout << "Wygenerowana posortowana lista m-elementowa: [";
	for (int i = 0; i < m; i++) {
		if (i < m - 1) {
			cout << T[i] << ", ";
		}
		else {
			cout << T[i] << "]" << endl;
		}
	}
	return 0;
}