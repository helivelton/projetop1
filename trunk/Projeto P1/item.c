#include "item.h"

void preencher_item(Titem *objeto, float x, float y, int altura, int largura, char imagem_link[255],int posicaox,int posicaoy,
                    int ativo, int tipo)
{
    BITMAP *tiles = load_bitmap(link_imagem(imagem_link),NULL);
    objeto->imagem = create_bitmap(32,32);
    blit(tiles,objeto->imagem,posicaox*32,posicaoy*32,0,0,32,32);
    objeto->x=x;
    objeto->y=y;
    objeto->altura=altura;
    objeto->largura=largura;
    destroy_bitmap(tiles);
    objeto->tipo=tipo;
    objeto->ativo=ativo;
}

void desenhar_item(BITMAP *buffer,Titem *objeto,int mov_mapa[2])
{
    draw_sprite(buffer, objeto->imagem, objeto->x + mov_mapa[0] -(32-objeto->largura)/2,
                objeto->y - (32-objeto->altura)/2); // manda objeto para buffer
}
