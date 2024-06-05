//========================================================
//
//�E�C���h�E�̐����� (score.h)
//Author ���{����
//
//========================================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "object2D.h"

//�}�N����`
#define TIME_MAX									(3)		//�X�R�A�̌���

//===================================
//�w�i�̃N���X
//===================================
class CTime : public CObject
{
public:
	CTime(int nPriority = 4);								//�R���X�g���N�^
	~CTime();								//�f�X�g���N�^

	static CTime *Create();				//�G�̐���

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	void SetTime(int nTime);				//�ݒ菈��
	int GetTime(void);
	int GetInitTime(void);
	D3DXVECTOR3 GetPos(void);				//�ʒu��Ԃ�
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;						//�I�u�W�F�N�g�̈ʒu

private:
	static int m_nIdxTexture;				//�e�N�X�`���̔ԍ�
	CObject2D *m_apObject2D[TIME_MAX];		//�^�C���̃I�u�W�F�N�g
	int m_aTexU[TIME_MAX];					//�e�N�X�`���̃X�R�A�X�V�p�ϐ�
	int m_nTime;							//�^�C��
	int m_nInitTime;						//�^�C���̏����l
	int m_nSecondCount;						//
};

#endif