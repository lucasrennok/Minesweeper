#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>
#include <stdbool.h>
#include <math.h>
//
typedef struct pontoMatriz{
	bool mina;
	bool aberto;
	bool bandeira;
	int minas_ao_redor;
} pMatriz;

void configuracao(int* x, int* y, int* bombas);
pMatriz** alocacao(int x, int y);
void gerarCampo(pMatriz** matriz, int x, int y, int bombas);
void printaCampo(pMatriz** matriz, int x, int y, int finalizado, float tempo, int bombas);
int decisaoJogador(pMatriz** matriz, int x, int y, int bombas);
bool campoResolvido(pMatriz** matriz, int x, int y);
int bombasRestantesBandeira(pMatriz** matriz, int x, int y, int bombas);
void limpaZerosArea(pMatriz** matriz, int x, int y, int linha, int coluna);
void desalocacao(pMatriz** matriz, int x);

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

void configuracao(int* x, int* y, int* bombas){
	int dificuldade;
	printf("Qual a dificuldade do campo minado?\n\n1-Facil\n2-Intermediario\n3-Dificil\nESCOLHA: ");
	scanf("%d", &dificuldade);
	switch(dificuldade){
		default:
		case 1:
		*x=8;*y=8;*bombas=10; 
		printf("\n_Dificuldade Facil Selecionada_\n");
		break;
		case 2:
		*x=16;*y=16;*bombas=40; 
		printf("\n_Dificuldade Intermediaria Selecionada_\n");
		break;
		case 3:
		*x=16;*y=30;*bombas=99; 
		printf("\n_Dificuldade Dificil Selecionada_\n");
		break;
	}
	printf("\n");
}

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

int decisaoJogador(pMatriz** matriz, int x, int y, int bombas){
	int linha, coluna, escolha;
	printf("--> Qual coordenada do Campo Minado(%dx%d)?\nESCOLHA: ", x, y);
	scanf("%d %d", &linha, &coluna);
	if(linha>=0 && linha<x && coluna>=0 && coluna<y){
		printf("1-Liberar Espaco\n2-Marcar Bandeira\n");
		scanf("%d", &escolha);
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