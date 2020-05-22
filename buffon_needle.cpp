#include <iostream>
#include<time.h>
#include<cmath>

using namespace std;

/*	WYZNACZANIE LICZBY PI METOD� IG�Y BUFFONA

	W p�tli generowane s� dwie zmienne pseudolosowe reprezentuj�ce odpowiednio odleg�o�� od �rodka ig�y do linii (od 0 do 1) oraz k�t mi�dzy ig�� a lini� (od 0 do PI/2). Nast�pnie za pomoc� warunku (odleg�o�� od �rodka ig�y do jej ko�ca jest wi�sza b�d� r�wna odleg�o�ci od �rodka ig�y do linii) inkrementowana jest zmienna reprezentuj�ca liczb� przeci�� ig�y z lini�. Nst�pnie wszystkie potrzebne dane podstawiane s� do wzoru.
*/
int main() {

	double x;			//Odleg�o�� �rodka ig�y od najbli�szej linii (od 0 do d/2)
	double angle;		//K�t ostry mi�dzy ig�� a lini� (od 0 do PI/2)
	double n;			//Liczba losowa�
	double l;			//D�ugo�� ig�y
	double d;			//Odleg�o�� mi�dzy liniami
	double t;			//Liczba spe�nionych warunk�w
	double y;			//Odleg�o�� od �rodka do ko�ca ig�y

	double pi;

	cout << "Wyznaczanie liczby PI metoda igly Buffona" << endl << endl;
	cout << "Podaj liczbe losowan: " << endl;
	cin >> n;

	srand(time(NULL));
	
	t = 0;
	l = 1.5;			//l <= d
	d = 2;				//Bo x jest zakresu <0,1>

	for (int i = 0; i < n; i++) {
		x = (double)rand() / (RAND_MAX);
		angle = ((double)rand() / (RAND_MAX)) * (3.14159265359/2);

		y = (sin(angle) * l) / 2;
		if (y >= x) t++;

	}
	pi = (2 * n * l) / (t * d);

	cout << "Aproksymowana liczba PI wynosi: " << pi << endl;

	return 0;
}