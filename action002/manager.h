//========================================================
//
//ウインドウの生成等 (manager.h)
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
#include "Xmodel.h"
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

	static CManager *GetInstance();									//マネージャーのポインタを返す関数
	CRenderer *GetRenderer() { return m_pRenderer; }				//レンラダーのポインタを返す関数
	CInputKeyboard *GetInputKeyboard() { return m_pInputKeyboard; }	//キーボードのポインタを返す関数
	CInputMouse *GetInputMouse() { return m_pInputMouse; }			//マウスのポインタを返す関数
	CTexture *GetTexture() { return m_pTexture; }					//テクスチャのポインタを返す関数
	CXmodel *GetXmodel() { return m_pXmodel; }						//Xモデルのポインタを返す関数
	CCamera *GetCamera() { return m_pCamera; }						//カメラのポインタを返す関数
	CLight *GetLight() { return m_pLight; }							//ライトのポインタを返す関数
	CScene *GetScene() { return m_pScene; }							//シーンのポインタを返す関数
	CSound *GetSound() { return m_pSound; }							//サウンドのポインタを返す関数
	CFade *GetFade() { return m_pFade; }							//フェードのポインタを返す関数

	void SetMode(CScene::MODE Mode);

private:
	static CManager *m_pManager;								//マネージャーのポインタ
	CRenderer *m_pRenderer;										//レンラダーのポインタ
	CInputKeyboard *m_pInputKeyboard;							//キーボードのポインタ
	CInputMouse *m_pInputMouse;									//マウスのポインタ
	CTexture *m_pTexture;										//テクスチャのポインタ
	CXmodel *m_pXmodel;											//Xモデルのポインタ
	CCamera *m_pCamera;											//カメラのポインタ
	CLight *m_pLight;											//ライトのポインタ
	CScene *m_pScene;											//シーンのポインタ
	CSound *m_pSound;											//サウンドのポインタ
	CFade *m_pFade;												//フェードのポインタ

};


#endif