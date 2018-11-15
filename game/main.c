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

// CRIAR VARIAVEL LOOP

// posicao_bandidox = 2+ rand() * (LINHA - 2) / RAND_MAX e POSICAO = 2+ rand() * (COLUNA - 2) / RAND_MAX

// ------------------------ ESTRUTURAS -----------------------

typedef struct coordenada
{
    int coordenadax;
    int coordenaday;
} COORDENADA;
// -----------------------------------

typedef struct jogador
{
    char nome[TAMSTRING];
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

// --------------------------------

typedef struct jogo
{
    JOGADOR salvaxerife;
    COORDENADA salvarochas[NUM_ROCHAS];
    ESPECIAL salvaespeciais[MAX_ESPECIAIS];
    BANDIDO salvabandidos[MAX_BANDIDOS];
} JOGO;

// ----------------------------- CHAMADA DOS SUBPROGRAMAS -----------------------

void desenhacenario();
void desenhajogador(JOGADOR xerife);
void desenhabandido (BANDIDO bandido[]);
void desenharochas(COORDENADA rochas[]);
void resetacor();
void apagaelemento(int x, int y);
void movimentajogador(JOGADOR *xerife, COORDENADA desloc, COORDENADA rochas[]);
void desenhainfotempo(clock_t clock_inicial);
void desenhaespeciais(ESPECIAL especial[]);
void desenhainfosjogador(JOGADOR xerife, int bandidosnacadeia, int mododejogo);
void desenhamenu();
int salvajogo(JOGO jogo);
int carregajogo(JOGO *jogo, char nome_jogador[]);

// ------------------------------ FUNCAO PRINCIPAL DO JOGO ----------------------

int main()
{
    // Inicializacao das estruturas

    COORDENADA desloc;
    JOGADOR xerife;
    COORDENADA rochas[NUM_ROCHAS] = {{10, 10}, {20, 20}, {15, 15}};
    BANDIDO bandidos[MAX_BANDIDOS] = {{5, 5}, {16,21}, {12, 17}};
    ESPECIAL especiais[MAX_ESPECIAIS] = {{3,3}, {11,12}, {3,6}, {6,7}, {8,9}};
    JOGO jogo;

    // Inicializacao das variaveis
    clock_t clock_inicial;

    // Posicao inicial do xerife no jogo
    xerife.posicao_xerife.coordenadax = 30;
    xerife.posicao_xerife.coordenaday = 13;

    int mododejogo;
    int parar = 0;
    int bandidosnacadeia = 0;
    int opcao;

    desenhamenu();
    printf("\n\n");
    scanf("%d", &opcao);

    switch(opcao)
    {
    case 1:
    {
        clrscr();
        printf("Insira o nome do jogador: ");
        scanf("%s", xerife.nome);
        printf("\n");
        printf("Insira o modo de jogo: 0 - Facil, 1 - Dificil: ");
        scanf("%d", &mododejogo);
        printf("\n");
        clrscr();
        desenhacenario();
        desenhajogador(xerife);
        desenharochas(rochas);
        desenhabandido(bandidos);
        desenhaespeciais(especiais);
        desenhainfosjogador(xerife, bandidosnacadeia, mododejogo);
        clock_inicial = clock();
    }
    break;

    case 2:
    {

    }
    break;

    case 3:
    {

    }
    break;

    case 4:
    {

    }
    break;

    case 5:
    {

    }
    break;

    case 6:
    {

    }
    break;

    default:
    {
        printf("\nOpcao invalida!");
    }

    }

    // ----------------------------------- Laco principal -------------------------------------------

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

int salvajogo(JOGO jogo) // A FAZER
{
    FILE *arq;
    JOGADOR xerife;

    if(arq = fopen("game.dat", "ab"))
    {
        if (!strcmp(jogo.salvaxerife.nome, xerife.nome))
        {
            fwrite(&xerife, sizeof(JOGADOR), 1, arq);
            return 1;

            // ESCREVER DADOS NO JOGO
        }

        else
        {
            fwrite(&jogo, sizeof(JOGO), 1, arq);
            return 1;
        }
    }

    else
    {
        printf("\nErro na abertura do arquivo");
        return 0;
    }

    fclose(arq);
}

int carregajogo(JOGO *jogo, char nome_jogador[]) // A FAZER
{
    FILE *arq;
    JOGADOR xerife;
    int achou = 0;

    printf("Insira um nome para ser buscado: ");
    scanf("%s", nome_jogador);

    if(arq = fopen("game.dat", "rb"))
    {
        while(!feof(arq) && achou != 1)
        {
            fread(&jogo, sizeof(JOGO), 1, arq);

            if(!strcmp(nome_jogador, xerife.nome))
            {
                // TODOS OS VALORES RECEBERÃO OS QUE ESTÃO NOS DO JOGO
                return 1;
            }

            else
            {
                printf("\nNome nao encontrado!\n");
            }
        }


    }

    else
    {
        printf("\nErro na abertura do arquivo");
    }

    fclose(arq);
}

// -------------------------------------------------- MENU ---------------------------------------------------------------------

void desenhamenu() // A FAZER
{
    printf("Bandit Hunter \n\n");
    printf("1 - Novo Jogo: Facil \n\n");
    printf("2 - Novo Jogo: Modo Corrupcao Brasil \n\n");
    printf("3 - Carregar Partida \n\n");
    printf("4 - Ajuda \n\n");
    printf("5 - Ranking \n\n");
    printf("6 - Sair \n\n");
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
    for (i = 0; i < MAX_BANDIDOS; i++)
    {
        textbackground(RED);
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
        putchxy(rochas[i].coordenadax, rochas[i].coordenaday, 'R');
    }
}
// --------------------------------------------------------------------------------------------

void desenhaespeciais(ESPECIAL especial[])
{
    int i;
    for (i = 0; i < MAX_BANDIDOS; i++)
    {
        textbackground(BLUE);
        putchxy(especial[i].posicao_especial.coordenadax, especial[i].posicao_especial.coordenaday, 'E');
    }
}

// -------------------------------------------------------------------------------------

void desenhainfosjogador(JOGADOR xerife, int bandidosnacadeia, int mododejogo)
{
    int contador;

    textbackground(BLACK);
    cputsxy(1,LINHA + 1,"Nome: ");
    printf("%s", xerife.nome);


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

void desenhainfotempo(clock_t clock_inicial)
{
    int segundos, minutos;

    clock_t clock_atual = clock();

    segundos = (clock_atual - clock_inicial) / CLOCKS_PER_SEC;

    minutos = segundos/ 60;

    segundos = segundos%60;
    textbackground(GREEN);
    gotoxy(65, LINHA+1);
    printf("%02d : %02d", 2 - minutos, 59 - segundos);

}


// ------------------------ MOVIMENTACAO ---------------------------------------------------------------------------------------

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

/*
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
*/

// --------------------------------------------------------------------------------------------------------

int testacolisaojogador(JOGADOR *xerife, COORDENADA desloc, COORDENADA rochas[])
{
    int i;
    int colidiu = 0;

    for (i = 0; i < NUM_ROCHAS; i++)
    {
        if (((*xerife).posicao_xerife.coordenadax + desloc.coordenadax == rochas[i].coordenadax) && ((*xerife).posicao_xerife.coordenadax + desloc.coordenaday == rochas[i].coordenadax))
        {

            colidiu = 1;

        }

    }

    return colidiu;
}

// ----------------------------------------------------------------------------------------------
int testacolisaobandido(BANDIDO *bandido[], COORDENADA desloc, COORDENADA rochas[]) // A FAZER
{

}

// -------------------------------------------------------------------------------------------------------

int testacapturaespecial(JOGADOR xerife, ESPECIAL especial[]) // A FAZER
{

}

// -------------------------------------- ESPECIAIS --------------------------------------------------------------------------------

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
