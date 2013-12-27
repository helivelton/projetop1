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
    int janela_atual = 0; // controla janela atual
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
    BITMAP *background = create_bitmap(960,480);

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

    // declara BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H); // Cria o buffer;
    BITMAP *mapa = create_bitmap(LARGURA_MAPA,ALTURA_MAPA); // Cria o mapa
    BITMAP *texturas[MAX_TERRENOS]; // declara a array de texturas

    // Declara fontes
    FONT* corpo_texto = load_font("fontes/corpo.pcx",NULL,NULL);
    FONT* titulo_texto = load_font("fontes/titulos.pcx",NULL,NULL);

/*  #######################################################################################
                                fim da declaração das variáveis
    #######################################################################################
*/
    // carregamento inicial
    itens.n_itens = 0;
    preencher_item(&itens.todosItens[0],550,NIVEL_CHAO-20,20,15,"imagens_p1/Itens1.bmp",6,12,1,1);
    itens.n_itens+=1;

    preenche_criatura(&guerreiro,0,NIVEL_CHAO-34,20,34,1,2,3,2,1,0); // preenche status guerreiro
    imagens_guerreiro(&guerreiro); // preenche vetor de imagens do guerreiro

    inimigos.goblins_guerreiros.n_goblins=0;
    inimigos.goblins_arqueiros.n_goblins=0;
    inimigos.chefes.chefe_atual=0;
    preenche_criatura(&inimigos.goblins_guerreiros.goblins[0],SCREEN_W-50,NIVEL_CHAO-32,28,32,2,1,1,2,0,0); // preenche status goblin
    inimigos.goblins_guerreiros.n_goblins+=1;
    imagens_goblin_guerreiro(&inimigos.goblins_guerreiros.goblins[0]); // preenche vetor de imagens do goblin tipo 1
    preenche_criatura(&inimigos.goblins_guerreiros.goblins[1],750,NIVEL_CHAO-32,28,32,2,1,2,1,0,0); // preenche status goblin
    inimigos.goblins_guerreiros.n_goblins+=1;
    imagens_goblin_guerreiro(&inimigos.goblins_guerreiros.goblins[1]); // preenche vetor de imagens do goblin tipo 1
    carrega_texturas(texturas); // prepara as texturas

    janelas.n_janelas=0;
    preencher_janela(&janelas.total[0],70,300,0,0,0,0,0,"Joao","Oh, terrivel goblin esqueleto, irei mata-lo de novo, por todo o sempre.");
    janelas.n_janelas+=1;
    preencher_janela(&janelas.total[1],70,300,0,0,0,0,0,"Joao","Irei derrota-lo com certeza.");
    janelas.n_janelas+=1;

    BITMAP *fundo = load_bitmap(link_imagem("imagens_p1/Forest01.bmp"),NULL);
    clear_bitmap(background);
    draw_sprite(background,fundo,0,0);
    destroy_bitmap(fundo);

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

                    for(i=0;i<inimigos.goblins_guerreiros.n_goblins;i++)
                    {
                        movimento_goblin_guerreiro(&inimigos.goblins_guerreiros.goblins[i],&guerreiro,tempo_de_jogo,matriz_tela,bloqueios);
                        ataque_goblin_guerreiro(&inimigos.goblins_guerreiros.goblins[i],&guerreiro,tempo_de_jogo);
                    }

                    botao_w(&janela_atual,&janelas,tempo_de_jogo);

                    verifique_efeito(&itens,&guerreiro);

                }

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

                if(DEBUG)janela_texto(buffer,SCREEN_W/2-60,10,120,50,"Kill Goblins","",
                             titulo_texto,corpo_texto,150,0,-1,tempo_de_jogo,0); // desenha titulo
                if(DEBUG)janela_variavel(buffer,SCREEN_W-50,0,50,50,(tempo_de_jogo)/60,titulo_texto,40); // desenha tempo

                if(DEBUG)
                {
                    rectfill(buffer,guerreiro.x+ajuste_mapa,guerreiro.y,guerreiro.x+ajuste_mapa+1,guerreiro.y+1,makecol(0,0,160));
                    rectfill(buffer,guerreiro.x+guerreiro.largura+ajuste_mapa,guerreiro.y,guerreiro.x+guerreiro.largura+ajuste_mapa+1,guerreiro.y+1,makecol(0,0,160));
                    rectfill(buffer,LARGURA_SCREEN/2,guerreiro.y-5,LARGURA_SCREEN/2+1,guerreiro.y-4,makecol(0,255,0));
                    rectfill(buffer,0,guerreiro.y-5,1,guerreiro.y-4,makecol(0,255,0));
                    rectfill(buffer,LARGURA_SCREEN-1,guerreiro.y-5,LARGURA_SCREEN,guerreiro.y-4,makecol(0,255,0));
                    janela_texto(buffer,20,170,50,50,"x/32","",
                                 corpo_texto,corpo_texto,0,0,-1,tempo_de_jogo,0);
                    janela_texto(buffer,20,200,50,50,"x","",
                                 corpo_texto,corpo_texto,0,0,-1,tempo_de_jogo,0);
                    janela_texto(buffer,20,230,50,50,"x+l","",
                                 corpo_texto,corpo_texto,0,0,-1,tempo_de_jogo,0);
                    janela_texto(buffer,20,260,50,50,"y","",
                                 corpo_texto,corpo_texto,0,0,-1,tempo_de_jogo,0);
                    janela_texto(buffer,20,290,50,50,"y+a","",
                                 corpo_texto,corpo_texto,0,0,-1,tempo_de_jogo,0);
                    janela_texto(buffer,150,170,50,50,"pocaoX","",
                                 corpo_texto,corpo_texto,0,0,-1,tempo_de_jogo,0);
                    janela_texto(buffer,150,200,50,50,"pocaoY","",
                                 corpo_texto,corpo_texto,0,0,-1,tempo_de_jogo,0);
                    janela_texto(buffer,310,200,50,50,"goblinHP","",
                                 corpo_texto,corpo_texto,0,0,-1,tempo_de_jogo,0);
                    janela_texto(buffer,150,50,100,50,"GuerreiroHP","",
                                 corpo_texto,corpo_texto,0,0,-1,tempo_de_jogo,0);
                    janela_variavel(buffer,80,170,50,50,(guerreiro.x)/32,corpo_texto,0);
                    janela_variavel(buffer,50,200,50,50,guerreiro.x,corpo_texto,0);
                    janela_variavel(buffer,50,230,50,50,guerreiro.x+guerreiro.largura,corpo_texto,0);
                    janela_variavel(buffer,50,260,50,50,guerreiro.y,corpo_texto,0);
                    janela_variavel(buffer,50,290,50,50,guerreiro.y+guerreiro.altura,corpo_texto,0);
                    janela_variavel(buffer,250,50,50,50,guerreiro.caracteristicas.hp,titulo_texto,0);
                    janela_variavel(buffer,210,170,50,50,itens.todosItens[0].x,corpo_texto,0);
                    janela_variavel(buffer,210,200,50,50,itens.todosItens[0].y,corpo_texto,0);
                    janela_variavel(buffer,390,200,50,50,inimigos.goblins_guerreiros.goblins[0].caracteristicas.hp,corpo_texto,0);
                    janela_variavel(buffer,390,230,50,50,inimigos.goblins_guerreiros.goblins[1].caracteristicas.hp,corpo_texto,0);
                    janela_variavel(buffer,450,230,50,50,guerreiro.atacando,corpo_texto,0);
                    janela_variavel(buffer,450,260,50,50,inimigos.goblins_guerreiros.goblins[1].x,corpo_texto,0);
                    janela_variavel(buffer,500,260,50,50,inimigos.goblins_guerreiros.goblins[1].largura,corpo_texto,0);
                    janela_variavel(buffer,450,290,50,50,inimigos.goblins_guerreiros.goblins[1].y,corpo_texto,0);
                    janela_variavel(buffer,500,290,50,50,inimigos.goblins_guerreiros.goblins[1].altura,corpo_texto,0);
                }

                if(janela_atual==1) // teste de janela
                {
                    /*janela_texto(buffer,150,250,300,100,"Jaques","Oi, esse e meu nome.",
                             titulo_texto,corpo_texto,150,controle_janela[0],
                             controle_janela[1],tempo_de_jogo); // exemplo caixa texto*/
                    janela_dialogo(buffer,&guerreiro,janelas.total[0].x,janelas.total[0].y,titulo_texto,corpo_texto,
                                   janelas.total[0].tempo_inicio,janelas.total[0].tempo_fim,tempo_de_jogo,janelas.total[0].titulo,
                                   janelas.total[0].conteudo,1);
                    if(tempo_de_jogo==janelas.total[0].tempo_fim)
                        janela_atual=0;
                }
                else if(janela_atual==2)
                {
                    janela_dialogo(buffer,&guerreiro,janelas.total[1].x,janelas.total[1].y,titulo_texto,corpo_texto,
                                   janelas.total[1].tempo_inicio,janelas.total[1].tempo_fim,tempo_de_jogo,janelas.total[1].titulo,
                                   janelas.total[1].conteudo,0);
                    if(tempo_de_jogo==janelas.total[1].tempo_fim)
                        janela_atual=0;
                }

                if(pause) // o que acontece em um pause
                {
                    drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
                    set_trans_blender(255,0,0,150);
                    rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(160,160,160));
                    solid_mode();
                }

                blit(buffer,screen,0,0,0,0,LARGURA_SCREEN,ALTURA_SCREEN); // Manda o buffer para a tela;


                // nova fase
                if(guerreiro.x +guerreiro.largura >= LARGURA_MAPA-50 && fase<N_FASES)
                {
                    carrega_fase=1;
                    guerreiro.x = 10;
                    inimigos.goblins_guerreiros.goblins[0].x = 300;
                    inimigos.goblins_guerreiros.goblins[1].x = 500;
                    ajuste_mapa=0;
                    fase++;
                    tela=9;
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
