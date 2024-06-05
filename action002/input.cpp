//========================================================
//
//ウインドウの生成等 (input.cpp)
//Author 橋本賢太
//
//========================================================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX									(256)		//キーの最大数

LPDIRECTINPUT8 CInput::m_pInput = NULL;
DIMOUSESTATE CInputMouse::g_CurrentMouseState;
DIMOUSESTATE CInputMouse::g_PrevMouseState;

//========================================================
//コンストラクタ
//========================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//========================================================
//デストラクタ
//========================================================
CInput::~CInput()
{

}

//========================================================
//キーボードの初期化処理
//========================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL));
	}

	return S_OK;
}

//========================================================
//キーボードの終了処理
//========================================================
void CInput::Uninit(void)
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();          //キーボードへのアクセス権を破棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//========================================================
//コンストラクタ
//========================================================
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = {};
	}
}

//========================================================
//デストラクタ
//========================================================
CInputKeyboard::~CInputKeyboard()
{

}

//========================================================
//インプットキーボードの初期化処理
//========================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//調教モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得する
	m_pDevice->Acquire();

	return S_OK;
}

//========================================================
//インプットキーボードの終了処理
//========================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//========================================================
//インプットキーボードの更新処理
//========================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];             //キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];			//キーボードのトリガー情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey];																//キーボードのプレス情報を保存
		}
	}

	else
	{
		m_pDevice->Acquire();				//キーボードへのアクセス権を獲得
	}
}

//========================================================
//キーボードのプレス情報を取得
//========================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//========================================================
//キーボードのトリガー情報を取得
//========================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//========================================================
//コンストラクタ
//========================================================
CInputMouse::CInputMouse()
{
	
}

//========================================================
//デストラクタ
//========================================================
CInputMouse::~CInputMouse()
{

}

//========================================================
//マウスの初期化処理
//========================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//調教モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得する
	m_pDevice->Acquire();

	//一定間隔でデバイスの情報を同期させて取得できるようにする
	m_pDevice->Poll();

	return S_OK;
}

//========================================================
//マウスの終了処理
//========================================================
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}

//========================================================
//マウスの更新処理
//========================================================
void CInputMouse::Update(void)
{
	//最新マウス情報を保存する
	g_PrevMouseState = g_CurrentMouseState;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(g_CurrentMouseState), &g_CurrentMouseState)))
	{
		m_aMouseState = g_CurrentMouseState;
	}

	else
	{
		m_pDevice->Acquire();				//キーボードへのアクセス権を獲得
	}

	GetCursorPos(&Pos);

	// スクリーン座標をクライアント座標に変換する
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &Pos);

	Pos.x = Pos.x - 640;
	Pos.y = Pos.y - 360;
}

//========================================================
//マウスのプレス情報を取得
//========================================================
bool CInputMouse::GetPress(MOUSE_BUTTON type)
{
	return (m_aMouseState.rgbButtons[type] & 0x80) ? true : false;
}

//========================================================
//マウスの位置を取得
//========================================================
POINT CInputMouse::GetPos(void)
{
	return Pos;
}

//========================================================
//マウスの移動量を取得
//========================================================
D3DXVECTOR2 CInputMouse::GetMouseMove(void)
{
	return D3DXVECTOR2((float)m_aMouseState.lX, (float)m_aMouseState.lY);
}

//========================================================
// クリックした瞬間の判定
//========================================================
bool CInputMouse::OnMouseDown(MOUSE_BUTTON type)
{
	if (((g_PrevMouseState.rgbButtons[type] & 0x80) ? true : false) == false &&
		((g_CurrentMouseState.rgbButtons[type] & 0x80) ? true : false) == true)
	{
		return true;
	}

	return false;
}