//========================================================
// 
// �E�C���h�E�̐����� (bg.h)
// Author ���{����
// 
//========================================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object2D.h"

//===================================
// �w�i�̃N���X
//===================================
class CBG : public CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BG000,
		TYPE_BG001,
		TYPE_BG002,
		TYPE_MAX,
	}TYPE;

	CBG();						// �R���X�g���N�^
	~CBG();						// �f�X�g���N�^

	static CBG *Create();		// �G�̐���

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	D3DXVECTOR3 GetPos(void);	// �ʒu��Ԃ�
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;			// �I�u�W�F�N�g�̈ʒu

private:
	static int m_nIdxTexture[3];	// �e�N�X�`���̔ԍ�
	CObject2D *m_apObject2D[3];		// �w�i�̃I�u�W�F�N�g
	float m_aTexV[3];				// �e�N�X�`���̃X�N���[���p
	TYPE m_type[3];					// �e�N�X�`���̎��
};

#endif