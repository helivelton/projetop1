#ifndef MAPA_H
#define MAPA_H

#include "basico.h"

enum{
TERRA,
CHAO,
PEDRA,
ARVORE_MORTA,
ARVORE_1,
ARVORE_2,
ARVORE_3,
ARVORE_4,
ARVORE_5,
ARVORE_6,
ARVORE_7,
ARVORE_8,
ARVORE_9,
MAX_TERRENOS
};

/*
Prepara as texturas individuais.
Só é chamada uma vez no jogo.
*/
void carrega_texturas(BITMAP *texturas[MAX_TERRENOS]);

/*
Prepara a matriz do mapa
*/
void prepara_mapa(int matriz_tela[SCREEN_H/32][SCREEN_W/32]);

/*
Desenha o mapa.
Chamada uma vez a cada fase.
*/
void carrega_mapa(BITMAP *mapa,BITMAP *texturas[MAX_TERRENOS],int matriz_tela[SCREEN_H/32][SCREEN_W/32]);

#endif // MAPA_H
