//========================================================
//
//�E�C���h�E�̐����� (score.cpp)
//Author ���{����
//
//========================================================
#include "ranking.h"
#include "manager.h"
#include "game.h"

//========================================================
//�ÓI�����o�ϐ�
//========================================================
int CRanking::CurScore = 0;
int CRanking::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CRanking::CRanking()
{
	m_nRankingScore[RANKING_MAX] = {};
}

//========================================================
//�f�X�g���N�^
//========================================================
CRanking::~CRanking()
{

}

//========================================================
//��������
//========================================================
CRanking *CRanking::Create()
{
	CRanking *pScore;

	//2D�I�u�W�F�N�g�̐���
	pScore = new CRanking();

	//����������
	pScore->Init();

	return pScore;
}

//========================================================
//����������
//========================================================
HRESULT CRanking::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\number_blackclover_07.png" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			m_nIdxTexture = nCnt;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\number_blackclover_07.png");
	}

	for (int nCnt = 0; nCnt < NUMBER_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = new CObject2D;

		m_apObject2D[nCnt]->Init();

		m_apObject2D[nCnt]->BindTexture(m_nIdxTexture);
	}



	FILE *pFile;	//�t�@�C���|�C���^��錾

					//�t�@�C�����J��
	pFile = fopen("data\\TEXT\\ranking.txt", "r");			//(�t�@�C�������w��,�@���[�h�̎w��hr�h�œǂݍ���)

													//NULL�`�F�b�N
	if (pFile != NULL)
	{
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
	}

	fclose(pFile);

	//�t�@�C�����J��
	pFile = fopen("data\\TEXT\\ranking.txt", "w");			//(�t�@�C�������w��,�@���[�h�̎w��hw�h�ŏ�������)

														//NULL�`�F�b�N
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
//�I������
//========================================================
void CRanking::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUMBER_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Uninit();
	}

	Release();
}

//========================================================
//�X�V����
//========================================================
void CRanking::Update(void)
{

}

//========================================================
//�`�揈��
//========================================================
void CRanking::Draw(void)
{
	for (int nCnt = 0; nCnt < NUMBER_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}
}

//========================================================
//�ݒ菈��
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
//����̃X�R�A�ݒ菈��
//========================================================
void CRanking::SetCurScore(int nScore)
{
	CurScore = nScore;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CRanking::GetPos(void)
{
	return m_pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CRanking::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CRanking::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}