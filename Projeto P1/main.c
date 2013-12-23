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
    int mov_mapa[2]; // vetor que cuida do movimento do mapa e dos objetos nele
    mov_mapa[0]=0; // o primeiro índice controla com o segundo os objetos no mapa
    mov_mapa[1]=0;
    int janela_atual = 0; // controla janela atual
    Tjanela totalJanelas[15];
    int tela = 0, selecionar = 0; //controla o carregamento de cada tela
    int fase=1;
    int carrega_fase=1;
    char nome_fase[N_FASES][10]={"mapa1.txt","mapa2.txt","mapa3.txt"};
    int loading_time = 0;
    int bloqueios[3] = {TERRA, PEDRA, CHAO};

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
    Tcriatura guerreiro; // declara objeto guerreiro
    Tcriatura goblin1; // declara objeto goblin
    Titem pocao;
    preencher_item(&pocao,450,NIVEL_CHAO,20,15,"imagens_p1/Itens1.bmp",6,12);


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
    preenche_criatura(&guerreiro,0,NIVEL_CHAO-34,20,34,1,2,2,2,1,0); // preenche status guerreiro
    imagens_guerreiro(&guerreiro); // preenche vetor de imagens do guerreiro
    preenche_criatura(&goblin1,SCREEN_W-50,NIVEL_CHAO-36,18,36,2,1,1,1,0,0); // preenche status goblin
    imagens_goblin1(goblin1.vetor_sprite); // preenche vetor de imagens do goblin tipo 1
    carrega_texturas(texturas); // prepara as texturas
    preencher_janela(&totalJanelas[0],70,300,0,0,0,0,0,"Joao","Oh, terrivel goblin esqueleto, irei mata-lo de novo, por todo o sempre.");
    preencher_janela(&totalJanelas[1],70,300,0,0,0,0,0,"Joao","Irei derrota-lo com certeza.");

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
    goblin1.controle_estado = timer; // velocidade de modificação do sprite goblin1

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
                if(carrega_fase)
                {
                    prepara_mapa(matriz_tela, nome_fase[fase-1]); // preenche matriz com os tilesets corretos
                    carrega_mapa(mapa,texturas,matriz_tela); // cria mapa com as texturas
                    carrega_fase=0;
                }

                // incrementa o tempo de jogo
                tempo_de_jogo++;

                // limpa bitmaps de armazenamento
                clear_bitmap(buffer); // Limpa o buffer;
                clear_bitmap(guerreiro.sprite); // Limpa bitmap guerreiro
                clear_bitmap(goblin1.sprite); // Limpa bitmap goblin tipo 1

                // atualiza estado do teclado
                keyboard_input();

                // Lógica do jogo
                movimento_guerreiro(&guerreiro,mov_mapa,matriz_tela, bloqueios);
                goblin1.x += mov_mapa[0] - mov_mapa[1]; // ajusta posição goblin com mov_mapa
                movimento_goblin1(&goblin1,guerreiro.x);
                mov_mapa[1] = mov_mapa[0]; // evita acumulação no próximo ajuste mapa (se houver)

                botao_w(&janela_atual,totalJanelas,tempo_de_jogo);

                // Desenhar
                draw_sprite(buffer, mapa, mov_mapa[0], 0); // manda mapa para o buffer na posição mov_mapa
                desenhar_goblin1(buffer,&goblin1); // desenha goblin tipo 1 e manda para o buffer
                desenhar_guerreiro(buffer,&guerreiro); // desenha guerreiro e manda para buffer

                desenhar_item(buffer,&pocao,mov_mapa);

                janela_texto(buffer,SCREEN_W/2-60,10,120,50,"Kill Goblins","",
                             titulo_texto,corpo_texto,150,0,-1,tempo_de_jogo,0); // desenha titulo
                janela_variavel(buffer,SCREEN_W-50,0,50,50,(tempo_de_jogo)/60,titulo_texto,40); // desenha tempo

                if(DEBUG)
                {
                    rectfill(buffer,guerreiro.x,guerreiro.y,guerreiro.x+1,guerreiro.y+1,makecol(0,0,160));
                    rectfill(buffer,guerreiro.x+guerreiro.largura,guerreiro.y,guerreiro.x+guerreiro.largura+1,guerreiro.y+1,makecol(0,0,160));
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
                    janela_variavel(buffer,110,170,50,50,(guerreiro.x-mov_mapa[0])/32,corpo_texto,0);
                    janela_variavel(buffer,50,200,50,50,guerreiro.x-mov_mapa[0],corpo_texto,0);
                    janela_variavel(buffer,50,230,50,50,guerreiro.x+guerreiro.largura,corpo_texto,0);
                    janela_variavel(buffer,50,260,50,50,guerreiro.y,corpo_texto,0);
                    janela_variavel(buffer,50,290,50,50,guerreiro.y+guerreiro.altura,corpo_texto,0);
                }

                if(janela_atual==1) // teste de janela
                {
                    /*janela_texto(buffer,150,250,300,100,"Jaques","Oi, esse e meu nome.",
                             titulo_texto,corpo_texto,150,controle_janela[0],
                             controle_janela[1],tempo_de_jogo); // exemplo caixa texto*/
                    janela_dialogo(buffer,&guerreiro,totalJanelas[0].x,totalJanelas[0].y,titulo_texto,corpo_texto,
                                   totalJanelas[0].tempo_inicio,totalJanelas[0].tempo_fim,tempo_de_jogo,totalJanelas[0].titulo,
                                   totalJanelas[0].conteudo,1);
                    if(tempo_de_jogo==totalJanelas[0].tempo_fim)
                        janela_atual=0;
                }
                else if(janela_atual==2)
                {
                    janela_dialogo(buffer,&guerreiro,totalJanelas[1].x,totalJanelas[1].y,titulo_texto,corpo_texto,
                                   totalJanelas[1].tempo_inicio,totalJanelas[1].tempo_fim,tempo_de_jogo,totalJanelas[1].titulo,
                                   totalJanelas[1].conteudo,0);
                    if(tempo_de_jogo==totalJanelas[1].tempo_fim)
                        janela_atual=0;
                }

                if(colisao(guerreiro.x,guerreiro.y,guerreiro.altura,guerreiro.largura, goblin1.x, goblin1.y,goblin1.altura,goblin1.largura))
                    rectfill(buffer,50,50,100,100,makecol(0,0,160));

                blit(buffer,screen,0,0,0,0,LARGURA_SCREEN,ALTURA_SCREEN); // Manda o buffer para a tela;

                // nova fase
                if(guerreiro.x +guerreiro.largura -mov_mapa[0] >= LARGURA_MAPA-50 && fase<N_FASES)
                {
                    carrega_fase=1;
                    guerreiro.x = 10;
                    goblin1.x = 300;
                    mov_mapa[0]=0;
                    mov_mapa[1]=0;
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
    for (i = 0; i < 4; i++)
    {
        destroy_bitmap(tela_loading[i]);
    }

    for(i=0;i<MAX_TERRENOS;i++)
    {
        destroy_bitmap(texturas[i]);
    }
    for(i=0;i<4;i++)
    {
        destroy_bitmap(guerreiro.vetor_sprite[i]);
    }
    for(i=0;i<3;i++)
    {
        destroy_bitmap(goblin1.vetor_sprite[i]);
    }
    destroy_bitmap(guerreiro.sprite);
    destroy_bitmap(guerreiro.face);
    destroy_bitmap(goblin1.sprite);
    destroy_font(corpo_texto);
    destroy_font(titulo_texto);
    destroy_bitmap(pocao.imagem);

    return 0 ;
}
END_OF_MAIN(); // para finalizar o main no allegro
