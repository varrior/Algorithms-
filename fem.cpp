#include <iostream>
#include<cmath>
#include<vector>

using namespace std;

/*					NUMERYCZNE OBLICZANIE POCHODNYCH

	Program oblicza wartoœæ pierwszej i drugiej pochodnej w punkcie x
		- Funkcja pomocnicza f() zwraca tablicê funkcji, których obliczane s¹ dwie pierwsze pochodne
	Podane funkcje musz¹ byæ ci¹g³e i okreslone w punkcie x;
	Poni¿sza metoda w pewnych przypadkach zwraca wynik dla funkcji nieci¹g³ej :)
*/

 vector<double> f(double x) {

	vector<double> arr;

	arr.push_back(x * x * x - 3 * x + 4);
	arr.push_back(5 * x * x - 3 * x + sin(x));
	arr.push_back(4 * x * x - 9 * x * x + 4 * x);
	arr.push_back(sin(x));

	return arr;
}

int finite_method(double x) {

	 const double H = 0.00001;

	 double n1; //Pierwsza pochodna funkcji
	 double n2; //Druga pochodna funkcji

	 for (int i = 0; i < f(x).size(); i++) {
		n1 = (f(x + H)[i] - f(x - H)[i]) / (2 * H);
		n2 = (f(x + H)[i] + f(x - H)[i] - 2 * f(x)[i]) / (H * H);

		cout << endl << "Wartosc pierwszej pochodnej dla funkcji nr " << i + 1 << " wynosi: " << n1<<endl;
		cout << "Wartosc drugiej pochodnej dla funkcji nr " << i + 1 << " wynosi: " << n2 << endl;
	 }

	 return 0;
}

int main() {

	double x; //Punkt, w którym badana jest pochodna

	cout << "Podaj wartosc punktu x: " << endl;
	cin >> x;

	finite_method(x);

	return 0; 
}