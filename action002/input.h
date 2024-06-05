//========================================================
//
//ウインドウの生成等 (input.h)
//Author 橋本賢太
//
//========================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//===================================
//入力のクラス
//===================================
class CInput
{
public:
	CInput();						//コンストラクタ
	virtual ~CInput();				//デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	virtual void Uninit(void);									//終了処理
	virtual void Update(void) = 0;								//更新処理

protected:
	static LPDIRECTINPUT8 m_pInput;			//キーボードのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevice;			//デバイスのポインタ
};

//===================================
//キーボードのクラス
//===================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();				//コンストラクタ
	~CInputKeyboard();				//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	bool GetPress(int nKey);							//キーボードのプレス情報を取得
	bool GetTrigger(int nKey);							//キーボードのトリガー情報を取得

private:
	BYTE m_aKeyState[256];								//キーボードの情報
	BYTE m_aKeyStateTrigger[256];						//キーボードのトリガー情報
};

//===================================
//マウスのクラス
//===================================
class CInputMouse : public CInput
{
public:
	typedef enum
	{
		TYPE_LEFT = 0,
		TYPE_RIGHT,
		TYPE_WHEEL,
		TYPE_MAX,
	}MOUSE_BUTTON;

	CInputMouse();				//コンストラクタ
	~CInputMouse();				//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	bool GetPress(MOUSE_BUTTON type);					//キーボードのプレス情報を取得
	POINT GetPos(void);
	D3DXVECTOR2 GetMouseMove(void);

	bool OnMouseDown(MOUSE_BUTTON type);

private:
	static DIMOUSESTATE g_CurrentMouseState;
	static DIMOUSESTATE g_PrevMouseState;

	DIMOUSESTATE m_aMouseState;
	POINT Pos;
};
#endif