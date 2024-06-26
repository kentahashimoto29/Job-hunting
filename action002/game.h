//========================================================
//
//�E�C���h�E�̐����� (goal.h)
//Author ���{����
//
//========================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "manager.h"
#include "player3D.h"
#include "enemymanager.h"
#include "block3D.h"
#include "death_block.h"
#include "through_block.h"
#include "time.h"
#include "score.h"
#include "field.h"
#include "wall.h"
#include "item_manager.h"
class CSkill_UI;
class CWallObjManager;

//===================================
//�Q�[���̃N���X
//===================================
class CGame : public CScene
{
public:
	CGame();								//�R���X�g���N�^
	~CGame();								//�f�X�g���N�^

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	D3DXVECTOR3 m_pos;						//�I�u�W�F�N�g�̈ʒu;

	static CPlayer3D *GetPlayer3D();			//�v���C���[3D�̃|�C���^��Ԃ��֐�
	static CBlock3D *GetBlock3D();				//�u���b�N3D�̃|�C���^��Ԃ��֐�
	static CDeathBlock *GetDeathBlock();		//�����u���b�N�̃|�C���^��Ԃ��֐�
	static CThroughBlock *GetThroughBlock();	//�ʂ蔲�����u���b�N�̃|�C���^��Ԃ��֐�
	static CTime *GetTime();					//�^�C���̃|�C���^��Ԃ��֐�
	static CScore *GetScore();					//�X�R�A�̃|�C���^��Ԃ��֐�
	static CEnemyManager *GetEnemyManager();	//�G�}�l�[�W���[�̃|�C���^��Ԃ��֐�
	static CWallObjManager *GetWallManager();	//�G�}�l�[�W���[�̃|�C���^��Ԃ��֐�
	static CItemManager *GetItemManager();		//�A�C�e���}�l�[�W���[�̃|�C���^��Ԃ��֐�
	static CSkill_UI *GetSkillUI();				//�A�C�e���}�l�[�W���[�̃|�C���^��Ԃ��֐�
	CField *GetField();							//�t�B�[���h�̃|�C���^��Ԃ��֐�
	CWall *GetWall();							//�ǂ̃|�C���^��Ԃ��֐�

	static float GetInitPos();
	static int GetGameScore();
	static void SetScore(int nScore);
	static void AddScore();

private:

	static CPlayer3D *m_pPlayer3D;				//�v���C���[3D�̃|�C���^
	static CBlock3D *m_pBlock3D;				//�u���b�N3D�̃|�C���^
	static CDeathBlock *m_pDeathBlock;			//�����u���b�N�̃|�C���^
	static CThroughBlock *m_pThroughBlock;		//�ʂ蔲�����u���b�N�̃|�C���^
	static CTime *m_pTime;						//�^�C���̃|�C���^
	static CScore *m_pScore;					//�X�R�A�̃|�C���^
	static CEnemyManager *m_pEnemyManager;		//�G�l�~�[3D�̃|�C���^
	static CWallObjManager *m_pWallManager;		//�G�l�~�[3D�̃|�C���^
	static CItemManager *m_pItemManager;		//�A�C�e���}�l�[�W���[�̃|�C���^
	static CSkill_UI *m_pSkillUI;				//�A�C�e���}�l�[�W���[�̃|�C���^
	CField *m_pField[256];						//�t�B�[���h�̃|�C���^
	CWall *m_pWall[256];						//�ǂ̃|�C���^

	static float m_nInitPos;

	bool b;
	static int m_nScore;
};

#endif