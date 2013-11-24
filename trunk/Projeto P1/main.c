/*  #################################################################################
    #includes

    Inclua somente arquivos h do projeto
    As bibliotecas básicas são incluídas em básico.h
*/
#include "basico.h"
#include "mapa.h"
#include "criaturas.h"
#include "controle.h"
//  #################################################################################

// variável e função de saída
volatile int exit_program;
void fecha_programa(){exit_program = TRUE;}
END_OF_FUNCTION(fecha_programa)

// variavel e função tempo
volatile int timer;
void incrementa_timer(){timer++;}
END_OF_FUNCTION(incrementa_timer)

int main()
{
    init(); // inicializa

/*  #######################################################################################
                    declaração das variáveis (e algumas inicializações)
    #######################################################################################
*/
    int i; // controlador de loops e auxiliares
    int ticks; // controla velocidade do jogo
    int matriz_tela[ALTURA_TELA/32][LARGURA_TELA/32]; // matriz da tela
    int mov_mapa=0; // variável que cuida do movimento do mapa

    // variáveis de status
    Tcriatura guerreiro_status; // declara status guerreiro
    Tcriatura goblin1_status; // declara status goblin

    // declara BITMAPS
    BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H); // Cria o buffer;
    BITMAP *mapa = create_bitmap(LARGURA_TELA,ALTURA_TELA); // Cria o mapa
    BITMAP *texturas[MAX_TERRENOS]; // declara a array de texturas
    BITMAP *im_guerreiro[4]; // array de bitmaps do guerreiro
    BITMAP *guerreiro = create_bitmap(32,48); // imagem atual guerreiro
    BITMAP *im_goblin1[3]; // array de bitmaps do goblin tipo 1
    BITMAP *goblin1 = create_bitmap(32,48); // imagem atual goblin tipo 1

/*  #######################################################################################
                                fim da declaração das variáveis
    #######################################################################################
*/
    // carregamento inicial
    preenche_criatura(&guerreiro_status,0,12*32-(48-ALTURA_SPRITE)/2,1,0,2,2,2,1,0); // preenche status guerreiro
    imagens_guerreiro(im_guerreiro); // preenche vetor de imagens do guerreiro
    preenche_criatura(&goblin1_status,SCREEN_W-50,12*32-(48-ALTURA_SPRITE)/2,2,0,1,1,1,0,0); // preenche status goblin
    imagens_goblin1(im_goblin1); // preenche vetor de imagens do goblin tipo 1
    carrega_texturas(texturas); // prepara as texturas
    prepara_mapa(&matriz_tela); // preenche matriz com os tilesets corretos
    carrega_mapa(mapa,texturas,matriz_tela); // cria mapa com as texturas

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
    guerreiro_status.controle_estado = timer; // velocidade de modificação do sprite guerreiro
    goblin1_status.controle_estado = timer; // velocidade de modificação do sprite goblin1

    // Processo de repetição principal
    while (!exit_program)
    {
        // termina jogo se pressionar esc
        if(key[KEY_ESC])
            fecha_programa();

        // loop válido
        while(ticks==timer)
        {
            // limpa bitmaps de armazenamento
            clear_bitmap(buffer); // Limpa o buffer;
            clear_bitmap(guerreiro); // Limpa bitmap guerreiro
            clear_bitmap(goblin1); // Limpa bitmap goblin tipo 1

            // atualiza estado do teclado
            keyboard_input();

            // cálculos dos movimentos
            movimento_guerreiro(&guerreiro_status,timer,&mov_mapa);
            goblin1_status.x -= goblin1_status.ajuste_x - mov_mapa; // ajusta posição goblin com mov_mapa
            movimento_goblin1(&goblin1_status,guerreiro_status.x,timer);
            goblin1_status.ajuste_x = mov_mapa; // evita acumulação no próximo ajuste mapa (se houver)

            // Desenhar
            draw_sprite(buffer, mapa, mov_mapa, 0); // manda mapa para o buffer na posição mov_mapa
            desenhar_goblin1(buffer,goblin1,&goblin1_status,im_goblin1); // desenha goblin tipo 1 e manda para o buffer
            desenhar_guerreiro(buffer,guerreiro,&guerreiro_status,im_guerreiro); // desenha guerreiro e manda para buffer
            textout_ex(buffer, font, "Kill Goblins", 250,2, makecol(255,255,255 ),-1 ); // manda texto para buffer
            textprintf_right_ex(buffer,font,SCREEN_W,0,makecol(255,255,255),-1,"%d",timer/60); // desenha tempo
            draw_sprite(screen, buffer, 0, 0); // Manda o buffer para a tela;
            ticks++; // incrementa controle de velocidade do jogo
        }
    }

    deinit(); // finaliza

    // destruição de bitmaps
    destroy_bitmap(buffer);
    destroy_bitmap(mapa);
    for(i=0;i<MAX_TERRENOS;i++)
    {
        destroy_bitmap(texturas[i]);
    }
    for(i=0;i<4;i++)
    {
        destroy_bitmap(im_guerreiro[i]);
    }
    for(i=0;i<3;i++)
    {
        destroy_bitmap(im_goblin1[i]);
    }
    destroy_bitmap(guerreiro);
    destroy_bitmap(goblin1);

    return 0 ;
}
END_OF_MAIN(); // para finalizar o main no allegro
