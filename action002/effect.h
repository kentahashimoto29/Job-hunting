//========================================================
//
//�E�C���h�E�̐����� (effect.h)
//Author ���{����
//
//========================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include "object2D.h"

//===================================
//�G�t�F�N�g�̃N���X
//===================================
class CEffect : public CObject2D
{
public:
	CEffect();									//�R���X�g���N�^
	CEffect(D3DXVECTOR3 pos);					//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CEffect();									//�f�X�g���N�^

	static CEffect *Create(D3DXVECTOR3 pos);	//�����̐���

	HRESULT Init(void);							//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��

private:
	static int m_nIdxTexture;			//�e�N�X�`���̔ԍ�
	float AlphaData;					//���l
};

#endif