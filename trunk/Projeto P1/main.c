#include <allegro.h>

void init(); // criação da janela, instalação do teclado, mouse e timer
void deinit();// finaliza tudo

int main()
{
    init(); // inicializa
    // declaração das variáveis
    float x = 30; // posição x herói
    float y = 330; // posição y herói
    float x2 = 330; // posição x goblin
    float y2 = 330; // posição y goblin
    float dir = 1; // direção goblin (1 para direita, 2 para esquerda)

    BITMAP *buffer = create_bitmap(640,480); // Cria o buffer;
    BITMAP *tela = load_bitmap("imagens/tela.bmp",NULL); // imagem cenário
    BITMAP *guerreiro = load_bitmap("imagens/guerreiro.bmp", NULL); // imagem guerreiro
    BITMAP *goblin1 = load_bitmap("imagens/goblin1.bmp",NULL); // imagem goblin
    // fim da declaração das variáveis

    while (!key[KEY_ESC]) // Processo de repetição principal
    {
        clear_bitmap(buffer); // Limpa o buffer;
        // movimentação goblin
        if (x2 > 500)
        {
            dir=2;
        }
        else if (x2 < 50)
        {
            dir=1;
        }
        if(dir==1)
        {
            x2=x2+0.25;
        }
        else
        {
            x2=x2-0.25;
        }
        // fim movimentação goblin

        // movimentação guerreiro
        if (key[KEY_RIGHT] && x < 550)
        {
            x=x+0.5;
        }
        else if (key[KEY_LEFT] && x > 0)
        {
            x=x-0.5;
        }
        // fim movimentação guerreiro

        draw_sprite(buffer, tela, 0, 0); // manda tela para o buffer
        draw_sprite(buffer, goblin1, x2, y2); // manda goblin para buffer
        draw_sprite(buffer, guerreiro, x, y); // manda guerreiro para buffer
        textout_ex(buffer, font, "Kill Goblins", 250,2, makecol(255,255,255 ),-1 ); // manda texto para buffer
        draw_sprite(screen, buffer, 0, 0); // Manda o buffer para a tela;

    }

    deinit(); // finaliza
    return 0 ;
}
END_OF_MAIN(); // para finalizar o main no allegro

void init()
{
    int res;
    allegro_init();

    set_color_depth(32);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640 , 480 , 0 , 0 ); // cria tela 640x480

    if (res != 0 ) // verifica se houve erro na criação da tela
    {
        allegro_message(allegro_error);
        exit( -1 );
    }
    // instalação do timer, teclado e mouse
    install_timer();
    install_keyboard();
    install_mouse();
}
void deinit()
{
    clear_keybuf(); // libera espaço
}
