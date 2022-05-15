#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include "Jogo.h"

/*
DWORD WINAPI escreveComandos(LPVOID param) {
    Memoria* m = (Memoria*)param;
    while (_tccmp(m->comando, _T("fim")) != 0) {
        if (_tccmp(m->comando, _T("nenhum"))!= 0) {
            _fgetts(m->comando, 100, stdin);
            m->comando[_tcslen(m->comando) - 1] = '\0';
        }
    }
    return 0;
}
*/


int _tmain(int argc, LPTSTR argv[]) {

    JOGO jogo;

#ifdef UNICODE
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
#endif

    /*AQUI VAI SER A TAB*/

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
/*
    int tid;
    int stop;
    HANDLE comandos = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)escreveComandos, ptr, 0, &tid);
    */

    while (ptr->jogo.ganhou == 2) {
            jogo = ptr->jogo;
            system("cls");
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