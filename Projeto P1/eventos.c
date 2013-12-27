#include "eventos.h"

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

void carregar_var_fase(int fase,Titens *itens, Tcriatura *guerreiro,Toponentes *inimigos,Tjanelas *janelas,BITMAP *background,
                       BITMAP *texturas[MAX_TERRENOS])
{
    BITMAP *fundo;

    if(fase==1)
    {
        preencher_item(&itens->todosItens[0],550,NIVEL_CHAO-20,20,15,"imagens_p1/Itens1.bmp",6,12,1,1,0);
        itens->n_itens=1;

        preenche_criatura(guerreiro,0,NIVEL_CHAO-34,20,34,1,2,3,2,1,0); // preenche status guerreiro
        imagens_guerreiro(guerreiro); // preenche vetor de imagens do guerreiro

        preenche_criatura(&inimigos->goblins_guerreiros.goblins[0],SCREEN_W-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[0],0); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[1],750,NIVEL_CHAO-32,28,32,2,1,2,1,0,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[1],0); // preenche vetor de imagens do goblin tipo 1
        inimigos->goblins_guerreiros.n_goblins=2;

        carrega_texturas(texturas); // prepara as texturas

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,0,"Joao","Oh, terrivel goblin esqueleto, irei mata-lo de novo, por todo o sempre.");
        preencher_janela(&janelas->total[1],70,300,0,0,0,0,0,"Joao","Irei derrota-lo com certeza.");
        janelas->n_janelas=2;

        fundo = load_bitmap(link_imagem("imagens_p1/Forest01.bmp"),NULL);
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }

    if(fase==2)
    {
        preencher_item(&itens->todosItens[0],550,NIVEL_CHAO-20,20,15,"imagens_p1/Itens1.bmp",6,12,1,1,1);
        itens->n_itens=1;

        preenche_criatura(guerreiro,0,NIVEL_CHAO-34,20,34,1,2,3,2,1,0); // preenche status guerreiro

        preenche_criatura(&inimigos->goblins_guerreiros.goblins[0],SCREEN_W-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[0],1); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[1],750,NIVEL_CHAO-32,28,32,2,1,2,1,0,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[1],1); // preenche vetor de imagens do goblin tipo 1
        inimigos->goblins_guerreiros.n_goblins=2;

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,0,"Joao","Oh, terrivel goblin esqueleto, irei mata-lo de novo, por todo o sempre.");
        preencher_janela(&janelas->total[1],70,300,0,0,0,0,0,"Joao","Irei derrota-lo com certeza.");
        janelas->n_janelas=2;

        fundo = load_bitmap(link_imagem("imagens_p1/Stone2.bmp"),NULL);
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }

    if(fase==3)
    {
        preencher_item(&itens->todosItens[0],550,NIVEL_CHAO-20,20,15,"imagens_p1/Itens1.bmp",6,12,1,1,1);
        itens->n_itens=1;

        preenche_criatura(guerreiro,0,NIVEL_CHAO-34,20,34,1,2,3,2,1,0); // preenche status guerreiro

        preenche_criatura(&inimigos->goblins_guerreiros.goblins[0],SCREEN_W-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[0],1); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[1],750,NIVEL_CHAO-32,28,32,2,1,2,1,0,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[1],1); // preenche vetor de imagens do goblin tipo 1
        inimigos->goblins_guerreiros.n_goblins=2;

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,0,"Joao","Oh, terrivel goblin esqueleto, irei mata-lo de novo, por todo o sempre.");
        preencher_janela(&janelas->total[1],70,300,0,0,0,0,0,"Joao","Irei derrota-lo com certeza.");
        janelas->n_janelas=2;

        fundo = load_bitmap(link_imagem("imagens_p1/Forest01.bmp"),NULL);
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }

    destroy_bitmap(fundo);
}
