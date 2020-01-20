#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77

#define ALTURADOMAPA 12
#define LARGURADOMAPA 20

void main() {
    srand(time(NULL));

    int fruta_x = rand()%(LARGURADOMAPA-2) + 1, fruta_y = rand()%(ALTURADOMAPA-2) + 1;
    int obstaculo_x[30], obstaculo_y[30], contadorObstaculo=0;
    int cabeca_x = 1, cabeca_y = 1;
    int corpo_x[100], corpo_y[100];
    int pontuacao=1;
    int velocidade = 500;
    int x, y, i, j;

    char comando = ARROW_RIGHT;//inicia andando para a direita

    COORD inicio = {0,0};
    HANDLE cursor = GetStdHandle (STD_OUTPUT_HANDLE);

    for (;;){
        SetConsoleCursorPosition (cursor, inicio);

        //testa se uma fruta foi pega
        if(cabeca_x==fruta_x && cabeca_y==fruta_y){
            pontuacao++;

            //aumenta a velocidade do jogo
            velocidade-=15;

            // a cada 3 pontos um novo obstaculo aleatorio e criado
            if(pontuacao%3==0){
                contadorObstaculo++;
                obstaculo_x[contadorObstaculo] = rand()%(LARGURADOMAPA-2) + 1;
                obstaculo_y[contadorObstaculo] = rand()%(ALTURADOMAPA-2) + 1;
            }

            //testa se o novo obstaculo não esta em algum ponto do corpo da cobra
            for(i=0;i<=pontuacao;i++){
                if(obstaculo_x[contadorObstaculo]==corpo_x[i] && obstaculo_y[contadorObstaculo]==corpo_y[i]){
                    obstaculo_x[contadorObstaculo] = rand()%(LARGURADOMAPA-2) + 1;
                    obstaculo_y[contadorObstaculo] = rand()%(ALTURADOMAPA-2) + 1;
                    i=-1;
                }
            }

            //cria uma nova posição para a fruta e testa se ela esta em algum obstaculo ou no corpo da cobra
            fruta_x= rand()%(LARGURADOMAPA-2) + 1;
            fruta_y= rand()%(ALTURADOMAPA-2) + 1;

            for(i=0;i<=pontuacao;i++){
                    if((fruta_x==corpo_x[i] && fruta_y==corpo_y[i]) || (fruta_x==cabeca_x && fruta_y==cabeca_y) || (fruta_x==obstaculo_x[i]&&fruta_y==obstaculo_y[i])){
                        fruta_x= rand()%(LARGURADOMAPA-2) + 1;
                        fruta_y= rand()%(ALTURADOMAPA-2) + 1;
                        i=-1;
                    }
            }
        }

        //passa as coordenadas de cada pedaço do corpo da cobra para o que vem depois dele
        for(i=pontuacao;i>0;i--){
            corpo_x[i]= corpo_x[i-1];
            corpo_y[i]= corpo_y[i-1];
        }

        for (y = 0; y < ALTURADOMAPA; y++){
            for (x = 0; x < LARGURADOMAPA; x++){

                //testa se nessas coordenadas tera alguma parte do corpo
                for(i=0;i<=pontuacao;i++){
                    if(x==corpo_x[i] && y==corpo_y[i])
                        break;
                }

                //testa se nessa coordenada tera algum obstaculo
                for(j=0; j<=contadorObstaculo; j++){
                    if(x==obstaculo_x[j]&&y==obstaculo_y[j])
                        break;
                }

                if (x==0 && y==0)
                    printf(" %c", 201, 205);//codigos de caractere para uso do box drowing
                else if (x==0 && y==ALTURADOMAPA-1)
                    printf(" %c", 200, 205);
                else if (x==LARGURADOMAPA-1 && y==0)
                    printf("%c%c", 205, 187);
                else if (x==LARGURADOMAPA-1 && y==ALTURADOMAPA-1)
                    printf("%c%c", 205, 188);
                else if (x==0 || x==LARGURADOMAPA-1)
                    printf(" %c", 186);
                else if (y==0 || y==ALTURADOMAPA-1)
                    printf("%c%c", 205, 205);
                else if (x == cabeca_x && y == cabeca_y)
                    printf(" %c", 184);
                else if (x==corpo_x[i] && y==corpo_y[i])
                     printf(" o");
                else if (x == obstaculo_x[j] && y == obstaculo_y[j])
                    printf(" %c", 254);
                else if (x == fruta_x && y == fruta_y)
                    printf(" %c", 190);
                else
                    printf("  ");
            }
            printf("\n");
        }

        printf("\n");
        printf("Comandos: \nSeta_Cima \t(cima)\nSeta_baixo \t(baixo)\nSeta_Esquerda \t(esquerda)\nSeta_Direita \t(direita)\n");

        //comando que controla a velocidade do jogo e roda o loop infinito ate uma tecla ser apertada e mudar o comando
        Sleep(velocidade);
        if(kbhit()){
            comando = getch();
            if(comando == -32){
                comando = getch();
            }
        }
        switch(comando){
            case ARROW_UP:
                corpo_x[0]=cabeca_x;
                corpo_y[0]=cabeca_y;
                cabeca_y -= 1;
                if (cabeca_y < 1){
                    printf("\nVoce perdeu!\nSua pontuacao foi: %i\n", pontuacao-1);
                    system("PAUSE");
                    exit(1);
                }
                break;

            case ARROW_DOWN:
                corpo_x[0]=cabeca_x;
                corpo_y[0]=cabeca_y;
                cabeca_y += 1;
                if (cabeca_y >= ALTURADOMAPA - 1){
                    printf("\nVoce perdeu!\nSua pontuacao foi: %i\n", pontuacao-1);
                    system("PAUSE");
                    exit(1);
                }
                break;

            case ARROW_LEFT:
                corpo_x[0]=cabeca_x;
                corpo_y[0]=cabeca_y;
                cabeca_x -= 1;
                if (cabeca_x < 1){
                    printf("\nVoce perdeu!\nSua pontuacao foi: %i\n", pontuacao-1);
                    system("PAUSE");
                    exit(1);
                }
                break;

            case ARROW_RIGHT:
                corpo_x[0]=cabeca_x;
                corpo_y[0]=cabeca_y;
                cabeca_x += 1;
                if (cabeca_x >= LARGURADOMAPA - 1){
                    printf("\nVoce perdeu!\nSua pontuacao foi: %i\n", pontuacao-1);
                    system("PAUSE");
                    exit(1);
                }
                break;

            default:
                printf("Comando invalido!\n");
                system("PAUSE");
                system("CLS");
        }

        //testa se alguma parte do corpo da propria cobra foi atingido
        for(i=0;i<=pontuacao;i++){
            if(cabeca_x==corpo_x[i] && cabeca_y==corpo_y[i]){
                printf("\nVoce perdeu!\nSua pontuacao foi: %i\n", pontuacao-1);
                system("PAUSE");
                exit(1);
            }
        }

        //teste se algum obstaculo foi atingido
        for(i=0;i<=contadorObstaculo;i++){
            if(cabeca_x==obstaculo_x[i]&&cabeca_y==obstaculo_y[i]){
                printf("\nVoce perdeu!\nSua pontuacao foi: %i\n", pontuacao-1);
                system("PAUSE");
                exit(1);
            }
        }
    }
}
