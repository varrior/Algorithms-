#include<iostream>
#include<cmath>
#include<time.h>
#include<cstdlib>

using namespace std;

/*							GENEROWANIE PODCI¥GÓW METOD¥ TESTU LOSOWEGO

	Program zwraca m-elementow¹ posortowan¹ listê z³o¿on¹ z losowych liczb z przedzia³u od 1 do n; 
		- choose_numbers() - za pomoc¹ testu losowego z przedzia³u liczb od 1 do n funkcja zwraca m posortowanych liczb
*/
float* choose_numbers(float m, float n) {

	float p;				//Prawdopodobieñstwo wylosowania kolejnej liczby;
	float r;				//Liczba losowa z przedzia³u [0,1);
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

	float m; //Liczba losowych elementów w posortowanej liœcie
	float n; //Górna granica zakresu niepowtarzaj¹cych siê liczb 1,,,,,n

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