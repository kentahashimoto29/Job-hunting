//========================================================
//
//ウインドウの生成等 (score.cpp)
//Author 橋本賢太
//
//========================================================
#include "title.h"
#include "manager.h"
#include "object2D.h"
#include "fade.h"

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
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\イヴェルカーナ.png" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\イヴェルカーナ.png");
	}

	m_apObject2D[0] = new CObject2D;

	m_apObject2D[0]->BindTexture(m_nIdxTexture);

	m_apObject2D[0]->Init();

	m_apObject2D[0]->SetVtxResult();

	m_apObject2D[0]->SetType(CObject::TYPE_TITLE);

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CTitle::Uninit(void)
{
	m_apObject2D[0]->Uninit();
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
	m_apObject2D[0]->Draw();
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