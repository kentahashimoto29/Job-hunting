//========================================================
//
//�E�C���h�E�̐����� (score.cpp)
//Author ���{����
//
//========================================================
#include "score.h"
#include "manager.h"

int CScore::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CScore::CScore()
{
	m_nScore = 0;
}

//========================================================
//�f�X�g���N�^
//========================================================
CScore::~CScore()
{

}

//========================================================
//��������
//========================================================
CScore *CScore::Create()
{
	CScore *pScore;

	//2D�I�u�W�F�N�g�̐���
	pScore = new CScore();

	//����������
	pScore->Init();

	return pScore;
}

//========================================================
//����������
//========================================================
HRESULT CScore::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\number000.png" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\number000.png");
	}

	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = new CObject2D;

		m_apObject2D[nCnt]->Init();

		m_apObject2D[nCnt]->BindTexture(m_nIdxTexture);
	}

	SetScore(m_nScore);

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Uninit();
	}
}

//========================================================
//�X�V����
//========================================================
void CScore::Update(void)
{

}

//========================================================
//�`�揈��
//========================================================
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}
}

//========================================================
//�ݒ菈��
//========================================================
void CScore::SetScore(int nScore)
{
	m_aTexU[0] = nScore / 10000000;
	m_aTexU[1] = nScore % 10000000 / 1000000;
	m_aTexU[2] = nScore % 1000000 / 100000;
	m_aTexU[3] = nScore % 100000 / 10000;
	m_aTexU[4] = nScore % 10000 / 1000;
	m_aTexU[5] = nScore % 1000 / 100;
	m_aTexU[6] = nScore % 100 / 10;
	m_aTexU[7] = nScore % 10;

	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->SetVtxScore(m_aTexU[nCnt], nCnt);
	}
}

//========================================================
//�X�R�A�̉��Z
//========================================================
void CScore::AddScore(int nValae)
{
	m_nScore += nValae;

	m_aTexU[0] = m_nScore / 10000000;
	m_aTexU[1] = m_nScore % 10000000 / 1000000;
	m_aTexU[2] = m_nScore % 1000000 / 100000;
	m_aTexU[3] = m_nScore % 100000 / 10000;
	m_aTexU[4] = m_nScore % 10000 / 1000;
	m_aTexU[5] = m_nScore % 1000 / 100;
	m_aTexU[6] = m_nScore % 100 / 10;
	m_aTexU[7] = m_nScore % 10;

	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->SetVtxScore(m_aTexU[nCnt], nCnt);
	}
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CScore::GetPos(void)
{
	return m_pos;
}


//========================================================
//�ʒu��Ԃ�
//========================================================
void CScore::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CScore::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}