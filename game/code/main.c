#include "../header/ctjump.h"

int score = 0;
int highscore = 0;
int level = 1;

int animais_y[3] = {n_linhas-2,n_linhas-2,n_linhas-2}; 
const int animais_x[3] = {vaca_x, porco_x, galinha_x};

bool animal_vivo[3] = {true,true,true}; 
bool animal_pulando[3] = {false,false,false};
bool animal_caindo[3] = {false,false,false}; 
bool animal_tick = false; 

int inimigo_ar_x[MAX_INIMIGOS_AR] ;
int inimigo_ar_y[MAX_INIMIGOS_AR] ;
bool inimigo_ar_existe[MAX_INIMIGOS_AR];

int inimigo_terra_x[MAX_INIMIGOS_TERRA];
const int inimigo_terra_y = n_linhas-2;
bool inimigo_terra_existe[MAX_INIMIGOS_TERRA];

bool game_is_lost = false;

int main()
{
    int opcao_selecionada = 1;
    int c;

    //system("printf '\e[8;40;180t'");

    initscr(); 
    noecho();  
    cbreak();
    curs_set(0); 
    nodelay(stdscr,false);
    keypad(stdscr,true); 
    wresize(stdscr,n_linhas,n_colunas); 

    while(1) { 

        desenha_menu(opcao_selecionada);
        c = getch(); 
        if(c == KEY_UP) { 

            if(opcao_selecionada == 1) 
                opcao_selecionada = 4;
            else
                opcao_selecionada--;
		
	    audio(4);

        } else if(c== KEY_DOWN) {
            if(opcao_selecionada == 4)
                opcao_selecionada = 1;
            else
                opcao_selecionada++;

	    audio(4);
        }

        if(c == (int)'\n') { 
	    
	    audio(40);

            if(opcao_selecionada == 4)
                break;

            else if(opcao_selecionada == 3)
            {
                desenha_recorde();
            }

            else if(opcao_selecionada == 2) 
            {
                desenha_instrucoes();
            }
            else if(opcao_selecionada == 1) { 

                long int tick = 0; 
                inicia_jogo(); 
		


                while (game_is_lost == false) {

                    detecta_tecla_apertada();

                    if (tick % (TEMPO_TICK / 96) == 0) { //ocorre 96 vezes por ciclo
                        inimigo_ar_move();
                        inimigo_terra_move();

                        verifica_estado_jogo(); 
                    }

                    if (tick % (TEMPO_TICK / 48) == 0) { //ocorre 48 vezes por ciclo

                        for (int i = 0; i < 3; i++)
                            animal_pula(i);
                    }

                    if (tick % (TEMPO_TICK / 48) == 0) {
                        atualiza_mapa();
                    }

                    if (tick % (TEMPO_TICK / 12) == 0) { //ocorre 12 vezes por ciclo

                        if (animal_tick == false)
                            animal_tick = true;
                        else
                            animal_tick = false;
                    }

                    tick++;


                    if (tick > TEMPO_TICK) { //ocorre no fim de cada ciclo
                        tick = 1;
                        aleatoriza_inimigo();
                    }
		   
                }
                game_over(); 
            }
	}
    }
    endwin(); 

    return 0;
}

void coloca_inimigo_terra(int id_inimigo) 
{
    if( inimigo_terra_existe[id_inimigo] == true)
    {
        if (inimigo_terra_x[id_inimigo] < n_colunas - 1 && inimigo_terra_x[id_inimigo] > 0) {
            mvprintw(n_linhas-2, inimigo_terra_x[id_inimigo], "|");
            mvprintw(n_linhas-3, inimigo_terra_x[id_inimigo], "|");
            mvprintw(n_linhas-4, inimigo_terra_x[id_inimigo], "|");
            mvprintw(n_linhas-5, inimigo_terra_x[id_inimigo], "|");
            mvprintw(n_linhas-6, inimigo_terra_x[id_inimigo], "|");
        }

        if (inimigo_terra_x[id_inimigo] < n_colunas - 2 && inimigo_terra_x[id_inimigo] > -1) {
            mvprintw(n_linhas-2, inimigo_terra_x[id_inimigo] + 1, "_");
            mvprintw(n_linhas-7, inimigo_terra_x[id_inimigo] + 1, "_");
        }

        if (inimigo_terra_x[id_inimigo] < n_colunas - 3 && inimigo_terra_x[id_inimigo] > -2) {
            mvprintw(n_linhas-2, inimigo_terra_x[id_inimigo] + 2, "|");
            mvprintw(n_linhas-3, inimigo_terra_x[id_inimigo] + 2, "|");
            mvprintw(n_linhas-4, inimigo_terra_x[id_inimigo] + 2, "|");
            mvprintw(n_linhas-5, inimigo_terra_x[id_inimigo] + 2, "|");
            mvprintw(n_linhas-6, inimigo_terra_x[id_inimigo] + 2, "|");
        }

        if (inimigo_terra_x[id_inimigo] < n_colunas - 4 && inimigo_terra_x[id_inimigo] > -3) {
            mvprintw(n_linhas-3, inimigo_terra_x[id_inimigo] + 3, "_");
            mvprintw(n_linhas-4, inimigo_terra_x[id_inimigo] + 3, "_");
            mvprintw(n_linhas-5, inimigo_terra_x[id_inimigo] + 3, "_");
            mvprintw(n_linhas-6, inimigo_terra_x[id_inimigo] + 3, "_");
        }

        if (inimigo_terra_x[id_inimigo] < n_colunas - 5 && inimigo_terra_x[id_inimigo] > -4) {
            mvprintw(n_linhas-3, inimigo_terra_x[id_inimigo] + 4, "_");
            mvprintw(n_linhas-4, inimigo_terra_x[id_inimigo] + 4, "_");
            mvprintw(n_linhas-5, inimigo_terra_x[id_inimigo] + 4, "_");
            mvprintw(n_linhas-6, inimigo_terra_x[id_inimigo] + 4, "_");
        }

        if (inimigo_terra_x[id_inimigo] < n_colunas - 6 && inimigo_terra_x[id_inimigo] > -5) {
            mvprintw(n_linhas-3, inimigo_terra_x[id_inimigo] + 5, "_");
            mvprintw(n_linhas-4, inimigo_terra_x[id_inimigo] + 5, "_");
            mvprintw(n_linhas-5, inimigo_terra_x[id_inimigo] + 5, "_");
            mvprintw(n_linhas-6, inimigo_terra_x[id_inimigo] + 5, "_");
        }

        if (inimigo_terra_x[id_inimigo] < n_colunas - 7 && inimigo_terra_x[id_inimigo] > -6) {
            mvprintw(n_linhas-3, inimigo_terra_x[id_inimigo] + 6, "_");
            mvprintw(n_linhas-4, inimigo_terra_x[id_inimigo] + 6, "_");
            mvprintw(n_linhas-5, inimigo_terra_x[id_inimigo] + 6, "_");
            mvprintw(n_linhas-6, inimigo_terra_x[id_inimigo] + 6, "_");
        }

        if (inimigo_terra_x[id_inimigo] < n_colunas - 8 && inimigo_terra_x[id_inimigo] > -7) {
            mvprintw(n_linhas-3, inimigo_terra_x[id_inimigo] + 7, "_");
            mvprintw(n_linhas-4, inimigo_terra_x[id_inimigo] + 7, "_");
            mvprintw(n_linhas-5, inimigo_terra_x[id_inimigo] + 7, "_");
            mvprintw(n_linhas-6, inimigo_terra_x[id_inimigo] + 7, "_");
        }

        if (inimigo_terra_x[id_inimigo] < n_colunas - 9 && inimigo_terra_x[id_inimigo] > -8) {
            mvprintw(n_linhas-3, inimigo_terra_x[id_inimigo] + 8, "_");
            mvprintw(n_linhas-4, inimigo_terra_x[id_inimigo] + 8, "_");
            mvprintw(n_linhas-5, inimigo_terra_x[id_inimigo] + 8, "_");
            mvprintw(n_linhas-6, inimigo_terra_x[id_inimigo] + 8, "_");
        }

        if (inimigo_terra_x[id_inimigo] < n_colunas - 10 && inimigo_terra_x[id_inimigo] > -9) {
            mvprintw(n_linhas-2, inimigo_terra_x[id_inimigo] + 9, "|");
            mvprintw(n_linhas-3, inimigo_terra_x[id_inimigo] + 9, "|");
            mvprintw(n_linhas-4, inimigo_terra_x[id_inimigo] + 9, "|");
            mvprintw(n_linhas-5, inimigo_terra_x[id_inimigo] + 9, "|");
            mvprintw(n_linhas-6, inimigo_terra_x[id_inimigo] + 9, "|");
        }

        if (inimigo_terra_x[id_inimigo] < n_colunas - 11 && inimigo_terra_x[id_inimigo] > -10) {
            mvprintw(n_linhas-2, inimigo_terra_x[id_inimigo] + 10, "_");
            mvprintw(n_linhas-7, inimigo_terra_x[id_inimigo] + 10, "_");
        }

        if (inimigo_terra_x[id_inimigo] < n_colunas - 12 && inimigo_terra_x[id_inimigo] > -11) {
            mvprintw(n_linhas-2, inimigo_terra_x[id_inimigo] + 11, "|");
            mvprintw(n_linhas-3, inimigo_terra_x[id_inimigo] + 11, "|");
            mvprintw(n_linhas-4, inimigo_terra_x[id_inimigo] + 11, "|");
            mvprintw(n_linhas-5, inimigo_terra_x[id_inimigo] + 11, "|");
            mvprintw(n_linhas-6, inimigo_terra_x[id_inimigo] + 11, "|");
        }
    }
}

void coloca_inimigo_ar(int id_inimigo) {

    if (inimigo_ar_existe[id_inimigo] == true) {

        if (inimigo_ar_x[id_inimigo] < n_colunas - 1 && inimigo_ar_x[id_inimigo] > 0)
            mvprintw(inimigo_ar_y[id_inimigo], inimigo_ar_x[id_inimigo], "<");

        if (inimigo_ar_x[id_inimigo] < n_colunas - 2 && inimigo_ar_x[id_inimigo] > -1)
            mvprintw(inimigo_ar_y[id_inimigo], inimigo_ar_x[id_inimigo] + 1, "-");

        if (inimigo_ar_x[id_inimigo] < n_colunas - 3 && inimigo_ar_x[id_inimigo] > -2)
            mvprintw(inimigo_ar_y[id_inimigo], inimigo_ar_x[id_inimigo] + 2, "-");

        if (inimigo_ar_x[id_inimigo] < n_colunas - 4 && inimigo_ar_x[id_inimigo] > -3)
            mvprintw(inimigo_ar_y[id_inimigo], inimigo_ar_x[id_inimigo] + 3, "x");

    }
}

void coloca_todos_inimigos() 
{
    for(int i = 0; i < MAX_INIMIGOS_TERRA; i++)
    {
        coloca_inimigo_terra(i);
    }
    for(int i = 0; i < MAX_INIMIGOS_AR; i++)
    {
        coloca_inimigo_ar(i);
    }
}

void coloca_animal(int id_animal)
{
    if(id_animal == GALINHA) {



            if (animal_tick == false) {
                mvprintw(animais_y[GALINHA], animais_x[GALINHA] + 1, "^ ^");
                mvprintw(animais_y[GALINHA] - 2, animais_x[GALINHA] + 2, "/o>");
                mvprintw(animais_y[GALINHA] - 3, animais_x[GALINHA] + 3, ",");

            } else {
                mvprintw(animais_y[GALINHA], animais_x[GALINHA], "^   ^");
                mvprintw(animais_y[GALINHA] - 2, animais_x[GALINHA] + 2, "_/o>");
                mvprintw(animais_y[GALINHA] - 3, animais_x[GALINHA] + 4, ",");
            }

            mvprintw(animais_y[GALINHA] - 1, animais_x[GALINHA], "\\_c_|");
            mvprintw(animais_y[GALINHA] - 2, animais_x[GALINHA], "__");

    }

    if(id_animal == PORCO) {


            if (animal_tick == false) {
                move(animais_y[PORCO], animais_x[PORCO] + 1);
                printw("/_/   \\_\\");

            } else {
                move(animais_y[PORCO], animais_x[PORCO] + 2);
                printw("\\_\\ /_/");
            }

            move(animais_y[PORCO] - 1, animais_x[PORCO] + 1);
            printw("\\  ___  /");
            move(animais_y[PORCO] - 2, animais_x[PORCO]);
            printw("~|        _d");
            move(animais_y[PORCO] - 3, animais_x[PORCO] + 2);
            printw("_____| o |");
            move(animais_y[PORCO] - 4, animais_x[PORCO] + 8);
            printw("n__");

    }

    if(id_animal == VACA) {


            if (animal_tick == false) {
                move(animais_y[VACA], animais_x[VACA] + 1);
                printw("/_/\\_\\  /_/\\_\\");
                move(animais_y[VACA] - 1, animais_x[VACA] + 2);
                printw("/ /\\    /\\ \\");

            } else {
                move(animais_y[VACA], animais_x[VACA] + 2);
                printw("|_|     |_|");
                move(animais_y[VACA] - 1, animais_x[VACA] + 2);
                printw("| |     | |");
            }

            move(animais_y[VACA] - 2, animais_x[VACA]);
            printw("W |  ___(_)  /");
            move(animais_y[VACA] - 3, animais_x[VACA]);
            printw("//|      _    /");
            move(animais_y[VACA] - 4, animais_x[VACA] + 1);
            printw("/  (___)   U  _d");
            move(animais_y[VACA] - 5, animais_x[VACA] + 2);
            printw("_________/ O \\");
            move(animais_y[VACA] - 6, animais_x[VACA] + 12);
            printw("___");

    }

}

void coloca_todos_animais()
{
    for(int i = 0; i < 3; i++)
    {
        if(animal_vivo[i] == true)
            coloca_animal(i);
    }
}

void coloca_mapa(){ 

    box(stdscr,0,0);
    move(2,1); 
    hline(0,14);
    move(1,14);
    vline(0,1); 
    mvprintw(1,2,"SCORE %05d",score); 
    if(level == 4)
        mvprintw(1,n_colunas - 15,"Level HELL!!!");
    else 
        mvprintw(1,n_colunas - 9,"Level %d",level);

}

void animal_pula(int id_animal) { 

    if (animal_vivo[id_animal] == true) {

        if (animal_pulando[id_animal] == true) {

            animais_y[id_animal]--;

            if (animais_y[id_animal] == n_linhas - 18) { 
                animal_pulando[id_animal] = false;
                animal_caindo[id_animal] = true;
            }

        } else if (animal_caindo[id_animal]) {
            animais_y[id_animal]++;

            if (animais_y[id_animal] == n_linhas - 2)
                animal_caindo[id_animal] = false;
        }
    }
}

void inimigo_ar_move() { 
    for (int i = 0; i < MAX_INIMIGOS_AR; i++) {
        if (inimigo_ar_existe[i] == true)
            inimigo_ar_x[i]--;
        if (inimigo_ar_x[i] == -3)
            inimigo_ar_existe[i] = false;
    }
}

void inimigo_terra_move() 
{
    for(int i = 0; i < MAX_INIMIGOS_TERRA; i++)
    {
        if(inimigo_terra_existe[i] == true)
            inimigo_terra_x[i]--;
        if(inimigo_terra_x[i] == -11)
            inimigo_terra_existe[i] =false;
    }
}

void cria_inimigo_ar(int y, int x) 
{
    for(int i = 0; i < MAX_INIMIGOS_AR; i++)
    {
        if(inimigo_ar_existe[i] == false)
        {
            inimigo_ar_existe[i] = true;
            inimigo_ar_x[i] = x;
            inimigo_ar_y[i] = y;
            break;
        }
    }
}

void cria_inimigo_terra(int n_inimigos) 
{
    for(int i = 0; i < MAX_INIMIGOS_TERRA; i++) {
        if(inimigo_terra_existe[i] == false)
        {
            if(n_inimigos >= 1)
            {
                inimigo_terra_existe[i] = true;
                inimigo_terra_x[i] = n_colunas -1;
            }
            if(n_inimigos >= 2)
            {
                for(int j = 0; j < MAX_INIMIGOS_TERRA; j++) {
                    if(inimigo_terra_existe[j] == false) {
                        inimigo_terra_existe[j] = true;
                        inimigo_terra_x[j] = n_colunas +11;
                        break;
                    }
                }
            }
            if(n_inimigos == 3) {
                for(int j = 0; j < MAX_INIMIGOS_TERRA; j++) {
                    if (inimigo_terra_existe[j] == false) {
                        inimigo_terra_existe[j] = true;
                        inimigo_terra_x[j] = n_colunas + 23;
                        break;
                    }
                }
            }

            break;
        }
    }
}

void aleatoriza_inimigo()
{
    int aleatorio;

    srand(time(NULL));

    if(level == 1)
    {
        if( (rand() % 100) < 65) 
        {
            aleatorio = rand() % 100;

            if(aleatorio < 30)
            {
                cria_inimigo_ar(n_linhas - 3, n_colunas - 1);
            }
            else if(aleatorio < 50)
            {
                cria_inimigo_ar(n_linhas - 5, n_colunas - 1);
            }
            else if(aleatorio < 70)
            {
                cria_inimigo_ar(n_linhas - 7, n_colunas - 1);
            }
            else if(aleatorio < 85)
            {
                cria_inimigo_ar(n_linhas - 9, n_colunas - 1);
            }
            else
            {
                cria_inimigo_ar(n_linhas - 15, n_colunas - 1);
            }

        }
    }

    if(level == 2)
    {
        if( (rand() % 100) < 80) 
        {
            aleatorio = rand() % 100;

            if (aleatorio < 20) {
                cria_inimigo_ar(n_linhas - 3, n_colunas - 1);
            } else if (aleatorio < 40) {
                cria_inimigo_ar(n_linhas - 5, n_colunas - 1);
            } else if (aleatorio < 60) {
                cria_inimigo_ar(n_linhas - 7, n_colunas - 1);
            } else if (aleatorio < 70) {
                cria_inimigo_ar(n_linhas - 9, n_colunas - 1);
            } else if (aleatorio < 85) {
                cria_inimigo_ar(n_linhas - 3, n_colunas - 1);
                cria_inimigo_ar(n_linhas - 15, n_colunas + 20);
            } else {
                cria_inimigo_ar(n_linhas - 15, n_colunas - 1);
                cria_inimigo_ar(n_linhas - 3, n_colunas + 20);
            }

        }
    }

    if(level == 3) {
        if ((rand() % 100) < 80) 
        {
            aleatorio = rand() % 100;

            if (aleatorio < 10) {
                cria_inimigo_ar(n_linhas - 3, n_colunas - 1);
            } else if (aleatorio < 20) {
                cria_inimigo_ar(n_linhas - 5, n_colunas - 1);
            } else if (aleatorio < 30) {
                cria_inimigo_ar(n_linhas - 7, n_colunas - 1);
            } else if (aleatorio < 40) {
                cria_inimigo_ar(n_linhas - 9, n_colunas - 1);
            } else if (aleatorio < 50) {
                cria_inimigo_ar(n_linhas - 3, n_colunas - 1);
                cria_inimigo_ar(n_linhas - 15, n_colunas + 20);
            } else if (aleatorio < 60) {
                cria_inimigo_ar(n_linhas - 15, n_colunas - 1);
                cria_inimigo_ar(n_linhas - 3, n_colunas + 20);
            } else if (aleatorio < 85) {
                cria_inimigo_terra(1);
            } else
                cria_inimigo_terra(2);
        }
    }
    if(level == 4)
    {
        aleatorio = rand() % 100;
        if (aleatorio < 10) {
            cria_inimigo_ar(n_linhas - 3, n_colunas - 1);
        } else if (aleatorio < 20) {
            cria_inimigo_ar(n_linhas - 5, n_colunas - 1);
        } else if (aleatorio < 30) {
            cria_inimigo_ar(n_linhas - 7, n_colunas - 1);
        } else if (aleatorio < 40) {
            cria_inimigo_ar(n_linhas - 3, n_colunas - 1);
            cria_inimigo_ar(n_linhas - 15, n_colunas + 20);
            cria_inimigo_ar(n_linhas - 3, n_colunas + 40);
        } else if (aleatorio < 50) {
            cria_inimigo_ar(n_linhas - 3, n_colunas - 1);
            cria_inimigo_ar(n_linhas - 15, n_colunas + 20);
        } else if(aleatorio < 60){
            cria_inimigo_ar(n_linhas - 15, n_colunas - 1);
            cria_inimigo_ar(n_linhas - 3, n_colunas + 20);
        } else if(aleatorio < 80){
            cria_inimigo_terra(2);
        } else {
            cria_inimigo_terra(3);
        }

    }
}

void atualiza_mapa()
{
    clear();
    coloca_todos_animais();
    coloca_todos_inimigos();
    coloca_mapa();
    refresh();
}

void desenha_menu(int opcao_selecionada)
{
    clear();
    box(stdscr,0,0);
    mvprintw(8,24, " ###############   #################   #################");
    mvprintw(9,24, "################   #################   #################");
    mvprintw(10,24,"################   #################   #################");
    mvprintw(11,24,"######                   #####               #####");
    mvprintw(12,24,"######                   #####               #####");
    mvprintw(13,24,"######                   #####               #####   ###    ###   ##        ##   #########");
    mvprintw(14,24,"######                   #####               #####   ###    ###   ###      ###   ##########");
    mvprintw(15,24,"######                   #####               #####   ###    ###   ####    ####   ###    ###");
    mvprintw(16,24,"################         #####         ###########   ###    ###   ############   ###    ###");
    mvprintw(17,24,"################         #####         ###########   ##########   ###  ##  ###   ##########"       );
    mvprintw(18,24," ###############         #####         ##########     ########    ###      ###   ######### "       );
    mvprintw(19,105,                                                                                "###");
    mvprintw(20,105,                                                                                "###");
    mvprintw(21,105,                                                                                "###");

    mvprintw(23,68,"PLAY");
    mvprintw(25,64,"INSTRUCTIONS");
    mvprintw(27,65,"HIGHSCORES");
    mvprintw(29,68,"EXIT");

    if(opcao_selecionada == 1)
        mvprintw(23,65,"->");
    else if(opcao_selecionada == 2)
        mvprintw(25,61,"->");
    else if(opcao_selecionada == 3)
        mvprintw(27,62,"->");
    else if(opcao_selecionada == 4)
        mvprintw(29,65,"->");

    mvprintw(32,3,"UP/DOWN ARROW - Move menu");
    mvprintw(33,3,"ENTER         - Select tab");


}

void desenha_recorde()
{
    clear();
    box(stdscr,0,0);
    mvprintw(16,65,"HIGHSCORE");
    mvprintw(18,67,"%05d",highscore);
    mvprintw(33,90,"(Press any button to return to the main menu...)");
    getch();
    audio(40);
}

void desenha_instrucoes()
{
    clear();
    box(stdscr,0,0);
    mvprintw(3,5, "Jump for your life!!!");
    mvprintw(5,5, "The animals are running and need to survive the obstacles. Avoid them to live. Jump them to earn points.");
    mvprintw(6,5, "Each animal gains different points. As your score gets higher, the level goes up, and the game gets harder.");
    mvprintw(7,5, "If all the animals die, you lose. GOOD LUCK!");
    mvprintw(10,5, "Each arrow jumped gives:              Each fence jumped gives:");
    mvprintw(12,5," -8pts with the COW                      -16pts with the COW");
    mvprintw(13,5," -5pts with the PIG                      -10pts with the PIG");
    mvprintw(14,5," -2pts with the CHICKEN                  -04pts with the CHICKEN");

    mvprintw(18,5,"Score > 0  : Level 1");
    mvprintw(19,5,"Score > 75 : Level 2");
    mvprintw(20,5,"Score > 200: Level 3");
    mvprintw(21,5,"Score > 500: Level HELL (Good luck on this one)");
   
 mvprintw(25,5,"CONTROLS:");
    mvprintw(27,5," Q - COW JUMP");
    mvprintw(28,5," W - PIG JUMP");
    mvprintw(29,5," E - CHICKEN JUMP");
    mvprintw(31,5," P - PAUSE GAME");
    mvprintw(32,5," BACKSPACE - END GAME ( Brutally murder all the animals D= )");
    mvprintw(33,90,"(Press any button to return to the main menu...)");

    refresh();
    getch();
    audio(40);
}

void game_over()
{
    nodelay(stdscr,false);
    clear();
    box(stdscr,0,0);

    mvprintw(16,50,"THE ANIMALS ARE ALL DEAD... GAME OVER...");
    if(highscore < score) {
        highscore = score;
        mvprintw(20,62,"NEW HIGHSCORE!!");
    }else
        mvprintw(20,67,"Score");

    mvprintw(21,67,"%05d",score);

    mvprintw(33,90,"(Press any button to return to the main menu...)");


    refresh();
    getch();
    audio(40);

}

void inicia_jogo()
{

    nodelay(stdscr,true);

    score = 0;
    level = 1;
    for(int i = 0; i < 3; i++)
    {
        animais_y[i] = n_linhas -2;
        animal_vivo[i] = true;
        animal_pulando[i] = false;
        animal_caindo[i] = false;
    }

    for(int i = 0; i < MAX_INIMIGOS_AR; i++)
    {
        inimigo_ar_existe[i] = false;
    }

    for(int i = 0; i < MAX_INIMIGOS_TERRA; i++)
    {
        inimigo_terra_existe[i] = false;
    }

    game_is_lost = false;

    clear();
    coloca_mapa();
    refresh();
    
    sleep(1);
   
    coloca_animal(VACA);
    mvprintw(10,n_colunas/2,"3");
    refresh();
    audio(3);

    sleep(1);
    coloca_animal(PORCO);
    mvprintw(10,n_colunas/2,"2");
    refresh();
    audio(2);

    sleep(1);
    coloca_animal(GALINHA);
    mvprintw(10,n_colunas/2,"1");
    refresh();
    audio(1);
    
    sleep(1);
    mvprintw(10,n_colunas/2 - 2,"GO!!!");
    refresh();

    sleep(1);

}

void pausa_jogo()
{
    mvprintw(20,87,"PAUSED");
    refresh();
    nodelay(stdscr,false);
    while(1)
    {
        int c = getch();
        if(c == 80 || c == 112)
            break;
    }
    nodelay(stdscr,true);
}

void detecta_tecla_apertada()
{
    int c = getch();

    if(c == 113 || c == 81)
    {
        if(animal_pulando[VACA] == false && animal_caindo[VACA] == false)
            animal_pulando[VACA] = true;
    }
    else if(c == 119 || c == 87)
    {
        if(animal_pulando[PORCO] == false && animal_caindo[PORCO] == false)
            animal_pulando[PORCO] = true;
    }
    else if(c == 101 || c == 69) {
        if (animal_pulando[GALINHA] == false && animal_caindo[GALINHA] == false)
            animal_pulando[GALINHA] = true;
    }
    else if(c == 80 || c == 112)
        pausa_jogo();

    else if(c == KEY_BACKSPACE)
    {
        animal_vivo[VACA]    = false;
        animal_vivo[PORCO]   = false;
        animal_vivo[GALINHA] = false;
	audio(5);
    }



}

void verifica_estado_jogo()  //auxilio Paulo
{
    for(int i = 0; i < MAX_INIMIGOS_AR; i++) {

        if(animal_vivo[VACA] == true && inimigo_ar_existe[i] == true && inimigo_ar_x[i] <= animais_x[VACA] +16) {

            if ((inimigo_ar_x[i] >= animais_x[VACA] - 2 && inimigo_ar_x[i] <= animais_x[VACA] + 12 &&
            inimigo_ar_y[i] <= animais_y[VACA] && inimigo_ar_y[i] >= animais_y[VACA] - 4) || (inimigo_ar_y[i] == animais_y[VACA] - 5 &&
            inimigo_ar_x[i] >= animais_x[VACA] + 8 && inimigo_ar_x[i] <= animais_x[VACA] +15) || (inimigo_ar_y[i] == animais_y[VACA] - 4 &&
            inimigo_ar_x[i] >= animais_x[VACA] + 8 && inimigo_ar_x[i] <= animais_x[VACA] +16) || ((inimigo_ar_y[i] == animais_x[VACA] + 3 || inimigo_ar_y[i] == animais_x[VACA] + 4) &&
            inimigo_ar_x[i] == animais_x[VACA] + 13)) {

                animal_vivo[VACA] = false;
                inimigo_ar_existe[i] = false;
		audio(30);
            }

            else if(inimigo_ar_x[i] == animais_x[VACA] -4 && animais_y[VACA] < inimigo_ar_y[i]) {
                score += 8;
		audio(0);
	    }
        }

        if(animal_vivo[PORCO] == true && inimigo_ar_existe[i] == true && inimigo_ar_x[i] <= animais_x[PORCO] +11) {

            if((inimigo_ar_y[i] <= animais_y[PORCO] && inimigo_ar_y[i] >= animais_y[PORCO] -2 && inimigo_ar_x[i] <= animais_x[PORCO] +9 && inimigo_ar_x[i] >= animais_x[PORCO] -2) ||
            ( (inimigo_ar_y[i] == animais_y[PORCO] - 2  || inimigo_ar_y[i] == animais_y[PORCO] - 3) && inimigo_ar_x[i] <= animais_x[PORCO] +11 && inimigo_ar_x[i] >= animais_x[PORCO] +4)) {

                animal_vivo[PORCO] = false;
                inimigo_ar_existe[i] = false;
		audio(20);
            }

            else if(inimigo_ar_x[i] == animais_x[PORCO] -4 && animais_y[PORCO] < inimigo_ar_y[i]) {
                score += 5;
		audio(0);
	    }
        }

        if(animal_vivo[GALINHA] == true && inimigo_ar_existe[i] == true && inimigo_ar_x[i] <= animais_x[GALINHA] +4) {

            if( ( (inimigo_ar_y[i] == animais_y[GALINHA] || inimigo_ar_y[i] == animais_y[GALINHA] -1) && inimigo_ar_x[i] <= animais_x[GALINHA] +4 && inimigo_ar_x[i] >= animais_x[GALINHA] -3) ||
            (inimigo_ar_y[i] == animais_y[GALINHA] - 2 && inimigo_ar_x[i] >= animais_x[GALINHA] -1 && inimigo_ar_x[i] <= animais_x[GALINHA] +4) ) {

                animal_vivo[GALINHA] = false;
                inimigo_ar_existe[i] = false;
		audio(10);
            }

            else if(inimigo_ar_x[i] == animais_x[GALINHA] -4 && animais_y[GALINHA] < inimigo_ar_y[i]) {
                score += 2;
		audio(0);
	    }
        }
    }


    for(int i = 0; i < MAX_INIMIGOS_TERRA; i++)
    {
        if(animal_vivo[VACA] == true && inimigo_terra_existe[i] == true && inimigo_terra_x[i] <= animais_x[VACA] +16)
        {
            if( (animais_y[VACA] >= inimigo_terra_y -4 && animais_x[VACA] +2 <= inimigo_terra_x[i] +8 && animais_x[VACA] +12 >= inimigo_terra_x[i] +3) ||
            (animais_y[VACA] -3 >= inimigo_terra_y -4 && animais_x[VACA] +11 <= inimigo_terra_x[i] +8 && animais_x[VACA] +16 >= inimigo_terra_x[i] +3) ) {

                animal_vivo[VACA] = false;
                inimigo_terra_existe[i] = false;
		audio(30);
            }

            else if(animais_x[VACA] == inimigo_terra_x[i] +9){
                score += 16;
		audio(0);
	    }
        }

        if(animal_vivo[PORCO] == true && inimigo_terra_existe[i] == true && inimigo_terra_x[i] <= animais_x[PORCO] +11)
        {
            if( (animais_y[PORCO] >= inimigo_terra_y -4 && animais_x[PORCO] +1 <= inimigo_terra_x[i] +8 && animais_x[PORCO] +9 >= inimigo_terra_x[i] +3) ||
                (animais_y[PORCO] -2 >= inimigo_terra_y -4 && animais_x[PORCO] +7 <= inimigo_terra_x[i] +8 && animais_x[PORCO] +11 >= inimigo_terra_x[i] +3) ) {

                animal_vivo[PORCO] = false;
                inimigo_terra_existe[i] = false;
		audio(20);
            }

            else if(animais_x[PORCO] == inimigo_terra_x[i] +9) {
                score += 10;
		audio(0);
	    }
        }

        if(animal_vivo[GALINHA] == true && inimigo_terra_existe[i] == true && inimigo_terra_x[i] <= animais_x[GALINHA] +4)
        {
            if(animais_y[GALINHA] >= inimigo_terra_y -4 && animais_x[GALINHA] <= inimigo_terra_x[i] +8 && animais_x[GALINHA] +4 >= inimigo_terra_x[i] +3){

                animal_vivo[GALINHA] = false;
                inimigo_terra_existe[i] = false;
		audio(10);
            }

            else if(animais_x[GALINHA] == inimigo_terra_x[i] +9) {
                score += 4;
		audio(0);
	    }
        }

    }

    if(animal_vivo[VACA] == false && animal_vivo[PORCO] == false && animal_vivo[GALINHA] == false)
        game_is_lost = true;

    if(score > 500){
        if(level == 3) 
	audio(6);
	level = 4;
    }

    else if(score > 200){
        if(level == 2) 
	audio(6);
	level = 3;
    }
    
    else if(score > 75){
        if(level == 1) 
	audio(6);
	level = 2;
    }

}

void audio(int _audio)  //auxiliado
        int id = fork();
        if(id == 0)
        {
            if(_audio == 1)
                system("aplay -q ../audio/galinha.wav");
            else if(_audio == 10)
                system("aplay -q ../audio/galinha_morre.wav");
            else if(_audio == 2)
                system("aplay -q ../audio/porco.wav");
            else if(_audio == 20)
                system("aplay -q ../audio/porco_morre.wav");
            else if(_audio == 3)
                system("aplay -q ../audio/vaca.wav");
            else if(_audio == 30)
                system("aplay -q ../audio/vaca_morre.wav");
            else if(_audio == 4)
                system("aplay -q ../audio/trocando_menu.wav");
            else if(_audio == 40)
                system("aplay -q ../audio/menu_selected.wav");
            else if(_audio == 5)
                system("aplay -q ../audio/desistir.wav");
            else if(_audio == 6)
                system("aplay -q ../audio/levelup.wav");
	    else if(_audio == 7)
		system("aplay -q ../audio/start.wav");
            else if(_audio == 0)
                system("aplay -q ../audio/points.wav");

            exit(0);
        }
    }



