#include "mapa.h"

void carrega_texturas(BITMAP *texturas[MAX_TEXTURAS])
{
    int i;
    for(i=0;i<MAX_TEXTURAS;i++)
    {
        texturas[i] = create_bitmap(32,32);
    }
    BITMAP *tileset=load_bitmap(link_imagem("imagens_p1/tiles01b.bmp"),NULL);// tileset básico
    blit(tileset,texturas[ 0], 0*32, 0*32,0,0,32,32); //terra
    blit(tileset,texturas[ 1], 1*32, 0*32,0,0,32,32); //chão
    blit(tileset,texturas[ 2], 0*32, 1*32,0,0,32,32); //pedra
    blit(tileset,texturas[ 3], 8*32, 8*32,0,0,32,32); //arvore morta
    blit(tileset,texturas[ 4], 6*32,10*32,0,0,32,32); //arvore parte 1
    blit(tileset,texturas[ 5], 7*32,10*32,0,0,32,32); //arvore parte 2
    blit(tileset,texturas[ 6], 8*32,10*32,0,0,32,32); //arvore parte 3
    blit(tileset,texturas[ 7], 6*32,11*32,0,0,32,32); //arvore parte 4
    blit(tileset,texturas[ 8], 7*32,11*32,0,0,32,32); //arvore parte 5
    blit(tileset,texturas[ 9], 8*32,11*32,0,0,32,32); //arvore parte 6
    blit(tileset,texturas[10], 6*32,12*32,0,0,32,32); //arvore parte 7
    blit(tileset,texturas[11], 7*32,12*32,0,0,32,32); //arvore parte 8
    blit(tileset,texturas[12], 8*32,12*32,0,0,32,32); //arvore parte 9
    destroy_bitmap(tileset);
}

void prepara_mapa()
{

}

void carrega_mapa(BITMAP *mapa,BITMAP *texturas[MAX_TEXTURAS])
{
    int i,j,contador;
    rectfill(mapa,0,0,640,480,makecol(127,127,127));
    for(i=0;i<20;i++)
    {
        draw_sprite(mapa,texturas[1],i*32,13*32);
        draw_sprite(mapa,texturas[0],i*32,14*32);
    }
    draw_sprite(mapa,texturas[2],18*32,12*32);
    draw_sprite(mapa,texturas[3],5*32,12*32);
    contador=4;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            draw_sprite(mapa,texturas[contador],(12+j)*32,(10+i)*32);
            contador++;
        }
    }
    contador=4;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            draw_sprite(mapa,texturas[contador],(14+j)*32,(10+i)*32);
            contador++;
        }
    }
    contador=4;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            draw_sprite(mapa,texturas[contador],(7+j)*32,(10+i)*32);
            contador++;
        }
    }
}

