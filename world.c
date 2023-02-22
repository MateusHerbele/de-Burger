#include "header.h"

// Essa função compara o primeiro elemento da fila com a pilha inteira
int verifyOrder(struct stack* stack, struct queue* queue){
    int i = 0;
    char* first = queueFirst(queue);
    struct node* temp = stack->top;
    while (temp != NULL) {
        if (temp->data == first[i]) {
            i++;
            temp = temp->next;
        }
        else{
            clearStack(stack);
            return 0;
        }
    }
    if (i == isEmptyQueue(queue)){
        clearStack(stack);
        return 0;
    } else {
        clearStack(stack);
        deQueue(queue);
        return 1;
    }
}


void playerMove(int key, struct classObj* player, int* dir_x, int* dir_y) {
    // Key check
 int key_left, key_right, key_down, key_up;
    if (key == KEY_LEFT || key == 'a') {
        key_left = 1;
    } else {
        key_left = 0;
    }

    if (key == KEY_RIGHT || key == 'd') {
        key_right = 1;
    } else {
        key_right = 0;
    }

    if (key == KEY_DOWN || key == 's') {
        key_down = 1;
    } else {
        key_down = 0;
    }

    if (key == KEY_UP || key == 'w') {
        key_up = 1;
    } else {
        key_up = 0;
    }

    // key dir
    *dir_x = key_right - key_left;
    *dir_y = key_down  - key_up;

    strcpy(player->symbol, "&");


    player->hsp = 1 * *dir_x;
    player->vsp = 1 * *dir_y;

    if (player->hsp != 0) {
        player->vsp = 0;
    } else if (player->vsp != 0) {
        player->hsp = 0;
    }

    player->x += player->hsp;
    player->y += player->vsp;
}

// Collsiion
char playerCollision(short current_lvl[][13], struct classObj* player) {
        for (int y = 0; y < 12; y++) {
            for (int x = 0; x < 13; x++) {
        switch(current_lvl[player->y][player->x]) {
            // Collision
            case i_wall:    // wall
                player->x -= player->hsp;
                player->y -= player->vsp;
                return 0;
            break;

            case i_bread:    //adiciona ingrediente
                return 'P';
            break;

            case i_hamburguer:    
                return 'H';
            break;

            case i_lettuce:    
                return 'A';
            break;

            case i_tomato:    
                return 'T';
            break;
            
            case i_cheese:    
                return 'Q';
            break;

            case i_onion:   
                return 'C';
            break;

            case i_deliver:   
                return 'V';
            break;

            case i_discart:   
                return 'X';
            break;

            default:
                return -1;
            }
        }
    }
    return -1;
}   

// Draw Current Level
void drawKitchen(short lvl[][13], struct classObj* player, int w, int h) {
    for (int y = 0; y < 12; y++) {
        for (int x = 0; x < 13; x++) {
            switch(lvl[y][x]) {

                // Draw static object
                case i_wall:   drawInstance(y, x, c_wall,  s_wall, w, h);  break;
                case i_hamburguer: drawInstance(y, x, c_hamburguer, s_hamburguer, w, h); break;
                case i_bread: drawInstance(y, x, c_bread, s_bread, w, h); break;
                case i_lettuce: drawInstance(y, x, c_lettuce, s_lettuce, w, h); break;
                case i_cheese: drawInstance(y, x, c_cheese, s_cheese, w, h); break;
                case i_tomato: drawInstance(y, x, c_tomato, s_tomato, w, h); break;
                case i_onion: drawInstance(y, x, c_onion, s_onion, w, h); break;
                case i_deliver: drawInstance(y, x, c_deliver, s_deliver, w, h); break;
                case i_discart: drawInstance(y, x, c_discart, s_discart, w, h); break;
                
                // Draw dynamic object
                default:

                    // Draw player
                    if (x == player->x && y == player->y) {
                        drawInstance(y, x, c_player, player->symbol, w, h);
                        break;
                    }

                break;
            }
        }
    }
}
// Update game
char gameUpdate(int key, short current_lvl[][13], int* p_score, struct classObj* player, int* dir_x, int* dir_y, bool* EXIT, int w, int h) {
    // Player
    playerMove(key, player, dir_x, dir_y);
    char collision = playerCollision(current_lvl, player);

    // Draw map
    drawKitchen(current_lvl, player, w, h);

    // Over
    if (*p_score <= 0)
        gameOver(EXIT);

    return collision;
}

// Init lvl
char kitchenInit(short index_lvl, struct classObj* player, int keyPressed, short kitchen[12][13], int* p_score, int* dir_x, int* dir_y, bool* EXIT, int w, int h){
    static bool init = true;
    char required; 

    if (!init) {
        if (index_lvl == 1) 
            required = gameUpdate(keyPressed, kitchen, p_score, player, dir_x, dir_y, EXIT, w, h);   

        
        return required;
    }

            player->x = 5;
            player->y = 6;
            init = false;
            return 0;
}

// Set color
void setColor() {
    start_color();
    init_pair(c_wall,   COLOR_WHITE,     COLOR_BLACK);
    init_pair(c_bread,  COLOR_YELLOW,    COLOR_BLACK);
    init_pair(c_hamburguer,   COLOR_RED,      COLOR_BLACK);   
    init_pair(c_lettuce,  COLOR_GREEN,    COLOR_BLACK);
    init_pair(c_tomato,   COLOR_RED,    COLOR_BLACK);
    init_pair(c_cheese, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(c_onion, COLOR_MAGENTA,    COLOR_BLACK);
    init_pair(c_deliver,  COLOR_GREEN,      COLOR_BLACK);
    init_pair(c_discart,    COLOR_RED,   COLOR_BLACK);
}


void drawInstance(int y, int x, int color, char name[], int w, int h) {
    attron(COLOR_PAIR(color));

    // Win offset
    int win_xoffset = w/2;
    int win_yoffset = h/2;
    
    // Level offset
    int lvl_xoffset = (13/2)*symbol_count+(13%2);
    int lvl_yoffset = (12+(td_indent*2))/2-(1 /* +1 indent hud */+(12%2));

    mvprintw(
        /* Y pos */ ceil(win_yoffset - lvl_yoffset) + (y+td_indent), 
        /* X pos */ ceil(win_xoffset - lvl_xoffset) + (x*symbol_count), 
        /* S pos */ name
    );
    attroff(COLOR_PAIR(color));
}

// Hud
void drawHud(int* p_score, struct queue* queue, struct stack* stack) {
    mvprintw(1, 2, "SCORE: %d\n", *p_score);
    mvprintw(2, 2, "PEDIDOS: \n");
    mvprintw(1, 25, "MONTAGEM: \n" );
    printQueue(queue);
    printStack(stack);
}

// Game Over
void gameOver(bool* EXIT){
    *EXIT = true;
    endwin();
    printf("Game Over!\n");
}

// set obj Parametrs
void objInit(struct classObj *obj, int x, int y, int dir, char *objname) {
    obj->x = x;
    obj->y = y;
    //obj->direction = dir;
    strcpy(obj->symbol, objname);
}
// Get char len
int strLen(char* str) {
    int size = 0;
    while(*str++) ++size;
    return size;
}

// Get logo len
int getLogoWSize(int logoHSize, char** menuLogo) {
    int logoWSize = 1;

    for (int i = 0; i < logoHSize; i++) {
        int len = strLen(menuLogo[i]);
        if (len > logoWSize) {
            logoWSize = strLen(menuLogo[i]);
        }
    }
    return logoWSize;
}

void drawLogo(int h, int w, int logoWSize, int logoHSize, char** menuLogo) {
    // Get w size
    
        logoWSize = getLogoWSize(logoHSize, menuLogo) / 2;
    

    // Draw
    attron(COLOR_PAIR(c_hud));
    for (int i = 0; i < logoHSize; i++) {
        mvprintw(3 + i /* Logo Y pos */, w/2 - logoWSize, menuLogo[i]);
    }
    attroff(COLOR_PAIR(c_hud));
}

