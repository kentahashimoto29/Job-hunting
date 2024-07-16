//========================================================
//
//�E�C���h�E�̐����� (skill_UI.h)
//Author ���{����
//
//========================================================
#ifndef _SKILL_UI_H_
#define _SKILL_UI_H_
#include "main.h"
#include "manager.h"
class CObject2D;

//===================================
// �X�L��UI�̃N���X
//===================================
class CSkill_UI : public CObject
{
public:
	CSkill_UI();							//�R���X�g���N�^
	~CSkill_UI();							//�f�X�g���N�^

	static CSkill_UI *Create();				//�G�̐���

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	D3DXVECTOR3 GetPos(void);				//�ʒu��Ԃ�
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	CObject2D *GetObjectGauge2D() { return m_apObjectGauge2D; }

	D3DXVECTOR3 m_pos;						//�I�u�W�F�N�g�̈ʒu

private:
	D3DXCOLOR m_col;
	CObject2D *m_apObject2D;				//�^�C�g���̃I�u�W�F�N�g
	CObject2D *m_apObjectGauge2D;			//�^�C�g���̃I�u�W�F�N�g
	static int m_nIdxTexture;				//�e�N�X�`���̔ԍ�

	bool b;
};

#endif