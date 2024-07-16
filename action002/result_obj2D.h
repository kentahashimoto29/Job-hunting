//========================================================
//
//�E�C���h�E�̐����� (result_obj2D.h)
//Author ���{����
//
//========================================================
#ifndef _RESULT_OBJ_H_
#define _RESULT_OBJ_H_
#include "main.h"
#include "manager.h"
class CObject2D;

//===================================
//�^�C�g�����S�̃N���X
//===================================
class CResult_Obj2D : public CObject
{
public:
	CResult_Obj2D();							//�R���X�g���N�^
	~CResult_Obj2D();						//�f�X�g���N�^

	static CResult_Obj2D *Create();				//�G�̐���

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	D3DXVECTOR3 GetPos(void);				//�ʒu��Ԃ�
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;						//�I�u�W�F�N�g�̈ʒu

private:
	CObject2D *m_apObject2D[3];				//�^�C�g���̃I�u�W�F�N�g
	static int m_nIdxTexture;				//�e�N�X�`���̔ԍ�

	bool b;
};

#endif