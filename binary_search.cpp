#include<iostream>
#include<cstdlib>
#include<cmath>
#include<time.h>
#include<iomanip>
using namespace std;

int main(){ 

	int x;
	cout << "Podaj liczbe elementow w tablicy: " << endl;
	cin >> x;

	double *T = new double[x];
	float k; //Wybrany element do wyszukania indeksu w tablicy

	int tp = 0; //Pocz�tek rozpatrywanego przedzia�u (pierwzy element tablicy)
	int tsr; //�rodek rozpatrywanego przedzia�u
	int tk = x - 1; //Koniec rozpatrywanego przedzia�u (ostatni element tablicy)
	int y = -1; //Indeks szukanego elementu (domy�lnie brak znalezionego elementu)

	int loop = 0; //Liczba wykonanych p�tli

	//Generowanie losowej niemalej�cej tablicy
	srand((unsigned)time(NULL));

	T[0] = rand()%10;
	for (int j = 1; j < x; j++) {
		T[j] = T[j-1] + rand() % 10;
	}
	cout << "Twoja wygenerowana tablica to: [";
	for (int i = 0; i < x; i++) {
		if (i < (x - 1)) cout << setprecision(15)<< T[i] << ", ";
		else cout << setprecision(15) << T[i];
	}
	cout << "]" << endl;
	cout << endl << "Wybierz element tablicy: " << endl;
	cin >> k;

	//while(true)
	while (tp<=tk) {
		loop++;
		tsr = ceil((tp + tk) / 2);
		/*if(tp>tk){
			y=-1;
			break;
		}*/
		if (T[tsr] == k) {
			y = tsr;
			break;
		}
		else if (T[tsr] > k) {
			tk = tsr - 1; 
		}
		else {
			tp = tsr + 1; 
		}
	}
	//cout << "Wybrana wartosc " << k << " znajduje sie w tablicy pod indeksem nr " << y << endl; ---> Gdy nie znajdzie zwr�ci -1
	if (y >= 0) {
		cout << "Wybrana wartosc " << k << " znajduje sie w tablicy pod indeksem nr " << y << endl;
	}
	else {
		cout << "Element NIE znajduje sie w rozpatrywanej tablicy" << endl;
	}

	cout << endl << "Liczba wykonanych iteracji w petli: " << loop << endl;

	return 0;
}