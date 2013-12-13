#ifndef CRIATURAS_H
#define CRIATURAS_H

#include "basico.h"
#include "controle.h"

// Funções para todas as criaturas
void preenche_criatura(Tcriatura *ser,float x,float y,float largura, float altura,int direcao,int f,int h,int r,int a,int pdf);

// Funções do guerreiro
void imagens_guerreiro(Tcriatura *guerreiro);
void movimento_guerreiro(Tcriatura *guerreiro,int mov_mapa[2]);
void desenhar_guerreiro(BITMAP *buffer,Tcriatura *guerreiro);

// Funções do goblin tipo 1
void imagens_goblin1(BITMAP *im_goblin1[4]);
void movimento_goblin1(Tcriatura *goblin1,int x_guerreiro);
void desenhar_goblin1(BITMAP *buffer,Tcriatura *goblin1);

int colisao(float ax,float ay, float ah, float al, float bx, float by, float bh, float bl);

#endif // CRIATURAS_H
