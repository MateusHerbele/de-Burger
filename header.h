#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>  
#include<stdlib.h>
#include<time.h>
#include<ncurses.h>
#include<unistd.h>
#include<math.h>
#include<string.h>
#include <ctype.h>


// Structs da stack
struct node{
    char data; //dados do nó
    struct node *next; //ponteiro para o próximo nó
};
struct stack{
    struct node *top; //ponteiro para o topo da pilha
};

// Structs da queue
struct nodeDup{ // nó duplamente encadeado
    char* data; //dados do nó
    int num; //numero associado ao nó, nesse caso do programa o número do cliente
    struct nodeDup *next; //ponteiro para o próximo nó
    struct nodeDup *prev; //ponteiro para o nó anterior
};
struct queue{
    struct nodeDup *first; //ponteiro para o primeiro nó
    struct nodeDup *last; //ponteiro para o último nó
};

//funções da stack
// coloca um elemento na pilha
void push(struct stack *stack, int data);
// remove um elemento da pilha o topo no caso
void pop(struct stack *stack);
// retorna o topo da pilha
int stackTop(struct stack *stack);
// retorna 1 se a pilha estiver vazia
int isEmpty(struct stack *stack);
// limpa a pilha
void clearStack(struct stack *stack);
// retorna o tamanho da pilha
int sizeStack(struct stack *stack);
// imprime a pilha
void printStack(struct stack* stack);
// libera a stack
void endStack(struct stack* stack);

//funções da queue
//enfileirar
void enqueue(struct queue* queue, char* data, int num);
// remove a fila
//int removeQueue(struct queue* queue);
// remove o primeiro elemento da fila
int deQueue(struct queue* queue);
// retorna o primeiro elemento da fila
char* queueFirst(struct queue* queue);
//gera um número de elementos totais para data, sendo no mínimo 3 e no máximo 8, e coloca os elementos dentro de data.
//tem que começar com 1 e terminar com 1 e os elementos entre o começoe e o final variam de 2 - 7
char* genElements();
// é igual a endqueue mas n da free na fila
void clearQueue(struct queue* queue);
// termina a fila, da free em tudo que foi alocado nela e seus nós
void endQueue(struct queue* queue);
//verifica se está vazia
int isEmptyQueue(struct queue* queue);
//imprime a fila 
void printQueue(struct queue* orderList, int* numOfclients);

// struck dos objetos
struct classObj{
    char symbol[2];
    int hsp, vsp; // "velocidade" vertical e  horizontal do player, só ele se move então só ele usa
    int x, y; // posição do objeto / player
};

// index dos objetos, pra por na matriz e chamar eles dai
#define i_wall   1
#define i_bread  2
#define i_breadBottom  10
#define i_hamburguer   3
#define i_salad 13
#define i_cheese 6
#define i_fries  11
#define i_coca   12
#define i_deliver 8
#define i_discart 9
// cores deles
#define c_wall          1
#define c_bread         2
#define c_breadBottom       2
#define c_hamburguer    3
#define c_salad         4
#define c_cheese        6
#define c_fries        6
#define c_coca          7
#define c_deliver       8
#define c_discart       9
#define c_hud           2
#define c_player        1
// simbolos deles
#define s_wall  "||"
#define s_bread  "P"
#define s_breadBottom  "p"
#define s_hamburguer "H"
#define s_lettuce  "A"
#define s_tomato  "T"
#define s_salad  "S"
#define s_cheese "Q"
#define s_onion   "C"
#define s_fries   "F"
#define s_coca    "R"
#define s_deliver "@"
#define s_discart "o"

#define td_indent 2 // Top & down ident
#define symbol_count 3

// Key Kode
#define vk_space  32
#define vk_enter  10

// Game
// Verifica o pedido quando o jogador entrega
int verifyOrder(struct stack* stack, struct queue* queue);
// faz o player se mover
void playerMove(int key, struct classObj* player, int* dir_x, int* dir_y);
// verifica a colisão do player
void playerCollision(short current_lvl[][13], struct classObj* player, struct stack* p_stack, struct queue* p_queue, int* areaLocker, bool* END, int* loseConditionOne, int* loseConditionTwo, int* score);
//desenha o mapa
void drawKitchen(short lvl[][13], struct classObj* player, int w, int h);
// atualiza o jogo
void gameUpdate(int key, short current_lvl[][13], struct stack* p_stack, struct queue* p_queue, struct classObj* player, int* dir_x, int* dir_y, int w, int h, bool* END, int* areaLocker, int* loseConditionOne, int* loseConditionTwo, int* score);
// inicia a cozinha
void kitchenInit(struct classObj* player, struct stack* p_stack, struct queue* p_queue, int keyPressed, int* dir_x, int* dir_y, bool* END, int w, int h, int* areaLocker, int* loseConditionOne, int* loseConditionTwo, int* score);
// precisa setar as cores dos objetos
void setColor();
// desenha os objetos
void drawInstance(int y, int x, int color, char name[], int w, int h) ;
//desenha a hud
void drawHud(struct queue* queue, struct stack* stack, int* numOfClients, int* loseConditionOne, int* loseConditionTwo, int* p_score, int h, int w);
// Game Over
void gameOver();
// spawna o objeto e passa os parâmetros do objeto para ele
void objInit(struct classObj *obj, int x, int y, int dir, char *objname);
// pega o tamanho de uma string
int strLen(char* str);
// retorna o tamanaho da largura de cada linha do logo
int getLogoWSize(int logoHSize, char** menuLogo);
// desenha o logo
void drawLogo(int h, int w);
// desenha as infos
void drawInfo(int h, int w, int x, int y);
// faz as ações do jogador, seja no jogo ou no menu
void actionsPlayer(int h, int w, int keyPressed, struct queue* p_queue, struct stack* p_stack, struct classObj* p_player, bool* END, char* p_data);

#endif