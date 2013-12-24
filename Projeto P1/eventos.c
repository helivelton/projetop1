#include "eventos.h"
#include "controle.h"

void botao_w(int *janela_atual, Tjanelas *janelas,int tempo_de_jogo)
{
    if(apertou(KEY_W)) // W controla caixa de texto. teste.
    {
        if(*janela_atual==0)
        {
            *janela_atual=1;
            janelas->total[0].tempo_inicio=tempo_de_jogo;
            janelas->total[0].tempo_fim=-1;
        }
        else if(*janela_atual==1)
        {
            *janela_atual=2;
            janelas->total[1].tempo_inicio=tempo_de_jogo;
            janelas->total[1].tempo_fim=-1;
        }
        else
            janelas->total[1].tempo_fim=tempo_de_jogo+20;
    }
}
