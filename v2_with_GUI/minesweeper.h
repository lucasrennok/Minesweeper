#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

typedef struct pontoMatriz{
    bool mina;
    bool aberto;
    bool bandeira;
    int minas_ao_redor;
} pMatriz;

bool campoResolvido(pMatriz** matriz, int x, int y);
pMatriz** alocacao(int x, int y);
void gerarCampo(pMatriz** matriz, int x, int y, int bombas);
void printaCampo(pMatriz** matriz, int x, int y, int finalizado, float tempo, int bombas);
int bombasRestantesBandeira(pMatriz** matriz, int x, int y, int bombas);
int decisaoJogador(pMatriz** matriz, int x, int y, int bombas);
void limpaZerosArea(pMatriz** matriz, int x, int y, int linha, int coluna);
void desalocacao(pMatriz** matriz, int x);

pMatriz** alocacao(int x, int y){
    printf("\nAlocando matriz...\n");
    pMatriz** matriz = (pMatriz**)malloc(x*sizeof(pMatriz*));
    for(int i=0; i<x; i++){
        matriz[i] = (pMatriz*)malloc(y*sizeof(pMatriz));
    }
    printf("Alocado com sucesso.\n");
    return matriz;
}

void gerarCampo(pMatriz** matriz, int x, int y, int bombas){
    printf("\nGerando o campo...\n");
    srand(time(NULL));
    int linha, coluna;
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            matriz[i][j].mina = false;
            matriz[i][j].aberto = false;
            matriz[i][j].bandeira = false;
            matriz[i][j].minas_ao_redor = 0;
        }
    }
    while(bombas>0){
        linha = rand()%x; coluna = rand()%y;
        if(matriz[linha][coluna].mina==false){
            matriz[linha][coluna].mina = true;
            bombas--;
        }
    }

    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            if(matriz[i][j].mina==true){
                matriz[i][j].minas_ao_redor=1;
            }else{
                if(i-1>=0 && j-1>=0){
                    if(matriz[i-1][j-1].mina==true)
                        matriz[i][j].minas_ao_redor++;
                }
                if(i-1>=0){
                    if(matriz[i-1][j].mina==true)
                        matriz[i][j].minas_ao_redor++;
                }
                if(i-1>=0 && j+1<y){
                    if(matriz[i-1][j+1].mina==true)
                        matriz[i][j].minas_ao_redor++;
                }
                if(j+1<y){
                    if(matriz[i][j+1].mina==true)
                        matriz[i][j].minas_ao_redor++;
                }
                if(i+1<x && j+1<y){
                    if(matriz[i+1][j+1].mina==true)
                        matriz[i][j].minas_ao_redor++;
                }
                if(i+1<x){
                    if(matriz[i+1][j].mina==true)
                        matriz[i][j].minas_ao_redor++;
                }
                if(i+1<x && j-1>=0){
                    if(matriz[i+1][j-1].mina==true)
                        matriz[i][j].minas_ao_redor++;
                }
                if(j-1>=0){
                    if(matriz[i][j-1].mina==true)
                        matriz[i][j].minas_ao_redor++;
                }
            }
        }
    }

    printf("Campo gerado.\n");
}

void printaCampo(pMatriz** matriz, int x, int y, int finalizado, float tempo, int bombas){
    int bombas_restantes = bombasRestantesBandeira(matriz, x, y, bombas);
    printf("\nCAMPO MINADO - Bombas Restantes: %d - Tempo: %f segundos \n\n__", bombas_restantes, tempo);
    for(int j=0; j<y; j++){
        if(j<10)
            printf(" 0%d", j);
        else
            printf(" %d", j);
    }
    printf("\n");
    for(int i=0; i<x; i++){
        if(i<10)
            printf("0%d|", i);
        else
            printf("%d|", i);
        for(int j=0; j<y; j++){
            if(matriz[i][j].aberto==true || finalizado>0){
                if(matriz[i][j].mina==false)
                    if(matriz[i][j].minas_ao_redor!=-1)
                    printf(" %d ", matriz[i][j].minas_ao_redor);
                    else
                    printf(" 0 ");
                else
                    printf(" * ");
            }
            else if(matriz[i][j].bandeira==true){
                printf(" B ");
            }
            else
                printf(" # ");
        }
        printf("\n");
    }
    printf("\n");
}

int bombasRestantesBandeira(pMatriz** matriz, int x, int y, int bombas){
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            if(matriz[i][j].bandeira==true){
                bombas--;
            }
        }
    }
    return bombas;
}

int decisaoJogador(pMatriz** matriz, int x, int y, int bombas, int linha, int coluna, int escolha){
    printf("Coordenadas escolhidas: %dx%d\n", linha, coluna);
    if(linha>=0 && linha<x && coluna>=0 && coluna<y){
        printf("1-Liberar Espaco\n2-Marcar Bandeira\nESCOLHA: %d\n", escolha);
        if(escolha==2){
            if(bombasRestantesBandeira(matriz,x,y,bombas)==0){
                printf("\n!__!MAXIMO DE BANDEIRAS JA ATINGIDO!__!\n");
            }
            else if(matriz[linha][coluna].aberto==false && bombasRestantesBandeira(matriz,x,y,bombas)>0){
                if(matriz[linha][coluna].bandeira==false)
                    matriz[linha][coluna].bandeira=true;
                else
                    matriz[linha][coluna].bandeira=false;
            }
        }else{
            matriz[linha][coluna].aberto=true;
            if(matriz[linha][coluna].mina==true)
                return 2;
            else if(campoResolvido(matriz,x,y))
                return 1;
            matriz[linha][coluna].bandeira=false;
            if(matriz[linha][coluna].minas_ao_redor==0){
                limpaZerosArea(matriz,x,y,linha,coluna);
            }
        }
    }else{
        printf("\n!__!VALOR INVALIDO DE LINHA OU COLUNA!__!\n");
    }
    return 0;
}

void limpaZerosArea(pMatriz** matriz, int x, int y, int linha, int coluna){
    if(matriz[linha][coluna].minas_ao_redor==0){
        matriz[linha][coluna].minas_ao_redor=-1;
        matriz[linha][coluna].aberto=true;
        matriz[linha][coluna].bandeira=false;
        if(linha-1>=0){
            matriz[linha-1][coluna].aberto=true;
            if(matriz[linha-1][coluna].minas_ao_redor==0)
                limpaZerosArea(matriz,x,y,linha-1,coluna);
        }
        if(coluna+1<y){
            matriz[linha][coluna+1].aberto=true;
            if(matriz[linha][coluna+1].minas_ao_redor==0)
                limpaZerosArea(matriz,x,y,linha,coluna+1);
        }
        if(linha+1<x){
            matriz[linha+1][coluna].aberto=true;
            if(matriz[linha+1][coluna].minas_ao_redor==0)
                limpaZerosArea(matriz,x,y,linha+1,coluna);
        }
        if(coluna-1>=0){
            matriz[linha][coluna-1].aberto=true;
            if(matriz[linha][coluna-1].minas_ao_redor==0)
                limpaZerosArea(matriz,x,y,linha,coluna-1);
        }
    }
    return;
}

bool campoResolvido(pMatriz** matriz, int x, int y){
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            if(matriz[i][j].aberto==false && matriz[i][j].mina==false){
                return false;
            }
        }
    }
    return true;
}

void desalocacao(pMatriz** matriz, int x){
    printf("\nDesalocando matriz...\n");
    for(int i=0; i<x; i++){
        free(matriz[i]);
    }
    free(matriz);
    printf("Desalocado com sucesso.\n");
}

#endif // MINESWEEPER_H
