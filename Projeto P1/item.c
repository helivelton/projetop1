#include "item.h"

void preencher_item(Titem *objeto, float x, float y, int altura, int largura,
                    int ativo, int tipo,int imagem_preenchida,int id_arqueiro)
{
    BITMAP *tiles;

    if(tipo==1)
        tiles = load_bitmap(link_imagem("imagens_p1/Itens1.bmp"),NULL);
    else if(tipo==2)
        tiles = load_bitmap(link_imagem("imagens_p1/flecha.bmp"),NULL);

    if(!imagem_preenchida)
        objeto->imagem = create_bitmap(32,32);
    else
        clear_bitmap(objeto->imagem);

    if(tipo==1)
        blit(tiles,objeto->imagem,6*32,12*32,0,0,32,32);
    else if(tipo==2)
    {
        rectfill(objeto->imagem,0,0,32,32,makecol(255,0,255));
        draw_sprite(objeto->imagem,tiles,0,0);
    }

    objeto->x=x;
    objeto->y=y;
    objeto->altura=altura;
    objeto->largura=largura;
    objeto->tipo=tipo;
    objeto->ativo=ativo;
    objeto->id_arqueiro=id_arqueiro;
    objeto->direcao=0;
    objeto->imagem_buffer = create_bitmap(32,32);

    destroy_bitmap(tiles);
}

void movimento_itens(Titens *itens,Tcriatura *guerreiro,int tempo_jogo)
{
    int i;
    for(i=0;i<itens->n_itens;i++)
    {
        if(itens->todosItens[i].ativo)
        {
            switch(itens->todosItens[i].tipo)
            {
            case 2:
                if(itens->todosItens[i].direcao==1)
                    itens->todosItens[i].x+=2;
                else
                    itens->todosItens[i].x-=2;
                if(guerreiro->x - itens->todosItens[i].x > SCREEN_W || guerreiro->x - itens->todosItens[i].x < (-1)*SCREEN_W)
                    itens->todosItens[i].ativo=0;
                break;
            }
        }
    }
}

void desenhar_itens(BITMAP *buffer,Titens *objetos,int ajuste_x)
{
    int i;

    for(i=0;i<objetos->n_itens;i++)
    {
        if(objetos->todosItens[i].ativo)
        {
            clear_bitmap(objetos->todosItens[i].imagem_buffer);
            rectfill(objetos->todosItens[i].imagem_buffer,0,0,32,32,makecol(255,0,255));
            if(objetos->todosItens[i].direcao==1)
                draw_sprite_ex(objetos->todosItens[i].imagem_buffer,objetos->todosItens[i].imagem,0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
            else
                draw_sprite_ex(objetos->todosItens[i].imagem_buffer,objetos->todosItens[i].imagem,0,0,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
            draw_sprite(buffer, objetos->todosItens[i].imagem_buffer, objetos->todosItens[i].x + ajuste_x -(32-objetos->todosItens[i].largura)/2,
                        objetos->todosItens[i].y - (32-objetos->todosItens[i].altura)/2); // manda objeto para buffer
        }
    }
}

void verifique_efeito_item(Titens *itens,Tcriatura *guerreiro,Toponentes *inimigos,int tempo_jogo,SAMPLE *som_dano,SAMPLE* som_cura)
{
    int i;

    for(i=0;i<itens->n_itens;i++)
    {
        if (itens->todosItens[i].ativo)
        {
            if (colisao(guerreiro->x,guerreiro->y,guerreiro->altura,guerreiro->largura,itens->todosItens[i].x,
                        itens->todosItens[i].y,itens->todosItens[i].altura,itens->todosItens[i].largura))
            {
                switch(itens->todosItens[i].tipo)
                {
                case 1: // poção
                    play_sample(som_cura,255,128,1000,FALSE);
                    guerreiro->caracteristicas.hp+=5;
                    itens->todosItens[i].ativo=0;
                    guerreiro->curando=tempo_jogo;
                    break;
                case 2: // flecha
                    play_sample(som_dano,255,128,1000,FALSE);
                    guerreiro->levando_dano=1;
                    guerreiro->tempo_dano=tempo_jogo;
                    calcular_dano(&inimigos->goblins_arqueiros.goblins[itens->todosItens[i].id_arqueiro-1],guerreiro,1);
                    itens->todosItens[i].ativo=0;
                    break;
                }
            }
        }
    }
}
