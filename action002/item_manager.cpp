//========================================================
// 
// �E�C���h�E�̐����� (item_manager.cpp)
// Author ���{����
// 
//========================================================
#include "item_manager.h"
#include "game.h"

int CItemManager::m_nNum = 0;

//========================================================
// �R���X�g���N�^
//========================================================
CItemManager::CItemManager()
{
	memset(&m_pItemThrow[0], NULL, sizeof(m_pItemThrow));		// 
}

//========================================================
// �f�X�g���N�^
//========================================================
CItemManager::~CItemManager()
{

}

//========================================================
// ��������
//========================================================
CItemManager *CItemManager::Create()
{
	CItemManager *pEnemyManager = NULL;

	// 2D�I�u�W�F�N�g�̐���
	pEnemyManager = new CItemManager;

	// ����������
	pEnemyManager->Init();

	return pEnemyManager;
}

//========================================================
// ����������
//========================================================
HRESULT CItemManager::Init(void)
{
	return S_OK;
}

//========================================================
// �I������
//========================================================
void CItemManager::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		if (m_pItemThrow[nCntEnemy] != NULL)
		{
			m_pItemThrow[nCntEnemy]->Uninit();
			m_pItemThrow[nCntEnemy] = NULL;

			// �������Z
			m_nNum--;
		}
	}
}

//========================================================
// �X�V����
//========================================================
void CItemManager::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// W�L�[���������Ƃ�
	if (pInputKeyboard->GetTrigger(DIK_V) == true)
	{
		SetItemThrow(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//==========================================================================
// �j��
//==========================================================================
void CItemManager::Release(int nIdx)
{
	if (m_pItemThrow[nIdx] != NULL)
	{
		m_pItemThrow[nIdx] = NULL;
	}

	// �������Z
	m_nNum--;

	CGame::AddScore();
}

//==========================================================================
// �j��
//==========================================================================
void CItemManager::Kill(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		if (m_pItemThrow[nCntEnemy] != NULL)
		{
			m_pItemThrow[nCntEnemy]->Uninit();
			m_pItemThrow[nCntEnemy] = NULL;
		}
	}
}

//==========================================================================
// �G�z�u
//==========================================================================
CItemThrow **CItemManager::SetItemThrow(D3DXVECTOR3 pos)
{
	CItemThrow *pEnemy[16];
	memset(&pEnemy[0], NULL, sizeof(pEnemy));

	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		if (m_pItemThrow[nCnt] != NULL)
		{// ��񂪓����Ă���
			continue;
		}



		// �G�̐���
		m_pItemThrow[nCnt] = CItemThrow::Create(pos, nCnt);			// ���

		if (m_pItemThrow[nCnt] == NULL)
		{// ���s���Ă�����

			delete m_pItemThrow[nCnt];
			m_pItemThrow[nCnt] = NULL;
			break;
		}

		// �|�C���^�R�s�[
		pEnemy[nCnt] = m_pItemThrow[nCnt];

		// �������Z
		m_nNum++;
		break;
	}

	return &pEnemy[0];
}

//========================================================
// �ʒu��Ԃ�
//========================================================
int CItemManager::GetNum(void)
{
	return m_nNum;
}

//==========================================================================
// �G�擾
//==========================================================================
CItemThrow **CItemManager::GetItemThrow(void)
{
	return &m_pItemThrow[0];
}