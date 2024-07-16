//========================================================
//
// �E�C���h�E�̐����� (score.cpp)
// Author ���{����
//
//========================================================
#include "ranking.h"
#include "manager.h"
#include "game.h"

//========================================================
// �ÓI�����o�ϐ�
//========================================================
int CRanking::CurScore = 0;
int CRanking::m_nIdxTexture = 0;

//========================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//========================================================
CRanking::~CRanking()
{

}

//========================================================
// ��������
//========================================================
CRanking *CRanking::Create()
{
	CRanking *pRanking;

	// 2D�I�u�W�F�N�g�̐���
	pRanking = new CRanking();

	// ����������
	pRanking->Init();

	return pRanking;
}

//========================================================
// ����������
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

	FILE *pFile;	// �t�@�C���|�C���^��錾

					// �t�@�C�����J��
	pFile = fopen("data\\TEXT\\ranking.txt", "r");			//(�t�@�C�������w��,�@���[�h�̎w��hr�h�œǂݍ���)

	// NULL�`�F�b�N
	if (pFile != NULL)
	{
		// ����̃X�R�A��ێ�
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
			// ����̃X�R�A�������L���O�ɓ����Ă����ꍇ
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

	// �t�@�C�����J��
	pFile = fopen("data\\TEXT\\ranking.txt", "w");			// (�t�@�C�������w��,�@���[�h�̎w��hw�h�ŏ�������)

														// NULL�`�F�b�N
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
// �I������
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
// �X�V����
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
// �`�揈��
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
// �ݒ菈��
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
// ����̃X�R�A�ݒ菈��
//========================================================
void CRanking::SetCurScore(int nScore)
{
	CurScore = nScore;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CRanking::GetPos(void)
{
	return m_pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CRanking::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CRanking::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================================================
// �_�ŏ���
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
