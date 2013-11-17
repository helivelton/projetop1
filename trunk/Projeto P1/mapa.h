#include <allegro.h>
#include "basico.h"

#define MAX_TEXTURAS 13

/*
Prepara as texturas individuais.
Só é chamada uma vez no jogo.
*/
void carrega_texturas(BITMAP *texturas[MAX_TEXTURAS]);

/*
Desenha o mapa.
Chamada uma vez a cada fase.
*/
void carrega_mapa(BITMAP *mapa,BITMAP *texturas[MAX_TEXTURAS]);
