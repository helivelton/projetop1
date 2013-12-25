#ifndef MAPA_H
#define MAPA_H

#include "basico.h"

/*
Prepara as texturas individuais.
Só é chamada uma vez no jogo.
*/
void carrega_texturas(BITMAP *texturas[MAX_TERRENOS]);

/*
Prepara a matriz do mapa
*/
void prepara_mapa(int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32],char nome_mapa[10]);

/*
Desenha o mapa.
Chamada uma vez a cada fase.
*/
void carrega_mapa(BITMAP *mapa,BITMAP *texturas[MAX_TERRENOS],int matriz_tela[SCREEN_H/32][SCREEN_W/32]);

// Colisões das criaturas com o mapa
int colisao_direita(float x,float y, int altura, int latguta, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
int colisao_esquerda(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
int colisao_abaixo(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);
int colisao_cima(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3]);

#endif // MAPA_H
