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
    BITMAP *menu_iniciar = load_bitmap(link_imagem("imagens_p1/menu1.bmp"), NULL);//menu iniciar
    BITMAP *menu_creditos = load_bitmap(link_imagem("imagens_p1/menu3.bmp"),NULL);
    BITMAP *menu_options = load_bitmap (link_imagem("imagens_p1/menu2.bmp"), NULL);//menu opções
    BITMAP *menu_exit = load_bitmap (link_imagem("imagens_p1/menu4.bmp"), NULL);//menu saída

    BITMAP *logo = load_bitmap(link_imagem("imagens_p1/logo.bmp"),NULL);

    // BITMAPS da tela de carregamento
    BITMAP *tela_loading[4];
    tela_loading[0] = load_bitmap (link_imagem("imagens_p1/carregar1.bmp"), NULL);
    tela_loading[1] = load_bitmap (link_imagem("imagens_p1/carregar2.bmp"), NULL);
    tela_loading[2] = load_bitmap (link_imagem("imagens_p1/carregar3.bmp"), NULL);
    tela_loading[3] = load_bitmap (link_imagem("imagens_p1/carregar4.bmp"), NULL);

    // Declara fontes
    FONT* corpo_texto = load_font("fontes/corpo.pcx",NULL,NULL);
    FONT* titulo_texto = load_font("fontes/titulos.pcx",NULL,NULL);

    // Declara sons
    MIDI* musica_floresta = load_midi(link_imagem("imagens_p1/f1.mid"));
    MIDI* musica_caverna = load_midi(link_imagem("imagens_p1/c1.mid"));
    MIDI* musica_chefe1 = load_midi(link_imagem("imagens_p1/b1.mid"));
    MIDI* musica_chefe2 = load_midi(link_imagem("imagens_p1/b2.mid"));
    MIDI* musica_chefe3 = load_midi(link_imagem("imagens_p1/b3.mid"));
    MIDI* musica_menu = load_midi(link_imagem("imagens_p1/menu.mid"));
    MIDI* musica_gameover = load_midi(link_imagem("imagens_p1/gOver.mid"));

    SAMPLE* selecao = load_sample(link_imagem("imagens_p1/selec.wav"));
    SAMPLE* confirmar = load_sample(link_imagem("imagens_p1/conf.wav"));
    SAMPLE* espada = load_sample(link_imagem("imagens_p1/sword.wav"));
    SAMPLE* besta = load_sample(link_imagem("imagens_p1/bow.wav"));
    SAMPLE* som_pause = load_sample(link_imagem("imagens_p1/pause.wav"));
    SAMPLE* som_dano_goblin = load_sample(link_imagem("imagens_p1/GobD.wav"));
    SAMPLE* som_dano_guerreiro = load_sample(link_imagem("imagens_p1/heroD.wav"));
    SAMPLE* som_cura = load_sample(link_imagem("imagens_p1/cura.wav"));
    SAMPLE* som_vinhas = load_sample(link_imagem("imagens_p1/vinhas.wav"));
    SAMPLE* som_recuo = load_sample(link_imagem("imagens_p1/recuo.wav"));

    volume=255;
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
                                       &janelas,background,texturas,&eventos,mapa);
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
                    movimento_itens(&itens,&guerreiro,tempo_de_jogo);
                }

                verificar_evento(&pause,fase,&eventos,&guerreiro,&janelas,matriz_tela,bloqueios,&ajuste_mapa,musica_chefe1,
                                 musica_chefe2,musica_chefe3,confirmar);

                // Desenhar
                draw_sprite(buffer,background,ajuste_mapa/10,0);
                draw_sprite(buffer, mapa, ajuste_mapa, 0); // manda mapa para o buffer na posição mov_mapa
                desenhar_todos_goblins(&inimigos,buffer,ajuste_mapa,tempo_de_jogo);
                desenhar_guerreiro(buffer,&guerreiro,&inimigos,ajuste_mapa,tempo_de_jogo); // desenha guerreiro e manda para buffer
                desenhar_itens(buffer,&itens,ajuste_mapa);
                desenhos_evento(buffer,fase,&eventos,&janelas,&guerreiro,corpo_texto,titulo_texto,&inimigos);

                pause_menu(&pause,&eventos,buffer,&selecionar,&tela,tempo_de_jogo,&tela_destino,&loading_time,
                           selecao,confirmar,&tocando);
                game_over(&pause,&eventos,buffer,&selecionar,&tela,tempo_de_jogo,&tela_destino,&loading_time,selecao,confirmar,
                          &tocando,musica_gameover,&guerreiro,&estagio_loading,&tocando_game_over,&carrega_fase);

                blit(buffer,screen,0,0,0,0,LARGURA_SCREEN,ALTURA_SCREEN); // Manda o buffer para a tela;

                // nova fase?
                verifica_nova_fase(&guerreiro,&fase,&carrega_fase,&tela,&loading_time,&estagio_loading,&tela_destino,
                                   &inimigos.chefes,&eventos,&tocando);
            }
            ticks++; // incrementa controle de velocidade do jogo
        }
    }

    deinit(); // finaliza

    // destruição de bitmaps
    destroy_bitmap(buffer);
    destroy_bitmap(mapa);
    destroy_bitmap(menu_iniciar);
    destroy_bitmap(menu_options);
    destroy_bitmap(menu_creditos);
    destroy_bitmap(menu_exit);
    destroy_bitmap(logo);
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
    for(i=0;i<8;i++)
    {
        destroy_bitmap(inimigos.goblins_guerreiros.goblins[0].vetor_sprite[i]);
        destroy_bitmap(inimigos.goblins_guerreiros.goblins[1].vetor_sprite[i]);

        if(i!=7)destroy_bitmap(inimigos.goblins_arqueiros.goblins[0].vetor_sprite[i]);
        if(i!=7)destroy_bitmap(inimigos.goblins_arqueiros.goblins[1].vetor_sprite[i]);

        destroy_bitmap(inimigos.chefes.chefe[0].vetor_sprite[i]);
    }
    destroy_bitmap(guerreiro.sprite);
    destroy_bitmap(guerreiro.face);

    destroy_bitmap(inimigos.goblins_guerreiros.goblins[0].sprite);
    destroy_bitmap(inimigos.goblins_guerreiros.goblins[1].sprite);
    destroy_bitmap(inimigos.goblins_arqueiros.goblins[0].sprite);
    destroy_bitmap(inimigos.goblins_arqueiros.goblins[1].sprite);
    destroy_bitmap(inimigos.chefes.chefe[0].sprite);

    destroy_font(corpo_texto);
    destroy_font(titulo_texto);

    destroy_bitmap(itens.todosItens[0].imagem);
    destroy_bitmap(itens.todosItens[1].imagem);
    destroy_bitmap(itens.todosItens[2].imagem);
    destroy_bitmap(itens.todosItens[0].imagem_buffer);
    destroy_bitmap(itens.todosItens[1].imagem_buffer);
    destroy_bitmap(itens.todosItens[2].imagem_buffer);

    destroy_midi(musica_floresta);
    destroy_midi(musica_caverna);
    destroy_midi(musica_chefe1);
    destroy_midi(musica_chefe2);
    destroy_midi(musica_chefe3);
    destroy_midi(musica_menu);
    destroy_midi(musica_gameover);

    destroy_sample(selecao);
    destroy_sample(confirmar);
    destroy_sample(espada);
    destroy_sample(besta);
    destroy_sample(som_pause);
    destroy_sample(som_dano_goblin);
    destroy_sample(som_dano_guerreiro);
    destroy_sample(som_cura);
    destroy_sample(som_vinhas);
    destroy_sample(som_recuo);

    return 0 ;
}
END_OF_MAIN(); // para finalizar o main no allegro
