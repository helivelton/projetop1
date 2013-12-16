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

void movimento_guerreiro(Tcriatura *guerreiro,int mov_mapa[2])
{
    int i;
    if (segurou(KEY_RIGHT) && guerreiro->x+guerreiro->largura < SCREEN_W)
    {
        for(i=0;i<VELOCIDADE && guerreiro->x+guerreiro->largura < SCREEN_W;i++)
        {
            if(guerreiro->x < SCREEN_W/2 || mov_mapa[0] <= ((-32)*(LARGURA_MAPA/32-20)))
            {
                guerreiro->x+=1;
            }
            else
            {
                mov_mapa[0]-=1;
            }
            if (timer-guerreiro->controle_estado>=ATUALIZAR_ESTADO && (guerreiro->y + guerreiro->altura >= NIVEL_CHAO))
            {
                guerreiro->controle_estado=timer;
                guerreiro->estado_sprite=(guerreiro->estado_sprite+1)%4;
            }
        }
        guerreiro->direcao =1;
    }
    else if (segurou(KEY_LEFT) && guerreiro->x > 0)
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
            if (timer-guerreiro->controle_estado>=ATUALIZAR_ESTADO && (guerreiro->y + guerreiro->altura >= NIVEL_CHAO))
            {
                guerreiro->controle_estado=timer;
                guerreiro->estado_sprite=(guerreiro->estado_sprite+1)%4;
            }
        }
        guerreiro->direcao = 2;
    }

    if(guerreiro->y + guerreiro->altura == NIVEL_CHAO)
    {
        guerreiro->caindo=0;
    }

    if(guerreiro->y <= ALTURA_PULO)
    {
        guerreiro->caindo=1;
        guerreiro->permitir_pulo = 0;
    }


    if(guerreiro->caindo && guerreiro->y + guerreiro->altura < NIVEL_CHAO)
    {
        for(i=0;i<5 && guerreiro->y + guerreiro->altura < NIVEL_CHAO;i++)
        {
            guerreiro->y+=1;
        }

    }

    if(segurou(KEY_UP) && guerreiro->y > ALTURA_PULO && !guerreiro->caindo && guerreiro->permitir_pulo)
    {
        for(i=0;i<VELOCIDADE && guerreiro->y > ALTURA_PULO;i++)
        {
            guerreiro->y = guerreiro->y - 1;
        }

    }
    if(soltou(KEY_UP))
    {
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
