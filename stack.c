#include "header.h"

void push(struct stack *stack, int data){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if(newNode == NULL){
        printf("Erro: falha ao alocar memória para 'newNode'.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

void pop(struct stack *stack){
    if(stack->top == NULL){
        printf("Pilha vazia");//pilha vazia
    }
    else{
        struct node *temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}

int stackTop(struct stack *stack){
    if(stack->top == NULL){
        printf("Pilha vazia");//pilha vazia
    }
    return stack->top->data;
}

int isEmpty(struct stack *stack){
    if(stack->top == NULL){
        return 1;//pilha vazia
    }
    else{
        return 0;//pilha não vazia
    }
}

// limpa a pilha
void clearStack(struct stack *stack){
    while(stack->top != NULL){
        pop(stack);
    }
}

// retorna o tamanho da pilha
int sizeStack(struct stack *stack){
    int size = 0;
    struct node* current = stack->top;
    while(current != NULL){
        size++;
        current = current->next;
    }
    return size;
}

void printStack(struct stack* stack){
    int size = sizeStack(stack);
    char* elements = malloc(size * sizeof(char));

    // Armazena os elementos da pilha em um vetor
    struct node* current = stack->top;
    for (int i = 0; i < size; i++){
        elements[i] = current->data;
        current = current->next;
    }

    // Imprime os elementos na tela, do último ao primeiro
    int column = 25;
    for (int i = size-1; i >= 0; i--){
        mvprintw(2, column, "%c ", elements[i]);
        column++;
    }

    free(elements);
}

void endStack(struct stack* stack){
    clearStack(stack);
    free(stack);
}