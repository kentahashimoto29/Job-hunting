//========================================================
//
//�E�C���h�E�̐����� (fade.h)
//Author ���{����
//
//========================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"
#include "object2D.h"

//===================================
//�t�F�[�h�̃N���X
//===================================
class CFade
{
public:

	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;


	CFade();								//�R���X�g���N�^
	~CFade();								//�f�X�g���N�^

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	void SetFade(CScene::MODE mode);
	void SetFadeFirst(CScene::MODE mode);

	FADE GetState(void);	// ��Ԏ擾

private:

	static int m_nIdxTexture;

	CObject2D *m_pObject2D;				//�t�F�[�h�̃|���S��

	CScene::MODE m_modenext;				//���̉��
	D3DXCOLOR m_color;						//�|���S���̐F
	FADE m_fade;
};

#endif