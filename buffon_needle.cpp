#include <iostream>
#include<time.h>
#include<cmath>

using namespace std;

/*	WYZNACZANIE LICZBY PI METOD¥ IG£Y BUFFONA

	W pêtli generowane s¹ dwie zmienne pseudolosowe reprezentuj¹ce odpowiednio odleg³oœæ od œrodka ig³y do linii (od 0 do 1) oraz k¹t miêdzy ig³¹ a lini¹ (od 0 do PI/2). Nastêpnie za pomoc¹ warunku (odleg³oœæ od œrodka ig³y do jej koñca jest wiêsza b¹dŸ równa odleg³oœci od œrodka ig³y do linii) inkrementowana jest zmienna reprezentuj¹ca liczbê przeciêæ ig³y z lini¹. Nstêpnie wszystkie potrzebne dane podstawiane s¹ do wzoru.
*/
int main() {

	double x;			//Odleg³oœæ œrodka ig³y od najbli¿szej linii (od 0 do d/2)
	double angle;		//K¹t ostry miêdzy ig³¹ a lini¹ (od 0 do PI/2)
	double n;			//Liczba losowañ
	double l;			//D³ugoœæ ig³y
	double d;			//Odleg³oœæ miêdzy liniami
	double t;			//Liczba spe³nionych warunków
	double y;			//Odleg³oœæ od œrodka do koñca ig³y

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