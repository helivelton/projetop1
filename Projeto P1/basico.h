#ifndef BASICO_H
#define BASICO_H

/*  #############################################################################
    Todas as bibliotecas b�sicas usadas no projeto

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
// controla velocidade padr�o dos sprites
#define VELOCIDADE 3
// controla velocidade padr�o de mudan�a dos estados dos sprites
#define ATUALIZAR_ESTADO 6
// Altura e largura da tela da screen
#define ALTURA_SCREEN 480
#define LARGURA_SCREEN 640
// Altura e largura das fases
#define ALTURA_TELA 480
#define LARGURA_TELA 640*5
//  #############################################################################

/*
    Cabe�alhos das fun��es
*/

void init(); // cria��o da janela, instala��o do teclado, mouse e timer

void deinit();// finaliza tudo

/*
######################### Processo para usar imagens no projeto em desenvolvimento ########################

Quest�o: O reposit�rio n�o pode conter os arquivos de imagens (que ser�o muitas, e o reposit�rio
tem espa�o limitado), e essas imagens dever�o estar compartilhadas entre os membros do grupo.

Resolu��o: Usar o Dropbox para os arquivos de imagens, e se referir a elas atrav�s de um caminho relativo.

Nova quest�o: ap�s o projeto terminar, a pasta com todas as imagens dever�o estar na pasta do projeto. Assim,
todos os links ir�o mudar, e dever�o ser alterados manualmente.

Resolu��o: Ao inv�s disso, podemos contornar esse problema usando uma constante que adiciona uma string em
cada link. Siga esses procedimentos:

1. Em cada arquivo que for trabalhar, se for referenciar uma imagem, use o arquivo header "basico.h".

2. Ao definir um link, use a fun��o link_imagem(link), e no par�nteses defina o link como se a pasta de
imagens estivesse na pasta do projeto. A fun��o retornar� o link corrigido.

Ap�s a conclus�o do projeto, pegue a pasta com as imagens (neste caso, imagens_p1), e coloque na pasta do
projeto. E simplesmente mude a constante LINKRELAT do arquivo basico.c para "" (string vazia).
N�o ser�o necess�rias altera��es adicionais.
*/

char *link_imagem(char caminho[256]);

#endif // BASICO_H
