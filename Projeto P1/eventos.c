#include "eventos.h"

void verificar_evento(int *pause,int fase,Teventos *eventos,Tcriatura *guerreiro,Tjanelas *janelas,
                      int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3],int *ajuste_mapa,
                      MIDI* musica_boss1,MIDI* musica_boss2,MIDI*musica_boss3,SAMPLE *confirmar)
{
    // eventos da primeira fase
    if(fase==1)
    {
        // evento 1
        if(!eventos->eventos_executados[0] &&
           (guerreiro->x>=100 || eventos->evento_atual==1))
        {
            // diminui volume
            set_volume(volume-100,volume-100);

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
                play_sample(confirmar,255,128,1000,FALSE);
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
                set_volume(volume,volume);
            }
        }
        // evento 2, batalha com chefe
        else if(!eventos->eventos_executados[1] &&
           (guerreiro->x>=LARGURA_MAPA-450 || eventos->evento_atual==2))
        {
            // diminui volume
            set_volume(volume-100,volume-100);
            // trava o evento atual e pausa o jogo
            if(!eventos->evento_atual)
            {
                eventos->evento_atual=2;
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
                calcular_ajuste_mapa(guerreiro,ajuste_mapa);
            }

            // agora chama janela com texto
            if(janelas->janela_atual==0 && janelas->total[2].tempo_fim==-1 && timer>=eventos->tempo_evento_atual+60)
            {
                janelas->janela_atual=3;
                janelas->total[2].tempo_inicio=timer;
                janelas->total[2].tempo_fim=-1;
            }

            if((apertou(KEY_ENTER)||apertou(KEY_SPACE)) && timer>=eventos->tempo_evento_atual+60)
            {
                play_sample(confirmar,255,128,1000,FALSE);
                if(janelas->janela_atual==3)
                {
                    janelas->janela_atual=4;
                    janelas->total[3].tempo_inicio=timer;
                    janelas->total[3].tempo_fim=-1;
                }
                else if(janelas->janela_atual==4)
                {
                    janelas->janela_atual=5;
                    janelas->total[4].tempo_inicio=timer;
                    janelas->total[4].tempo_fim=-1;
                }
                else if(janelas->janela_atual==5 && janelas->total[4].tempo_fim==-1)
                    janelas->total[4].tempo_fim=timer+20;
            }
            // agora a condição de saída é janelas->janela_atual==0
            if(janelas->janela_atual==3  && janelas->total[4].tempo_fim!=-1 && timer>=eventos->tempo_evento_atual+60)
            {
                set_volume(volume,volume);
                eventos->evento_atual=0;
                eventos->eventos_executados[1]=1;
                *pause=0;
                play_midi(musica_boss1,TRUE);
            }
        }
    }
    else if(fase==2)
    {
        // evento 1
        if(!eventos->eventos_executados[0] &&
           (guerreiro->x>=100 || eventos->evento_atual==1))
        {
            set_volume(volume-100,volume-100);
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
                play_sample(confirmar,255,128,1000,FALSE);
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
                set_volume(volume,volume);
                eventos->evento_atual=0;
                eventos->eventos_executados[0]=1;
                *pause=0;
            }
        }
        // evento 2, batalha com chefe
        else if(!eventos->eventos_executados[1] &&
           (guerreiro->x>=LARGURA_MAPA-450 || eventos->evento_atual==2))
        {
            set_volume(volume-100,volume-100);
            // trava o evento atual e pausa o jogo
            if(!eventos->evento_atual)
            {
                eventos->evento_atual=2;
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
                calcular_ajuste_mapa(guerreiro,ajuste_mapa);
            }

            // agora chama janela com texto
            if(janelas->janela_atual==0 && janelas->total[2].tempo_fim==-1 && timer>=eventos->tempo_evento_atual+60)
            {
                janelas->janela_atual=3;
                janelas->total[2].tempo_inicio=timer;
                janelas->total[2].tempo_fim=-1;
            }

            if((apertou(KEY_ENTER)||apertou(KEY_SPACE)) && timer>=eventos->tempo_evento_atual+60)
            {
                play_sample(confirmar,255,128,1000,FALSE);
                if(janelas->janela_atual==3)
                {
                    janelas->janela_atual=4;
                    janelas->total[3].tempo_inicio=timer;
                    janelas->total[3].tempo_fim=-1;
                }
                else if(janelas->janela_atual==4)
                {
                    janelas->janela_atual=5;
                    janelas->total[4].tempo_inicio=timer;
                    janelas->total[4].tempo_fim=-1;
                }
                else if(janelas->janela_atual==5 && janelas->total[4].tempo_fim==-1)
                    janelas->total[4].tempo_fim=timer+20;
            }
            // agora a condição de saída é janelas->janela_atual==0
            if(janelas->janela_atual==3  && janelas->total[4].tempo_fim!=-1 && timer>=eventos->tempo_evento_atual+60)
            {
                set_volume(volume,volume);
                eventos->evento_atual=0;
                eventos->eventos_executados[1]=1;
                *pause=0;
                play_midi(musica_boss2,TRUE);
            }
        }
    }
    else if(fase==3)
    {
        // evento 1
        if(!eventos->eventos_executados[0] &&
           (guerreiro->x>=100 || eventos->evento_atual==1))
        {
            set_volume(volume-100,volume-100);
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
                play_sample(confirmar,255,128,1000,FALSE);
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
                set_volume(volume,volume);
                eventos->evento_atual=0;
                eventos->eventos_executados[0]=1;
                *pause=0;
            }
        }
        // evento 2, batalha com chefe
        else if(!eventos->eventos_executados[1] &&
           (guerreiro->x>=LARGURA_MAPA-450 || eventos->evento_atual==2))
        {
            set_volume(volume-100,volume-100);
            // trava o evento atual e pausa o jogo
            if(!eventos->evento_atual)
            {
                eventos->evento_atual=2;
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
                calcular_ajuste_mapa(guerreiro,ajuste_mapa);
            }

            // agora chama janela com texto
            if(janelas->janela_atual==0 && janelas->total[2].tempo_fim==-1 && timer>=eventos->tempo_evento_atual+60)
            {
                janelas->janela_atual=3;
                janelas->total[2].tempo_inicio=timer;
                janelas->total[2].tempo_fim=-1;
            }

            if((apertou(KEY_ENTER)||apertou(KEY_SPACE)) && timer>=eventos->tempo_evento_atual+60)
            {
                play_sample(confirmar,255,128,1000,FALSE);
                if(janelas->janela_atual==3)
                {
                    janelas->janela_atual=4;
                    janelas->total[3].tempo_inicio=timer;
                    janelas->total[3].tempo_fim=-1;
                }
                else if(janelas->janela_atual==4)
                {
                    janelas->janela_atual=5;
                    janelas->total[4].tempo_inicio=timer;
                    janelas->total[4].tempo_fim=-1;
                }
                else if(janelas->janela_atual==5 && janelas->total[4].tempo_fim==-1)
                    janelas->total[4].tempo_fim=timer+20;
            }
            // agora a condição de saída é janelas->janela_atual==0
            if(janelas->janela_atual==3  && janelas->total[4].tempo_fim!=-1 && timer>=eventos->tempo_evento_atual+60)
            {
                set_volume(volume,volume);
                eventos->evento_atual=0;
                eventos->eventos_executados[1]=1;
                *pause=0;
                play_midi(musica_boss3,TRUE);
            }
        }
    }
}

void desenhos_evento(BITMAP *buffer, int fase,Teventos *eventos,Tjanelas *janelas,Tcriatura *guerreiro,FONT* corpo_texto,
                     FONT *titulo_texto,Toponentes *inimigos)
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
                if(timer<=janelas->total[1].tempo_fim)
                    janelas->janela_atual=0;
            }
        }
        // segundo evento
        if(eventos->evento_atual==2)
        {
            if(janelas->janela_atual==3) // teste de janela
            {
                janela_dialogo(buffer,guerreiro,janelas->total[2].x,janelas->total[2].y,titulo_texto,corpo_texto,
                               janelas->total[2].tempo_inicio,janelas->total[2].tempo_fim,timer,janelas->total[2].titulo,
                               janelas->total[2].conteudo,1);
                if(timer==janelas->total[2].tempo_fim)
                    janelas->janela_atual=0;
            }
            else if(janelas->janela_atual==4)
            {
                janela_dialogo(buffer,&inimigos->chefes.chefe[0],janelas->total[3].x,janelas->total[3].y,titulo_texto,corpo_texto,
                               janelas->total[3].tempo_inicio,janelas->total[3].tempo_fim,timer,janelas->total[3].titulo,
                               janelas->total[3].conteudo,0);
                if(timer==janelas->total[3].tempo_fim)
                    janelas->janela_atual=0;
            }
            else if(janelas->janela_atual==5)
            {
                janela_dialogo(buffer,guerreiro,janelas->total[4].x,janelas->total[4].y,titulo_texto,corpo_texto,
                               janelas->total[4].tempo_inicio,janelas->total[4].tempo_fim,timer,janelas->total[4].titulo,
                               janelas->total[4].conteudo,0);
                if(timer<=janelas->total[4].tempo_fim)
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
            else if(janelas->janela_atual==2)
            {
                janela_dialogo(buffer,guerreiro,janelas->total[1].x,janelas->total[1].y,titulo_texto,corpo_texto,
                               janelas->total[1].tempo_inicio,janelas->total[1].tempo_fim,timer,janelas->total[1].titulo,
                               janelas->total[1].conteudo,0);
                if(timer<=janelas->total[1].tempo_fim)
                    janelas->janela_atual=0;
            }
        }
        // segundo evento
        if(eventos->evento_atual==2)
        {
            if(janelas->janela_atual==3) // teste de janela
            {
                janela_dialogo(buffer,guerreiro,janelas->total[2].x,janelas->total[2].y,titulo_texto,corpo_texto,
                               janelas->total[2].tempo_inicio,janelas->total[2].tempo_fim,timer,janelas->total[2].titulo,
                               janelas->total[2].conteudo,1);
                if(timer==janelas->total[2].tempo_fim)
                    janelas->janela_atual=0;
            }
            else if(janelas->janela_atual==4)
            {
                janela_dialogo(buffer,&inimigos->chefes.chefe[0],janelas->total[3].x,janelas->total[3].y,titulo_texto,corpo_texto,
                               janelas->total[3].tempo_inicio,janelas->total[3].tempo_fim,timer,janelas->total[3].titulo,
                               janelas->total[3].conteudo,0);
                if(timer==janelas->total[3].tempo_fim)
                    janelas->janela_atual=0;
            }
            else if(janelas->janela_atual==5)
            {
                janela_dialogo(buffer,guerreiro,janelas->total[4].x,janelas->total[4].y,titulo_texto,corpo_texto,
                               janelas->total[4].tempo_inicio,janelas->total[4].tempo_fim,timer,janelas->total[4].titulo,
                               janelas->total[4].conteudo,0);
                if(timer<=janelas->total[4].tempo_fim)
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
            else if(janelas->janela_atual==2)
            {
                janela_dialogo(buffer,guerreiro,janelas->total[1].x,janelas->total[1].y,titulo_texto,corpo_texto,
                               janelas->total[1].tempo_inicio,janelas->total[1].tempo_fim,timer,janelas->total[1].titulo,
                               janelas->total[1].conteudo,0);
                if(timer<=janelas->total[1].tempo_fim)
                    janelas->janela_atual=0;
            }
        }
        // segundo evento
        if(eventos->evento_atual==2)
        {
            if(janelas->janela_atual==3) // teste de janela
            {
                janela_dialogo(buffer,guerreiro,janelas->total[2].x,janelas->total[2].y,titulo_texto,corpo_texto,
                               janelas->total[2].tempo_inicio,janelas->total[2].tempo_fim,timer,janelas->total[2].titulo,
                               janelas->total[2].conteudo,1);
                if(timer==janelas->total[2].tempo_fim)
                    janelas->janela_atual=0;
            }
            else if(janelas->janela_atual==4)
            {
                janela_dialogo(buffer,&inimigos->chefes.chefe[0],janelas->total[3].x,janelas->total[3].y,titulo_texto,corpo_texto,
                               janelas->total[3].tempo_inicio,janelas->total[3].tempo_fim,timer,janelas->total[3].titulo,
                               janelas->total[3].conteudo,0);
                if(timer==janelas->total[3].tempo_fim)
                    janelas->janela_atual=0;
            }
            else if(janelas->janela_atual==5)
            {
                janela_dialogo(buffer,guerreiro,janelas->total[4].x,janelas->total[4].y,titulo_texto,corpo_texto,
                               janelas->total[4].tempo_inicio,janelas->total[4].tempo_fim,timer,janelas->total[4].titulo,
                               janelas->total[4].conteudo,0);
                if(timer<=janelas->total[4].tempo_fim)
                    janelas->janela_atual=0;
            }
        }
    }
}

void carregar_var_fase(int fase,Titens *itens, Tcriatura *guerreiro,Toponentes *inimigos,Tjanelas *janelas,BITMAP *background,
                       BITMAP *texturas[MAX_TERRENOS],Teventos *eventos,DATAFILE* graficos)
{
    int i;
    BITMAP *fundo;

    for(i=0;i<3;i++)
        eventos->eventos_executados[i]=0;

    eventos->evento_atual=0;

    if(fase==1)
    {
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
        inimigos->goblins_guerreiros.n_goblins=2;

        preenche_criatura(&inimigos->goblins_arqueiros.goblins[0],1020,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,2);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[0],0,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[1],1520,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,3);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[1],0,graficos);
        inimigos->goblins_arqueiros.n_goblins=2;

        preenche_criatura(&inimigos->chefes.chefe[0],LARGURA_MAPA-300,NIVEL_CHAO-32,28,32,2,3,3,2,2,2,-19,0,19,26,2,0);
        imagens_goblin_chefe(&inimigos->chefes.chefe[0],0,graficos);
        inimigos->chefes.chefe_atual=1;

        carrega_texturas(texturas,graficos); // prepara as texturas

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,-1,"Heroi","Droga, me perdi nesta maldita floresta infestada de goblins.");
        preencher_janela(&janelas->total[1],70,300,0,0,0,0,-1,"Heroi","Agora tenho de sair daqui...");
        preencher_janela(&janelas->total[2],70,300,0,0,0,0,-1,"Heroi","Droga, esse goblin parece ser forte. Terei de derrota-lo.");
        preencher_janela(&janelas->total[3],70,300,0,0,0,0,-1,"Goblin","Grrr!! FrknknfK k feknkn xinksd.");
        preencher_janela(&janelas->total[4],70,300,0,0,0,0,-1,"Heroi","Acho que ele nao vai com a minha cara...");
        janelas->janela_atual=0;
        janelas->n_janelas=5;

        fundo = (BITMAP*) graficos[FLORESTA].dat;
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }

    if(fase==2)
    {
        eventos->n_eventos=2;

        preencher_item(&itens->todosItens[0],550,NIVEL_CHAO-20,20,15,1,1,1,0,graficos);
        preencher_item(&itens->todosItens[1],0,0,8,15,0,2,1,1,graficos);
        preencher_item(&itens->todosItens[2],0,0,8,15,0,2,1,2,graficos);
        itens->n_itens=3;

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
        inimigos->goblins_arqueiros.n_goblins=2;

        preenche_criatura(&inimigos->chefes.chefe[0],LARGURA_MAPA-300,NIVEL_CHAO-32,28,32,2,3,3,2,2,2,-19,0,19,26,2,0);
        imagens_goblin_chefe(&inimigos->chefes.chefe[0],1,graficos);
        inimigos->chefes.chefe_atual=1;

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,-1,"Heroi","Terei de atravessar essa montanha se quiser sair desta floresta.");
        preencher_janela(&janelas->total[1],70,300,0,0,0,0,-1,"Heroi","Nao acho que sera facil...");
        preencher_janela(&janelas->total[2],70,300,0,0,0,0,-1,"Heroi","O que? Voce de novo?");
        preencher_janela(&janelas->total[3],70,300,0,0,0,0,-1,"Goblin","Grrr!! FrknknfK k feknkn xinksd.");
        preencher_janela(&janelas->total[4],70,300,0,0,0,0,-1,"Heroi","Mas que droga!");
        janelas->janela_atual=0;
        janelas->n_janelas=5;

        fundo = (BITMAP*) graficos[CAVERNA].dat;
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }

    if(fase==3)
    {
        eventos->n_eventos=2;

        preencher_item(&itens->todosItens[0],550,NIVEL_CHAO-20,20,15,1,1,1,0,graficos);
        preencher_item(&itens->todosItens[1],0,0,8,15,0,2,1,1,graficos);
        preencher_item(&itens->todosItens[2],0,0,8,15,0,2,1,2,graficos);
        itens->n_itens=3;

        preenche_criatura(guerreiro,0,NIVEL_CHAO-34,20,34,1,3*POWER,3,2,2*POWER,0,-16,-4,20,25,4,0); // preenche status guerreiro

        preenche_criatura(&inimigos->goblins_guerreiros.goblins[0],SCREEN_W-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[0],1,graficos); // preenche vetor de imagens do goblin tipo 1
        preenche_criatura(&inimigos->goblins_guerreiros.goblins[1],750,NIVEL_CHAO-32,28,32,2,1,2,1,0,0,-19,0,19,26,2,0); // preenche status goblin
        imagens_goblin_guerreiro(&inimigos->goblins_guerreiros.goblins[1],1,graficos); // preenche vetor de imagens do goblin tipo 1
        inimigos->goblins_guerreiros.n_goblins=2;

        preenche_criatura(&inimigos->goblins_arqueiros.goblins[0],1020,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,2);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[0],1,graficos);
        preenche_criatura(&inimigos->goblins_arqueiros.goblins[1],1520,NIVEL_CHAO-32,28,32,2,0,2,1,1,2,0,0,1,1,2,3);
        imagens_goblin_arqueiro(&inimigos->goblins_arqueiros.goblins[1],1,graficos);
        inimigos->goblins_arqueiros.n_goblins=2;

        preenche_criatura(&inimigos->chefes.chefe[0],LARGURA_MAPA-300,NIVEL_CHAO-32,28,32,2,3,3,2,2,2,-19,0,19,26,2,0);
        imagens_goblin_chefe(&inimigos->chefes.chefe[0],1,graficos);
        inimigos->chefes.chefe_atual=1;

        preencher_janela(&janelas->total[0],70,300,0,0,0,0,-1,"Heroi","Agora estou mais perto de sair daqui!");
        preencher_janela(&janelas->total[1],70,300,0,0,0,0,-1,"Heroi","Basta continuar andando...");
        preencher_janela(&janelas->total[2],70,300,0,0,0,0,-1,"Heroi","Eu nao acredito nisso!");
        preencher_janela(&janelas->total[3],70,300,0,0,0,0,-1,"Goblin","Grrr!! FrknknfK k feknkn xinksd.");
        preencher_janela(&janelas->total[4],70,300,0,0,0,0,-1,"Heroi","Cala a boca!");
        janelas->janela_atual=0;
        janelas->n_janelas=5;

        fundo = (BITMAP*) graficos[FLORESTA].dat;
        clear_bitmap(background);
        draw_sprite(background,fundo,0,0);
    }
}

void pausar(int *pause, int *selecionar,SAMPLE* som_pause)
{
    if (apertou(KEY_ESC))
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
