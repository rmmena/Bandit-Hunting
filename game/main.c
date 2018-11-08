#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define LINHA 24
#define COLUNA 80
#define TAMSTRING 10
#define NUM_ROCHAS 3
#define MAX_BANDIDOS 3
#define MAX_ESPECIAIS 5

// ESTRUTURAS

typedef struct coordenada
{
    int coordenadax;
    int coordenaday;
} COORDENADA;

typedef struct jogador
{
    char* nome[TAMSTRING];
    COORDENADA posicao_xerife;
    int velocidade;
} JOGADOR;

typedef struct bandido
{
    COORDENADA posicao_bandido;
    int na_cadeia;
    int velocidade;
} BANDIDO;

typedef struct especial
{
    COORDENADA posicao_especial;
    int status;
    int velocidade;
} ESPECIAL;

int main()
{
    // Inicializacao das estruturas

    COORDENADA desloc;
    JOGADOR xerife;
    COORDENADA rochas[NUM_ROCHAS] = {{10, 10}, {20, 20}, {15, 15}};
    BANDIDO bandidos[MAX_BANDIDOS] = {{5, 5}, {16,21}, {12, 17}};
    ESPECIAL especiais[MAX_ESPECIAIS] = {{3,3}, {11,12}, {3,6}, {6,7}, {8,9}};

    // Posicao inicial do xerife no jogo
    xerife.posicao_xerife.coordenadax = 30;
    xerife.posicao_xerife.coordenaday = 13;


}
