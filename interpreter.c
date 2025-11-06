// Implementacja własnego interpretera za pomocą fork i execv. 
// Wczytujemy polecenia wraz z argumentami z konsoli i umieszczamy je w tablicy ciągów znakowych,
// robimy forka i wait'a, w procesie potomnym wykonujemy execv z zbudowaną wcześniej tablicą ciągów, wyświetlamy błędy jeśli się pojawią.
// Jeśli użytkownik wpisze 'exit' program kończy się  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_SIZE 1024

int main(){
	//1. Wczytywanie
	char polecenie_user[MAX_SIZE];

	char **lista_arg_do_execvp=NULL; //Pusta tablica do przechowywania argumentów
	int counter=0, stat;

	printf("/>");
	fgets(polecenie_user, sizeof(polecenie_user), stdin);
	// Usuwamy znak nowej lini \n
	polecenie_user[strlen(polecenie_user)-1] = 0;

	// Dzielimy stringa na części
	char *ptr = strtok(polecenie_user, " ");


	// Dzielenie stringa na poszczególne człony i pakowanie ich do tablicy
	while(ptr != NULL){
		lista_arg_do_execvp = realloc(lista_arg_do_execvp, sizeof(char*)*(counter+1)); //alokujemy pamięć dla nowego argumentu
		lista_arg_do_execvp[counter] = strdup(ptr); // kopiujemy słowo do listy argumentów
		counter++;
		ptr = strtok(NULL, " "); // "Przesuwamy się" do kolejnego argumentu
	}
	lista_arg_do_execvp = realloc(lista_arg_do_execvp, sizeof(char*)*(counter+1)); // Tworzymy miejsce na ostatni argument - NULL
	lista_arg_do_execvp[counter] = NULL; 

	for(int i=0; i<=counter; i++){
		printf("Arg %d: %s\n", i, lista_arg_do_execvp[i]);
	}

	// 2. Tworzymy proces potomny i uruchamiamy w nim execvp
	if(fork()==0){
		// W procesie potomnym odpalamy execa
		execvp(lista_arg_do_execvp[0], lista_arg_do_execvp); 
	}
	else{
		wait(&stat);
		//printf("Status=%d\n", WIFEXITED);
	}
	printf("Zrobione?\n");
	
	return(0);
}
