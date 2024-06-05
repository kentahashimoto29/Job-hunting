//========================================================
//
//ウインドウの生成等 (score.cpp)
//Author 橋本賢太
//
//========================================================
#include "ranking.h"
#include "manager.h"
#include "game.h"

int CRanking::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CRanking::CRanking()
{
	m_nRankingScore[RANKING_MAX] = {};
}

//========================================================
//デストラクタ
//========================================================
CRanking::~CRanking()
{

}

//========================================================
//生成処理
//========================================================
CRanking *CRanking::Create()
{
	CRanking *pScore;

	//2Dオブジェクトの生成
	pScore = new CRanking();

	//初期化処理
	pScore->Init();

	return pScore;
}

//========================================================
//初期化処理
//========================================================
HRESULT CRanking::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\number000.png" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			m_nIdxTexture = nCnt;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\number000.png");
	}

	for (int nCnt = 0; nCnt < NUMBER_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = new CObject2D;

		m_apObject2D[nCnt]->Init();

		m_apObject2D[nCnt]->BindTexture(m_nIdxTexture);
	}



	FILE *pFile;	//ファイルポインタを宣言

					//ファイルを開く
	pFile = fopen("data\\ranking.txt", "r");			//(ファイル名を指定,　モードの指定”r”で読み込み)

													//NULLチェック
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
		{
			fscanf(pFile, "%d", &m_nRankingScore[nCnt]);
		}

		int CurScore = CGame::GetTime()->GetInitTime() - CGame::GetTime()->GetTime();

		for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
		{
			if (CurScore < m_nRankingScore[nCnt])
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
	}

	//ファイルを開く
	pFile = fopen("data\\ranking.txt", "w");			//(ファイル名を指定,　モードの指定”w”で書き込み)

														//NULLチェック
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
		{
			fprintf(pFile, "%d\n", m_nRankingScore[nCnt]);
		}
	}

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CRanking::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUMBER_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Uninit();
	}
}

//========================================================
//更新処理
//========================================================
void CRanking::Update(void)
{

}

//========================================================
//描画処理
//========================================================
void CRanking::Draw(void)
{
	for (int nCnt = 0; nCnt < SCORE_NUM; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}
}

//========================================================
//設定処理
//========================================================
void CRanking::SetScore(int nScore, int nCntR)
{

	m_aTexU[0] = nScore % 1000 / 100;
	m_aTexU[1] = nScore % 100 / 10;
	m_aTexU[2] = nScore % 10;

	for (int nCnt = 0; nCnt < SCORE_NUM; nCnt++)
	{
		m_apObject2D[nCnt + 3 * nCntR]->SetVtxRanking(m_aTexU[nCnt], nCnt, nCntR);
	}
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CRanking::GetPos(void)
{
	return m_pos;
}

//========================================================
//位置を返す
//========================================================
void CRanking::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//位置を返す
//========================================================
void CRanking::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}