#include "header.h"

int main(){

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
    //logo
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
    // pega o tamanho da logo
    int logoHSize = sizeof(menuLogo)/sizeof(menuLogo[0]);
    int logoWSize = 1;


    // score
    int score;
    int* p_score;
    p_score = &score;
    score = 11;

    //dados gerados
    char data;
    char* p_data;
    p_data = &data;

    //contagem do tempo
    int last_time = 0;

    // bloqueia repetitivas somas na mesma área
    int areaLocker = 0;

    // estado
    bool END = false;
    bool* p_exit;
    p_exit = &END;

    // tamanho da janela w de widht e h de heigth
    int w, h;

    // key event
    int keyPressed = 0;
    
    // player
    struct classObj player;
    struct classObj* p_player = &player;
    int dir_x = 0;
    int dir_y = 0;
    int* p_dir_x;
    p_dir_x = &dir_x;
    int* p_dir_y;
    p_dir_y = &dir_y;

    
    char whap = 0; // whats happening
    int deliver; // pra verificar se foi entregue correto o pedido
    
    //incia a stack
    struct stack* p_stack = (struct stack*)malloc(sizeof(struct stack));
    if (p_stack == NULL) {
        printf("Erro: falha ao alocar memória para 'p_stack'.\n");
        exit(1);
    }

    // inicializa a stack
    p_stack->top = NULL;

    //inicia a fila
    struct queue* p_queue = (struct queue*)malloc(sizeof(struct queue));
    if (p_queue == NULL) {
        printf("Erro: falha ao alocar memória para 'p_queue'.\n");
        exit(1);
    }

    // inicializa a fila
    p_queue->first = NULL;
    p_queue->last = NULL;
        


    // Start curses mode
    initscr(); // inicia a tela
    keypad(stdscr, TRUE); //habilita as setinhas
    savetty(); //salva o estado do terminal para depois retornar ao que estava
    cbreak(); //tira a necessidade de dar enter pra todo caractér digitado
    noecho(); //desabilita a exibição do que é digitado
    timeout(0); //possiblita a execução externa de outras tarefas sem esperar resposta do teclado
    leaveok(stdscr, TRUE);//não impede que o cursor saia da janela de execução
    curs_set(0); //desativa a exibição do cursor na execução

    //verifica se tem cores
    if (!has_colors()) {
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

    while(!END){

        // pega as cores
        setColor();

        // pega o h e o w, essa função m,ede a tela toda e pega os valores de altura e largura e joga nas variaveis
        getmaxyx(stdscr, h, w);

        // menu
        static int menuItem = 0; //precisa ser static para não resetar a cada loop
        if (keyPressed == KEY_UP)   
            menuItem--;
        if (keyPressed == KEY_DOWN) 
            menuItem++;

        if (menuItem >= 2) menuItem = 2;
        if (menuItem <= 0) menuItem = 0;

        // no menu
        switch(gameStates){
            // Menu
            case 0:
                // Logo
                drawLogo(h, w, logoHSize, logoWSize, menuLogo);
                if (menuItem == 0) {
                    mvprintw(h/2 - logoHSize + 9, w/2 - strLen(itemStartGame[0])/2, itemStartGame[0]);
                } else {
                    mvprintw(h/2 - logoHSize + 9, w/2 - strLen(itemStartGame[1])/2, itemStartGame[1]);
                }

                if (menuItem == 1) {
                    mvprintw(h/2 - logoHSize + 11, w/2 - strLen(itemInfo[0])/2, itemInfo[0]);
                } else {
                    mvprintw(h/2 - logoHSize + 11, w/2 - strLen(itemInfo[1])/2, itemInfo[1]);
                }

                if (menuItem == 2) {
                    mvprintw(h/2 - logoHSize + 13, w/2 - strLen(itemExit[0])/2, itemExit[0]);
                } else {
                    mvprintw(h/2 - logoHSize + 13, w/2 - strLen(itemExit[1])/2, itemExit[1]);
                }


                mvprintw(h-2, 2, "Mateus Herbele");

                // desenha a caixa em volta de tudo
                attron(COLOR_PAIR(c_hud));
                box(stdscr, 0, 0);
                attron(COLOR_PAIR(c_hud));

                // escolha
                if (keyPressed == vk_enter) { 
                    switch(menuItem) {
                        case 0:
                            gameStates = 2;
                        break;

                        case 1:
                            // Info page is dev
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
                int len_xoff = 31;
                int len_yoff = 2;
                mvprintw(h/2-len_yoff,   w/2-len_xoff, "Projeto final da materia de programacao I ");
                mvprintw(h/2-len_yoff+1, w/2-len_xoff, "Feito por Mateus Herbele");
                mvprintw(h/2-len_yoff+2, w/2-len_xoff, "Utilizado como base o projeto: https://github.com/uriid1/ascii-c-game ");
                mvprintw(h/2-len_yoff+3, w/2-len_xoff, "As teclas direcionais assim como WASD servem para mover o cozinheiro '&'");
                mvprintw(h/2-len_yoff+4, w/2-len_xoff, "Seu objetivo eh percorrer a cozinha para tentar entregar o primeiro pedido da lista");
                mvprintw(h/2-len_yoff+5, w/2-len_xoff, "Cada entrega errada subtrai 10 pontos e cada entrega certa soma 15 pontos");

                // menu
                mvprintw(h-4, w/2-ceil(len_xoff/2), "'q' to exit to menu"); // ceil arrenonda pra cima

                mvprintw(h-2, 2, "Mateus Herbele");

                box(stdscr, 0, 0);
            break;

            // Game
            case 2:
                whap = kitchenInit(1, p_player, keyPressed, kitchen, p_score, p_dir_x, p_dir_y, p_exit, w, h);
                drawHud(p_score, p_queue, p_stack);
                if(time(NULL) - last_time > 15){
                    last_time = time(NULL);
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
                END = TRUE;
            break;
        }

        // volta pro menu
        if (keyPressed == 'q')
            gameStates = 0;

        // key events:
        keyPressed = wgetch(stdscr);
        napms(100);//  delay pra evitar pegar mais de um input nas teclas
        keyPressed = wgetch(stdscr);

        // limpa tudo
        erase();

    }

    // fecha a janela do curses e da free na memoria
    endQueue(p_queue);
    endStack(p_stack);
    endwin();

    return 0;
}