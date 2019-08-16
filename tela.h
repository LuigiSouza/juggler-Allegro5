#ifndef _tela_h_
#define _tela_h_

#include "Includes.h"
#include <stdbool.h>


int tela_cria_cor(float vm, float az, float vd);


void tela_cade_o_rato(float *x, float *y);

void tela_circulo(float x, float y, float r, float l, int corl, int corint);

void tela_inicia_desenho(void);

void tela_inicio(int largura, int altura, char nome[]);

void tela_linha(float x1, float y1, float x2, float y2, float l, int corl);

void tela_rato_clique(float *x, float *y);

void tela_retangulo(float x1, float y1, float x2, float y2, float l,
                    int corl, int corint);

void tela_termina_desenho(void);

void tela_texto(float x, float y, int tam, int c, char t[]);

void tela_texto_dir(float x, float y, int tam, int c, char t[]);

void tela_texto_esq(float x, float y, int tam, int c, char t[]);

void tela_fim(void);


char tela_le_tecla(void);


double tela_relogio(void);


bool tela_rato_apertado(void);

bool tela_rato_clicado(void);

#endif
