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
    int i; // controlador de loops e auxiliares
    int ticks; // controla velocidade do jogo
    int tempo_de_jogo=0; // controla o tempo de jogo
    int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32]; // matriz da tela
    int ajuste_mapa = 0; // vetor que cuida do movimento do mapa e dos objetos nele
    int tela = 0, selecionar = 0; //controla o carregamento de cada tela
    int fase=1;
    int carrega_fase=1;
    char nome_fase[N_FASES][10]={"mapa1.txt","mapa2.txt","mapa3.txt"};
    int loading_time = 0;
    int bloqueios[3] = {TERRA, PEDRA, CHAO};
    int pause = 0;

    //BITMAPs do Menu
    BITMAP *bg = load_bitmap(link_imagem("imagens_p1/menu.bmp"), NULL); //fundo do menu
    BITMAP *menu_iniciar = load_bitmap (link_imagem("imagens_p1/menu1.bmp"), NULL);//menu iniciar
    BITMAP *menu_options = load_bitmap (link_imagem("imagens_p1/menu2.bmp"), NULL);//menu opções
    BITMAP *menu_exit = load_bitmap (link_imagem("imagens_p1/menu3.bmp"), NULL);//menu saída


    // BITMAPS da tela de carregamento
    BITMAP *tela_loading[4];
    tela_loading[0] = load_bitmap (link_imagem("imagens_p1/carregar1.bmp"), NULL);
    tela_loading[1] = load_bitmap (link_imagem("imagens_p1/carregar2.bmp"), NULL);
    tela_loading[2] = load_bitmap (link_imagem("imagens_p1/carregar3.bmp"), NULL);
    tela_loading[3] = load_bitmap (link_imagem("imagens_p1/carregar4.bmp"), NULL);

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

    // Declara fontes
    FONT* corpo_texto = load_font("fontes/corpo.pcx",NULL,NULL);
    FONT* titulo_texto = load_font("fontes/titulos.pcx",NULL,NULL);

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

    // inicializa controles de velocidade
    ticks = timer; // velocidade do jogo
    guerreiro.controle_estado = timer; // velocidade de modificação do sprite guerreiro
    inimigos.goblins_guerreiros.goblins[0].controle_estado = timer;// velocidade de modificação do sprite goblin1
    inimigos.goblins_guerreiros.goblins[1].controle_estado = timer;// velocidade de modificação do sprite goblin1

    // Processo de repetição principal
    while (!exit_program)
    {
        // loop válido
        while(ticks<=timer && !exit_program)
        {
            // termina jogo se pressionar esc
            if(key[KEY_ESC])
                fecha_programa();

            // tela de menu
            if(tela==0)
            {
                clear_bitmap(buffer);
                keyboard_input();

                menu_inicial(buffer, &selecionar, menu_iniciar, menu_options, menu_exit, &loading_time, &tela);
            }

            // tela de loading
            else if (tela == 9)
            {
                clear_bitmap(buffer);
                tela_carregamento(buffer, tela_loading, &loading_time, &tela);

            }

            // tela de jogo
            else if(tela==1)
            {
                if(carrega_fase)// carrega todos os elementos da fase
                {
                    prepara_mapa(matriz_tela, nome_fase[fase-1]); // preenche matriz com os tilesets corretos
                    carregar_var_fase(fase,&itens,&guerreiro,&inimigos,&janelas,background,texturas,&eventos);
                    carrega_mapa(mapa,texturas,matriz_tela); // cria mapa com as texturas
                    carrega_fase=0;
                }

                // atualiza estado do teclado
                keyboard_input();

                if (apertou(KEY_SPACE))
                {
                    if (pause == TRUE)
                        pause = FALSE;
                    else
                        pause = TRUE;
                }

                // limpa bitmaps de armazenamento
                clear_bitmap(buffer); // Limpa o buffer;
                clear_bitmap(guerreiro.sprite); // Limpa bitmap guerreiro
                clear_bitmap(inimigos.goblins_guerreiros.goblins[0].sprite); // Limpa bitmap goblin tipo 1
                clear_bitmap(inimigos.goblins_guerreiros.goblins[1].sprite); // Limpa bitmap goblin tipo 1

                if (!pause)
                {
                    // incrementa o tempo de jogo
                    tempo_de_jogo++;

                    // Lógica do jogo
                    tocou_oponente(&guerreiro,&inimigos,tempo_de_jogo);
                    if(guerreiro.tempo_dano+20<=tempo_de_jogo)
                        guerreiro.levando_dano=0;
                    movimento_guerreiro(&guerreiro,matriz_tela, bloqueios);
                    ataque_guerreiro(&guerreiro,tempo_de_jogo,&inimigos);

                    if(guerreiro.x>=SCREEN_W/2 && guerreiro.x <= (LARGURA_MAPA-SCREEN_W/2))
                        ajuste_mapa=(-1)*(guerreiro.x-SCREEN_W/2);
                    else if(guerreiro.x<SCREEN_W/2)
                        ajuste_mapa=0;
                    else
                        ajuste_mapa=(-1)*(LARGURA_MAPA-SCREEN_W);

                    for(i=0;i<inimigos.goblins_guerreiros.n_goblins;i++)
                    {
                        movimento_goblin_guerreiro(&inimigos.goblins_guerreiros.goblins[i],&guerreiro,tempo_de_jogo,matriz_tela,bloqueios);
                        ataque_goblin_guerreiro(&inimigos.goblins_guerreiros.goblins[i],&guerreiro,tempo_de_jogo);
                    }

                    verifique_efeito_item(&itens,&guerreiro);
                }

                verificar_evento(&pause,fase,&eventos,&guerreiro,&janelas);

                // Desenhar
                draw_sprite(buffer,background,ajuste_mapa/10,0);
                draw_sprite(buffer, mapa, ajuste_mapa, 0); // manda mapa para o buffer na posição mov_mapa

                for(i=0;i<inimigos.goblins_guerreiros.n_goblins;i++)
                {
                    if(inimigos.goblins_guerreiros.goblins[i].caracteristicas.hp<=0
                            && !inimigos.goblins_guerreiros.goblins[i].levando_dano)
                        inimigos.goblins_guerreiros.goblins[i].estado_sprite=0;
                    desenhar_goblin_guerreiro(buffer,&inimigos.goblins_guerreiros.goblins[i],ajuste_mapa); // desenha goblin tipo 1 e manda para o buffer
                }

                desenhar_guerreiro(buffer,&guerreiro,ajuste_mapa); // desenha guerreiro e manda para buffer

                if (itens.todosItens[0].ativo)desenhar_item(buffer,&itens.todosItens[0],ajuste_mapa);

                desenhos_evento(buffer,fase,&eventos,&janelas,&guerreiro,corpo_texto,titulo_texto);

                if(pause) // o que acontece em um pause
                {
                    if(eventos.evento_atual==0)
                    {
                        // coloca tela cinza por cima da tela atual
                        drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
                        set_trans_blender(255,0,0,150);
                        rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(160,160,160));
                        solid_mode();
                    }
                }

                blit(buffer,screen,0,0,0,0,LARGURA_SCREEN,ALTURA_SCREEN); // Manda o buffer para a tela;

                // nova fase
                if(guerreiro.x +guerreiro.largura >= LARGURA_MAPA-50 && fase<N_FASES)
                {
                    carrega_fase=1;
                    fase++;
                    tela=9; // a próxima tela será a de loading game
                    loading_time = timer;
                }

            }
            ticks++; // incrementa controle de velocidade do jogo
        }
    }

    deinit(); // finaliza

    // destruição de bitmaps
    destroy_bitmap(buffer);
    destroy_bitmap(mapa);
    destroy_bitmap(bg);
    destroy_bitmap(menu_iniciar);
    destroy_bitmap(menu_options);
    destroy_bitmap(menu_exit);
    destroy_bitmap(background);
    for (i = 0; i < 4; i++)
    {
        destroy_bitmap(tela_loading[i]);
    }

    for(i=0;i<MAX_TERRENOS;i++)
    {
        destroy_bitmap(texturas[i]);
    }
    for(i=0;i<8;i++)
    {
        destroy_bitmap(guerreiro.vetor_sprite[i]);
    }
    for(i=0;i<10;i++)
    {
        destroy_bitmap(guerreiro.barraHp[i]);
    }
    for(i=0;i<7;i++)
    {
        destroy_bitmap(inimigos.goblins_guerreiros.goblins[0].vetor_sprite[i]);
        destroy_bitmap(inimigos.goblins_guerreiros.goblins[1].vetor_sprite[i]);
    }
    destroy_bitmap(guerreiro.sprite);
    destroy_bitmap(guerreiro.face);
    destroy_bitmap(inimigos.goblins_guerreiros.goblins[0].sprite);
    destroy_bitmap(inimigos.goblins_guerreiros.goblins[1].sprite);
    destroy_font(corpo_texto);
    destroy_font(titulo_texto);
    destroy_bitmap(itens.todosItens[0].imagem);

    return 0 ;
}
END_OF_MAIN(); // para finalizar o main no allegro
