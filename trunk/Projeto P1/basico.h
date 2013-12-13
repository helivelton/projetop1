#ifndef BASICO_H
#define BASICO_H

/*  #############################################################################
    Todas as bibliotecas básicas usadas no projeto

*/
#include <stdio.h>
#include <allegro.h>
#include <string.h>
//  #############################################################################

/*  #############################################################################
    Todos os defines usados no projeto

*/
// corrige link das imagens
#define LINKRELAT "../../Dropbox/"
// Altura e largura dos sprites do jogo
#define ALTURA_SPRITE 34
#define LARGURA_SPRITE 18
// controla velocidade padrão dos sprites
#define VELOCIDADE 3
// controla velocidade padrão de mudança dos estados dos sprites
#define ATUALIZAR_ESTADO 10
// Altura e largura da tela da screen
#define ALTURA_SCREEN 480
#define LARGURA_SCREEN 640
// Altura e largura das fases
#define ALTURA_MAPA 480
#define LARGURA_MAPA 640*5
// Nível do chão
#define NIVEL_CHAO 13*32
// Altura máxima do pulo
#define ALTURA_PULO 9*32+16
//  #############################################################################

volatile int exit_program; // variável de saída
volatile int timer; // variável de tempo

// tipos atributo e criatura
typedef struct atributo
{
    int forca;
    int habilidade;
    int resistencia;
    int armadura;
    int poder_de_fogo;
    int hp;
    int mp;
}Tatributo;

typedef struct criatura
{
    float x;
    float y;
    float largura;
    float altura;
    int direcao;
    int direcao_anterior;
    int estado_sprite; // estado atual
    int controle_estado; // verifica certos intervalos de tempo
    int caindo;
    int pulando;
    int permitir_pulo;
    BITMAP *sprite;
    BITMAP *vetor_sprite[4];
    BITMAP *face;
    Tatributo caracteristicas;
}Tcriatura;


/*
    Cabeçalhos das funções
*/

// criação da janela, instalação do teclado, mouse e timer
void init();

// finaliza tudo
void deinit();

// Use para corrigir os links das imagens
char *link_imagem(char caminho[256]);

// funções de janela ____________________________________________________________________________________________
void desenhar_retangulo(BITMAP *buffer,int pos_x,int pos_y,int largura,int altura,int transparencia);
void janela_texto(BITMAP *buffer,int pos_x,int pos_y,int largura,int altura,
                  char texto_titulo[256],char texto_corpo[256], FONT* titulo,FONT* corpo,int transparencia,
                  int inicio,int fim,int tempo_jogo);
void janela_variavel(BITMAP *buffer,int pos_x,int pos_y,int largura,int altura,int variavel, FONT* fonte,int transparencia);
void janela_dialogo(BITMAP *buffer,Tcriatura *personagem,int pos_x,int pos_y,FONT* titulo,FONT* corpo,int inicio,
                    int fim, int tempo_jogo, char texto_titulo[50],char texto_corpo[256]);
//_______________________________________________________________________________________________________________

// funções que controlam as variáveis globais timer e exit_program
void fecha_programa();
void incrementa_timer();

#endif // BASICO_H
