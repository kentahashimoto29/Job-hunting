//========================================================
//
//�E�C���h�E�̐����� (goal.h)
//Author ���{����
//
//========================================================
#ifndef _GOAL_H_
#define _GOAL_H_
#include "main.h"
#include "object2D.h"

//===================================
//�S�[���̃N���X
//===================================
class CGoal : public CObject2D
{
public:
	CGoal();								//�R���X�g���N�^
	~CGoal();								//�f�X�g���N�^

	static CGoal *Create();					//�G�̐���

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	D3DXVECTOR3 GetPos(void);				//�ʒu��Ԃ�

	D3DXVECTOR3 m_pos;						//�I�u�W�F�N�g�̈ʒu

private:
	static int m_nIdxTexture;				//�e�N�X�`���̔ԍ�
};

#endif