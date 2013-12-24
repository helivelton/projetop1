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
    ser->atacando=0;
    ser->levando_dano=0;
    ser->sprite = create_bitmap(64,64);
}

void imagens_guerreiro(Tcriatura *guerreiro)
{
    int i,j;
    BITMAP *tiles = load_bitmap(link_imagem("imagens_p1/guerreiro_.bmp"),NULL);

    for(i=0;i<2;i++)
    {
        for(j=0;j<4;j++)
        {
            guerreiro->vetor_sprite[j+4*i]=create_bitmap(64,64);
            blit(tiles,guerreiro->vetor_sprite[j+4*i],j*64,i*64,0,0,64,64);
        }

    }

    guerreiro->face = load_bitmap(link_imagem("imagens_p1/hero_face.bmp"),NULL);

    destroy_bitmap(tiles);
}

void movimento_guerreiro(Tcriatura *guerreiro,int mov_mapa[2], int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{
    int i;

    if(guerreiro->estado_sprite > 3 && !guerreiro->atacando)
        guerreiro->estado_sprite = 0;

    if (segurou(KEY_RIGHT) && guerreiro->x+guerreiro->largura < SCREEN_W
        && !colisao_direita(guerreiro->x - mov_mapa[0], guerreiro->y, guerreiro->altura, guerreiro->largura, matriz_tela, bloqueios))
    {
        for(i=0;i<guerreiro->caracteristicas.habilidade && guerreiro->x+guerreiro->largura < SCREEN_W ;i++)
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
    else if (segurou(KEY_LEFT) && guerreiro->x > 0 &&
             !colisao_esquerda(guerreiro->x - mov_mapa[0], guerreiro->y, guerreiro->altura, guerreiro->largura, matriz_tela, bloqueios))
    {
        for(i=0;i<guerreiro->caracteristicas.habilidade && guerreiro->x > 0;i++)
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
        if(!key[KEY_UP])guerreiro->nivel_plataforma = guerreiro->y+guerreiro->altura - 1;
        guerreiro->pulando=0;
        if(!key[KEY_UP])guerreiro->permitir_pulo=1;

    }

    if(guerreiro->y <= guerreiro->nivel_plataforma - ALTURA_PULO ||
       (!colisao_abaixo(guerreiro->x - mov_mapa[0], guerreiro->y, guerreiro->altura, guerreiro->largura, matriz_tela, bloqueios)
        && !guerreiro->pulando)||
       colisao_cima(guerreiro->x - mov_mapa[0],guerreiro->y,guerreiro->altura,guerreiro->largura,matriz_tela,bloqueios))
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

    if(segurou(KEY_UP) && guerreiro->y > guerreiro->nivel_plataforma - ALTURA_PULO && !guerreiro->caindo && guerreiro->permitir_pulo &&
       !colisao_cima(guerreiro->x - mov_mapa[0],guerreiro->y,guerreiro->altura,guerreiro->largura,
                     matriz_tela,bloqueios))
    {
        guerreiro->pulando=1;
        for(i=0;i<VELOCIDADE && guerreiro->y > guerreiro->nivel_plataforma - ALTURA_PULO;i++)
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

void ataque_guerreiro(Tcriatura *guerreiro,int tempo_jogo,Toponentes *inimigos, int mov_mapa[2])
{
    int i;
    if(apertou(KEY_Z) && !guerreiro->atacando)
    {
        guerreiro->atacando = 1;
        guerreiro->tempo_ataque = tempo_jogo;
    }
    if(guerreiro->tempo_ataque + 19 <= tempo_jogo)
    {
        guerreiro->atacando = 0;
    }
    if(guerreiro->atacando)
    {
        guerreiro->estado_sprite = ((tempo_jogo-guerreiro->tempo_ataque)/5)%4;
        guerreiro->estado_sprite = guerreiro->estado_sprite + 4;
    }
    for(i=0;i<inimigos->goblins_guerreiros.n_goblins && guerreiro->atacando && !inimigos->goblins_guerreiros.goblins[i].levando_dano;i++)
    {
        if(guerreiro->direcao==2)//esquerda
        {
            if(colisao(guerreiro->x - 16,guerreiro->y-4,25,20,
                       inimigos->goblins_guerreiros.goblins[i].x,inimigos->goblins_guerreiros.goblins[i].y,
                       inimigos->goblins_guerreiros.goblins[i].altura,
                       inimigos->goblins_guerreiros.goblins[i].largura ))
               {
                   inimigos->goblins_guerreiros.goblins[i].levando_dano=1;
                   inimigos->goblins_guerreiros.goblins[i].tempo_dano=tempo_jogo;
                   calcular_dano(guerreiro,&inimigos->goblins_guerreiros.goblins[i],0);
               }
        }
        if(guerreiro->direcao==1)//direita
        {
            if(colisao(guerreiro->x + guerreiro->largura - 4,guerreiro->y-4,25,20,
                       inimigos->goblins_guerreiros.goblins[i].x,inimigos->goblins_guerreiros.goblins[i].y,
                       inimigos->goblins_guerreiros.goblins[i].altura,
                       inimigos->goblins_guerreiros.goblins[i].largura ))
               {
                   inimigos->goblins_guerreiros.goblins[i].levando_dano=1;
                   inimigos->goblins_guerreiros.goblins[i].tempo_dano=tempo_jogo;
                   calcular_dano(guerreiro,&inimigos->goblins_guerreiros.goblins[i],0);
               }
        }
    }
}

void desenhar_guerreiro(BITMAP *buffer,Tcriatura *guerreiro)
{
    rectfill(guerreiro->sprite,0,0,64,64,makecol(255,0,255));
    if(guerreiro->direcao==1)
    {
        draw_sprite_ex(guerreiro->sprite,guerreiro->vetor_sprite[guerreiro->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
    }
    else
    {
        draw_sprite_ex(guerreiro->sprite,guerreiro->vetor_sprite[guerreiro->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
    }
    draw_sprite(buffer, guerreiro->sprite, guerreiro->x-(64 - guerreiro->largura)/2,
                guerreiro->y - (64 - guerreiro->altura)/2); // manda guerreiro para buffer
}

void imagens_goblin1(Tcriatura *goblin)
{
    int i;
    BITMAP *tiles = load_bitmap(link_imagem("imagens_p1/goblinG.bmp"),NULL);

    for(i=0;i<8;i++)
    {
        goblin->vetor_sprite[i]=create_bitmap(64,64);
        blit(tiles,goblin->vetor_sprite[i],i*64,0,0,0,64,64);
    }

    destroy_bitmap(tiles);
}

void movimento_goblin1(Tcriatura *goblin1,int x_guerreiro, int tempo_jogo)
{


    if(!goblin1->levando_dano)
    {
        if(goblin1->estado_sprite < 5 && !goblin1->atacando)
            goblin1->estado_sprite = 5;

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
            goblin1->x=goblin1->x+goblin1->caracteristicas.habilidade;
            if(timer-goblin1->controle_estado >= ATUALIZAR_ESTADO)
            {
                goblin1->controle_estado = timer;
                if(goblin1->estado_sprite > 4)
                {
                    goblin1->estado_sprite=goblin1->estado_sprite-5;
                    goblin1->estado_sprite = (goblin1->estado_sprite + 1)%3;
                    goblin1->estado_sprite = goblin1->estado_sprite + 5;
                }

            }
        }
        else if(goblin1->direcao==2)
        {
            goblin1->x=goblin1->x-goblin1->caracteristicas.habilidade;
            if(timer-goblin1->controle_estado >= ATUALIZAR_ESTADO)
            {
                goblin1->controle_estado = timer;
                if(goblin1->estado_sprite > 4)
                {
                    goblin1->estado_sprite=goblin1->estado_sprite-5;
                    goblin1->estado_sprite = (goblin1->estado_sprite + 1)%3;
                    goblin1->estado_sprite = goblin1->estado_sprite + 5;
                }
            }
        }
    }
    else
    {
        goblin1->estado_sprite = 1;
        if(goblin1->tempo_dano+10>=tempo_jogo)
        {
            if(goblin1->direcao==1)//direita
            {
                goblin1->x = goblin1->x - 6;
            }
            else
            {
                goblin1->x = goblin1->x + 6;
            }
        }
        else
        {
            goblin1->levando_dano=0;
        }
    }

}

void desenhar_goblin1(BITMAP *buffer,Tcriatura *goblin1)
{
    rectfill(goblin1->sprite,0,0,64,64,makecol(255,0,255));
    if(goblin1->direcao==1)
    {
        draw_sprite_ex(goblin1->sprite,goblin1->vetor_sprite[goblin1->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
        goblin1->direcao_anterior=1;
    }
    else if(goblin1->direcao==2)
    {
        draw_sprite_ex(goblin1->sprite,goblin1->vetor_sprite[goblin1->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        goblin1->direcao_anterior=2;

    }
    else if(goblin1->direcao==0)
    {
        if(goblin1->direcao_anterior==1)
        {
            draw_sprite_ex(goblin1->sprite,goblin1->vetor_sprite[goblin1->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
        }
        else
        {
            draw_sprite_ex(goblin1->sprite,goblin1->vetor_sprite[goblin1->estado_sprite],0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
    }
    draw_sprite(buffer, goblin1->sprite, goblin1->x-(64-goblin1->largura)/2,
                goblin1->y-(64-goblin1->altura)/2);
}

int colisao_direita(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{

    y=y+2;
    altura=altura-4;
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

    y=y+2;
    altura=altura-4;
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

    x+=2;
    largura=largura-4;
    y=y+1;

    int xMatrix = x/32;
    int yMatrix = (y + altura)/32;

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
        xMatrix = (x+largura)/32;
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

int colisao_cima(float x,float y, int altura, int largura, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{
    x+=2;
    largura=largura-4;
    y = y -1;

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
        xMatrix = (x+largura)/32;
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

int dano_ataque(Tcriatura* atacante, int tipo_ataque)
{
    int ataque;
    if(tipo_ataque==0)
    {
        ataque=atacante->caracteristicas.forca;
    }
    else
    {
        ataque=atacante->caracteristicas.poder_de_fogo;
    }
    ataque+=atacante->caracteristicas.habilidade;
    float a = (rand()%100)/100.0;
    ataque= ataque*(0.8 + a*0.4);
    return ataque;
}


void calcular_dano(Tcriatura* atacante, Tcriatura* alvo,int tipo_ataque)
{
    int ataque = dano_ataque(atacante,tipo_ataque);
    //int forca=atacante->caracteristicas.forca;
    int defesa= alvo->caracteristicas.resistencia + alvo->caracteristicas.armadura;
    //int hp= alvo->caracteristicas.hp;
    float chance_critico=0.1;
    float a = (rand()%100)/100.0;
    int critico = chance_critico > a? 2 : 1;
    int dano;

    dano= (ataque-defesa)*critico;
    dano= dano > 0? dano : 1;

    alvo->caracteristicas.hp-=dano;
}
