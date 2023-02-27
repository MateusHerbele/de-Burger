#include "header.h"
//enfileirar
void enqueue(struct queue* queue, char* data, int num){
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
    newNode->num = num;
    newNode->next = NULL;//nó novo é o último da fila então o next dele é NULL
    if(queue->last != NULL){ // se a fila não estiver vazia
        newNode->prev = queue->last; // o prev do novo nó é o last da fila
        queue->last->next = newNode; // o next do last da fila é o novo nó
    }
    else { // se a fila estiver vazia
        newNode->prev = NULL; // o prev do novo nó é NULL
        queue->first = newNode; // atribui o primeiro nó da fila
    }
    queue->last = newNode; // atualiza o last da fila
    if(queue->first == NULL){ // se a fila estiver vazia
        queue->first = newNode; // atribui o primeiro nó da fila
    }
}
// remove o primeiro elemento da fila
int deQueue(struct queue* queue){
    if(queue->first == NULL){
        return 0;//fila vazia
    }
    else{
        struct nodeDup *temp = queue->first; // guarda o primeiro nó da fila
        queue->first = queue->first->next; // atualiza o primeiro nó da fila
        if(queue->first != NULL){ // se a fila não estiver vazia
            queue->first->prev = NULL;  // atualiza o prev do novo primeiro nó da fila
        }
        else{ // se a fila estiver vazia
            queue->last = NULL; // atualiza o last da fila
        }
        free(temp->data); // libera o data do nó
        free(temp); // libera o nó
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
//gera um número de uma refeição
char* genElements(){
    int meal = rand() % 6 + 1;
    switch(meal){
        case 1: //x-burger
            char* data1 = malloc(5*sizeof(char));
            if(data1 == NULL){
                printf("Erro: falha ao alocar memória para 'data1'.\n");
                exit(1);
            }
            data1[0] = 1;
            data1[1] = 'P'; //pHQP
            data1[2] = 'Q';
            data1[3] = 'H';
            data1[4] = 'p';
            return data1;
        break;
        case 2: //x-salada
            char* data2 = malloc(5*sizeof(char));
            if(data2 == NULL){
                printf("Erro: falha ao alocar memória para 'data2'.\n");
                exit(1);
            }
            data2[0] = 2;
            data2[1] = 'P'; //pHSP
            data2[2] = 'S';
            data2[3] = 'H';
            data2[4] = 'p';
            return data2;
        break;
        case 3: //combo 1
            char* data3 = malloc(7*sizeof(char));
            if(data3 == NULL){
                printf("Erro: falha ao alocar memória para 'data3'.\n");
                exit(1);
            }
            data3[0] = 3;
            data3[1] = 'R'; //pHQPFR
            data3[2] = 'F';
            data3[3] = 'P';
            data3[4] = 'Q';
            data3[5] = 'H';
            data3[6] = 'p';
            return data3;
        break;
        case 4: //combo 2
            char* data4 = malloc(7*sizeof(char));
            if(data4 == NULL){
                printf("Erro: falha ao alocar memória para 'data4'.\n");
                exit(1);
            }
            data4[0] = 4;
            data4[1] = 'R'; //pHSPFR
            data4[2] = 'F';
            data4[3] = 'P';
            data4[4] = 'S';
            data4[5] = 'H';
            data4[6] = 'p';
            return data4;
        break;
        case 5: //vegetariano
            char* data5 = malloc(6*sizeof(char));
            if(data5 == NULL){
                printf("Erro: falha ao alocar memória para 'data5'.\n");
                exit(1);
            }
            data5[0] = 5;
            data5[1] = 'R'; //pQPFR
            data5[2] = 'F';
            data5[3] = 'P';
            data5[4] = 'Q';
            data5[5] = 'p';
            return data5;
        break;
        case 6: //vegano
            char* data6 = malloc(4*sizeof(char));
            if(data6 == NULL){
                printf("Erro: falha ao alocar memória para 'data6'.\n");
                exit(1);
            }
            data6[0] = 6;
            data6[1] = 'R'; //SFR
            data6[2] = 'F';
            data6[3] = 'S';
            return data6;
        break;
    }
    return 0; // pra evitar o wall, mas sempre entra no switch
}
// limpa a fila é igual a endQueue mas não da free na fila
void clearQueue(struct queue* queue){
    while(queue->first != NULL){
        struct nodeDup *temp = queue->first;
        queue->first = queue->first->next;
        free(temp->data);
        free(temp);
    }
    queue->first = NULL;
    queue->last = NULL;
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
void printQueue(struct queue* orderList, int* numOfCLients){
    struct nodeDup* current = orderList->first;
    int linha = 4;
    while(current != NULL){
        switch(current->data[0]){
            case 1:
                mvprintw(linha, 3, "CLIENTE %d:X-Burger: pHQP", current->num);
                linha++;
            break;
            case 2:
                mvprintw(linha, 3, "CLIENTE %d:X-Salada: pHSP", current->num);
                linha++;
            break;
            case 3:
                mvprintw(linha, 3, "CLIENTE %d:Combo 1: pHQPFR", current->num);
                linha++;
            break;
            case 4:
                mvprintw(linha, 3, "CLIENTE %d:Combo 2: pHSPFR", current->num);
                linha++;
            break;
            case 5:
                mvprintw(linha, 3, "CLIENTE %d:Vegetariano: pQPFR", current->num);
                linha++;
            break;
            case 6:
                mvprintw(linha, 3, "CLIENTE %d:Vegano: SFR", current->num);
                linha++;
            break;
        }
        if(linha == 9) break; // pra imprimir só 5 por vez, começa na linha 4 + 5 = 9
        current = current->next;
    }
}