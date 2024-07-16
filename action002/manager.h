//========================================================
//
//�E�C���h�E�̐����� (manager.h)
//Author ���{����
//
//========================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "Xmodel.h"
#include "object3D.h"
#include "sound.h"
class CFade;



//===================================
//�V�[���N���X
//===================================
class CScene : public CObject
{
public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}MODE;

	CScene();					//�R���X�g���N�^
	CScene(MODE Mode);			//�R���X�g���N�^
	~CScene();					//�f�X�g���N�^

	static CScene *Create(MODE Mode);			//��������

	HRESULT Init();								//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��

	MODE GetMode(void);
	void SetMode(MODE Mode);

	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

private:
	MODE m_mode;

	D3DXVECTOR3 pos;
};


//===================================
//�}�l�[�W���̃N���X
//===================================
class CManager
{
public:
	CManager();					//�R���X�g���N�^
	~CManager();				//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	//����������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��

	static CManager *GetInstance();									//�}�l�[�W���[�̃|�C���^��Ԃ��֐�
	CRenderer *GetRenderer() { return m_pRenderer; }				//�������_�[�̃|�C���^��Ԃ��֐�
	CInputKeyboard *GetInputKeyboard() { return m_pInputKeyboard; }	//�L�[�{�[�h�̃|�C���^��Ԃ��֐�
	CInputMouse *GetInputMouse() { return m_pInputMouse; }			//�}�E�X�̃|�C���^��Ԃ��֐�
	CTexture *GetTexture() { return m_pTexture; }					//�e�N�X�`���̃|�C���^��Ԃ��֐�
	CXmodel *GetXmodel() { return m_pXmodel; }						//X���f���̃|�C���^��Ԃ��֐�
	CCamera *GetCamera() { return m_pCamera; }						//�J�����̃|�C���^��Ԃ��֐�
	CLight *GetLight() { return m_pLight; }							//���C�g�̃|�C���^��Ԃ��֐�
	CScene *GetScene() { return m_pScene; }							//�V�[���̃|�C���^��Ԃ��֐�
	CSound *GetSound() { return m_pSound; }							//�T�E���h�̃|�C���^��Ԃ��֐�
	CFade *GetFade() { return m_pFade; }							//�t�F�[�h�̃|�C���^��Ԃ��֐�

	void SetMode(CScene::MODE Mode);

private:
	static CManager *m_pManager;								//�}�l�[�W���[�̃|�C���^
	CRenderer *m_pRenderer;										//�������_�[�̃|�C���^
	CInputKeyboard *m_pInputKeyboard;							//�L�[�{�[�h�̃|�C���^
	CInputMouse *m_pInputMouse;									//�}�E�X�̃|�C���^
	CTexture *m_pTexture;										//�e�N�X�`���̃|�C���^
	CXmodel *m_pXmodel;											//X���f���̃|�C���^
	CCamera *m_pCamera;											//�J�����̃|�C���^
	CLight *m_pLight;											//���C�g�̃|�C���^
	CScene *m_pScene;											//�V�[���̃|�C���^
	CSound *m_pSound;											//�T�E���h�̃|�C���^
	CFade *m_pFade;												//�t�F�[�h�̃|�C���^

};


#endif