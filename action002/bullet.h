//========================================================
//
//�E�C���h�E�̐����� (bullet.h)
//Author ���{����
//
//========================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "object2D.h"

//===================================
//�e�̃N���X
//===================================
class CBullet : public CObject2D
{
public:
	CBullet();									//�R���X�g���N�^
	CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CBullet();									//�f�X�g���N�^

	static CBullet *Create(D3DXVECTOR3 pos);	//�e�̐���

	HRESULT Init(void);							//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��

private:
	bool CollisionEnemy(D3DXVECTOR3 pos);		//�G�ƒe�Ƃ̓����蔻��

	static int m_nIdxTexture;
	D3DXVECTOR3 m_move;							//�e�̈ړ���
	int m_nLife;								//�e�̗̑�
};

#endif