#include "mapa.h"

void carrega_texturas(BITMAP *texturas[MAX_TERRENOS])
{
    int i;
    for(i=0;i<MAX_TERRENOS;i++)
    {
        texturas[i] = create_bitmap(32,32);
    }
    BITMAP *tileset=load_bitmap(link_imagem("imagens_p1/tiles01b.bmp"),NULL);// tileset básico
    blit(tileset,texturas[TERRA], 0*32, 0*32,0,0,32,32); //terra
    blit(tileset,texturas[CHAO], 1*32, 0*32,0,0,32,32); //chão
    blit(tileset,texturas[PEDRA], 0*32, 1*32,0,0,32,32); //pedra
    blit(tileset,texturas[ARVORE_MORTA], 8*32, 8*32,0,0,32,32); //arvore morta
    blit(tileset,texturas[ARVORE_1], 6*32,10*32,0,0,32,32); //arvore parte 1
    blit(tileset,texturas[ARVORE_2], 7*32,10*32,0,0,32,32); //arvore parte 2
    blit(tileset,texturas[ARVORE_3], 8*32,10*32,0,0,32,32); //arvore parte 3
    blit(tileset,texturas[ARVORE_4], 6*32,11*32,0,0,32,32); //arvore parte 4
    blit(tileset,texturas[ARVORE_5], 7*32,11*32,0,0,32,32); //arvore parte 5
    blit(tileset,texturas[ARVORE_6], 8*32,11*32,0,0,32,32); //arvore parte 6
    blit(tileset,texturas[ARVORE_7], 6*32,12*32,0,0,32,32); //arvore parte 7
    blit(tileset,texturas[ARVORE_8], 7*32,12*32,0,0,32,32); //arvore parte 8
    blit(tileset,texturas[ARVORE_9], 8*32,12*32,0,0,32,32); //arvore parte 9
    destroy_bitmap(tileset);
}

void prepara_mapa(int matriz_tela[SCREEN_H/32][SCREEN_W/32])
{
    int i,j,contador;
    for(i=0;i<SCREEN_H/32;i++)
    {
        for(j=0;j<SCREEN_W/32;j++)
        {
            matriz_tela[i][j]=-1;
        }
    }
    for(i=0;i<20;i++)
    {
        matriz_tela[13][i]=CHAO;
        matriz_tela[14][i]=TERRA;
    }
    matriz_tela[12][18]=PEDRA;
    matriz_tela[12][5]=ARVORE_MORTA;
    contador=4;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            matriz_tela[10+i][11+j]=contador;
            contador++;
        }
    }
    contador=4;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            matriz_tela[10+i][14+j]=contador;
            contador++;
        }
    }
    contador=4;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            matriz_tela[10+i][7+j]=contador;
            contador++;
        }
    }
}

void carrega_mapa(BITMAP *mapa,BITMAP *texturas[MAX_TERRENOS],int matriz_tela[SCREEN_H/32][SCREEN_W/32])
{
    int i,j;
    rectfill(mapa,0,0,640,480,makecol(127,127,127));
    for(i=0;i<SCREEN_H/32;i++)
    {
        for(j=0;j<SCREEN_W/32;j++)
        {
            if(matriz_tela[i][j]!=-1)
            {
                draw_sprite(mapa,texturas[matriz_tela[i][j]],j*32,i*32);
            }
        }
    }
}

