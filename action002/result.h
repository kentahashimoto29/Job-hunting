//========================================================
// 
// �E�C���h�E�̐����� (result.h)
// Author ���{����
// 
//========================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"
#include "manager.h"
#include "object2D.h"
#include "ranking.h"

class CResult_Obj2D;

//===================================
// ���U���g�̃N���X
//===================================
class CResult : public CScene
{
public:
	CResult();								// �R���X�g���N�^
	~CResult();								// �f�X�g���N�^

	HRESULT Init(void);						// ����������
	void Uninit(void);						// �I������
	void Update(void);						// �X�V����
	void Draw(void);						// �`�揈��

	static CRanking *GetRanking();			// �A�C�e���}�l�[�W���[�̃|�C���^��Ԃ��֐�

	D3DXVECTOR3 GetPos(void);				// �ʒu��Ԃ�
	D3DXVECTOR3 m_pos;						// �I�u�W�F�N�g�̈ʒu

private:
	static CResult_Obj2D *m_apResultObj;
	static CRanking *m_pRanking;			// �A�C�e���}�l�[�W���[�̃|�C���^��Ԃ��֐�

	static int m_nIdxTexture;				// �e�N�X�`���̔ԍ�
	bool b;
};

#endif