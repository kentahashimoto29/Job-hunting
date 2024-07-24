//========================================================
// 
// �E�C���h�E�̐����� (score.cpp)
// Author ���{����
// 
//========================================================
#include "score.h"
#include "manager.h"
#include "ranking.h"

int CScore::m_nIdxTexture = 0;

//========================================================
// �R���X�g���N�^
//========================================================
CScore::CScore()
{
	m_nScore = 0;
}

//========================================================
// �f�X�g���N�^
//========================================================
CScore::~CScore()
{

}

//========================================================
// ��������
//========================================================
CScore *CScore::Create()
{
	CScore *pScore;

	// 2D�I�u�W�F�N�g�̐���
	pScore = new CScore();

	// ����������
	pScore->Init();

	return pScore;
}

//========================================================
// ����������
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
// �I������
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
// �X�V����
//========================================================
void CScore::Update(void)
{

}

//========================================================
// �`�揈��
//========================================================
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}
}

//========================================================
// �ݒ菈��
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
// �X�R�A�̉��Z
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
	{// �X�R�A�̒��_���W��ݒ�
		m_apObject2D[nCnt]->SetVtxScore(m_aTexU[nCnt], nCnt);
	}
}

//========================================================
// �ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CScore::GetPos(void)
{
	return m_pos;
}


//========================================================
// �ʒu��Ԃ�
//========================================================
void CScore::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CScore::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}