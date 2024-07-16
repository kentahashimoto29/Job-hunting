//========================================================
//
//ウインドウの生成等 (result.cpp)
//Author 橋本賢太
//
//========================================================
#include "result.h"
#include "result_obj2D.h"
#include "manager.h"
#include "object2D.h"
#include "fade.h"

#define OBJ_MAX (1)

//========================================================
//静的メンバ変数
//========================================================
CRanking *CResult::m_pRanking = NULL;
CResult_Obj2D *CResult::m_apResultObj = NULL;
int CResult::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CResult::CResult()
{

}

//========================================================
//デストラクタ
//========================================================
CResult::~CResult()
{

}

//========================================================
//初期化処理
//========================================================
HRESULT CResult::Init(void)
{
	m_apResultObj = CResult_Obj2D::Create();
	m_pRanking = CRanking::Create();

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CResult::Uninit(void)
{
	//NULLチェック
	if (m_apResultObj != NULL)
	{
		//終了処理
		m_apResultObj->Uninit();
		m_apResultObj = NULL;
	}

	//NULLチェック
	if (m_pRanking != NULL)
	{
		//終了処理
		m_pRanking->Uninit();
		m_pRanking = NULL;
	}

	CScene::Uninit();
}

//========================================================
//更新処理
//========================================================
void CResult::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//マウスの取得
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	 if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		 if (CManager::GetInstance()->GetFade()->GetState() == CFade::FADE_NONE)
		 {
			 CManager::GetInstance()->GetFade()->SetFade(CManager::GetInstance()->GetScene()->MODE_TITLE);
			 b = true;
		 }
	}
}

//========================================================
//描画処理
//========================================================
void CResult::Draw(void)
{
	m_apResultObj->Draw();
	m_pRanking->Draw();
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CResult::GetPos(void)
{
	return m_pos;
}

//========================================================
//ランキングのポインタを返す関数
//========================================================
CRanking *CResult::GetRanking(void)
{
	return m_pRanking;
}
