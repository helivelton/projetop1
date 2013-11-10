#include <stdio.h>
#include <allegro.h>
#include "basico.h" // link_imagem(), init(), deinit()

int main()
{
    init(); // inicializa
    // declara��o das vari�veis
    float x = 30; // posi��o x her�i
    float y = 330; // posi��o y her�i
    float x2 = 330; // posi��o x goblin
    float y2 = 330; // posi��o y goblin
    float dir = 1; // dire��o goblin (1 para direita, 2 para esquerda)

    BITMAP *buffer = create_bitmap(640,480); // Cria o buffer;
    BITMAP *tela = load_bitmap(link_imagem("imagens_p1/tela.bmp"),NULL); // imagem cen�rio
    BITMAP *guerreiro = load_bitmap(link_imagem("imagens_p1/guerreiro.bmp"), NULL); // imagem guerreiro
    BITMAP *goblin1 = load_bitmap(link_imagem("imagens_p1/goblin1.bmp"),NULL); // imagem goblin
    // fim da declara��o das vari�veis

    while (!key[KEY_ESC]) // Processo de repeti��o principal
    {
        clear_bitmap(buffer); // Limpa o buffer;
        // movimenta��o goblin
        if (x2 > x)
        {
            dir=2;
        }
        else if (x2 < x)
        {
            dir=1;
        }
        else
        {
            dir=0;
        }
        if(dir==1)
        {
            x2=x2+0.25;
        }
        else if(dir==2)
        {
            x2=x2-0.25;
        }
        // fim movimenta��o goblin

        // movimenta��o guerreiro
        if (key[KEY_RIGHT] && x < 550)
        {
            x=x+0.5;
        }
        else if (key[KEY_LEFT] && x > 0)
        {
            x=x-0.5;
        }
        // fim movimenta��o guerreiro

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
