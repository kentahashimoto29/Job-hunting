//========================================================
//
//ウインドウの生成等 (score.cpp)
//Author 橋本賢太
//
//========================================================
#include "title.h"
#include "title_obj2D.h"
#include "object2D.h"
#include "fade.h"

//========================================================
//静的メンバ変数
//========================================================
CTitle_Obj2D *CTitle::m_apTitleObj = NULL;
int CTitle::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CTitle::CTitle()
{
	b = false;
}

//========================================================
//デストラクタ
//========================================================
CTitle::~CTitle()
{

}

//========================================================
//初期化処理
//========================================================
HRESULT CTitle::Init(void)
{
	m_apTitleObj = CTitle_Obj2D::Create();

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CTitle::Uninit(void)
{
	m_apTitleObj->Uninit();
	CScene::Uninit();
}

//========================================================
//更新処理
//========================================================
void CTitle::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//マウスの取得
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	 if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (b != true)
		{
			if (CManager::GetInstance()->GetFade()->GetState() == CFade::FADE_NONE)
			{
				CManager::GetInstance()->GetFade()->SetFade(CManager::GetInstance()->GetScene()->MODE_GAME);
				b = true;
			}
		}
	}
}

//========================================================
//描画処理
//========================================================
void CTitle::Draw(void)
{
	m_apTitleObj->Draw();
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CTitle::GetPos(void)
{
	return m_pos;
}

//========================================================
//位置を返す
//========================================================
void CTitle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//位置を返す
//========================================================
void CTitle::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}