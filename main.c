#include "dbheader.h"

void verifyOrder(int* recipe, int numOfOrders, int* order){
    for(int orderSearch = 0; orderSearch <= numOfOrders; orderSearch++)
        for(int i = 0; i < 8; i++){
            if(recipe[i] != order[i]){
                break;
            }
            if(i == 8){
                clearRecipe(recipe);
                removeOrder(orderSearch);
                return;
            }
        }
        //Pedido inválido
        clearRecipe(recipe);
        printf("Pedido inválido");
}

int main(){

    return 0;
}
