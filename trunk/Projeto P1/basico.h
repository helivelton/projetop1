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
#define ATUALIZAR_ESTADO 6
// Altura e largura da tela da screen
#define ALTURA_SCREEN 480
#define LARGURA_SCREEN 640
// Altura e largura das fases
#define ALTURA_TELA 480
#define LARGURA_TELA 640*5
//  #############################################################################

/*
    Cabeçalhos das funções
*/

void init(); // criação da janela, instalação do teclado, mouse e timer

void deinit();// finaliza tudo

/*
######################### Processo para usar imagens no projeto em desenvolvimento ########################

Questão: O repositório não pode conter os arquivos de imagens (que serão muitas, e o repositório
tem espaço limitado), e essas imagens deverão estar compartilhadas entre os membros do grupo.

Resolução: Usar o Dropbox para os arquivos de imagens, e se referir a elas através de um caminho relativo.

Nova questão: após o projeto terminar, a pasta com todas as imagens deverão estar na pasta do projeto. Assim,
todos os links irão mudar, e deverão ser alterados manualmente.

Resolução: Ao invés disso, podemos contornar esse problema usando uma constante que adiciona uma string em
cada link. Siga esses procedimentos:

1. Em cada arquivo que for trabalhar, se for referenciar uma imagem, use o arquivo header "basico.h".

2. Ao definir um link, use a função link_imagem(link), e no parênteses defina o link como se a pasta de
imagens estivesse na pasta do projeto. A função retornará o link corrigido.

Após a conclusão do projeto, pegue a pasta com as imagens (neste caso, imagens_p1), e coloque na pasta do
projeto. E simplesmente mude a constante LINKRELAT do arquivo basico.c para "" (string vazia).
Não serão necessárias alterações adicionais.
*/

char *link_imagem(char caminho[256]);

#endif // BASICO_H
