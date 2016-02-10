#include <stdio.h>
#include <stdlib.h>

typedef struct TipoPonto {
    double x;
    double y;
} TipoPonto;

typedef struct Registro{
    TipoPonto * point;
    int numPontos;
    int maxPontos;
    TipoPonto eixo;
} Registro;

typedef struct No * ApontadorArvore;

typedef struct No {
    Registro Reg;
    ApontadorArvore Quad1, Quad2, Quad3, Quad4;
} No;

typedef ApontadorArvore TipoDicionario;

//Pega os argumentos da linha de comando
void PegaArgumentos(int, char **, char **, char **);

//Inicializa a árvore
void Inicializa(ApontadorArvore *);

//Insere um registro na árvore
void InsereArvore(Registro, ApontadorArvore *);

//Insere um ponto na quadtree
void InserePonto(TipoPonto, ApontadorArvore *, double, int, int);

//Conta o número de quadrantes da quadtree
void numQuadrantes(ApontadorArvore *, int *);

//Faz a consulta e imprime os pontos consultados no arquivo
void ImprimeConsultaRetangulo (TipoPonto * pontos, TipoPonto *, int, FILE *);

//As funções abaixo fazem parte do algoritmo de ordenação Quicksort()
void Particao(int, int, int *, int *, TipoPonto *);
void Ordena(int, int, TipoPonto *);
void QuickSort(TipoPonto *, int *);

//Le o arquivo executando as funções sobre a quadtree
void LeArquivo(char *, char *);
