#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include "../Monitor/Jogo.h"
#define TAM 200


DWORD WINAPI Terminar(LPVOID param) {
    int* sair = (int*)param;

    _gettch();
    (*sair) = 1;
    return 0;
}

void metestartEnd(TCHAR t[][20], int a, int l) {
    int auxA;
    int auxL;

    auxA = (int)(rand() % a);
    auxL = (int)(rand() % l);

    if (rand() > 0.5) {
        t[auxA][0] = _T('I');
        auxA = rand() % a;
        t[auxA][l - 1] = _T('F');
    }
    else {
        t[0][auxL] = _T('I');
        auxL = rand() % l;
        t[a - 1][auxL] = _T('F');
    }
}


TCHAR pegaAPeca() {
    TCHAR c, l[3] = { _T('━'),_T('┃'),_T('┏') };
    int i = (int)(rand() % 3);
    c = l[i];
    return c;
}

void escolheLocal(TCHAR t[][20], int a, int l) {
    int auxA, auxL, aprovado = 1, opcao = 0;
    TCHAR c;

    c = pegaAPeca();

    while (aprovado) {
        _tprintf(_T("Quais as Coordenadas pretendidas para a peça %c ?"), c);
        _tscanf_s(_T("%d %d"), &auxA, &auxL);
        if ((auxA <= a && auxL <= l) && t[auxA - 1][auxL - 1] == _T('█')) {
            aprovado = 0;
        }
    }

    if (c == _T('┏')) {
        while (1 > opcao || opcao > 4) {
            _tprintf(_T("Quais a rotação desejada?/n 1: ┏ /n 2: ┓ /n 3: ┛ /n 4: ┗ "));
            _tscanf_s(_T("%d"), &opcao);
        };
        switch (opcao)
        {
        case 1:
            c = _T('┏');
            break;
        case 2:
            c = _T('┓');
            break;
        case 3:
            c = _T('┛');
            break;
        case 4:
            c = _T('┗');
            break;
        default:
            break;
        }
    }
    t[auxA - 1][auxL - 1] = c;

}

int correAgua(TCHAR t[][20], int a, int l,int tempo) {
    int auxA = 0, auxL = 0, ganhou = 1;
    Sleep(tempo * 1000);
    //printf("DEBUG ENTROU");
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            if (t[i][j] == _T('I')) {
                auxA = i;
                auxL = j;
            }
        }
    }
    while (ganhou) {
        if (t[auxA][auxL] == _T('I')) {
            if (auxA == 0 && auxL > 0) {//teto
                if (t[auxA + 1][auxL] == _T('┗') || t[auxA + 1][auxL] == _T('┛') || t[auxA + 1][auxL] == _T('┃'))
                    auxA++;
                else {
                    ganhou = 0;
                    Sleep(100);
                    return ganhou;
                }
            }
            else if (auxA >= 0 && auxL == 0) {//lado direito
                if (t[auxA][auxL + 1] == _T('┛') || t[auxA][auxL + 1] == _T('┓') || t[auxA][auxL + 1] == _T('━'))
                    auxL++;
                else {
                    ganhou = 0;
                    Sleep(100);
                    return ganhou;
                }
            }
        }
        else if (t[auxA][auxL] == _T('┏'))
        {
            t[auxA][auxL] = _T('*');
            //verifica Final
            if (t[auxA + 1][auxL] == _T('F') || t[auxA][auxL + 1] == _T('F')) {
                Sleep(100);
                return ganhou;
            }

            //baixo
            if (t[auxA + 1][auxL] == _T('┗') || t[auxA + 1][auxL] == _T('┛') || t[auxA + 1][auxL] == _T('┃')) {
                auxA++;
            }
            //direita
            else  if (t[auxA][auxL + 1] == _T('┛') || t[auxA][auxL + 1] == _T('┓') || t[auxA][auxL + 1] == _T('━')) {
                auxL++;
            }
            else {
                ganhou = 0;
                Sleep(100);
                return ganhou;
            }


        }
        else if (t[auxA][auxL] == _T('┓'))
        {
            t[auxA][auxL] = _T('*');
            //verifica Final
            if (t[auxA + 1][auxL] == _T('F') || t[auxA][auxL - 1] == _T('F')) {
                Sleep(100);
                return ganhou;
            }

            //baixo
            if (t[auxA + 1][auxL] == _T('┗') || t[auxA + 1][auxL] == _T('┛') || t[auxA + 1][auxL] == _T('┃')) {
                auxA++;
            }
            //esquerda
            else  if (t[auxA][auxL - 1] == _T('┗') || t[auxA][auxL - 1] == _T('┏') || t[auxA][auxL - 1] == _T('━')) {
                auxL--;
            }
            else {
                ganhou = 0;
                Sleep(100);
                return ganhou;
            }

        }
        else if (t[auxA][auxL] == _T('┛'))
        {
            t[auxA][auxL] = _T('*');
            if (t[auxA - 1][auxL] == _T('F') || t[auxA][auxL - 1] == _T('F')) {
                Sleep(100);
                return ganhou;
            }
            //cima
            if (t[auxA - 1][auxL] == _T('┏') || t[auxA - 1][auxL] == _T('┓') || t[auxA - 1][auxL] == _T('┃')) {
                auxA--;
            }
            //esquerda
            else if (t[auxA][auxL - 1] == _T('┗') || t[auxA][auxL - 1] == _T('┏') || t[auxA][auxL - 1] == _T('━')) {
                auxL--;
            }
            else {
                ganhou = 0;
                Sleep(100);
                return ganhou;
            }



        }
        else if (t[auxA][auxL] == _T('┗')) {

            t[auxA][auxL] = _T('*');
            //verifica Final
            if (t[auxA - 1][auxL] == _T('F') || t[auxA][auxL + 1] == _T('F')) {
                Sleep(100);
                return ganhou;
            }

            //cima
            if (t[auxA - 1][auxL] == _T('┏') || t[auxA - 1][auxL] == _T('┓') || t[auxA - 1][auxL] == _T('┃')) {
                auxA--;
            }
            //direita
            else  if (t[auxA][auxL + 1] == _T('┛') || t[auxA][auxL + 1] == _T('┓') || t[auxA][auxL + 1] == _T('━')) {
                auxL++;
            }
            else {
                ganhou = 0;
                Sleep(100);
                return ganhou;
            }

        }
        else if (t[auxA][auxL] == _T('━'))
        {
            t[auxA][auxL] = _T('*');
            if (t[auxA][auxL + 1] == _T('F') || t[auxA][auxL - 1] == _T('F')) {
                Sleep(100);
                return ganhou;
            }
            //esquerda
            if (t[auxA][auxL - 1] == _T('┗') || t[auxA][auxL - 1] == _T('┏') || t[auxA][auxL - 1] == _T('━')) {
                auxL--;
                // direita
            }
            else if (t[auxA][auxL + 1] == _T('┛') || t[auxA][auxL + 1] == _T('┓') || t[auxA][auxL + 1] == _T('━')) {
                auxL++;
            }
            else {
                ganhou = 0;
                Sleep(100);
                return ganhou;
            }

        }
        else if (t[auxA][auxL] == _T('┃'))
        {
            t[auxA][auxL] = _T('*');
            //verifica Final
            if (t[auxA + 1][auxL] == _T('F') || t[auxA - 1][auxL] == _T('F')) {
                Sleep(100);
                return ganhou;
            }

            //baixo
            if (t[auxA + 1][auxL] == _T('┗') || t[auxA + 1][auxL] == _T('┛') || t[auxA + 1][auxL] == _T('┃')) {
                auxA++;
            }
            // cima
            else if (t[auxA - 1][auxL] == _T('┓') || t[auxA - 1][auxL] == _T('┏') || t[auxA - 1][auxL] == _T('┃')) {
                auxA--;
            }
            else {
                ganhou = 0;
                Sleep(100);
                return ganhou;
            }


        }
        Sleep(2000);
    }

    return ganhou;
}


int _tmain(int argc, LPTSTR argv[]) {
    //CHAVES
    HKEY chave; //aberto ou fechado
    DWORD resultado; //o que aconteceu com a chave
    TCHAR caminho_chave[TAM] = TEXT("SOFTWARE\\PRESETTUBO\\PresetsJogo");
    TCHAR chave_nome[TAM]= TEXT("PresetsJogo");
    TCHAR par_Altura_nome[TAM] = TEXT("Altura");
    TCHAR par_Altura_valor[TAM] = TEXT("10");
    TCHAR par_LARGURA_nome[TAM] = TEXT("Largura");
    TCHAR par_LARGURA_valor[TAM] = TEXT("10");
    TCHAR par_TEMPO_AGUA_nome[TAM] = TEXT("TempoSegundos");
    TCHAR par_TEMPO_AGUA_valor[TAM] = TEXT("5");
    //============================================================
    JOGO jogo;


#ifdef UNICODE
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
#endif

    if (RegCreateKeyEx(HKEY_CURRENT_USER,				//HKEY hKey -> qual a diretoria onde eu quero criar a chave,
        caminho_chave,						            //LPCTSTR lpSubKey -> qual é o nome desta chave
        0,								                //DWORD Reserved
        NULL,							                // LPTSTR lpClass
        REG_OPTION_NON_VOLATILE,		                // -> a chave nao se apaga quando se desliga e liga o pc
        KEY_ALL_ACCESS,					                // -> podemos fazer tudo da chave
        NULL,							                //const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        &chave,						                    //PHKEY phkResult
        &resultado) != ERROR_SUCCESS) {
        _tprintf(TEXT("Chave nao foi criada nem aberta ! ERRO!\n"));
        return -1;
    }

    //é porque a chave foi criada
    if (resultado == REG_CREATED_NEW_KEY)
        _tprintf(TEXT("A chave foi criada: %s\n"), chave_nome);
    //é porque a chave ja existe e foi aberta
    else
        _tprintf(TEXT("A chave foi aberta:%s\n"), chave_nome);


    if (RegSetValueEx(
        chave,						//HKEY   hKey
        par_Altura_nome,					//LPCSTR     lpValueName,
        0,							//DWORD      Reserved,
        REG_SZ,						//DWORD      dwType -> tipo do atributo,
        par_Altura_valor,					//const BYTE * lpData -> que valor queremos lá por
        sizeof(TCHAR) * (_tcslen(par_Altura_valor) + 1)			//DWORD      cbData -> tamanho do valor + 1 para terminar a string
    ) != ERROR_SUCCESS)
        _tprintf(TEXT("Atributo não foi alterado nem criado ! ERRO!\n"));

    if (RegSetValueEx(
        chave,						//HKEY   hKey
        par_LARGURA_nome,					//LPCSTR     lpValueName,
        0,							//DWORD      Reserved,
        REG_SZ,						//DWORD      dwType -> tipo do atributo,
        par_LARGURA_valor,					//const BYTE * lpData -> que valor queremos lá por
        sizeof(TCHAR) * (_tcslen(par_LARGURA_valor) + 1)			//DWORD      cbData -> tamanho do valor + 1 para terminar a string
    ) != ERROR_SUCCESS)
        _tprintf(TEXT("Atributo não foi alterado nem criado ! ERRO!\n"));

    if (RegSetValueEx(
        chave,						//HKEY   hKey
        par_TEMPO_AGUA_nome,					//LPCSTR     lpValueName,
        0,							//DWORD      Reserved,
        REG_SZ,						//DWORD      dwType -> tipo do atributo,
        par_TEMPO_AGUA_valor,					//const BYTE * lpData -> que valor queremos lá por
        sizeof(TCHAR) * (_tcslen(par_TEMPO_AGUA_valor) + 1)			//DWORD      cbData -> tamanho do valor + 1 para terminar a string
    ) != ERROR_SUCCESS)
        _tprintf(TEXT("Atributo não foi alterado nem criado ! ERRO!\n"));

    par_Altura_valor[0] = '\0'; // esta vazio
    DWORD tamanho = sizeof(par_Altura_valor);

    if (RegQueryValueEx(
        chave,
        par_Altura_nome,
        0,							//DWORD      Reserved,
        NULL,
        par_Altura_valor,
        &tamanho
    ) != ERROR_SUCCESS)
        _tprintf(TEXT("Atributo não foi encontrado! ERRO!\n"));
    else
        jogo.altura = _ttoi(par_Altura_valor);//_tprintf(TEXT("Atributo encontrado com valor:%s e tamanho:%d\n"), par_Altura_valor, tamanho);

    par_LARGURA_valor[0] = '\0'; // esta vazio
    tamanho = sizeof(par_LARGURA_valor);

    if (RegQueryValueEx(
        chave,
        par_LARGURA_nome,
        0,							//DWORD      Reserved,
        NULL,
        par_LARGURA_valor,
        &tamanho
    ) != ERROR_SUCCESS)
        _tprintf(TEXT("Atributo não foi encontrado! ERRO!\n"));
    else
        jogo.largura = _ttoi(par_LARGURA_valor);//_tprintf(TEXT("Atributo encontrado com valor:%s e tamanho:%d\n"), par_LARGURA_valor, tamanho);

    par_TEMPO_AGUA_valor[0] = '\0'; // esta vazio
    tamanho = sizeof(par_TEMPO_AGUA_valor);

    if (RegQueryValueEx(
        chave,
        par_TEMPO_AGUA_nome,
        0,							//DWORD      Reserved,
        NULL,
        par_TEMPO_AGUA_valor,
        &tamanho
    ) != ERROR_SUCCESS)
        _tprintf(TEXT("Atributo não foi encontrado! ERRO!\n"));
    else
        jogo.tempo_agua = _ttoi(par_TEMPO_AGUA_valor);//_tprintf(TEXT("Atributo encontrado com valor:%s e tamanho:%d\n"), par_TEMPO_AGUA_valor, tamanho);

//logica de jogo e afins


        RegCloseKey(chave);

        

        //Gera Area de jogo
        for (int i = 0; i < jogo.altura; i++)
            for (int j = 0; j < jogo.largura; j++)
                jogo.tab[i][j] = _T('█');

        //mete Começo(I) e FIM(F) na tabela aleatoriamente
        //metestartEnd(jogo.tab, jogo.altura, jogo.largura);

        //TABULEIRO PREDEFINIDO
        jogo.tab[2][0] = _T('I');
        for (int i = 1; i < jogo.altura - 1; i++)
            jogo.tab[2][i] = _T('━');
        jogo.tab[2][jogo.altura - 1] = _T('F');
        //=======================================================
        jogo.ganhou = 2;
        //PARA escolher a peça
        //while (memoria.jogo.ganhou == 2) {
        //    escolheLocal(memoria.jogo.tab, memoria.jogo.altura, memoria.jogo.largura);
        //}

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
        /*if (instancia) {
            ZeroMemory(ptr, sizeof(Memoria));
        }*/
        ptr->jogo.ganhou = 2;

        while (ptr->jogo.ganhou == 2) {
            ptr->jogo = jogo;
            ptr->jogo.ganhou = correAgua(ptr->jogo.tab, ptr->jogo.altura,ptr->jogo.largura,ptr->jogo.tempo_agua);
            
        }



    return 0;
}