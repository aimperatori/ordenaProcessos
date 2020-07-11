## Autores ##

* Anderson Imperatori
* Leonardo Bertele Tosin

## Definição ##

Universidade de Caxias do Sul
Área do Conhecimento de Ciências Exatas e Engenharias
FBX4052 - Fundamentos de Sistemas Operacionais
Prof. André Luis Martinotto
Prof. Daniel Luis Notari

Trabalho de Implementação

Descrição do Projeto

O arquivo de dados intergenic.csv contém os dados de uma aplicação de genoma de bactérias. As informações do arquivo estão separadas por “;”. As informações contêm o nome do organismo, nome do gene, tipo do organismo, família do organismo, papel biológico, posição inicial no genoma, posição final no genoma e a sequência de DNA. Este arquivo contém dados repetidos para as cinco primeiras informações.
Objetivo

O software a ser desenvolvido envolve o problema de programação concorrente de sistemas operacionais usando threads ou processos. As linguagens de programação C, C#, Java e Python podem ser usadas para desenvolver este trabalho.

Implementar as seguintes operações

Leitura do Arquivo: Deve-se ler o arquivo para a memória, mas o arquivo não pode estar todo na memória ao mesmo tempo.
Ordenação do Arquivo: Deve-se ordenar este conjunto de dados pelo gene em ordem crescente e, dentro do conjunto do mesmo gene, ordenar pelo nome do organismo. Utilize mais de um processo ou thread para ordenar partes diferentes do arquivo e, depois para juntar o resultado.
Gravar o Arquivo: Deve-se gravar o conjunto de dados ordenado em um nome arquivo com as informações separadas por “;”.
Sugestão: cada thread deverá ler uma parte do arquivo não interferindo na parte das outras threads. Após, a leitura cada thread poderá ordenar a sua parte do arquivo. Por fim, a thread principal poderá fazer um merge das partes e gravar no arquivo de saída.

Grupos: O trabalho deve ser realizado em grupos de até três alunos.

Entregar:

código fonte
instruções para a execução do código fonte
vídeo contendo o detalhamento da implementação, exemplificação da execução, mostrar o arquivo original e o arquivo gerado.

## Nota ##

O nome do programa(o não sequencial) e o nome do projeto é ordenaThreads, mas foi usado processos, e não threads

## Instruções para executar ##

```bash
gcc -o ordenaThreads ordenaThreads.c
```
