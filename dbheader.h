#ifndef DEBURGUER_H
#define DEBURGUER_H

#include<stdio.h>  
#include<stdlib.h>

struct client* createClient(int id, struct order order);
void addClient(struct list* list, struct client* client);
void removeClient(struct list* list, struct client* client);
void sortTime(struct client client);
int genNumIng(int numIng);




#endif // DEBURGUER_H