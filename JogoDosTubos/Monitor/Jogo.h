#pragma once
typedef struct JOGODOSTUBOS {
	TCHAR tab[20][20];
	int altura, largura, tempo_agua;
	int stop,ganhou;
}JOGO;

typedef struct {
	JOGO jogo;
	int in, out;
	int nmonitores, nservidores;
}Memoria;