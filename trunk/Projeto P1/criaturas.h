#ifndef CRIATURAS_H
#define CRIATURAS_H

#include "basico.h"
#include "controle.h"
#include "mapa.h"

// Funções para todas as criaturas
void preenche_criatura(Tcriatura *ser,float x,float y,float largura, float altura,int direcao,int f,int h,int r,int a,int pdf);
int colisao_direita(float x,float y, int altura, int latguta, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
int colisao_esquerda(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
int colisao_abaixo(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
// Funções do guerreiro
void imagens_guerreiro(Tcriatura *guerreiro);
void movimento_guerreiro(Tcriatura *guerreiro,int mov_mapa[2], int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
void desenhar_guerreiro(BITMAP *buffer,Tcriatura *guerreiro);

// Funções do goblin tipo 1
void imagens_goblin1(BITMAP *im_goblin1[4]);
void movimento_goblin1(Tcriatura *goblin1,int x_guerreiro);
void desenhar_goblin1(BITMAP *buffer,Tcriatura *goblin1);

#endif // CRIATURAS_H
