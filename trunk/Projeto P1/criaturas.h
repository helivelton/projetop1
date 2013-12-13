#ifndef CRIATURAS_H
#define CRIATURAS_H

#include "basico.h"
#include "controle.h"

// Fun��es para todas as criaturas
void preenche_criatura(Tcriatura *ser,float x,float y,float largura, float altura,int direcao,int f,int h,int r,int a,int pdf);

// Fun��es do guerreiro
void imagens_guerreiro(Tcriatura *guerreiro);
void movimento_guerreiro(Tcriatura *guerreiro,int mov_mapa[2]);
void desenhar_guerreiro(BITMAP *buffer,Tcriatura *guerreiro);

// Fun��es do goblin tipo 1
void imagens_goblin1(BITMAP *im_goblin1[4]);
void movimento_goblin1(Tcriatura *goblin1,int x_guerreiro);
void desenhar_goblin1(BITMAP *buffer,Tcriatura *goblin1);

#endif // CRIATURAS_H
