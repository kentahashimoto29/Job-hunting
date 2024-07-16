//========================================================
// 
// �E�C���h�E�̐����� (player.h)
// Author ���{����
// 
//========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "object2D.h"

//===================================
// �v���C���[�̃N���X
//===================================
class CPlayer : public CObject2D
{
public:
	CPlayer();									// �R���X�g���N�^
	CPlayer(D3DXVECTOR3 pos);					// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CPlayer();									// �f�X�g���N�^

	static CPlayer *Create(D3DXVECTOR3 pos);	// ��������

	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	bool CollisionBlock(void);					// �u���b�N�Ƃ̓����蔻��

	D3DXVECTOR3 GetPos(void);					// �ʒu��Ԃ�

private:
	static int m_nIdxTexture;					// �e�N�X�`���̔ԍ�
	D3DXVECTOR3 m_move;							// �ړ���
	int GravityCnt;								// �d�͒����̃J�E���g

	int m_nCntAnim;								// �A�j���[�V�����̃J�E���g
	int m_nPtnAnim;								// �A�j���[�V�����̃p�^�[���iX���j
	int m_nPtnAnim2;							// �A�j���[�V�����̃p�^�[���Q�iY���j
};

#endif