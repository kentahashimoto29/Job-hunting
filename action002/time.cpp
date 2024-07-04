//========================================================
//
//�E�C���h�E�̐����� (score.cpp)
//Author ���{����
//
//========================================================
#include "time.h"
#include "manager.h"

int CTime::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CTime::CTime(int nPriority) : CObject(nPriority)
{
	m_nTime = 30;
	m_nInitTime = m_nTime;
}

//========================================================
//�f�X�g���N�^
//========================================================
CTime::~CTime()
{

}

//========================================================
//��������
//========================================================
CTime *CTime::Create()
{
	CTime *pTime;

	//2D�I�u�W�F�N�g�̐���
	pTime = new CTime();

	//����������
	pTime->Init();

	return pTime;
}

//========================================================
//����������
//========================================================
HRESULT CTime::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\number_blackclover_07.png" == pTexture->GetName(nCnt))
		{
			m_nIdxTexture = nCnt;
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\number_blackclover_07.png");
	}

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = new CObject2D();

		m_apObject2D[nCnt]->Init();

		m_apObject2D[nCnt]->BindTexture(m_nIdxTexture);
	}

	SetType(CObject::TYPE_TIME);

	SetTime(m_nTime);

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Uninit();
	}

	Release();
}

//========================================================
//�X�V����
//========================================================
void CTime::Update(void)
{

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		SetTime(m_nTime);
	}

	m_nSecondCount++;

	if (m_nSecondCount >= 60)
	{
		m_nSecondCount = 0;

		m_nTime--;

		if (m_nTime <= 0)
		{
			m_nTime = 0;
		}
	}
}

//========================================================
//�`�揈��
//========================================================
void CTime::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->AlphaTestValid();

		m_apObject2D[nCnt]->Draw();

		m_apObject2D[nCnt]->AlphaTestInvalid();
	}
}

//========================================================
//�ݒ菈��
//========================================================
void CTime::SetTime(int nTime)
{
	m_aTexU[0] = nTime % 1000 / 100;
	m_aTexU[1] = nTime % 100 / 10;
	m_aTexU[2] = nTime % 10;

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->SetVtxTime(m_aTexU[nCnt], nCnt);
	}
}

//========================================================
//�ݒ菈��
//========================================================
int CTime::GetTime(void)
{
	return m_nTime;
}

//========================================================
//�ݒ菈��
//========================================================
int CTime::GetInitTime(void)
{
	return m_nInitTime;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CTime::GetPos(void)
{
	return m_pos;
}


//========================================================
//�ʒu��Ԃ�
//========================================================
void CTime::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//========================================================
//�ʒu��Ԃ�
//========================================================
void CTime::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}