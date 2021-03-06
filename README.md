# Bandit-Hunting

/* ESQUELETO DO JOGO XERIFE - ALGORITMOS E PROGRAMAÇÃO 2018/2 */



///// INICIALIZAÇÃO /////

> mostrar tela inicial (nomes dos alunos, disciplina e semestre) e pedir nome do jogador
> exibir menu principal, com as seguintes opções:
	* NOVO JOGO MODO FÁCIL
	* NOVO JOGO MODO DIFÍCIL
	* CARREGAR PARTIDA
	* AJUDA
	* RANKING
	* SAIR



///// ALGORITMO DO JOGO /////

> registrar o tempo inicial
> instanciar estruturas de dados dos elementos do jogo:
	* jogador
	* cadeia
	* bandidos
	* especiais
	* rochas
> imprimir informações na barra inferior (nome, modo de jogo, cadeia, especiais, tempo)
> desenhar borda da tela e elementos do jogo
> laço do jogo:
	> atualizar tempo (decrescente)
	> atualizar informações na barra inferior
	> testar captura de bandido
	> testar aparecimento e coleta de especiais
	> movimentar jogador (testar colisão com bordas e rochas)
	> movimentar bandidos
	> testar PAUSA, VITÓRIA e DERROTA
	até PAUSA ou VITÓRIA ou DERROTA
> se PAUSA
	> salvar estruturas de dados num arquivo binário
> senão se VITÓRIA
	> registrar tempo final (pontuação do jogador)
	> carregar arquivo de highscores
	> inserir pontuação no arquivo
	> ordenar arquivo de highscores
	> exibir lista de highscores em ordem decrescente com mensagem de parabéns
> senão (se DERROTA)
	> exibir mensagem de solidariedade
> voltar para o menu principal



///// ESTRUTURAS DE DADOS /////

Tipo COORDENADA
	X inteiro
	Y inteiro

Tipo JOGADOR
	Nome 	   string
	Posição    COORDENADA
	Tempo	   inteiro
	Velocidade inteiro
	Simbolo	   caractere (opcional)
	Cor	   COLOR ou inteiro (opcional)

Tipo BANDIDO
	Posição	   COORDENADA
	Status	   booleano
	Velocidade inteiro
	Simbolo	   caractere (opcional)
	Cor	   COLOR ou inteiro (opcional)

Bandidos: arranjo[MAX_BANDIDOS] BANDIDO

Cadeia: arranjo[MAX_BANDIDOS] caractere

Tipo ESPECIAL
	Poder	inteiro
	Posição	COORDENADA

Especiais: arranjo[5] ESPECIAL

Rochas: arranjo[NUM_ROCHAS] COORDENADA
