//========================================================
// 
// �E�C���h�E�̐����� (player3D.h)
// Author ���{����
// 
//========================================================
#ifndef _PLAYER3D_H_
#define _PLAYER3D_H_
#include "main.h"
#include "object.h"
#include "model.h"
#include "motion.h"
class CShadow;

//===================================
// �v���C���[�̃N���X
//===================================
class CPlayer3D : public CObject
{
public:

	// ���[�V�����̎��
	typedef enum
	{
		MOTION_NEUTRAL = 0,		// �ҋ@
		MOTION_MOVE,			// �ړ�
		MOTION_JUMP,			// �W�����v
		MOTION_LANDING,			// ���n
		MOTION_MAX,
	}MOTIONTYPE;

	// 
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_ACCEL,			// ����
		TYPE_DELAY,			// �x��
		TYPE_MAX,
	}SKILL;

	CPlayer3D(int nPriority = 6);									// �R���X�g���N�^
	CPlayer3D(D3DXVECTOR3 pos, int nPriority = 6);					// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CPlayer3D();									// �f�X�g���N�^

	static CPlayer3D *Create(D3DXVECTOR3 pos);		// ��������

	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	D3DXMATRIX GetMtxWorld(void);				// �}�g���b�N�X��Ԃ�
	D3DXVECTOR3 GetPos(void);					// �ʒu��Ԃ�
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 GetRot(void);					// ������Ԃ�
	D3DXVECTOR3 GetMove(void);					// �ړ��ʂ�Ԃ�

	CModel *GetModel(int nIdx);					// ���f���̃|�C���^��Ԃ�

	void Respawn();

	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, TYPE type);
	bool Collisionbool(D3DXVECTOR3 *pPos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, TYPE type);
	bool CollisionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);

private:
	static int m_nIdxTexture;					// �e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_Oldpos;			// �O�t���[���ʒu
	D3DXVECTOR3 m_revivalpos;		// �����ʒu
	D3DXVECTOR3 m_rot;				// ����
	D3DXVECTOR3 m_revivalrot;		// ��������
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_keepmove;				// �ړ���
	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_Destrot;			// 
	D3DXVECTOR3 m_Diffrot;			// 

	D3DXVECTOR3 m_VtxMax;			// 
	D3DXVECTOR3 m_VtxMin;			// 

	MOTIONTYPE m_nType;				// 
	MOTIONTYPE m_nOldType;				// 
	SKILL m_nSkill;

	CModel *m_apModel[32];			// ���f���ւ̃|�C���^
	int m_nNumModel;				// ���f���̑���

	CMotion *m_pMotion;				// ���[�V�����̃|�C���^

	int m_nSkillTime;
	int m_nCnt;

	int m_nSkillCoolTime;

	bool m_bJump;
	bool m_bGoal;
	bool m_bWalk;

	CShadow *m_pShadow;
};

#endif