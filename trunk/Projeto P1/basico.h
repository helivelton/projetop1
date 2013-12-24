#ifndef BASICO_H
#define BASICO_H

/*  #############################################################################
    Todas as bibliotecas básicas usadas no projeto

*/
#include <stdio.h>
#include <allegro.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

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
#define ALTURA_PULO 130
// Quantidade de fases
#define N_FASES 3
// DEBUG
#define DEBUG 1

//  #############################################################################

volatile int exit_program; // variável de saída
volatile int timer; // variável de tempo

//  ##############  ENUMERADORES   #####################

enum{
TERRA,
CHAO,
PEDRA,
ARVORE_MORTA,
ARVORE_1,
ARVORE_2,
ARVORE_3,
ARVORE_4,
ARVORE_5,
ARVORE_6,
ARVORE_7,
ARVORE_8,
ARVORE_9,
MAX_TERRENOS
};

//  ##############    TYPEDEFS    #########################

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
    char nome[30];
    float x;
    float y;
    float largura;
    float altura;
    int direcao; // direita 1 e esquerda 2
    int direcao_anterior;
    int estado_sprite; // estado atual
    int controle_estado; // verifica certos intervalos de tempo
    int caindo;
    int pulando;
    int permitir_pulo;
    int nivel_plataforma;
    int atacando;
    int tempo_ataque;
    int levando_dano;
    int tempo_dano;
    BITMAP *sprite;
    BITMAP *vetor_sprite[8];
    BITMAP *face;
    Tatributo caracteristicas;
}Tcriatura;

typedef struct goblinsA
{
    Tcriatura goblins[10];
    int n_goblins;
}TgoblinsA;

typedef struct goblinsB
{
    Tcriatura goblins[6];
    int n_goblins;
}TgoblinsB;

typedef struct chefes
{
    Tcriatura chefe[3];
    int chefe_atual;// se 0, então nenhum
}Tchefes;

typedef struct oponentes
{
    TgoblinsA goblins_guerreiros;
    TgoblinsB goblins_arqueiros;
    Tchefes chefes;
}Toponentes;

typedef struct item
{
    float x;
    float y;
    int largura;
    int altura;
    int tipo;
    int ativo;
    BITMAP *imagem;
}Titem;

typedef struct _itens
{
    Titem todosItens[15];
    int n_itens;
}Titens;

typedef struct janela
{
    float x;
    float y;
    int altura;
    int largura;
    int controle;
    int tempo_inicio;
    int tempo_fim;
    char titulo[30];
    char conteudo[256];
}Tjanela;

typedef struct _janelas
{
    Tjanela total[15];
    int n_janelas;
}Tjanelas;

/*
    Cabeçalhos das funções
*/

// funções que controlam as variáveis globais timer e exit_program
void fecha_programa();
void incrementa_timer();

// criação da janela, instalação do teclado, mouse e timer
void init();

// finaliza tudo
void deinit();

// Use para corrigir os links das imagens
char *link_imagem(char caminho[256]);

// Funções gerais que afetam diversos tipos de objetos
int colisao(float ax,float ay, float ah, float al, float bx, float by, float bh, float bl);

// funções de janela ____________________________________________________________________________________________
void desenhar_retangulo(BITMAP *buffer,int pos_x,int pos_y,int largura,int altura,int transparencia);
void janela_texto(BITMAP *buffer,int pos_x,int pos_y,int largura,int altura,
                  char texto_titulo[256],char texto_corpo[256], FONT* titulo,FONT* corpo,int transparencia,
                  int inicio,int fim,int tempo_jogo,int efeito);
void janela_variavel(BITMAP *buffer,int pos_x,int pos_y,int largura,int altura,int variavel, FONT* fonte,int transparencia);
void janela_dialogo(BITMAP *buffer,Tcriatura *personagem,int pos_x,int pos_y,FONT* titulo,FONT* corpo,int inicio,
                    int fim, int tempo_jogo, char texto_titulo[50],char texto_corpo[256],int efeito);
void preencher_janela(Tjanela *janela_atual,float x, float y, int altura, int largura, int controle, int tempo_inicio,
                      int tempo_fim, char titulo[30],char conteudo[256]);
void menu_inicial (BITMAP *buffer, int *selecionar, BITMAP *menu_iniciar, BITMAP *menu_options, BITMAP *menu_exit, int *loading_time,
                    int *tela);
void tela_carregamento (BITMAP *buffer, BITMAP *tela_loading[4], int *loading_time, int *tela);
//_______________________________________________________________________________________________________________

#endif // BASICO_H