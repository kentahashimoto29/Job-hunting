//========================================================
// 
// �E�C���h�E�̐����� (item3D.h)
// Author ���{����
// 
//========================================================
#ifndef _ITEMTHROW_H_
#define _ITEMTHROW_H_
#include "main.h"
#include "objectX.h"

//===================================
// �v���C���[�̃N���X
//===================================
class CItemThrow : public CObjectX
{
public:
	CItemThrow(int nPriority = 6);									// �R���X�g���N�^
	CItemThrow(D3DXVECTOR3 pos, int nPriority = 6);					// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CItemThrow();									// �f�X�g���N�^

	static CItemThrow *Create(D3DXVECTOR3 pos, int nIdx);	// ��������

	HRESULT Init(int nIdx);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	D3DXVECTOR3 GetPos(void);					// �ʒu��Ԃ�

	bool CollisionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);

private:
	static int m_nIdxTexture;					// �e�N�X�`���̔ԍ�
	bool bUse;

	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_VtxMax;						// ���f���̍ő�l
	D3DXVECTOR3 m_VtxMin;						// ���f���̍ŏ��l

	int m_nIdx;
};

#endif