#include "quadtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    char *entrada=NULL, *saida=NULL;
    PegaArgumentos(argc, argv, &entrada, &saida); //L� argumentos passados por linha de comando.
    LeArquivo(entrada, saida);
    //GeradorDePontos(saida, 1, 100000, 100000, 4, 200000, 10);//Inst�ncias, limiteX, limiteY, maxPtsQuadrante, pontos, consultas;
    return 0;
}
