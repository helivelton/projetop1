#include "item.h"

void preencher_item(Titem *objeto, float x, float y, int altura, int largura, char imagem_link[255],int posicaox,int posicaoy,
                    int ativo, int tipo,int imagem_preenchida)
{
    BITMAP *tiles = load_bitmap(link_imagem(imagem_link),NULL);

    if(!imagem_preenchida)
        objeto->imagem = create_bitmap(32,32);
    else
        clear_bitmap(objeto->imagem);

    blit(tiles,objeto->imagem,posicaox*32,posicaoy*32,0,0,32,32);

    objeto->x=x;
    objeto->y=y;
    objeto->altura=altura;
    objeto->largura=largura;
    objeto->tipo=tipo;
    objeto->ativo=ativo;

    destroy_bitmap(tiles);
}

void desenhar_item(BITMAP *buffer,Titem *objeto,int ajuste_x)
{
    draw_sprite(buffer, objeto->imagem, objeto->x + ajuste_x -(32-objeto->largura)/2,
                objeto->y - (32-objeto->altura)/2); // manda objeto para buffer
}

void verifique_efeito_item(Titens *itens,Tcriatura *guerreiro)
{
    int i;

    for(i=0;i<itens->n_itens;i++)
    {
        if (itens->todosItens[i].ativo)
        {
            if (colisao(guerreiro->x,guerreiro->y,guerreiro->altura,guerreiro->largura,itens->todosItens[i].x,itens->todosItens[i].y,itens->todosItens[i].altura,itens->todosItens[i].largura))
            {
                switch(itens->todosItens[i].tipo)
                {
                case 1:
                    guerreiro->caracteristicas.hp+=5;
                    itens->todosItens[i].ativo=0;
                    break;
                }
            }
        }
    }


}
