#include "dbheader.h"

int main(){
    
    int *amountOfOrders = 0;
    int countOfLoops = 0;

    int h,w;
    // definições de cor da hud
    const short pHud = 1;

// const char * const menuLogo[11] = {
//     " /$$$$$$$                    /$$$$$$$",
//     "| $$__  $$                  | $$__  $$",
//     "| $$  | $$  /$$$$$$         | $$  | $$ /$$   /$$  /$$$$$$   /$$$$$$  /$$   /$$  /$$$$$$   /$$$$$$",
//     "| $$  | $$ /$$__  $$ /$$$$$$| $$$$$$$ | $$  | $$ /$$__  $$ /$$__  $$| $$  | $$ /$$__  $$ /$$__  $$",
//     "| $$  | $$| $$$$$$$$|______/| $$__  $$| $$  | $$| $$  |__/| $$  | $$| $$  | $$| $$$$$$$$| $$  |__/",
//     "| $$  | $$| $$_____/        | $$  | $$| $$  | $$| $$      | $$  | $$| $$  | $$| $$_____/| $$",
//     "| $$$$$$$/|  $$$$$$$        | $$$$$$$/|  $$$$$$/| $$      |  $$$$$$$|  $$$$$$/|  $$$$$$$| $$",
//     "|_______/  |_______/        |_______/  |______/ |__/       |____  $$ |______/  |_______/|__/",
//     "                                                           /$$  | $$",
//     "                                                          |  $$$$$$/",
//     "                                                           |______/"
// };



// Cozinh + tabelas
short kitchen[20][27] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 0, 1, 1, 1, 0, 2, 2, 2, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1 },
    { 0, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1 },
    { 0, 0, 0, 0, 0, 7, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 1 },
    { 1, 0, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 1 }
};

// número das cores dos objetos - p de paleta pra diferenciar de c de caracteres
const short pBread = 1;
const short pHamburguer = 2;
const short pLettuce = 3;
const short pTomato = 4;
const short pCheese = 5;
const short pOnion = 6;
const short pDeliver = 7;
const short pDiscart = 8;
const short pWall = 9;
const short pPlayer = 1;

int dirX;
int dirY;

// Key event
int keyEvent = 0;

// Get logo size
//int logoHSize = sizeof(menuLogo)/sizeof(menuLogo[0]);
//int logoWSize = 1;


    // aloca de forma correta a lista
    struct list* list;
    list = createList();

    // Start curses mode
    initscr();
    keypad(stdscr, TRUE);
    savetty();
    cbreak();
    noecho();
    timeout(0);
    leaveok(stdscr, TRUE);
    curs_set(0);

    // if not support color
    if (!has_colors()) {
        endwin();
        printf("Terminal não admite cores \n");
    }

    ////////////////////
    // Enum game state
    ///////////////////
  

    //   typedef enum {
    //     STATE_MENU,
    //     STATE_INFO,
    //     STATE_GAME,
    //     STATE_EXIT,
    // } game_states;


    // Init current state
    struct gameStates* currentState;   
    //game_states current_state;
    currentState->STATE_MENU = 1;


    //////////////
    // init obj
    //////////////
    // Player
    // configurações do player
    // struct player* player = {.score = 0, .local = { .x = 5, .y = 5 }};
    // player.score = 0;
    // player.local.x = 5;
    // player.local.y = 6;
    struct player* player = malloc(sizeof(struct player));
    player->score = 10;
    player->local.x = 5;
    player->local.y = 6;
    genPlayer(player, 5 /* x pos */, 5 /* y pos */, "&");


// Temporizador
int lastTime = time(NULL);
    ////////////////
    // Main loop
    ///////////////

    // Menu item
    // Item start game
    const char *startGame[2] = {
        "> START GAME <",
        "start game",
    };

    // Item info
    const char *info[2] = {
        "> INFO <",
        "info",
    };

    // Item exit
    const char *exitGame[2] = {
        "> EXIT <",
        "exit",
    };

    while (currentState->STATE_EXIT != 1){

        // Color
        setColor(pBread, pHamburguer, pLettuce, pTomato, pCheese, pOnion, pDeliver, pDiscart, pWall);

        // Get window width & Height
        getmaxyx(stdscr, h, w);

        // Menu state
        static int menuItem = 0;
        if (keyEvent == KEY_UP)   menuItem--;
        if (keyEvent == KEY_DOWN) menuItem++;

        if (menuItem >= 2) menuItem = 2;
        if (menuItem <= 0) menuItem = 0;

        // In menu state
        if (currentState->STATE_MENU == 1) {
            // Logo
           // drawLogo(h, w, logoWSize, logoHSize, menuLogo, pHud);

            ///////////
            // Items
            //////////
            // Item start game
          int selectStartGame;
            if (menuItem == 0) {
                selectStartGame = 0;
            } else {
                selectStartGame = 1;
            }
            //mvprintw(h/2 - logoHSize + 9, w/2 - strLen(startGame[selectStartGame])/2, startGame[selectStartGame]);

            int selectInfo;
            if (menuItem == 1) {
                selectInfo = 0;
            } else {
                selectInfo = 1;
            }
            //mvprintw(h/2 - logoHSize + 11, w/2 - strLen(info[selectInfo])/2, info[selectInfo]);

            int selectExit;
            if (menuItem == 2) {
                selectExit = 0;
            } else {
                selectExit = 1;
            }
            //mvprintw(h/2 - logoHSize + 13, w/2 - strLen(exitGame[selectExit])/2, exitGame[selectExit]);

            // By dev
            mvprintw(h-2, 2, "Develop: uriid1");

            // Draw box
            attron(COLOR_PAIR(pHud));
            box(stdscr, 0, 0);
            attron(COLOR_PAIR(pHud));

            // Click handler
            if (keyEvent == keyEnter) { 
                switch(menuItem) {
                    case 0:
                        currentState->STATE_GAME = 1;
                        currentState->STATE_MENU = 0;
                    break;

                    case 1:
                        // Info page is dev
                        currentState->STATE_INFO = 1;
                        currentState->STATE_MENU = 0;
                    break;

                    case 2:
                        currentState->STATE_EXIT = 1;
                        currentState->STATE_MENU = 0;
                    break;
                }
            }
        }
        if(currentState->STATE_INFO == 1){
            currentState->STATE_MENU = 0;
            static int len_xoff = 31;
            static int len_yoff = 2;
            mvprintw(h/2-len_yoff,   w/2-len_xoff, "Mateus Herbele - Trabalho final ");
            mvprintw(h/2-len_yoff+1, w/2-len_xoff, "Programação de computadores I");

            // To menu
            mvprintw(h-4, w/2-ceil(len_xoff/2), "Pressione Q para sair do menu");

            // By dev
            mvprintw(h-2, 2, "Desenvolvido por: Mateus Herbele");

            box(stdscr, 0, 0);
        }
        if(currentState->STATE_GAME == 1){
            currentState->STATE_MENU = 0;
            // Limpa a tela
           // clear();
           if(countOfLoops == 0){
                genKitchen(kitchen, player, w, h, pBread, pHamburguer, pLettuce, pTomato, pCheese, pOnion, pDeliver, pDiscart, pWall, pPlayer);
                //drawHud(player.score);
                countOfLoops++;
            }
            drawHud(player->score);
            if(time(NULL) - lastTime > 15){
                struct order* newOrder = createOrder();
                struct orderNode* newNode = createNode(amountOfOrders, newOrder, amountOfOrders);
                addOrderNode(list, newNode);
                sortTime(list->head);
                lastTime = time(NULL);
                gameUpdate(keyEvent,kitchen,player, currentState, list, dirX, dirY, amountOfOrders, w, h, pBread, pHamburguer, pLettuce, pTomato, pCheese, pOnion, pWall, pDeliver, pDiscart, pPlayer);
            }
            
        }

        if(currentState->STATE_EXIT == 1){
            // Limpa a tela
            clear();
            endwin();
            exit(1);
        }

        // Exit to menu
        if (keyEvent == 'q')
            currentState->STATE_MENU = 1;

        // Get key pressed
        keyEvent = wgetch(stdscr);
        napms(100);
        keyEvent = wgetch(stdscr);

        // Clear
        erase();

    }

    // End curses mode
    endwin();
    return 0;
}
