#ifndef ITEM_H
#define ITEM_H

#include "basico.h"
#include "criaturas.h"

// se id_arqueiro = 0, ent�o n�o � flecha
void preencher_item(Titem *objeto, float x, float y, int altura, int largura,
                    int ativo, int tipo,int imagem_preenchida,int id_arqueiro,DATAFILE* graficos);
void movimento_itens(Titens *itens,Tcriatura *guerreiro,int tempo_jogo);
void desenhar_itens(BITMAP *buffer,Titens *objetos,int ajuste_x);
void verifique_efeito_item(Titens *itens,Tcriatura *guerreiro,Toponentes *inimigos,int tempo_jogo,SAMPLE *som_dano,SAMPLE* som_cura);

#endif // ITEM_H
