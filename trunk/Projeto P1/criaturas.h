#include <allegro.h>
#include "basico.h"

typedef struct criatura
{
    int x;
    int y;
    int direcao;
    int estado_sprite;
}Tcriatura;

void imagens_guerreiro(BITMAP *im_guerreiro[4]);
void preenche_guerreiro(Tcriatura *guerreiro);

