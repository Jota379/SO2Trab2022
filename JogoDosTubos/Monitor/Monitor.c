#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <fcntl.h>
#include "Jogo.h"



HANDLE semRead;
HANDLE semWrite;
HANDLE mutRead;
HANDLE mutWrite;
HANDLE waitStart;



void escreveMonitorToServidor(MonToSer* m,int comando) {
    WaitForSingleObject(semWrite, INFINITE);	
    WaitForSingleObject(mutWrite, INFINITE);	
    memcpy(&m->comando[m->proxwrite], &comando, sizeof(comando));	
    m->proxwrite == (m->maxPos - 1) ? m->proxwrite = 0 : m->proxwrite++;	
    ReleaseMutex(mutWrite);						
    if (ReleaseSemaphore(semRead, 1, NULL) == 0)		
        _tprintf(TEXT("\nErro a libertar semáforo %s -> %d\n"), MONITOR_TO_SERVIDOR_LER_SEMAFORO, GetLastError());
}

DWORD WINAPI escreveComandos(LPVOID param) {
    MonToSer* m = (MonToSer*)param;
    m->maxPos = 10;
    m->proxRead = 0;
    m->proxwrite = 0;
    int tempo;

    TCHAR* token;
    TCHAR comando[100];
    while (_tccmp(comando, _T("fim")) != 0) {
        _fgetts(comando, 100, stdin);
        token = _tcstok(comando, " ");
        if (_tccmp(token, _T("para")) == 0) {
            escreveMonitorToServidor(m, PARAR_AGUA);
            token = _tcstok(NULL, " ");
            tempo = _ttoi(token);
            escreveMonitorToServidor(m, tempo);

        }else if (_tccmp(comando, _T("random")== 0)){
            escreveMonitorToServidor(m,MODO_ALEATORIO);
        }
    }
    escreveMonitorToServidor(m, OFF);
    return 0;
}

void existeUnicidade() {

    HANDLE existe = CreateFileMapping(
        INVALID_HANDLE_VALUE,		//usado para quando não há um ficheiro a abrir, é só na ram
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(TCHAR),
        _T("ALREADY_CREATED_MONITOR")
    );
    if (existe == NULL) {
        _tprintf(_T("Não foi possivel criar map unicidade \nA desligar\n"));
        exit(1);
    }
    else if (GetLastError() == ERROR_ALREADY_EXISTS) {
        _tprintf(_T("Ja se encontra ligada uma instancia do Monitor\nA desligar\n"));
        exit(2);
    }

}

int _tmain(int argc, LPTSTR argv[]) {


    existeUnicidade();

    JOGO jogo;

#ifdef UNICODE
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
#endif

    /*AQUI VAI SER A TAB*/

    semRead = CreateSemaphore(NULL, 0, 10, MONITOR_TO_SERVIDOR_LER_SEMAFORO);
    semWrite = CreateSemaphore(NULL, 1, 10, MONITOR_TO_SERVIDOR_ESCREVER_SEMAFORO);
    mutRead = CreateMutex(NULL, FALSE, MONITOR_TO_SERVIDOR_LER_MUTEX);
    mutWrite = CreateMutex(NULL, FALSE, MONITOR_TO_SERVIDOR_ESCREVER_MUTEX);
    HANDLE waitStart = CreateMutex(NULL, TRUE, MONITOR_TO_SERVIDOR_START_MUTEX);


    HANDLE mapMonToServ = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(MonToSer), MONITOR_TO_SERVIDOR_MAP);
    if (mapMonToServ == NULL) {
        _tprintf(_T("Erro a criar o FileMap do MonToSer: %d"), GetLastError());
        CloseHandle(mapMonToServ);
        return -1;
    }

    MonToSer* ptrMonToServ = (MonToSer*)MapViewOfFile(mapMonToServ, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (ptrMonToServ == NULL) {
        _tprintf(_T("Erro a criar o MonToSer: %d"), GetLastError());
        return -1;
    }

    int tid;
    HANDLE comandos = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)escreveComandos, ptrMonToServ,0, &tid);

    //WaitForSingleObject(waitStart, INFINITE);

    HANDLE map = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(Memoria), _T("JOGODOSTUBOS"));
    if (map == NULL) {
        _tprintf(_T("Erro a criar o FileMap: %d"), GetLastError());
        CloseHandle(map);
        return -1;
    }

    Memoria* ptr = (Memoria*)MapViewOfFile(map, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (ptr == NULL) {
        _tprintf(_T("Erro a criar a Memória: %d"), GetLastError());
        return -1;
    }

    ptr->jogo.ganhou = 2;


    

    while (ptr->jogo.ganhou == 2) {
            Sleep(2000);
            jogo = ptr->jogo;
            //system("cls");
            for (int i = 0; i < jogo.altura; i++) {
                for (int j = 0; j < jogo.largura; j++)
                    _tprintf(_T("%c"), jogo.tab[i][j]);
                _tprintf(_T("\n"));
            }
            
    }

    if (ptr->jogo.ganhou == 1) {
        _tprintf(_T("Ganhou"));
    }
    else if (ptr->jogo.ganhou == 0) {
        _tprintf(_T("Perdeu"));
    }
    else if (ptr->jogo.ganhou == 3) {
        _tprintf(_T("Jogo fechado pelo admin"));
    }

    return 0;
}