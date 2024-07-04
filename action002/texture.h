//========================================================
//
//�E�C���h�E�̐����� (texture.h)
//Author ���{����
//
//========================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "main.h"

#define TEXTURE_MAX									(64)	//�e�N�X�`���̍ő吔

//===================================
//�e�N�X�`���̃N���X
//===================================
class CTexture
{
public:
	CTexture();									//�R���X�g���N�^
	~CTexture();								//�f�X�g���N�^

	HRESULT Load(void);							//�e�N�X�`���̐���
	void Unload(void);							//�e�N�X�`���̔j��

	int Regist(const char *pFilename);			//�w��e�N�X�`���̓ǂݍ���
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);	//�w��̃e�N�X�`����Ԃ�
	const char *GetName(int nIdx);				//�w��̃e�N�X�`���̖��O��Ԃ�

private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];	//�e�N�X�`���̃|�C���^
	const char *m_aFilename[TEXTURE_MAX];			//�e�N�X�`���̖��O
	static int m_nNumAll;							//�e�N�X�`���̑���
};

#endif