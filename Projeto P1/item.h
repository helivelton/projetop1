#ifndef ITEM_H
#define ITEM_H

#include "basico.h"

void preencher_item(Titem *objeto, float x, float y, int altura, int largura, char imagem_link[255],int posicaox,int posicaoy);
void desenhar_item(BITMAP *buffer,Titem *objeto,int mov_mapa[2]);

#endif // ITEM_H