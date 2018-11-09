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
void desenhabandido (int bandido_x, int bandido_y);
void desenharochas(COORDENADA rochas[]);
void resetacor();
void apagaelemento(int x, int y);
void movimentajogador(JOGADOR *xerife, COORDENADA desloc, COORDENADA rochas[]);
void desenhainfotempo(clock_t clock_inicial);


// ------------------------------ FUNCAO PRINCIPAL DO JOGO ----------------------

int main()
{
    // Inicializacao das estruturas

    COORDENADA desloc;
    JOGADOR xerife;
    COORDENADA rochas[NUM_ROCHAS] = {{10, 10}, {20, 20}, {15, 15}};
    BANDIDO bandidos[MAX_BANDIDOS] = {{5, 5}, {16,21}, {12, 17}};
    ESPECIAL especiais[MAX_ESPECIAIS] = {{3,3}, {11,12}, {3,6}, {6,7}, {8,9}};

    // Inicializacao das variaveis
    clock_t clock_inicial;

    // Posicao inicial do xerife no jogo
    xerife.posicao_xerife.coordenadax = 30;
    xerife.posicao_xerife.coordenaday = 13;

    int mododejogo;
    clock_inicial = clock();
    int parar = 0;

    desenhacenario();
    desenhajogador(xerife);
    desenharochas(rochas);

    // Laco principal

    while (parar != 1)
    {
        desenhainfotempo(clock_inicial);

        if (GetKeyState (VK_RIGHT) & 0x80) // Seta para direita pressionada
        {
            if (xerife.posicao_xerife.coordenadax + 1 < COLUNA)
            {
                desloc.coordenadax = 1;
                desloc.coordenaday = 0;

                movimentajogador(&xerife, desloc, rochas);
            }

        }

        if (GetKeyState (VK_LEFT) & 0x80) // Seta para esquerda pressionada
        {

            if(xerife.posicao_xerife.coordenadax - 1 > 1)
            {
                desloc.coordenadax = -1;
                desloc.coordenaday = 0;

                movimentajogador(&xerife, desloc, rochas);

            }
        }

        if (GetKeyState (VK_UP) & 0x80) // Seta para cima pressionada
        {
            if (xerife.posicao_xerife.coordenaday - 1 > 1)
            {
                desloc.coordenadax = 0;
                desloc.coordenaday = -1;

                movimentajogador(&xerife, desloc, rochas);

            }

        }

        if (GetKeyState (VK_DOWN) & 0x80) // Seta para baixo pressionada
        {

            if (xerife.posicao_xerife.coordenaday + 1 < LINHA)
            {
                desloc.coordenadax = 0;
                desloc.coordenaday = 1;

                movimentajogador(&xerife, desloc, rochas);

            }

        }

        if (GetKeyState (VK_ESCAPE) & 0x80) // Tecla "ESC" pressionada
        {
            parar = 1;
        }

        Sleep(100);

    }
    return 0;


}

// ------------------------------------- FUNCOES DE ARQUIVO --------------------------------------------------------------------








// -------------------------------------------------- MENU ---------------------------------------------------------------------








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

void desenhabandido (int bandido_x, int bandido_y) // PROBLEMA: FAZER COMO O DESENHA ROCHAS
{
    textbackground(GREEN);
    putchxy(bandido_x, bandido_y, 'B');

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

void desenhainfosjogador(JOGADOR xerife, int bandidosnacadeia, int mododejogo) // PROBLEMA: CHAMAR CORRETAMENTE O NOME DO XERIFE
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
    for(contador = 0; contador < bandidosnacadeia; contador++)
    {
        printf("B");
    }

}
// -------------------------------------------------------------------------------------

void desenhainfotempo(clock_t clock_inicial) // PROBLEMA: a cada vez que o jogador se movimenta a cor de fundo do tempo se modifica e fica igual ao do xerife
{
    int segundos, minutos;

    clock_t clock_atual = clock();

    segundos = (clock_atual - clock_inicial) / CLOCKS_PER_SEC;

    minutos = segundos/ 60;

    segundos = segundos%60;

    gotoxy(65, LINHA+1);
    printf("%02d : %02d", 2 - minutos, 59 - segundos);

}






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

void movimentabandido(BANDIDO *bandido[], COORDENADA desloc, COORDENADA rochas[]) // A FAZER
{

}





// ----------------------- TESTES ------------------------------------------------------------------------------------------------

int testaproximidade(COORDENADA coordA, COORDENADA coordB)
{
    int distancia = sqrt(pow(coordB.coordenadax - coordA.coordenadax, 2) + pow(coordB.coordenaday - coordA.coordenaday, 2));
    int raio;

    if (distancia <= raio)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}
// ------------------------------------------------------------------------------------------------------

int testacaptura(JOGADOR xerife, BANDIDO *bandido, int *bandidos_na_cadeia)
{
    int raio = 2;
    if ((GetKeyState (VK_SPACE) & 0x80 && testaproximidade(xerife.posicao_xerife, (*bandido).posicao_bandido)))
    {
        apagaelemento((*bandido).posicao_bandido.coordenadax, (*bandido).posicao_bandido.coordenaday);
        (*bandido).posicao_bandido.coordenadax == -1;
        (*bandido).posicao_bandido.coordenaday == -1;
        (*bandidos_na_cadeia)++;

        (*bandido).na_cadeia = 1;

        return (*bandido).na_cadeia;
    }

    else
    {
        desenhabandido((*bandido).posicao_bandido.coordenadax, (*bandido).posicao_bandido.coordenaday);
        (*bandido).na_cadeia = 0;
        return (*bandido).na_cadeia;
    }
}
// --------------------------------------------------------------------------------------------------------

int testacolisaojogador(JOGADOR *xerife, COORDENADA desloc, COORDENADA rochas[]) // PROBLEMA: se colocar ela em todas as direcoes de movimento, o jogador fica travado, se colocar em uma so, assim que chegar perto da rocha, ele nao deixa mais se movimentar para aquele lado
{
    int i;
    int colidiu = 0;

    for (i = 0; i < NUM_ROCHAS; i++)
    {
        // Testa Colisao
        if (((*xerife).posicao_xerife.coordenadax + desloc.coordenadax == rochas[i].coordenadax) && ((*xerife).posicao_xerife.coordenadax + desloc.coordenaday == rochas[i].coordenadax))
        {

            colidiu = 1;
            return colidiu;
        }

        else
        {
            colidiu = 0;
            return colidiu;
        }

    }
}

// ----------------------------------------------------------------------------------------------
int testacolisaobandido(BANDIDO *bandido[], COORDENADA desloc, COORDENADA rochas[]) // A FAZER
{

}

// -------------------------------------------------------------------------------------------------------

int testacapturaespecial(JOGADOR xerife, ESPECIAL especial[]) // A FAZER
{

}






// -------------------------------------- ESPECIAIS -------------------------------------------

void alteravelocidade(JOGADOR *xerife, int aceleracao)
{
    (*xerife).velocidade += aceleracao;
}

// --------------------------------------------------------------------------------------------

// FUNÇÃO ESPECIAL 1

// ---------------------------------------------------------------------------------------------

// FUNCÃO ESPECIAL 2

// ---------------------------------------------------------------------------------------------

// FUNCAO ESPECIAL 3
