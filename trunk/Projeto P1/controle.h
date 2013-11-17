#include <allegro.h>

int teclas_anteriores[KEY_MAX];

void keyboard_input();
int apertou(int TECLA);
int segurou(int TECLA);
int soltou(int TECLA);
