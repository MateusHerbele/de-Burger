#include "dbheader.h"

void verifyOrder(struct player* player, int* recipe, int* numOfOrders, struct list* list){
    struct orderNode* current = list->head;
    for(int* orderSearch = 0; orderSearch <= numOfOrders; orderSearch++)
        for(int i = 0; i < 8; i++){
            if(recipe[i] != current->id->ingredients[i]){
                break;
            }
            if(i == 7){
                clearRecipe(recipe);
                player->score += current->id->score;
                removeOrderNode(list, current);
                return;
            }
        }
        //Pedido inválido
        clearRecipe(recipe);
        player->score += -10;
        printf("Pedido inválido");
}

int strLen(const char* str){
    int size = 0;
    while(*str++)
    ++size;
    return size;
}



// Get logo len
int getLogoWSize(int logoHSize, const char * const menuLogo[]){
    int logoWSize = 1;

    for (int i = 0; i < logoHSize; i++) {
        int len = strLen(menuLogo[i]);
        if (len > logoWSize) {
            logoWSize = len;
        }
    }
    return logoWSize;
}


// Draw the logo
void drawLogo(int h, int w, int logoWSize, int logoHSize, const char * const menuLogo[], int pHud){
    // Get w size
    if (logoWSize == 1) {
        logoWSize = getLogoWSize(logoHSize, menuLogo) / 2;
    }

    // Draw
    attron(COLOR_PAIR(pHud));
    for (int i = 0; i < logoHSize; i++) {
        mvprintw(3 + i /* Logo Y pos */, w/2 - logoWSize, menuLogo[i]);
    }
    attroff(COLOR_PAIR(pHud));
}

void drawMenu(int h, int w, int pHud, int logoWSize, int logoHSize, char * const menuLogo[]){
    // Draw logo
   // drawLogo(h, w, logoWSize, logoHSize, menuLogo, pHud);

    // Draw menu
    attron(COLOR_PAIR(pHud));
    mvprintw(h/2, w/2 - 5, "1 - Start");
    mvprintw(h/2 + 1, w/2 - 5, "2 - Exit");
    attroff(COLOR_PAIR(pHud));
}


// Colorindo
void setColor(int pBread, int pHamburguer, int pLettuce, int pTomato, int pCheese, int pOnion, int pDeliver, int pDiscart, int pWall) {
    start_color();
    init_pair(pBread,   COLOR_YELLOW,     COLOR_BLACK);
    init_pair(pHamburguer,  COLOR_BLACK,    COLOR_BLACK);
    init_pair(pLettuce,   COLOR_GREEN,      COLOR_BLACK);   
    init_pair(pTomato,  COLOR_RED,    COLOR_BLACK);
    init_pair(pCheese,   COLOR_YELLOW,    COLOR_BLACK);
    init_pair(pOnion, COLOR_MAGENTA,  COLOR_BLACK);
    init_pair(pDeliver, COLOR_GREEN,    COLOR_BLACK);
    init_pair(pDiscart,  COLOR_RED,      COLOR_BLACK);
    init_pair(pWall,    COLOR_WHITE,   COLOR_BLACK); 
}

void drawObject(int y, int x, int color, char name[], int w, int h){
    attron(COLOR_PAIR(color));

    // Win offset
    int oWidht = w/2;
    int oHeight = h/2;
    
    // Level offset
    int kitchenX = (27/2)*symbol_count+(27%2);
    int kitchenY = (20+(td_indent*2))/2-(1 /* +1 indent hud */+(20%2));

    mvprintw(
        /* Y pos */ ceil(oHeight - kitchenY) + (y+td_indent), 
        /* X pos */ ceil(oWidht - kitchenX) + (x*symbol_count), 
        /* S pos */ name
    );
    attroff(COLOR_PAIR(color));
}

// configurações do player
//struct player player = {.score = 0, .local = { .x = 5, .y = 6 }};
// player.score = 0;
// player.local.x = 5;
// player.local.y = 6;

// gera objetos
void genObjcts(struct object *object, int x, int y,char *skin){
    object->local.x = x;
    object->local.y = y;
    //object->dir = dir;
    strcpy(object->skin, skin);
}

void genPlayer(struct player *player, int x, int y, char *skin){
    player->local.x = x;
    player->local.y = y;
    strcpy(player->skin, skin);
}

void playerMove(int key, struct player* player, int dirX, int dirY){
    // key events
    int keyLeft;
    int keyRight;
    int keyDown;
    int keyUp;

    switch(key)
    {
    case KEY_LEFT:
        keyLeft = 1;
        break;
    case KEY_RIGHT:
        keyRight = 1;
        break;
    case KEY_DOWN:
        keyDown = 1;
        break;
    case KEY_UP:
        keyUp = 1;
        break;
    default:
        keyLeft = 0;
        keyRight = 0;
        keyDown = 0;
        keyUp = 0;
    }

    // key dir
    dirX = keyRight - keyLeft;
    dirY = keyDown  - keyUp;

    // mostra o player
    strcpy(player->skin, "&");

    player->local.hSpace = 1 * dirX;
    player->local.vSpace = 1 * dirY;

    if (player->local.hSpace != 0) {
        player->local.vSpace = 0;
    } else if (player->local.vSpace != 0) {
        player->local.hSpace = 0;
    }

    player->local.x += player->local.hSpace;
    player->local.y += player->local.vSpace;
}

void playerCollision(short kitchen[20][27], struct player* player, int* amountOfOrders, struct list* list){
    switch(kitchen[player->local.y][player->local.x]) {
        case oWall:    // parede - se ele tentar passar retorna ele pra posição anterior
            player->local.x -= player->local.hSpace;
            player->local.y -= player->local.vSpace;
        break;

        // Ingredientes
        case oBread:
            kitchen[player->local.y][player->local.x] = 0;
            player->recipe.ingredients[player->recipe.amountIng] = 1;
            player->recipe.amountIng++;
        break;
        case oHamburguer:
            kitchen[player->local.y][player->local.x] = 0;
            player->recipe.ingredients[player->recipe.amountIng] = 2;
            player->recipe.amountIng++;
        break;
        case oLettuce:
            kitchen[player->local.y][player->local.x] = 0;
            player->recipe.ingredients[player->recipe.amountIng] = 3;
            player->recipe.amountIng++;
        break;
        case oTomato:
            kitchen[player->local.y][player->local.x] = 0;
            player->recipe.ingredients[player->recipe.amountIng] = 4;
            player->recipe.amountIng++;
        break;
        case oCheese:
            kitchen[player->local.y][player->local.x] = 0;
            player->recipe.ingredients[player->recipe.amountIng] = 5;
            player->recipe.amountIng++;
        break;
        case oOnion:
            kitchen[player->local.y][player->local.x] = 0;
            player->recipe.ingredients[player->recipe.amountIng] = 6;
            player->recipe.amountIng++;
        break;
        
        // Entrega
        case oDeliver:
            kitchen[player->local.y][player->local.x] = 0;
            verifyOrder(player, player->recipe.ingredients, amountOfOrders, list); 
        break;
        // Lixo
        case oDiscart:
            kitchen[player->local.y][player->local.x] = 0;
            clearRecipe(player->recipe.ingredients);
        break;
    }
}

// gerar cozinha
void genKitchen(short kitchen[][27], struct player* player, int w, int h, int pBread, int pHamburguer, int pLettuce, int pTomato, int pCheese, int pOnion, int pWall, int pDeliver, int pDiscart, int pPlayer){
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 27; x++) {
            switch(kitchen[y][x]) {

                // Draw static object
                case oBread: 
                    drawObject(y, x, pBread,  cBread, w, h);  
                break;

                case oHamburguer: 
                    drawObject(y, x, pHamburguer,   cHamburguer, w, h);
                break;

                case oLettuce: 
                drawObject(y, x, pLettuce,  cLettuce, w, h);  
                break;

                case oTomato: 
                drawObject(y, x, pTomato,   cTomato, w, h);   
                break;

                case oCheese: 
                drawObject(y, x, pCheese,   cCheese, w, h);   
                break;

                case oOnion: 
                drawObject(y, x, pOnion,    cOnion, w, h);    
                break;

                case oWall: 
                drawObject(y, x, pWall,     cWall, w, h);     
                break;

                case oDeliver: 
                drawObject(y, x, pDeliver, cDeliver, w, h); 
                break;

                case oDiscart: 
                drawObject(y, x, pDiscart, cDiscart, w, h); 
                break;

                // Draw dynamic object
                default:

                    // Draw player
                    if (x == player->local.x && y == player->local.y) {
                        drawObject(y, x, pPlayer, player->skin, w, h);
                        break;
                    }
    
        }
    }
}
}


// gerar hud
void drawHud(int score){
    // if(player.score == 0) {
    //     mvprintw(1, 2, "Score: %d\n", player.score);
    //     return;
    // }
    mvprintw(1, 2, "Score: %d\n", score);
}

// terminar jogo
void gameOver(struct gameStates* gameStatus){

    gameStatus->STATE_GAME = OVER;
    endwin();
    printf("Game Over!\n");

}

//atualização do jogo - taxa de atualização
void gameUpdate(int key, short kitchen[][27], struct player* player, struct gameStates* gameStatus, struct list* list, int dirX, int dirY, int* amountOfOrders, int w, int h, int pBread, int pHamburguer, int pLettuce, int pTomato, int pCheese, int pOnion, int pWall, int pDeliver, int pDiscart, int pPlayer){
    //player
    playerMove(key, player, dirX, dirY);
    playerCollision(kitchen, player, amountOfOrders, list);
    //mapa
    genKitchen(kitchen, player, w, h, pBread, pHamburguer, pLettuce, pTomato, pCheese, pOnion, pWall, pDeliver, pDiscart, pPlayer);

    //chamada do game over
    if(player->score == 0){
        gameOver(gameStatus);
    }
}
