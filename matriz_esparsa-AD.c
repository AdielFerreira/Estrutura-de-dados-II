#include <stdio.h>
#include <stdlib.h>

#include <malloc.h>

//definicao das estruturas
//lista
typedef struct tempNo{
	float valor;
	int coluna;
	struct tempNo* prox;
}NO;
typedef NO* PONT;

//matriz esparsa
typedef struct{
	PONT* A;
	int linhas;
	int colunas;
}MATRIZ;

//prototipacao de funcoes
MATRIZ *inicializaMatriz(int lin, int col);
MATRIZ *somaMatrizes(MATRIZ *m, MATRIZ *n);
void imprimeMatriz(MATRIZ* m);
float imprimeValorMatriz(MATRIZ* m,int lin, int col);
void atribuiMatriz(MATRIZ* m,int lin, int col, float val);
float multValor(MATRIZ* m, float val);
float somaValor(MATRIZ* m);
void removeDuploMatriz(MATRIZ *m, MATRIZ *n);
void LerArquivo(MATRIZ *m,int tam,char *nomeArq);


int main(){
	
	MATRIZ *m;
	MATRIZ *n;
	MATRIZ *s;
	
//	Inicializa matriz tamanho 3x3
	m = inicializaMatriz(3,3);
//	Matriz M carregada de arquivo
	LerArquivo(m,9,"teste.txt");
	printf("\nMatriz M:\n");
	imprimeMatriz(m);
	
//	Inicializa matriz tamanho 3x3
	n = inicializaMatriz(3,3);
// 	Insere valores na linha 1 colunas 0,1,2
	atribuiMatriz(n,1,0,2);
	atribuiMatriz(n,1,1,3);
	atribuiMatriz(n,1,2,5);
	printf("\nMatriz N:\n");
	imprimeMatriz(n);
	
//	Testa funcao remover numeros duplicados
	removeDuploMatriz(m,n);
	printf("\nMATRIZ M SEM VALORES EM N\n");
	imprimeMatriz(m);

//	Inicializa matriz S	
	s = inicializaMatriz(3,3);
//	Matriz S recebe m + n
	s = somaMatrizes(m,n);
	printf("\nMatriz S (M + N):\n");
	imprimeMatriz(s);
	
//	Testa funcoes de multiplicacao e somados da matriz
	printf("\nValores multiplicados da matriz M: %.f\n",multValor(m,2.0));
	printf("\nValores somados da matriz M: %.f\n",somaValor(m));
	
//	Testa recuperar valores de linha/coluna especifico da matriz
//	printf("%.f",imprimeValorMatriz(m,1,1));	
	

}

MATRIZ *inicializaMatriz(int lin, int col){
	
	MATRIZ *m;
	m = (MATRIZ *) malloc (sizeof(MATRIZ));
	
	m->linhas = lin;
	m->colunas = col;
	m->A = (PONT*) malloc(lin*sizeof(PONT));
	for(int i=0;i<lin;i++){
		m->A[i] = NULL;
	}
	return m;
}

void imprimeMatriz(MATRIZ* m){
	
	PONT novo;
	for(int i=0;i<m->linhas;i++){
		for(int c=0;c<m->colunas;c++){
			printf("[%.f]",imprimeValorMatriz(m,i,c));
		}
		printf("\n");
	}
}

float imprimeValorMatriz(MATRIZ* m,int lin, int col){
	
	if(lin < 0 || lin >= m->linhas || col < 0  || col >= m->colunas){
		return 0;
	}
	
	PONT atual = m->A[lin];
	while(atual != NULL && atual->coluna < col){
		atual = atual->prox;
	}
	if(atual != NULL && atual->coluna == col){
		return atual->valor;
	}else{
		return 0;
	}
}

void atribuiMatriz(MATRIZ* m,int lin, int col, float val){
	//Verifica se os valores passados atendem as dimensoes
	if(lin < 0 || lin >= m->linhas || col < 0 || col >= m->colunas){
		return 0;
	}
	
	//percorre a matriz ate achar a linha/col desejada	
	PONT ant = NULL;
	PONT atual = m->A[lin];
	while(atual != NULL && atual->coluna < col){
		ant = atual;
		atual = atual->prox;
	}	
	
	if(atual != NULL && atual->coluna == col){
		//se o valor a ser inserido for 0 excluiremos o que tives na posicao da matriz
		if(val == 0){
			if(ant == NULL){
				m->A[lin] = atual->prox;
			}else{
				ant->prox = atual->prox;
			}
			free(atual);
		}else{
			atual->valor = val;
		}
	}else{
		PONT novo = (PONT) malloc(sizeof(NO));
		novo->coluna = col;
		novo->valor = val;
		novo->prox = atual;
		if(ant == NULL){
			m->A[lin] = novo;
		}else{
			ant->prox = novo;
		}
	}
	return 1;
}

float multValor(MATRIZ* m, float val){
	float valorFinal = val;
	printf("\nMultiplicando o valor %.f pelos valores da matriz...",val);
	PONT novo;
	for(int i=0;i<m->linhas;i++){
		for(int c=0;c<m->colunas;c++){
			if(imprimeValorMatriz(m,i,c) != 0){
				printf("\n%.f * %.f\n",valorFinal,imprimeValorMatriz(m,i,c));
				valorFinal = (valorFinal *  imprimeValorMatriz(m,i,c));
			}
		}
	}
	return valorFinal;
}
float somaValor(MATRIZ* m){
	float valorFinal = 0.0;
	printf("\nSomando todos os valores da matriz...");
	PONT novo;
	for(int i=0;i<m->linhas;i++){
		for(int c=0;c<m->colunas;c++){
			if(imprimeValorMatriz(m,i,c) != 0){
				printf("\n%.f + %.f\n",valorFinal,imprimeValorMatriz(m,i,c));
				valorFinal += imprimeValorMatriz(m,i,c);
			}
		}
	}
	return valorFinal;
}
MATRIZ *somaMatrizes(MATRIZ *m, MATRIZ *n){
	MATRIZ *soma;
	soma = (MATRIZ *) malloc (sizeof(MATRIZ));
	soma->linhas = m->linhas;
	soma->colunas = m->colunas;
	soma->A = (PONT*) malloc(m->linhas*sizeof(PONT));
	
	float valorSomado = 0;
	//verifica se as matrizes são de tamanhos iguais
	if((m->linhas != n->linhas) && (m->colunas != m->colunas)){
		printf("Matrizes de tamanhos diferentes não podem ser somadas!");
		return 0;
	}
	
	for(int i=0;i<m->linhas;i++){
		for(int c=0;c<m->colunas;c++){	
			valorSomado = imprimeValorMatriz(m,i,c) + imprimeValorMatriz(n,i,c);
			atribuiMatriz(soma,i,c,valorSomado);
		}
	}
	return soma;
}

void removeDuploMatriz(MATRIZ *m, MATRIZ *n){
	
	for(int i=0;i<m->linhas;i++){
		for(int c=0;c<m->colunas;c++){	
			if(imprimeValorMatriz(m,i,c) == imprimeValorMatriz(n,i,c)){
				atribuiMatriz(m,i,c,0);
			}
		}
	}
}

//funcao de ler arquivo
void LerArquivo(MATRIZ *m,int tam,char *nomeArq){
	
	FILE *arq;	
	arq = fopen(nomeArq,"rt");
	
	if(arq == NULL){
		printf("\nErro no arquivo\n");
	}
	
	//LE DO ARQUIVO
	float valor; 
	for(int i=0;i<m->linhas;i++){
		for(int c=0;c<m->colunas;c++){	
			fscanf(arq,"%f\n",&valor);	
			atribuiMatriz(m,i,c,valor);
		}
	}
	fclose(arq);
}
