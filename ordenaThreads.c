#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_ARQUIVO "teste.csv"
#ifdef DEGUB
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

// set the pointer of file to a specific line
void setPosFile(FILE *file, int pos) {
	// always points to beginning
	file = fseek(file, 0, SEEK_SET);

	while (pos--) 
		fscanf(file, "%*[^\n]\n");
}

// set the current line into struct
int le_linha(FILE *file, ARGS *args){
    int isEOF;
    //ARGS args;

    //args->dna = malloc((int) sizeof(char) * 113500);

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
	return fprintf("%s;%s;%s;%s;%s;%s;%s;%s;", 
				args->nomeOrganismo, args->nomeGene, args->tipoOrganismo, args->familiaOrganismos, 
				args->papelBiologico, args->posInicialGenoma, args->posFinalGenoma, args->dna);
}

void qs_disk(FILE *file, int left, int right) {
    long int i, j;
    char x[100];
    
    i = left; j = right;
    
    strcpy(x, get_gene(file, (long)(i+j)/2)); /* obtém o GENE intermediário */
    
    do {
        while (strcmp(get_gene(file, i), x) < 0 && i < right) i++;
		
        while (strcmp(get_gene(file, j), x) > 0 && j > left) j--;
        
        if (i <= j) {
            swap_all_fields(file, i, j);
            i++; j--;
        }
    } while(i <= j);
    
    if (left < j) qs_disk(file, left, (int) j);
    if (i < right) qs_disk(file, (int) i, right);
}

void swap_all_fields(FILE *file, long i, long j) {
    ARGS a, b;
    
    /* primeiro lê os registros i e j */
	setPosFile(file, i);
	le_linha(file, &a);

    //fseek(file, sizeof(ainfo) * i, SEEK_SET);
    //fread(a, sizeof(ainfo), 1, file);
    
	setPosFile(file, j);
	le_linha(file, &b);

    //fseek(file, sizeof(ainfo) * j, SEEK_SET);
    //fread(b, sizeof(ainfo), 1, file);
    
    /* em seguida escreve de volta em posições diferentes */
	setPosFile(file, i);
	escreve_linha(file, &a);

	setPosFile(file, j);
	escreve_linha(file, &b);

    //fseek(file, sizeof(ainfo) * j, SEEK_SET);
    //fwrite(a, sizeof(ainfo), 1, file);
    
    //fseek(file, sizeof(ainfo) * i, SEEK_SET);
    //fwrite(b, sizeof(ainfo), 1, file);
}

char *get_gene(FILE *file, long row) {
    ARGS args;
    
    setPosFile(file, row);
	le_linha(file, &args);
    
    return args.nomeGene;
}

int main(void) {
    FILE *file = fopen(NOME_ARQUIVO, "r");

    ARGS args;

    args.dna = malloc((int) sizeof(char) * 113500);


	le_linha(file, &args);

	setPosFile(file, 4);

	// fseek(file, sizeof(ARGS), SEEK_SET);

	le_linha(file, &args);


	/*
    while(le_linha(file, &args) != EOF){

        printf("%s %s %s %s %s %s %s --> TAM: %d <--\n", 
            args.nomeOrganismo, args.nomeGene, args.tipoOrganismo, args.familiaOrganismos, 
            args.papelBiologico, args.posInicialGenoma, args.posFinalGenoma, (int) strlen(args.dna));
        
    }
	*/


    fclose(file);

    return 0;
}