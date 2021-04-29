#include <stdio.h>
#include <stdlib.h>

 //PROTOTIPAÇÃO DAS FUNÇÕES
typedef struct lista Lista;
Lista* criaLista(void); 
Lista* insereInicio(Lista* li, int i);
Lista* insereFim(Lista* li, int i);
Lista* insereFimRecursivo(Lista* li, int i);
Lista* insereOrdenado(Lista* li, int i);
Lista* insereOrdenadoRecursivo(Lista* li,Lista* ant, int i);
Lista* exclui(Lista* li, int i);
Lista* altera(Lista* li, int vantigo, int vnovo);
void imprime(Lista* li);

int main(){
	
	Lista* lista = criaLista();
	
	//insere no fim
	lista = insereFim(lista,1);
	lista = insereFim(lista,2);
	lista = insereFim(lista,3);
	//insere no fim da lista de forma recursiva
	lista = insereFimRecursivo(lista,9);
	lista = insereFimRecursivo(lista,10);
	//insere ordenado
	lista = insereOrdenado(lista,5);
	//insere ordenado de forma recursiva
	lista = insereOrdenadoRecursivo(lista,lista,6);
	lista = insereOrdenadoRecursivo(lista,lista,7);
	lista = insereOrdenadoRecursivo(lista,NULL,4);
	//mostra a lista
	printf("Lista completa");
	imprime(lista);
	//exclui elementos da lista
	lista = exclui(lista,3);
	lista = exclui(lista,6);
	//troca um valor da lista por outro
	lista = altera(lista,7,100);
	lista = altera(lista,2,100);
	//imprime a lista com as alteracoes
	printf("Lista Alterada e com exclusoes\n");
	imprime(lista);
}

//Define a estrutura LISTA
struct lista{ 
	int info; //Valor inteiro da lista
	struct lista* prox; //Endereco de memoria do proximo elemento
};
//cria a lista inicialmente vazia
Lista* criaLista(void){
	return NULL;
};
//insere no inicio da lista
Lista* insereInicio(Lista* li, int i){
	Lista* novo = (Lista*) malloc(sizeof(Lista));//Aloca memoria para armazenar valores na lista
	novo->info = i;//Insere o valor i dentro da info na struct lista
	novo->prox = li;//seta o endereco da lista, apontando para o proximo elemento
	
	return novo;
}


Lista* insereFim(Lista* li, int i){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = i;
	novo->prox = NULL;
	
	Lista* p = li;
	Lista* q = li;
	
	//Funcao que encontra o ultimo da lista
	while(p != NULL){
		q = p;
		p = p->prox;
	}
	if (q != NULL){
		q->prox = novo;
	}else{
		li= novo;
	}
	return li;
}

Lista* insereFimRecursivo(Lista* li, int i){
	
	if(li->prox == NULL){ //verifica se o proximo elemento da lista existe
		//caso exista, aloca um novo elemento e adiciona no final
		Lista* novo = (Lista*) malloc(sizeof(Lista));
		novo->info = i;
		novo->prox = NULL;
		
		li->prox = novo;
	}else{
		//caso não exista, chama a propria funcao, passando o endereço do proximo elemento para verificacao
		insereFimRecursivo(li->prox,i);
	}
	return li;
}

Lista* insereOrdenado(Lista* li, int i){
	Lista* novo;
	Lista* ant = NULL; //ponteiro para elemento anterior
	Lista* p = li; //ponteiro para percorrer a lista
	//procura posicao de insercao	                         
	while(p != NULL && p->info < i){
		ant = p;
		p = p->prox;
	}
	novo = (Lista*) malloc(sizeof(Lista));
	novo->info = i;
	if(ant == NULL){
		novo->prox = li;
		li = novo;
	}else{
		novo->prox = ant->prox;
		ant->prox = novo;
	}
	return li;
}
Lista* insereOrdenadoRecursivo(Lista* li,Lista* ant, int i){
	if(li != NULL){
		if(li->info > i){
			Lista* novo = (Lista*) malloc(sizeof(Lista));
			novo->info = i;
			if(ant == NULL){
				novo->prox = li;
				li= novo;
			}else{
				novo->prox = ant->prox;
				ant->prox = novo;
			}
		}else{
			insereOrdenadoRecursivo(li->prox,li,i);
		}
	}else{
		insereOrdenadoRecursivo(li->prox,li,i);
	}
	return li;
}
Lista* exclui(Lista* li, int i){
	
		Lista* ant = NULL; //ponteiro para elemento anterior
		Lista* p = li; //ponteiro para percorrer a lista
		//procura posicao de insercao	                         
		while(p != NULL){
			ant = p;
			p = p->prox;
			if(p->info == i){
				ant->prox = p->prox;
				printf("EXCLUIDO %d \n", p->info);
				return li;
			}
		}
}
Lista* altera(Lista* li, int vantigo, int vnovo){
		Lista* ant = NULL; //ponteiro para elemento anterior
		Lista* p = li; //ponteiro para percorrer a lista
		//procura posicao de insercao	                         
		while(p != NULL){
			ant = p;
			p = p->prox;
			if(p->info == vantigo){
				printf("Alterando %d por %d \n ",p->info,vnovo);
				p->info = vnovo;
				return li;
		}
	}
	
}
void imprime(Lista* li){ 
	Lista* p;
	for(p = li;p != NULL;p = p->prox){
		printf("\ninfo = %d\n",p->info);
	}
}
