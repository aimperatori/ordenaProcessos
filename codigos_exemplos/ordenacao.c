#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

/*-----------------------------------------------*/
#define N 100000

/*-----------------------------------------------*/
void gera_vetor(int vet[N]){
	int i;
	srand(time(NULL));		
	for (i=0;i<N;i++){
		vet[i] = rand()%10;
	}
}
/*-----------------------------------------------*/
void ordena_vetor(int ini, int np, int vet[N], int ordenado[N]){
	int i, j, cont;

	for ( i=ini; i<N; i+=np ){
		cont = 0;
		for ( j=0; j<N; j++ ){
			if (  (vet[j] < vet[i]) ||  (vet[j] == vet[i] && i < j ) ){
				cont++;			
			}		
		}
		ordenado[cont] = vet[i];
	}

}

/*-----------------------------------------------*/
void escreve_vetor(int vet[N]){
	int i;
	for (i=0;i<N;i++){
		printf("%d ", vet[i]); 	
	}
	printf("\n");
}

/*-----------------------------------------------*/
int main(){
	int vet[N];
	int *ordenado;
	int shm;
	int chave = 5;
	int pid;

	gera_vetor(vet);
//	escreve_vetor(vet);
	
	shm = shmget(chave, N*sizeof(int), 0600 | IPC_CREAT);

	ordenado = (int *)shmat(shm, 0, 0);

	pid = fork();
	
	if (pid > 0){

		pid = fork();

		if ( pid > 0 ){
			pid = fork();
			
			if (pid > 0 ){
				ordena_vetor(0, 4, vet,ordenado);
				wait(NULL);
				wait(NULL);
				wait(NULL);
//				escreve_vetor(ordenado);
				shmdt(ordenado);
				shmctl(shm, IPC_RMID, 0);
			}
			else{
				ordena_vetor(1, 4, vet,ordenado);
				shmdt(ordenado);
			}
		}
		else{
			ordena_vetor(2, 4, vet,ordenado);
			shmdt(ordenado);
		}
	}
	else{
		ordena_vetor(3, 4, vet,ordenado);
		shmdt(ordenado);
	}
}
/*-----------------------------------------------*/
