#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 40

typedef struct{
	char nome[25];
	float borsellino;
} player;

typedef struct{
	int valore;
	int seme;	//cuori quadri fiori picche
} carta;

void mix(carta mazzo[]){
	int i, cont[2] = {1, 1};
	carta temp;
	for(i=0;i<M;i++){
		mazzo[i].valore = cont[0];
		mazzo[i].seme = cont[1];
		if((i+1)%10==0){
			cont[0] = 0;
			cont[1]++;
		}
		cont[0]++;
	}
	for(i=0;i<M;i++){
		int index = rand()%39+1;
		temp = mazzo[i];
		mazzo[i] = mazzo[index];
		mazzo[index] = temp;
	}
}

int open(char nome[25], FILE** f, char mode[]){
	*f = fopen(nome, mode);
	if(f == NULL)
		return 0;
	else
		return 1;
}

int set_ngiocatori(){
	int n;
	do{
		printf("\nDigita quanti giocatori giocheranno [MAX 5]: ");
		scanf("%d", &n);
	}while(n>5 || n<0);
	return n;
}

int elimina(char nome[], player database[], int* dim){
	int p, i;
	p = ricerca(nome, database, *dim);
	if(p == -1)
		return -1;
	for(i=p;i<*dim-1;i++){
		database[i] = database[i+1];
	}
	(*dim)--;
	return 1;
}

int ricerca(char nome[], player db[], int d){
	int i;
	for(i=0;i<d;i++){
		if(strcmp(db[i].nome, nome) == 0)
			return i;
	}
	return -1;
}

int query_db(FILE **db, player database[], int *dim, char mode){
	player buffer;
	int i;
	
	if(mode == 'r'){
		if(!open("giocatori.dat", db, "rb")){
			printf("\nDatabase non trovato");
			return 0;
		}
		
		while(!feof(*db)){
			fread(&buffer, sizeof(player), 1, *db);
			if(!feof(*db)){
				database[*dim] = buffer;
				*dim += 1;
			}
			
		}
		fclose(*db);
		return 1;
	}else if(mode == 'w'){
		if(!open("giocatori.dat", db, "wb")){
			printf("\nDatabase non trovato");
			return 0;
		}
		for(i=0;i<*dim;i++){
			fwrite(&database[i], sizeof(database[i]), 1, *db);
		}
		fclose(*db);
		return 1;
	}
	

	
}

int get_db(player database[], int dim){
	int i, s;
	for(i=0;i<dim;i++){
		printf("\n-%d\tNOME: %s\tBORSELLINO: %f", i+1, database[i].nome, database[i].borsellino);
	}
	printf("\nDigita il numero del giocatore con cui desideri giocare: ");
	scanf("%d", &s);
	return s-1;
}

void set_giocatori(int n, player giocatori[], player database[], int dim){
	int i, cont=0, pos=0;
	char buffer[25];
	float b;
	for(i=0;i<n;i++){
		printf("\nDigita il nome del giocatore o altrimenti digita 1 per visualizzare i giocatori nel database\n=> ");
		scanf("%s", buffer);
		if(buffer[0] == '1'){
			if(dim == 0){
				printf("\nDatabase vuoto, digita il nome del giocatore: ");
				scanf("%s", buffer);
				strcpy(giocatori[cont].nome, buffer);
				printf("\nDigita la cifra del borsellino: ");
				scanf("%f", &b);
				giocatori[cont].borsellino = b;
				cont++;
			}else{
				pos = get_db(database, dim);
				giocatori[cont] = database[pos];
				cont++;
			}
		}else{
			strcpy(giocatori[cont].nome, buffer);
			printf("\nDigita la cifra del borsellino: ");
			scanf("%f", &b);
			giocatori[cont].borsellino = b;
			cont++;
		}
	}
}

void update_db(player giocatori[], int dim, player database[], int* dim_db){
	int i, j, flag=0;
	for(i=0;i<dim;i++){
		for(j=0;j<*dim_db;j++){
			if(strcmp(giocatori[i].nome, database[j].nome) == 0){
				database[j].borsellino = giocatori[i].borsellino;
				flag = 1;
			}
		}
		if(flag==0){
			database[*dim_db] = giocatori[i];
			(*dim_db)++;
		}
		flag = 0;
	}
}

void stampaCarta(carta carta){
	switch(carta.seme){
		case 1:
			switch(carta.valore){
				case 1:
					printf("\nASSO DI %c", 3);
					break;
				case 8:
					printf("\nDONNA DI %c", 3);
					break;
				case 9:
					printf("\nFANTE DI %c", 3);
					break;
				case 10:
					printf("\nRE DI %c", 3);
					break;
				default:
					printf("\n %d di %c", carta.valore, 3);
			}
			break;
		case 2:
			switch(carta.valore){
				case 1:
					printf("\nASSO DI %c", 4);
					break;
				case 8:
					printf("\nDONNA DI %c", 4);
					break;
				case 9:
					printf("\nFANTE DI %c", 4);
					break;
				case 10:
					printf("\nRE DI %c", 4);
					break;
				default:
					printf("\n %d di %c", carta.valore, 4);
			}
			break;
		case 3:
			switch(carta.valore){
				case 1:
					printf("\nASSO DI %c", 5);
					break;
				case 8:
					printf("\nDONNA DI %c", 5);
					break;
				case 9:
					printf("\nFANTE DI %c", 5);
					break;
				case 10:
					printf("\nRE DI %c", 5);
					break;
				default:
					printf("\n %d di %c", carta.valore, 5);
			}
			break;
		case 4:
			switch(carta.valore){
				case 1:
					printf("\nASSO DI %c", 6);
					break;
				case 8:
					printf("\nDONNA DI %c", 6);
					break;
				case 9:
					printf("\nFANTE DI %c", 6);
					break;
				case 10:
					printf("\nRE DI %c", 6);
					break;
				default:
					printf("\n %d di %c", carta.valore, 6);
			}
			break;
			
	}
}

float valore(carta carta){
	float v;
	if(carta.valore > 7)
		v = 0.5;
	else
		v = carta.valore;
	return v;
}

void gioco(player *giocatore, carta mazzo[]){
	printf("\nGIOCATORE: %s", giocatore->nome);
	//3 4 5 6 cuori quadri fiori picche
	carta primaC;
	carta temp;
	float sommaC = 0;
	float sommaG = 0;
	char ch;
	int stop = 0;
	float puntata = 0;
	float val;
	
	do{
		printf("\nInserisci il valore della tua puntata (minore del totale del borsellino => %f ): ", giocatore->borsellino);
		fflush(stdin);
		scanf("%f", &puntata);
	}while(puntata > giocatore->borsellino && puntata > 0);
	giocatore->borsellino -= puntata;
	
	
	srand(time(NULL));
	
	printf("\nIl mazziere pesca la prima carta");
	primaC = mazzo[rand()%40];
	sommaC += valore(primaC);
	
	do{
		if(stop != 1){
			printf("\nLa tua carta:\t");
			temp = mazzo[rand()%40];
			stampaCarta(temp);
			if(temp.valore == 10  && temp.seme == 2){
				printf("\nHai pescato la matta scegli il valore da assegnargli => ");
				fflush(stdin);
				scanf("%f", &val);
				sommaG += val;
			}
			else{
				sommaG += valore(temp);
			}
			printf("\nPunteggio totale: %f", sommaG);
			printf("\npremi s per stare o r per richiedere un'altra carta => ");
			fflush(stdin);
			scanf("%c", &ch);
			if(ch == 's')
				stop = 1;	
		}
	}while(stop == 0);
	
	temp = mazzo[rand()%40];
	sommaC += valore(temp);
	printf("\nPrima carta del mazziere:\t");
	stampaCarta(primaC);
	printf("\nSeconda carta del mazziere:\t");
	stampaCarta(temp);
	printf("\nPunteggio totale mazziere: %f", sommaC);
	printf("\nIl tuo punteggio totale : %f\n\n" , sommaG);
	
	//FIX
	
	if(sommaC > 7.5 && sommaG < 7.5){
		printf("Il mazziere ha sballato, hai vinto!");
		giocatore->borsellino += (puntata)*2;
		printf("\nValore borsellino %f", giocatore->borsellino);
		return;
	}else if(sommaG > 7.5 && sommaC != 7.5 && sommaG != 7.5){
		printf("Hai sballato, hai perso la tua puntata!");
		printf("\nValore borsellino %f", giocatore->borsellino);
		return;
	}
	
	if(sommaG == sommaC && sommaG < 7.5){
		printf("\nPareggio!");
		giocatore->borsellino += puntata;
		printf("\nValore borsellino %f", giocatore->borsellino);
		return;
	}
	
	if(sommaG < 7.5 && sommaC < 7.5 && sommaG > sommaC && sommaG != 7.5){
		printf("\nHai vinto!");
		giocatore->borsellino += (puntata)*2;
		printf("\nValore borsellino %f", giocatore->borsellino);
		return;
	}else if(sommaG < 7.5 && sommaC < 7.5 && sommaC > sommaG && sommaG != 7.5){
		printf("\nGame Over, hai perso la tua puntata!");
		printf("\nValore borsellino %f", giocatore->borsellino);
		return;
	}
	
	if(sommaG == 7.5){
		printf("\nSette 1/2 reale!");
		giocatore->borsellino += (puntata)*4;
		printf("\nValore borsellino %f", giocatore->borsellino);
		return;
	}else if(sommaC == 7.5){
		printf("\nGame Over il mazziere ha fatto 7 1/2 reale, perdi il doppio della puntata");
		giocatore->borsellino -= puntata;
		printf("\nValore borsellino %f", giocatore->borsellino);
		return;
	}
	

	
	
}


void main(){
	FILE *db;
	carta mazzo[M];
	
	int dim_db = 0;
	player giocatori[5], database[10];
	
	printf("\n\t7 1/2");
	query_db(&db, database, &dim_db, 'r');
	
	int n = set_ngiocatori();
	
	set_giocatori(n, giocatori, database, dim_db);
	
	int i;
	for(i=0;i<n;i++){
		printf("\nGIOCATORE: %s BORSELLINO: %f", giocatori[i].nome, giocatori[i].borsellino);
	}
	
	///////////// GIOCO
	int num = n;
	
	for(i=0;i<num;i++){
		char c;
	
		do{
			mix(mazzo);
			gioco(&giocatori[i], mazzo);
			update_db(giocatori, n, database, &dim_db);
			query_db(&db, database, &dim_db, 'w');
			if(giocatori[i].borsellino <= 0){
				printf("\nHai perso tutto!");
				elimina(giocatori[i].nome, giocatori, &n);
				elimina(giocatori[i].nome, database, &dim_db);
				update_db(giocatori, n, database, &dim_db);
				query_db(&db, database, &dim_db, 'w');
				c = 'x';
			}else{
				printf("\n\nPremi x per smettere di giocare => ");
				fflush(stdin);
				scanf("%c", &c);
				system("cls");
			}
		}while(c != 'x');
	}
	
	///////////// GIOCO
	
}
