/* Aqui os pedidos devem ser gerados de forma infinita
seguindo regras como sempre ter o pão na parte de cima e de baixo
e alternarem entre 4-8 ingredientes, sendo eles 
-pão = 1
-hamburguer = 2
-alface = 3 
-tomate = 4
-queijo = 5 
-cebola = 6

O que precisa ser feito é:
- Criar a lista que deve incorporar os pedidos
- Criar a função que gera os pedidos
- Criar um tempo para cada pedido que estara dentro da estrutura de dados dele
- Criar uma função que reconhece se o pedido montado é igual a algum dos pedidos na lista
- Criar uma função que remove os pedidos que já foram entregues
- Criar uma função que remove o pedido caso ele não tenha sido entregue dentro de um tempo limite
- Criar função que retorna um número de pontos para cada pedido entregue dentro do tempo limite
- Criar função que subtrai uma quantidade de pontos por pedidos expirados 
*/
#include "dbheader.h"
#include<time.h>

// Set da SEED do rand
srand(time(NULL));

// Estrutras dos pedidos ======================================================
struct order{
    int numIng;
    int* ingredients;
    ingredients; 
    int deadline;// 30 segundos por pedido, pode ser alterado
    int points;// 50 pontos por pedido entregue, pode ser alterado
};

struct client{
    int id;
    struct order order;
    int* nxtClient;
};

struct list{
    struct client* head;
    struct client* tail;
    int size;
};
// =============================================================================

struct list* createList(){
    struct list* newList = malloc(sizeof(struct list));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

struct client* createClient(int id, struct order order){
    struct client* newClient = malloc(sizeof(struct client));
    newClient->id = id;
    newClient->order = order;
    newClient->nxtClient = NULL;
    return newClient;
}

void addClient(struct list* list, struct client* client){
    if(list->head == NULL){
        list->head = client;
        list->tail = client;
    }
    else{
        list->tail->nxtClient = client;
        list->tail = client;
    }
    list->size++;
}

void removeClient(struct list* list, struct client* client){
    struct client* aux = list->head;
    if(aux == client){
        list->head = aux->nxtClient;
        free(aux);
    }
    else{
        while(aux->nxtClient != client){
            aux = aux->nxtClient;
        }
        aux->nxtClient = client->nxtClient;
        free(client);
    }
    list->size--;
}

void sortTime(struct client client){
    // função que ordena os pedidos de acordo com o tempo limite
    struct client* aux;
    int trades;

    if(head == NULL){
        return;
    }
    while(1){
        aux = head;
        trades = 0;
        while(aux->nxtPedido != NULL){
            if(aux->order->deadline > aux->nxtClient->order->deadline){
                struct client* temp = aux->id;
                aux->id = aux->nxtClient->id;
                aux->nxtClient->id = temp;
                trades++;
            }
            aux = aux->nxtPedido;
        }
        if(trades == 0){
            return;
        }
    }
}

int genNumIng(int numIng){
    // função que gera um número aleatório de ingredientes entre 4 e 8
    return (rand() % 5 + 4);
}

int genIngredients(int numIng){
    // função que gera um vetor de ingredientes aleatórios
    int* ing = malloc (numIng*sizeof(int));
    ing[0] = 1;
    ing[numIng-1] = 1;

    int gnr;


    for(int i = 1; i < numIng-1; i++){
        ing[i] = (rand() % 6 + 2);
    }
    return ing;
}

struct order* createOrder(int numIng, int* ingredients){
    struct order* newOrder = malloc(sizeof(struct order));
    newOrder->numIng = genNumIng(numIng);
    newOrder->ingredients = genIngredients(numIng);
    return newOrder;
}



