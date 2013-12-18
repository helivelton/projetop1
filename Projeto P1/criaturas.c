#include "criaturas.h"

void preenche_criatura(Tcriatura *ser,float x,float y,float largura, float altura,int direcao,int f,int h,int r,int a,int pdf)
{
    ser->x=x;
    ser->y=y;
    ser->altura = altura;
    ser->largura = largura;
    ser->direcao=direcao;
    ser->direcao_anterior=1;
    ser->estado_sprite=0;
    ser->caracteristicas.forca=f;
    ser->caracteristicas.habilidade=h;
    ser->caracteristicas.resistencia=r;
    ser->caracteristicas.armadura=a;
    ser->caracteristicas.poder_de_fogo=pdf;
    ser->caracteristicas.hp=ser->caracteristicas.resistencia*5;
    ser->caracteristicas.mp=ser->caracteristicas.resistencia*5;
    ser->caindo=0;
    ser->pulando=0;
    ser->permitir_pulo = 1;
    ser->sprite = create_bitmap(64,64);
}

void imagens_guerreiro(Tcriatura *guerreiro)
{
    int i;
    for(i=0;i<4;i++)
    {
        guerreiro->vetor_sprite[i]=create_bitmap(32,48);
    }
    BITMAP *tiles = load_bitmap(link_imagem("imagens_p1/hero.bmp"),NULL);
    blit(tiles,guerreiro->vetor_sprite[0],0,0,0,0,32,48);
    blit(tiles,guerreiro->vetor_sprite[1],32,0,0,0,32,48);
    blit(tiles,guerreiro->vetor_sprite[2],2*32,0,0,0,32,48);
    blit(tiles,guerreiro->vetor_sprite[3],3*32,0,0,0,32,48);

    guerreiro->face = load_bitmap(link_imagem("imagens_p1/hero_face.bmp"),NULL);

    destroy_bitmap(tiles);
}

void movimento_guerreiro(Tcriatura *guerreiro,int mov_mapa[2], int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{
    int i;
    if (segurou(KEY_RIGHT) && guerreiro->x+guerreiro->largura < SCREEN_W  && !colisao_direita(guerreiro->x - mov_mapa[0], guerreiro->y, guerreiro->altura, guerreiro->largura, matriz_tela, bloqueios))
    {
        for(i=0;i<VELOCIDADE && guerreiro->x+guerreiro->largura < SCREEN_W ;i++)
        {
            if(guerreiro->x < SCREEN_W/2 || mov_mapa[0] <= ((-32)*(LARGURA_MAPA/32-20)))
            {
                guerreiro->x+=1;
            }
            else
            {
                mov_mapa[0]-=1;
            }
            if (timer-guerreiro->controle_estado>=ATUALIZAR_ESTADO && !guerreiro->pulando)
            {
                guerreiro->controle_estado=timer;
                guerreiro->estado_sprite=(guerreiro->estado_sprite+1)%4;
            }
        }
        guerreiro->direcao =1;
    }
    else if (segurou(KEY_LEFT) && guerreiro->x > 0 && !colisao_esquerda(guerreiro->x - mov_mapa[0], guerreiro->y, guerreiro->altura, guerreiro->largura, matriz_tela, bloqueios))
    {
        for(i=0;i<VELOCIDADE && guerreiro->x > 0;i++)
        {
            if(guerreiro->x > SCREEN_W/2 || mov_mapa[0] >= 0)
            {
                guerreiro->x-=1;
            }
            else
            {
                mov_mapa[0]+=1;
            }
            if (timer-guerreiro->controle_estado>=ATUALIZAR_ESTADO && !guerreiro->pulando)
            {
                guerreiro->controle_estado=timer;
                guerreiro->estado_sprite=(guerreiro->estado_sprite+1)%4;
            }
        }
        guerreiro->direcao = 2;
    }

    if(colisao_abaixo(guerreiro->x - mov_mapa[0], guerreiro->y, guerreiro->altura, guerreiro->largura, matriz_tela, bloqueios))
    {
        guerreiro->caindo=0;
        guerreiro->permitir_pulo=1;

    }

    if(guerreiro->y <= ALTURA_PULO || (!colisao_abaixo(guerreiro->x - mov_mapa[0], guerreiro->y, guerreiro->altura, guerreiro->largura, matriz_tela, bloqueios) && !guerreiro->pulando))
    {

        guerreiro->caindo=1;
        guerreiro->permitir_pulo = 0;
    }


    if(guerreiro->caindo && !colisao_abaixo(guerreiro->x - mov_mapa[0], guerreiro->y, guerreiro->altura, guerreiro->largura, matriz_tela, bloqueios))
    {
        for(i=0;i<5 && !colisao_abaixo(guerreiro->x - mov_mapa[0], guerreiro->y, guerreiro->altura, guerreiro->largura, matriz_tela, bloqueios);i++)
        {
            guerreiro->y+=1;
        }

    }

    if(segurou(KEY_UP) && guerreiro->y > ALTURA_PULO && !guerreiro->caindo && guerreiro->permitir_pulo)
    {
        guerreiro->pulando=1;
        for(i=0;i<VELOCIDADE && guerreiro->y > ALTURA_PULO;i++)
        {
            guerreiro->y = guerreiro->y - 1;
        }

    }
    if(soltou(KEY_UP))
    {
        guerreiro->pulando=0;
        guerreiro->caindo=1;
        guerreiro->permitir_pulo=1;
    }
}

void desenhar_guerreiro(BITMAP *buffer,Tcriatura *guerreiro)
{
    rectfill(guerreiro->sprite,0,0,64,64,makecol(255,0,255));
    if(guerreiro->direcao==1)
    {
        draw_sprite_ex(guerreiro->sprite,guerreiro->vetor_sprite[guerreiro->estado_sprite],16,8,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
    }
    else
    {
        draw_sprite_ex(guerreiro->sprite,guerreiro->vetor_sprite[guerreiro->estado_sprite],16,8,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
    }
    draw_sprite(buffer, guerreiro->sprite, guerreiro->x-(64 - guerreiro->largura)/2,
                guerreiro->y - (64 - guerreiro->altura)/2); // manda guerreiro para buffer
}

void imagens_goblin1(BITMAP *im_goblin1[4])
{
    int i;
    for(i=0;i<3;i++)
    {
        im_goblin1[i]=create_bitmap(32,48);
    }
    BITMAP *tiles = load_bitmap(link_imagem("imagens_p1/skel.bmp"),NULL);
    blit(tiles,im_goblin1[0],0*0,0,0,0,32,48);
    blit(tiles,im_goblin1[1],1*32,0,0,0,32,48);
    blit(tiles,im_goblin1[2],2*32,0,0,0,32,48);

    destroy_bitmap(tiles);
}

void movimento_goblin1(Tcriatura *goblin1,int x_guerreiro)
{
    if (goblin1->x > x_guerreiro)
    {
        goblin1->direcao=2;
    }
    else if (goblin1->x < x_guerreiro)
    {
        goblin1->direcao=1;
    }
    else
    {
        goblin1->direcao=0;
    }

    if(goblin1->direcao==1)
    {
        goblin1->x=goblin1->x+VELOCIDADE/2;
        if(timer-goblin1->controle_estado >= ATUALIZAR_ESTADO)
        {
            goblin1->controle_estado = timer;
            goblin1->estado_sprite = (goblin1->estado_sprite + 1)%3;
        }
    }
    else if(goblin1->direcao==2)
    {
        goblin1->x=goblin1->x-VELOCIDADE/2;
        if(timer-goblin1->controle_estado >= ATUALIZAR_ESTADO)
        {
            goblin1->controle_estado = timer;
            goblin1->estado_sprite = (goblin1->estado_sprite + 1)%3;
        }
    }
}

void desenhar_goblin1(BITMAP *buffer,Tcriatura *goblin1)
{
    rectfill(goblin1->sprite,0,0,64,64,makecol(255,0,255));
    if(goblin1->direcao==1)
    {
        draw_sprite_ex(goblin1->sprite,goblin1->vetor_sprite[goblin1->estado_sprite],16,8,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
        goblin1->direcao_anterior=1;
    }
    else if(goblin1->direcao==2)
    {
        draw_sprite_ex(goblin1->sprite,goblin1->vetor_sprite[goblin1->estado_sprite],16,8,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        goblin1->direcao_anterior=2;

    }
    else if(goblin1->direcao==0)
    {
        if(goblin1->direcao_anterior==1)
        {
            draw_sprite_ex(goblin1->sprite,goblin1->vetor_sprite[goblin1->estado_sprite],16,8,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
        }
        else
        {
            draw_sprite_ex(goblin1->sprite,goblin1->vetor_sprite[goblin1->estado_sprite],16,8,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
    }
    draw_sprite(buffer, goblin1->sprite, goblin1->x-(64-goblin1->largura)/2,
                goblin1->y-(64-goblin1->altura)/2);
}

int colisao_direita(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{

    y=y+1;
    altura=altura-2;
    x= x + largura + 1;
    int xMatrix = x/32;
    int yMatrix = y/32;

    int i, ehBloqueio=0;
    //int j;
    //int intervalo;

    for(i=0;i<3;i++)
    {
        if(matriz_tela[yMatrix][xMatrix]==bloqueios[i])
        {
            ehBloqueio=1;
        }
    }

    if(!ehBloqueio)
    {
        yMatrix = (y+altura)/32;
        for(i=0;i<3;i++)
        {
            if(matriz_tela[yMatrix][xMatrix]==bloqueios[i])
            {
                ehBloqueio=1;
            }
        }
    }
/*
    if(!ehBloqueio)
    {

        i=(altura*1.0)/6;

        if(i<1)i=1;
        intervalo=i;
        for(i=i;i<(y+altura);i+=intervalo)
        {
            yMatrix= (y + i)/32;

            for(j=0;j<3;j++)
            {
                if(matriz_tela[yMatrix][xMatrix]==bloqueios[j])
                {
                    ehBloqueio=1;
                }
            }
        }
    }
*/
    if(!ehBloqueio)
    {
        int intermediario = altura/2;
        yMatrix = (y+intermediario)/32;
        for(i=0;i<3;i++)
        {
            if(matriz_tela[yMatrix][xMatrix]==bloqueios[i])
            {
                ehBloqueio=1;
            }
        }
    }


    return ehBloqueio;
}

int colisao_esquerda(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{

    y=y+1;
    altura=altura-2;
    x = x - 1;
    int xMatrix = x/32;
    int yMatrix = y/32;

    int i, ehBloqueio=0;
    //int j;
    //int intervalo;

    for(i=0;i<3;i++)
    {
        if(matriz_tela[yMatrix][xMatrix]==bloqueios[i])
        {
            ehBloqueio=1;
        }
    }

    if(!ehBloqueio)
    {
        yMatrix = (y+altura)/32;
        for(i=0;i<3;i++)
        {
            if(matriz_tela[yMatrix][xMatrix]==bloqueios[i])
            {
                ehBloqueio=1;
            }
        }
    }
/*
    if(!ehBloqueio)
    {

        i=(altura*1.0)/6;

        if(i<1)i=1;
        intervalo=i;
        for(i=i;i<(y+altura);i+=intervalo)
        {
            yMatrix= (y + i)/32;

            for(j=0;j<3;j++)
            {
                if(matriz_tela[yMatrix][xMatrix]==bloqueios[j])
                {
                    ehBloqueio=1;
                }
            }
        }
    }
*/
    if(!ehBloqueio)
    {
        int intermediario = altura/2;
        yMatrix = (y+intermediario)/32;
        for(i=0;i<3;i++)
        {
            if(matriz_tela[yMatrix][xMatrix]==bloqueios[i])
            {
                ehBloqueio=1;
            }
        }
    }


    return ehBloqueio;
}

int colisao_abaixo(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{

    y+=1;


    int xMatrix = (x+2)/32;
    int yMatrix = (y + altura + 1)/32;

    int i, ehBloqueio=0;
    //int j;
    //int intervalo;

    for(i=0;i<3;i++)
    {
        if(matriz_tela[yMatrix][xMatrix]==bloqueios[i])
        {
            ehBloqueio=1;
        }
    }

    if(!ehBloqueio)
    {
        xMatrix = (x+largura-2)/32;
        for(i=0;i<3;i++)
        {
            if(matriz_tela[yMatrix][xMatrix]==bloqueios[i])
            {
                ehBloqueio=1;
            }
        }
    }
/*
    if(!ehBloqueio)
    {

        i=(altura*1.0)/6;

        if(i<1)i=1;
        intervalo=i;
        for(i=i;i<(y+altura);i+=intervalo)
        {
            yMatrix= (y + i)/32;

            for(j=0;j<3;j++)
            {
                if(matriz_tela[yMatrix][xMatrix]==bloqueios[j])
                {
                    ehBloqueio=1;
                }
            }
        }
    }
*/
    if(!ehBloqueio)
    {
        int intermediario = largura/2;
        xMatrix = (x+intermediario)/32;
        for(i=0;i<3;i++)
        {
            if(matriz_tela[yMatrix][xMatrix]==bloqueios[i])
            {
                ehBloqueio=1;
            }
        }
    }


    return ehBloqueio;
}
