//========================================================
// 
// �E�C���h�E�̐����� (light.h)
// Author ���{����
// 
//========================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "main.h"

//===================================
// ���C�g�̃N���X
//===================================
class CLight
{
public:
	CLight();					// �R���X�g���N�^
	~CLight();					// �f�X�g���N�^

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����

private:
	D3DLIGHT9 m_Light[4];			// ���C�g�̏��
};

#endif