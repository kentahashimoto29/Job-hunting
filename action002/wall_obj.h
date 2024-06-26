//========================================================
//
//�E�C���h�E�̐����� (enemy3D.h)
//Author ���{����
//
//========================================================
#ifndef _WALLOBJ_H_
#define _WALLOBJ_H_
#include "main.h"
#include "objectX.h"

class CPlayer3D;
class CItemThrow;

//===================================
//�G�̃N���X
//===================================
class CWallObj : public CObjectX
{
public:
	CWallObj(int nPriority = 6);									//�R���X�g���N�^
	CWallObj(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority = 6);					//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CWallObj();								//�f�X�g���N�^

	static CWallObj *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx);	//�G�̐���

	HRESULT Init(int nIdx);							//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��

	D3DXVECTOR3 GetPos(void);					//�ʒu��Ԃ�

	void HitEnemy(void);						//�G�̃_���[�W����
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);
	bool Collision(CPlayer3D *pPlayer, CItemThrow *pItemThrow);

private:

	D3DXVECTOR3 m_VtxMax;						//���f���̍ő�l
	D3DXVECTOR3 m_VtxMin;						//���f���̍ŏ��l

	D3DXVECTOR3 m_Oldpos;						//

	int m_nLife;								//�̗�
	int m_nIdx;

	bool bCollision;
};

#endif