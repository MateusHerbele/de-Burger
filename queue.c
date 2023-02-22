#include "header.h"

//enfileirar
void enqueue(struct queue* queue, char* data){
    if(queue == NULL) {
        printf("Erro: ponteiro 'queue' é nulo.\n");
        exit(1);
    }
    if(data == NULL) {
        printf("Erro: ponteiro 'data' é nulo.\n");
        exit(1);
    }
    struct nodeDup* newNode = (struct nodeDup*)malloc(sizeof(struct nodeDup));
    if(newNode == NULL) {
        printf("Erro: falha ao alocar memória para 'newNode'.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    if(queue->last != NULL){
        newNode->prev = queue->last;
        queue->last->next = newNode;
    }
    else {
        newNode->prev = NULL;
        queue->first = newNode; // atribui o primeiro nó da fila
    }
    queue->last = newNode;
    if(queue->first == NULL){
        queue->first = newNode;
    }
}

// remove a fila
// int removeQueue(struct queue* queue){
//     if(queue->first == NULL){
//         return 0;//fila vazia
//     }
//     else{
//         struct nodeDup *temp = queue->first;
//         queue->first = queue->first->next;
//         if(queue->first != NULL){
//             queue->first->prev = NULL;
//         }
//         else{
//             queue->last = NULL;
//         }
//         free(temp);
//         return 1;
//     }
// }

// remove nó da fila
// int removeNodeQueue(struct queue* queue, struct nodeDup* node){
//     if(queue->first == NULL){
//         return 0;//fila vazia
//     }
//     else{
//         if(node->prev != NULL){
//             node->prev->next = node->next;
//         }
//         else{
//             queue->first = node->next;
//         }
//         if(node->next != NULL){
//             node->next->prev = node->prev;
//         }
//         else{
//             queue->last = node->prev;
//         }
//         free(node->data);
//         free(node);
//         return 1;
//     }
// }

// remove o primeiro elemento da fila
int deQueue(struct queue* queue){
    if(queue->first == NULL){
        return 0;//fila vazia
    }
    else{
        struct nodeDup *temp = queue->first;
        queue->first = queue->first->next;
        if(queue->first != NULL){
            queue->first->prev = NULL;
        }
        else{
            queue->last = NULL;
        }
        free(temp->data);
        free(temp);
        return 1;
    }
}

// retorna o primeiro elemento da fila
char* queueFirst(struct queue* queue){
    if(queue->first == NULL){
        return 0;//fila vazia
    }
    return queue->first->data;
}

//gera um número de elementos totais para data, sendo no mínimo 3 e no máximo 8, e coloca os elementos dentro de data.
//tem que começar com 1 e terminar com 1 e os elementos entre o começoe e o final variam de 2 - 6
char* genElements(){
    srand(time(NULL));
    int totalElements = rand() % 6 + 3;
    int* data = malloc(totalElements * sizeof(int));
    if(data == NULL){
        printf("Erro: falha ao alocar memória para 'data'.\n");
        exit(1);
    }
    for(int i = 1; i < totalElements; i++){
        data[i] = rand() % 5 + 2;
    }
    char* characters = malloc(totalElements * sizeof(char));
    characters[0] = 'P';
    characters[totalElements-1] = 'P';
    for(int i = 1; i < totalElements-1; i++){
        switch(data[i]){
            case 2:
                characters[i] = 'H';
                break;
            case 3:
                characters[i] = 'A';
                break;
            case 4:
                characters[i] = 'T';
                break;
            case 5:
                characters[i] = 'Q';
                break;
            case 6:
                characters[i] = 'C';
                break;
        }
    }
    return characters;
}

// termina a fila, da free em tudo que foi alocado nela e seus nós
void endQueue(struct queue* queue){
    while(queue->first != NULL){
        struct nodeDup *temp = queue->first;
        queue->first = queue->first->next;
        free(temp->data);
        free(temp);
    }
    free(queue);
}

// verifica se a fila está vazia
int isEmptyQueue(struct queue* queue){
    if(queue->first == NULL){
        return 1;
    }
    return 0;
}

void printQueue(struct queue* orderList){
    struct nodeDup* current = orderList->first;
    int linha = 3;
    while(current != NULL){
        if(current->data[0] == 'P' && current->data[strlen(current->data)-1] == 'P'){
            // Inverte a string current->data
            char inverted[strlen(current->data) + 1]; // Array de char temporário para armazenar a string invertida
            int i, j;
            for(i = strlen(current->data) - 1, j = 0; i >= 0; i--, j++){
                inverted[j] = current->data[i];
            }
            inverted[j] = '\0'; // Adiciona o caractere nulo no final da string

            // Imprime a string invertida
            mvprintw(linha, 2, "%s", inverted);
            linha++;
        }
        current = current->next;
    }
}