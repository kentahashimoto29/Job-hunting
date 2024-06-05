//========================================================
//
//�E�C���h�E�̐����� (score.h)
//Author ���{����
//
//========================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "object2D.h"

//�}�N����`
#define SCORE_MAX									(8)		//�X�R�A�̌���

//===================================
//�w�i�̃N���X
//===================================
class CScore : public CObject
{
public:
	CScore();								//�R���X�g���N�^
	~CScore();								//�f�X�g���N�^

	static CScore *Create();				//�G�̐���

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	void SetScore(int nScore);				//�ݒ菈��
	void AddScore(int nValae);				//�X�R�A�̉��Z
	D3DXVECTOR3 GetPos(void);				//�ʒu��Ԃ�
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;						//�I�u�W�F�N�g�̈ʒu

private:
	static int m_nIdxTexture;				//�e�N�X�`���̔ԍ�
	CObject2D *m_apObject2D[SCORE_MAX];		//�X�R�A�̃I�u�W�F�N�g
	int m_aTexU[SCORE_MAX];					//�e�N�X�`���̃X�R�A�X�V�p�ϐ�
	int m_nScore;							//�X�R�A
};

#endif