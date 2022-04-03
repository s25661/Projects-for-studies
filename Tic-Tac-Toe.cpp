#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
												//Void nam nic nie zwraca 
void plansza(char tablica[])                    //Funkcja ryszuję plansze do gry w kółko i krzyżyk 
{												// Plansza przechowywana jest w tablicy o inteksach od 1 do 9 
	for (int i = 1; i <= 9; i++)
	{
		cout << " " << tablica[i] << " ";		//w pustych miejscach wpisujemy zawartość tablicy czyli biorąc pod uwagę że to jest typ char x lub y 
		if (i % 3) {
			cout << "|";						// Po elementach 1,2,4,5,7,8 drukują się słupki 
		}
		else if (i != 9) {
			cout << "\n---+---+---\n";			// Po elementach 3 i 6 poprzeczka 
		}
		else {
			cout << endl;						// Po 9 elemencie koniec wiersza 
		}
	}
}

void ruch(char tablica[], char& gracz, string& player1, string& player2)   //Funkcja umozliwiajaca ruch gracza 
{																			// Po ruchu nastepuje zmiana gracza 
	int pozycja;								

	plansza(tablica);
	if (gracz == 'O') {

		cout << endl;
		cout << "Twoja kolej " << player1 << " wstaw" << " \"O\" " << "na pole o numerze: ";
		cin >> pozycja;
		cout << endl;
		
	}
	else {

		cout << endl;
		cout << "Twoja kolej " << player2 << " wstaw" << " \"X\" " << "na pole o numrzerze: ";
		cin >> pozycja;
		cout << endl;
		
	}
	if ((pozycja >= 1) && (pozycja <= 9) && (tablica[pozycja] == ' ')) {
		
		tablica[pozycja] = gracz;								// do tablicy wrzucamy liczbe podana przez uzytkownika podpisujac ja pod indeks ktory wybral
		gracz = (gracz == 'O') ? 'X' : 'O';						// gracz kolko zaczyna co jest napisane w wierszu nr 131 za pomoca jezeli gracz zaladowal
	}															// kolko to nastepuje nastepny warunek i gracz laduje x a potem zachodzi zmiana 
}

bool wygrana(char tablica[], char gracz, string& player1, string& player2) //Funkcja ma typ bool i wtedy kiedy zwrata true to ktorys z zawodnikow wygrywa 
{
	bool sprawdzenie;
	int i;

	sprawdzenie = false;					//Zmienna przyjmuje wartosc true kiedy jeden z zawodnikow ma trzy figury z rzedu w poziomie pionie lub na przekatnych 
	for (i = 1; i <= 7; i += 3)
		sprawdzenie |= ((tablica[i] == gracz) && (tablica[i + 1] == gracz) && (tablica[i + 2] == gracz)); //sprawdzamy wiersze 
	for (i = 1; i <= 3; i++)
		sprawdzenie |= ((tablica[i] == gracz) && (tablica[i + 3] == gracz) && (tablica[i + 6] == gracz)); // sprawdzamy kolumny 
	sprawdzenie |= ((tablica[1] == gracz) && (tablica[5] == gracz) && (tablica[9] == gracz)); // przekątna 1-5-9
	sprawdzenie |= ((tablica[3] == gracz) && (tablica[5] == gracz) && (tablica[7] == gracz)); // przekatna 3-5-7

	if (sprawdzenie)
	{
		plansza(tablica);
		if (gracz == 'O') {

			cout << "\nWygrywa " << player1 << endl << "GRATULACJE!!!\n" << endl;
		}
		else {

			cout << "\nWygrywa " << player2 << endl << "GRATULACJE!!!\n" << endl;
		}
		return true;
	}
	return false;
}

bool remis(char tablica[])         //Funkcja zwraca true jeżeli na planszy nie ma żadnego wolnego pola 
{
	for (int i = 1; i <= 9; i++) {

		if (tablica[i] == ' ') {        // warunek działa dopoki sa puste miejsca 

			return false;
		}
	}
	plansza(tablica);
	cout << "\nREMIS\n" << endl;
	return true;
}

int main()
{
	char pozycja[10], gracz;
	string player1, player2, instrukcja, wybór;

	cout << "Witam w grze w kolko i krzyzyk dla dwoch graczy.\n" << endl;
	cout << "Checie zobaczyc instrukcje do gry?(Tak/Nie): ";
	cin >> instrukcja;

	if (((instrukcja == "TAK") || (instrukcja == "Tak") || (instrukcja == "tak"))) {

		cout << "\nPlansza podzielona jest na 9 pol.\nKazdemu polu odpowiada cyfra od 1 do 9." << endl;
		cout << "[1]|[2]|[3]\n---+---+---\n[4]|[5]|[6]\n---+---+---\n[7]|[8]|[9]" << endl;
		cout << "Wybierz liczbe z zakresu i ciesz sie gra." << endl;
		cout << "Gracz, ktory wybierze \"O\" zaczyna.\n" << endl;
	}
	else {
		cout << endl;
	}

	cout << "Podaj nick dla gracza \"O\": ";
	cin >> player1;
	cout << "Podaj nick dla gracza \"X\": ";
	cin >> player2;
	cout << endl;

	do
	{
		cout << "===================" << endl;
		cout << "Gra rozpoczela sie." << endl;
		cout << "===================\n" << endl;

		for (int i = 1; i <= 9; i++) {

			pozycja[i] = ' '; // zeruje tablcie 
			gracz = 'O';      //kolko zaczyna 
		}
		while (!wygrana(pozycja, 'X', player1, player2) && !wygrana(pozycja, 'O', player1, player2) && !remis(pozycja)) {

			ruch(pozycja, gracz, player1, player2); // dopoki program nie wykryje wygranej jednego z zawodnikow lub remisu bedzie umozliwaj nam ruch 
		}
		cout << "Checie zagrac jeszcze raz?(Tak/Nie) : "; // jezeli gra sie skonczy z powodu remisu lub wygranej program zapyta nas czy chemy zagrac jeszcze raz 
		cin >> wybór;
		cout << endl;
	} while ((wybór == "TAK") || (wybór == "Tak") || (wybór == "tak")); //jezeli wybierzemy nie program zakonczy sie 

	cout << "KONIEC GRY";
	return 0;
}