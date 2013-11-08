#include <stdio.h>
#include <allegro.h>
#include <string.h>

void init(); // criação da janela, instalação do teclado, mouse e timer
void deinit();// finaliza tudo

// ".." significa uma pasta acima
#define LINKRELAT "../../Dropbox/"
/*
######################### Processo para usar imagens no projeto em desenvolvimento ########################

Questão: O repositório não pode conter os arquivos de imagens (que serão muitas, e o repositório
tem espaço limitado), e essas imagens deverão estar compartilhadas entre os membros do grupo.

Resolução: Usar o Dropbox para os arquivos de imagens, e se referir a elas através de um caminho relativo.

Nova questão: após o projeto terminar, a pasta com todas as imagens deverão estar na pasta do projeto. Assim,
todos os links irão mudar, e deverão ser alterados manualmente.

Resolução: Ao invés disso, podemos contornar esse problema usando uma constante que adiciona uma string em
cada link. Siga esses procedimentos:

1. Em cada arquivo que for trabalhar, tenha a certeza de definir uma contante fora de qualquer função,
no topo, e uma variável char de tamanho 256 dentro de cada função que referenciar imagens:
    #define LINKRELAT "../../Dropbox/"
    char link_imagem[256];

2. Observe que a constante acima está definida com um valor relativo. Mantenha assim durante a execução
do projeto.

3. Antes de referenciar cada imagem, use a função strcpy (você irá precisar da biblioteca string.h) para
inserir a constante LINKRELAT na variável link_imagem:
    strcpy(link_imagem,LINKRELAT);

4. Na referência à imagem, use a função strcat para juntar o conteúdo de link_imagem ao caminho relativo
desejado. Por exemplo, para carregar um BITMAP do guerreiro, usamos (observe que o primeiro argumento
de load_bitmap é um caminho relativo, e usamos strcat para concatenar o conteúdo de link_imagem com
a string restante para a imagem desejada):
    BITMAP *guerreiro = load_bitmap(strcat(link_imagem,"imagens_p1/guerreiro.bmp"), NULL);

Após a conclusão do projeto, pegue a pasta com as imagens (neste caso, imagens_p1), e coloque na pasta do
projeto. E simplesmente mude todas as constantes LINKREALT de todos os arquivos para "" (string vazia).
Não serão necessárias alterações adicionais.

##########################################################################################################
*/

int main()
{
    init(); // inicializa
    // declaração das variáveis
    float x = 30; // posição x herói
    float y = 330; // posição y herói
    float x2 = 330; // posição x goblin
    float y2 = 330; // posição y goblin
    float dir = 1; // direção goblin (1 para direita, 2 para esquerda)
    char link_imagem[256]; // necessário para os links das imagens

    BITMAP *buffer = create_bitmap(640,480); // Cria o buffer;

    // a primeira linha a seguir é necessária ao se referenciar cada imagem
    strcpy(link_imagem,LINKRELAT); // copia a string da constante LINKRELAT para link_imagem
    BITMAP *tela = load_bitmap(strcat(link_imagem,"imagens_p1/tela.bmp"),NULL); // imagem cenário
    strcpy(link_imagem,LINKRELAT);
    BITMAP *guerreiro = load_bitmap(strcat(link_imagem,"imagens_p1/guerreiro.bmp"), NULL); // imagem guerreiro
    strcpy(link_imagem,LINKRELAT);
    BITMAP *goblin1 = load_bitmap(strcat(link_imagem,"imagens_p1/goblin1.bmp"),NULL); // imagem goblin
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
