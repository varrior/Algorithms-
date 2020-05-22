#include <iostream>
#include<cstdlib>
#include<time.h>
#include<vector>
using namespace std;

vector<double> func(double x=1) {
	vector <double> arr;

	arr.push_back(x*x+2*x);

	return arr;
}

int main() {

	const int LPL = 50000;

	double a; //Pocz¹tek przedzia³u ca³kowania
	double b; //Koniec przedzia³u ca³kowania
	double dx; //D³ugoœæ przedzia³u ca³kowania;
	double s; //Wartoœæ ca³ki ozaczonej
	double r; //Wartoœæ pseudolosowa;

	vector<double> n = func(); //Zmienna pomocnicza s³u¿aca do okreslenia wielkoœci zwracanej tablicy

	cout << "Calkowanie numeryczne metoda Monte-Carlo" << endl;
	cout << "Okreslenie przedzialu calkowania:" << endl;

	for (int i = 0; i < n.size(); i++) {
		cout << endl << "Podaj wartosc poczatku przedzialu calkowania: " << endl;
		cin >> a;
		cout << "Podaj wartosc konca przedzialu calkowania: " << endl;
		cin >> b;

		srand(time(NULL));
		s = 0;
		dx = b - a;

		for (int j = 1; j <= LPL; j++) {
			r = a + ((double)rand() / (double)(RAND_MAX + 1) * dx);
			s += func(r)[i];
		}
		s = dx * s / LPL;

		cout << "Wartosc calki wysnosi: " << s << endl;

	}

	return 0;
}

