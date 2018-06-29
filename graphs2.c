#include <stdio.h>
#include <stdlib.h>

#define SIZE 40
#define NIVELRECOMENDACAO 2
#define OUTRONIVEL 9999

typedef struct Fila{
    int items[SIZE];
    int listaRecomendacoes[SIZE];
    int nRecomendacoes;
    int nAmigos;
    int nivel;
    int inicio;
    int final;
}Fila;

Fila* criaFila();
void adicionaFila(Fila* q, int);
int removeFila(Fila* q);
int eVazio(Fila* q);
void imprimeFila(Fila* q);

typedef struct No{
    int nivel;
    int vertice;
    struct No* prox;
}No;

struct No* criaNo(int);

typedef struct Grafo
{
    int numVertices;
    No** listaAdj;
    int* visitado;
}Grafo;

Grafo* criaGrafo(int vertices);
void buscaLargura(Grafo* grafo, int verticeInicial);
void adicionarNo(Grafo* grafo, int src, int dest);

int main()
{
    Grafo* grafo = criaGrafo(8);
    adicionarNo(grafo, 0, 1);
    adicionarNo(grafo, 0, 2);
    adicionarNo(grafo, 0, 3);
    adicionarNo(grafo, 0, 6);
    adicionarNo(grafo, 2, 7);
    adicionarNo(grafo, 1, 6);
    adicionarNo(grafo, 3, 4);
    adicionarNo(grafo, 4, 5);
    adicionarNo(grafo, 4, 6);
    adicionarNo(grafo, 4, 7);





    buscaLargura(grafo, 0);

    return 0;
}

void buscaLargura(Grafo* grafo, int verticeInicial) {
    Fila* q = criaFila();
    int amigosAnalisados = -1;
    q->nRecomendacoes = 0;
    q->nAmigos = 0;

    grafo->visitado[verticeInicial] = 1;
    adicionaFila(q, verticeInicial);

    printf("                                EXECUCAO DA BUSCA                                       \n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    while(!eVazio(q)){
        amigosAnalisados++;
        if (amigosAnalisados > 0 && amigosAnalisados <= q->nAmigos) {
          q->nivel = NIVELRECOMENDACAO;
        }else{
          q->nivel = OUTRONIVEL;
        }
        imprimeFila(q);
        int verticeAtual = removeFila(q);
        printf("\nVisitou %d\n", verticeAtual);

        No* temp = grafo->listaAdj[verticeAtual];

       while(temp){
            if (verticeAtual == verticeInicial){
              q->nAmigos++;
            }
            int adjVertex = temp->vertice;

            if(grafo->visitado[adjVertex] == 0){
                grafo->visitado[adjVertex] = 1;
                adicionaFila(q, adjVertex);
            }
            temp = temp->prox;
       }
    }
      printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\nRecomendacoes de amizade: ");
    for (int i = 0; i < q->nRecomendacoes; i++) {
      printf("%d ", q->listaRecomendacoes[i]);
    }
    printf("\n");

}


No* criaNo(int v)
{
    No* novoNo = malloc(sizeof(No));
    novoNo->vertice = v;
    novoNo->prox = NULL;
    return novoNo;
}


Grafo* criaGrafo(int vertices)
{
    Grafo* grafo = malloc(sizeof(Grafo));
    grafo->numVertices = vertices;

    grafo->listaAdj = malloc(vertices * sizeof(No*));
    grafo->visitado = malloc(vertices * sizeof(int));


    int i;
    for (i = 0; i < vertices; i++) {
        grafo->listaAdj[i] = NULL;
        grafo->visitado[i] = 0;
    }

    return grafo;
}

void adicionarNo(Grafo* grafo, int src, int dest)
{
    // Add edge from src to dest
    No* novoNo = criaNo(dest);
    novoNo->prox = grafo->listaAdj[src];
    grafo->listaAdj[src] = novoNo;

    // Add edge from dest to src
    novoNo = criaNo(src);
    novoNo->prox = grafo->listaAdj[dest];
    grafo->listaAdj[dest] = novoNo;
}

Fila* criaFila() {
    Fila* q = malloc(sizeof(Fila));
    q->inicio = -1;
    q->final = -1;
    return q;
}


int eVazio(Fila* q) {
    if(q->final == -1)
        return 1;
    else
        return 0;
}

void adicionaFila(Fila* q, int value){
    if(q->final == SIZE-1)
        printf("\nFila esta cheia!\n");
    else {
        if(q->inicio == -1)
            q->inicio = 0;
        q->final++;
        q->items[q->final] = value;
        if (q->nivel == NIVELRECOMENDACAO){
          q->listaRecomendacoes[q->nRecomendacoes] = value;
          q->nRecomendacoes++;
        }
    }
}

int removeFila(Fila* q){
    int item;
    if(eVazio(q)){
        printf("\nFila esta vazia!\n");
        item = -1;
    }
    else{
        item = q->items[q->inicio];
        q->inicio++;
        if(q->inicio > q->final){
            printf("\nResetando Fila!\n");
            q->inicio = q->final = -1;
        }
    }
    return item;
}

void imprimeFila(Fila *q) {
    int i = q->inicio;

    if(eVazio(q)) {
        printf("\nFila esta vazia!\n");
    } else {
        printf("\nFila contem:\n");
        for(i = q->inicio; i < q->final + 1; i++) {
                printf("%d ", q->items[i]);
        }
    }
}
