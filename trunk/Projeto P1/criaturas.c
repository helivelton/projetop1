#include "criaturas.h"

void imagens_guerreiro(BITMAP *im_guerreiro[4])
{
    int i;
    for(i=0;i<4;i++)
    {
        im_guerreiro[i]=create_bitmap(32,48);
    }
    BITMAP *tiles = load_bitmap(link_imagem("imagens_p1/hero.bmp"),NULL);
    blit(tiles,im_guerreiro[0],0,0,0,0,32,48);
    blit(tiles,im_guerreiro[1],32,0,0,0,32,48);
    blit(tiles,im_guerreiro[2],2*32,0,0,0,32,48);
    blit(tiles,im_guerreiro[3],3*32,0,0,0,32,48);

    destroy_bitmap(tiles);
}

void preenche_guerreiro(Tcriatura *guerreiro)
{
    guerreiro->x=30;
    guerreiro->y=12*32+(32-ALTURA_GUERREIRO);
    guerreiro->direcao=1;
    guerreiro->estado_sprite=0;
}
