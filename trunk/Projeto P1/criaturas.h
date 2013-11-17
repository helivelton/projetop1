#include "basico.h"
#include "controle.h"

typedef struct criatura
{
    float x;
    float y;
    int direcao;
    int direcao_anterior;
    int estado_sprite;
    int controle_estado;
}Tcriatura;

// Funções para todas as criaturas
void preenche_criatura(Tcriatura *ser,float x,float y,int direcao,int estado_sprite);

// Funções do guerreiro
void imagens_guerreiro(BITMAP *im_guerreiro[4]);
void movimento_guerreiro(Tcriatura *guerreiro_status,int timer);
void desenhar_guerreiro(BITMAP *buffer,BITMAP *guerreiro,Tcriatura *guerreiro_status,BITMAP *im_guerreiro[4]);

// Funções do goblin tipo 1
void imagens_goblin1(BITMAP *im_goblin1[3]);
void movimento_goblin1(Tcriatura *goblin1_status,int x_guerreiro, int timer);
void desenhar_goblin1(BITMAP *buffer,BITMAP *goblin1,Tcriatura *goblin1_status,BITMAP *im_goblin1[3]);
