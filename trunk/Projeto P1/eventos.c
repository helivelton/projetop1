#include "eventos.h"

void verificar_evento(int *pause,int fase,Teventos *eventos,Tcriatura *guerreiro,Tjanelas *janelas,
                      int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3],int *ajuste_mapa,
                      MIDI* musica_boss1,MIDI* musica_boss2,MIDI*musica_boss3,SAMPLE *confirmar)
{
    int i;
    for(i=0;i<eventos->n_eventos;i++)
    {
        if(!eventos->eventos_executados[i] &&
           (guerreiro->x >= eventos->posicaoX_guerreiro[i] || eventos->evento_atual == i+1))
        {

            // trava o evento atual e pausa o jogo
            if(!eventos->evento_atual)
            {
                // diminui volume
                set_volume(volume-100,volume-100);

                eventos->evento_atual=i+1;
                eventos->tempo_evento_atual=timer;
            }

            if(*pause==0)
                *pause=1;

            // faz o guerreiro cair e andar um pouco
            if(eventos->tempo_evento_atual + eventos->tempo_movimento_guerreiro[i] >= timer)
            {
                guerreiro->pulando=0;
                guerreiro->caindo=1;
                guerreiro->permitir_pulo=1;
                colide_chao(guerreiro,matriz_tela,bloqueios,1);
                verificar_queda(guerreiro,matriz_tela,bloqueios);
                movimento_direita(guerreiro,1,matriz_tela,bloqueios,1,1,0,3);
                calcular_ajuste_mapa(guerreiro,ajuste_mapa);
            }

            // agora chama janela com texto
            if(janelas->janela_atual==0 && janelas->total[eventos->quadro_min[i]-1].tempo_fim==-1 &&
               timer >= eventos->tempo_evento_atual + eventos->tempo_movimento_guerreiro[i])
            {
                janelas->janela_atual=eventos->quadro_min[i];
                janelas->total[eventos->quadro_min[i]-1].tempo_inicio=timer;
                janelas->total[eventos->quadro_min[i]-1].tempo_fim=-1;
            }

            if((apertou(KEY_ENTER)||apertou(KEY_SPACE)) && timer>=eventos->tempo_evento_atual + eventos->tempo_movimento_guerreiro[i])
            {
                play_sample(confirmar,255,128,1000,FALSE);

                if(janelas->janela_atual==eventos->quadro_min[i])
                    janelas->total[eventos->quadro_min[i]-1].tempo_fim=timer;

                if(janelas->janela_atual!=eventos->quadro_max[i])
                {
                    janelas->janela_atual+=1;
                    janelas->total[janelas->janela_atual-1].tempo_inicio=timer;
                    janelas->total[janelas->janela_atual-1].tempo_fim=-1;
                }
                else if(janelas->janela_atual==eventos->quadro_max[i] && janelas->total[eventos->quadro_min[i]-1].tempo_fim!=-1)
                {
                    janelas->total[eventos->quadro_max[i]-1].tempo_fim=timer+20;
                }
            }
            // agora a condição de saída é janelas->janela_atual==0
            if(janelas->janela_atual == 0  && timer >= eventos->tempo_evento_atual + eventos->tempo_movimento_guerreiro[i])
            {
                eventos->evento_atual=0;
                eventos->eventos_executados[i]=1;
                *pause=0;

                if(eventos->chefe[i])
                    stop_midi();

                if(fase==1 && eventos->chefe[i])
                    play_midi(musica_boss1,TRUE);
                else if(fase==2 && eventos->chefe[i])
                    play_midi(musica_boss2,TRUE);
                else if(fase==3 && eventos->chefe[i])
                    play_midi(musica_boss3,TRUE);

                set_volume(volume,volume);
            }
        }
    }
}

void desenhos_evento(BITMAP *buffer, int fase,Teventos *eventos,Tjanelas *janelas,Tcriatura *guerreiro,FONT* corpo_texto,
                     FONT *titulo_texto,Toponentes *inimigos)
{
    int efeito=0;
    if(janelas->janela_atual!=0)
    {
        if(janelas->janela_atual == eventos->quadro_min[eventos->evento_atual-1])
            efeito=1;
        if(janelas->total[janelas->janela_atual-1].ator==0)
            janela_dialogo(buffer,guerreiro,janelas->total[janelas->janela_atual-1].x,janelas->total[janelas->janela_atual-1].y,
                           titulo_texto,corpo_texto,janelas->total[janelas->janela_atual-1].tempo_inicio,
                           janelas->total[janelas->janela_atual-1].tempo_fim,timer,janelas->total[janelas->janela_atual-1].titulo,
                           janelas->total[janelas->janela_atual-1].conteudo,efeito);
        else
            janela_dialogo(buffer,&inimigos->chefes.chefe[inimigos->chefes.chefe_atual-1],janelas->total[janelas->janela_atual-1].x,
                           janelas->total[janelas->janela_atual-1].y,
                           titulo_texto,corpo_texto,janelas->total[janelas->janela_atual-1].tempo_inicio,
                           janelas->total[janelas->janela_atual-1].tempo_fim,timer,janelas->total[janelas->janela_atual-1].titulo,
                           janelas->total[janelas->janela_atual-1].conteudo,efeito);

        if(timer==janelas->total[janelas->janela_atual-1].tempo_fim)
            janelas->janela_atual=0;
    }
}

void carregar_var_fase(int fase,Titens *itens, Tcriatura *guerreiro,Toponentes *inimigos,Tjanelas *janelas,BITMAP *background,
                       BITMAP *texturas[MAX_TERRENOS],Teventos *eventos,DATAFILE* graficos)
{
    int i;
    BITMAP *fundo;

    for(i=0;i<2;i++)
        eventos->eventos_executados[i]=0;

    eventos->evento_atual=0;

    if(fase==1)
    {
        eventos->tempo_movimento_guerreiro[0]=60;
        eventos->quadro_min[0]=1;
        eventos->quadro_max[0]=2;
        eventos->posicaoX_guerreiro[0]=100;
        eventos->chefe[0]=0;
        eventos->tempo_movimento_guerreiro[1]=60;
        eventos->quadro_min[1]=3;
        eventos->quadro_max[1]=5;
        eventos->posicaoX_guerreiro[1]=LARGURA_MAPA-450;
        eventos->chefe[1]=1;
        eventos->n_eventos=2;

        preencher_item(&itens->todosItens[0],550,NIVEL_CHAO-20,20,15,1,1,0,0,graficos);
        preencher_item(&itens->todosItens[1],0,0,8,15,0,2,0,1,graficos);
        preencher_item(&itens->todosItens[2],0,0,8,15,0,2,0,2,graficos);
        itens->n_itens=3;

        preenche_criatura(guerreiro,0,NIVEL_CHAO-34,20,34,1,2*POWER,3,2,1*POWER,0,-16,-4,20,25,4,0); // preenche status guerreiro
        imagens_guerreiro(guerreiro,graficos); // preenche vetor de imagens do guerreiro

        preenche_criatura(&inimigos->goblins_guerreiros.goblins[0],SCREEN_W-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[0],0,graficos); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[1],750,NIVEL_CHAO-32,28,32,2,1,2,1,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[1],0,graficos); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[2],LARGURA_MAPA-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[2],0,graficos); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[3],LARGURA_MAPA-100,NIVEL_CHAO-32,28,32,2,1,2,1,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[3],0,graficos); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[4],1770,NIVEL_CHAO-32,28,32,2,1,1,2,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[4],0,graficos); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[5],2100,NIVEL_CHAO-32,28,32,2,1,1,2,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[5],0,graficos); // preenche vetor de imagens do goblin tipo 1
        inimigos->goblins_guerreiros.n_goblins=6;

        preenche_criatura(&inimigos->goblins_arqueiros.goblins[0],1020,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,2);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[0],0,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[1],1520,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,3);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[1],0,graficos);
        inimigos->goblins_arqueiros.n_goblins=2;

        preenche_criatura(&inimigos->chefes.chefe[0],LARGURA_MAPA-300,NIVEL_CHAO-32,28,32,2,3,3,2,2,2,-19,0,19,26,2,0);
        imagens_goblin_chefe(&inimigos->chefes.chefe[0],0,graficos);
        inimigos->chefes.chefe_atual=1;

        carrega_texturas(texturas,graficos); // prepara as texturas

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,-1,"Heroi","Droga, me perdi nesta maldita floresta infestada de goblins.",0);
        preencher_janela(&janelas->total[1],70,300,0,0,0,0,-1,"Heroi","Agora tenho de sair daqui...",0);
        preencher_janela(&janelas->total[2],70,300,0,0,0,0,-1,"Heroi","Droga, esse goblin parece ser forte. Terei de derrota-lo.",0);
        preencher_janela(&janelas->total[3],70,300,0,0,0,0,-1,"Goblin","Grrr!! FrknknfK k feknkn xinksd.",1);
        preencher_janela(&janelas->total[4],70,300,0,0,0,0,-1,"Heroi","Acho que ele nao vai com a minha cara...",0);
        janelas->janela_atual=0;
        janelas->n_janelas=5;

        fundo = (BITMAP*) graficos[FLORESTA].dat;
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }

    if(fase==2)
    {
        eventos->tempo_movimento_guerreiro[0]=60;
        eventos->quadro_min[0]=1;
        eventos->quadro_max[0]=2;
        eventos->posicaoX_guerreiro[0]=100;
        eventos->chefe[0]=0;
        eventos->tempo_movimento_guerreiro[1]=60;
        eventos->quadro_min[1]=3;
        eventos->quadro_max[1]=5;
        eventos->posicaoX_guerreiro[1]=LARGURA_MAPA-450;
        eventos->chefe[1]=1;
        eventos->n_eventos=2;

        preencher_item(&itens->todosItens[0],550,NIVEL_CHAO-20,20,15,1,1,1,0,graficos);
        preencher_item(&itens->todosItens[1],0,0,8,15,0,2,1,1,graficos);
        preencher_item(&itens->todosItens[2],0,0,8,15,0,2,1,2,graficos);
        preencher_item(&itens->todosItens[3],0,0,8,15,0,2,0,3,graficos);
        preencher_item(&itens->todosItens[4],0,0,8,15,0,2,0,4,graficos);
        preencher_item(&itens->todosItens[5],0,0,8,15,0,2,0,5,graficos);
        preencher_item(&itens->todosItens[6],0,0,8,15,0,2,0,6,graficos);
        preencher_item(&itens->todosItens[7],550,NIVEL_CHAO-20,20,15,0,1,0,0,graficos);
        itens->n_itens=8;

        preenche_criatura(guerreiro,0,NIVEL_CHAO-34,20,34,1,2*POWER,3,2,2*POWER,0,-16,-4,20,25,4,0); // preenche status guerreiro

        preenche_criatura(&inimigos->goblins_guerreiros.goblins[0],SCREEN_W-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[0],1,graficos); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[1],750,NIVEL_CHAO-32,28,32,2,1,2,1,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[1],1,graficos); // preenche vetor de imagens do goblin tipo 1
        inimigos->goblins_guerreiros.n_goblins=2;

        preenche_criatura(&inimigos->goblins_arqueiros.goblins[0],1020,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,2);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[0],1,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[1],1520,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,3);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[1],1,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[2],LARGURA_MAPA-50,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,4);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[2],0,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[3],LARGURA_MAPA-100,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,5);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[3],0,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[4],1700,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,6);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[4],0,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[5],2100,NIVEL_CHAO-32,28,32,2,0,3,1,1,2,0,0,1,1,2,7);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[5],0,graficos);
        inimigos->goblins_arqueiros.n_goblins=6;

        preenche_criatura(&inimigos->chefes.chefe[0],LARGURA_MAPA-300,NIVEL_CHAO-32,28,32,2,3,3,3,2,2,-19,0,19,26,2,0);
        imagens_goblin_chefe(&inimigos->chefes.chefe[0],1,graficos);
        inimigos->chefes.chefe_atual=1;

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,-1,"Heroi","Terei de atravessar essa montanha se quiser sair desta floresta.",0);
        preencher_janela(&janelas->total[1],70,300,0,0,0,0,-1,"Heroi","Nao acho que sera facil...",0);
        preencher_janela(&janelas->total[2],70,300,0,0,0,0,-1,"Heroi","O que? Voce de novo?",0);
        preencher_janela(&janelas->total[3],70,300,0,0,0,0,-1,"Goblin","Grrr!! FrknknfK k feknkn xinksd.",1);
        preencher_janela(&janelas->total[4],70,300,0,0,0,0,-1,"Heroi","Mas que droga!",0);
        janelas->janela_atual=0;
        janelas->n_janelas=5;

        fundo = (BITMAP*) graficos[CAVERNA].dat;
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }

    if(fase==3)
    {
        eventos->tempo_movimento_guerreiro[0]=60;
        eventos->quadro_min[0]=1;
        eventos->quadro_max[0]=2;
        eventos->posicaoX_guerreiro[0]=100;
        eventos->chefe[0]=0;
        eventos->tempo_movimento_guerreiro[1]=60;
        eventos->quadro_min[1]=3;
        eventos->quadro_max[1]=5;
        eventos->posicaoX_guerreiro[1]=LARGURA_MAPA-450;
        eventos->chefe[1]=1;
        eventos->n_eventos=2;

        preencher_item(&itens->todosItens[0],550,NIVEL_CHAO-20,20,15,1,1,1,0,graficos);
        preencher_item(&itens->todosItens[1],0,0,8,15,0,2,1,1,graficos);
        preencher_item(&itens->todosItens[2],0,0,8,15,0,2,1,2,graficos);
        preencher_item(&itens->todosItens[3],0,0,8,15,0,2,1,3,graficos);
        preencher_item(&itens->todosItens[4],0,0,8,15,0,2,1,4,graficos);
        preencher_item(&itens->todosItens[5],0,0,8,15,0,2,1,5,graficos);
        preencher_item(&itens->todosItens[6],550,NIVEL_CHAO-20,20,15,0,1,1,0,graficos);
        itens->n_itens=7;

        preenche_criatura(guerreiro,0,NIVEL_CHAO-34,20,34,1,3*POWER,3,2,2*POWER,0,-16,-4,20,25,4,0); // preenche status guerreiro

        preenche_criatura(&inimigos->goblins_guerreiros.goblins[0],SCREEN_W-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[0],1,graficos); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[1],750,NIVEL_CHAO-32,28,32,2,1,2,1,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[1],1,graficos); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[2],1800,NIVEL_CHAO-32,28,32,2,3,1,2,1,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[2],1,graficos); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[3],LARGURA_MAPA-100,NIVEL_CHAO-32,28,32,2,1,2,1,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[3],1,graficos);
        inimigos->goblins_guerreiros.n_goblins=4;

        preenche_criatura(&inimigos->goblins_arqueiros.goblins[0],720,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,2);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[0],1,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[1],1320,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,3);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[1],1,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[2],LARGURA_MAPA-50,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,4);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[2],1,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[3],1720,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,5);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[3],1,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[4],2520,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,6);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[4],1,graficos);
        inimigos->goblins_arqueiros.n_goblins=5;

        preenche_criatura(&inimigos->chefes.chefe[0],LARGURA_MAPA-300,NIVEL_CHAO-32,28,32,2,3,3,2,2,2,-19,0,19,26,2,0);
        imagens_goblin_chefe(&inimigos->chefes.chefe[0],1,graficos);
        inimigos->chefes.chefe_atual=1;

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,-1,"Heroi","Agora estou mais perto de sair daqui!",0);
        preencher_janela(&janelas->total[1],70,300,0,0,0,0,-1,"Heroi","Basta continuar andando...",0);
        preencher_janela(&janelas->total[2],70,300,0,0,0,0,-1,"Heroi","Eu nao acredito nisso!",0);
        preencher_janela(&janelas->total[3],70,300,0,0,0,0,-1,"Goblin","Grrr!! FrknknfK k feknkn xinksd.",1);
        preencher_janela(&janelas->total[4],70,300,0,0,0,0,-1,"Heroi","Cala a boca!",0);
        janelas->janela_atual=0;
        janelas->n_janelas=5;

        fundo = (BITMAP*) graficos[FLORESTA].dat;
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }
}

void pausar(int *pause, int *selecionar,SAMPLE* som_pause)
{
    if (apertou(KEY_ESC) && !inicio_fase && !fim_fase)
    {
        transparencia=0;
        if (*pause == TRUE)
        {
            *pause = FALSE;
            set_volume(volume,volume);
        }

        else
        {
            *pause = TRUE;
            set_volume(volume-100,volume-100);
        }

        play_sample(som_pause,255,128,1000,FALSE);

        if(*selecionar!=0 && *pause==TRUE)
            *selecionar=0;
    }
}

void verifica_nova_fase(Tcriatura *guerreiro, int *fase, int *carrega_fase, int *tela, int *loading_time, int *estagio_loading,
                        int *tela_destino,Tchefes *chefes_,Teventos *eventos,int *tocando,int *pause,BITMAP* buffer)
{
    if(chefes_->chefe_atual!=0)
    {
        if(chefes_->chefe[chefes_->chefe_atual-1].caracteristicas.hp<=0  && *fase<N_FASES)
        {
            if(fim_fase==0)
            {
                fim_fase=1;
                *pause=1;
                eventos->evento_atual=20;
            }

            transparencia+=2;
            drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
            set_trans_blender(255,0,0,transparencia);
            rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(0,0,0));
            solid_mode();

            if(transparencia==254 || transparencia==255)
            {
                eventos->evento_atual=0;
                *pause=0;
                *carrega_fase=1;
                *fase=*fase+1;
                *tela=9; // a próxima tela será a de loading game
                *loading_time = timer;
                *estagio_loading=0;
                *tela_destino=1;
                stop_midi();
                *tocando=0;
            }
        }
        else if(chefes_->chefe[chefes_->chefe_atual-1].caracteristicas.hp<=0  && *fase==N_FASES)
        {
            if(fim_fase==0)
            {
                fim_fase=1;
                *pause=1;
                eventos->evento_atual=20;
            }

            transparencia+=2;
            drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
            set_trans_blender(255,0,0,transparencia);
            rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(0,0,0));
            solid_mode();
            if(transparencia==254 || transparencia==255)
            {
                eventos->evento_atual=0;
                *pause=0;
                *tela=4;
                stop_midi();
                *tocando=0;
            }
        }
    }
}
