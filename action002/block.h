//========================================================
// 
// �E�C���h�E�̐����� (block.h)
// Author ���{����
// 
//========================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "main.h"
#include "object2D.h"

// �}�N����`
#define BLOCK_MAX									(32)		// �u���b�N�̍ő吔
#define BLOCK_WIDTH									(80.0f)		// �u���b�N�̕�
#define BLOCK_HEIGHT								(80.0f)		// �Ԃ̍���


//===================================
// �w�i�̃N���X
//===================================
class CBlock : public CObject2D
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_MAX,
	}TYPE;

	CBlock();										// �R���X�g���N�^
	CBlock(D3DXVECTOR3 pos);						// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CBlock();										// �f�X�g���N�^

	static CBlock *Create(D3DXVECTOR3 pos);			// ��������

	HRESULT Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

private:
	static int m_nIdxTexture;
};

#endif