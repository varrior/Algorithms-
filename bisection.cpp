#include <iostream>
#include<cmath>
#include<vector>
#include <cstdlib>

using namespace std;

const double EPS = 1e-9;

//Funkcja zwracaj¹ca tablicê funkcji testowych
vector<double> funcs(double x);

//Liczenie pierwiastka metod¹ bisekcji
int bisection();

int main() {
	bisection();

	return 0;
}

vector<double> funcs(double x=1) {

	vector<double> arr;

	arr.push_back(x * x - 5 * x + 3);
	arr.push_back(x * x * x * (x + sin(x * x - 1) - 1) - 1);
	arr.push_back(x * x * x + 3 * x * x + 15 * x + 9);
	arr.push_back(x * x * (tan(x * x) - 2) + 5);

	return arr;
}
int bisection() {
	//Funkcja musi byæ okreœlona w przedziale <a,b>, dla ka¿dego x f(x) musi mieæ okreœlon¹ wartoœæ 
	//Funkcja musi byæ ci¹g³a w przedziale <a,b>, dla ka¿dego x f(x) musi mieæ inn¹ wartoœæ
	//Funkcja f(x) na krañcach przedzia³u <a,b> przyjmuje wartoœci ró¿nych znaków

	double a, b, s;
	vector<double> fa; 
	vector<double> fb; 
	vector<double> fs;
	vector<double> n = funcs();

	cout << "Obliczanie miejsca zerowego funkcji metoda bisekcji" << endl << "Okreslenie przedzialu argumentow funkcji" << endl;

	for (int i = 0; i < n.size(); i++) {
		cout << endl << "Podaj poczatkowa wartosc dziedziny: ";
		cin >> a;
		cout << "Podaj koncowa wartosc dziedziny: ";
		cin >> b;

		fa = funcs(a);
		fb = funcs(b);

		if (fa[i] * fb[i] > 0) {
			cout << "Znaki krancowych argumentow funkcji sa takie same. Dziedzina nie spelnia zalozen." << endl;
		}
		else {
			while (abs(a - b) > EPS) {
				s = (a + b) / 2;
				fs = funcs(s);
				if (abs(fs[i]) < EPS) {
					break;
				}
				else if (fa[i] * fs[i] < 0) {
					b = s;
				}
				else {
					a = s;
				}
			}
			cout << "Pierwiastek funcji nr " << i + 1 << " wynosi: " << s << endl;
		}
	}

	return 0;
}