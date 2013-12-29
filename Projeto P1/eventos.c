#include "eventos.h"

void verificar_evento(int *pause,int fase,Teventos *eventos,Tcriatura *guerreiro,Tjanelas *janelas,
                      int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{
    // eventos da primeira fase
    if(fase==1)
    {
        // evento 1
        if(!eventos->eventos_executados[0] &&
           (guerreiro->x>=100 || eventos->evento_atual==1))
        {
            // trava o evento atual e pausa o jogo
            if(!eventos->evento_atual)
            {
                eventos->evento_atual=1;
                eventos->tempo_evento_atual=timer;
            }

            if(*pause==0)
                *pause=1;

            // faz o guerreiro cair e andar um pouco
            if(eventos->tempo_evento_atual+60>=timer)
            {
                guerreiro->pulando=0;
                guerreiro->caindo=1;
                guerreiro->permitir_pulo=1;
                colide_chao(guerreiro,matriz_tela,bloqueios,1);
                verificar_queda(guerreiro,matriz_tela,bloqueios);
                movimento_direita(guerreiro,1,matriz_tela,bloqueios,1,1,0,3);
            }

            // agora chama janela com texto
            if(janelas->janela_atual==0 && janelas->total[1].tempo_fim==-1 && timer>=eventos->tempo_evento_atual+60)
            {
                janelas->janela_atual=1;
                janelas->total[0].tempo_inicio=timer;
                janelas->total[0].tempo_fim=-1;
            }

            if((apertou(KEY_ENTER)||apertou(KEY_SPACE)) && timer>=eventos->tempo_evento_atual+60)
            {
                if(janelas->janela_atual==1)
                {
                    janelas->janela_atual=2;
                    janelas->total[1].tempo_inicio=timer;
                    janelas->total[1].tempo_fim=-1;
                }
                else if(janelas->janela_atual==2 && janelas->total[1].tempo_fim==-1)
                    janelas->total[1].tempo_fim=timer+20;
            }
            // agora a condição de saída é janelas->janela_atual==0
            if(janelas->janela_atual==0  && timer>=eventos->tempo_evento_atual+60)
            {
                eventos->evento_atual=0;
                eventos->eventos_executados[0]=1;
                *pause=0;
            }
        }
    }
    else if(fase==2)
    {
        // evento 1
        if(!eventos->eventos_executados[0] &&
           (guerreiro->x>=100 || eventos->evento_atual==1))
        {
            // trava o evento atual e pausa o jogo
            if(!eventos->evento_atual)
                eventos->evento_atual=1;

            if(*pause==0)
                *pause=1;

            // agora chama janela com texto
            if(janelas->janela_atual==0 && janelas->total[0].tempo_fim==-1)
            {
                janelas->janela_atual=1;
                janelas->total[0].tempo_inicio=timer;
                janelas->total[0].tempo_fim=-1;
            }

            if(apertou(KEY_ENTER)||apertou(KEY_SPACE))
            {
                if(janelas->janela_atual==1 && janelas->total[0].tempo_fim==-1)
                    janelas->total[0].tempo_fim=timer+20;
            }
            // agora a condição de saída é janelas->janela_atual==0
            if(janelas->janela_atual==0)
            {
                eventos->evento_atual=0;
                eventos->eventos_executados[0]=1;
                *pause=0;
            }
        }
    }
    else if(fase==3)
    {
        // evento 1
        if(!eventos->eventos_executados[0] &&
           (guerreiro->x>=100 || eventos->evento_atual==1))
        {
            // trava o evento atual e pausa o jogo
            if(!eventos->evento_atual)
                eventos->evento_atual=1;

            if(*pause==0)
                *pause=1;

            // agora chama janela com texto
            if(janelas->janela_atual==0 && janelas->total[0].tempo_fim==-1)
            {
                janelas->janela_atual=1;
                janelas->total[0].tempo_inicio=timer;
                janelas->total[0].tempo_fim=-1;
            }

            if(apertou(KEY_ENTER)||apertou(KEY_SPACE))
            {
                if(janelas->janela_atual==1 && janelas->total[0].tempo_fim==-1)
                    janelas->total[0].tempo_fim=timer+20;
            }
            // agora a condição de saída é janelas->janela_atual==0
            if(janelas->janela_atual==0)
            {
                eventos->evento_atual=0;
                eventos->eventos_executados[0]=1;
                *pause=0;
            }
        }
    }
}

void desenhos_evento(BITMAP *buffer, int fase,Teventos *eventos,Tjanelas *janelas,Tcriatura *guerreiro,FONT* corpo_texto,
                     FONT *titulo_texto)
{
    // eventos da primeira fase
    if(fase==1)
    {
        // primeiro evento
        if(eventos->evento_atual==1)
        {
            if(janelas->janela_atual==1) // teste de janela
            {
                janela_dialogo(buffer,guerreiro,janelas->total[0].x,janelas->total[0].y,titulo_texto,corpo_texto,
                               janelas->total[0].tempo_inicio,janelas->total[0].tempo_fim,timer,janelas->total[0].titulo,
                               janelas->total[0].conteudo,1);
                if(timer==janelas->total[0].tempo_fim)
                    janelas->janela_atual=0;
            }
            else if(janelas->janela_atual==2)
            {
                janela_dialogo(buffer,guerreiro,janelas->total[1].x,janelas->total[1].y,titulo_texto,corpo_texto,
                               janelas->total[1].tempo_inicio,janelas->total[1].tempo_fim,timer,janelas->total[1].titulo,
                               janelas->total[1].conteudo,0);
                if(timer==janelas->total[1].tempo_fim)
                    janelas->janela_atual=0;
            }
        }
    }
    else if(fase==2)
    {
        // primeiro evento
        if(eventos->evento_atual==1)
        {
            if(janelas->janela_atual==1) // teste de janela
            {
                janela_dialogo(buffer,guerreiro,janelas->total[0].x,janelas->total[0].y,titulo_texto,corpo_texto,
                               janelas->total[0].tempo_inicio,janelas->total[0].tempo_fim,timer,janelas->total[0].titulo,
                               janelas->total[0].conteudo,1);
                if(timer==janelas->total[0].tempo_fim)
                    janelas->janela_atual=0;
            }
        }
    }
    else if(fase==3)
    {
        // primeiro evento
        if(eventos->evento_atual==1)
        {
            if(janelas->janela_atual==1) // teste de janela
            {
                janela_dialogo(buffer,guerreiro,janelas->total[0].x,janelas->total[0].y,titulo_texto,corpo_texto,
                               janelas->total[0].tempo_inicio,janelas->total[0].tempo_fim,timer,janelas->total[0].titulo,
                               janelas->total[0].conteudo,1);
                if(timer==janelas->total[0].tempo_fim)
                    janelas->janela_atual=0;
            }
        }
    }
}

void carregar_var_fase(int fase,Titens *itens, Tcriatura *guerreiro,Toponentes *inimigos,Tjanelas *janelas,BITMAP *background,
                       BITMAP *texturas[MAX_TERRENOS],Teventos *eventos)
{
    int i;
    BITMAP *fundo;

    for(i=0;i<3;i++)
        eventos->eventos_executados[i]=0;

    eventos->evento_atual=0;

    if(fase==1)
    {
        eventos->n_eventos=2;

        preencher_item(&itens->todosItens[0],550,NIVEL_CHAO-20,20,15,1,1,0,0);
        preencher_item(&itens->todosItens[1],0,0,8,15,0,2,0,1);
        preencher_item(&itens->todosItens[2],0,0,8,15,0,2,0,2);
        itens->n_itens=3;

        preenche_criatura(guerreiro,0,NIVEL_CHAO-34,20,34,1,2,3,2,1,0,-16,-4,20,25,4,0); // preenche status guerreiro
        imagens_guerreiro(guerreiro); // preenche vetor de imagens do guerreiro

        preenche_criatura(&inimigos->goblins_guerreiros.goblins[0],SCREEN_W-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[0],0); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[1],750,NIVEL_CHAO-32,28,32,2,1,2,1,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[1],0); // preenche vetor de imagens do goblin tipo 1
        inimigos->goblins_guerreiros.n_goblins=2;

        preenche_criatura(&inimigos->goblins_arqueiros.goblins[0],1020,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,2);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[0],0);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[1],1520,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,3);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[1],0);
        inimigos->goblins_arqueiros.n_goblins=2;

        preenche_criatura(&inimigos->chefes.chefe[0],LARGURA_MAPA-150,NIVEL_CHAO-32,28,32,2,3,3,2,2,2,-19,0,19,26,2,0);
        imagens_goblin_chefe(&inimigos->chefes.chefe[0],0);
        inimigos->chefes.chefe_atual=1;

        carrega_texturas(texturas); // prepara as texturas

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,-1,"Heroi","Droga, me perdi nesta maldita floresta infestada de goblins.");
        preencher_janela(&janelas->total[1],70,300,0,0,0,0,-1,"Heroi","Agora tenho de sair daqui...");
        janelas->janela_atual=0;
        janelas->n_janelas=2;

        fundo = load_bitmap(link_imagem("imagens_p1/Forest01.bmp"),NULL);
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }

    if(fase==2)
    {
        // destruição dos bitmaps da fase anterior
        // ****

        eventos->n_eventos=1;
        inimigos->chefes.chefe_atual=0;

        preencher_item(&itens->todosItens[0],550,NIVEL_CHAO-20,20,15,0,1,1,0);
        itens->n_itens=1;

        preenche_criatura(guerreiro,0,NIVEL_CHAO-34,20,34,1,2,3,2,1,0,-16,-4,20,25,4,0); // preenche status guerreiro

        preenche_criatura(&inimigos->goblins_guerreiros.goblins[0],SCREEN_W-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[0],1); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[1],750,NIVEL_CHAO-32,28,32,2,1,2,1,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[1],1); // preenche vetor de imagens do goblin tipo 1
        inimigos->goblins_guerreiros.n_goblins=2;
        inimigos->goblins_arqueiros.n_goblins=0;

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,-1,"Heroi","Hum...");
        janelas->janela_atual=0;
        janelas->n_janelas=1;

        fundo = load_bitmap(link_imagem("imagens_p1/Stone2.bmp"),NULL);
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }

    if(fase==3)
    {
        // destruição dos bitmaps da fase anterior
        // ****

        eventos->n_eventos=1;
        inimigos->chefes.chefe_atual=0;

        preencher_item(&itens->todosItens[0],550,NIVEL_CHAO-20,20,15,0,1,1,0);
        itens->n_itens=1;

        preenche_criatura(guerreiro,0,NIVEL_CHAO-34,20,34,1,2,3,2,1,0,-16,-4,20,25,4,0); // preenche status guerreiro

        preenche_criatura(&inimigos->goblins_guerreiros.goblins[0],SCREEN_W-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[0],1); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[1],750,NIVEL_CHAO-32,28,32,2,1,2,1,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[1],1); // preenche vetor de imagens do goblin tipo 1
        inimigos->goblins_guerreiros.n_goblins=2;
        inimigos->goblins_arqueiros.n_goblins=0;

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,-1,"Heroi","Agora estou mais proximo de sair desse lugar horrivel.");
        janelas->janela_atual=0;
        janelas->n_janelas=1;

        fundo = load_bitmap(link_imagem("imagens_p1/Forest01.bmp"),NULL);
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }

    destroy_bitmap(fundo);
}

void pausar(int *pause, int *selecionar)
{
    if (apertou(KEY_ESC))
    {
        if (*pause == TRUE)
            *pause = FALSE;
        else
            *pause = TRUE;
        if(*selecionar!=0 && *pause==TRUE)
            *selecionar=0;
    }
}

void verifica_nova_fase(Tcriatura *guerreiro, int *fase, int *carrega_fase, int *tela, int *loading_time, int *estagio_loading,
                        int *tela_destino)
{
    if(guerreiro->x +guerreiro->largura >= LARGURA_MAPA-50 && *fase<N_FASES)
    {
        *carrega_fase=1;
        *fase=*fase+1;
        *tela=9; // a próxima tela será a de loading game
        *loading_time = timer;
        *estagio_loading=0;
        *tela_destino=1;
    }
}
