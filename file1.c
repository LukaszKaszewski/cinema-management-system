#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // getch()
#include <string.h> // strcmp
#include <ctype.h> // header
#include "header1.h"
#define WIERSZ 6
#define KOLUMNA 10
#define NORMALTICKET 20
#define HALFPRICETICKET 13

int Miejsca1[WIERSZ][KOLUMNA];
int Miejsca2[WIERSZ][KOLUMNA];
int Miejsca3[WIERSZ][KOLUMNA];
int Miejsca4[WIERSZ][KOLUMNA];
int Miejsca5[WIERSZ][KOLUMNA];
int **temp_M;
double daily_money;

 /*!
 logging into the system with a password
 */
void login()
{
	// login: cinema
	// haslo: zut
	// haslo2: admin

	int i = 0, a = 0;
    char userlogin [10];
    char password [10];
    char p;

    do {
    logo();
    printf(" \n              Wpisz login: ");
	scanf("%s", &userlogin);
	printf(" \n              Wpisz haslo: ");

	while(i <= 10)
	{
	    password[i] = getch();
	    p = password[i];
        if (p == 8) {   // BACKSPACE (ASCII)
            putch('\b'); // '\b' = 8
            putch(' ');
            putch('\b');
            i--;
          continue;
         } else if (p == 13) { // ENTER (ASCII)
            break;
	     } else if (p == 27) { // ESCAPE (ASCII)
            break;
	     } else printf("*");
        i++;
	}
	password[i]='\0';
	i=0;
		if (strcmp(userlogin, "cinema") == 0 && strcmp(password, "zut") == 0) {
	        printf("\n\n\n                    Logowanie udane");
            printf("\n\n                    Witamy z systemie rezerwacyjnym");
            printf("\n\n                    Nacisnij ENTER aby powrocic...");
            getch();
            break;
	} else {
            printf("\n\n\n                    Nieprawidlowy login lub haslo");
            printf("\n\n                    Nacisnij ENTER aby powrocic...");
            a++;
            getch();
            system("cls");
	}
} while (a<=2);
    if (a>2)
	{
		printf(" Wpisano nieprawidlowy login lub haslo po raz trzeci!!!");
        printf("\n\n ==================== DO WIDZENIA ====================\n");
                exit (0);
		getch();
		}
		system ("cls");
}

 /*!
 main menu - all available program options
 \param int choice1
 */
void menu_glowne(int choice1)
{
    struct film *fl = NULL;
    struct klient *kl = NULL;
    struct klient *dane = NULL;
    fl = (struct film *)malloc(sizeof(struct film));
    kl = (struct klient *)malloc(sizeof(struct klient));
    dane = (struct Osoba *)malloc(sizeof(struct Osoba));

    do {
    system("cls");
    logo();
    const char *menu[10]={"\t\t[1] Dodaj nowy film (haslo)\n","\t\t[2] Pokaz liste filmow\n","\t\t[3] Skasuj film (haslo)\n","\t\t[4] Zarezerwuj bilet\n",
                          "\t\t[5] Pokaz rezerwacje\n","\t\t[6] Usun rezerwacje\n","\t\t[7] Wybor miejsca / sprawdz dostepne miejsca\n",
                          "\t\t[8] Usun zarezerwowane miejsce na sali\n","\t\t[9] Odczyt rezerwacji z pliku\n","\t\t[0] Wyjdz\n\n"};
    for(int i=0; i<10; i++)
        printf("%s", menu[i]);
        printf("\t\tDokonaj wyboru: ");

    scanf("%d",&choice1);

    switch(choice1)
        {
            case 1 :
                dodaj_film();
                break;
            case 2 :
                pokaz_filmy();
                break;
            case 3 :
                skasuj_film();
                break;
            case 4 :
                zarezerwuj_bilet();
                break;
            case 5 :
                pokaz_rezerwacje();
                break;
            case 6 :
                skasuj_rezerwacje();
                break;
            case 7 :
                rezerwuj_miejsca();
                break;
            case 8 :
                usun_miejsce();
                break;
            case 9 :
                odczyt_z_pliku();
                break;
            case 0 :
                system("cls");
                logo();
                printf("\n\tDziesiejszy przychod kina wynosi: %.2f PLN\n", daily_money);
                printf("\n\tPrzed wyjsciem do domu, pamietaj o rozliczeniu kasy");
                printf("\n\n============================== DO WIDZENIA ==============================\n");
                Sleep(1500);
                free(fl);
                free(kl);
                free(dane);
                exit(0);
                break;
            default:
                printf(" Nie ma takiej opcji w Menu  [WCISNIJ ENTER]");
        }
    getchar(); getchar();
    } while(choice1 != 0);
}

 /*!
 small alphanumeric graphics
 */
void logo()
{
    const char *logo[5]={"*************************************************************************\n","*\t\t\t\t\t\t\t\t\t*\n",
                         "*\t\tWitaj w programie rezerwacyjnym kina ZUT!!!\t\t*\n","*\t\t\t\t\t\t\t\t\t*\n",
                         "*************************************************************************\n"};
    for(int i=0; i<5; i++)
        printf("%s", logo[i]);
}

 /*!
 password protected option, used to change the cinema repertoire - adds a new movie
 */
void dodaj_film()
{
	int i = 0;
	char p;
	char pass[10], pass2[10]="admin";
	printf("\n Wprowadz haslo dostepu: ");

	while(i <= 10)
	{
	    pass[i] = getch();
	    p = pass [i];
        if (p == 8) { // BACKSPACE
            putch('\b'); // BACKSPACE
            putch(' ');
            putch('\b');
            i--;
          continue;
         } else if (p == 13) { // ENTER
            break;
	     } else if (p == 27) { // ESCAPE
            break;
	     } else printf("*");
        i++;
	}
	pass[i]='\0';

	if (strcmp(pass,pass2)==0) {
    FILE *fp;
	struct film fl;
	printf("\n Aby anulowac wprowadzenie filmu do repertuaru, w polu PODAJ CENE - wybierz [*]");
	printf("\n\n Wpisz nr sali [x]: ");
	scanf("%d",&fl.kod);
	if(fl.kod<1 || fl.kod>5) {
        printf(" Wybrano nieprawidlowa sale, sprobuj ponownie");
        return EXIT_SUCCESS;
	} else
	getchar();
    printf(" Podaj tytul: ");
    gets(fl.tytul);
	printf(" Podaj date emisji [RRRR.MM.DD]: ");
	scanf("%s",fl.data);
    printf(" Podaj godzine emisji [xx:xx]: ");
	scanf("%s",fl.godzina);
	printf(" Podaj cene biletu [PLN]: ");
	scanf("%d",&fl.cena);

	fp=fopen("repertuar.txt","a");

	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
		fprintf(fp,"Sala nr: %d\tTytul: %s\t\tData: %s\tGodzina: %s\tCena: %d\n",fl.kod,fl.tytul,fl.data,fl.godzina, fl.cena); // kolejnosc zapisu danych w pliku
		printf("\n Dodano nowy film\n");

        fclose(fp);

     } else
		printf("\n\n\n                    Nieprawidlowy login lub haslo");
        printf("\n\n                    Nacisnij ENTER...");

}

 /*!
 is used to display the cinema's repertoire
 */
void pokaz_filmy()
{
	system("cls");
	logo();
	char ch;
	FILE *fp;

	fp = fopen("repertuar.txt","r");
	if(fp == NULL)
	{
		printf(" Nie znaleziono pliku");
	}
	else
	{
		while( ( ch = fgetc(fp) ) != EOF )
      		printf("%c",ch);
	}
    printf("\n\n                    Nacisnij ENTER aby powrocic...");
	fclose(fp);
}

 /*!
 password protected option, used to change the cinema's repertoire - deletes the old movie
 */
void skasuj_film()
{
	int i = 0;
	char p;
	char pass[10],pass2[10]="admin";
	printf("\n Wprowadz haslo dostepu: ");

	while(i <= 10)
	{
	    pass[i] = getch();
	    p = pass [i];
        if (p == 8) {
            putch('\b');
            putch(NULL);
            putch('\b');
            i--;
          continue;
         } else if (p == 13) {
            break;
	     } else if (p == 27) {
            break;
	     } else printf("*");
        i++;
	}
	pass[i]='\0';
	i=0;
	if (strcmp(pass,pass2)==0) {

	FILE *fileptr1, *fileptr2;
    char filename[] = "repertuar.txt";
    char ch;
    int skasuj_linie, temp = 1;

    system("cls");
    logo();
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }

    rewind(fileptr1);
    printf(" \n Wprowadz numer linii ktory chcesz skasowac? (aby przerwac, wybierz [0])\n");
    scanf("%d", &skasuj_linie);
    if(skasuj_linie==0) {
        printf("\n\n                    Nacisnij ENTER aby powrocic...");
        return EXIT_SUCCESS;
    } else
    fileptr2 = fopen("replika.c", "w");
    ch = 'A';
    while (ch != EOF)
    {
        ch = getc(fileptr1);
        if (temp != skasuj_linie)
        {
            putc(ch, fileptr2);
        }
        if (ch == '\n')
        {
            temp++;
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove(filename);
    rename("replika.c", filename);
    printf("\n Po zmianach repertuar wyglada nastepujaca: \n\n");
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    printf("\n\n                    Nacisnij ENTER aby powrocic...");
    fclose(fileptr1);
    return 0;

    } else
		printf("\n\n\n                    Nieprawidlowy login lub haslo");
        printf("\n\n                    Nacisnij ENTER aby powrocic...");
	return 0;
}

 /*!
 makes it possible to reserve the number of places, displays the amount to be paid
 */
void zarezerwuj_bilet()
{
	double n_ticket, hp_ticket;
	FILE *fp;
	struct klient kl;
	printf("\n Aby anulowac wprowadzenie rezerwacji, w polu ILOSC BILETOW (N/U) - wybierz [*]\n"),
	printf("\n Podaj sale: ");
	scanf("%d",&kl.jaki_film );
	if(kl.jaki_film<1 || kl.jaki_film>5) {
        printf(" Wybrano zly seans, sprobuj ponownie");
        return EXIT_SUCCESS;
	} else
	getchar();
	printf(" Podaj imie i nazwisko: ");
	gets(kl.dane.nazwisko);
    printf(" Podaj adres mailowy: ");
    scanf("%s",kl.dane.mail);
	printf(" Podaj numer telefonu: ");
	scanf("%s",kl.dane.telefon);
	printf(" Podaj liczbe rezerwacji: ");
	scanf("%d",&kl.ile_rez );
	printf(" Rezerwowane miejsca: ");
	scanf("%s", kl.miejsca);
	printf(" Ile biletow normalnych (20 PLN): ");
	scanf("%lf", &n_ticket);
	printf(" Ile biletow ulgowych (13PLN - emeryci, rencisci, mlodzierz uczaca sie do 26ego roku zycia): ");
	scanf("%lf", &hp_ticket);

	fp=fopen("rezerwacje.txt","a");

	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
		fprintf(fp,"Sala nr: %d\tImie i nazwisko: %s\t\tAdres mailowy: %s\tTelefon: %s\tLiczba rezerwacji: %d\tKtore miejsca: %s\n",kl.jaki_film,kl.dane.nazwisko,kl.dane.mail,kl.dane.telefon,kl.ile_rez,kl.miejsca); // sekwencja zapisu danych w pliku
		printf("\n Dodano nowa rezerwacje\n");
		printf(" Koszt biletow to: %.2f PLN", n_ticket*NORMALTICKET+hp_ticket*HALFPRICETICKET);
		printf("\n\n                    Nacisnij ENTER aby powrocic...");

        fclose(fp);
        zarabiam(n_ticket, hp_ticket);
}

 /*!
 shows all current bookings
 */
void pokaz_rezerwacje()
{
    system("cls");
	logo();
	char ch;
	FILE *fp;

	fp = fopen("rezerwacje.txt","r");
	if(fp == NULL)
	{
		printf(" Nie znaleziono pliku");
	}
	else
	{
		while( ( ch = fgetc(fp) ) != EOF )
      		printf("%c",ch);
	}
    printf("\n\n                    Nacisnij ENTER aby powrocic...");
	fclose(fp);
}

 /*!
 allows you to delete reservations from the system
 */
void skasuj_rezerwacje()
{
    FILE *fileptr1, *fileptr2;
    char filename[] = "rezerwacje.txt";
    char ch;
    int skasuj_linie, temp = 1;

    system("cls");
    logo();
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }

    rewind(fileptr1); //przewija plik do poczatku
    printf(" \n Wprowadz numer linii ktory chcesz skasowac? (aby przerwac, wybierz [0])\n");
    scanf("%d", &skasuj_linie);
    if(skasuj_linie==0) {
        printf("\n\n                    Nacisnij ENTER aby powrocic...");
        return EXIT_SUCCESS;
    } else
    fileptr2 = fopen("replika.c", "w");
    ch = 'A';
    while (ch != EOF)
    {
        ch = getc(fileptr1);

        if (temp != skasuj_linie) // z wyjatkiem kasowanej linii
        {
            putc(ch, fileptr2);// kopiuje zawartossc do pliku tymczasowego replika.c
        }
        if (ch == '\n')
        {
            temp++;
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove(filename);
    rename("replika.c", filename);
    printf("\n Po zmianach lista rezerwacji wyglada nastepujaca: \n\n");
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    printf("\n\n                    Nacisnij ENTER aby powrocic...");
    fclose(fileptr1);
    return 0;
}

 /*!
 allows you to reserve indicated seats in the cinema room
 \param int choice2
 */
void rezerwuj_miejsca(int choice2)
{
    system("cls");
    logo();
    const char *sala[7]={"\t\tNa ktorej sali rezerwujesz miejsce: \n\n","\t\t[1] Sala nr 1\n","\t\t[2] Sala nr 2\n","\t\t[3] Sala nr 3\n","\t\t[4] Sala nr 4\n","\t\t[5] Sala nr 5\n","\t\t[0] Wyjdz\n\n"};
    for(int i=0; i<7; i++)
        printf("%s", sala[i]);
        printf("\t\tDokonaj wyboru: ");
    scanf("%d", &choice2);

    switch (choice2)
        {
            case 1 :
                rezerwuj_sala1();
                break;
            case 2 :
                rezerwuj_sala2();
                break;
            case 3 :
                rezerwuj_sala3();
                break;
            case 4 :
                rezerwuj_sala4();
                break;
            case 5 :
                rezerwuj_sala5();
                break;
            case 0:
                printf("\n\n                    Nacisnij ENTER aby powrocic...");
                return EXIT_SUCCESS;
                break;
            default:
                printf(" Nie ma takiej opcji w Menu  [WCISNIJ ENTER]");
        }
}

 /*!
 book a place - cinema room No. 1
 */
void rezerwuj_sala1()
{
    int i, j;
    int rzad, miejsce;
    int ile_miejsc;
    temp_M = (int**)malloc(WIERSZ*sizeof(int*));
    for (i = 0; i < WIERSZ; i++)
        temp_M[i]=(int*)malloc(KOLUMNA*sizeof(int));
        temp_M[i][j] = Miejsca1[i][j];
    printf("\t \t Miejsca\n");
    printf("\t1 2 3 4 5 6 7 8 9 10\n");
    for (i = 0; i < WIERSZ; i++)
    {
        printf("rzad %d: ", i + 1);
        for (j = 0; j < KOLUMNA; j++)
           printf("%d ", Miejsca1[i][j]);
           printf("\n");
    }
    printf("\n");

    printf(" Ile miejsc chcesz zarezerwowac? (aby przerwac, wybierz [0])\n");
    scanf_s("%d", &ile_miejsc);
    if(ile_miejsc==0) {
            printf("\n                    Nacisnij ENTER aby powrocic...");
            return EXIT_SUCCESS;
    } else
    for (i = 1; i <= ile_miejsc; i++)
    {
        printf("Ktory rzad chcesz wybrac? : ");
        scanf_s("%d", &rzad);
        printf("Ktore miejsce chcesz wybrac? : ");
        scanf_s("%d", &miejsce);

        if (rzad > WIERSZ || miejsce > KOLUMNA) {
            printf("Zly wybor, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else if (Miejsca1[rzad - 1][miejsce - 1] != 0) {
            printf("Wybrane miejsce jest juz zajete, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else {
            Miejsca1[rzad - 1][miejsce - 1] = 1;
            printf("Gratuluje! Miejsce zarezerwowanie!\n");
            printf("\t \t Miejsca\n");
            printf("\t1 2 3 4 5 6 7 8 9 10\n");
            for (int i = 0; i < WIERSZ; i++)
                {
                    printf("rzad %d: ", i + 1);
                    for (int j = 0; j < KOLUMNA; j++)
                    printf("%d ", Miejsca1[i][j]);
                    printf("\n");
                }
            printf("\n");
        }
    }

    remove("sala1.txt");
    FILE *fp;
	fp=fopen("sala1.txt","a");
	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
        fprintf(fp,"\t \t Miejsca\n");
        fprintf(fp,"\t1 2 3 4 5 6 7 8 9 10\n");
		for (i = 0; i < WIERSZ; i++)
                {
                    fprintf(fp,"rzad %d: ", i + 1);
                    for (j = 0; j < KOLUMNA; j++)
                    fprintf(fp,"%d ", Miejsca1[i][j]);
                    fprintf(fp,"\n");
                }
        fclose(fp);
    printf("\n\n                    Nacisnij ENTER aby powrocic...");
    for(int i=0; i<WIERSZ; i++)
        free(temp_M[i]);
    free(temp_M);
}

 /*!
 book a place - cinema room No. 2
 */
void rezerwuj_sala2()
{
    int i, j;
    int rzad, miejsce;
    int ile_miejsc;
    temp_M = (int**)malloc(WIERSZ*sizeof(int*));
    for (i = 0; i < WIERSZ; i++)
        temp_M[i]=(int*)malloc(KOLUMNA*sizeof(int));
        temp_M[i][j] = Miejsca2[i][j];
    printf("\t \t Miejsca\n");
    printf("\t1 2 3 4 5 6 7 8 9 10\n");
    for (i = 0; i < WIERSZ; i++)
    {
        printf("rzad %d: ", i + 1);
        for (j = 0; j < KOLUMNA; j++)
           printf("%d ", Miejsca2[i][j]);
           printf("\n");
    }
    printf("\n");

    printf(" Ile miejsc chcesz zarezerwowac? (aby przerwac, wybierz [0])\n");
    scanf_s("%d", &ile_miejsc);
    if(ile_miejsc==0) {
            printf("\n                    Nacisnij ENTER aby powrocic...");
            return EXIT_SUCCESS;
    } else
    for (i = 1; i <= ile_miejsc; i++)
    {
        printf("Ktory rzad chcesz wybrac? : ");
        scanf_s("%d", &rzad);
        printf("Ktore miejsce chcesz wybrac? : ");
        scanf_s("%d", &miejsce);
        if (rzad > WIERSZ || miejsce > KOLUMNA) {
            printf("Zly wybor, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else if (Miejsca2[rzad - 1][miejsce - 1] != 0) {
            printf("Wybrane miejsce jest juz zajete, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else {
            Miejsca2[rzad - 1][miejsce - 1] = 1;
            printf("Gratuluje! Miejsce zarezerwowanie!\n");
            printf("\t \t Miejsca\n");
            printf("\t1 2 3 4 5 6 7 8 9 10\n");
            for (int i = 0; i < WIERSZ; i++)
                {
                    printf("rzad %d: ", i + 1);
                    for (int j = 0; j < KOLUMNA; j++)
                    printf("%d ", Miejsca2[i][j]);
                    printf("\n");
                }
            printf("\n");
        }
    }

    remove("sala2.txt");
    FILE *fp;
	fp=fopen("sala2.txt","a");
	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
        fprintf(fp,"\t \t Miejsca\n");
        fprintf(fp,"\t1 2 3 4 5 6 7 8 9 10\n");
		for (i = 0; i < WIERSZ; i++)
                {
                    fprintf(fp,"rzad %d: ", i + 1);
                    for (j = 0; j < KOLUMNA; j++)
                    fprintf(fp,"%d ", Miejsca2[i][j]);
                    fprintf(fp,"\n");
                }
        fclose(fp);

    printf("\n\n                    Nacisnij ENTER aby powrocic...");
    for(int i=0; i<WIERSZ; i++)
        free(temp_M[i]);
    free(temp_M);
}

 /*!
 book a place - cinema room No. 3
 */
void rezerwuj_sala3()
{

    int i, j;
    int rzad, miejsce;
    int ile_miejsc;
    temp_M = (int**)malloc(WIERSZ*sizeof(int*));
    for (i = 0; i < WIERSZ; i++)
        temp_M[i]=(int*)malloc(KOLUMNA*sizeof(int));
        temp_M[i][j] = Miejsca3[i][j];
    printf("\t \t Miejsca\n");
    printf("\t1 2 3 4 5 6 7 8 9 10\n");
    for (i = 0; i < WIERSZ; i++)
    {
        printf("rzad %d: ", i + 1);
        for (j = 0; j < KOLUMNA; j++)
           printf("%d ", Miejsca3[i][j]);
           printf("\n");
    }
    printf("\n");

    printf(" Ile miejsc chcesz zarezerwowac? (aby przerwac, wybierz [0])\n");
    scanf_s("%d", &ile_miejsc);
    if(ile_miejsc==0) {
            printf("\n                    Nacisnij ENTER aby powrocic...");
            return EXIT_SUCCESS;
    } else
    for (i = 1; i <= ile_miejsc; i++)
    {
        printf("Ktory rzad chcesz wybrac? : ");
        scanf_s("%d", &rzad);
        printf("Ktore miejsce chcesz wybrac? : ");
        scanf_s("%d", &miejsce);
        if (rzad > WIERSZ || miejsce > KOLUMNA) {
            printf("Zly wybor, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else if (Miejsca3[rzad - 1][miejsce - 1] != 0) {
            printf("Wybrane miejsce jest juz zajete, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else {
            Miejsca3[rzad - 1][miejsce - 1] = 1;
            printf("Gratuluje! Miejsce zarezerwowanie!\n");
            printf("\t \t Miejsca\n");
            printf("\t1 2 3 4 5 6 7 8 9 10\n");
            for (int i = 0; i < WIERSZ; i++)
                {
                    printf("rzad %d: ", i + 1);
                    for (int j = 0; j < KOLUMNA; j++)
                    printf("%d ", Miejsca3[i][j]);
                    printf("\n");
                }
            printf("\n");
        }
    }

    remove("sala3.txt");
    FILE *fp;
	fp=fopen("sala3.txt","a");
	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
        fprintf(fp,"\t \t Miejsca\n");
        fprintf(fp,"\t1 2 3 4 5 6 7 8 9 10\n");
		for (i = 0; i < WIERSZ; i++)
                {
                    fprintf(fp,"rzad %d: ", i + 1);
                    for (j = 0; j < KOLUMNA; j++)
                    fprintf(fp,"%d ", Miejsca3[i][j]);
                    fprintf(fp,"\n");
                }
        fclose(fp);

    printf("\n\n                    Nacisnij ENTER aby powrocic...");
    for(int i=0; i<WIERSZ; i++)
        free(temp_M[i]);
    free(temp_M);
}
 /*!
 book a place - cinema room No. 4
 */
void rezerwuj_sala4()
{
    int i, j;
    int rzad, miejsce;
    int ile_miejsc;
    temp_M = (int**)malloc(WIERSZ*sizeof(int*));
    for (i = 0; i < WIERSZ; i++)
        temp_M[i]=(int*)malloc(KOLUMNA*sizeof(int));
        temp_M[i][j] = Miejsca4[i][j];
    printf("\t \t Miejsca\n");
    printf("\t1 2 3 4 5 6 7 8 9 10\n");
    for (i = 0; i < WIERSZ; i++)
    {
        printf("rzad %d: ", i + 1);
        for (j = 0; j < KOLUMNA; j++)
           printf("%d ", Miejsca4[i][j]);
           printf("\n");
    }
    printf("\n");

    printf(" Ile miejsc chcesz zarezerwowac? (aby przerwac, wybierz [0])\n");
    scanf_s("%d", &ile_miejsc);
    if(ile_miejsc==0) {
            printf("\n                    Nacisnij ENTER aby powrocic...");
            return EXIT_SUCCESS;
    } else
    for (i = 1; i <= ile_miejsc; i++)
    {
        printf("Ktory rzad chcesz wybrac? : ");
        scanf_s("%d", &rzad);
        printf("Ktore miejsce chcesz wybrac? : ");
        scanf_s("%d", &miejsce);
        if (rzad > WIERSZ || miejsce > KOLUMNA) {
            printf("Zly wybor, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else if (Miejsca4[rzad - 1][miejsce - 1] != 0) {
            printf("Wybrane miejsce jest juz zajete, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else {
            Miejsca4[rzad - 1][miejsce - 1] = 1;
            printf("Gratuluje! Miejsce zarezerwowanie!\n");
            printf("\t \t Miejsca\n");
            printf("\t1 2 3 4 5 6 7 8 9 10\n");
            for (int i = 0; i < WIERSZ; i++)
                {
                    printf("rzad %d: ", i + 1);
                    for (int j = 0; j < KOLUMNA; j++)
                    printf("%d ", Miejsca4[i][j]);
                    printf("\n");
                }
            printf("\n");
        }
    }

    remove("sala4.txt");
    FILE *fp;
	fp=fopen("sala4.txt","a");
	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
        fprintf(fp,"\t \t Miejsca\n");
        fprintf(fp,"\t1 2 3 4 5 6 7 8 9 10\n");
		for (i = 0; i < WIERSZ; i++)
                {
                    fprintf(fp,"rzad %d: ", i + 1);
                    for (j = 0; j < KOLUMNA; j++)
                    fprintf(fp,"%d ", Miejsca4[i][j]);
                    fprintf(fp,"\n");
                }
		printf("\n Stan rezerwacji zapisany do pliku\n");
        fclose(fp);

    printf("\n\n                    Nacisnij ENTER aby powrocic...");
    for(int i=0; i<WIERSZ; i++)
        free(temp_M[i]);
    free(temp_M);
}

 /*!
 book a place - cinema room No. 5
 */
void rezerwuj_sala5()
{
    int i, j;
    int rzad, miejsce;
    int ile_miejsc;
    temp_M = (int**)malloc(WIERSZ*sizeof(int*));
    for (i = 0; i < WIERSZ; i++)
        temp_M[i]=(int*)malloc(KOLUMNA*sizeof(int));
        temp_M[i][j] = Miejsca5[i][j];
    printf("\t \t Miejsca\n");
    printf("\t1 2 3 4 5 6 7 8 9 10\n");
    for (i = 0; i < WIERSZ; i++)
    {
        printf("rzad %d: ", i + 1);
        for (j = 0; j < KOLUMNA; j++)
           printf("%d ", Miejsca5[i][j]);
           printf("\n");
    }
    printf("\n");

    printf(" Ile miejsc chcesz zarezerwowac? (aby przerwac, wybierz [0])\n");
    scanf_s("%d", &ile_miejsc);
    if(ile_miejsc==0) {
            printf("\n                    Nacisnij ENTER aby powrocic...");
            return EXIT_SUCCESS;
    } else
    for (i = 1; i <= ile_miejsc; i++)
    {
        printf("Ktory rzad chcesz wybrac? : ");
        scanf_s("%d", &rzad);
        printf("Ktore miejsce chcesz wybrac? : ");
        scanf_s("%d", &miejsce);
        if (rzad > WIERSZ || miejsce > KOLUMNA) {
            printf("Zly wybor, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else if (Miejsca5[rzad - 1][miejsce - 1] != 0) {
            printf("Wybrane miejsce jest juz zajete, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else {
            Miejsca5[rzad - 1][miejsce - 1] = 1;
            printf("Gratuluje! Miejsce zarezerwowanie!\n");
            printf("\t \t Miejsca\n");
            printf("\t1 2 3 4 5 6 7 8 9 10\n");
            for (int i = 0; i < WIERSZ; i++)
                {
                    printf("rzad %d: ", i + 1);
                    for (int j = 0; j < KOLUMNA; j++)
                    printf("%d ", Miejsca5[i][j]);
                    printf("\n");
                }
            printf("\n");
        }
    }

    remove("sala5.txt");
    FILE *fp;
	fp=fopen("sala5.txt","a");
	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
        fprintf(fp,"\t \t Miejsca\n");
        fprintf(fp,"\t1 2 3 4 5 6 7 8 9 10\n");
		for (i = 0; i < WIERSZ; i++)
                {
                    fprintf(fp,"rzad %d: ", i + 1);
                    for (j = 0; j < KOLUMNA; j++)
                    fprintf(fp,"%d ", Miejsca5[i][j]);
                    fprintf(fp,"\n");
                }
		printf("\n Stan rezerwacji zapisany do pliku\n");
        fclose(fp);

    printf("\n\n                    Nacisnij ENTER aby powrocic...");
    for(int i=0; i<WIERSZ; i++)
        free(temp_M[i]);
    free(temp_M);
}

 /*!
 deletes reservations for selected seats in the cinema hall
 \param int choice3
 */
void usun_miejsce(int choice3)
{
    system("cls");
    logo();
    const char *sala[7]={"\t\tNa ktorej sali chcesz anulowac rezerwacje: \n\n","\t\t[1] Sala nr 1\n","\t\t[2] Sala nr 2\n","\t\t[3] Sala nr 3\n","\t\t[4] Sala nr 4\n","\t\t[5] Sala nr 5\n","\t\t[0] Wyjdz\n\n"};
    for(int i=0; i<7; i++)
        printf("%s", sala[i]);
        printf("\t\tDokonaj wyboru: ");
    scanf("%d", &choice3);

    switch (choice3)
        {
            case 1 :
                usun_sala1();
                break;
            case 2 :
                usun_sala2();
                break;
            case 3 :
                usun_sala3();
                break;
            case 4 :
                usun_sala4();
                break;
            case 5 :
                usun_sala5();
                break;
            case 0:
                printf("\n\n                    Nacisnij ENTER aby powrocic...");
                return EXIT_SUCCESS;
                break;
            default:
                printf(" Nie ma takiej opcji w Menu  [WCISNIJ ENTER]");
        }
}

 /*!
 delete a place - cinema room No. 1
 */
void usun_sala1()
{
    int i, j;
    int rzad, miejsce;
    int ile_miejsc;
    printf("\t \t Miejsca\n");
    printf("\t1 2 3 4 5 6 7 8 9 10\n");
    for (i = 0; i < WIERSZ; i++)
    {
        printf("rzad %d: ", i + 1);
        for (j = 0; j < KOLUMNA; j++)
           printf("%d ", Miejsca1[i][j]);
           printf("\n");
    }
    printf("\n");

    printf(" Ile rezerwacji chcesz anulowac? (aby przerwac, wybierz [0])\n");
    scanf_s("%d", &ile_miejsc);
    if(ile_miejsc==0) {
            printf("\n                    Nacisnij ENTER aby powrocic...");
            return EXIT_SUCCESS;
    } else
    for (i = 1; i <= ile_miejsc; i++)
    {
        printf("Ktory rzad chcesz wybrac? : ");
        scanf_s("%d", &rzad);
        printf("Ktore miejsce chcesz wybrac? : ");
        scanf_s("%d", &miejsce);
        if (rzad > WIERSZ || miejsce > KOLUMNA) {
            printf("Zly wybor, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else if (Miejsca1[rzad - 1][miejsce - 1] != 1) {
            printf("Wybrane miejsce nie bylo zajete, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else {
            Miejsca1[rzad - 1][miejsce - 1] = 0;
            printf("Miejsce usuniete z rezerwacji!\n");
            printf("\t \t Miejsca\n");
            printf("\t1 2 3 4 5 6 7 8 9 10\n");
            for (int i = 0; i < WIERSZ; i++)
                {
                    printf("rzad %d: ", i + 1);
                    for (int j = 0; j < KOLUMNA; j++)
                    printf("%d ", Miejsca1[i][j]);
                    printf("\n");
                }
            printf("\n");
        }
    }

    remove("sala1.txt");
    FILE *fp;
	fp=fopen("sala1.txt","a");
	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
        fprintf(fp,"\t \t Miejsca\n");
        fprintf(fp,"\t1 2 3 4 5 6 7 8 9 10\n");
		for (i = 0; i < WIERSZ; i++)
                {
                    fprintf(fp,"rzad %d: ", i + 1);
                    for (j = 0; j < KOLUMNA; j++)
                    fprintf(fp,"%d ", Miejsca1[i][j]);
                    fprintf(fp,"\n");
                }
		printf("\n Stan rezerwacji zapisany do pliku\n");
        fclose(fp);

    printf("\n\n                    Nacisnij ENTER aby powrocic...");
}

 /*!
 delete a place - cinema room No. 2
 */
void usun_sala2()
{
    int i, j;
    int rzad, miejsce;
    int ile_miejsc;
    printf("\t \t Miejsca\n");
    printf("\t1 2 3 4 5 6 7 8 9 10\n");
    for (i = 0; i < WIERSZ; i++)
    {
        printf("rzad %d: ", i + 1);
        for (j = 0; j < KOLUMNA; j++)
           printf("%d ", Miejsca2[i][j]);
           printf("\n");
    }
    printf("\n");

    printf(" Ile rezerwacji chcesz anulowac? (aby przerwac, wybierz [0])\n");
    scanf_s("%d", &ile_miejsc);
    if(ile_miejsc==0) {
            printf("\n                    Nacisnij ENTER aby powrocic...");
            return EXIT_SUCCESS;
    } else
    for (i = 1; i <= ile_miejsc; i++)
    {
        printf("Ktory rzad chcesz wybrac? : ");
        scanf_s("%d", &rzad);
        printf("Ktore miejsce chcesz wybrac? : ");
        scanf_s("%d", &miejsce);
        if (rzad > WIERSZ || miejsce > KOLUMNA) {
            printf("Zly wybor, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else if (Miejsca2[rzad - 1][miejsce - 1] != 1) {
            printf("Wybrane miejsce nie bylo zajete, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else {
            Miejsca2[rzad - 1][miejsce - 1] = 0;
            printf("Miejsce usuniete z rezerwacji!\n");
            printf("\t \t Miejsca\n");
            printf("\t1 2 3 4 5 6 7 8 9 10\n");
            for (int i = 0; i < WIERSZ; i++)
                {
                    printf("rzad %d: ", i + 1);
                    for (int j = 0; j < KOLUMNA; j++)
                    printf("%d ", Miejsca2[i][j]);
                    printf("\n");
                }
            printf("\n");
        }
    }

    remove("sala2.txt");
    FILE *fp;
	fp=fopen("sala2.txt","a");
	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
        fprintf(fp,"\t \t Miejsca\n");
        fprintf(fp,"\t1 2 3 4 5 6 7 8 9 10\n");
		for (i = 0; i < WIERSZ; i++)
                {
                    fprintf(fp,"rzad %d: ", i + 1);
                    for (j = 0; j < KOLUMNA; j++)
                    fprintf(fp,"%d ", Miejsca2[i][j]);
                    fprintf(fp,"\n");
                }
        fclose(fp);
    printf("\n\n                    Nacisnij ENTER aby powrocic...");
}

 /*!
 delete a place - cinema room No. 3
 */
void usun_sala3()
{
    int i, j;
    int rzad, miejsce;
    int ile_miejsc;
    printf("\t \t Miejsca\n");
    printf("\t1 2 3 4 5 6 7 8 9 10\n");
    for (i = 0; i < WIERSZ; i++)
    {
        printf("rzad %d: ", i + 1);
        for (j = 0; j < KOLUMNA; j++)
           printf("%d ", Miejsca3[i][j]);
           printf("\n");
    }
    printf("\n");

    printf(" Ile rezerwacji chcesz anulowac? (aby przerwac, wybierz [0])\n");
    scanf_s("%d", &ile_miejsc);
    if(ile_miejsc==0) {
            printf("\n                    Nacisnij ENTER aby powrocic...");
            return EXIT_SUCCESS;
    } else
    for (i = 1; i <= ile_miejsc; i++)
    {
        printf("Ktory rzad chcesz wybrac? : ");
        scanf_s("%d", &rzad);
        printf("Ktore miejsce chcesz wybrac? : ");
        scanf_s("%d", &miejsce);
        if (rzad > WIERSZ || miejsce > KOLUMNA) {
            printf("Zly wybor, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else if (Miejsca3[rzad - 1][miejsce - 1] != 1) {
            printf("Wybrane miejsce nie bylo zajete, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else {
            Miejsca3[rzad - 1][miejsce - 1] = 0;
            printf("Miejsce usuniete z rezerwacji!\n");
            printf("\t \t Miejsca\n");
            printf("\t1 2 3 4 5 6 7 8 9 10\n");
            for (int i = 0; i < WIERSZ; i++)
                {
                    printf("rzad %d: ", i + 1);
                    for (int j = 0; j < KOLUMNA; j++)
                    printf("%d ", Miejsca3[i][j]);
                    printf("\n");
                }
            printf("\n");
        }
    }

    remove("sala3.txt");
    FILE *fp;
	fp=fopen("sala3.txt","a");
	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
        fprintf(fp,"\t \t Miejsca\n");
        fprintf(fp,"\t1 2 3 4 5 6 7 8 9 10\n");
		for (i = 0; i < WIERSZ; i++)
                {
                    fprintf(fp,"rzad %d: ", i + 1);
                    for (j = 0; j < KOLUMNA; j++)
                    fprintf(fp,"%d ", Miejsca3[i][j]);
                    fprintf(fp,"\n");
                }
        fclose(fp);
    printf("\n\n                    Nacisnij ENTER aby powrocic...");
}

 /*!
 delete a place - cinema room No. 4
 */
void usun_sala4()
{
    int i, j;
    int rzad, miejsce;
    int ile_miejsc;
    printf("\t \t Miejsca\n");
    printf("\t1 2 3 4 5 6 7 8 9 10\n");
    for (i = 0; i < WIERSZ; i++)
    {
        printf("rzad %d: ", i + 1);
        for (j = 0; j < KOLUMNA; j++)
           printf("%d ", Miejsca4[i][j]);
           printf("\n");
    }
    printf("\n");

    printf(" Ile rezerwacji chcesz anulowac? (aby przerwac, wybierz [0])\n");
    scanf_s("%d", &ile_miejsc);
    if(ile_miejsc==0) {
            printf("\n                    Nacisnij ENTER aby powrocic...");
            return EXIT_SUCCESS;
    } else
    for (i = 1; i <= ile_miejsc; i++)
    {
        printf("Ktory rzad chcesz wybrac? : ");
        scanf_s("%d", &rzad);
        printf("Ktore miejsce chcesz wybrac? : ");
        scanf_s("%d", &miejsce);
        if (rzad > WIERSZ || miejsce > KOLUMNA) {
            printf("Zly wybor, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else if (Miejsca4[rzad - 1][miejsce - 1] != 1) {
            printf("Wybrane miejsce nie bylo zajete, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else {
            Miejsca4[rzad - 1][miejsce - 1] = 0;
            printf("Miejsce usuniete z rezerwacji!\n");
            printf("\t \t Miejsca\n");
            printf("\t1 2 3 4 5 6 7 8 9 10\n");
            for (int i = 0; i < WIERSZ; i++)
                {
                    printf("rzad %d: ", i + 1);
                    for (int j = 0; j < KOLUMNA; j++)
                    printf("%d ", Miejsca4[i][j]);
                    printf("\n");
                }
            printf("\n");
        }
    }

    remove("sala4.txt");
    FILE *fp;
	fp=fopen("sala4.txt","a");
	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
        fprintf(fp,"\t \t Miejsca\n");
        fprintf(fp,"\t1 2 3 4 5 6 7 8 9 10\n");
		for (i = 0; i < WIERSZ; i++)
                {
                    fprintf(fp,"rzad %d: ", i + 1);
                    for (j = 0; j < KOLUMNA; j++)
                    fprintf(fp,"%d ", Miejsca4[i][j]);
                    fprintf(fp,"\n");
                }
        fclose(fp);
    printf("\n\n                    Nacisnij ENTER aby powrocic...");
}

 /*!
 delete a place - cinema room No. 5
 */
void usun_sala5()
{
    int i, j;
    int rzad, miejsce;
    int ile_miejsc;
    printf("\t \t Miejsca\n");
    printf("\t1 2 3 4 5 6 7 8 9 10\n");
    for (i = 0; i < WIERSZ; i++)
    {
        printf("rzad %d: ", i + 1);
        for (j = 0; j < KOLUMNA; j++)
           printf("%d ", Miejsca5[i][j]);
           printf("\n");
    }
    printf("\n");

    printf(" Ile rezerwacji chcesz anulowac? (aby przerwac, wybierz [0])\n");
    scanf_s("%d", &ile_miejsc);
    if(ile_miejsc==0) {
            printf("\n                    Nacisnij ENTER aby powrocic...");
            return EXIT_SUCCESS;
    } else
    for (i = 1; i <= ile_miejsc; i++)
    {
        printf("Ktory rzad chcesz wybrac? : ");
        scanf_s("%d", &rzad);
        printf("Ktore miejsce chcesz wybrac? : ");
        scanf_s("%d", &miejsce);
        if (rzad > WIERSZ || miejsce > KOLUMNA) {
            printf("Zly wybor, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else if (Miejsca5[rzad - 1][miejsce - 1] != 1) {
            printf("Wybrane miejsce nie bylo zajete, sprobuj ponownie!\n");
            printf("Ktory rzad chcesz wybrac? : ");
            scanf_s("%d", &rzad);
            printf("Ktore miejsce chcesz wybrac? : ");
            scanf_s("%d", &miejsce);
        } else {
            Miejsca5[rzad - 1][miejsce - 1] = 0;
            printf("Miejsce usuniete z rezerwacji!\n");
            printf("\t \t Miejsca\n");
            printf("\t1 2 3 4 5 6 7 8 9 10\n");
            for (int i = 0; i < WIERSZ; i++)
                {
                    printf("rzad %d: ", i + 1);
                    for (int j = 0; j < KOLUMNA; j++)
                    printf("%d ", Miejsca5[i][j]);
                    printf("\n");
                }
            printf("\n");
        }
    }

    remove("sala5.txt");
    FILE *fp;
	fp=fopen("sala5.txt","a");
	if(fp == NULL)
	{
		printf("Nie znaleziono pliku docelowego");
	} else
        fprintf(fp,"\t \t Miejsca\n");
        fprintf(fp,"\t1 2 3 4 5 6 7 8 9 10\n");
		for (i = 0; i < WIERSZ; i++)
                {
                    fprintf(fp,"rzad %d: ", i + 1);
                    for (j = 0; j < KOLUMNA; j++)
                    fprintf(fp,"%d ", Miejsca5[i][j]);
                    fprintf(fp,"\n");
                }
        fclose(fp);
    printf("\n\n                    Nacisnij ENTER aby powrocic...");
}

 /*!
 emergency reading of reserved seats in the cinema
 \param int choice4
 */
void odczyt_z_pliku(int choice4)
{
    system("cls");
    logo();
    char ch;
    FILE *fp;
    const char *sala[7]={"\t\tNa ktorej sali chcesz sprawdzic rezerwacje: \n\n","\t\t[1] Sala nr 1\n","\t\t[2] Sala nr 2\n","\t\t[3] Sala nr 3\n","\t\t[4] Sala nr 4\n","\t\t[5] Sala nr 5\n","\t\t[0] Wyjdz\n\n"};
    for(int i=0; i<7; i++)
        printf("%s", sala[i]);
    printf("\t\tDokonaj wyboru: ");

    scanf("%d", &choice4);

    switch(choice4) {
    case 1 :
        system("cls");
        logo();
        fp = fopen("sala1.txt","r");
        if(fp==NULL) {
            printf(" Nie znaleziono pliku");
        } else {
            while((ch=fgetc(fp))!= EOF)
                printf("%c",ch);
        }
        printf("\n\n                    Nacisnij ENTER aby powrocic...");
        fclose(fp);
        break;
    case 2 :
        system("cls");
        logo();
        fp = fopen("sala2.txt","r");
        if(fp==NULL) {
            printf(" Nie znaleziono pliku");
        } else {
            while((ch=fgetc(fp))!= EOF)
                printf("%c",ch);
        }
        printf("\n\n                    Nacisnij ENTER aby powrocic...");
        fclose(fp);
    case 3 :
        system("cls");
        logo();
        fp = fopen("sala3.txt","r");
        if(fp==NULL) {
            printf(" Nie znaleziono pliku");
        } else {
            while((ch=fgetc(fp))!= EOF)
                printf("%c",ch);
        }
        printf("\n\n                    Nacisnij ENTER aby powrocic...");
        fclose(fp);
        break;
    case 4 :
        system("cls");
        logo();
        fp = fopen("sala4.txt","r");
        if(fp==NULL) {
            printf(" Nie znaleziono pliku");
        } else {
            while((ch=fgetc(fp))!= EOF)
                printf("%c",ch);
        }
        printf("\n\n                    Nacisnij ENTER aby powrocic...");
        fclose(fp);
        break;
    case 5 :
        system("cls");
        logo();
        fp = fopen("sala5.txt","r");
        if(fp==NULL) {
            printf(" Nie znaleziono pliku");
        } else {
            while((ch=fgetc(fp))!= EOF)
                printf("%c",ch);
        }
        printf("\n\n                    Nacisnij ENTER aby powrocic...");
        fclose(fp);
        break;
    case 0 :
        printf("\n\n                    Nacisnij ENTER aby powrocic...");
        return EXIT_SUCCESS;
        break;
    default:
        printf(" Nie ma takiej opcji w Menu  [WCISNIJ ENTER]");
    }
}

 /*!
 adds up the daily cinema revenue
 \param double n_ticket
 \param double hp_ticket
 */
double zarabiam(double n_ticket, double hp_ticket)
{
    daily_money += (n_ticket*NORMALTICKET+hp_ticket*HALFPRICETICKET);
    return daily_money;
}
