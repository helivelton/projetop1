/*  #################################################################################
    #includes

    Inclua somente arquivos h do projeto
    As bibliotecas básicas são incluídas em básico.h
*/
#include "basico.h"
#include "mapa.h"
#include "criaturas.h"
#include "controle.h"
#include "item.h"
#include "eventos.h"
//  #################################################################################

int main()
{
    init(); // inicializa

/*  #######################################################################################
                    declaração das variáveis (e algumas inicializações)
    #######################################################################################
*/
    int i,j; // controladores de loops e auxiliares
    int ticks; // controla velocidade do jogo
    int tempo_de_jogo=0; // controla o tempo de jogo
    int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32]; // matriz da tela
    int ajuste_mapa = 0; // vetor que cuida do movimento do mapa e dos objetos nele
    int tela = 0, selecionar = 0; //controla o carregamento de cada tela
    int tela_destino=1; // determina qual tela será carregada após a tela de carregamento
    int fase=1;
    int carrega_fase=1;
    char nome_fase[N_FASES][10]={"mapa1.txt","mapa2.txt","mapa3.txt"};
    int loading_time = 0;
    int estagio_loading=0;
    int bloqueios[3] = {TERRA, PEDRA, CHAO};
    int pause = 0;
    int tocando=0;
    int tocando_game_over=0;

    // abrindo os datafiles
    DATAFILE* graficos = NULL;
    DATAFILE* musicas = NULL;
    DATAFILE* efeitos = NULL;
    DATAFILE* fontes = NULL;

    packfile_password("kill");

    graficos = load_datafile("imagens.dat");
    musicas = load_datafile("musicas.dat");
    efeitos = load_datafile("efeitos.dat");
    fontes = load_datafile("fontes.dat");

    packfile_password(NULL);

    // variáveis de objetos
    Tjanelas janelas;
    Tcriatura guerreiro; // declara objeto guerreiro
    Toponentes inimigos;
    Titens itens;
    Teventos eventos;

    // declara BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H); // Cria o buffer;
    BITMAP *mapa = create_bitmap(LARGURA_MAPA,ALTURA_MAPA); // Cria o mapa
    BITMAP *texturas[MAX_TERRENOS]; // declara a array de texturas
    BITMAP *background = create_bitmap(960,480);

    //BITMAPs do Menu
    BITMAP *menu_iniciar = (BITMAP*) graficos[MENU_1].dat;//menu iniciar
    BITMAP *menu_creditos = (BITMAP*) graficos[MENU_3].dat;
    BITMAP *menu_options = (BITMAP*) graficos[MENU_2].dat;//menu opções
    BITMAP *menu_exit = (BITMAP*) graficos[MENU_4].dat;//menu saída

    BITMAP *logo = (BITMAP*) graficos[LOGO_1].dat;

    // BITMAPS da tela de carregamento
    BITMAP *tela_loading[4];
    tela_loading[0] = (BITMAP*) graficos[CARREGAR_1].dat;
    tela_loading[1] = (BITMAP*) graficos[CARREGAR_2].dat;
    tela_loading[2] = (BITMAP*) graficos[CARREGAR_3].dat;
    tela_loading[3] = (BITMAP*) graficos[CARREGAR_4].dat;

    // Declara fontes
    FONT* corpo_texto = (FONT*) fontes[CORPO_TEXTO].dat;
    FONT* titulo_texto = (FONT*) fontes[TITULO_TEXTO].dat;

    // Declara sons
    MIDI* musica_floresta = (MIDI*) musicas[MUSICA_FLORESTA].dat;
    MIDI* musica_caverna = (MIDI*) musicas[MUSICA_CAVERNA].dat;
    MIDI* musica_chefe1 = (MIDI*) musicas[MUSICA_CHEFE_1].dat;
    MIDI* musica_chefe2 = (MIDI*) musicas[MUSICA_CHEFE_2].dat;
    MIDI* musica_chefe3 = (MIDI*) musicas[MUSICA_CHEFE_3].dat;
    MIDI* musica_menu = (MIDI*) musicas[MUSICA_MENU].dat;
    MIDI* musica_gameover = (MIDI*) musicas[MUSICA_GAMEOVER].dat;

    SAMPLE* selecao = (SAMPLE*) efeitos[SELECIONAR].dat;
    SAMPLE* confirmar = (SAMPLE*) efeitos[CONFIRMAR].dat;
    SAMPLE* espada = (SAMPLE*) efeitos[ESPADA].dat;
    SAMPLE* besta = (SAMPLE*) efeitos[BESTA].dat;
    SAMPLE* som_pause = (SAMPLE*) efeitos[PAUSE].dat;
    SAMPLE* som_dano_goblin = (SAMPLE*) efeitos[DANO_GOBLIN].dat;
    SAMPLE* som_dano_guerreiro = (SAMPLE*) efeitos[DANO_HEROI].dat;
    SAMPLE* som_cura = (SAMPLE*) efeitos[CURA].dat;
    SAMPLE* som_vinhas = (SAMPLE*) efeitos[PARALISIA].dat;
    SAMPLE* som_recuo = (SAMPLE*) efeitos[RECUO].dat;

    volume=250;
    set_volume(volume,volume);

/*  #######################################################################################
                                fim da declaração das variáveis
    #######################################################################################
*/

    // configura saída com o botão x no alto da tela
    exit_program = FALSE;
    LOCK_FUNCTION(fecha_programa);
    LOCK_VARIABLE(exit_program);
    set_close_button_callback(fecha_programa); // fecha a qualquer momento com o botão fechar

    // timer
    timer=0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer,BPS_TO_TIMER(60)); // para que o jogo execute 60 vezes por segundo

    ticks = timer; // velocidade do jogo

    // Processo de repetição principal
    while (!exit_program)
    {
        // loop válido, executado 60 vezes por segundo
        while(ticks<=timer && !exit_program)
        {
            // tela de menu
            if(tela==0)
            {
                clear_bitmap(buffer);
                keyboard_input();
                menu_inicial(buffer, &selecionar, menu_iniciar, menu_options, menu_exit,menu_creditos,&loading_time, &tela,
                             &estagio_loading,&tela_destino,&fase,&carrega_fase,&tempo_de_jogo,selecao,confirmar,&tocando,
                             musica_menu);
            }

            // tela de loading
            else if (tela == 9)
            {
                clear_bitmap(buffer);
                tela_carregamento(buffer, tela_loading, &loading_time,tela_destino, &tela,logo);
                carrega_elementos_fase(&carrega_fase,&estagio_loading,matriz_tela,nome_fase,fase,&itens,&guerreiro,&inimigos,
                                       &janelas,background,texturas,&eventos,mapa,graficos);
            }

            // tela de jogo
            else if(tela==1)
            {
                if(!tocando)
                {
                    if(fase==1 || fase==3)
                        play_midi(musica_floresta,TRUE);
                    else
                        play_midi(musica_caverna,TRUE);
                    tocando=1;
                }

                // atualiza estado do teclado
                keyboard_input();

                pausar(&pause,&selecionar,som_pause); // verifica se pressionou pause

                // limpa bitmaps de armazenamento
                clear_bitmap(buffer); // Limpa o buffer;
                clear_bitmap(guerreiro.sprite); // Limpa bitmap guerreiro
                clear_bitmap(inimigos.goblins_guerreiros.goblins[0].sprite); // Limpa bitmap goblin tipo 1
                clear_bitmap(inimigos.goblins_guerreiros.goblins[1].sprite); // Limpa bitmap goblin tipo 1

                if (!pause) // pause pode travar toda a lógica e tempo de jogo, exceto os eventos
                {
                    // incrementa o tempo de jogo
                    tempo_de_jogo++;

                    // Lógica do jogo
                    tocou_oponente(&guerreiro,&inimigos,tempo_de_jogo,som_dano_guerreiro);
                    verificar_status(&guerreiro,&inimigos,tempo_de_jogo,&itens);
                    movimento_guerreiro(&guerreiro,matriz_tela, bloqueios,som_recuo);
                    ataque_guerreiro(&guerreiro,tempo_de_jogo,&inimigos,espada,som_dano_goblin);

                    calcular_ajuste_mapa(&guerreiro,&ajuste_mapa);
                    acoes_goblins(&inimigos,&guerreiro,tempo_de_jogo,matriz_tela,bloqueios,&itens,espada,besta,som_dano_guerreiro,
                                  som_vinhas);
                    verifique_efeito_item(&itens,&guerreiro,&inimigos,tempo_de_jogo,som_dano_guerreiro,som_cura);
                    movimento_itens(&itens,&guerreiro,tempo_de_jogo,matriz_tela,bloqueios);
                }

                verificar_evento(&pause,fase,&eventos,&guerreiro,&janelas,matriz_tela,bloqueios,&ajuste_mapa,musica_chefe1,
                                 musica_chefe2,musica_chefe3,confirmar);

                // Desenhar
                draw_sprite(buffer,background,ajuste_mapa/10,0);
                draw_sprite(buffer, mapa, ajuste_mapa, 0); // manda mapa para o buffer na posição mov_mapa
                desenhar_todos_goblins(&inimigos,buffer,ajuste_mapa,tempo_de_jogo);
                desenhar_guerreiro(buffer,&guerreiro,&inimigos,ajuste_mapa,tempo_de_jogo,graficos); // desenha guerreiro e manda para buffer
                desenhar_itens(buffer,&itens,ajuste_mapa);
                desenhos_evento(buffer,fase,&eventos,&janelas,&guerreiro,corpo_texto,titulo_texto,&inimigos);

                pause_menu(&pause,&eventos,buffer,&selecionar,&tela,tempo_de_jogo,&tela_destino,&loading_time,
                           selecao,confirmar,&tocando);
                game_over(&pause,&eventos,buffer,&selecionar,&tela,tempo_de_jogo,&tela_destino,&loading_time,selecao,confirmar,
                          &tocando,musica_gameover,&guerreiro,&estagio_loading,&tocando_game_over,&carrega_fase,graficos);

                // se inicio da fase, coloca um efeito de opacidade
                if(inicio_fase)
                {
                    eventos.evento_atual=20;
                    pause=1;
                    if(opacidade>=2)opacidade-=2;

                    drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
                    set_trans_blender(255,0,0,opacidade);
                    rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(0,0,0));
                    solid_mode();

                    if(opacidade==0 && fase!=1)
                    {
                        inicio_fase=0;
                        pause=0;
                        eventos.evento_atual=0;
                    }
                    // se fase 1, desenha controles
                    else if(opacidade==0 && fase==1)
                    {
                        drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
                        set_trans_blender(255,0,0,150);
                        draw_sprite_ex(buffer,(BITMAP*)graficos[TUTORIAL].dat,30,50,DRAW_SPRITE_TRANS,DRAW_SPRITE_NO_FLIP);
                        solid_mode();

                        if((timer/16)%2==0)
                        {
                            rectfill(buffer,SCREEN_W-35,255,SCREEN_W-45,255+10,makecol(255,0,0));
                            rectfill(buffer,SCREEN_W-37,255-2,SCREEN_W-47,255+10-2,makecol(180,0,0));
                        }
                        else
                            rectfill(buffer,SCREEN_W-35,255,SCREEN_W-45,255+10,makecol(180,0,0));

                        if(apertou(KEY_ENTER)||apertou(KEY_ESC)||apertou(KEY_SPACE))
                        {
                            play_sample(confirmar,volume,128,1000,FALSE);
                            inicio_fase=0;
                            pause=0;
                            eventos.evento_atual=0;
                        }
                    }
                }

                // nova fase?
                verifica_nova_fase(&guerreiro,&fase,&carrega_fase,&tela,&loading_time,&estagio_loading,&tela_destino,
                                   &inimigos.chefes,&eventos,&tocando,&pause,buffer);

                blit(buffer,screen,0,0,0,0,LARGURA_SCREEN,ALTURA_SCREEN); // Manda o buffer para a tela;


            }
            // tela de opçções
            else if(tela==2)
            {
                clear_bitmap(buffer);
                keyboard_input();

                menu_opcoes(buffer,graficos,selecao,confirmar,&tela);
            }
            // tela de créditos
            else if(tela==3)
            {
                clear_bitmap(buffer);
                keyboard_input();

                creditos(buffer,graficos,confirmar,&tela);
            }
            else if(tela==4)
            {
                clear_bitmap(buffer);
                keyboard_input();

                if(opacidade>0)
                {
                    if(opacidade==244||opacidade==255)
                        rest(2000);

                    opacidade-=2;

                    drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
                    set_trans_blender(255,0,0,opacidade);

                    draw_sprite_ex(buffer,(BITMAP*)graficos[CONTINUE].dat,0,0,DRAW_SPRITE_TRANS,DRAW_SPRITE_NO_FLIP);

                    solid_mode();

                }
                else if(opacidade==0)
                {
                    draw_sprite_ex(buffer,(BITMAP*)graficos[CREDITOS].dat,0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);

                    if(apertou(KEY_ENTER)||apertou(KEY_SPACE)||apertou(KEY_ESC))
                    {
                        tela=0;
                        play_sample(confirmar,volume,128,1000,FALSE);
                    }
                }
                draw_sprite(screen,buffer,0,0);

            }
            ticks++; // incrementa controle de velocidade do jogo
        }
    }

    deinit(); // finaliza

    // destruição de bitmaps
    destroy_bitmap(buffer);
    destroy_bitmap(mapa);
    destroy_bitmap(background);

    for(i=0;i<MAX_TERRENOS;i++)
        destroy_bitmap(texturas[i]);

    destroy_bitmap(guerreiro.sprite);

    for(i=0;i<8;i++)
        destroy_bitmap(guerreiro.vetor_sprite[i]);

    for(i=0;i<10;i++)
        destroy_bitmap(guerreiro.barraHp[i]);

    for(i=0;i<8;i++)
    {
        for(j=0;j<6;j++)
            destroy_bitmap(inimigos.goblins_guerreiros.goblins[j].vetor_sprite[i]);

        if(i!=7)
        {
            for(j=0;j<6;j++)
                destroy_bitmap(inimigos.goblins_arqueiros.goblins[j].vetor_sprite[i]);
        }

        destroy_bitmap(inimigos.chefes.chefe[0].vetor_sprite[i]);
    }

    for(i=0;i<6;i++)
    {
        destroy_bitmap(inimigos.goblins_guerreiros.goblins[i].sprite);
        destroy_bitmap(inimigos.goblins_arqueiros.goblins[i].sprite);
    }

    destroy_bitmap(inimigos.chefes.chefe[0].sprite);

    for(i=0;i<8;i++)
    {
        destroy_bitmap(itens.todosItens[i].imagem);
        destroy_bitmap(itens.todosItens[i].imagem_buffer);
    }

    return 0 ;
}
END_OF_MAIN(); // para finalizar o main no allegro
