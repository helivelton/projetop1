#ifndef CRIATURAS_H
#define CRIATURAS_H

#include "basico.h"
#include "controle.h"

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
    int estado_sprite;
    int controle_estado;
    int caindo;
    int pulando;
    BITMAP *sprite;
    BITMAP *vetor_sprite[4];
    Tatributo caracteristicas;
}Tcriatura;

// Funções para todas as criaturas
void preenche_criatura(Tcriatura *ser,float x,float y,int direcao,int estado_sprite,int f,int h,int r,int a,int pdf);

// Funções do guerreiro
void imagens_guerreiro(BITMAP *im_guerreiro[4]);
void movimento_guerreiro(Tcriatura *guerreiro,int mov_mapa[2]);
void desenhar_guerreiro(BITMAP *buffer,Tcriatura *guerreiro);

// Funções do goblin tipo 1
void imagens_goblin1(BITMAP *im_goblin1[4]);
void movimento_goblin1(Tcriatura *goblin1,int x_guerreiro);
void desenhar_goblin1(BITMAP *buffer,Tcriatura *goblin1);

#endif // CRIATURAS_H
