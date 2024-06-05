//========================================================
//
//�E�C���h�E�̐����� (item3D.h)
//Author ���{����
//
//========================================================
#ifndef _ITEM3D_H_
#define _ITEM3D_H_
#include "main.h"
#include "objectX.h"

//===================================
//�v���C���[�̃N���X
//===================================
class CItem3D : public CObjectX
{
public:
	CItem3D(int nPriority = 6);									//�R���X�g���N�^
	CItem3D(D3DXVECTOR3 pos, int nPriority = 6);					//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CItem3D();									//�f�X�g���N�^

	static CItem3D *Create(D3DXVECTOR3 pos);	//��������

	HRESULT Init(void);							//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��

	D3DXVECTOR3 GetPos(void);					//�ʒu��Ԃ�

private:
	static int m_nIdxTexture;					//�e�N�X�`���̔ԍ�
};

#endif