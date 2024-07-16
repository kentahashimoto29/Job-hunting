//========================================================
//
//�E�C���h�E�̐����� (score.h)
//Author ���{����
//
//========================================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "main.h"
#include "object2D.h"

//�}�N����`
#define SCORE_NUM									(3)		//�X�R�A�̌���
#define RANKING_MAX									(5)		//�X�R�A�̌�
#define NUMBER_MAX									(15)	//�X�R�A�̌���


//===================================
//�����L���O�̃N���X
//===================================
class CRanking : public CObject
{
public:
	CRanking();								//�R���X�g���N�^
	~CRanking();								//�f�X�g���N�^

	static CRanking *Create();				//�G�̐���

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	void SetScore(int nScore, int nCntR);	//�ݒ菈��
	static void SetCurScore(int nScore);	//����̃X�R�A�ݒ菈��
	D3DXVECTOR3 GetPos(void);				//�ʒu��Ԃ�
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	void BlinkingCol();

	D3DXVECTOR3 m_pos;						//�I�u�W�F�N�g�̈ʒu

private:
	static int m_nIdxTexture;					//�e�N�X�`���̔ԍ�
	CObject2D *m_apObject2D[NUMBER_MAX];		//�X�R�A�̃I�u�W�F�N�g
	CObject2D *m_apObject2DRank[RANKING_MAX];	//���ʂ̃I�u�W�F�N�g
	int m_aTexU[SCORE_NUM];						//�e�N�X�`���̃X�R�A�X�V�p�ϐ�
	int m_nRankingScore[RANKING_MAX];			//�X�R�A
	static int CurScore;						//����̃X�R�A

	int m_nNewRec;								//�j���[���R�[�h�̏���
	bool m_bNewRec;								//�j���[���R�[�h���Ă��邩�ǂ���
	D3DXCOLOR m_col;
	float m_Alpha;

	bool b;
};

#endif