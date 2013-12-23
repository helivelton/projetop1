#include "eventos.h"
#include "controle.h"

void botao_w(int *janela_atual, Tjanela *totalJanelas,int tempo_de_jogo)
{
    if(apertou(KEY_W)) // W controla caixa de texto. teste.
    {
        if(*janela_atual==0)
        {
            *janela_atual=1;
            totalJanelas[0].tempo_inicio=tempo_de_jogo;
            totalJanelas[0].tempo_fim=-1;
        }
        else if(*janela_atual==1)
        {
            *janela_atual=2;
            totalJanelas[1].tempo_inicio=tempo_de_jogo;
            totalJanelas[1].tempo_fim=-1;
        }
        else
            totalJanelas[1].tempo_fim=tempo_de_jogo+20;
    }
}
