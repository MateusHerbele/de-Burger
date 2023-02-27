#include "header.h"

void push(struct stack *stack, int data){ // push = empurar, coloca algo novo na stack
    if(stack == NULL){
        printf("Erro: ponteiro 'stack' é nulo.\n");
        exit(1);
    }
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if(newNode == NULL){
        printf("Erro: falha ao alocar memória para 'newNode'.\n");
        exit(1);
    }
    newNode->data = data; // atribui o dado ao novo nó
    newNode->next = stack->top; // o next do novo nó é o top da pilha
    stack->top = newNode;   // atualiza o top da pilha
}

void pop(struct stack *stack){ // pop = tirar, remove o elemento do topo da pilha
    if(stack->top == NULL){
        printf("Pilha vazia");//pilha vazia
    }
    else{
        struct node *temp = stack->top; // guarda o top da pilha
        stack->top = stack->top->next; // atualiza o top da pilha
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
    struct node* current = stack->top; // guarda o top da pilha
    while(current != NULL){ // enquanto não chegar no final da pilha
        size++; // incrementa o tamanho da pilha
        current = current->next; // atualiza o current para o próximo nó
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
    int column = 69;
    for (int i = size-1; i >= 0; i--){
        mvprintw(4, column, "%c ", elements[i]);
        column++;
    }

    free(elements);
}

void endStack(struct stack* stack){
    clearStack(stack);
    free(stack);
}