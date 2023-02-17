/* Aqui deve ser as funções responsáveis por montar o pedido conforme o 
chapeiro anda pela cozinha e recolhe os ingredientes
Quero fazer uma fila que adquiria os elementos que o player passar pela seção
e após isso eu consiga comparar os elementos da fila com um vetor para confirmar se é igual ou não
*/

#include "dbheader.h"

int* locker = 0;
// Preencher com 0 o vetor da montagem
//clearRecipe(player->recipe.ingredients); - No main


void kitchenPlaces(struct player* player){
//pão
if(player->local.x == 1 && player->local.y == 1 && locker == 0){
        addIngredient(player->recipe.ingredients, 1);
        *locker = 1;
}
//hamburguer)
if(player->local.x == 1 && player->local.y == 1 && locker == 0){
        addIngredient(player->recipe.ingredients, 2);
        *locker = 1;
}
//alface
if(player->local.x == 1 && player->local.y == 1 && locker == 0){ 
        addIngredient(player->recipe.ingredients, 3);
        *locker = 1;
}
//tomate
if(player->local.x == 1 && player->local.y == 1 && locker == 0){
        addIngredient(player->recipe.ingredients, 4);
        *locker = 1;
}
//queijo
if(player->local.x == 1 && player->local.y == 1 && locker == 0){
        addIngredient(player->recipe.ingredients, 5);
        *locker = 1;
}
//cebola
if(player->local.x == 1 && player->local.y == 1 && locker == 0){
        addIngredient(player->recipe.ingredients, 6);
        *locker = 1;
}

// aqui o player envia o pedido:
if(player->local.x == 1 && player->local.y == 1 && locker == 0){
        verifyOrder(player->recipe.ingredients);
        *locker = 1;
}
// aqui o player descarta a montagem:
if(player->local.x == 1 && player->local.y == 1 && locker == 0){
        clearRecipe(player->recipe.ingredients);
        *locker = 1;
}
//Verifica se o player entrou em um local neutro
if(player->local.x == 1 && player->local.y == 1){
        *locker = 0;
}
}

void addIngredient(struct player* player, int ingredient){
   switch(ingredient){
    case 1:
        player->recipe.ingredients[player->recipe.amountIng] = 1;
        player->recipe.amountIng++;
        break;

    case 2:
        player->recipe.ingredients[player->recipe.amountIng] = 2;
        player->recipe.amountIng++;
        break;
   
    case 3:
        player->recipe.ingredients[player->recipe.amountIng] = 3;
        player->recipe.amountIng++;
        break;
   
    case 4:
        player->recipe.ingredients[player->recipe.amountIng] = 4;
        player->recipe.amountIng++;
        break;

    case 5:
        player->recipe.ingredients[player->recipe.amountIng] = 5;
        player->recipe.amountIng++;
        break;
    
    case 6:
        player->recipe.ingredients[player->recipe.amountIng] = 6;
        player->recipe.amountIng++;
        break;
    }
}

void clearRecipe(int* recipe){
    for(int i = 0; i < 8; i++){
        recipe[i] = 0;
    }
}
