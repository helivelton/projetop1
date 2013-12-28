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

void desenhar_itens(BITMAP *buffer,Titens *objetos,int ajuste_x)
{
    int i;

    for(i=0;i<objetos->n_itens;i++)
    {
        if(objetos->todosItens[i].ativo)
            draw_sprite(buffer, objetos->todosItens[i].imagem, objetos->todosItens[i].x + ajuste_x -(32-objetos->todosItens[i].largura)/2,
                        objetos->todosItens[i].y - (32-objetos->todosItens[i].altura)/2); // manda objeto para buffer
    }
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
                case 1: // poção
                    guerreiro->caracteristicas.hp+=5;
                    itens->todosItens[i].ativo=0;
                    break;
                }
            }
        }
    }


}
