//========================================================
// 
// �E�C���h�E�̐����� (enemy3D.h)
// Author ���{����
// 
//========================================================
#ifndef _ENEMY3D_H_
#define _ENEMY3D_H_
#include "main.h"
#include "objectX.h"

class CPlayer3D;
class CItemThrow;

//===================================
// �G�̃N���X
//===================================
class CEnemy3D : public CObjectX
{
public:
	CEnemy3D(int nPriority = 6);									// �R���X�g���N�^
	CEnemy3D(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority = 6);					// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CEnemy3D();								// �f�X�g���N�^

	static CEnemy3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx);	// �G�̐���

	HRESULT Init(int nIdx);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	D3DXVECTOR3 GetPos(void);					// �ʒu��Ԃ�

	void HitEnemy(void);						// �G�̃_���[�W����
	bool Collision();

private:

	D3DXVECTOR3 m_VtxMax;						// ���f���̍ő�l
	D3DXVECTOR3 m_VtxMin;						// ���f���̍ŏ��l

	float m_Angle;								// �G�ƃv���C���[�̊p�x
	D3DXVECTOR3 m_Oldpos;						// 
	D3DXVECTOR3 m_move;							// �ړ���
	D3DXVECTOR3 m_Destrot;						// 
	D3DXVECTOR3 m_Diffrot;						// 

	int m_nLife;								// �̗�
	int m_nIdx;

	bool bCollision;
};

#endif