#ifndef DEBURGUER_H
#define DEBURGUER_H

#include<stdio.h>  
#include<stdlib.h>
#include<time.h>

// Estrutras dos pedidos ======================================================
struct order{
    int numClient;
    int numIng;
    int* ingredients;
    int deadline;// 30 segundos por pedido, pode ser alterado
    int points;// 50 pontos por pedido entregue, pode ser alterado
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
// Pedido
struct list* createList();

struct orderNode* createNode(int id, struct order order);

void addOrderNode(struct list* list, struct orderNode* orderNode);

void removeOrderNode(struct list* list, struct orderNode* orderNode);

void sortTime(struct orderNode* head);

int genNumIng(int numIng);

int genIngredients(int numIng);

struct order* createOrder(int numIng, int* ingredients);

//Estutura de dados da montagem=================================================
struct local{
    int x;
    int y;
};

struct recipe{
    int amountIng;
    int ingredients[8];
};

struct player{
    struct local local;
    struct recipe recipe;
};
//=============================================================================

//Montagem
void kitchenPlaces(struct player* player);

void addIngredient(struct player* player, int ingredient);

void clearRecipe(int* recipe);


#endif // DEBURGUER_H
