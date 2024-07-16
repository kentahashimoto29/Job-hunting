//========================================================
// 
// �E�C���h�E�̐����� (block3D.h)
// Author ���{����
// 
//========================================================
#ifndef _BLOCK3D_H_
#define _BLOCK3D_H_
#include "main.h"
#include "objectX.h"

//===================================
// �v���C���[�̃N���X
//===================================
class CBlock3D : public CObjectX
{
public:
	CBlock3D(int nPriority = 6);									// �R���X�g���N�^
	CBlock3D(D3DXVECTOR3 pos, int nPriority = 6);					// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CBlock3D();									// �f�X�g���N�^

	static CBlock3D *Create(D3DXVECTOR3 pos);	// ��������

	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	bool Collisionbool(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pmove, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pmove, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);
	D3DXVECTOR3 GetPos(void);					// �ʒu��Ԃ�

private:
	static int m_nIdxTexture;					// �e�N�X�`���̔ԍ�
	D3DXVECTOR3 m_VtxMax;						// ���f���̍ő�l
	D3DXVECTOR3 m_VtxMin;						// ���f���̍ŏ��l
};

#endif