//========================================================
//
//ウインドウの生成等 (Manager.cpp)
//Author 橋本賢太
//
//========================================================
#include "manager.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"

//マクロ定義
#define BG_MAX									(3)		//背景の最大数

CManager *CManager::m_pManager = NULL;

//========================================================
//コンストラクタ
//========================================================
CManager::CManager()
{
	m_pRenderer = NULL;
	m_pInputKeyboard = NULL;
	m_pInputMouse = NULL;
	m_pTexture = NULL;
	m_pCamera = NULL;
	m_pLight = NULL;
	m_pScene = NULL;
	m_pSound = NULL;
}

//========================================================
//デストラクタ
//========================================================
CManager::~CManager()
{

}

//========================================================
//初期化処理
//========================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//NULLチェック
	if (m_pRenderer == NULL)
	{
		//レンダラーの生成
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != NULL)
	{
		//初期化処理
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//初期化処理が失敗した場合
			return -1;
		}
	}

	//NULLチェック
	if (m_pInputKeyboard == NULL)
	{
		//キーボードの生成
		m_pInputKeyboard = new CInputKeyboard;
	}

	if (m_pInputKeyboard != NULL)
	{
		//初期化処理
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{//初期化処理が失敗した場合
			return -1;
		}
	}

	//NULLチェック
	if (m_pInputMouse == NULL)
	{
		//キーボードの生成
		m_pInputMouse = new CInputMouse;
	}

	if (m_pInputMouse != NULL)
	{
		//初期化処理
		if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
		{//初期化処理が失敗した場合
			return -1;
		}
	}

	//NULLチェック
	if (m_pSound == NULL)
	{
		//キーボードの生成
		m_pSound = new CSound;
	}

	if (m_pSound != NULL)
	{
		//初期化処理
		if (FAILED(m_pSound->Init(hWnd)))
		{//初期化処理が失敗した場合
			return -1;
		}
	}

	m_pTexture = new CTexture;

	//フェードの生成
	m_pFade = new CFade;
	m_pFade->Init();

	//ライトの生成
	m_pLight = new CLight;
	m_pLight->Init();

	//カメラの生成
	m_pCamera = new CCamera;
	m_pCamera->Init();

	SetMode(GetScene()->MODE_TITLE);

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CManager::Uninit(void)
{
	//NULLチェック
	if (m_pRenderer != NULL)
	{
		//終了処理
		m_pRenderer->Uninit();

		delete m_pRenderer;

		m_pRenderer = NULL;
	}

	//NULLチェック
	if (m_pInputKeyboard != NULL)
	{
		//終了処理
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;

		m_pInputKeyboard = NULL;
	}

	//NULLチェック
	if (m_pCamera != NULL)
	{
		//終了処理
		m_pCamera->Uninit();

		delete m_pCamera;

		m_pCamera = NULL;
	}

	//NULLチェック
	if (m_pLight != NULL)
	{
		//終了処理
		m_pLight->Uninit();

		delete m_pLight;

		m_pLight = NULL;
	}
}

//========================================================
//更新処理
//========================================================
void CManager::Update(void)
{
	//更新処理
	m_pFade->Update();
	m_pCamera->Update();
	//m_pScene->Update();
	m_pRenderer->Update();
	m_pInputKeyboard->Update();
	m_pInputMouse->Update();
}

//========================================================
//描画処理
//========================================================
void CManager::Draw(void)
{
	//描画処理
	m_pFade->Draw();
	m_pRenderer->Draw();
}

//========================================================
//マネージャーのポインタを返す関数
//========================================================
CManager *CManager::GetInstance(void)
{
	if (m_pManager == NULL)
	{
		return m_pManager = new CManager;
	}

	else
	{
		return m_pManager;
	}
}

//========================================================
//レンラダーのポインタを返す関数
//========================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//========================================================
//キーボードのポインタを返す関数
//========================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//========================================================
//キーボードのポインタを返す関数
//========================================================
CInputMouse *CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//========================================================
//テクスチャのポインタを返す関数
//========================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}

//========================================================
//カメラのポインタを返す関数
//========================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//========================================================
//ライトのポインタを返す関数
//========================================================
CLight *CManager::GetLight(void)
{
	return m_pLight;
}

//========================================================
//シーンのポインタを返す関数
//========================================================
CScene *CManager::GetScene(void)
{
	return m_pScene;
}

//========================================================
//サウンドのポインタを返す関数
//========================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//========================================================
//サウンドのポインタを返す関数
//========================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}

//========================================================
//モード設定
//========================================================
void CManager::SetMode(CScene::MODE Mode)
{
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();

		m_pScene = NULL;

		m_pFade->SetFade(Mode);
	}

	else
	{
		m_pFade->SetFadeFirst(Mode);
	}


	/*if (Mode == CScene::MODE_RESULT)
	{
		CObject::ReleaseAll();
	}*/


	if (m_pScene == NULL)
	{
		m_pScene = CScene::Create(Mode);
	}
}



//========================================================
//コンストラクタ
//========================================================
CScene::CScene()
{

}

//========================================================
//コンストラクタ
//========================================================
CScene::CScene(MODE Mode)
{
	m_mode = Mode;
}

//========================================================
//デストラクタ
//========================================================
CScene::~CScene()
{

}

//========================================================
//生成処理
//========================================================
CScene *CScene::Create(MODE Mode)
{
	CScene *pScene = NULL;

	//2Dオブジェクトの生成
	switch (Mode)
	{
	case MODE_TITLE:
		pScene = new CTitle;
		break;

	case MODE_GAME:
		pScene = new CGame;
		break;

	case MODE_RESULT:
		pScene = new CResult;
		break;

	default:
		break;
	}

	//初期化処理
	pScene->Init();

	pScene->m_mode = Mode;

	return pScene;
}

//========================================================
//初期化処理
//========================================================
HRESULT CScene::Init()
{

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CScene::Uninit(void)
{
	Release();
}

//========================================================
//更新処理
//========================================================
void CScene::Update(void)
{
	
}

//========================================================
//描画処理
//========================================================
void CScene::Draw(void)
{

}

//========================================================
//モードを返す関数
//========================================================
CScene::MODE CScene::GetMode(void)
{
	return m_mode;
}

//========================================================
//モードを返す関数
//========================================================
void CScene::SetMode(MODE Mode)
{
	m_mode = Mode;
}

//========================================================
//位置を返す関数
//========================================================
D3DXVECTOR3 CScene::GetPos(void)
{
	return pos;
}

//========================================================
//位置を返す
//========================================================
void CScene::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//位置を返す
//========================================================
void CScene::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}