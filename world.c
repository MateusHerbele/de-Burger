#include "header.h"

// Essa função compara o primeiro elemento da fila com a pilha inteira
int verifyOrder(struct stack* stack, struct queue* queue){
    int i = 0;
    char* first = queueFirst(queue); // Pega o primeiro elemento da fila
    struct node* temp = stack->top; // Pega o topo da pilha
    while(temp != NULL) { // Enquanto não chegar no final da pilha
        if(temp->data == first[i]){ // Se o elemento da pilha for igual ao elemento da fila
            i++;
            temp = temp->next;// Passa para o próximo elemento da pilha
        }
        else{// Se o elemento da pilha for diferente do elemento da fila
            clearStack(stack);
            return 0;
        }
    }
    if(isEmptyQueue(queue) || stack->top == NULL){ // Se a fila estiver vazia ou a pilha estiver vazia
        clearStack(stack);
        return 0;// Retorna 0
    } else {
        clearStack(stack);
        deQueue(queue);
        return 1;
    }
}


void playerMove(int key, struct classObj* player, int* dir_x, int* dir_y){
    // Key check
 int key_left, key_right, key_down, key_up;
    if(key == KEY_LEFT || key == 'a'){
        key_left = 1;
    }else{
        key_left = 0;
    }

    if(key == KEY_RIGHT || key == 'd'){
        key_right = 1;
    }else{
        key_right = 0;
    }

    if(key == KEY_DOWN || key == 's'){
        key_down = 1;
    }else{
        key_down = 0;
    }

    if(key == KEY_UP || key == 'w'){
        key_up = 1;
    }else{
        key_up = 0;
    }

    // direção que as teclas geram
    *dir_x = key_right - key_left; // podem ser positivas ou negativas 
    *dir_y = key_down  - key_up;

    strcpy(player->symbol, "&"); // simbolo do jogador


    player->hsp = 1 * *dir_x; //coloca na velocidade horizontal a direção que o jogador está indo. se for positivo desce e se for negativo sobe
    player->vsp = 1 * *dir_y; // se for positivo vai para direita, se for negativo vai para esquerda


    /* aqui tem o check para o player se mover uma direção por vez só
    quando a velocidade dele em uma direção é diferente de 0 a velocidade da outra direção vai pra 0*/
    if(player->hsp != 0){ 
        player->vsp = 0;
    }else if(player->vsp != 0){
        player->hsp = 0;
    }
    
    player->x += player->hsp;//atualiza a posição do jogador
    player->y += player->vsp;
}

// Collsiion
char playerCollision(short current_lvl[][13], struct classObj* player){
        for (int y = 0; y < 12; y++){
            for (int x = 0; x < 13; x++){
        switch(current_lvl[player->y][player->x]){
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

// desenha a cozinha
void drawKitchen(short kitchen[][13], struct classObj* player, int w, int h){
    for (int y = 0; y < 12; y++){
        for (int x = 0; x < 13; x++){
            switch(kitchen[y][x]){
                // desenha os objetos staticos
                case i_wall:   drawInstance(y, x, c_wall,  s_wall, w, h);  break;
                case i_hamburguer: drawInstance(y, x, c_hamburguer, s_hamburguer, w, h); break;
                case i_bread: drawInstance(y, x, c_bread, s_bread, w, h); break;
                case i_lettuce: drawInstance(y, x, c_lettuce, s_lettuce, w, h); break;
                case i_cheese: drawInstance(y, x, c_cheese, s_cheese, w, h); break;
                case i_tomato: drawInstance(y, x, c_tomato, s_tomato, w, h); break;
                case i_onion: drawInstance(y, x, c_onion, s_onion, w, h); break;
                case i_deliver: drawInstance(y, x, c_deliver, s_deliver, w, h); break;
                case i_discart: drawInstance(y, x, c_discart, s_discart, w, h); break;
                
                // desenha o player e os objetos dinamicos(no  caso só o player)
                default:
                    if(x == player->x && y == player->y){
                        drawInstance(y, x, c_player, player->symbol, w, h);
                        break;
                    }
                break;
            }
        }
    }
}
// Update game
char gameUpdate(int key, short current_lvl[][13], int* p_score, struct classObj* player, int* dir_x, int* dir_y, bool* EXIT, int w, int h){
    // Player
    playerMove(key, player, dir_x, dir_y);
    char collision = playerCollision(current_lvl, player);

    // Desenha a cozinha
    drawKitchen(current_lvl, player, w, h);

    // Game Over
    if(*p_score <= 0)
        gameOver(EXIT);

    return collision;
}

// Init lvl
char kitchenInit(struct classObj* player, int keyPressed, int* p_score, int* dir_x, int* dir_y, bool* EXIT, int w, int h){
    //matriz da cozinha
    short kitchen[12][13] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 1, 2, 2, 2, 0, 3, 3, 3, 0, 4, 4, 4, 1},
    { 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1},
    { 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1},
    { 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1},
    { 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 7, 7, 0, 0, 8, 0, 9, 0, 0, 6, 6, 1},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
    static bool init = true; // primeiro inicia o player dps a cozinha
    char required; 

    if(!init){
            required = gameUpdate(keyPressed, kitchen, p_score, player, dir_x, dir_y, EXIT, w, h);   
        return required;
    }
    // Player
            player->x = 5;
            player->y = 6;
            init = false;
            return 0;
}

// Set color
void setColor(){
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


void drawInstance(int y, int x, int color, char name[], int w, int h){
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
void drawHud(int* p_score, struct queue* queue, struct stack* stack){
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
void objInit(struct classObj *obj, int x, int y, int dir, char *objname){
    obj->x = x;
    obj->y = y;
    //obj->direction = dir;
    strcpy(obj->symbol, objname);
}
// Get char len
int strLen(char* str){
    int size = 0;
    while(*str++) ++size;
    return size;
}

// Get logo len
int getLogoWSize(int logoHSize, char** menuLogo){
    int logoWSize = 1;

    for (int i = 0; i < logoHSize; i++){
        int len = strLen(menuLogo[i]);
        if(len > logoWSize) {
            logoWSize = strLen(menuLogo[i]);
        }
    }
    return logoWSize;
}

void drawLogo(int h, int w){
     char *menuLogo[11] = {
    " /$$$$$$$                    /$$$$$$$",
    "| $$__  $$                  | $$__  $$",
    "| $$  | $$  /$$$$$$         | $$  | $$ /$$   /$$  /$$$$$$   /$$$$$$  /$$   /$$  /$$$$$$   /$$$$$$",
    "| $$  | $$ /$$__  $$ /$$$$$$| $$$$$$$ | $$  | $$ /$$__  $$ /$$__  $$| $$  | $$ /$$__  $$ /$$__  $$",
    "| $$  | $$| $$$$$$$$|______/| $$__  $$| $$  | $$| $$  |__/| $$  | $$| $$  | $$| $$$$$$$$| $$  |__/",
    "| $$  | $$| $$_____/        | $$  | $$| $$  | $$| $$      | $$  | $$| $$  | $$| $$_____/| $$",
    "| $$$$$$$/|  $$$$$$$        | $$$$$$$/|  $$$$$$/| $$      |  $$$$$$$|  $$$$$$/|  $$$$$$$| $$",
    "|_______/  |_______/        |_______/  |______/ |__/       |____  $$ |______/  |_______/|__/",
    "                                                           /$$  | $$",
    "                                                          |  $$$$$$/",
    "                                                           |______/"
};
    int logoWSize = getLogoWSize(11, menuLogo) / 2; // divide por 2 para centralizar
    // Desenha
    attron(COLOR_PAIR(c_hud));
    for (int i = 0; i < 11; i++){
        mvprintw(3 + i /* Logo Y pos */, w/2 - logoWSize, menuLogo[i]);
    }
    attroff(COLOR_PAIR(c_hud));
}

void drawInfo(int h, int w, int x, int y){
                mvprintw(h/2-y,   w/2-x, "Projeto final da materia de programacao I ");
                mvprintw(h/2-y+1, w/2-x, "Feito por Mateus Herbele");
                mvprintw(h/2-y+2, w/2-x, "Utilizado como base o projeto: https://github.com/uriid1/ascii-c-game ");
                mvprintw(h/2-y+3, w/2-x, "As teclas direcionais assim como WASD servem para mover o cozinheiro '&'");
                mvprintw(h/2-y+4, w/2-x, "Seu objetivo eh percorrer a cozinha para tentar entregar o primeiro pedido da lista");
                mvprintw(h/2-y+5, w/2-x, "Cada entrega errada subtrai 10 pontos e cada entrega certa soma 15 pontos");

                // menu
                mvprintw(h-4, w/2-ceil(x/2), "'q' to exit to menu"); // ceil arrenonda pra cima

                mvprintw(h-2, 2, "Mateus Herbele");

                box(stdscr, 0, 0);
}

void actionsPlayer(int h, int w, int keyPressed, int* p_score, struct queue* p_queue, struct stack* p_stack, struct classObj* p_player, bool* END, char* p_data){
   //verifica se tem cores
    if(!has_colors()){
        endwin();
        printf("Terminal não tem cores para uso \n");
    }
    // estados do jogo -> iniciar no menu
     int gameStates = 0;
    /*
    gameStates = 0 -> menu
    gameStates = 1 -> info
    gameStates = 2 -> game
    gameStates = 3 -> exit
    */
    // Incia o player
    objInit(p_player, 5 , 5, 0, "&");
    // impede que fique pegando várias vezes o mesmo elemento quando se está em uma mesma área
    int areaLocker = 0;
    // whats happening - o que ta acontecendo de interações no mapa
    int whap = 0;
    // pra verificar se foi entregue correto o pedido
    int deliver;
    // direções
    int dir_x = 0;
    int dir_y = 0;
    int* p_dir_x;
    p_dir_x = &dir_x;
    int* p_dir_y;
    p_dir_y = &dir_y;
    // atualiza o tempo do jogo
    int lastTime = 0;
    
    // start game
    char* itemStartGame[2] = {
        "> START GAME <",
        "start game",
    };

    // info
    char* itemInfo[2] = {
        "> INFO <",
        "info",
    };

    //  exit
    char* itemExit[2] = {
        "> EXIT <",
        "exit",
    };

    while(!*END){
        // pega as cores
        setColor();

        // pega o h e o w, essa função m,ede a tela toda e pega os valores de altura e largura e joga nas variaveis
        getmaxyx(stdscr, h, w);

        // menu
        static int menuItem = 0; //precisa ser static para não resetar a cada loop
        if(keyPressed == KEY_UP)   
            menuItem--;
        if(keyPressed == KEY_DOWN) 
            menuItem++;

        if(menuItem >= 2) menuItem = 2;
        if(menuItem <= 0) menuItem = 0;

        // no menu
        switch(gameStates){
            // Menu
            case 0:
                // Logo
                drawLogo(h, w);
                if(menuItem == 0) {
                    mvprintw(h/2 - 11 + 9, w/2 - strLen(itemStartGame[0])/2, itemStartGame[0]);
                } else {
                    mvprintw(h/2 - 11 + 9, w/2 - strLen(itemStartGame[1])/2, itemStartGame[1]);
                }

                if(menuItem == 1) {
                    mvprintw(h/2 - 11 + 11, w/2 - strLen(itemInfo[0])/2, itemInfo[0]);
                } else {
                    mvprintw(h/2 - 11 + 11, w/2 - strLen(itemInfo[1])/2, itemInfo[1]);
                }

                if(menuItem == 2) {
                    mvprintw(h/2 - 11 + 13, w/2 - strLen(itemExit[0])/2, itemExit[0]);
                } else {
                    mvprintw(h/2 - 11 + 13, w/2 - strLen(itemExit[1])/2, itemExit[1]);
                }
                mvprintw(h-2, 2, "Mateus Herbele");
                // desenha a caixa em volta de tudo
                attron(COLOR_PAIR(c_hud));
                box(stdscr, 0, 0);
                attron(COLOR_PAIR(c_hud));
                // escolha
                if(keyPressed == vk_enter){ 
                    switch(menuItem) {
                        case 0:
                            gameStates = 2;
                        break;
                        case 1:
                            gameStates = 1;
                        break;

                        case 2:
                            gameStates = 3;
                        break;
                    }
                }
            break;

            // info
            case 1:
                drawInfo(h, w, 31, 2);
            break;

            // Game
            case 2:
                whap = kitchenInit(p_player, keyPressed, p_score, p_dir_x, p_dir_y, END, w, h);
                drawHud(p_score, p_queue, p_stack);
                if(time(NULL) - lastTime >= 10){
                    lastTime = time(NULL);
                    p_data = genElements();
                    enqueue(p_queue, p_data);
                }       
                switch(whap){
                    case 'P':
                        if(areaLocker == 0){
                            push(p_stack, whap);
                            areaLocker = 1;
                        }
                    break;
                    case 'H':
                        if(areaLocker == 0){
                            push(p_stack, whap);
                            areaLocker = 1;
                        }
                    break;
                    case 'A':
                        if(areaLocker == 0){
                            push(p_stack, whap);
                            areaLocker = 1;
                        }
                    break;
                    case 'T':
                        if(areaLocker == 0){
                            push(p_stack, whap);
                            areaLocker = 1;
                        }
                    break;
                    case 'Q':
                        if(areaLocker == 0){
                            push(p_stack, whap);
                            areaLocker = 1;
                        }
                    break;
                    case 'C':
                        if(areaLocker == 0){
                            push(p_stack, whap);
                            areaLocker = 1;   
                        }
                    break;
                    case 'V':
                        if(areaLocker == 0){
                        deliver = verifyOrder(p_stack, p_queue);
                        if(deliver == 1){
                            *p_score += 15;
                        }else{
                            *p_score += -10;
                        }
                        areaLocker = 1;
                        }
                       
                    break;
                    case 'X':
                        if(areaLocker == 0){
                            *p_score += -3;
                            clearStack(p_stack);    
                            areaLocker = 1;
                        }
                    break;

                    default:
                        areaLocker = 0;
                }
                box(stdscr, 0, 0);
            break;

            // Exit
            case 3:
                endwin();
                *END = TRUE;
            break;
        }
        // volta pro menu
        if(keyPressed == 'q'){
            lastTime = time(NULL) - 11;
            *p_score = 11;
            p_player->x = 5;
            p_player->y = 6;
            clearStack(p_stack);
            clearQueue(p_queue);
            gameStates = 0;
        }
        // key events:
        keyPressed = wgetch(stdscr);
        napms(100);//  delay pra evitar pegar mais de um input nas teclas
        keyPressed = wgetch(stdscr);

        // limpa tudo
        erase();

    }
}
