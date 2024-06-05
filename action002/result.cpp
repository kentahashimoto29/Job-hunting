//========================================================
//
//ウインドウの生成等 (score.cpp)
//Author 橋本賢太
//
//========================================================
#include "result.h"
#include "manager.h"
#include "object2D.h"
#include "fade.h"

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
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\Goal001.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Goal001.jpg");
	}

	m_apObject2D[0] = new CObject2D;

	m_apObject2D[0]->BindTexture(m_nIdxTexture);

	m_apObject2D[0]->Init();

	m_apObject2D[0]->SetVtxResult();

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CResult::Uninit(void)
{
	m_apObject2D[0]->Uninit();
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
	m_apObject2D[0]->Draw();
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CResult::GetPos(void)
{
	return m_pos;
}