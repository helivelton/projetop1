#include "item.h"

void preencher_item(Titem *objeto, float x, float y, int altura, int largura, char imagem_link[255])
{
    objeto->imagem=load_bitmap(link_imagem(imagem_link),NULL);
    objeto->x=x;
    objeto->y=y;
    objeto->altura=altura;
    objeto->largura=largura;
}
