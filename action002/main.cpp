//========================================================
//
//ウインドウの生成等 (main.cpp)
//Author 橋本賢太
//
//========================================================
#include "main.h"
#include "object.h"
#include "renderer.h"
#include "manager.h"

//マクロ定義
#define WINDOW_NAME				"3Dアクションシューティング"			//ウインドウの名前
#define ID_BUTTON_FINISH		(101)									//終了ボタンのID

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);		//ウインドウプロシージャ

//グローバル変数
int g_nCountFPS;

//========================================================
//メイン関数
//========================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	CManager *pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),									//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,											//ウインドウのスタイル
		WindowProc,											//ウインドウプロシージャ
		0,													//0にする
		0,													//0にする
		hInstance,											//インスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),					//タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW),						//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),							//クライアント領域の背景色
		NULL,												//メニューバー
		CLASS_NAME,											//ウインドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION)						//ファイルアイコン
	};
	HWND hWnd;												//ウインドウハンドル
	MSG msg;												//メッセージを格納する変数

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };		//画面サイズの構造体

															//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(
		0,								//拡張ウインドウスタイル
		CLASS_NAME,						//ウインドウクラスの名前
		WINDOW_NAME,					//ウインドウの名前
		WS_OVERLAPPEDWINDOW,			//ウインドウスタイル
		CW_USEDEFAULT,					//ウインドウの左上X座標
		CW_USEDEFAULT,					//ウインドウの左上Y座標
		(rect.right - rect.left),		//ウインドウの幅
		(rect.bottom - rect.top),		//ウインドウの高さ
		NULL,							//親ウインドウのハンドル
		NULL,							//メニューハンドルまたは子ウインドウID
		hInstance,						//インスタンスハンドル
		NULL);							//ウインドウ作成データ

										//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//NULLチェック
	pManager = CManager::GetInstance();

	pManager->Init(hInstance, hWnd, TRUE);

	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;                                       //フレームカウント
	DWORD dwFPSLastTime;                                      //最後にFPSを計測した時刻

	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windousの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}

			else
			{
				//メッセージの設定
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
		}

		else
		{//DirectXの処理

			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
			 //FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;                    //
				dwFrameCount = 0;                                 //
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				if (pManager != NULL)
				{
					//更新処理
					pManager->Update();

					//描画処理
					pManager->Draw();

					dwFrameCount++;                            //
				}
			}
		}
 	}

	//NULLチェック
	if (pManager != NULL)
	{
		//終了処理
		pManager->Uninit();

		delete pManager;

		pManager = NULL;
	}

	timeEndPeriod(1);

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//========================================================
//ウインドウプロシージャ
//========================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;					//返り値を格納

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:			//キー押下にメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:			//[ESC]キーが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
			break;
		}

	case WM_COMMAND:			//コマンド発行のメッセージ
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{//終了ボタンが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
		}
		break;

	case WM_CLOSE:				//閉じるボタン押下のメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
		}

		else
		{
			return 0;			//ウィンドウを終了しないようにする
		}
		break;

	case WM_LBUTTONDOWN:		//マウス左クリック

								//対象ウィンドウにフォーカスを合わせる
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//========================================================
//ウインドウプロシージャ
//========================================================
int GetFPSCount(void)
{
	return g_nCountFPS;
}