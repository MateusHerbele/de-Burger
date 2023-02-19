#ifndef DEBURGUER_H
#define DEBURGUER_H

#include<stdio.h>  
#include<stdlib.h>
#include<time.h>
#include<ncurses.h>
#include<unistd.h>
#include<math.h>
#include<string.h>

// Estrutras dos pedidos ======================================================
struct order{
    int numClient;
    int numIng;
    int* ingredients;
    int deadline;// 30 segundos por pedido, pode ser alterado
    int score;// 50 pontos por pedido entregue, pode ser alterado
};

struct orderNode{
    struct order* id;
    struct orderNode* nxtOrder;
};

struct list{
    struct orderNode* head;
    struct orderNode* tail;
    int size;
};
// =============================================================================

struct list* createList();
//lista geral

struct orderNode* createNode(int* id, struct order* order, int* amountOfOrders);

void addOrderNode(struct list* list, struct orderNode* orderNode);

int removeOrderNode(struct list* list, struct orderNode* orderNode);

void sortTime(struct orderNode* head);

int genNumIng();

int* genIngredients(int numIng);

struct order* createOrder();

//Estutura de dados da montagem=================================================
struct local{
    int x;
    int y;
    int hSpace; // espaço horizontal
    int vSpace; // espaço vertical
};

struct recipe{
    int amountIng;
    int ingredients[8];
};

struct player{
    struct local local;
    struct recipe recipe;
    char* skin;
    int score;
};
//=============================================================================

//Montagem
void kitchenPlaces(struct player* player, int* amountOfOrders, struct list* list);

void addIngredient(struct player* player, int ingredient);

void clearRecipe(int* recipe);

// Defições do mundo ===========================================================
//Definição do estado do jogo
#define NORMAL  true;
#define OVER  false;

struct object{
    struct local local;
    char* skin;
    //int dir;
    };

//int gameStatus = NORMAL;



// objetos do mapa
#define oBread 1
#define oHamburguer 2
#define oLettuce 3
#define oTomato 4
#define oCheese 5
#define oOnion 6
#define oDeliver 7
#define oDiscart 8
#define oWall 0


// O mapa
#define cBread "8"
#define cHamburguer "O"
#define cLettuce "W"
#define cTomato "T"
#define cCheese "-"
#define cOnion "ç"
#define cDeliver "D"
#define cDiscart "X"
#define cWall "█"
#define cEmpty " "; // Pra onde não tiver nada


// Draw colored instance
#define td_indent 2 // Top & down ident
#define symbol_count 3



// Funções World
void verifyOrder(struct player* player, int* recipe, int* numOfOrders, struct list* list);
int strLen(const char* str);
int getLogoWSize(int logoHSize,  const char * const menuLogo[]);
void drawLogo(int h, int w, int logoWSize, int logoHSize,  const char * const menuLogo[], int pHud);
void drawMenu(int h, int w, int pHud, int logoWSize, int logoHSize, char * const menuLogo[]);
void setColor(int pBread, int pHamburguer, int pLettuce, int pTomato, int pCheese, int pOnion, int pDeliver, int pDiscart, int pWall);
void drawObject(int y, int x, int color, char name[], int w, int h);
void genObjcts(struct object *object, int x, int y,char *skin);
void genPlayer(struct player *player, int x, int y, char *skin);
void playerMove(int key, struct player* player, int dirX, int dirY);
void playerCollision(short kitchen[20][27], struct player* player, int* amountOfOrders, struct list* list);
void genKitchen(short kitchen[20][27], struct player* player, int w, int h, int pBread, int pHamburguer, int pLettuce, int pTomato, int pCheese, int pOnion, int pWall, int pDeliver, int pDiscart, int pPlayer);
void drawHud(int score);

  struct gameStates{
        int STATE_MENU;
        int STATE_INFO;
        int STATE_GAME;
        int STATE_EXIT;
    };
void gameOver(struct gameStates* gameStatus);
void gameUpdate(int key, short kitchen[][27], struct player* player, struct gameStates* gameStatus, struct list* list, int dirX, int dirY, int* amountOfOrders, int w, int h, int pBread, int pHamburguer, int pLettuce, int pTomato, int pCheese, int pOnion, int pWall, int pDeliver, int pDiscart, int pPlayer);
//pro main
 
    #define keyEnter 10
    #define keyEspace 32

#endif // DEBURGUER_H
