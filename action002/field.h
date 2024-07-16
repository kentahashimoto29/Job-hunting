//========================================================
// 
// �E�C���h�E�̐����� (Field.h)
// Author ���{����
// 
//========================================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "main.h"
#include "object3D.h"

#define FIElD_MAX							(4)		// �n�ʂ̍ő吔

//===================================
// �t�B�[���h�̃N���X
//===================================
class CField : public CObject3D
{
public:
	CField();									// �R���X�g���N�^
	CField(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CField();									// �f�X�g���N�^

	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	static CField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// ��������
	D3DXVECTOR3 GetPos(void);										// �ʒu��Ԃ�
	LPDIRECT3DINDEXBUFFER9 GetIdxBuff(void);						// 

private:
	static int m_nIdxTexture;					// �e�N�X�`���̔ԍ�
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			// �C���f�b�N�X�o�b�t�@�̃|�C���^
};

#endif