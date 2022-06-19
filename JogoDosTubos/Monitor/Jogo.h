#pragma once

#define PARAR_AGUA 1
#define INSERIR_PAREDE 2
#define MODO_ALEATORIO 3
#define OFF 4
#define START 5
#define MONITOR_TO_SERVIDOR_START_MUTEX _T("MONITOR_TO_SERVIDOR_START_MUTEX")
#define MONITOR_TO_SERVIDOR_ESCREVER_MUTEX _T("MONITOR_TO_SERVIDOR_ESCREVER_MUTEX")
#define MONITOR_TO_SERVIDOR_LER_MUTEX _T("MONITOR_TO_SERVIDOR_LER_MUTEX")
#define MONITOR_TO_SERVIDOR_ESCREVER_SEMAFORO _T("MONITOR_TO_SERVIDOR_ESCREVER_SEMAFORO")
#define MONITOR_TO_SERVIDOR_LER_SEMAFORO _T("MONITOR_TO_SERVIDOR_LER_SEMAFORO")
#define MONITOR_TO_SERVIDOR_MAP _T("MONITOR_TO_SERVIDOR_MAP")


typedef struct JOGODOSTUBOS {
	TCHAR tab[20][20];
	int altura, largura, tempo_agua;
	int stop, ganhou;
}JOGO;

typedef struct COMUNICAÇÂO {
	int posx, posy;
	TCHAR c;
}CLITOSERV;

typedef struct {
	JOGO jogo;
	//char comando[100];
	//int in, out;
	//int nmonitores, nservidores;
}Memoria;

typedef struct {
	int comando[10];
	int proxRead;
	int proxwrite;
	int maxPos;
}MonToSer;