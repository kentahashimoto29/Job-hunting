//========================================================
//
//�E�C���h�E�̐����� (Renderer.h)
//Author ���{����
//
//========================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

//===================================
//�������_�[�̃N���X
//===================================
class CRenderer
{
public:
	CRenderer();							//�R���X�g���N�^
	~CRenderer();							//�f�X�g���N�^

	HRESULT Init(HWND hWnd, BOOL bWindow);	//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	LPDIRECT3DDEVICE9 GetDevice(void);		//�f�o�C�X��Ԃ�
	void SetDevice(LPDIRECT3DDEVICE9 dev);		//�f�o�C�X��Ԃ�

	LPD3DXFONT GetFont(void);

	void DrawFPS(void);

private:
	LPDIRECT3D9 m_pD3D;						//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;			//Direct3D�f�o�C�X�ւ̃|�C���^

	LPD3DXFONT m_pFont;

	int m_nCountFPS;
};

#endif