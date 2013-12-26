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

void movimento_guerreiro(Tcriatura *guerreiro, int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{
    if(!guerreiro->levando_dano) // se n�o esta levando dano
    {
        // para movimento s�o os estados 0 a 3 do sprite
        if(guerreiro->estado_sprite > 3 && !guerreiro->atacando)
            guerreiro->estado_sprite = 0;

        // apertou direita
        if(segurou(KEY_RIGHT))
            movimento_direita(guerreiro,guerreiro->caracteristicas.habilidade,matriz_tela,bloqueios,1,1);

        // apertou esquerda
        if(segurou(KEY_LEFT))
            movimento_esquerda(guerreiro,guerreiro->caracteristicas.habilidade,matriz_tela,bloqueios,1,1);

        // apertou para cima
        if(segurou(KEY_UP))
            pulo(guerreiro,guerreiro->caracteristicas.habilidade,0,matriz_tela,bloqueios);

        // apertou para baixo
        if(apertou(KEY_DOWN))
            guerreiro->tempo_recuo=timer; // limita tempo de recuo
        if(segurou(KEY_DOWN))
            recuo(guerreiro,guerreiro->caracteristicas.habilidade,matriz_tela,bloqueios);

        // se soltar o bot�o de pulo
        if(soltou(KEY_UP))
        {
            guerreiro->pulando=0;
            guerreiro->caindo=1;
            guerreiro->permitir_pulo=1;
        }
    }
    else // se sofre dano
        recuo_por_dano(guerreiro,matriz_tela,bloqueios);

    // verifica��es b�sicas
    colide_chao(guerreiro,matriz_tela,bloqueios,1); // colidiu com o ch�o? primeira verifica��o obrigat�ria
    verificar_queda(guerreiro,matriz_tela,bloqueios); // atingiu o limite de pulo? est� em queda?
}

void ataque_guerreiro(Tcriatura *guerreiro,int tempo_jogo,Toponentes *inimigos)
{
    int i;
    int confirmacao=0;

    if(apertou(KEY_Z))
        confirmacao=1;

    ataque_ajustes(guerreiro,tempo_jogo,confirmacao,4,7);

    for(i=0;i<inimigos->goblins_guerreiros.n_goblins && guerreiro->atacando
            && !inimigos->goblins_guerreiros.goblins[i].levando_dano;i++)
    {
        ataque(guerreiro,&inimigos->goblins_guerreiros.goblins[i],tempo_jogo,0,-16,-4,20,25);
    }
}

void desenhar_guerreiro(BITMAP *buffer,Tcriatura *guerreiro,int ajuste_x)
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
    draw_sprite(buffer, guerreiro->sprite, ajuste_x + guerreiro->x - (64 - guerreiro->largura)/2,
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

void desenhar_goblin1(BITMAP *buffer,Tcriatura *goblin1,int ajuste_x)
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
    draw_sprite(buffer, goblin1->sprite, ajuste_x + goblin1->x-(64-goblin1->largura)/2,
                goblin1->y-(64-goblin1->altura)/2);
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

void movimento_direita(Tcriatura *ser,int deslocamento,int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3],
                       int mudar_direcao,int mudar_sprite)
{
    int i;
    for(i=0; i < deslocamento && (ser->x + ser->largura) < LARGURA_MAPA &&
        !colisao_direita_mapa(ser->x, ser->y, ser->altura, ser->largura, matriz_tela, bloqueios);i++)
    {
        ser->x+=1;
    }
    if(mudar_direcao)
        ser->direcao=1;
    if(mudar_sprite)
    {
        if (!ser->pulando)
            mudanca_sprite(0,3,&ser->estado_sprite,12,0,0);
    }
}

void movimento_esquerda(Tcriatura *ser,int deslocamento,int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3],
                       int mudar_direcao,int mudar_sprite)
{
    int i;
    for(i=0; i < deslocamento && ser->x > 0 &&
        !colisao_esquerda_mapa(ser->x, ser->y, ser->altura, ser->largura, matriz_tela, bloqueios);i++)
    {
        ser->x-=1;
    }
    if(mudar_direcao)
        ser->direcao=2;
    if(mudar_sprite)
    {
        if (!ser->pulando)
            mudanca_sprite(0,3,&ser->estado_sprite,12,0,0);
    }
}

void pulo(Tcriatura *ser,int deslocamentoy,int deslocamentox,int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{
    int i;
    for(i=0; i < deslocamentoy && ser->y > ser->nivel_plataforma - ALTURA_PULO && !ser->caindo && ser->permitir_pulo &&
        !colisao_cima_mapa(ser->x, ser->y, ser->altura, ser->largura, matriz_tela, bloqueios);i++)
    {
        ser->pulando=1;
        ser->y-=1;
        if(deslocamentox!=0)
        {
            if(deslocamentox<0)
                movimento_esquerda(ser,(-1)*deslocamentox,matriz_tela,bloqueios,0,0);
            if(deslocamentox>0)
                movimento_direita(ser,deslocamentox,matriz_tela,bloqueios,0,0);
        }
    }
}

void recuo(Tcriatura *ser,int deslocamento,int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{
    if(ser->tempo_recuo + 20 >= timer && !ser->pulando && !ser->caindo)
    {
        if(ser->direcao==2)
            movimento_direita(ser,deslocamento*3,matriz_tela,bloqueios,0,0);
        else
            movimento_esquerda(ser,deslocamento*3,matriz_tela,bloqueios,0,0);
    }
}

void recuo_por_dano(Tcriatura *ser,int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{
    ser->estado_sprite=0;
    ser->caindo=1;
    ser->pulando=0;

    // ele recua dependendo da dire��o que estiver
    if (ser->direcao==2)
        movimento_direita(ser,6,matriz_tela,bloqueios,0,0);
    else
        movimento_esquerda(ser,6,matriz_tela,bloqueios,0,0);
}

void mudanca_sprite(int limite_inferior,int limite_superior,int *estado_sprite,int intervalo,int tempo_inicio,int tempo_jogo)
{
    if(*estado_sprite < limite_inferior || *estado_sprite > limite_superior)
        *estado_sprite = limite_inferior;
    if (timer%intervalo==0 && tempo_inicio<=0)
    {
        *estado_sprite = *estado_sprite - limite_inferior;
        *estado_sprite = (*estado_sprite + 1) % (limite_superior-limite_inferior+1);
        *estado_sprite = *estado_sprite + limite_inferior;
    }
    if (tempo_inicio>0)
    {
        *estado_sprite = ((tempo_jogo-tempo_inicio)/intervalo)%(limite_superior-limite_inferior+1);
        *estado_sprite = *estado_sprite + (limite_superior-limite_inferior + 1);
    }
}

void colide_chao(Tcriatura *ser,int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3],int tipo_criatura)
{
    // tipo_criatura pode ser 1 para heroi, e qualquer outro quando n�o �
    if(colisao_abaixo_mapa(ser->x, ser->y, ser->altura, ser->largura, matriz_tela, bloqueios))
    {
        ser->caindo=0;
        if(tipo_criatura==1)
        {
            if(!key[KEY_UP])ser->nivel_plataforma = ser->y+ser->altura - 1;
        }
        else
            ser->nivel_plataforma = ser->y+ser->altura - 1;
        ser->pulando=0;
        if(tipo_criatura==1)
        {
            if(!key[KEY_UP])ser->permitir_pulo=1;
        }
        else
            ser->permitir_pulo=1;
    }
}

void verificar_queda(Tcriatura *ser,int matriz_tela[ALTURA_MAPA/32][LARGURA_MAPA/32], int bloqueios[3])
{
    int i;

    if(ser->y <= ser->nivel_plataforma - ALTURA_PULO ||
       (!colisao_abaixo_mapa(ser->x, ser->y, ser->altura, ser->largura, matriz_tela, bloqueios)
        && !ser->pulando)||
       colisao_cima_mapa(ser->x,ser->y,ser->altura,ser->largura,matriz_tela,bloqueios))
    {
        ser->caindo=1;
        ser->permitir_pulo = 0;
    }

    for(i=0;i<5 && ser->caindo && !colisao_abaixo_mapa(ser->x, ser->y, ser->altura, ser->largura, matriz_tela, bloqueios);i++)
    {
        ser->y+=1;
    }
}

void ataque_ajustes(Tcriatura *atacante,int tempo_jogo,int confirmacao,int sprite_lim_inf,int sprite_lim_sup)
{
    if(!atacante->atacando && confirmacao)
    {
        atacante->atacando = 1;
        atacante->tempo_ataque = tempo_jogo;
    }
    if(atacante->tempo_ataque + 19 <= tempo_jogo)
        atacante->atacando = 0;

    if(atacante->atacando)
        mudanca_sprite(sprite_lim_inf,sprite_lim_sup,&atacante->estado_sprite,5,atacante->tempo_ataque,tempo_jogo);
}

void ataque(Tcriatura *atacante,Tcriatura *alvo,int tempo_jogo,int tipo_at,int at_ajusteX,int at_ajusteY,int at_largura,int at_altura)
{
    if(atacante->atacando && !alvo->levando_dano)
    {
        if(atacante->direcao==2)//esquerda
        {
            if(colisao(atacante->x + at_ajusteX,atacante->y + at_ajusteY,at_altura,at_largura,
                       alvo->x,alvo->y,alvo->altura,alvo->largura)&& tempo_jogo-atacante->tempo_ataque > 15)
               {
                   alvo->levando_dano=1;
                   alvo->tempo_dano=tempo_jogo;
                   calcular_dano(atacante,alvo,tipo_at);
               }
        }
        else //direita
        {
            if(colisao(atacante->x + atacante->largura + ((-1)*(at_largura+at_ajusteX)),atacante->y+at_ajusteY,at_altura,at_largura,
                       alvo->x,alvo->y,alvo->altura,alvo->largura )&& tempo_jogo-atacante->tempo_ataque > 15)
               {
                   alvo->levando_dano=1;
                   alvo->tempo_dano=tempo_jogo;
                   calcular_dano(atacante,alvo,tipo_at);
               }
        }
    }
}
