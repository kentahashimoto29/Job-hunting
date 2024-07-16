//========================================================
// 
// �E�C���h�E�̐����� (enemy.h)
// Author ���{����
// 
//========================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "object2D.h"

//===================================
// �G�̃N���X
//===================================
class CEnemy : public CObject2D
{
public:
	CEnemy();									// �R���X�g���N�^
	CEnemy(D3DXVECTOR3 pos);					// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CEnemy();									// �f�X�g���N�^

	static CEnemy *Create(D3DXVECTOR3 pos);		// �G�̐���

	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

private:
	static int m_nIdxTexture;					// �e�N�X�`���̔ԍ�
};

#endif