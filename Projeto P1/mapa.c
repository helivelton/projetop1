#include "mapa.h"

void carrega_texturas(BITMAP *texturas[MAX_TERRENOS])
{
    int i;
    for(i=0;i<MAX_TERRENOS;i++)
    {
        texturas[i] = create_bitmap(32,32);
    }
    BITMAP *tileset=load_bitmap(link_imagem("imagens_p1/tiles01b.bmp"),NULL);// tileset b�sico
    blit(tileset,texturas[TERRA], 0*32, 0*32,0,0,32,32); //terra
    blit(tileset,texturas[CHAO], 1*32, 0*32,0,0,32,32); //ch�o
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

void prepara_mapa(int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32],char nome_mapa[10])
{
    int i=0,j=0,m;
    char carac;
    FILE* f = fopen(nome_mapa, "r");
    while((carac = getc(f)) != EOF)
    {
        // carrega tiles
        if(j<LARGURA_MAPA/32)
        {
            switch(carac)
            {
                case '0':
                    m=0;
                    break;
                case '1':
                    m=1;
                    break;
                case '2':
                    m=2;
                    break;
                case '3':
                    m=3;
                    break;
                case '4':
                    m=4;
                    break;
                case '5':
                    m=5;
                    break;
                case '6':
                    m=6;
                    break;
                case '7':
                    m=7;
                    break;
                case '8':
                    m=8;
                    break;
                case '9':
                    m=9;
                    break;
                case 'a':
                    m=10;
                    break;
                case 'b':
                    m=11;
                    break;
                case 'c':
                    m=12;
                    break;
                default:
                    m=-1;
            }
            matriz_tela[i][j]=m;
            j++;
        }
        else
        {
            i++;
            j=0;
        }
    }

    fclose(f);
}

void carrega_mapa(BITMAP *mapa,BITMAP *texturas[MAX_TERRENOS],int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32])
{
    int i,j;
    rectfill(mapa,0,0,640*5,480,makecol(127,127,127));
    for(i=0;i<ALTURA_MAPA/32;i++)
    {
        for(j=0;j<LARGURA_MAPA/32;j++)
        {
            if(matriz_tela[i][j]!=-1)
            {
                draw_sprite(mapa,texturas[matriz_tela[i][j]],j*32,i*32);
            }
        }
    }
}

