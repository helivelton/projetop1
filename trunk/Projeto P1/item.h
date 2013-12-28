#ifndef ITEM_H
#define ITEM_H

#include "basico.h"

void preencher_item(Titem *objeto, float x, float y, int altura, int largura, char imagem_link[255],int posicaox,int posicaoy,
                    int ativo, int tipo,int imagem_preenchida);
void desenhar_itens(BITMAP *buffer,Titens *objetos,int ajuste_x);
void verifique_efeito_item(Titens *itens,Tcriatura *guerreiro);

#endif // ITEM_H
