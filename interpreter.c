// Implementacja własnego interpretera za pomocą fork i execv. 
// Wczytujemy polecenia wraz z argumentami z konsoli i umieszczamy je w tablicy ciągów znakowych,
// robimy forka i wait'a, w procesie potomnym wykonujemy execv z zbudowaną wcześniej tablicą ciągów, wyświetlamy błędy jeśli się pojawią.
// Jeśli użytkownik wpisze 'exit' program kończy się  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE 100

int main(){
	//1. Wczytywanie
	char polecenie_user[MAX_SIZE];

	//Dynamiczna tablica charów do rzechowywania słów polecenia
	char *ptr, *komenda, **lista_arg_do_execvp;
	int counter=0, licznik=0, pierwsze_slowo=0;

	printf("/>");
	fgets(polecenie_user, sizeof(polecenie_user), stdin);
	printf("Wczytany tekst: %s", polecenie_user);
	for(int i=0; i<10; i++){
		
	}
	//printf("Spacja:%d1\n", polecenie_user[3]);
	// Dzielenie stringa na poszczególne człony i pakowanie ich do tablicy
	// Inicjujemy pointer do przechowania słowa
	ptr = malloc(sizeof(char)*10);
	komenda = malloc(sizeof(char)*4);
	// Inicjujemy tabele do przechowywania słów
	lista_arg_do_execvp = malloc(sizeof(char)*3);
	for(int i=0; i<10; i++){
		printf("Litera %d: %d Stan ptr: %s Komenda: %s\n", i, polecenie_user[i], ptr, komenda);
		// Koniec ciągu znaków
		if(polecenie_user[i]==10){
			printf("Koniec ciągu znaków, przerywam pętlę.\n");
			lista_arg_do_execvp[licznik]=malloc(sizeof(char)*4);
			strcpy(lista_arg_do_execvp[licznik], ptr);
			//free(ptr);
			break;
		}
		// Jeśli mamy pierwsze słowo
		if((polecenie_user[i]==32) && (pierwsze_slowo==0)){
			printf("Koniec pierwszego słowa!\n");
			pierwsze_slowo++;
			strcpy(komenda, ptr);
			printf("Komenda zaraz po zapisaniu: %s\n", komenda);
			free(ptr);
			ptr = malloc(sizeof(char)*10);
			counter=0;
		}
		// Jeśli element jest spacją (wyłapujemy słowa od drugiego wzwyż)
		if((polecenie_user[i]==32) && (pierwsze_slowo>0)){
			printf("Koniec kolejnego słowa\n");
			//Zapisujemy instrukcje do tablicy
			//lista_arg_do_execvp[licznik] = ptr;
			lista_arg_do_execvp[licznik]=malloc(sizeof(char)*4);
			printf("Tu>\n");
			strcpy(lista_arg_do_execvp[licznik], ptr);
			printf("Lista arg na el %d zaraz po zapisaniu: %s", licznik, lista_arg_do_execvp[licznik]);
			//Zerujemy ptr
			free(ptr);
			ptr = malloc(sizeof(char)*10);
			licznik++;
			counter=0;
			// Jeśli jednak mamy więcej słow trzeba dodać miejsce na kolejne
			if(licznik>=(sizeof(lista_arg_do_execvp)/sizeof(char))){
				lista_arg_do_execvp = realloc(lista_arg_do_execvp, sizeof(lista_arg_do_execvp) + sizeof(char)*2);
			}
		}
		
		// Jeśli nie jest spacją przepisujemy dalej
		else{
			char c = polecenie_user[i];
			ptr[counter]=c; //dopisujemy literkę do słowa
			counter++;
			//Jeśli słowo jest dłuższe niż wstępne 10 to musimy alokować więcej pamięci
			if(counter>=sizeof(ptr)){
				ptr = realloc(ptr, sizeof(ptr)+sizeof(char)*2);
			}
		}
	}
	// Mamy już podzielone na słowa - można wpisać do execav
	printf("Komenda: %s\n", komenda);
	printf("Arg 0: %s\n", lista_arg_do_execvp[0]);
	// if(fork()==0){
	// 	// W procesie potomnym odpalamy execa
	// 	execvp(komenda, ptr); 
	// }
	// else{
	// 	//Oczekiwanie na sygnał z procesu potomnego signal() - to doczytać jak działa i zaimplementować, tak, żeby proces główny czekał na sygnał syschd
	// }
	// printf("Zrobione?\n");
	
	return(0);
}
