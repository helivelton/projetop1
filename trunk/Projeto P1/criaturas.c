#include "criaturas.h"

void preenche_criatura(Tcriatura *ser,float x,float y,int direcao,int estado_sprite,int f,int h,int r,int a,int pdf)
{
    ser->x=x;
    ser->ajuste_x = 0;
    ser->y=y;
    ser->direcao=direcao;
    ser->direcao_anterior=1;
    ser->estado_sprite=estado_sprite;
    ser->caracteristicas.forca=f;
    ser->caracteristicas.habilidade=h;
    ser->caracteristicas.resistencia=r;
    ser->caracteristicas.armadura=a;
    ser->caracteristicas.poder_de_fogo=pdf;
    ser->caracteristicas.hp=ser->caracteristicas.resistencia*5;
    ser->caracteristicas.mp=ser->caracteristicas.resistencia*5;
    ser->caindo=0;
    ser->pulando=0;
}

void imagens_guerreiro(BITMAP *im_guerreiro[4])
{
    int i;
    for(i=0;i<4;i++)
    {
        im_guerreiro[i]=create_bitmap(32,48);
    }
    BITMAP *tiles = load_bitmap(link_imagem("imagens_p1/hero.bmp"),NULL);
    blit(tiles,im_guerreiro[0],0,0,0,0,32,48);
    blit(tiles,im_guerreiro[1],32,0,0,0,32,48);
    blit(tiles,im_guerreiro[2],2*32,0,0,0,32,48);
    blit(tiles,im_guerreiro[3],3*32,0,0,0,32,48);

    destroy_bitmap(tiles);
}

void movimento_guerreiro(Tcriatura *guerreiro_status,int timer,int *mov_mapa)
{
    if (segurou(KEY_RIGHT) && guerreiro_status->x < SCREEN_W-32)
    {
        if(guerreiro_status->x <= SCREEN_W/2 || *mov_mapa <= ((-32)*((LARGURA_TELA/32-20)-1)))
        {
            guerreiro_status->x+=VELOCIDADE;
        }
        else
        {
            *mov_mapa-=VELOCIDADE;
        }
        if (timer-guerreiro_status->controle_estado>=ATUALIZAR_ESTADO && (guerreiro_status->y>=12*32-(48-ALTURA_SPRITE)/2))
        {
            guerreiro_status->controle_estado=timer;
            guerreiro_status->estado_sprite=(guerreiro_status->estado_sprite+1)%4;
        }
        guerreiro_status->direcao =1;
    }
    else if (segurou(KEY_LEFT) && guerreiro_status->x > 0)
    {
        if(guerreiro_status->x >= SCREEN_W/2 || *mov_mapa >= 0)
        {
            guerreiro_status->x-=VELOCIDADE;
        }
        else
        {
            *mov_mapa+=VELOCIDADE;
        }
        if (timer-guerreiro_status->controle_estado>=ATUALIZAR_ESTADO && (guerreiro_status->y>=12*32-(48-ALTURA_SPRITE)/2))
        {
            guerreiro_status->controle_estado=timer;
            guerreiro_status->estado_sprite=(guerreiro_status->estado_sprite+1)%4;
        }
        guerreiro_status->direcao = 2;
    }

    if(guerreiro_status->y>=12*32-(48-ALTURA_SPRITE)/2)
    {
        guerreiro_status->caindo=0;
    }

    if(guerreiro_status->y<=300)
    {
        guerreiro_status->caindo=1;
    }


    if(guerreiro_status->caindo && guerreiro_status->y<12*32-(48-ALTURA_SPRITE)/2)
    {
        guerreiro_status->y+=5;
    }


    if  (segurou(KEY_UP) && guerreiro_status->y >300 && !guerreiro_status->caindo)
    {

            guerreiro_status->y=guerreiro_status->y-VELOCIDADE;

    }

    if(soltou(KEY_UP)) guerreiro_status->caindo=1;
}

void desenhar_guerreiro(BITMAP *buffer,BITMAP *guerreiro,Tcriatura *guerreiro_status,BITMAP *im_guerreiro[4])
{
    rectfill(guerreiro,0,0,32,48,makecol(255,0,255));
    if(guerreiro_status->direcao==1)
    {
        draw_sprite_ex(guerreiro,im_guerreiro[guerreiro_status->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
    }
    else
    {
        draw_sprite_ex(guerreiro,im_guerreiro[guerreiro_status->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
    }
    draw_sprite(buffer, guerreiro, guerreiro_status->x, guerreiro_status->y); // manda guerreiro para buffer
}

void imagens_goblin1(BITMAP *im_goblin1[3])
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

void movimento_goblin1(Tcriatura *goblin1_status,int x_guerreiro,int timer)
{
    if (goblin1_status->x > x_guerreiro)
    {
        goblin1_status->direcao=2;
    }
    else if (goblin1_status->x < x_guerreiro)
    {
        goblin1_status->direcao=1;
    }
    else
    {
        goblin1_status->direcao=0;
    }

    if(goblin1_status->direcao==1)
    {
        goblin1_status->x=goblin1_status->x+VELOCIDADE/2;
        if(timer-goblin1_status->controle_estado >= ATUALIZAR_ESTADO)
        {
            goblin1_status->controle_estado = timer;
            goblin1_status->estado_sprite = (goblin1_status->estado_sprite + 1)%3;
        }
    }
    else if(goblin1_status->direcao==2)
    {
        goblin1_status->x=goblin1_status->x-VELOCIDADE/2;
        if(timer-goblin1_status->controle_estado >= ATUALIZAR_ESTADO)
        {
            goblin1_status->controle_estado = timer;
            goblin1_status->estado_sprite = (goblin1_status->estado_sprite + 1)%3;
        }
    }
}

void desenhar_goblin1(BITMAP *buffer,BITMAP *goblin1,Tcriatura *goblin1_status,BITMAP *im_goblin1[3])
{
    rectfill(goblin1,0,0,32,48,makecol(255,0,255));
    if(goblin1_status->direcao==1)
    {
        draw_sprite_ex(goblin1,im_goblin1[goblin1_status->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
        goblin1_status->direcao_anterior=1;
    }
    else if(goblin1_status->direcao==2)
    {
        draw_sprite_ex(goblin1,im_goblin1[goblin1_status->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        goblin1_status->direcao_anterior=2;

    }
    else if(goblin1_status->direcao==0)
    {
        if(goblin1_status->direcao_anterior==1)
        {
            draw_sprite_ex(goblin1,im_goblin1[goblin1_status->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
        }
        else
        {
            draw_sprite_ex(goblin1,im_goblin1[goblin1_status->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
    }
    draw_sprite(buffer, goblin1, goblin1_status->x, goblin1_status->y);
}
