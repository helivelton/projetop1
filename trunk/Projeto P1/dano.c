#include "dano.h"

int dano_ataque(Tcriatura* atacante)
{
    int ataque=atacante->caracteristicas.forca;

    float a = (rand()%100)/100.0;
    ataque= ataque*(0.8 + a*0.4);
    return ataque;
}


void calcular_dano(Tcriatura* atacante, Tcriatura* alvo)
{
    int ataque = dano_ataque(atacante);
    //int forca=atacante->caracteristicas.forca;
    int defesa= alvo->caracteristicas.resistencia + alvo->caracteristicas.armadura;
    int hp= alvo->caracteristicas.hp;
    float chance_critico=0.1;
    float a = (rand()%100)/100.0;
    int critico = chance_critico > a? 2 : 1;
    int dano;

    dano= (ataque-defesa)*critico;
    dano= dano > 0? dano : 0;

    alvo->caracteristicas.hp-=dano;



    return dano;

}
