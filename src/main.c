
// para compilar este programa, use este comando:
// gcc -Wall -o exemplo exemplo.c tela.c -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro

#include "Includes.h"

typedef struct{

    float Velocidadex, Gravidadey;
    float tempoMORTO;
    float posx, posy;

} Bolinha;

void desenha_tela(int pontos, int num, Bolinha* bola,
                  float margee, float marged, int vidas,
                  float marge, float tempo){

    tela_inicia_desenho();

    tela_cria_fundo();

    int i;

    tela_retangulo(margee, 580, marged, 565, 3, verde, azul);

    char s[20];
    char v[5];
    char t[20];
    char m[20];

    int seg = tempo;
    int minu = (int)tempo/60;

    if(minu != 0){
        seg = (int)tempo%60;
    }

    sprintf(s, "%d", pontos);
    sprintf(v, "%d", vidas);
    sprintf(t, "%02d", seg);
    sprintf(m, "%02d", minu);

    tela_texto(65, 40, 26, branco, "Pontos: ");
    tela_texto(255, 40, 26, branco, "Vidas: ");
    tela_texto(410, 40, 26, branco, "Tempo: ");
    tela_texto(495, 38, 26, branco, ":");

    tela_texto_dir(120, 27, 26, branco, s);
    tela_texto(310, 40, 26, branco, v);
    tela_texto(515, 40, 26, branco, t);
    tela_texto(475, 40, 26, branco, m);

    for(i=0;i<num;i++){
        tela_circulo(bola[i].posx, bola[i].posy, RAIO, 2, azul, vermelho);
    }

    tela_termina_desenho();
}

int main(void){

    tela_inicio(LARGURA_TELA, ALTURA_TELA, "exemplo da tela");

    Bolinha bola[10];

    float var = 0, var2 = 0, var3 = 0;

    while(1){

        char z = 0, letra;

        int num = 1, i, x=0, y=0, vidas = 5, restart;
        int pontuacao = 0;
        int fase = 0, nivel = 1;

        float tempo = 0, tempoPause = 0, tempoReal = 0, tempoAux = 0, stop;

        bool wat = false;

        for(i=0;i<10;i++){
            bola[i].posx = 80 + (PULABOLA*i), bola[i].posy = SAIBOLA;
            bola[i].Velocidadex = 2, bola[i].Gravidadey = 0;
            bola[i].tempoMORTO = 0;
        }

        while(x != 1){

            var += 0.01;
            var2 += 0.05;
            var3 += 0.02;

            x = Menu(var, var2, var3);
        }

        while (y != 1){
            y = MostraNivel(nivel);
        }

        y = 0;

        tempo = tela_relogio();
        tempoPause += tempo;

        while (vidas > 0) {

            letra = tela_le_tecla();

            if(wat == false){
                letra = 0;
                wat = true;
            }

            if(letra == '\n'){

                bool pause = false;

                stop = tela_relogio();

                while(pause == false){
                    pause = Func_pause(&restart);
                }

                stop = tela_relogio() - stop;
                tempoPause += stop;
                tempo += stop;

                if(restart == 1){
                    z = 1;
                    break;
                }
                else if(restart == 2){

                    y = 0;
                    num = 1, x=1, y=0, /*z=0,*/ vidas = 5;
                    pontuacao = 0;
                    fase = 0, nivel = 1;

                    tempoPause = 0;
                    tempo = tela_relogio();
                    tempoPause += tempo;

                    for(i=0;i<10;i++){
                        bola[i].posx = 80 + (PULABOLA*i), bola[i].posy = SAIBOLA;
                        bola[i].Velocidadex = 2, bola[i].Gravidadey = 0;
                        bola[i].tempoMORTO = 0;
                    }

                    continue;
                }
            }

            tempoReal = tela_relogio() - tempoPause;

            float xr, yr;

            float marge = TamPlata(pontuacao);

            float margeme = xr-marge;
            float margemd = xr+marge;

            if(xr-marge < 0){
                margeme = 0;
                margemd = 2*marge;
            }

            if(xr+marge > LARGURA_TELA){
                margemd = LARGURA_TELA;
                margeme = LARGURA_TELA-2*marge;
            }

            tela_cade_o_rato(&xr, &yr);

            desenha_tela(pontuacao, num, bola, margeme, margemd, vidas, marge, tempoReal);

            for(i=0;i<num;i++){

                if((pontuacao == 200 || pontuacao == 500 || pontuacao == 700) && fase == 0){

                    for(i=0;i<10;i++){
                        bola[i].posx = 80 + (PULABOLA*i), bola[i].posy = SAIBOLA;
                        bola[i].Velocidadex = 2, bola[i].Gravidadey = 0;
                        bola[i].tempoMORTO = 0;
                    }

                    num = 1;
                    fase = 1;
                    nivel ++;

                    tempoAux = tela_relogio();

                    while (y != 1){
                        y = MostraNivel(nivel);
                    }

                    tempoPause += tela_relogio() - tempoAux;
                    tempo = tela_relogio();

                    y = 0;

                    break;
                }

                int wait = 0, j;

                float gravity = 0.25;
                float desvio = 0.1;

                gravity = VeloAum(pontuacao, gravity);
                desvio = VeloAum(pontuacao, desvio);

                if(bola[i].posx > LARGURA_TELA-RAIO && bola[i].Velocidadex < 0){
                    bola[i].posx = LARGURA_TELA-RAIO;
                }

                if(bola[i].posx < RAIO && bola[i].Velocidadex > 0){
                    bola[i].posx = RAIO;
                }

                float AuxDesvio;

                if (bola[i].posx < RAIO || bola[i].posx > LARGURA_TELA-RAIO) {
                    bola[i].Velocidadex *= -1;
                }

                if (bola[i].posy > ALTURA_TELA-RAIO){

                    bola[i].Gravidadey = 0;

                    for(j = 0; j < num; j++){

                        if(bola[j].posy > 300 && bola[j].posy < 590){
                            wait = 1;
                        }
                    }

                    if(bola[i].tempoMORTO == 0){
                        vidas--;
                        bola[i].tempoMORTO = tela_relogio()+2;
                    }

                    else if(tela_relogio() > bola[i].tempoMORTO && wait == 0){

                        bola[i].posy = 550;
                        bola[i].Velocidadex = 2, bola[i].Gravidadey = -13;

                        if(pontuacao>=500){
                            bola[i].Gravidadey = -18.5;
                        }

                        bola[i].tempoMORTO = 0;
                    }

                    continue;
                }

                if (bola[i].posy < SAIBOLA) {

                    if(bola[i].Gravidadey < 0){
                        bola[i].Gravidadey += 0.60;
                    }
                    else{
                        bola[i].Gravidadey += 0.2;
                    }

                    bola[i].posy += bola[i].Gravidadey;
                }
                else{
                    bola[i].posy += bola[i].Gravidadey;

                    bola[i].Gravidadey += gravity;
                }

                bola[i].posx += bola[i].Velocidadex;

                printf("\nbolass: %f", bola[0].Velocidadex);

                if (bate_bola(margeme, margemd, bola[i].posx, bola[i].posy, RAIO, 565, pontuacao)) {

                    AuxDesvio = (margemd-35) - (float)bola[i].posx;
                    AuxDesvio *= desvio;

                    bola[i].Velocidadex -= AuxDesvio;

                    if(bola[i].Velocidadex > 7){
                        bola[i].Velocidadex = 7;
                    }
                    if(bola[i].Velocidadex < -7){
                        bola[i].Velocidadex = -7;
                    }

                    bola[i].Gravidadey = bola[i].Gravidadey * (-1);

                    pontuacao += 20;
                    fase = 0;
                }

                if(Limite(num, pontuacao, tempo)) {
                        num++;
                }
            }
        }
        while(z != 1){
            z = telaGameOver(pontuacao, tempoReal);
        }
    }

  tela_fim();

  return 0;
}
