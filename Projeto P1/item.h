#ifndef ITEM_H
#define ITEM_H

#include "basico.h"
#include "criaturas.h"

// se id_arqueiro = 0, então não é flecha
void preencher_item(Titem *objeto, float x, float y, int altura, int largura, char imagem_link[255],int posicaox,int posicaoy,
                    int ativo, int tipo,int imagem_preenchida,int id_arqueiro);
void desenhar_itens(BITMAP *buffer,Titens *objetos,int ajuste_x);
void verifique_efeito_item(Titens *itens,Tcriatura *guerreiro,Toponentes *inimigos);

#endif // ITEM_H
