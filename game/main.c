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

// ------------------------ ESTRUTURAS -----------------------

typedef struct coordenada
{
    int coordenadax;
    int coordenaday;
} COORDENADA;
// -----------------------------------

typedef struct jogador
{
    char* nome[TAMSTRING];
    COORDENADA posicao_xerife;
    int velocidade;
} JOGADOR;
// ----------------------------------

typedef struct bandido
{
    COORDENADA posicao_bandido;
    int na_cadeia;
    int velocidade;
} BANDIDO;
// --------------------------------

typedef struct especial
{
    COORDENADA posicao_especial;
    int status;
    int velocidade;
} ESPECIAL;


// ----------------------------- CHAMADA DOS SUBPROGRAMAS -----------------------

void desenhacenario();
void desenhajogador(JOGADOR xerife);
void desenhabandido (BANDIDO bandido[]);
void desenharochas(COORDENADA rochas[]);
void desenhainfosjogador(JOGADOR xerife, BANDIDO bandido[], int mododejogo);
void resetacor();
void apagaelemento(int x, int y);
void movimentajogador(JOGADOR *xerife, COORDENADA desloc, COORDENADA rochas[]);


// ------------------------------ FUNCAO PRINCIPAL DO JOGO ----------------------

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

    int mododejogo;

    desenhacenario();
    desenhajogador(xerife);
    desenhabandido(bandidos);
    desenharochas(rochas);
    //desenhainfosjogador(xerife, bandidos, mododejogo); // COM PROBLEMAS
    movimentajogador(&xerife, desloc, rochas);





}

// --------------------------------------- CENARIO DO JOGO -------------------------------------------------

void desenhacenario()
{
    int contalinha, contacoluna;

    for (contalinha = 1; contalinha <= LINHA; contalinha++)
    {
        for (contacoluna = 1; contacoluna <= COLUNA; contacoluna++)
            if (contalinha == 1 || contalinha == LINHA)
            {
                textbackground(BLUE);
                putchxy(contacoluna, contalinha, '*');
            }

            else
            {
                textbackground(BLUE);
                putchxy(1, contalinha, '*');
                putchxy(COLUNA, contalinha, '*');
            }
    }
}

// ----------------------------------------------------------------------------------------

void desenhajogador(JOGADOR xerife)
{
    textbackground(YELLOW);
    putchxy(xerife.posicao_xerife.coordenadax, xerife.posicao_xerife.coordenaday, 'X');
}

// ----------------------------------------------------------------------------------------

void desenhabandido(BANDIDO bandido[])
{
    int i;

    for(i=0; i<MAX_BANDIDOS; i++)
    {
        textbackground(GREEN);
        putchxy(bandido[i].posicao_bandido.coordenadax, bandido[i].posicao_bandido.coordenaday, 'B');
    }
}

// ----------------------------------------------------------------------------------------

void desenharochas(COORDENADA rochas[])
{
    int i;
    for (i = 0; i < NUM_ROCHAS; i++)
    {
        textbackground(WHITE);
        putchxy(rochas[i].coordenadax, rochas[i].coordenaday, ' ');
    }
}

void desenhaespeciais(ESPECIAL especial[]) // A FAZER
{

}

// -------------------------------------------------------------------------------------

/* DESENHA INFO JOGADOR
void desenhainfosjogador(JOGADOR xerife, BANDIDO bandido[], int mododejogo) // PROBLEMAS: COMO EU CHAMO O BANDIDO NA FUNCAO
{
    int contador;

    textbackground(BLACK);
    cputsxy(1,LINHA + 1,"Nome: ");
    puts(xerife.nome);


    if (mododejogo == 0)
    {
        cputsxy(20,LINHA + 1,"Modo de jogo: ");
        printf("Facil");
    }

    if (mododejogo == 1)
    {
        cputsxy(20,LINHA + 1,"Modo de jogo: ");
        printf("Dificil");
    }

    cputsxy(47,LINHA + 1,"Cadeia: ");
    for(contador = 0; contador < bandido[contador].na_cadeia; contador++)
    {
        printf("B");
    }

}

*/

// ------------------------ MOVIMENTACAO ------------------------------------------

void resetacor()
{
    textbackground(BLACK);
    textcolor(WHITE);
}
// -----------------------------------------------------------------------------------------------------

void apagaelemento(int x, int y)
{
    resetacor();
    putchxy(x, y, ' ');
}
// -----------------------------------------------------------------------------------------------------

void movimentajogador(JOGADOR *xerife, COORDENADA desloc, COORDENADA rochas[])
{

    apagaelemento((*xerife).posicao_xerife.coordenadax, (*xerife).posicao_xerife.coordenaday);
    (*xerife).posicao_xerife.coordenadax += desloc.coordenadax;
    (*xerife).posicao_xerife.coordenaday += desloc.coordenaday;
    textbackground(YELLOW);
    putchxy((*xerife).posicao_xerife.coordenadax, (*xerife).posicao_xerife.coordenaday, 'X');
}
// ---------------------------------------------------------------------------------------------------
