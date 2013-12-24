#ifndef CRIATURAS_H
#define CRIATURAS_H

#include "basico.h"
#include "controle.h"

// Funções para todas as criaturas
void preenche_criatura(Tcriatura *ser,float x,float y,float largura, float altura,int direcao,int f,int h,int r,int a,int pdf);
int colisao_direita(float x,float y, int altura, int latguta, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
int colisao_esquerda(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
int colisao_abaixo(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
int colisao_cima(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
int dano_ataque(Tcriatura* atacante, int tipo_ataque);
void calcular_dano(Tcriatura* atacante, Tcriatura* alvo,int tipo_ataque);

// Funções do guerreiro
void imagens_guerreiro(Tcriatura *guerreiro);
void movimento_guerreiro(Tcriatura *guerreiro,int mov_mapa[2], int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
void ataque_guerreiro(Tcriatura *guerreiro,int tempo_jogo,Toponentes *inimigos, int mov_mapa[2]);
void desenhar_guerreiro(BITMAP *buffer,Tcriatura *guerreiro);

// Funções do goblin tipo 1
void imagens_goblin1(Tcriatura *goblin1);
void movimento_goblin1(Tcriatura *goblin1,int x_guerreiro,int tempo_jogo);
void desenhar_goblin1(BITMAP *buffer,Tcriatura *goblin1);

#endif // CRIATURAS_H