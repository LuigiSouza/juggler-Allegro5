#ifndef _Mechanics_
#define _Mechanics_

#include "Includes.h"


void Arruma_Limite(int *vet);

void desenha_nivel(int num, int nivel);

void Resetar_Recorde(void);

void Salvar_recorde(int pontos);


bool bate_bola(float raqx1, float raqx2, float bx, float by, float raio, float lim, int pontos);

bool desenha_recorde(int controle);

bool Limite(int num, int pontos, float tempo);


char OrdenaRecorde(int *result, int *z);


float TamPlata(int pontos);

float VeloAum(int pontos, float gravit);


int MostraNivel(int nivel);

int Recordes(void);


#endif // _Mechanics_
