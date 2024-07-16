//========================================================
//
// ウインドウの生成等 (score.cpp)
// Author 橋本賢太
//
//========================================================
#include "ranking.h"
#include "manager.h"
#include "game.h"

//========================================================
// 静的メンバ変数
//========================================================
int CRanking::CurScore = 0;
int CRanking::m_nIdxTexture = 0;

//========================================================
// コンストラクタ
//========================================================
CRanking::CRanking()
{
	m_nRankingScore[RANKING_MAX] = {};
	m_nNewRec = -1;
	m_bNewRec = false;
	m_Alpha = 0.0f;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//========================================================
// デストラクタ
//========================================================
CRanking::~CRanking()
{

}

//========================================================
// 生成処理
//========================================================
CRanking *CRanking::Create()
{
	CRanking *pRanking;

	// 2Dオブジェクトの生成
	pRanking = new CRanking();

	// 初期化処理
	pRanking->Init();

	return pRanking;
}

//========================================================
// 初期化処理
//========================================================
HRESULT CRanking::Init(void)
{
	for (int nCnt = 0; nCnt < NUMBER_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = new CObject2D;

		m_apObject2D[nCnt]->Init();

		m_apObject2D[nCnt]->SetPos(D3DXVECTOR3(620.0f, 110.0f, 0.0f));

		m_nIdxTexture = m_apObject2D[nCnt]->SetTex("data\\TEXTURE\\number_blackclover_07.png");

		m_apObject2D[nCnt]->BindTexture(m_nIdxTexture);
	}

	for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
	{
		m_apObject2DRank[nCnt] = new CObject2D;

		m_apObject2DRank[nCnt]->Init();

		m_apObject2DRank[nCnt]->SetPos(m_apObject2D[nCnt]->m_pos);

		m_apObject2DRank[nCnt]->SetVtxRanking(nCnt + 1, nCnt);

		m_nIdxTexture = m_apObject2DRank[nCnt]->SetTex("data\\TEXTURE\\number_blackclover_07.png");

		m_apObject2DRank[nCnt]->BindTexture(m_nIdxTexture);
	}

	FILE *pFile;	// ファイルポインタを宣言

					// ファイルを開く
	pFile = fopen("data\\TEXT\\ranking.txt", "r");			//(ファイル名を指定,　モードの指定”r”で読み込み)

	// NULLチェック
	if (pFile != NULL)
	{
		// 今回のスコアを保持
		int nPreScore = CurScore;

		for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
		{
			fscanf(pFile, "%d", &m_nRankingScore[nCnt]);
		}

		for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
		{
			if (CurScore > m_nRankingScore[nCnt])
			{
				int nData = m_nRankingScore[nCnt];

				m_nRankingScore[nCnt] = CurScore;

				CurScore = nData;
			}
		}

		for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
		{
			SetScore(m_nRankingScore[nCnt], nCnt);
		}

		for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
		{
			// 今回のスコアがランキングに入っていた場合
			if (nPreScore == m_nRankingScore[nCnt])
			{
				//m_apObject2D[nCnt * SCORE_NUM]->SetColor(D3DXCOLOR(1.0f, 0.4f, 0.3f, 1.0f));
				//m_apObject2D[nCnt * SCORE_NUM + 1]->SetColor(D3DXCOLOR(1.0f, 0.4f, 0.3f, 1.0f));
				//m_apObject2D[nCnt * SCORE_NUM + 2]->SetColor(D3DXCOLOR(1.0f, 0.4f, 0.3f, 1.0f));

				m_nNewRec = nCnt;
				m_bNewRec = true;

				//m_col = D3DXCOLOR(1.0f, 0.4f, 0.3f, 1.0f);

				m_Alpha = -0.015f;
				break;
			}
		}
	}

	fclose(pFile);

	// ファイルを開く
	pFile = fopen("data\\TEXT\\ranking.txt", "w");			// (ファイル名を指定,　モードの指定”w”で書き込み)

														// NULLチェック
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
		{
			fprintf(pFile, "%d\n", m_nRankingScore[nCnt]);
		}
	}

	fclose(pFile);

	return S_OK;
}

//========================================================
// 終了処理
//========================================================
void CRanking::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUMBER_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Uninit();
	}

	for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
	{
		m_apObject2DRank[nCnt]->Uninit();
	}

	Release();
}

//========================================================
// 更新処理
//========================================================
void CRanking::Update(void)
{
	if (m_bNewRec == true)
	{
		BlinkingCol();

		m_apObject2D[m_nNewRec * SCORE_NUM]->SetColor(m_col);
		m_apObject2D[m_nNewRec * SCORE_NUM + 1]->SetColor(m_col);
		m_apObject2D[m_nNewRec * SCORE_NUM + 2]->SetColor(m_col);
	}
}

//========================================================
// 描画処理
//========================================================
void CRanking::Draw(void)
{
	for (int nCnt = 0; nCnt < NUMBER_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}

	for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
	{
		m_apObject2DRank[nCnt]->Draw();
	}
}

//========================================================
// 設定処理
//========================================================
void CRanking::SetScore(int nScore, int nCntR)
{

	m_aTexU[0] = nScore % 1000 / 100;
	m_aTexU[1] = nScore % 100 / 10;
	m_aTexU[2] = nScore % 10;

	for (int nCnt = 0; nCnt < SCORE_NUM; nCnt++)
	{
		m_apObject2D[nCnt + 3 * nCntR]->SetVtxRankingScore(m_aTexU[nCnt], nCnt, nCntR);
	}
}

//========================================================
// 今回のスコア設定処理
//========================================================
void CRanking::SetCurScore(int nScore)
{
	CurScore = nScore;
}

//========================================================
// 位置を返す
//========================================================
D3DXVECTOR3 CRanking::GetPos(void)
{
	return m_pos;
}

//========================================================
// 位置を返す
//========================================================
void CRanking::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// 位置を返す
//========================================================
void CRanking::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================================================
// 点滅処理
//========================================================
void CRanking::BlinkingCol(void)
{
	if (m_col.a > 1.0f)
	{
		m_col.a = 1.0f;

		m_Alpha = -0.015f;
	}

	else if (m_col.a < 0.2f)
	{
		m_col.a = 0.2f;

		m_Alpha = 0.015f;
	}

	m_col.a += m_Alpha;
}
