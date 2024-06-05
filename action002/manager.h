//========================================================
//
//ウインドウの生成等 (Manager.h)
//Author 橋本賢太
//
//========================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "object3D.h"
#include "sound.h"
class CFade;



//===================================
//シーンクラス
//===================================
class CScene : public CObject
{
public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}MODE;

	CScene();					//コンストラクタ
	CScene(MODE Mode);			//コンストラクタ
	~CScene();					//デストラクタ

	static CScene *Create(MODE Mode);			//生成処理

	HRESULT Init();								//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	MODE GetMode(void);
	void SetMode(MODE Mode);

	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

private:
	MODE m_mode;

	D3DXVECTOR3 pos;
};


//===================================
//マネージャのクラス
//===================================
class CManager
{
public:
	CManager();					//コンストラクタ
	~CManager();				//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	//初期化処理
	void Uninit(void);											//終了処理
	void Update(void);											//更新処理
	void Draw(void);											//描画処理

	static CManager *GetInstance();								//マネージャーのポインタを返す関数
	CRenderer *GetRenderer();									//レンラダーのポインタを返す関数
	CInputKeyboard *GetInputKeyboard();							//キーボードのポインタを返す関数
	CInputMouse *GetInputMouse();								//マウスのポインタを返す関数
	CTexture *GetTexture();										//テクスチャのポインタを返す関数
	CCamera *GetCamera();										//カメラのポインタを返す関数
	CLight *GetLight();											//ライトのポインタを返す関数
	CScene *GetScene();											//シーンのポインタを返す関数
	CSound *GetSound();											//サウンドのポインタを返す関数
	CFade *GetFade();											//フェードのポインタを返す関数

	void SetMode(CScene::MODE Mode);

private:
	static CManager *m_pManager;								//マネージャーのポインタ
	CRenderer *m_pRenderer;										//レンラダーのポインタ
	CInputKeyboard *m_pInputKeyboard;							//キーボードのポインタ
	CInputMouse *m_pInputMouse;									//マウスのポインタ
	CTexture *m_pTexture;										//テクスチャのポインタ
	CCamera *m_pCamera;											//カメラのポインタ
	CLight *m_pLight;											//ライトのポインタ
	CScene *m_pScene;											//シーンのポインタ
	CSound *m_pSound;											//サウンドのポインタ
	CFade *m_pFade;												//フェードのポインタ

};


#endif