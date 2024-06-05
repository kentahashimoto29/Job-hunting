//========================================================
//
//ウインドウの生成等 (Renderer.h)
//Author 橋本賢太
//
//========================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

//===================================
//レンラダーのクラス
//===================================
class CRenderer
{
public:
	CRenderer();							//コンストラクタ
	~CRenderer();							//デストラクタ

	HRESULT Init(HWND hWnd, BOOL bWindow);	//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	LPDIRECT3DDEVICE9 GetDevice(void);		//デバイスを返す

	LPD3DXFONT GetFont(void);

	void DrawFPS(void);

private:
	LPDIRECT3D9 m_pD3D;						//Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;			//Direct3Dデバイスへのポインタ

	LPD3DXFONT m_pFont;

	int m_nCountFPS;
};

#endif