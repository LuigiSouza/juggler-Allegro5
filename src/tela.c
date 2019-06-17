
#include "Includes.h"


ALLEGRO_EVENT_QUEUE *tela_eventos_teclado;
void tela_inicializa_teclado(void)
{
  al_install_keyboard();

  tela_eventos_teclado = al_create_event_queue();
  al_register_event_source(tela_eventos_teclado,
                           al_get_keyboard_event_source());
}


ALLEGRO_COLOR cores[NCORES];
int ncores_predef = 10;
int prox_cor = 10;


void tela_inicializa_cores(void)
{
  cores[transparente] = al_map_rgba_f(0, 0, 0, 0);
  cores[azul]         = al_map_rgb_f(0, 0, 1);
  cores[vermelho]     = al_map_rgb_f(1, 0, 0);
  cores[verde]        = al_map_rgb_f(0, 1, 0);
  cores[amarelo]      = al_map_rgb_f(1, 1, 0);
  cores[preto]        = al_map_rgb_f(0, 0, 0);
  cores[laranja]      = al_map_rgb_f(1, 0.65, 0);
  cores[rosa]         = al_map_rgb_f(1, 0, 0.5);
  cores[branco]       = al_map_rgb_f(1, 1, 1);
  cores[marrom]       = al_map_rgb_f(0.58, 0.29, 0);
}

int tela_cria_cor(float vm, float az, float vd)
{
  int cor = prox_cor;

  prox_cor = prox_cor+1;

  if (prox_cor >= NCORES) {
    prox_cor = ncores_predef;
  }
  cores[cor] = al_map_rgb_f(vm, az, vd);

  return cor;
}

void tela_inicio(int largura, int altura, char nome[])
{
  al_init();
  al_install_mouse();
  al_init_primitives_addon();
  al_init_font_addon();
  al_init_ttf_addon();

  tela_inicializa_janela(largura, altura, nome);
  tela_inicializa_teclado();
  tela_inicializa_cores();
  tela_inicializa_imgtela();
  tela_inicializa_imgMenu();
  tela_inicializa_imgContagem();
  tela_inicializa_imgAjuda();
  tela_inicializa_imgGameOver();
  tela_inicializa_imgRecorde();
  tela_inicializa_imgPause();
}

void tela_fim(void)
{
  al_uninstall_system();
}

int conta_telas = 0;
void tela_termina_desenho(void)
{
  conta_telas++;

  double quando_a_tela_deve_ser_mostrada = conta_telas * PERIODO;
  double agora = tela_relogio();
  double tempo_ate_mostrar = quando_a_tela_deve_ser_mostrada - agora;

  if (tempo_ate_mostrar > 0) {
    al_rest(tempo_ate_mostrar);
  }

  al_flip_display();
}


void tela_inicia_desenho(void)
{
  al_clear_to_color(cores[preto]);
}

void tela_circulo(float x, float y, float r, float l, int corl, int corint)
{

  al_draw_filled_circle(x, y, r, cores[corint]);

  al_draw_circle(x, y, r, cores[corl], l);
}

void tela_linha(float x1, float y1, float x2, float y2, float l, int corl)
{
  al_draw_line(x1, y1, x2, y2, cores[corl], l);
}

void tela_retangulo(float x1, float y1, float x2, float y2, float l,
                    int corl, int corint)
{
  al_draw_filled_rectangle(x1, y1, x2, y2, cores[corint]);
  al_draw_rectangle(x1, y1, x2, y2, cores[corl], l);
}


ALLEGRO_FONT *fonte = NULL;
int tamanho_das_letras = 0;

void tela_prepara_fonte(int tam)
{

  if (tam == tamanho_das_letras) return;


  if (fonte != NULL) {
    al_destroy_font(fonte);
  }


  fonte = al_load_font("./img_ttf/DejaVuSans.ttf", tam, 0);

  if (fonte == NULL) {
    al_uninstall_system();
    printf("\n\nERRO FATAL\n");
    printf("ARQUIVO QUE DEFINE DESENHO DAS LETRAS (DejaVuSans.ttf.ttf) NAO ENCONTRADO.\n"
           "COPIE ESSE ARQUIVO, OU MUDE tela.c PARA USAR UM ARQUIVO QUE EXISTA.\n\n");
    exit(1);
  }

  tamanho_das_letras = tam;
}

void tela_texto(float x, float y, int tam, int c, char t[])
{
  tela_prepara_fonte(tam);
  al_draw_text(fonte, cores[c], x, y-tam/2, ALLEGRO_ALIGN_CENTRE, t);
}

void tela_texto_esq(float x, float y, int tam, int c, char t[])
{
  tela_prepara_fonte(tam);
  al_draw_text(fonte, cores[c], x, y, ALLEGRO_ALIGN_RIGHT, t);
}

void tela_texto_dir(float x, float y, int tam, int c, char t[])
{
  tela_prepara_fonte(tam);
  al_draw_text(fonte, cores[c], x, y, ALLEGRO_ALIGN_LEFT, t);
}

void tela_cade_o_rato(float *x, float *y)
{

  ALLEGRO_MOUSE_STATE rato;
  al_get_mouse_state(&rato);
  *x = al_get_mouse_state_axis(&rato, 0);
  *y = al_get_mouse_state_axis(&rato, 1);
}

bool tela_rato_apertado(void)
{
  ALLEGRO_MOUSE_STATE rato;
  al_get_mouse_state(&rato);

  return al_mouse_button_down(&rato, 1);
}

bool tava_apertado = false;
float x_clicado = 0;
float y_clicado = 0;
bool tela_rato_clicado(void)
{
  bool ta_apertado = tela_rato_apertado();
  bool foi_clicado = (!tava_apertado && ta_apertado);

  if (foi_clicado) {
    tela_cade_o_rato(&x_clicado, &y_clicado);
  }

  tava_apertado = ta_apertado;
  return foi_clicado;
}

void tela_rato_clique(float *x, float *y)
{
  *x = x_clicado;
  *y = y_clicado;
}

char tela_le_tecla(void)
{
  ALLEGRO_EVENT ev;

  while (al_get_next_event(tela_eventos_teclado, &ev)) {
    if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
      int c = ev.keyboard.unichar;
      if (c == '\r') c = '\n';
      if ((c >= 'A' && c <= '~' && (c < 48 || c > 57)) || c == '\b' || c == '\n') {
        return (char) c;
      }
    }
  }

  return '\0';
}

double tela_relogio(void)
{
  return al_get_time();
}


