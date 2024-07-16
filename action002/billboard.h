//========================================================
// 
// �E�C���h�E�̐����� (billboard.h)
// Author ���{����
// 
//========================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"
#include "object.h"

//===================================
// �r���{�[�h�̃N���X
//===================================
class CBillboard : public CObject
{
public:
	CBillboard(int nPriority = 4);					// �R���X�g���N�^
	~CBillboard();					// �f�X�g���N�^

	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��

	static CBillboard *Create(void);		// ��������
	D3DXVECTOR3 GetPos(void);				// �ʒu��Ԃ�
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_aVerBuff;		// ���_���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;						// �ʒu
};

#endif