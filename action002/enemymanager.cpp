//========================================================
//
//�E�C���h�E�̐����� (bullet.cpp)
//Author ���{����
//
//========================================================
#include "enemymanager.h"
#include "game.h"

int CEnemyManager::m_nNum = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CEnemyManager::CEnemyManager()
{
	memset(&m_pEnemy3D[0], NULL, sizeof(m_pEnemy3D));		// 
	m_nCreCnt = 0;
}

//========================================================
//�f�X�g���N�^
//========================================================
CEnemyManager::~CEnemyManager()
{

}

//========================================================
//��������
//========================================================
CEnemyManager *CEnemyManager::Create()
{
	CEnemyManager *pEnemyManager = NULL;

	//2D�I�u�W�F�N�g�̐���
	pEnemyManager = new CEnemyManager;

	//����������
	pEnemyManager->Init();

	return pEnemyManager;
}

//========================================================
//����������
//========================================================
HRESULT CEnemyManager::Init(void)
{
	SetEnemy(D3DXVECTOR3(-200.0f, 0.0f, 200.0f));
	SetEnemy(D3DXVECTOR3(200.0f, 0.0f, 200.0f));

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CEnemyManager::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		if (m_pEnemy3D[nCntEnemy] != NULL)
		{
			m_pEnemy3D[nCntEnemy]->Uninit();
			m_pEnemy3D[nCntEnemy] = NULL;

			// �������Z
			m_nNum--;
		}
	}
}

//========================================================
//�X�V����
//========================================================
void CEnemyManager::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	m_nCreCnt++;

	//W�L�[���������Ƃ�
	if (pInputKeyboard->GetTrigger(DIK_N) == true)
	{
		SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 200.0f));
	}

	if (m_nCreCnt >= 60 * 2)
	{
		SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_nCreCnt = 0;
	}
}

//==========================================================================
// �j��
//==========================================================================
void CEnemyManager::Release(int nIdx)
{
	if (m_pEnemy3D[nIdx] != NULL)
	{
		m_pEnemy3D[nIdx] = NULL;
	}

	// �������Z
	m_nNum--;

	CGame::AddScore();
}

//==========================================================================
// �j��
//==========================================================================
void CEnemyManager::Kill(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		if (m_pEnemy3D[nCntEnemy] != NULL)
		{
			m_pEnemy3D[nCntEnemy]->Uninit();
			m_pEnemy3D[nCntEnemy] = NULL;
		}
	}
}

//==========================================================================
// �G�z�u
//==========================================================================
CEnemy3D **CEnemyManager::SetEnemy(D3DXVECTOR3 pos)
{
	CEnemy3D *pEnemy[16];
	memset(&pEnemy[0], NULL, sizeof(pEnemy));

		for (int nCnt = 0; nCnt < 16; nCnt++)
		{
			if (m_pEnemy3D[nCnt] != NULL)
			{// ��񂪓����Ă���
				continue;
			}



			// �G�̐���
			m_pEnemy3D[nCnt] = CEnemy3D::Create(pos, nCnt);			// ���

			if (m_pEnemy3D[nCnt] == NULL)
			{// ���s���Ă�����

				delete m_pEnemy3D[nCnt];
				m_pEnemy3D[nCnt] = NULL;
				break;
			}

			// �|�C���^�R�s�[
			pEnemy[nCnt] = m_pEnemy3D[nCnt];

			// �������Z
			m_nNum++;
			break;
		}

	return &pEnemy[0];
}

//========================================================
//�ʒu��Ԃ�
//========================================================
int CEnemyManager::GetNum(void)
{
	return m_nNum;
}

//==========================================================================
// �G�擾
//==========================================================================
CEnemy3D **CEnemyManager::GetEnemy(void)
{
	return &m_pEnemy3D[0];
}