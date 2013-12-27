#ifndef EVENTOS_H
#define EVENTOS_H

#include "basico.h"
#include "controle.h"
#include "item.h"
#include "criaturas.h"
#include "mapa.h"

void botao_w(int *janela_atual, Tjanelas *janelas,int tempo_de_jogo);

void carregar_var_fase(int fase,Titens *itens, Tcriatura *guerreiro,Toponentes *inimigos,Tjanelas *janelas,BITMAP *background,
                       BITMAP *texturas[MAX_TERRENOS]);

#endif // EVENTOS_H
