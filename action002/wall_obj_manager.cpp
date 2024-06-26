//========================================================
//
//�E�C���h�E�̐����� (bullet.cpp)
//Author ���{����
//
//========================================================
#include <time.h>
#include "wall_obj.h"
#include "wall_obj_manager.h"
#include "game.h"

int CWallObjManager::m_nNum = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CWallObjManager::CWallObjManager()
{
	memset(&m_pWall[0], NULL, sizeof(m_pWall));		// 
	m_nCreCnt = 0;
}

//========================================================
//�f�X�g���N�^
//========================================================
CWallObjManager::~CWallObjManager()
{

}

//========================================================
//��������
//========================================================
CWallObjManager *CWallObjManager::Create()
{
	CWallObjManager *pEnemyManager = NULL;

	//2D�I�u�W�F�N�g�̐���
	pEnemyManager = new CWallObjManager;

	//����������
	pEnemyManager->Init();

	return pEnemyManager;
}

//========================================================
//����������
//========================================================
HRESULT CWallObjManager::Init(void)
{
	SetWall(D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CWallObjManager::Uninit(void)
{
	for (int nCntWall = 0; nCntWall < 16; nCntWall++)
	{
		if (m_pWall[nCntWall] != NULL)
		{
			m_pWall[nCntWall]->Uninit();
			m_pWall[nCntWall] = NULL;

			// �������Z
			m_nNum--;
		}
	}
}

//========================================================
//�X�V����
//========================================================
void CWallObjManager::Update(void)
{
	
}

//==========================================================================
// �j��
//==========================================================================
void CWallObjManager::Release(int nIdx)
{
	if (m_pWall[nIdx] != NULL)
	{
		m_pWall[nIdx] = NULL;
	}

	// �������Z
	m_nNum--;

	CGame::AddScore();
}

//==========================================================================
// �j��
//==========================================================================
void CWallObjManager::Kill(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		if (m_pWall[nCntEnemy] != NULL)
		{
			m_pWall[nCntEnemy]->Uninit();
			m_pWall[nCntEnemy] = NULL;
		}
	}
}

//==========================================================================
// �G�z�u
//==========================================================================
CWallObj **CWallObjManager::SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CWallObj *pWall[16];
	memset(&pWall[0], NULL, sizeof(pWall));

	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		if (m_pWall[nCnt] != NULL)
		{// ��񂪓����Ă���
			continue;
		}



		// �G�̐���
		m_pWall[nCnt] = CWallObj::Create(pos, rot, nCnt);			// ���

		if (m_pWall[nCnt] == NULL)
		{// ���s���Ă�����

			delete m_pWall[nCnt];
			m_pWall[nCnt] = NULL;
			break;
		}

		// �|�C���^�R�s�[
		pWall[nCnt] = m_pWall[nCnt];

		// �������Z
		m_nNum++;
		break;
	}

	return &pWall[0];
}

//========================================================
//�ʒu��Ԃ�
//========================================================
int CWallObjManager::GetNum(void)
{
	return m_nNum;
}

//==========================================================================
// �G�擾
//==========================================================================
CWallObj **CWallObjManager::GetWall(void)
{
	return &m_pWall[0];
}