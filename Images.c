
#include "Includes.h"


ALLEGRO_BITMAP *tela         = NULL;
ALLEGRO_BITMAP *telaMenu     = NULL;
ALLEGRO_BITMAP *telaContagem = NULL;
ALLEGRO_BITMAP *telaAjuda    = NULL;
ALLEGRO_BITMAP *gameover     = NULL;
ALLEGRO_BITMAP *telarec      = NULL;


void tela_inicializa_janela(float l, float a, char n[])
{
    if(!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar o Image Addon.\n");
        exit(1);
    }

    ALLEGRO_DISPLAY *janel = al_create_display(l, a);
}

void tela_inicializa_imgAjuda(void){

    telaAjuda = al_load_bitmap("./img_ttf/ajuda.png");

    if(!telaAjuda)
    {
        fprintf(stderr, "Falha ao carregar a imagem da tela de Ajuda.\n");
        exit(1);
    }
}

void tela_inicializa_imgContagem(void){

    telaContagem = al_load_bitmap("./img_ttf/contagem.jpg");

    if(!telaContagem)
    {
        fprintf(stderr, "Falha ao carregar a imagem da tela de Contagem.\n");
        exit(1);
    }
}

void tela_inicializa_imgGameOver(void){

    gameover = al_load_bitmap("./img_ttf/gameover.jpg");

    if(!gameover)
    {
        fprintf(stderr, "Falha ao carregar a imagem da tela de Fim.\n");
        exit(1);
    }
}

void tela_inicializa_imgMenu(void){

    telaMenu = al_load_bitmap("./img_ttf/Menu.jpg");

    if(!telaMenu)
    {
        fprintf(stderr, "Falha ao carregar a imagem do menu.\n");
        exit(1);
    }
}

void tela_inicializa_imgtela(void){

    tela = al_load_bitmap("./img_ttf/fundo.jpg");

    if(!tela)
    {
        fprintf(stderr, "Falha ao carregar a imagem de fundo.\n");
        exit(1);
    }
}

void tela_inicializa_imgRecorde(void){

    telarec = al_load_bitmap("./img_ttf/trofeu.jpg");

    if(!telarec)
    {
        fprintf(stderr, "Falha ao carregar a imagem dos recordes.\n");
        exit(1);
    }
}

void tela_cria_imgAjuda(void){
    al_draw_bitmap(telaAjuda, 30, 30, 0);
}

void tela_cria_imgContagem(void){
    al_draw_bitmap(telaContagem, 30, 30, 0);
}

void tela_cria_gameover(void){
    al_draw_bitmap(gameover, 30, 30, 0);
}

void tela_cria_imgMenu(void){
    al_draw_bitmap(telaMenu, 30, 30, 0);
}

void tela_cria_fundo(void){
    al_draw_bitmap(tela, 0, 0, 0);
}

void tela_cria_imgRec(void){
    al_draw_bitmap(telarec, 30, 30, 0);
}
