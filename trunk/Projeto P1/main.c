#include <stdio.h>
#include <allegro.h>
#include "basico.h" // link_imagem(), init(), deinit()
#include "mapa.h"
#include "criaturas.h"
#include "controle.h"

#define VELOCIDADE 3
#define ATUALIZAR_ESTADO 6

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
    // declaração das variáveis
    int i;

    // guerreiro
    Tcriatura guerreiro_status;
    preenche_guerreiro(&guerreiro_status);

    float x2 = 330; // posição x goblin
    float y2 = 12*32+(32-ALTURA_GOBLIN); // posição y goblin
    float dir = 1; // direção goblin (1 para direita, 2 para esquerda)

    BITMAP *buffer = create_bitmap(640,480); // Cria o buffer;
    BITMAP *mapa = create_bitmap(640,480); // Cria o mapa
    BITMAP *texturas[MAX_TEXTURAS]; // declara a array de texturas
    carrega_texturas(texturas); // prepara a textura
    carrega_mapa(mapa,texturas); // cria mapa

    BITMAP *im_guerreiro[4];
    imagens_guerreiro(im_guerreiro);
    BITMAP *guerreiro = create_bitmap(32,48); // imagem guerreiro
    BITMAP *goblin1 = load_bitmap(link_imagem("imagens_p1/skel.bmp"),NULL); // imagem goblin
    // fim da declaração das variáveis

    // configura saída com o botão x no alto da tela
    exit_program = FALSE;
    LOCK_FUNCTION(fecha_programa);
    LOCK_VARIABLE(exit_program);
    set_close_button_callback(fecha_programa);

    // timer
    timer=0;
    LOCK_FUNCTION(incrementa_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementa_timer,BPS_TO_TIMER(60));

    int ticks = timer;
    int controle_estados_sprites = timer;
    while (!exit_program) // Processo de repetição principal
    {
        if(key[KEY_ESC])
            fecha_programa();
        while(ticks==timer)
        {
            clear_bitmap(buffer); // Limpa o buffer;
            clear_bitmap(guerreiro);
            keyboard_input();
            // movimentação goblin
            if (x2 > guerreiro_status.x)
            {
                dir=2;
            }
            else if (x2 < guerreiro_status.x)
            {
                dir=1;
            }
            else
            {
                dir=0;
            }
            if(dir==1)
            {
                x2=x2+VELOCIDADE/2;
            }
            else if(dir==2)
            {
                x2=x2-VELOCIDADE/2;
            }
            // fim movimentação goblin

            // movimentação guerreiro
            if (segurou(KEY_RIGHT) && guerreiro_status.x < SCREEN_W-32)
            {
                guerreiro_status.x=guerreiro_status.x+VELOCIDADE;
                if (timer-controle_estados_sprites>=ATUALIZAR_ESTADO)
                {
                    controle_estados_sprites=timer;
                    guerreiro_status.estado_sprite=(guerreiro_status.estado_sprite+1)%4;
                }
                guerreiro_status.direcao =1;
            }
            else if (segurou(KEY_LEFT) && guerreiro_status.x > 0)
            {
                guerreiro_status.x=guerreiro_status.x-VELOCIDADE;
                if (timer-controle_estados_sprites>=ATUALIZAR_ESTADO)
                {
                    controle_estados_sprites=timer;
                    guerreiro_status.estado_sprite=(guerreiro_status.estado_sprite+1)%4;
                }
                guerreiro_status.direcao = 2;
            }
            // fim movimentação guerreiro

            draw_sprite(buffer, mapa, 0, 0); // manda mapa para o buffer
            draw_sprite(buffer, goblin1, x2, y2); // manda goblin para buffer
            rectfill(guerreiro,0,0,32,48,makecol(255,0,255));
            if(guerreiro_status.direcao==1)
            {
                draw_sprite_ex(guerreiro,im_guerreiro[guerreiro_status.estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
            }
            else
            {
                draw_sprite_ex(guerreiro,im_guerreiro[guerreiro_status.estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
            }

            draw_sprite(buffer, guerreiro, guerreiro_status.x, guerreiro_status.y); // manda guerreiro para buffer
            textout_ex(buffer, font, "Kill Goblins", 250,2, makecol(255,255,255 ),-1 ); // manda texto para buffer
            textprintf_right_ex(buffer,font,SCREEN_W,0,makecol(255,255,255),-1,"%d",timer/60);
            draw_sprite(screen, buffer, 0, 0); // Manda o buffer para a tela;
            ticks++;
        }
    }

    deinit(); // finaliza

    // destruição de bitmaps
    destroy_bitmap(buffer);
    destroy_bitmap(mapa);
    for(i=0;i<MAX_TEXTURAS;i++)
    {
        destroy_bitmap(texturas[i]);
    }
    for(i=0;i<4;i++)
    {
        destroy_bitmap(im_guerreiro[i]);
    }
    destroy_bitmap(guerreiro);
    destroy_bitmap(goblin1);
    return 0 ;
}
END_OF_MAIN(); // para finalizar o main no allegro
