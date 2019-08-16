#ifndef _Include_Geral_
#define _Include_Geral_

#include "tela.h"
#include "Images.h"
#include "Menus.h"
#include "Mecanicas.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define transparente 0
#define azul         1
#define vermelho     2
#define verde        3
#define amarelo      4
#define preto        5
#define laranja      6
#define rosa         7
#define branco       8
#define marrom       9

#define ALTURA_TELA  640
#define LARGURA_TELA 560
#define SAIBOLA      250
#define RAIO         12
#define PULABOLA     RAIO*2

#define PERIODO (1/30.0)
#define NCORES 100

#endif
