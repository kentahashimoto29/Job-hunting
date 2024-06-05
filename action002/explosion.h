//========================================================
//
//�E�C���h�E�̐����� (Player.h)
//Author ���{����
//
//========================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "object2D.h"

//===================================
//�����̃N���X
//===================================
class CExplosion : public CObject2D
{
public:
	CExplosion();									//�R���X�g���N�^
	CExplosion(D3DXVECTOR3 pos);					//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CExplosion();									//�f�X�g���N�^

	static CExplosion *Create(D3DXVECTOR3 pos);		//�����̐���

	HRESULT Init(void);								//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��

private:
	static int m_nIdxTexture;		//�e�N�X�`���̔ԍ�				
	int m_nCntrAnim;				//�A�j���[�V�����̃J�E���g
	int m_nPtnAnim;					//�A�j���[�V�����̃p�^�[��
};

#endif