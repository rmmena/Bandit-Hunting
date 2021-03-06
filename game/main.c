#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define LINHA 24
#define COLUNA 80
#define TAMSTRING 10
#define NUM_ROCHAS 15
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

// --------------- MENU --------------------------------------

void desenhamenu_ajuda();
void desenhamenu();

// -------------- CEN�RIO ------------------------------------

void desenhacenario();
void desenhajogador(JOGADOR xerife);
void desenhabandido (BANDIDO bandido[], int num_bandidos);
void desenharochas(COORDENADA rochas[], int num_rochas);
void resetacor();
void apagaelemento(int x, int y);
void desenhainfotempo(clock_t clock_inicial);
void desenhainfosjogador(JOGADOR xerife, int bandidosnacadeia, int mododejogo);

// ---------------------- JOGADOR ------------------------------

void movimentajogador(JOGADOR *xerife, COORDENADA desloc);
int testacolisaojogador(JOGADOR xerife, COORDENADA desloc, COORDENADA rochas[], int max_rochas);



// -------------------- BANDIDOS ------------------------------

void movimentaumbandido(BANDIDO *bandido, COORDENADA desloc, int direcao);
void movimentabandidos(BANDIDO bandido[], COORDENADA desloc, COORDENADA rochas[], int numrochas, int numbandidos);
int testacolisaobandido(BANDIDO bandido[], COORDENADA desloc, COORDENADA rochas[], int max_rochas, int max_bandidos);

// --------------------- FUNCOES DE ARQUIVO -----------------------------

void inicializa_rochas(COORDENADA rochas[], int* num_rochas, int max_rochas);
void inicializa_bandidos(BANDIDO bandido[], int* num_bandidos, int max_bandidos);


int salvajogo(JOGO jogo);
int carregajogo(JOGO *jogo, char nome_jogador[]);


// ------------------------------ FUNCAO PRINCIPAL DO JOGO ----------------------

int main()
{
    // Inicializacao das variaveis
    clock_t clock_inicial;
    int mododejogo;
    int parar = 0;
    int bandidosnacadeia = 0;
    int opcao;
    int maxrochas = 30;
    int numrochas = 0;
    int maxbandidos = 10;
    int numbandidos = 0;


    // Inicializacao das estruturas

    COORDENADA desloc;
    JOGADOR xerife;
    COORDENADA rochas[maxrochas];
    BANDIDO bandidos[maxbandidos];
    ESPECIAL especiais[MAX_ESPECIAIS];
    JOGO jogo;

    // Posicao inicial do xerife no jogo
    xerife.posicao_xerife.coordenadax = 30;
    xerife.posicao_xerife.coordenaday = 13;


    desenhamenu();

    while (opcao < 1 || opcao > 6)
    {
        scanf("%d", &opcao);
    }


    switch(opcao)
    {
    case 1:
    {
        maxbandidos = 5;
        maxrochas = 15;
        clrscr();
        mododejogo = 0;
        printf("Insira o nome do jogador: ");
        scanf("%s", xerife.nome);
        printf("\n");
        printf("\n");
        clrscr();
        desenhacenario();
        desenhajogador(xerife);
        inicializa_rochas(rochas, &numrochas, maxrochas);
        desenharochas(rochas, numrochas);
        inicializa_bandidos(bandidos, &numbandidos, maxbandidos);
        desenhabandido(bandidos, numbandidos);
        desenhainfosjogador(xerife, bandidosnacadeia, mododejogo);
        clock_inicial = clock();
    }
    break;

    case 2:
    {
        clrscr();
        mododejogo = 1;
        printf("Insira o nome do jogador: ");
        scanf("%s", xerife.nome);
        printf("\n");
        printf("\n");
        clrscr();
        desenhacenario();
        desenhajogador(xerife);
        inicializa_rochas(rochas, &numrochas, maxrochas);
        desenharochas(rochas, numrochas);
        inicializa_bandidos(bandidos, &numbandidos, maxbandidos);
        desenhabandido(bandidos, numbandidos);
        desenhainfosjogador(xerife, bandidosnacadeia, mododejogo);
        clock_inicial = clock();
    }
    break;

    case 3:
    {
        clrscr();
    }
    break;

    case 4:
    {
        clrscr();
        clrscr();
        desenhamenu_ajuda();
        scanf("%d", &opcao);
        if (opcao == 7 )
        {
            clrscr();
            clrscr();
            desenhamenu();

            while (opcao < 1 || opcao > 6)
            {
                scanf("%d", &opcao);
            }

            //inicia jogo()
        }

    }
    break;

    case 5:
    {
        clrscr();
    }
    break;

    case 6:
    {
        printf("\n\nEspero voce em breve para deter a corrupcao! Ate logo!\n\n");
        parar = 1;
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
        desloc.coordenadax = 0;
        desloc.coordenaday = 0;

        movimentabandidos(bandidos, desloc, rochas, maxrochas, maxbandidos);

        if (GetKeyState (VK_RIGHT) & 0x80) // Seta para direita pressionada
        {
            if (xerife.posicao_xerife.coordenadax + 1 < COLUNA)
            {
                desloc.coordenadax = 1;
                desloc.coordenaday = 0;
                if (!testacolisaojogador(xerife, desloc, rochas, maxrochas))
                {
                    movimentajogador(&xerife, desloc);
                }

            }

        }

        if (GetKeyState (VK_LEFT) & 0x80) // Seta para esquerda pressionada
        {

            if(xerife.posicao_xerife.coordenadax - 1 > 1)
            {
                desloc.coordenadax = -1;
                desloc.coordenaday = 0;

                if (!testacolisaojogador(xerife, desloc, rochas, maxrochas))
                {

                    movimentajogador(&xerife, desloc);
                }


            }
        }

        if (GetKeyState (VK_UP) & 0x80) // Seta para cima pressionada
        {
            if (xerife.posicao_xerife.coordenaday - 1 > 1)
            {
                desloc.coordenadax = 0;
                desloc.coordenaday = -1;
                if (!testacolisaojogador(xerife, desloc, rochas, maxrochas))
                {
                    movimentajogador(&xerife, desloc);
                }


            }

        }

        if (GetKeyState (VK_DOWN) & 0x80) // Seta para baixo pressionada
        {

            if (xerife.posicao_xerife.coordenaday + 1 < LINHA)
            {
                desloc.coordenadax = 0;
                desloc.coordenaday = 1;
                if (!testacolisaojogador(xerife, desloc, rochas, maxrochas))
                {

                    movimentajogador(&xerife, desloc);
                }
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
                // TODOS OS VALORES RECEBER�O OS QUE EST�O NOS DO JOGO
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

// SALVA PONTUACAO E NOME

// CARREGA PONTUACAO E NOME

// DESENHA MENU PAUSA

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

void desenhamenu()
{
    printf("------------------ Bandit Hunter (Versao Beta 2.003.2) ------------------\n\n");
    printf("1 - Novo Jogo: Facil \n\n");
    printf("2 - Novo Jogo: Dificil \n\n");
    printf("3 - Carregar Partida \n\n");
    printf("4 - Ajuda \n\n");
    printf("5 - Ranking \n\n");
    printf("6 - Sair \n\n");
    printf("\n\n Insira sua opcao, aperte a tecla Enter e vamos comecar: ");
}

// -----------------------------------------------------------------------------------------

void desenhamenu_ajuda()
{
    printf("------------------------ Seja bem-vindo ao jogo Bandit Hunter ------------------------------------- \n\n\n");
    printf("Voce e um xerife e deseja capturar os bandidos de sua cidade. Se escolher a dificuldade Facil, serao apenas 5 bandidos, a violencia nao se encerrara!\n\n");
    printf("Porem, se escolher a dificuldade Dificil, tera a oportunidade de prender todos os 10 bandidos que aterrorizam a cidade e acabar com a violencia existente nela, mas haverao mais obstaculos pelo caminho!\n\n");
    printf("Use as setas do teclado para se movimentar pelo cenario. \n\n");
    printf("Voce so conseguira capturar um bandido se pular para o mesmo lugar que ele esta e apertar a tecla espaco.\n\n");
    printf("Nao esqueca que se o cronometro chegar a 0, voce perdeu o jogo e a violencia seguira aterrorizando a cidade!\n\n");
    printf("Tambem existem 5 especiais espalhados pelo mapa que lhe ajudarao ou atrapalharao na sua busca. Porem, como esta e uma versao beta, esse recurso nao esta disponivel, ficara como surpresa para o lancamento oficial, que ainda nao tem data oficial marcada\n\n");
    printf("Vamos comecar essa busca? Digite 7 para voltar ao menu ou 8 para sair do jogo!");
}

// -----------------------------------------------------------------------------------------

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


// --------------------------------------- JOGADOR ---------------------------------------------------------

void desenhajogador(JOGADOR xerife)
{
    textbackground(YELLOW);
    putchxy(xerife.posicao_xerife.coordenadax, xerife.posicao_xerife.coordenaday, 'X');
}

// -------------------------------------------------------------------------------------------------

void movimentajogador(JOGADOR *xerife, COORDENADA desloc)
{

    apagaelemento((*xerife).posicao_xerife.coordenadax, (*xerife).posicao_xerife.coordenaday);
    (*xerife).posicao_xerife.coordenadax += desloc.coordenadax;
    (*xerife).posicao_xerife.coordenaday += desloc.coordenaday;
    textbackground(YELLOW);
    putchxy((*xerife).posicao_xerife.coordenadax, (*xerife).posicao_xerife.coordenaday, 'X');
}

// -------------------------------------------------------------------------------------------------

int testacolisaojogador(JOGADOR xerife, COORDENADA desloc, COORDENADA rochas[], int max_rochas)
{
    int i;
    int colidiu = 0;

    for (i = 0; i < max_rochas; i++)
    {
        if ((xerife.posicao_xerife.coordenadax + desloc.coordenadax == rochas[i].coordenadax) && xerife.posicao_xerife.coordenaday + desloc.coordenaday == rochas[i].coordenaday)
        {

            colidiu = 1;

        }

    }

    return colidiu;
}






// ------------------------------------- ROCHAS -------------------------------------------------------------

void desenharochas(COORDENADA rochas[], int num_rochas)
{
    int i;
    for (i = 0; i < num_rochas; i++)
    {
        textbackground(WHITE);
        putchxy(rochas[i].coordenadax, rochas[i].coordenaday, 'R');
    }
}
// --------------------------------------------------------------------------------

void inicializa_rochas(COORDENADA rochas[], int* num_rochas, int max_rochas)
{
    int contador = 0;

    FILE *arq = fopen("rochas.txt", "r");
    if(arq != NULL)

    {
        while (contador != max_rochas)
        {
            fscanf(arq, "(%d,%d)\n", &(rochas[contador].coordenadax), &(rochas[contador].coordenaday));
            contador++;
        }

    }

    else
    {
        printf("Erro na abertura do arquivo");
    }

    fclose(arq);

    *(num_rochas) = contador;
}



// ------------------------------------- BANDIDO ------------------------------------------------------------

void desenhabandido(BANDIDO bandido[], int num_bandidos)
{
    int i;
    for (i = 0; i < num_bandidos; i++)
    {
        textbackground(RED);
        putchxy(bandido[i].posicao_bandido.coordenadax, bandido[i].posicao_bandido.coordenaday, 'B');
    }
}

// -------------------------------------------------------------------------------

void desenhaumbandido(COORDENADA coordenada, char caractere)
{
    gotoxy(coordenada.coordenadax, coordenada.coordenaday);
    textbackground(RED);
    printf("%c", caractere);
}

// -------------------------------------------------------------------------------

void movimentaumbandido(BANDIDO *bandido, COORDENADA desloc, int direcao)
{
    switch(direcao)
    {
    case 0: //cima
    {
        desloc.coordenaday = -1;

        if(bandido->posicao_bandido.coordenaday + desloc.coordenaday > 1)
        {
            apagaelemento(bandido->posicao_bandido.coordenadax, bandido->posicao_bandido.coordenaday);
            bandido->posicao_bandido.coordenaday = bandido->posicao_bandido.coordenaday-1;
            desenhaumbandido(bandido->posicao_bandido, 'B');
        }

    }
    break;

    case 1: //direita
    {
        desloc.coordenadax = 1;

        if(bandido->posicao_bandido.coordenadax + desloc.coordenadax< COLUNA)
        {
            apagaelemento(bandido->posicao_bandido.coordenadax, bandido->posicao_bandido.coordenaday);
            bandido->posicao_bandido.coordenadax = bandido->posicao_bandido.coordenadax+1;
            desenhaumbandido(bandido->posicao_bandido, 'B');
        }

    }
    break;

    case 2: //esquerda
    {
        if(bandido->posicao_bandido.coordenadax - 1 > 1)
        {
            apagaelemento(bandido->posicao_bandido.coordenadax, bandido->posicao_bandido.coordenaday);
            bandido->posicao_bandido.coordenadax = bandido->posicao_bandido.coordenadax+1;
            desenhaumbandido(bandido->posicao_bandido, 'B');
        }
    }
    break;

    case 3: //baixo
    {
        if(bandido->posicao_bandido.coordenaday + 1 < LINHA)
        {
            apagaelemento(bandido->posicao_bandido.coordenadax, bandido->posicao_bandido.coordenaday);
            bandido->posicao_bandido.coordenaday = bandido->posicao_bandido.coordenaday+1;
            desenhaumbandido(bandido->posicao_bandido, 'B');
        }

    }
    break;

    case 4: //esquerda-cima
    {
        if((bandido->posicao_bandido.coordenadax - 1 > 1) && (bandido->posicao_bandido.coordenaday - 1 > 1))
        {
            apagaelemento(bandido->posicao_bandido.coordenadax, bandido->posicao_bandido.coordenaday);
            bandido->posicao_bandido.coordenadax = bandido->posicao_bandido.coordenadax-1;
            bandido->posicao_bandido.coordenaday = bandido->posicao_bandido.coordenaday-1;
            desenhaumbandido(bandido->posicao_bandido, 'B');
        }

    }
    break;

    case 5: //direita-cima
    {
        if((bandido->posicao_bandido.coordenadax + 1< COLUNA) && (bandido->posicao_bandido.coordenaday - 1 > 1))
        {
            apagaelemento(bandido->posicao_bandido.coordenadax, bandido->posicao_bandido.coordenaday);
            bandido->posicao_bandido.coordenadax = bandido->posicao_bandido.coordenadax+1;
            bandido->posicao_bandido.coordenaday = bandido->posicao_bandido.coordenaday-1;
            desenhaumbandido(bandido->posicao_bandido, 'B');
        }

    }
    break;

    case 6: //esquerda-baixo
    {
        if((bandido->posicao_bandido.coordenadax - 1 > 1) && (bandido->posicao_bandido.coordenaday + 1 < LINHA))
        {
            apagaelemento(bandido->posicao_bandido.coordenadax, bandido->posicao_bandido.coordenaday);
            bandido->posicao_bandido.coordenadax = bandido->posicao_bandido.coordenadax-1;
            bandido->posicao_bandido.coordenaday = bandido->posicao_bandido.coordenaday+1;
            desenhaumbandido(bandido->posicao_bandido, 'B');
        }

    }
    break;

    case 7: //direita-baixo
    {
        if((bandido->posicao_bandido.coordenadax + 1 < COLUNA) && (bandido->posicao_bandido.coordenaday + 1 < LINHA))
        {
            apagaelemento(bandido->posicao_bandido.coordenadax, bandido->posicao_bandido.coordenaday);
            bandido->posicao_bandido.coordenadax = bandido->posicao_bandido.coordenadax+1;
            bandido->posicao_bandido.coordenaday = bandido->posicao_bandido.coordenaday+1;
            desenhaumbandido(bandido->posicao_bandido, 'B');
        }

    }
    break;

    }
}

// --------------------------------------------------------------------------------------

void inicializa_bandidos(BANDIDO bandido[], int* num_bandidos, int max_bandidos)
{
    int contador = 0;

    FILE *arq = fopen("bandidos.txt", "r");
    if(arq != NULL)

    {

        while (contador != max_bandidos)
        {
            fscanf(arq, "(%d,%d)\n", &(bandido[contador].posicao_bandido.coordenadax), &(bandido[contador].posicao_bandido.coordenaday));
            contador++;
        }


    }

    else
    {
        printf("Erro na abertura do arquivo");
    }

    fclose(arq);

    *(num_bandidos) = contador;
}

// ---------------------------------------------------------------------------------

int testacolisaobandido(BANDIDO bandido[], COORDENADA desloc, COORDENADA rochas[], int max_rochas, int max_bandidos)
{
    int i;
    int colidiu = 0;
    int j;

    for (i = 0; i < max_bandidos; i++)
    {
        for(j = 0; j < max_rochas; j++)
        {


            if ((bandido[i].posicao_bandido.coordenadax + desloc.coordenadax == rochas[j].coordenadax) && bandido[i].posicao_bandido.coordenaday + desloc.coordenaday == rochas[j].coordenaday)
            {
                colidiu = 1;
            }
        }
    }

    return colidiu;
}

// ----------------------------------------------------------------------------------------------------------------------

void movimentabandidos(BANDIDO bandido[], COORDENADA desloc, COORDENADA rochas[], int numrochas, int numbandidos)
{
    int i, direcao;

    srand((unsigned)time(NULL));



        for(i = 0; i < numbandidos; i++)
        {

            direcao = (rand() % 8);
            //if(!testacolisaobandido(&bandido[i], desloc, rochas, numbandidos, numrochas))
            movimentaumbandido(&bandido[i], desloc, direcao);
        }


}







// -------------------------------------- FUN��ES GEN�RICAS -------------------------------------------------

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

    else USA UM FOR NO INICIO DA FUNCAO
    {
        desenhabandido((*bandido).posicao_bandido.coordenadax, (*bandido).posicao_bandido.coordenaday);
        (*bandido).na_cadeia = 0;
        return (*bandido).na_cadeia;
    }
}
*/



