#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
    #define INPUT "teste.csv"
#else
	#define INPUT "intergenidb.csv"
#endif
#define OUTPUT "saida.csv"
#define INCREMENTO 4
#ifdef DEBUG
	#define NUM_LINHAS 10
#else
	#define NUM_LINHAS 75252
#endif

typedef struct argumentos {
    char nomeOrganismo[100];
	char nomeGene[100];
	char tipoOrganismo[100];
	char familiaOrganismos[100];
	char papelBiologico[200];
    char posInicialGenoma[100];
    char posFinalGenoma[100];
    char *dna;
} ARGS;

typedef struct index {
    int fileIndex;
	char nomeGene[100];
	char nomeOrganismo[100];
} INDEX;

// set the current line into struct
int le_linha(FILE *file, ARGS *args){
    int isEOF;

    isEOF = fscanf(file, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n", 
                args->nomeOrganismo, args->nomeGene, args->tipoOrganismo, args->familiaOrganismos, 
                args->papelBiologico, args->posInicialGenoma, args->posFinalGenoma, args->dna);

    #ifdef DEBUG
        printf("%s %s %s %s %s %s %s --> TAM: %d <--\n", 
            args->nomeOrganismo, args->nomeGene, args->tipoOrganismo, args->familiaOrganismos, 
            args->papelBiologico, args->posInicialGenoma, args->posFinalGenoma, (int) strlen(args->dna));
    #endif
    
    return isEOF;
}

// write the struct in .csv formated into file
int escreve_linha(FILE *file, ARGS *args){
	return fprintf(file, "%s;%s;%s;%s;%s;%s;%s;%s\n", 
				args->nomeOrganismo, args->nomeGene, args->tipoOrganismo, args->familiaOrganismos, 
				args->papelBiologico, args->posInicialGenoma, args->posFinalGenoma, args->dna);
}

void escreve_linhas(FILE *in, FILE *out, INDEX index[NUM_LINHAS]){
    int i;
    ARGS args;    

    args.dna = malloc((int) sizeof(char) * 113500);

    for(i=0; i < NUM_LINHAS; i++){

        fseek(in, index[i].fileIndex, SEEK_SET);

        le_linha(in, &args);

        escreve_linha(out, &args);
    }
}

void ordena_vetor(int ini, int inc, INDEX vet[NUM_LINHAS], INDEX ordenado[NUM_LINHAS]){
	int i, j, cont;

	for (i = ini; i < NUM_LINHAS; i += inc){
		cont = 0;
		for (j=0; j < NUM_LINHAS; j++){            
            if((strcmp(vet[j].nomeGene, vet[i].nomeGene) < 0) || strcmp(vet[j].nomeGene, vet[i].nomeGene) == 0 && i< j) {
				cont++;			
			}
            #ifdef DEBUG
                printf("i[%d]: %s - j[%d]: %s -> count %d\n", i, vet[i].nomeGene, j, vet[j].nomeGene, cont);
            #endif
		}
		ordenado[cont] = vet[i];
	}
}

void index_arq(FILE *in, INDEX index[NUM_LINHAS]){
    int i;
    ARGS args;

    args.dna = malloc((long) sizeof(char) * 113500);

    for(i=0; i < NUM_LINHAS; i++){

        index[i].fileIndex = ftell(in);

        le_linha(in, &args);

        strcpy(index[i].nomeGene, args.nomeGene);
        strcpy(index[i].nomeOrganismo, args.nomeOrganismo);

        #ifdef DEBUG
            printf("%d %s %s\n", index[i].fileIndex, index[i].nomeGene, index[i].nomeOrganismo);
        #endif
    }
}

int main(void) {
    FILE *in = fopen(INPUT, "r");
    FILE *out = fopen(OUTPUT, "w");
    
    INDEX *index, *ordenado;

    index = malloc((long) sizeof(INDEX) * NUM_LINHAS);
    ordenado = malloc((long) sizeof(INDEX) * NUM_LINHAS);

    // cria indices do arquivo
    index_arq(in, index);

    // ordena pelos indices
    ordena_vetor(0, 1, index, ordenado);

    // escreve no arquivo ordenado
    escreve_linhas(in, out, ordenado);


    fclose(in);
    fclose(out);

    return 0;
}