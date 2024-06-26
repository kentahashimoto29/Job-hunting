//========================================================
//
//�E�C���h�E�̐����� (score.cpp)
//Author ���{����
//
//========================================================
#include "game.h"
#include "manager.h"
#include "fade.h"
#include "Skill_UI.h"
#include "wall_obj_manager.h"

#define PLAYER_SPAWN_X							(1400.0f)
#define FEILD_WIDTH								(16)
#define FEILD_HEIGHT							(16)
#define WALL_WIDTH								(16)
#define WALL_HEIGHT								(2)
#define WALL_NUM								(4)

//========================================================
//�ÓI�����o�ϐ�
//========================================================
CPlayer3D *CGame::m_pPlayer3D = NULL;
CEnemyManager *CGame::m_pEnemyManager = NULL;
CWallObjManager *CGame::m_pWallManager = NULL;
CBlock3D *CGame::m_pBlock3D = NULL;
CDeathBlock *CGame::m_pDeathBlock = NULL;
CThroughBlock *CGame::m_pThroughBlock = NULL;
CItemManager *CGame::m_pItemManager = NULL;
CTime *CGame::m_pTime = NULL;
CScore *CGame::m_pScore = NULL;
CSkill_UI *CGame::m_pSkillUI = NULL;
float CGame::m_nInitPos = 0.0f;
int CGame::m_nScore = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CGame::CGame()
{
	memset(&m_pField[0], NULL, sizeof(m_pField));		// 
	memset(&m_pWall[0], NULL, sizeof(m_pWall));			// 
	m_nInitPos = 0;
	m_nScore = 0;
}

//========================================================
//�f�X�g���N�^
//========================================================
CGame::~CGame()
{

}

//========================================================
//����������
//========================================================
HRESULT CGame::Init(void)
{

	m_pTime = CTime::Create();

	m_pPlayer3D = CPlayer3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pEnemyManager = CEnemyManager::Create();

	m_pWallManager = CWallObjManager::Create();

	m_pItemManager = CItemManager::Create();

	m_pScore = CScore::Create();

	m_pSkillUI = CSkill_UI::Create();

	for (int nCntHeight = 0; nCntHeight < FEILD_HEIGHT; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < FEILD_WIDTH; nCntWidth++)
		{
			m_pField[nCntWidth + nCntHeight * FEILD_WIDTH] = 
				CField::Create(D3DXVECTOR3(100.0f * nCntWidth, 0.0f, 100.0f * nCntHeight), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	m_nInitPos = ((100.0f * WALL_WIDTH) - 50.0f);


	for (int nCntHeight = 0; nCntHeight < WALL_HEIGHT; nCntHeight++)
	{
		for (int nCntNum = 0; nCntNum < WALL_NUM; nCntNum++)
		{
			for (int nCntWidth = 0; nCntWidth < WALL_WIDTH; nCntWidth++)
			{
				switch (nCntNum)
				{
				case 0:
					m_pWall[nCntWidth + nCntNum * WALL_WIDTH + nCntHeight * WALL_NUM * WALL_WIDTH] =
						CWall::Create(D3DXVECTOR3(-50.0f, 50.0f + 100.0f * nCntHeight, 100.0f * nCntWidth), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));
					break;


				case 1:
					m_pWall[nCntWidth + nCntNum * WALL_WIDTH + nCntHeight * WALL_NUM * WALL_WIDTH] =
						CWall::Create(D3DXVECTOR3(100.0f * nCntWidth, 50.0f + 100.0f * nCntHeight, m_nInitPos), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					break;


				case 2:
					m_pWall[nCntWidth + nCntNum * WALL_WIDTH + nCntHeight * WALL_NUM * WALL_WIDTH] =
						CWall::Create(D3DXVECTOR3(m_nInitPos, 50.0f + 100.0f * nCntHeight, (m_nInitPos - 50.0f) - 100.0f * nCntWidth), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
					break;


				case 3:
					m_pWall[nCntWidth + nCntNum * WALL_WIDTH + nCntHeight * WALL_NUM * WALL_WIDTH] =
						CWall::Create(D3DXVECTOR3(-100.0f * nCntWidth + (m_nInitPos - 50.0f), 50.0f + 100.0f * nCntHeight, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
					break;


				default:
					break;
				}
			}
		}
	}

	CManager::GetInstance()->GetCamera()->SetPosGame(m_pPlayer3D->GetPos(), m_pPlayer3D->GetPos());


	return S_OK;
}

//========================================================
//�I������
//========================================================
void CGame::Uninit(void)
{
	//NULL�`�F�b�N
	if (m_pTime != NULL)
	{
		//�I������
		m_pTime->Uninit();
		m_pTime = NULL;
	}

	//NULL�`�F�b�N
	if (m_pScore != NULL)
	{
		//�I������
		m_pScore->Uninit();
		m_pScore = NULL;
	}

	//NULL�`�F�b�N
	if (m_pSkillUI != NULL)
	{
		//�I������
		m_pScore->Uninit();
		m_pScore = NULL;
	}

	//NULL�`�F�b�N
	if (m_pPlayer3D != NULL)
	{
		//�I������
		m_pPlayer3D->Uninit();
		m_pPlayer3D = NULL;
	}

	//NULL�`�F�b�N
	if (m_pEnemyManager != NULL)
	{
		//�I������
		m_pEnemyManager->Uninit();
		m_pEnemyManager = NULL;
	}

	//NULL�`�F�b�N
	if (m_pWallManager != NULL)
	{
		//�I������
		m_pWallManager->Uninit();
		m_pWallManager = NULL;
	}

	//NULL�`�F�b�N
	if (m_pItemManager != NULL)
	{
		//�I������
		m_pItemManager->Uninit();
		m_pItemManager = NULL;
	}

	for (int nCntField = 0; nCntField < FEILD_WIDTH * FEILD_HEIGHT; nCntField++)
	{
		//NULL�`�F�b�N
		if (m_pField[nCntField] != NULL)
		{
			m_pField[nCntField]->Uninit();
			m_pField[nCntField] = NULL;
		}
	}

	for (int nCntWall = 0; nCntWall < WALL_WIDTH * WALL_HEIGHT * WALL_NUM; nCntWall++)
	{
		//NULL�`�F�b�N
		if (m_pWall[nCntWall] != NULL)
		{
			m_pWall[nCntWall]->Uninit();
			m_pWall[nCntWall] = NULL;
		}
	}

	Release();
}

//========================================================
//�X�V����
//========================================================
void CGame::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�}�E�X�̎擾
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (b != true)
		{
			if (CManager::GetInstance()->GetFade()->GetState() == CFade::FADE_NONE)
			{
				CManager::GetInstance()->GetFade()->SetFade(CManager::GetInstance()->GetScene()->MODE_RESULT);
				b = true;
			}
		}
	}

	if (CEnemyManager::GetNum() <= 0)
	{
		if (b != true)
		{
			if (CManager::GetInstance()->GetFade()->GetState() == CFade::FADE_NONE)
			{
				CManager::GetInstance()->GetFade()->SetFade(CManager::GetInstance()->GetScene()->MODE_RESULT);
				b = true;
			}
		}
	}

	m_pEnemyManager->Update();
	m_pItemManager->Update();
	m_pWallManager->Update();
}

//========================================================
//�`�揈��
//========================================================
void CGame::Draw(void)
{

}


//========================================================
//�v���C���[3D�̃|�C���^��Ԃ��֐�
//========================================================
CPlayer3D *CGame::GetPlayer3D(void)
{
	return m_pPlayer3D;
}

////========================================================
////�G�l�~�[3D�̃|�C���^��Ԃ��֐�
////========================================================
//CEnemy3D *CGame::GetEnemy3D(void)
//{
//	return m_pEnemy3D[0];
//}

//========================================================
//�u���b�N3D�̃|�C���^��Ԃ��֐�
//========================================================
CBlock3D *CGame::GetBlock3D(void)
{
	return m_pBlock3D;
}

//========================================================
//�����u���b�N�̃|�C���^��Ԃ��֐�
//========================================================
CDeathBlock *CGame::GetDeathBlock(void)
{
	return m_pDeathBlock;
}

//========================================================
//�ʂ蔲�����u���b�N�̃|�C���^��Ԃ��֐�
//========================================================
CThroughBlock *CGame::GetThroughBlock(void)
{
	return m_pThroughBlock;
}

//========================================================
//�^�C���̃|�C���^��Ԃ��֐�
//========================================================
CTime *CGame::GetTime(void)
{
	return m_pTime;
}

//========================================================
//�X�R�A�̃|�C���^��Ԃ��֐�
//========================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//========================================================
//�X�R�A�̃|�C���^��Ԃ��֐�
//========================================================
CSkill_UI *CGame::GetSkillUI(void)
{
	return m_pSkillUI;
}


//========================================================
//�G�}�l�[�W���[�̃|�C���^��Ԃ��֐�
//========================================================
CEnemyManager *CGame::GetEnemyManager(void)
{
	return m_pEnemyManager;
}

//========================================================
//�G�}�l�[�W���[�̃|�C���^��Ԃ��֐�
//========================================================
CWallObjManager *CGame::GetWallManager(void)
{
	return m_pWallManager;
}

//========================================================
//�A�C�e���}�l�[�W���[�̃|�C���^��Ԃ��֐�
//========================================================
CItemManager *CGame::GetItemManager(void)
{
	return m_pItemManager;
}


//==========================================================================
// �G�擾
//==========================================================================
CField *CGame::GetField(void)
{
	return m_pField[0];
}


//==========================================================================
// �G�擾
//==========================================================================
CWall *CGame::GetWall(void)
{
	return m_pWall[0];
}


//==========================================================================
// �X�R�A�擾
//==========================================================================
float CGame::GetInitPos(void)
{
	return m_nInitPos;
}


//==========================================================================
// �X�R�A�擾
//==========================================================================
int CGame::GetGameScore(void)
{
	return m_nScore;
}


//==========================================================================
// �X�R�A�ݒ�
//==========================================================================
void CGame::SetScore(int nScore)
{
	m_nScore = nScore;
}


//==========================================================================
// �X�R�A���Z
//==========================================================================
void CGame::AddScore()
{
	m_nScore++;
}