//========================================================
// 
// ウインドウの生成等 (score.cpp)
// Author 橋本賢太
// 
//========================================================
#include "score.h"
#include "manager.h"
#include "ranking.h"

int CScore::m_nIdxTexture = 0;

//========================================================
// コンストラクタ
//========================================================
CScore::CScore()
{
	m_nScore = 0;
}

//========================================================
// デストラクタ
//========================================================
CScore::~CScore()
{

}

//========================================================
// 生成処理
//========================================================
CScore *CScore::Create()
{
	CScore *pScore;

	// 2Dオブジェクトの生成
	pScore = new CScore();

	// 初期化処理
	pScore->Init();

	return pScore;
}

//========================================================
// 初期化処理
//========================================================
HRESULT CScore::Init(void)
{
	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = new CObject2D;

		m_apObject2D[nCnt]->Init();

		m_apObject2D[nCnt]->SetPos(D3DXVECTOR3(880.0f, 70.0f, 0.0f));

		m_apObject2D[nCnt]->SetSizeX(40.0f);
		m_apObject2D[nCnt]->SetSizeY(50.0f);

		m_nIdxTexture = m_apObject2D[nCnt]->SetTex("data\\TEXTURE\\number_blackclover_07.png");

		m_apObject2D[nCnt]->BindTexture(m_nIdxTexture);
	}

	m_nScore = 0;

	SetScore(m_nScore);

	return S_OK;
}

//========================================================
// 終了処理
//========================================================
void CScore::Uninit(void)
{
	CRanking::SetCurScore(m_nScore);

	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Uninit();
	}

	Release();
}

//========================================================
// 更新処理
//========================================================
void CScore::Update(void)
{

}

//========================================================
// 描画処理
//========================================================
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}
}

//========================================================
// 設定処理
//========================================================
void CScore::SetScore(int nScore)
{
	int n = 1;

	for (int i = 0; i < SCORE_MAX - 1; i++)
	{
		n = n * 10;
	}

	for (int i = 0; i < SCORE_MAX; i++)
	{
		switch (i)
		{
		case 0:
			m_aTexU[i] = m_nScore / n;

			break;

		case SCORE_MAX:
			m_aTexU[i] = m_nScore % n;

			break;

		default:
			m_aTexU[i] = m_nScore % n / (n / 10);

			n = n / 10;

			break;
		}
	}

	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->SetVtxScore(m_aTexU[nCnt], nCnt);
	}
}

//========================================================
// スコアの加算
//========================================================
void CScore::AddScore(int nValae)
{
	int n = 1;

	m_nScore += nValae;

	for (int i = 0; i < SCORE_MAX - 1; i++)
	{
		n = n * 10;
	}

	for (int i = 0; i < SCORE_MAX; i++)
	{
		switch (i)
		{
		case 0:
			m_aTexU[i] = m_nScore / n;

			break;

		case SCORE_MAX:
			m_aTexU[i] = m_nScore % n;

			break;

		default:
			m_aTexU[i] = m_nScore % n / (n / 10);

			n = n / 10;

			break;
		}
	}

	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{// スコアの頂点座標を設定
		m_apObject2D[nCnt]->SetVtxScore(m_aTexU[nCnt], nCnt);
	}
}

//========================================================
// 位置を返す
//========================================================
D3DXVECTOR3 CScore::GetPos(void)
{
	return m_pos;
}


//========================================================
// 位置を返す
//========================================================
void CScore::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// 位置を返す
//========================================================
void CScore::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}