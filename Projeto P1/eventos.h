#ifndef EVENTOS_H
#define EVENTOS_H

#include "basico.h"
#include "controle.h"
#include "item.h"
#include "criaturas.h"
#include "mapa.h"

void verificar_evento(int *pause,int fase,Teventos *eventos,Tcriatura *guerreiro,Tjanelas *janelas,
                      int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3],int *ajuste_mapa);

void desenhos_evento(BITMAP *buffer, int fase,Teventos *eventos,Tjanelas *janelas,Tcriatura *guerreiro,FONT* corpo_texto,
                     FONT *titulo_texto,Toponentes *inimigos);

void carregar_var_fase(int fase,Titens *itens, Tcriatura *guerreiro,Toponentes *inimigos,Tjanelas *janelas,BITMAP *background,
                       BITMAP *texturas[MAX_TERRENOS],Teventos *eventos);

void pausar(int *pause, int *selecionar);
void verifica_nova_fase(Tcriatura *guerreiro, int *fase, int *carrega_fase, int *tela, int *loading_time, int *estagio_loading,
                        int *tela_destino,Tchefes *chefes_,Teventos *eventos);

#endif // EVENTOS_H
