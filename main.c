#include "header.h"
int main(){
    // score
    int score;
    int* p_score;
    p_score = &score;
    score = 11;
    //dados gerados
    char data;
    char* p_data;
    p_data = &data;
    // estado
    bool END = false;
    bool* p_exit;
    p_exit = &END;
    // tamanho da janela w de widht e h de heigth
    int w, h;
    w = 0;
    h = 0;
    // key event
    int keyPressed = 0;
    // player
    struct classObj player;
    struct classObj* p_player = &player;
    //incia a stack
    struct stack* p_stack = malloc(sizeof(struct stack));
    if(p_stack == NULL){
        printf("Erro: falha ao alocar memória para 'p_stack'.\n");
        exit(1);
    }
    // inicializa a stack
    p_stack->top = NULL;
    //inicia a fila
    struct queue* p_queue = malloc(sizeof(struct queue));
    if(p_queue == NULL){
        printf("Erro: falha ao alocar memória para 'p_queue'.\n");
        exit(1);
    }
    // inicializa a fila
    p_queue->first = NULL;
    p_queue->last = NULL;
        
    // funções pra startar o ncurses
    initscr(); // inicia a tela
    keypad(stdscr, TRUE); //habilita as setinhas
    savetty(); //salva o estado do terminal para depois retornar ao que estava
    cbreak(); //tira a necessidade de dar enter pra todo caractér digitado
    noecho(); //desabilita a exibição do que é digitado
    timeout(0); //possiblita a execução externa de outras tarefas sem esperar resposta do teclado
    leaveok(stdscr, TRUE);//não impede que o cursor saia da janela de execução
    curs_set(0); //desativa a exibição do cursor na execução

    actionsPlayer(h, w, keyPressed, p_score, p_queue, p_stack, p_player, p_exit, p_data);
    //int h, int w, int keyPressed, int* p_score, struct queue* p_queue, struct stack* p_stack, struct classObj* p_player, bool* END, int* p_data

    // fecha a janela do curses e da free na memoria
    endQueue(p_queue);
    endStack(p_stack);
    endwin();

    return 0;
}