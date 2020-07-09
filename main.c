#include "minesweeper.h"

int main(){
	int x, y, bombas, derrotas=0, vitorias=0, acabou=0;
	float t1, t2, tempo_total=0;
	bool continuar = true;

	while(continuar){

		configuracao(&x, &y, &bombas);
		printf("Campo %dx%d (Minas: %d)\n", x,y,bombas);

		pMatriz** matriz = alocacao(x, y);
		gerarCampo(matriz,x,y,bombas);
		
		t1 = (float)clock()/(float)CLOCKS_PER_SEC;
		while(acabou==0){
			t2 = (float)clock()/(float)CLOCKS_PER_SEC;
			printaCampo(matriz,x,y,acabou,t2-t1,bombas);
			acabou = decisaoJogador(matriz,x,y,bombas);
			if(acabou==1){
				printaCampo(matriz,x,y,acabou,t2-t1,bombas);
				printf("!!!VITORIA!!!\n\n");
				vitorias++;
			}
			else if(acabou==2){
				printaCampo(matriz,x,y,acabou,t2-t1,bombas);
				printf("Infelizmente, voce perdeu, tente novamente.\n\n");
				derrotas++;
			}
		}
		tempo_total+=t2-t1;	acabou = 0;
		printf("** Placar **\n Vitorias %d/%d Derrotas \n Tempo Jogando: %f segundos\n\n", vitorias, derrotas, tempo_total);
		desalocacao(matriz, x);
		
		printf("\n--> Deseja continuar jogando?\n0-Nao\n1-Sim\n");
		scanf("%d", &continuar);
	}

	return 0;
}
