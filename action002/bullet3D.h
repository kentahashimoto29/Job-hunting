//========================================================
// 
// �E�C���h�E�̐����� (bullet.h)
// Author ���{����
// 
//========================================================
#ifndef _BULLET3D_H_
#define _BULLET3D_H_
#include "main.h"
#include "objectX.h"

//===================================
// �e�̃N���X
//===================================
class CBullet3D : public CObjectX
{
public:
	CBullet3D(int nPriority = 6);																// �R���X�g���N�^
	CBullet3D(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Mag, int nPriority = 6);						// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CBullet3D();																// �f�X�g���N�^

	static CBullet3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Mag);		// �e�̐���

	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	bool CollisionEnemy(D3DXVECTOR3 pos);		// �G�ƒe�Ƃ̓����蔻��

private:

	D3DXVECTOR3 m_move;							// �e�̈ړ���
	int m_nLife;								// �e�̗̑�

	float m_MoveMag;							// �ړ��ʂ̔{��
};

#endif