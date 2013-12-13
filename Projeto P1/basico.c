#include "basico.h"

// fun��o de sa�da
void fecha_programa(){exit_program = TRUE;}
END_OF_FUNCTION(fecha_programa)

//  fun��o tempo
void incrementa_timer(){timer++;}
END_OF_FUNCTION(incrementa_timer)

void init()
{
    int res;
    allegro_init();

    set_color_depth(32);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, LARGURA_SCREEN , ALTURA_SCREEN , 0 , 0 ); // cria tela 640x480

    if (res != 0 ) // verifica se houve erro na cria��o da tela
    {
        allegro_message(allegro_error);
        exit( -1 );
    }
    // instala��o do timer, teclado e mouse
    install_timer();
    install_keyboard();
    install_mouse();
}

void deinit()
{
    clear_keybuf(); // libera espa�o
}

char *link_imagem(char caminho[256])
{
    char adicao[256]=LINKRELAT;
    strcat(adicao,caminho);
    return adicao;
}

void desenhar_retangulo(BITMAP *buffer,int pos_x,int pos_y,int largura,int altura,int transparencia)
{
    drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
    set_trans_blender(255,0,0,transparencia);
    rectfill(buffer,pos_x,pos_y,pos_x+largura,pos_y+altura,makecol(0,0,160));
    rectfill(buffer,pos_x+5,pos_y+5,pos_x+largura-5,pos_y+altura-5,makecol(45,145,255));
    solid_mode();
}

void janela_texto(BITMAP *buffer,int pos_x,int pos_y,int largura,int altura,
                  char texto_titulo[256],char texto_corpo[256], FONT* titulo,FONT* corpo,int transparencia,
                  int inicio,int fim,int tempo_jogo)
{
    if(tempo_jogo>=inicio)
    {
        if (tempo_jogo<inicio+20)
            desenhar_retangulo(buffer,pos_x,pos_y,(largura/20)*(tempo_jogo-inicio),(altura/20)*(tempo_jogo-inicio),transparencia);
        else if((tempo_jogo > (fim-60)+40)&&(fim!=-1))
            desenhar_retangulo(buffer,pos_x,pos_y,(largura/20)*(fim-tempo_jogo),(altura/20)*(fim-tempo_jogo),transparencia);
        else
        {
            desenhar_retangulo(buffer,pos_x,pos_y,largura,altura,transparencia);
            textprintf_ex(buffer,titulo,pos_x+10,pos_y+10,makecol(0,0,150),-1,"%s",texto_titulo);
            textprintf_ex(buffer,corpo,pos_x+10,pos_y+30,makecol(250,250,250),-1,"%s",texto_corpo);
        }
    }
}

void janela_variavel(BITMAP *buffer,int pos_x,int pos_y,int largura,int altura,int variavel, FONT* fonte,int transparencia)
{
    desenhar_retangulo(buffer,pos_x,pos_y,largura,altura,transparencia);
    textprintf_ex(buffer,fonte,pos_x+15,pos_y+10,makecol(0,0,150),-1,"%d",variavel);
}

void janela_dialogo(BITMAP *buffer,Tcriatura *personagem,int pos_x,int pos_y,FONT* titulo,FONT* corpo,
                    int inicio, int fim, int tempo_jogo,char texto_titulo[50],char texto_corpo[256])
{

    janela_texto(buffer,pos_x,pos_y,106,106,"","",titulo,corpo,150,inicio,fim, tempo_jogo);
    janela_texto(buffer,pos_x+107,pos_y,300,106,texto_titulo,texto_corpo,titulo,corpo,150,inicio,fim, tempo_jogo);
    if(fim==-1 && tempo_jogo>inicio+20)
    {
        draw_sprite(buffer,personagem->face,pos_x+5,pos_y+5);
        if((tempo_jogo/16)%2==0)
        {
            rectfill(buffer,pos_x+380,pos_y+80,pos_x+380+10,pos_y+80+10,makecol(200,0,0));
        }
        else
        {
            rectfill(buffer,pos_x+380,pos_y+70,pos_x+380+10,pos_y+70+10,makecol(200,0,0));
        }
    }
}