#include "header.h"

// Essa função compara o primeiro elemento da fila com a pilha inteira
int verifyOrder(struct stack* stack, struct queue* queue){
    int i = 1;
    char* first = queueFirst(queue); // Pega o primeiro elemento da fila
    struct node* temp = stack->top; // Pega o topo da pilha
    while(temp != NULL) { // Enquanto não chegar no final da pilha
        if(temp->data == first[i]){ // Se o elemento da pilha for igual ao elemento da fila
            i++;
            temp = temp->next;// Passa para o próximo elemento da pilha
        }
        else{// Se o elemento da pilha for diferente do elemento da fila
            clearStack(stack);
            deQueue(queue);
            return 0;
        }
    }
    if(isEmptyQueue(queue) || stack->top == NULL){ // Se a fila estiver vazia ou a pilha estiver vazia
        clearStack(stack);
        deQueue(queue);
        return 0;
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
void playerCollision(short current_lvl[][13], struct classObj* player, struct stack* p_stack, struct queue* p_queue, int* areaLocker, bool* END, int* loseConditionOne, int* loseConditionTwo, int* score){
        int deliver = 0;
        
        for (int y = 0; y < 12; y++){
            for (int x = 0; x < 13; x++){
        switch(current_lvl[player->y][player->x]){
            // Collision
            case i_wall:    // wall
                player->x -= player->hsp;
                player->y -= player->vsp;
            break;
            case i_bread:    //adiciona ingrediente
             if(*areaLocker == 0){
                push(p_stack, 'P');
                *areaLocker = 1;   
                }
            break;
            case i_breadBottom:  
             if(*areaLocker == 0){
                push(p_stack, 'p');
                *areaLocker = 1;   
                }
            break;
            case i_hamburguer:    
             if(*areaLocker == 0){
                push(p_stack, 'H');
                *areaLocker = 1;   
                }
            break;
            case i_salad:    
             if(*areaLocker == 0){
                push(p_stack, 'S');
                *areaLocker = 1;   
                }
            break;
            case i_cheese:    
             if(*areaLocker == 0){
                push(p_stack, 'Q');
                *areaLocker = 1;   
                }
            break;
            case i_fries:
             if(*areaLocker == 0){
                push(p_stack, 'F');
                *areaLocker = 1;   
                }
            break;
            case i_coca:
             if(*areaLocker == 0){
                push(p_stack, 'R');
                *areaLocker = 1;   
                }
            break;
            case i_deliver:   
                    if(*areaLocker == 0){
                    deliver = verifyOrder(p_stack, p_queue);
                    if(deliver == 1){
                        *score += 1;
                        if(isEmptyQueue(p_queue)){
                            *END = true;
                            endwin();
                            printf("Você ganhou! Seu score foi de %d!\n", *score);

                        }
                    }else{
                        *loseConditionOne += 1;
                    }
                    *areaLocker = 1;
                    }                       
                    break;
            case i_discart:   
                if(*areaLocker == 0){
                    *loseConditionTwo += 1;
                    clearStack(p_stack);    
                    *areaLocker = 1;
                        }
            break;

            default:
                *areaLocker = 0;
            }
        }
    }
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
                case i_breadBottom: drawInstance(y, x, c_breadBottom, s_breadBottom, w, h); break;
                case i_salad: drawInstance(y, x, c_salad, s_salad, w, h); break;
                case i_cheese: drawInstance(y, x, c_cheese, s_cheese, w, h); break;
                case i_fries: drawInstance(y, x, c_fries, s_fries, w, h); break;
                case i_coca: drawInstance(y, x, c_coca, s_coca, w, h); break;
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
void gameUpdate(int key, short current_lvl[][13], struct stack* p_stack, struct queue* p_queue, struct classObj* player, int* dir_x, int* dir_y, int w, int h, bool* END, int* areaLocker, int* loseConditionOne, int* loseConditionTwo, int* score){
    // Player
    playerMove(key, player, dir_x, dir_y);
    playerCollision(current_lvl, player, p_stack, p_queue, areaLocker, END, loseConditionOne, loseConditionTwo, score);
    //short current_lvl[][13], struct classObj* player, struct stack* p_stack, struct queue* p_queue, int* p_score, int* areaLocker, bool* END){
    // Desenha a cozinha
    drawKitchen(current_lvl, player, w, h);

    // Game Over
    if(*loseConditionOne == 3 || *loseConditionTwo == 5)
        gameOver(END);
}

// Init lvl
void kitchenInit(struct classObj* player, struct stack* p_stack, struct queue* p_queue, int keyPressed, int* dir_x, int* dir_y, bool* END, int w, int h, int* areaLocker, int* loseConditionOne, int* loseConditionTwo, int* score){
    //matriz da cozinha
    short kitchen[12][13] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 1, 2, 2, 2, 0, 3, 3, 3, 0, 6, 6, 6, 1},
    { 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1},
    { 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1},
    { 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1},
    { 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 11,11, 0, 0, 8, 0, 9, 0, 0, 12, 12, 1},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
    static bool init = true; // primeiro inicia o player dps a cozinha 

    if(!init){
        gameUpdate(keyPressed, kitchen, p_stack, p_queue, player, dir_x, dir_y, w, h, END, areaLocker, loseConditionOne, loseConditionTwo, score);   
        return;
    }
    // Player
            player->x = 6;
            player->y = 6;
            init = false;
}

// Set color
void setColor(){
    start_color();
    init_pair(c_wall,   COLOR_WHITE,     COLOR_RED);
    init_pair(c_bread,  COLOR_YELLOW,    COLOR_BLACK);
    init_pair(c_breadBottom,  COLOR_YELLOW,    COLOR_BLACK);
    init_pair(c_hamburguer,   COLOR_RED,      COLOR_BLACK);   
    init_pair(c_salad,  COLOR_GREEN,     COLOR_BLACK);
    init_pair(c_cheese, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(c_fries, COLOR_YELLOW, COLOR_BLACK);
    init_pair(c_coca, COLOR_CYAN, COLOR_BLACK);
    init_pair(c_deliver,  COLOR_GREEN,      COLOR_BLACK);
    init_pair(c_discart,    COLOR_RED,   COLOR_BLACK);
}


void drawInstance(int y, int x, int color, char skin[], int w, int h){
    attron(COLOR_PAIR(color));

    // Win offset
    int win_xoffset = w/2;
    int win_yoffset = h/2;
    
    // Level offset
    int lvl_xoffset = (13/2)*symbol_count+(13%2);
    int lvl_yoffset = (12+(td_indent*2))/2-(1 /* +1 hud */+(12%2));

    mvprintw(
        /* Y pos */ ceil(win_yoffset - lvl_yoffset) + (y+td_indent), //função teto
        /* X pos */ ceil(win_xoffset - lvl_xoffset) + (x*symbol_count), //gunção teto
        /* S pos */ skin
    );
    attroff(COLOR_PAIR(color));
}

// Hud
void drawHud(struct queue* queue, struct stack* stack, int* numOfClients, int* loseConditionOne, int* loseConditionTwo, int* p_score, int h, int w){
    mvprintw(1, 3, "ENTREGAS ERRADAS: %d/3\n", *loseConditionOne);
    mvprintw(2, 3, "NUMERO(S) DE DESCARTE(S): %d/5", *loseConditionTwo);
    mvprintw(3, 3, "PEDIDOS: \n");
    mvprintw(4, 60, "MONTAGEM: \n" );
    mvprintw(1, 60,"SCORE: %d\n", *p_score);
    mvprintw(h-2, 2, "Pressione 'q' para restartar\n");
    printQueue(queue, numOfClients);
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
                mvprintw(h-4, w/2-ceil(x/2), "Pressione 'q' para voltar ao menu"); // ceil arrenonda pra cima

                mvprintw(h-2, 2, "Mateus Herbele");

                box(stdscr, 0, 0);
}

void actionsPlayer(int h, int w, int keyPressed, struct queue* p_queue, struct stack* p_stack, struct classObj* p_player, bool* END, char* p_data){
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
    objInit(p_player, 6 , 6, 0, "&");
    // impede que fique pegando várias vezes o mesmo elemento quando se está em uma mesma área
    int areaLocker = 0;
    int* p_areaLocker = &areaLocker;
    //impede que fique loopando na escolha
    int choiceLocker = 0;
    int digit = 0; // pra ir pegando o digito do usuário
    // direções
    int dir_x = 0;
    int dir_y = 0;
    int* p_dir_x;
    p_dir_x = &dir_x;
    int* p_dir_y;
    p_dir_y = &dir_y;
    //score do player
    int score = 0;
    int* p_score = &score;
    // número de clientes e perdidos
    int numOfClients = 0;
    int* p_numOfClients;
    p_numOfClients = &numOfClients;
    //Condições de perda
    int loseConditionOne = 0; // perder por 3 entregas erradas
    int* p_loseConditionOne = &loseConditionOne;
    int loseConditionTwo = 0; // perder por 5 descartes
    int* p_loseConditionTwo = &loseConditionTwo;
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
                if(choiceLocker == 0){
                    mvprintw(h/2, w/2 - 25, "Escolha o numero de pedidos a ser gerado(default: 10): ");
                    refresh(); // precisou desse refresh para não ficar estática a gereação da frase
                    while((digit = getch()) != vk_enter){
                        if(isdigit(digit) && digit != 42){ //evitar entrar carácter aqui e negativo, 42 na tabela asc = - (menos)
                            numOfClients = numOfClients * 10 + (digit - '0'); //pra ir fazendo a multiplicação por número adicionado
                            mvprintw(h/2, w/2 - 25, "Escolha o numero de pedidos a ser gerado(default: 10): %d", numOfClients);
                            refresh(); //mesmo motivo do de cima
                        }
                    }
                    if(numOfClients == 0) //se não escolher nada, fica com o default
                        numOfClients = 10;
                    srand(time(NULL));
                    for(int i = 0; i < numOfClients && choiceLocker == 0; i++){
                        p_data = genElements();
                        enqueue(p_queue, p_data, i+1);
                }      
                    choiceLocker = 1;
                }
                kitchenInit(p_player, p_stack, p_queue, keyPressed, p_dir_x, p_dir_y, END, w, h, p_areaLocker, p_loseConditionOne, p_loseConditionTwo, p_score);
                drawHud(p_queue, p_stack, p_numOfClients, p_loseConditionOne, p_loseConditionTwo, p_score, h, w);
 
                //
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
            score = 0;
            choiceLocker = 0;
            numOfClients = 0;
            p_player->x = 6;
            p_player->y = 6;
            loseConditionOne = 0;
            loseConditionTwo = 0;
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
