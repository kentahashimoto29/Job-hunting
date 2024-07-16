//========================================================
//
//�E�C���h�E�̐����� (through_block.h)
//Author ���{����
//
//========================================================
#ifndef _THROUGHBLOCK_H_
#define _THROUGHBLOCK_H_
#include "main.h"
#include "objectX.h"

//===================================
//���蔲���u���b�N�̃N���X
//===================================
class CThroughBlock : public CObjectX
{
public:
	CThroughBlock(int nPriority = 6);									//�R���X�g���N�^
	CThroughBlock(D3DXVECTOR3 pos, int nPriority = 6);					//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CThroughBlock();									//�f�X�g���N�^

	static CThroughBlock *Create(D3DXVECTOR3 pos);	//��������

	HRESULT Init(void);							//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��

	D3DXVECTOR3 GetPos(void);					//�ʒu��Ԃ�

private:
	static int m_nIdxTexture;					//�e�N�X�`���̔ԍ�
	D3DXVECTOR3 m_VtxMax;						//���f���̍ő�l
	D3DXVECTOR3 m_VtxMin;						//���f���̍ŏ��l
};

#endif