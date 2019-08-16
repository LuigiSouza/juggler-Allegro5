
#include "Includes.h"


float TamPlata(int pontos){

    float diminu = 45;

    if(pontos >= 700){
        diminu = 25;
    }

    return diminu;
}

float VeloAum(int pontos, float gravit){

    if(pontos >= 500){
        gravit *= 2;
    }

    return gravit;
}

void EncerraJogo(void){

    tela_fim();

    exit(1);
}

void Recordes(void){

    bool x = false;

    int controle = 0;

    while(x == false){
        x = desenha_recorde(controle);
    }
}

void Arruma_Limite(int *vet){

    FILE* arquivo = fopen("./img_ttf/Recordes.txt", "w");

    int i;

    if(arquivo == NULL){
        printf("\nFalha ao Abrir o arquivo de recorde (Recordes.txt...");
        EncerraJogo();
    }

    for(i=0;i<10;i++){
        fprintf(arquivo, "\n");
        fprintf(arquivo, "\n");
        fprintf(arquivo, "%d", *(vet+i));
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void Resetar_Recorde(void){

    FILE* arquivo = fopen("./img_ttf/Recordes.txt", "w");

    if(arquivo == NULL){
        printf("\nFalha ao Abrir o arquivo de recorde (Recordes.txt...");
        EncerraJogo();
    }

    fprintf(arquivo, " ");

    fclose(arquivo);
}

void Salvar_recorde(int pontos){

    FILE* arquivo = fopen("./img_ttf/Recordes.txt", "a+");

    if(arquivo == NULL){
        printf("\nFalha ao Abrir o arquivo de recorde (Recordes.txt...");
        EncerraJogo();
    }

    fprintf(arquivo, "\n");
    fprintf(arquivo, "\n");
    fprintf(arquivo, "%d", pontos);
    fprintf(arquivo, "\n");

    fclose(arquivo);
}

char OrdenaRecorde(int *result, int *z){

    FILE* arquivo = fopen("./img_ttf/Recordes.txt", "r+");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo...\n");
        EncerraJogo();
    }

    int i, j, control, aux, auxi;

    char linha[16];

    *z = 0;

    if(fgets(linha, 16, arquivo) == NULL){

        fclose(arquivo);

        Resetar_Recorde();

        arquivo = fopen("./img_ttf/Recordes.txt", "r+");
    }

    while (!feof(arquivo)){

        aux = 1;
        control = 1;
        fgets(linha, 16, arquivo);

        for(i=0;i<strlen(linha)-1;i++){
            if(linha[i] >= 48 && linha[i] <= 57){
                control = 0;
            }
        }

        if(control==0){

            *(result+*z) = 0;

            for(i=strlen(linha)-2;i>=0;i--){
                *(result+*z) += aux*(linha[i]-48);
                aux *= 10;
            }

            ++*z;
        }
    }

    --*z;

    for(i=0;i<*z;i++){

        for(j=0;j<*z;j++){

            if(*(result+j) < *(result+j+1) && j+1 != *z){
                auxi = *(result+j);
                *(result+j) = *(result+j+1);
                *(result+j+1) = auxi;
            }
            else{
                continue;
            }
        }
    }

    fclose(arquivo);

    if(*z > 10){

        Arruma_Limite(result);

        *z = 10;
    }

    return 1;
}

bool desenha_recorde(int controle){

    int clic = tela_rato_clicado();
    int pontos[11], i, z, j;
    int margem1, margem2 = 260;

    float xr, yr;

    char poin[11][11];

    tela_inicia_desenho();

    tela_cade_o_rato(&xr, &yr);

    tela_cria_imgRec();

    tela_retangulo(30, 30, 530, 610, 4, verde, transparente);
    tela_texto(LARGURA_TELA/2, 70, 50, amarelo, "Recordes");
    tela_texto(90, 200, 30, amarelo, "1:");
    tela_texto(90, 250, 30, laranja, "2:");
    tela_texto(90, 300, 30, marrom, "3:");
    tela_texto(90, 350, 30, azul, "4:");
    tela_texto(90, 400, 30, verde, "5:");
    tela_texto(300, 200, 30, preto, "6:");
    tela_texto(300, 250, 30, preto, "7:");
    tela_texto(300, 300, 30, preto, "8:");
    tela_texto(300, 350, 30, preto, "9:");
    tela_texto(300, 400, 30, preto, "10:");

    if(controle != 1){
        controle = OrdenaRecorde(&pontos[0], &z);
    }

    for(i=0;i<z;i++){

        j = i;

        if(i>4){
            j -= 5;
            margem2 = 470;
        }

        margem1 = 185 + (j*50);
        sprintf(poin[i], "%d", pontos[i]);
        tela_texto_esq(margem2, margem1, 30, amarelo, poin[i]);
    }

    if(xr >= 70 && xr <= 220 && yr <= 590 && yr >=560){
        tela_retangulo(70, 590, 220, 560, 2, azul, verde);
    }
    else{
        tela_retangulo(70, 590, 220, 560, 2, verde, azul);
    }
    tela_texto(145, 572, 25, branco, "Resetar");

    if(xr >= 340 && xr <= 490 && yr <= 590 && yr >=560){
        tela_retangulo(340, 590, 490, 560, 2, azul, verde);
    }
    else{
        tela_retangulo(340, 590, 490, 560, 2, verde, azul);
    }
    tela_texto(415, 572, 25, branco, "Voltar");

    if(clic ==1 && xr >= 340 && xr <= 490 && yr <= 590 && yr >=560){
        return true;
    }
    if(xr >= 70 && xr <= 220 && yr <= 590 && yr >=560 && clic == 1){
        controle = 0;
        Resetar_Recorde();
    }

    tela_termina_desenho();

    return false;
}

bool bate_bola(float raqx1, float raqx2, float bx, float by, float raio, float lim, int pontos){

    int margemRaq = 15;

    if(pontos >= 500){
        margemRaq = 20;
    }

    if(raqx1-RAIO<bx && RAIO+raqx2>bx && by+raio>=lim && by+raio<=lim+margemRaq){
        return true;
    }

    return false;
}

bool Limite(int num, int pontos, float tempo){

    if((num == 1 && tela_relogio() - tempo > 1) || (num == 2 && pontos >= 200 && tela_relogio() - tempo > 2)){
        return true;
    }

    return false;
}

char MostraNivel(int nivel){

    float Intervalo = tela_relogio();

    int resto;

    while(tela_relogio() <= Intervalo+4){

        resto = (int)tela_relogio()%2;

        if(resto == 0){
            desenha_nivel(1, nivel);
        }
        else{
            desenha_nivel(0, nivel);
        }
    }

    return 1;
}

void desenha_nivel(int num, int nivel){

    char niv[20];

    sprintf(niv, "%d", nivel);

    tela_inicia_desenho();
    tela_cria_imgContagem();
    tela_retangulo(30, 30, 530, 610, 4, verde, transparente);

    if(num == 1){
        tela_texto(LARGURA_TELA/2-20, ALTURA_TELA/2, 50, branco, "Nivel");
        tela_texto(350, ALTURA_TELA/2, 50, branco, niv);
    }
    else{
        tela_texto(LARGURA_TELA/2-20, ALTURA_TELA/2, 50, amarelo, "Nivel");
        tela_texto(350, ALTURA_TELA/2, 50, amarelo, niv);
    }

    tela_termina_desenho();
}