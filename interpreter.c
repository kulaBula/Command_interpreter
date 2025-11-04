// Implementacja własnego interpretera za pomocą fork i execv. 
// Wczytujemy polecenia wraz z argumentami z konsoli i umieszczamy je w tablicy ciągów znakowych,
// robimy forka i wait'a, w procesie potomnym wykonujemy execv z zbudowaną wcześniej tablicą ciągów, wyświetlamy błędy jeśli się pojawią.
// Jeśli użytkownik wpisze 'exit' program kończy się  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_SIZE 100

int main(){
	//1. Wczytywanie
	char polecenie[MAX_SIZE];

	//Dynamiczna tablica charów do rzechowywania słów polecenia
	char *ptr, *instrukcja_do_execv;
	int counter=0, licznik=0; 

	printf("/>");
	fgets(polecenie, sizeof(polecenie), stdin);
	printf("%s", polecenie);
	printf("%d", polecenie[0]);
	// Dzielenie stringa na poszczególne człony i pakowanie ich do tablicy
	// Inicjujemy pointer do przechowania słowa
	ptr = malloc(sizeof(char)*10);
	// Inicjujemy tabele do przechowywania słów
	instrukcja_do_execv = malloc(sizeof(char)*3);
	for(int i=0; i<MAX_SIZE; i++){
		// Jeśli element jest spacją
		if(polecenie[i]==32){
			instrukcja_do_execv[licznik] = ptr;
			//Zerujemy ptr
			free(ptr);
			licznik++;
			// Jeśli jednak mamy więcej słow trzeba dodać miejsce na kolejne
			if(licznik>=(sizeof(instrukcja_do_execv)/sizeof(char))){
				instrukcja_do_execv = (instrukcja_do_execv, sizeof(char)*2);
			}
		}
		// Jeśli nie jest spacją przepisujemy dalej
		else{
			char c = polecenie[i];
			ptr[counter]=c; //dopisujemy literkę do słowa
			counter++;
			//Jeśli słowo jest dłuższe niż wstępne 10 to musimy alokować więcej pamięci
			if(counter>=sizeof(ptr)){
				ptr = realloc(ptr, sizeof(char)*2);
				
			}
		}
	}
	// Mamy już podzielone na słowa - można wpisać do execav
	if(fork()==0){
		// W procesie potomnym odpalamy execa
		execv(ptr[0], ptr); // Jeden problem, trzeba usunąć polecenie z listy argumentów chyba, co można by zrobić wprowadzając bit sprawdzający czy wpisano pierwsze słowo, które w domyśle jest poleceniem
	
	}
	//Oczekiwanie na sygnał z procesu potomnego signal() - to doczytać jak działa i zaimplementować, tak, żeby proces główny czekał na sygnał syschd
	return(0);
}
