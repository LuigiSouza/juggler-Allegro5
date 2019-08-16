
#include "Includes.h"


char Menu(float var, float var2, float var3){

    desenha_menu(var, var2, var3);

    float xr, yr;

    bool clic;

    tela_cade_o_rato(&xr, &yr);
    clic = tela_rato_clicado();

    if(clic ==1 && xr >= 200 && xr <= 350 && yr <= 270 && yr >=240){
        return 1;
    }
    if(clic ==1 && xr >= 200 && xr <= 350 && yr <= 330 && yr >=300){
        ajuda();
    }
    if(clic ==1 && xr >= 200 && xr <= 350 && yr <= 390 && yr >=360){
        Recordes();
    }
    if(clic ==1 && xr >= 200 && xr <= 350 && yr <= 450 && yr >=420){
        EncerraJogo();
    }

    return 0;
}

void desenha_menu(float var, float var2, float var3){

    int z = tela_cria_cor((sin(var3)+1)/2, (sin(var2)+1)/2, (sin(var)+1)/2);

    float xr, yr;

    tela_inicia_desenho();
    tela_cria_imgMenu();
    tela_cade_o_rato(&xr, &yr);

    tela_retangulo(30, 30, 530, 610, 4, verde, transparente);
    tela_texto(275, 150, 50, z, "Juggler");

    if(xr >= 200 && xr <= 350 && yr <= 270 && yr >=240){
        tela_retangulo(200, 270, 350, 240, 2, azul, verde);
    }
    else{
        tela_retangulo(200, 270, 350, 240, 2, verde, azul);
    }
    if(xr >= 200 && xr <= 350 && yr <= 330 && yr >=300){
        tela_retangulo(200, 330, 350, 300, 2, azul, verde);
    }
    else{
        tela_retangulo(200, 330, 350, 300, 2, verde, azul);
    }
    if(xr >= 200 && xr <= 350 && yr <= 390 && yr >=360){
        tela_retangulo(200, 390, 350, 360, 2, azul, verde);
    }
    else{
        tela_retangulo(200, 390, 350, 360, 2, verde, azul);
    }
    if(xr >= 200 && xr <= 350 && yr <= 450 && yr >=420){
        tela_retangulo(200, 450, 350, 420, 2, azul, verde);
    }
    else{
        tela_retangulo(200, 450, 350, 420, 2, verde, azul);
    }

    tela_texto(275, 252, 25, branco, "Inicio");
    tela_texto(275, 312, 25, branco, "Ajuda");
    tela_texto(275, 372, 25, branco, "Recordes");
    tela_texto(275, 432, 25, branco, "Sair");

    tela_termina_desenho();
}

void desenha_FimdeJOGO(int pontos, float tempo){

    int seg = tempo;
    int minu = (int)tempo/60;

    float xr, yr;

    tela_cade_o_rato(&xr, &yr);

    if(minu != 0){
        seg = (int)tempo%60;
    }

    char pont[20];
    char temp[20];
    char tems[20];

    sprintf(pont, "%d", pontos);
    sprintf(temp, "%02d", minu);
    sprintf(tems, "%02d", seg);
    tela_inicia_desenho();

    tela_retangulo(30, 30, 530, 610, 4, verde, transparente);
    tela_cria_gameover();
    tela_texto(275, 180, 50, amarelo, "Game Over");

    tela_texto_dir(55, 290, 25, branco, "Pontuacao:");
    tela_texto_dir(211, 290, 25, branco, pont);
    tela_texto_dir(55, 330, 25, branco, "Tempo:");
    tela_texto(226, 343, 25, branco, temp);
    tela_texto(247, 341, 25, branco, ":");
    tela_texto(267, 343, 25, branco, tems);;

    if(xr >= 340 && xr <= 490 && yr <= 570 && yr >=540){
        tela_retangulo(340, 570, 490, 540, 2, azul, verde);
    }
    else{
        tela_retangulo(340, 570, 490, 540, 2, verde, azul);
    }

    tela_texto(415, 552, 25, branco, "Menu");

    tela_termina_desenho();
}

char telaGameOver(int pontos, float tempo){

    int clic = tela_rato_clicado();

    float xr, yr;

    tela_cade_o_rato(&xr, &yr);

    desenha_FimdeJOGO(pontos, tempo);

    if(xr >= 340 && xr <= 490 && yr <= 570 && yr >=540 && clic == 1){
        Salvar_recorde(pontos);
        Recordes();
        return 1;
    }

    return 0;
}

void ajuda(void){

    bool x = false;

    while(x == false){
        x = desenha_ajuda();
    }
}

bool desenha_ajuda(){

    int clic = tela_rato_clicado();

    float xr, yr;

    tela_cade_o_rato(&xr, &yr);
    tela_inicia_desenho();

    tela_cria_imgAjuda();

    tela_retangulo(30, 30, 530, 610, 4, verde, transparente);

    tela_texto(275, 80, 50, amarelo, "Instrucoes:");
    tela_texto(275, 160, 18, branco, "O objetivo do jogo eh controlar a raquete com o");
    tela_texto(275, 185, 18, branco, "mouse para rebater as bolas que caem no chao");
    tela_texto(275, 240, 18, branco, "Caso uma bola caia, o jogador perde uma vida.");
    tela_texto(275, 265, 18, branco, "Caso as vidas se esgotem, o jogo acaba");
    tela_texto(275, 305, 18, amarelo, "Pressione 'Enter' quando desejar Pausar");

    tela_texto(108, 350, 20, branco, "Raquete:");
    tela_retangulo(413, 360, 483, 345, 3, verde, azul);

    tela_texto(87, 400, 20, branco, "Bola:");
    tela_circulo(446, 400, RAIO, 2, azul, vermelho);

    tela_texto(100, 450, 20, branco, "Nivel 1:");
    tela_texto(243, 450, 20, branco, "0 Pontos");
    tela_texto(100, 480, 20, branco, "Nivel 2:");
    tela_texto(230, 480, 20, branco, "200 Pontos");
    tela_texto(100, 510, 20, branco, "Nivel 3:");
    tela_texto(230, 510, 20, branco, "500 Pontos");
    tela_texto(100, 540, 20, branco, "Nivel 4:");
    tela_texto(230, 540, 20, branco, "700 Pontos");

    if(xr >= 360 && xr <= 510 && yr <= 570 && yr >=540){
        tela_retangulo(340, 570, 490, 540, 2, azul, verde);
    }
    else{
        tela_retangulo(340, 570, 490, 540, 2, verde, azul);
    }

    tela_texto(415, 552, 25, branco, "Voltar");

    if(clic ==1 && xr >= 340 && xr <= 490 && yr <= 570 && yr >=540){
        return true;
    }

    tela_termina_desenho();

    return false;
}

bool Func_pause(int *restat){

    *restat = 0;

    int clic = tela_rato_clicado();
    float xr, yr;

    char l = tela_le_tecla();

    tela_cade_o_rato(&xr, &yr);

    if((xr >= 200 && xr <= 360 && yr <= 323 && yr >=283 && clic == 1) || l == '\n'){
        return true;
    }
    if(xr >= 200 && xr <= 360 && yr <= 383 && yr >=343 && clic == 1){
        *restat = 2;
        return true;
    }
    if(xr >= 200 && xr <= 360 && yr <= 443 && yr >=403 && clic == 1){
        *restat = 1;
        return true;
    }

    Desenha_pause(xr, yr);

    return false;
}

void Desenha_pause(float xr, float yr){
    
    tela_retangulo(180, 190, 380, 460, 6, azul, preto);

    if(xr >= 200 && xr <= 360 && yr <= 323 && yr >=283){
        tela_retangulo(200, 323, 360, 283, 2, azul, verde);
    }
    else{
        tela_retangulo(200, 323, 360, 283, 2, verde, azul);
    }
    if(xr >= 200 && xr <= 360 && yr <= 383 && yr >=343){
        tela_retangulo(200, 383, 360, 343, 2, azul, verde);
    }
    else{
        tela_retangulo(200, 383, 360, 343, 2, verde, azul);
    }
    if(xr >= 200 && xr <= 360 && yr <= 443 && yr >=403){
        tela_retangulo(200, 443, 360, 403, 2, azul, verde);
    }
    else{
        tela_retangulo(200, 443, 360, 403, 2, verde, azul);
    }

    tela_texto(280, 230, 35, amarelo, "Pause");
    tela_texto(280, 300, 25, branco, "Continuar");
    tela_texto(280, 360, 25, branco, "Reiniciar");
    tela_texto(280, 420, 25, branco, "Menu");

    tela_termina_desenho();

}
