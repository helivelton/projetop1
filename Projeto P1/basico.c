#include "basico.h"

void init()
{
    int res;
    allegro_init();

    set_color_depth(32);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, LARGURA_TELA , ALTURA_TELA , 0 , 0 ); // cria tela 640x480

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

char *link_imagem(char caminho[256])
{
    char adicao[256]=LINKRELAT;
    strcat(adicao,caminho);
    return adicao;
}
