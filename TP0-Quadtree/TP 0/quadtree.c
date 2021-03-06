#include "quadtree.h"
#include <unistd.h> //GETOPT()
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void PegaArgumentos(int argc, char **argv, char ** entrada, char ** saida){
    const char *vetorOpcoes = "i:o:O:I:";
    char opcoes;
    while ((opcoes = getopt(argc, argv, vetorOpcoes)) != EOF){
        switch (opcoes){
        case 'i':
            *entrada = optarg;
            break;
        case 'I':
            *entrada = optarg;
            break;
        case 'o':
            *saida = optarg;
            break;
        case 'O':
            *saida = optarg;
            break;
        default:
            break;
        }
    }

}

void Inicializa(ApontadorArvore *Dicionario){
    *Dicionario = NULL;
}

void InsereArvore(Registro x, ApontadorArvore *p){
    //Cria um novo quadrante
    if (*p == NULL) {//Se NULL, cria o n� e os quadrantes NULL
        *p = (ApontadorArvore) malloc (sizeof(No));
        (*p)->Reg = x;
        (*p)->Quad1 = NULL;
        (*p)->Quad2 = NULL;
        (*p)->Quad3 = NULL;
        (*p)->Quad4 = NULL;
    }
}

void InserePonto(TipoPonto ponto, ApontadorArvore *p, double h, int limiteX, int limiteY){
    if((*p)->Quad1 == NULL){
        if((*p)->Reg.maxPontos == (*p)->Reg.numPontos){ //Se a Lista estiver cheia
            int i=0, maxPontos;
            Registro regs[4];

            //Cria os quatro quadrantes com suas respecitvas informa��es
            for(i=0;i<4;i++){
                regs[i].numPontos=0;
                maxPontos=(*p)->Reg.maxPontos;
                regs[i].maxPontos=(*p)->Reg.maxPontos;
                regs[i].point = (TipoPonto *)malloc(maxPontos * sizeof(TipoPonto));

                if(i==0){//1� Quadrante
                    regs[i].eixo.x=(*p)->Reg.eixo.x + limiteX/pow(2.0, h);
                    regs[i].eixo.y=(*p)->Reg.eixo.y + limiteY/pow(2.0, h);
                    InsereArvore(regs[i], &(*p)->Quad1);
                }
                if(i==1){//2� Quadrante
                    regs[i].eixo.x=(*p)->Reg.eixo.x - limiteX/pow(2.0, h);
                    regs[i].eixo.y=(*p)->Reg.eixo.y + limiteY/pow(2.0, h);
                    InsereArvore(regs[i], &(*p)->Quad2);
                }
                if(i==2){//3� Quadrante
                    regs[i].eixo.x=(*p)->Reg.eixo.x - limiteX/pow(2.0, h);
                    regs[i].eixo.y=(*p)->Reg.eixo.y - limiteY/pow(2.0, h);
                    InsereArvore(regs[i], &(*p)->Quad3);
                }
                if(i==3){//4� Quadrante
                    regs[i].eixo.x=(*p)->Reg.eixo.x + limiteX/pow(2.0, h);
                    regs[i].eixo.y=(*p)->Reg.eixo.y - limiteY/pow(2.0, h);
                    InsereArvore(regs[i], &(*p)->Quad4);
                }
            }

            //Redireciona pontos do quadrante cheio para os quadrantes certos
            for(i=0;i<(*p)->Reg.maxPontos;i++){
                if (((*p)->Reg.point[i].x >= (*p)->Reg.eixo.x) && (((*p)->Reg.point[i].y >= (*p)->Reg.eixo.y)))
                    InserePonto((*p)->Reg.point[i], &(*p)->Quad1, h, limiteX, limiteY);
                if (((*p)->Reg.point[i].x < (*p)->Reg.eixo.x) && (((*p)->Reg.point[i].y >= (*p)->Reg.eixo.y)))
                    InserePonto((*p)->Reg.point[i], &(*p)->Quad2, h, limiteX, limiteY);
                if (((*p)->Reg.point[i].x < (*p)->Reg.eixo.x) && (((*p)->Reg.point[i].y < (*p)->Reg.eixo.y)))
                    InserePonto((*p)->Reg.point[i], &(*p)->Quad3, h, limiteX, limiteY);
                if (((*p)->Reg.point[i].x >= (*p)->Reg.eixo.x) && (((*p)->Reg.point[i].y < (*p)->Reg.eixo.y)))
                    InserePonto((*p)->Reg.point[i], &(*p)->Quad4, h, limiteX, limiteY);
            }

            //Insere o ponto que est� "na m�o".
            //1� Quadrante
            if ((ponto.x >= (*p)->Reg.eixo.x) && ((ponto.y >= (*p)->Reg.eixo.y)))
                InserePonto(ponto, &(*p)->Quad1, h+1, limiteX, limiteY);
            //2� Quadrante
            if ((ponto.x < (*p)->Reg.eixo.x) && ((ponto.y >= (*p)->Reg.eixo.y)))
                InserePonto(ponto, &(*p)->Quad2, h+1, limiteX, limiteY);
            //3� Quadrante
            if ((ponto.x < (*p)->Reg.eixo.x) && ((ponto.y < (*p)->Reg.eixo.y)))
                InserePonto(ponto, &(*p)->Quad3, h+1, limiteX, limiteY);
            //4� Quadrante
            if ((ponto.x >= (*p)->Reg.eixo.x) && ((ponto.y < (*p)->Reg.eixo.y)))
                InserePonto(ponto, &(*p)->Quad4, h+1, limiteX, limiteY);
        } else {//Se a lista n�o estiver cheia
            (*p)->Reg.point[(*p)->Reg.numPontos]=ponto;//Lista de pontos recebe o ponto
            (*p)->Reg.numPontos++;
        }
    }

    //Caminhando na �rvore
    //1� Quadrante
    else if ((ponto.x >= (*p)->Reg.eixo.x) && ((ponto.y >= (*p)->Reg.eixo.y)))
        InserePonto(ponto, &(*p)->Quad1, h+1, limiteX, limiteY);
    //2� Quadrante
    else if ((ponto.x < (*p)->Reg.eixo.x) && ((ponto.y >= (*p)->Reg.eixo.y)))
        InserePonto(ponto, &(*p)->Quad2, h+1, limiteX, limiteY);
    //3� Quadrante
    else if ((ponto.x < (*p)->Reg.eixo.x) && ((ponto.y < (*p)->Reg.eixo.y)))
        InserePonto(ponto, &(*p)->Quad3, h+1, limiteX, limiteY);
    //4� Quadrante
    else if ((ponto.x >= (*p)->Reg.eixo.x) && ((ponto.y < (*p)->Reg.eixo.y)))
        InserePonto(ponto, &(*p)->Quad4, h+1, limiteX, limiteY);
}

void numQuadrantes(ApontadorArvore *p, int * quadrantes){
    if((*p)->Quad1 != NULL){
        numQuadrantes(&(*p)->Quad1, quadrantes);
        numQuadrantes(&(*p)->Quad2, quadrantes);
        numQuadrantes(&(*p)->Quad3, quadrantes);
        numQuadrantes(&(*p)->Quad4, quadrantes);
    } else {
        TipoPonto * desaloca;
        desaloca = (*p)->Reg.point;
        (*p)->Reg.point=NULL;
        (*quadrantes)++;
        free(desaloca);
        free(*p);//Desaloca o quadrante folha que est� sendo pesquisado
        desaloca=NULL;
        p=NULL;
    }
}

void ImprimeConsultaRetangulo (TipoPonto * pontos, TipoPonto retanguloConsulta[2], int numPontos, FILE * fpSaida){
    int i, flag=0;

    for(i=0;i<numPontos;i++){
        if((pontos[i].x >= retanguloConsulta[0].x) && (pontos[i].x <= retanguloConsulta[1].x)){ //SE X do ponto > ou = e < ou = X da Consulta
            if((pontos[i].y >= retanguloConsulta[0].y) && (pontos[i].y <= retanguloConsulta[1].y)){//SE Y do ponto > ou = e < ou = Y da Consulta
                if(flag==0)
                    fprintf(fpSaida, "%.1lf %.1lf", pontos[i].x, pontos[i].y);//IMPRIME O PONTO EM QUEST�O NO  ARQUIVO
                else
                    fprintf(fpSaida, ", %.1lf %.1lf", pontos[i].x, pontos[i].y);//IMPRIME O PONTO EM QUEST�O NO  ARQUIVO
                flag++;
            }
        }
    }
    fprintf(fpSaida, "\n");
}

void Particao(int Esq, int Dir, int *i, int *j, TipoPonto * pontos){
    TipoPonto x,w;
    *i = Esq; *j = Dir;

    x.x = pontos[(*i + *j)/2].x;
    x.y = pontos[(*i + *j)/2].y;

    do{
        while (x.x >= pontos[*i].x){
            if(x.x == pontos[*i].x){
                 if(x.y > pontos[*i].y){
                     (*i)++;
                 } else
                        break;
            } else {
                (*i)++;
            }
        }

        while (x.x <= pontos[*j].x){
            if(x.x == pontos[*j].x){
                 if(x.y < pontos[*j].y){
                     (*j)--;
                 } else
                        break;
            } else {
                (*j)--;
            }
        }

        if (*i <= *j){
            w.x = pontos[*i].x;
            w.y = pontos[*i].y;
            pontos[*i].x = pontos[*j].x;
            pontos[*i].y = pontos[*j].y;
            pontos[*j].x = w.x;
            pontos[*j].y = w.y;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Ordena(int Esq, int Dir, TipoPonto * pontos){
    int i, j;
    Particao(Esq, Dir, &i, &j, pontos);
    if (Esq < j) Ordena(Esq, j, pontos);
    if (i < Dir) Ordena(i, Dir, pontos);
}

void QuickSort(TipoPonto * pontos, int *n){
    Ordena(0, *n, pontos);
}

void LeArquivo(char * entrada, char * saida){
    FILE *fpEntrada, *fpSaida;
    int numInstancias, limiteX, limiteY, maxPtsQuadrante, numPontos, numConsultas, quadrantes=0, i, j;
    double altura;
    TipoPonto retanguloConsulta[2], ponto, * pontos;
    ApontadorArvore apontadorArvore;
    Registro quadrante;

    fpEntrada=fopen(entrada, "r");
    fpSaida=fopen(saida, "w");
    fscanf(fpEntrada, "%d", &numInstancias);

    for(i=0;i<numInstancias;i++){
        fscanf(fpEntrada, "%d %d", &limiteX, &limiteY);
        fscanf(fpEntrada, "%d", &maxPtsQuadrante);
        fscanf(fpEntrada, "%d", &numPontos);

        //Coloca informa��es do primeiro quadrante
        quadrante.numPontos=0;
        quadrante.maxPontos=maxPtsQuadrante;
        quadrante.eixo.x=limiteX/2;
        quadrante.eixo.y=limiteY/2;

        Inicializa(&apontadorArvore);
        InsereArvore(quadrante, &apontadorArvore); //Coloca o primeiro quadrante na �rvore
        pontos = (TipoPonto *)malloc(numPontos*sizeof(TipoPonto));//Aloca espa�o para lista de pontos

        for(j=0;j<numPontos;j++){
            altura=2;
            fscanf(fpEntrada, "%lf %lf", &ponto.x, &ponto.y);//L� X e Y;
            InserePonto(ponto, &apontadorArvore, altura, limiteX, limiteY);
            pontos[j].x=ponto.x;
            pontos[j].y=ponto.y;
        }

        numQuadrantes(&apontadorArvore, &quadrantes);
        numPontos--;//Decrementa para passar coluna final da matriz correta para QuickSort()
        QuickSort(pontos, &numPontos);
        numPontos++;//numPontos correto novamente;
        fprintf(fpSaida, "%d\n", quadrantes);
        fscanf(fpEntrada, "%d", &numConsultas);
        for(j=0;j<numConsultas;j++){
            fscanf(fpEntrada, "%lf %lf %lf %lf", &retanguloConsulta[0].x, &retanguloConsulta[0].y, &retanguloConsulta[1].x, &retanguloConsulta[1].y);
            if(retanguloConsulta[0].x>retanguloConsulta[1].x){//Troca ponto x menor com maior caso esteja errado
                ponto.x=retanguloConsulta[1].x;
                retanguloConsulta[1].x=retanguloConsulta[0].x;
                retanguloConsulta[0].x=ponto.x;
            }
            if(retanguloConsulta[0].y>retanguloConsulta[1].y){//Troca ponto x menor com maior caso esteja errado
                ponto.y=retanguloConsulta[1].y;
                retanguloConsulta[1].y=retanguloConsulta[0].y;
                retanguloConsulta[0].y=ponto.y;
            }
            ImprimeConsultaRetangulo(pontos, retanguloConsulta, numPontos, fpSaida);
        }
        free(pontos);//Desaloca a lista de pontos
    }
    fclose(fpEntrada);
    fclose(fpSaida);
}

void GeradorDePontos(char * entrada, int numInstancias, int limiteX, int limiteY, int maxPtsQuadrante, int numPontos, int numConsulta){
    FILE *fpEntrada;
    int i;
    double ponto[2];

    fpEntrada=fopen(entrada, "w");
    fprintf(fpEntrada, "%d\n", numInstancias);
    fprintf(fpEntrada, "%d %d\n", limiteX, limiteY);
    fprintf(fpEntrada, "%d\n", maxPtsQuadrante);
    fprintf(fpEntrada, "%d\n", numPontos);

    for(i=0;i<numPontos;i++){
        ponto[0] = rand()%(limiteX+1);
        ponto[1] = rand()%(limiteY+1);
        fprintf(fpEntrada, "%lf %lf\n", ponto[0], ponto[1]);
    }

    fprintf(fpEntrada, "%d\n", numConsulta);

    for(i=0;i<numConsulta;i++){
        ponto[0] = rand()%(limiteX+1);
        ponto[1] = rand()%(limiteY+1);
        fprintf(fpEntrada, "%lf %lf ", ponto[0], ponto[1]);
        ponto[0] = rand()%(limiteX+1);
        ponto[1] = rand()%(limiteY+1);
        fprintf(fpEntrada, "%lf %lf\n", ponto[0], ponto[1]);
    }
    fclose(fpEntrada);
}

