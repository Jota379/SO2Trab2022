// Cliente.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Cliente.h"


#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

#include <stdio.h>

#define PIPE_JOGO TEXT("\\\\.\\pipe\\teste")

/* ===================================================== */
/* Programa base (esqueleto) para aplica��es Windows     */
/* ===================================================== */
// Cria uma janela de nome "Janela Principal" e pinta fundo de branco
// Modelo para programas Windows:
//  Composto por 2 fun��es: 
//	WinMain()     = Ponto de entrada dos programas windows
//			1) Define, cria e mostra a janela
//			2) Loop de recep��o de mensagens provenientes do Windows
//     TrataEventos()= Processamentos da janela (pode ter outro nome)
//			1) � chamada pelo Windows (callback) 
//			2) Executa c�digo em fun��o da mensagem recebida

LRESULT CALLBACK TrataEventos(HWND, UINT, WPARAM, LPARAM);

// Nome da classe da janela (para programas de uma s� janela, normalmente este nome � 
// igual ao do pr�prio programa) "szprogName" � usado mais abaixo na defini��o das 
// propriedades do objecto janela
TCHAR szProgName[] = TEXT("Cliente");

// ============================================================================
// FUN��O DE IN�CIO DO PROGRAMA: WinMain()
// ============================================================================
// Em Windows, o programa come�a sempre a sua execu��o na fun��o WinMain()que desempenha
// o papel da fun��o main() do C em modo consola WINAPI indica o "tipo da fun��o" (WINAPI
// para todas as declaradas nos headers do Windows e CALLBACK para as fun��es de
// processamento da janela)
// Par�metros:
//   hInst: Gerado pelo Windows, � o handle (n�mero) da inst�ncia deste programa 
//   hPrevInst: Gerado pelo Windows, � sempre NULL para o NT (era usado no Windows 3.1)
//   lpCmdLine: Gerado pelo Windows, � um ponteiro para uma string terminada por 0
//              destinada a conter par�metros para o programa 
//   nCmdShow:  Par�metro que especifica o modo de exibi��o da janela (usado em  
//        	   ShowWindow()


int WINAPI WinMain(HINSTANCE hInst, // instancia atual app
	HINSTANCE hPrevInst,//
	LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;		// hWnd � o handler da janela, gerado mais abaixo por CreateWindow()
	MSG lpMsg;		// MSG � uma estrutura definida no Windows para as mensagens
	WNDCLASSEX wcApp;	// WNDCLASSEX � uma estrutura cujos membros servem para 
			  // definir as caracter�sticas da classe da janela

	// ============================================================================
	// 1. Defini��o das caracter�sticas da janela "wcApp" 
	//    (Valores dos elementos da estrutura "wcApp" do tipo WNDCLASSEX)
	// ============================================================================
	wcApp.cbSize = sizeof(WNDCLASSEX);      // Tamanho da estrutura WNDCLASSEX
	wcApp.hInstance = hInst;		         // Inst�ncia da janela actualmente exibida 
								   // ("hInst" � par�metro de WinMain e vem 
										 // inicializada da�)
	wcApp.lpszClassName = szProgName;       // Nome da janela (neste caso = nome do programa)
	wcApp.lpfnWndProc = TrataEventos;       // Endere�o da fun��o de processamento da janela
											// ("TrataEventos" foi declarada no in�cio e
											// encontra-se mais abaixo)
	wcApp.style = CS_HREDRAW | CS_VREDRAW;  // Estilo da janela: Fazer o redraw se for
											// modificada horizontal ou verticalmente

	wcApp.hIcon = LoadIcon(NULL, IDI_WARNING);   // "hIcon" = handler do �con normal
										   // "NULL" = Icon definido no Windows
										   // "IDI_AP..." �cone "aplica��o"
	wcApp.hIconSm = LoadIcon(NULL, IDI_WARNING); // "hIconSm" = handler do �con pequeno
										   // "NULL" = Icon definido no Windows
										   // "IDI_INF..." �con de informa��o
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);	// "hCursor" = handler do cursor (rato) 
							  // "NULL" = Forma definida no Windows
							  // "IDC_ARROW" Aspecto "seta" 
	wcApp.lpszMenuName = NULL;			// Classe do menu que a janela pode ter
							  // (NULL = n�o tem menu)
	wcApp.cbClsExtra = 0;				// Livre, para uso particular
	wcApp.cbWndExtra = 0;				// Livre, para uso particular
	wcApp.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	// "hbrBackground" = handler para "brush" de pintura do fundo da janela. Devolvido por
	// "GetStockObject".Neste caso o fundo ser� branco

	// ============================================================================
	// 2. Registar a classe "wcApp" no Windows
	// ============================================================================
	if (!RegisterClassEx(&wcApp))
		return(0);

	// ============================================================================
	// 3. Criar a janela
	// ============================================================================
	hWnd = CreateWindow(
		szProgName,			// Nome da janela (programa) definido acima
		TEXT("Jogo dos Tubos"),// Texto que figura na barra do t�tulo
		WS_OVERLAPPEDWINDOW,	// Estilo da janela (WS_OVERLAPPED= normal)
		200,		// Posi��o x pixels (default=� direita da �ltima) 
		200,		// Posi��o y pixels (default=abaixo da �ltima)
		725,		// Largura da janela (em pixels)
		650,		// Altura da janela (em pixels)
		(HWND)HWND_DESKTOP,	// handle da janela pai (se se criar uma a partir de
						// outra) ou HWND_DESKTOP se a janela for a primeira, 
						// criada a partir do "desktop"
		(HMENU)NULL,			// handle do menu da janela (se tiver menu)
		(HINSTANCE)hInst,		// handle da inst�ncia do programa actual ("hInst" � 
						// passado num dos par�metros de WinMain()
		0);				// N�o h� par�metros adicionais para a janela




	// ============================================================================
	// 4. Mostrar a janela
	// ============================================================================
	ShowWindow(hWnd, nCmdShow);	// "hWnd"= handler da janela, devolvido por 
					  // "CreateWindow"; "nCmdShow"= modo de exibi��o (p.e. 
					  // normal/modal); � passado como par�metro de WinMain()
	UpdateWindow(hWnd);		// Refrescar a janela (Windows envia � janela uma 
					  // mensagem para pintar, mostrar dados, (refrescar)� 
	// ============================================================================
	// 5. Loop de Mensagens
	// ============================================================================
	// O Windows envia mensagens �s janelas (programas). Estas mensagens ficam numa fila de
	// espera at� que GetMessage(...) possa ler "a mensagem seguinte"	
	// Par�metros de "getMessage":
	// 1)"&lpMsg"=Endere�o de uma estrutura do tipo MSG ("MSG lpMsg" ja foi declarada no  
	//   in�cio de WinMain()):
	//			HWND hwnd		handler da janela a que se destina a mensagem
	//			UINT message		Identificador da mensagem
	//			WPARAM wParam		Par�metro, p.e. c�digo da tecla premida
	//			LPARAM lParam		Par�metro, p.e. se ALT tamb�m estava premida
	//			DWORD time		Hora a que a mensagem foi enviada pelo Windows
	//			POINT pt		Localiza��o do mouse (x, y) 
	// 2)handle da window para a qual se pretendem receber mensagens (=NULL se se pretendem
	//   receber as mensagens para todas as
	// janelas pertencentes � thread actual)
	// 3)C�digo limite inferior das mensagens que se pretendem receber
	// 4)C�digo limite superior das mensagens que se pretendem receber

	// NOTA: GetMessage() devolve 0 quando for recebida a mensagem de fecho da janela,
	// 	  terminando ent�o o loop de recep��o de mensagens, e o programa 

	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);	// Pr�-processamento da mensagem (p.e. obter c�digo 
					   // ASCII da tecla premida)
		DispatchMessage(&lpMsg);	// Enviar a mensagem traduzida de volta ao Windows, que
					   // aguarda at� que a possa reenviar � fun��o de 
					   // tratamento da janela, CALLBACK TrataEventos (abaixo)
	}

	// ============================================================================
	// 6. Fim do programa
	// ============================================================================
	return((int)lpMsg.wParam);	// Retorna sempre o par�metro wParam da estrutura lpMsg
}


LRESULT CALLBACK TrataEventos(HWND hWnd, UINT messg, WPARAM wParam,
	LPARAM lParam) {
	HDC hdc;
	HDC dc;
	PAINTSTRUCT ps;
	static int x = 0, y = 0;
	TCHAR texto[100];
	static int aux = 0;
	static HWND hNovoJogo, hObjetivo, hSair;

	//BITMAP
	// uma vez que temos de usar estas vars tanto na main como na funcao de tratamento de eventos
	// nao ha uma maneira de fugir ao uso de vars globais, dai estarem aqui
	HBITMAP hBmp,hBmp1,hBmp2,hBmp3,hBmp4,hBmp5,hBmp6; // handle para o bitmap
	static HDC bmpDC, bmpDC1, bmpDC2, bmpDC3, bmpDC4, bmpDC5, bmpDC6; // hdc do bitmap
	static BITMAP bmp, bmp1, bmp2, bmp3, bmp4, bmp5, bmp6; // informa��o sobre o bitmap
	int xBitmap; // posicao onde o bitmap vai ser desenhado
	int yBitmap;
	int xPos, yPos, numClicks = 1;
	int limDir; // limite direito
	HWND hWndGlobal; // handle para a janela
	HANDLE hMutex;

	HDC memDC = NULL; // copia do device context que esta em memoria, tem de ser inicializado a null
	HBITMAP hBitmapDB; // copia as caracteristicas da janela original para a janela que vai estar em memoria

	RECT rect;

	switch (messg) {
	case WM_COMMAND:
	{
		switch (wParam) {
		case 1:
			DestroyWindow(hNovoJogo);
			DestroyWindow(hObjetivo);
			DestroyWindow(hSair);

			aux = 1;
			InvalidateRect(hWnd, NULL, TRUE);

			break;
		case 2:
			/*DestroyWindow(hNovoJogo);
			DestroyWindow(hObjetivo);
			DestroyWindow(hSair);*/
			MessageBox(hWnd, TEXT("O Objetivo do Jogo dos Tubos e fazer com que a �gua v� de uma torneira a outra torneira por tubos que vos s�o dados mas sem haver nenhuma fuga de �gua!!"), TEXT("Objetivo"), MB_OK);
			break;
		case 3:
			/*	DestroyWindow(hNovoJogo);
				DestroyWindow(hObjetivo);
				DestroyWindow(hSair);*/
			if (MessageBox(hWnd, TEXT("Quer mesmo sair?"), TEXT("Fim"),
				MB_YESNO) == IDYES)
				PostQuitMessage(0);
			break;
		}
	}
	break;
	case WM_CREATE:

		// carregar o bitmap
		hBmp = (HBITMAP)LoadImage(NULL, TEXT("jogo1.bmp"), IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
		GetObject(hBmp, sizeof(bmp), &bmp); // vai buscar info sobre o handle do bitmap

		hBmp1 = (HBITMAP)LoadImage(NULL, TEXT("horizontal.bmp"), IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
		GetObject(hBmp1, sizeof(bmp1), &bmp1); // vai buscar info sobre o handle do bitmap

		hBmp2 = (HBITMAP)LoadImage(NULL, TEXT("vertical.bmp"), IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
		GetObject(hBmp2, sizeof(bmp2), &bmp2); // vai buscar info sobre o handle do bitmap

		hBmp3 = (HBITMAP)LoadImage(NULL, TEXT("cima.bmp"), IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
		GetObject(hBmp3, sizeof(bmp3), &bmp3); // vai buscar info sobre o handle do bitmap

		hBmp4 = (HBITMAP)LoadImage(NULL, TEXT("dir.bmp"), IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
		GetObject(hBmp4, sizeof(bmp4), &bmp4); // vai buscar info sobre o handle do bitmap

		hBmp5 = (HBITMAP)LoadImage(NULL, TEXT("baixo.bmp"), IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
		GetObject(hBmp5, sizeof(bmp5), &bmp5); // vai buscar info sobre o handle do bitmap

		hBmp6 = (HBITMAP)LoadImage(NULL, TEXT("esq.bmp"), IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
		GetObject(hBmp6, sizeof(bmp6), &bmp6); // vai buscar info sobre o handle do bitmap
		

		hdc = GetDC(hWnd);
		// criamos copia do device context e colocar em memoria
		bmpDC = CreateCompatibleDC(hdc);
		// aplicamos o bitmap ao device context
		SelectObject(bmpDC, hBmp);	
		///////////////
		bmpDC1 = CreateCompatibleDC(hdc);

		SelectObject(bmpDC1, hBmp1);
		///////////////
		bmpDC2 = CreateCompatibleDC(hdc);

		SelectObject(bmpDC2, hBmp2);
		///////////////
		bmpDC3 = CreateCompatibleDC(hdc);
	
		SelectObject(bmpDC3, hBmp3);
		///////////////
		bmpDC4 = CreateCompatibleDC(hdc);
	
		SelectObject(bmpDC4, hBmp4);
		///////////////
		bmpDC5 = CreateCompatibleDC(hdc);
		
		SelectObject(bmpDC5, hBmp5);
		///////////////
		bmpDC6 = CreateCompatibleDC(hdc);
		
		SelectObject(bmpDC6, hBmp6);

		ReleaseDC(hWnd, hdc);

		BitBlt(hdc, 15, 30, bmp.bmWidth, bmp.bmHeight, bmpDC, 0, 0, SRCCOPY);

		hNovoJogo = CreateWindowW(L"Button", L"Novo Jogo", WS_VISIBLE | WS_CHILD, 250, 340, 200, 50, hWnd, (HMENU)1, NULL, NULL);
		hObjetivo = CreateWindowW(L"Button", L"Objetivo", WS_VISIBLE | WS_CHILD, 250, 390, 200, 50, hWnd, (HMENU)2, NULL, NULL);
		hSair = CreateWindowW(L"Button", L"Sair", WS_VISIBLE | WS_CHILD, 250, 440, 200, 50, hWnd, (HMENU)3, NULL, NULL);

		break;
	case WM_PAINT:

		//aux = 1;
		if (aux == 1) {
			//MessageBox(hWnd, _T("janela de ajuda"), _T("Sair"), MB_OK);
			hdc = BeginPaint(hWnd, &ps);
			int i = 0, j;
			int Lx1 = 15, Lx2 = 65;
			int Cy1 = 30, Cy2 = 80;
			for (j = 0; j < 10; j++) {
				for (i = 0; i < 10; i++) {
					Rectangle(hdc, Lx1, Cy1, Lx2, Cy2);
					Lx1 = Lx2;
					Lx2 = Lx2 + 50;
				}
				Cy1 = Cy2;
				Cy2 = Cy2 + 50;
				Lx1 = 15, Lx2 = 65;
				/*BitBlt(hdc, 15, 30, bmp1.bmWidth, bmp1.bmHeight, bmpDC1, 0, 0, SRCCOPY);
				BitBlt(hdc, 50, 45, bmp2.bmWidth, bmp2.bmHeight, bmpDC2, 0, 0, SRCCOPY);
				BitBlt(hdc, 150, 45, bmp3.bmWidth, bmp3.bmHeight, bmpDC3, 0, 0, SRCCOPY);
				BitBlt(hdc, 200, 90, bmp4.bmWidth, bmp4.bmHeight, bmpDC4, 0, 0, SRCCOPY);
				BitBlt(hdc, 300, 40, bmp5.bmWidth, bmp5.bmHeight, bmpDC5, 0, 0, SRCCOPY);
				BitBlt(hdc, 450, 80, bmp6.bmWidth, bmp6.bmHeight, bmpDC6, 0, 0, SRCCOPY);*/
			}
			EndPaint(hWnd, &ps);
			//aux = 0;
		}
		break;


	case WM_LBUTTONDOWN: // <-BOTAO ESQUERDO, BOTADO DIREITO -> WM_RBUTTONDOWN
		numClicks++;
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);
		hdc = GetDC(hWnd); //A fun��o GetDC recupera um identificador para um contexto de dispositivo (DC)
		GetClientRect(hWnd, &rect);
		SetTextColor(hdc, RGB(139, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		rect.left = xPos;
		rect.top = yPos;
		BitBlt(hdc, 15, 30, bmp1.bmWidth, bmp1.bmHeight, bmpDC1, 0, 0, SRCCOPY);
		BitBlt(hdc, 50, 45, bmp2.bmWidth, bmp2.bmHeight, bmpDC2, 0, 0, SRCCOPY);
		BitBlt(hdc, 150, 45, bmp3.bmWidth, bmp3.bmHeight, bmpDC3, 0, 0, SRCCOPY);
		BitBlt(hdc, 200, 90, bmp4.bmWidth, bmp4.bmHeight, bmpDC4, 0, 0, SRCCOPY);
		BitBlt(hdc, 300, 40, bmp5.bmWidth, bmp5.bmHeight, bmpDC5, 0, 0, SRCCOPY);
		BitBlt(hdc, 450, 80, bmp6.bmWidth, bmp6.bmHeight, bmpDC6, 0, 0, SRCCOPY);
		//ReleaseDC(hWnd, hdc);
	/*	if (aux == 0)
			aux = 1;
		else
			aux = 0;*/
		InvalidateRect(hWnd, NULL, TRUE); // requisita WM_PAINT
		break;
	//case WM_RBUTTONDOWN:
	////rodar imagem
	//break;
	case WM_CLOSE: // Destruir a janela e terminar o programa 
		if (MessageBox(hWnd, TEXT("Quer mesmo sair?"), TEXT("Fim"),
			MB_YESNO) == IDYES)
			PostQuitMessage(0);
		break;
	default:
		// Neste exemplo, para qualquer outra mensagem (p.e. "minimizar","maximizar","restaurar") // n�o 
		//� efectuado nenhum processamento, apenas se segue o "default" do Windows
		return(DefWindowProc(hWnd, messg, wParam, lParam));
		break;
	}
	return(0);
}