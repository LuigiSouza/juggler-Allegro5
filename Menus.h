#ifndef _Telas_Menus_
#define _Telas_Menus_

#include "Includes.h"


char Menu(float var, float var2, float var3);

char telaGameOver(int pontos, float tempo);


bool desenha_ajuda(void);

bool Func_pause(int *restat);


void ajuda(void);

void desenha_FimdeJOGO(int pontos, float tempo);

void desenha_menu(float var, float var2, float var3);

void Desenha_pause(float xr, float yr);


#endif
