#ifndef ctjump_h
#define ctjump_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ncurses.h>
#include <time.h>


#define n_linhas  35
#define n_colunas 140

#define galinha_x 48
#define porco_x 30
#define vaca_x 8

#define VACA 0
#define PORCO 1
#define GALINHA 2            

#define MAX_INIMIGOS_AR 6
#define MAX_INIMIGOS_TERRA 6

#define TEMPO_TICK 3840000

void audio(int _audio);

void coloca_inimigo_terra(int id_inimigo);

void coloca_inimigo_ar(int id_inimigo);

void coloca_todos_inimigos();

void coloca_animal(int id_animal);

void coloca_todos_animais();

void coloca_mapa();

void animal_pula(int id_animal);

void inimigo_ar_move();

void inimigo_terra_move();

void cria_inimigo_ar(int y, int x);

void cria_inimigo_terra(int n_inimigos);

void aleatoriza_inimigo();

void atualiza_mapa();

void desenha_menu(int opcao_selecionada);

void desenha_recorde();

void desenha_instrucoes();

void game_over();

void inicia_jogo();

void pausa_jogo();

void detecta_tecla_apertada();

void verifica_estado_jogo();


#endif
