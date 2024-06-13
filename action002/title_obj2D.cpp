//========================================================
//
// ウインドウの生成等 (score.cpp)
// Author 橋本賢太
//
//========================================================
#include "title_obj2D.h"
#include "manager.h"
#include "object2D.h"

int CTitle_Obj2D::m_nIdxTexture = 0;

//========================================================
// コンストラクタ
//========================================================
CTitle_Obj2D::CTitle_Obj2D()
{
	m_Alpha = 0.0f;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	b = false;
}

//========================================================
// デストラクタ
//========================================================
CTitle_Obj2D::~CTitle_Obj2D()
{

}

//========================================================
// 生成処理
//========================================================
CTitle_Obj2D *CTitle_Obj2D::Create()
{
	CTitle_Obj2D *pTitleObj;

	//2Dオブジェクトの生成
	pTitleObj = new CTitle_Obj2D();

	//初期化処理
	pTitleObj->Init();

	return pTitleObj;
}

//========================================================
// 初期化処理
//========================================================
HRESULT CTitle_Obj2D::Init(void)
{
	for (int i = 0; i < 2; i++)
	{
		switch (i)
		{
			// 背景
		case 0:
			m_apObject2D[i] = new CObject2D;

			m_nIdxTexture = m_apObject2D[i]->SetTex("data\\TEXTURE\\イヴェルカーナ.png");

			m_apObject2D[i]->BindTexture(m_nIdxTexture);

			m_apObject2D[i]->Init();

			//m_apObject2D[i]->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

			m_apObject2D[i]->SetVtxResult();

			m_apObject2D[i]->SetType(CObject::TYPE_TITLE);
			break;

			// ENTERロゴ
		case 1:
			m_apObject2D[i] = new CObject2D;

			m_nIdxTexture = m_apObject2D[i]->SetTex("data\\TEXTURE\\enemy000.png");

			m_apObject2D[i]->BindTexture(m_nIdxTexture);

			m_apObject2D[i]->Init();

			m_apObject2D[i]->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

			m_apObject2D[i]->SetVtxTitle();

			m_apObject2D[i]->SetType(CObject::TYPE_TITLE);
			break;
		}
	}

	m_Alpha = -0.07f;

	return S_OK;
}

//========================================================
// 終了処理
//========================================================
void CTitle_Obj2D::Uninit(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apObject2D[nCnt]->Uninit();
	}
	Release();
}

//========================================================
// 更新処理
//========================================================
void CTitle_Obj2D::Update(void)
{
	for (int i = 0; i < 2; i++)
	{
		switch (i)
		{
			// ENTERロゴ
		case 1:
			// 点滅処理
			BlinkingCol();
			m_apObject2D[i]->SetColor(m_col);

			break;
		}
	}
}

//========================================================
// 描画処理
//========================================================
void CTitle_Obj2D::Draw(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}
}

//========================================================
// 点滅処理
//========================================================
void CTitle_Obj2D::BlinkingCol(void)
{
	if (m_col.a > 1.0f)
	{
		m_col.a = 1.0f;

		m_Alpha = -0.013f;
	}

	else if (m_col.a < 0.3f)
	{
		m_col.a = 0.3f;

		m_Alpha = 0.013f;
	}

	m_col.a += m_Alpha;
}

//========================================================
// 位置を返す
//========================================================
D3DXVECTOR3 CTitle_Obj2D::GetPos(void)
{
	return m_pos;
}

//========================================================
// 位置を返す
//========================================================
void CTitle_Obj2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// 位置を返す
//========================================================
void CTitle_Obj2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}