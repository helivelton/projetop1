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

void prepara_mapa(int matriz_tela[ALTURA_TELA/32][LARGURA_TELA/32])
{
    int n_matriz_tela[15][24] =
    //   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23
    {
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 0
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 1
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 2
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 3
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 4
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 5
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 6
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 7
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 8
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 9
        {-1,-1,-1,-1,-1,-1,-1, 4, 5, 6,-1,-1, 4, 5, 6,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 10
        {-1,-1,-1,-1,-1,-1,-1, 7, 8, 9,-1,-1, 7, 8, 9,-1,-1,-1,-1,-1,-1,-1,-1,-1}, // 11
        {-1,-1,-1,-1,-1, 3,-1,10,11,12,-1,-1,10,11,12,-1,-1,-1, 2,-1,-1,-1,-1,-1}, // 12
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 13
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // 14
    };
    int i,j;
    for(i=0;i<15;i++)
    {
        for(j=0;j<24;j++)
        {
            matriz_tela[i][j]=n_matriz_tela[i][j];
        }
    }
    for(i=13;i<15;i++)
    {
        for(j=24;j<LARGURA_TELA/32;j++)
        {
            if(i==13)
                matriz_tela[i][j]=1;
            if(i==14)
                matriz_tela[i][j]=0;
        }
    }
    for(i=0;i<13;i++)
    {
        for(j=24;j<LARGURA_TELA/32;j++)
            matriz_tela[i][j]=-1;
    }
    matriz_tela[12][LARGURA_TELA/32-3]=3;
}

void carrega_mapa(BITMAP *mapa,BITMAP *texturas[MAX_TERRENOS],int matriz_tela[ALTURA_TELA/32][LARGURA_TELA/32])
{
    int i,j;
    rectfill(mapa,0,0,640*5,480,makecol(127,127,127));
    for(i=0;i<ALTURA_TELA/32;i++)
    {
        for(j=0;j<LARGURA_TELA/32;j++)
        {
            if(matriz_tela[i][j]!=-1)
            {
                draw_sprite(mapa,texturas[matriz_tela[i][j]],j*32,i*32);
            }
        }
    }
}

