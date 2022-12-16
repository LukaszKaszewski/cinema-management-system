#ifndef HEADER1_H_INCLUDED
#define HEADER1_H_INCLUDED

 /*!
 movie information data - cinema room, display date, ticket price
 */
struct film {
	int kod;
	char tytul [30];
	char data [30];
	char godzina [30];
	int cena;
};

 /*!
 customer contact details - name and surname, email adress, phone number
 */
struct Osoba {
    char nazwisko [30];
    char mail [30];
    char telefon [30];
};

 /*!
 data that are needed for booking - customer contact details, cinema room, number of reservation, seats selection
 */
struct klient {
	int jaki_film;
	int ile_rez;
	char miejsca[60];
	struct Osoba dane;
};

void login();
void menu_glowne();
void dodaj_film();
void pokaz_filmy();
void skasuj_film();
void zarezerwuj_bilet();
void pokaz_rezerwacje();
void skasuj_rezerwacje();
void rezerwuj_miejsca();
void rezerwuj_sala1();
void rezerwuj_sala2();
void rezerwuj_sala3();
void rezerwuj_sala4();
void rezerwuj_sala5();
void usun_miejsce();
void usun_sala1();
void usun_sala2();
void usun_sala3();
void usun_sala4();
void usun_sala5();
void odczyt_z_pliku();
double zarabiam();

#endif // HEADER1_H_INCLUDED
