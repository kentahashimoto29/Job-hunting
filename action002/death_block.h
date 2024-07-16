//========================================================
// 
// �E�C���h�E�̐����� (block3D.h)
// Author ���{����
// 
//========================================================
#ifndef _DEATHBLOCK_H_
#define _DEATHBLOCK_H_
#include "main.h"
#include "objectX.h"

//===================================
// �f�X�u���b�N�̃N���X
//===================================
class CDeathBlock : public CObjectX
{
public:
	CDeathBlock(int nPriority = 6);						// �R ���X�g���N�^
	CDeathBlock(D3DXVECTOR3 pos, int nPriority = 6);	// �I �[�o�[���C�h���ꂽ�R���X�g���N�^
	~CDeathBlock();										// �f �X�g���N�^

	static CDeathBlock *Create(D3DXVECTOR3 pos);		// ��������

	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	D3DXVECTOR3 GetPos(void);					// �ʒu��Ԃ�
private:
	static int m_nIdxTexture;					// �e�N�X�`���̔ԍ�
	D3DXVECTOR3 m_VtxMax;						// ���f���̍ő�l
	D3DXVECTOR3 m_VtxMin;						// ���f���̍ŏ��l
};

#endif