//========================================================
//
//�E�C���h�E�̐����� (goal.h)
//Author ���{����
//
//========================================================
#ifndef _GOAL_H_
#define _GOAL_H_
#include "main.h"
#include "manager.h"
class CObject2D;

//===================================
//�^�C�g���̃N���X
//===================================
class CTitle : public CScene
{
public:
	CTitle();								//�R���X�g���N�^
	~CTitle();								//�f�X�g���N�^

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	D3DXVECTOR3 GetPos(void);				//�ʒu��Ԃ�
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;						//�I�u�W�F�N�g�̈ʒu

private:
	CObject2D *m_apObject2D[1];				//�^�C�g���̃I�u�W�F�N�g
	static int m_nIdxTexture;				//�e�N�X�`���̔ԍ�

	bool b;
};

#endif