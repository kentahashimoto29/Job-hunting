//========================================================
//
//�E�C���h�E�̐����� (Manager.cpp)
//Author ���{����
//
//========================================================
#include "manager.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"

//�}�N����`
#define BG_MAX									(3)		//�w�i�̍ő吔

CManager *CManager::m_pManager = NULL;

//========================================================
//�R���X�g���N�^
//========================================================
CManager::CManager()
{
	m_pRenderer = NULL;
	m_pInputKeyboard = NULL;
	m_pInputMouse = NULL;
	m_pTexture = NULL;
	m_pCamera = NULL;
	m_pLight = NULL;
	m_pScene = NULL;
	m_pSound = NULL;
}

//========================================================
//�f�X�g���N�^
//========================================================
CManager::~CManager()
{

}

//========================================================
//����������
//========================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//NULL�`�F�b�N
	if (m_pRenderer == NULL)
	{
		//�����_���[�̐���
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != NULL)
	{
		//����������
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//���������������s�����ꍇ
			return -1;
		}
	}

	//NULL�`�F�b�N
	if (m_pInputKeyboard == NULL)
	{
		//�L�[�{�[�h�̐���
		m_pInputKeyboard = new CInputKeyboard;
	}

	if (m_pInputKeyboard != NULL)
	{
		//����������
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{//���������������s�����ꍇ
			return -1;
		}
	}

	//NULL�`�F�b�N
	if (m_pInputMouse == NULL)
	{
		//�L�[�{�[�h�̐���
		m_pInputMouse = new CInputMouse;
	}

	if (m_pInputMouse != NULL)
	{
		//����������
		if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
		{//���������������s�����ꍇ
			return -1;
		}
	}

	//NULL�`�F�b�N
	if (m_pSound == NULL)
	{
		//�L�[�{�[�h�̐���
		m_pSound = new CSound;
	}

	if (m_pSound != NULL)
	{
		//����������
		if (FAILED(m_pSound->Init(hWnd)))
		{//���������������s�����ꍇ
			return -1;
		}
	}

	m_pTexture = new CTexture;

	//�t�F�[�h�̐���
	m_pFade = new CFade;
	m_pFade->Init();

	//���C�g�̐���
	m_pLight = new CLight;
	m_pLight->Init();

	//�J�����̐���
	m_pCamera = new CCamera;
	m_pCamera->Init();

	SetMode(GetScene()->MODE_GAME);

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CManager::Uninit(void)
{
	//NULL�`�F�b�N
	if (m_pRenderer != NULL)
	{
		//�I������
		m_pRenderer->Uninit();

		delete m_pRenderer;

		m_pRenderer = NULL;
	}

	//NULL�`�F�b�N
	if (m_pInputKeyboard != NULL)
	{
		//�I������
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;

		m_pInputKeyboard = NULL;
	}

	//NULL�`�F�b�N
	if (m_pCamera != NULL)
	{
		//�I������
		m_pCamera->Uninit();

		delete m_pCamera;

		m_pCamera = NULL;
	}

	//NULL�`�F�b�N
	if (m_pLight != NULL)
	{
		//�I������
		m_pLight->Uninit();

		delete m_pLight;

		m_pLight = NULL;
	}
}

//========================================================
//�X�V����
//========================================================
void CManager::Update(void)
{
	//�X�V����
	m_pFade->Update();
	m_pCamera->Update();
	//m_pScene->Update();
	m_pRenderer->Update();
	m_pInputKeyboard->Update();
	m_pInputMouse->Update();
}

//========================================================
//�`�揈��
//========================================================
void CManager::Draw(void)
{
	//�`�揈��
	m_pFade->Draw();
	m_pRenderer->Draw();
}

//========================================================
//�}�l�[�W���[�̃|�C���^��Ԃ��֐�
//========================================================
CManager *CManager::GetInstance(void)
{
	if (m_pManager == NULL)
	{
		return m_pManager = new CManager;
	}

	else
	{
		return m_pManager;
	}
}

//========================================================
//�������_�[�̃|�C���^��Ԃ��֐�
//========================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//========================================================
//�L�[�{�[�h�̃|�C���^��Ԃ��֐�
//========================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//========================================================
//�L�[�{�[�h�̃|�C���^��Ԃ��֐�
//========================================================
CInputMouse *CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//========================================================
//�e�N�X�`���̃|�C���^��Ԃ��֐�
//========================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}

//========================================================
//�J�����̃|�C���^��Ԃ��֐�
//========================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//========================================================
//���C�g�̃|�C���^��Ԃ��֐�
//========================================================
CLight *CManager::GetLight(void)
{
	return m_pLight;
}

//========================================================
//�V�[���̃|�C���^��Ԃ��֐�
//========================================================
CScene *CManager::GetScene(void)
{
	return m_pScene;
}

//========================================================
//�T�E���h�̃|�C���^��Ԃ��֐�
//========================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//========================================================
//�T�E���h�̃|�C���^��Ԃ��֐�
//========================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}

//========================================================
//���[�h�ݒ�
//========================================================
void CManager::SetMode(CScene::MODE Mode)
{
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();

		m_pScene = NULL;

		m_pFade->SetFade(Mode);
	}

	else
	{
		m_pFade->SetFadeFirst(Mode);
	}


	/*if (Mode == CScene::MODE_RESULT)
	{
		CObject::ReleaseAll();
	}*/


	if (m_pScene == NULL)
	{
		m_pScene = CScene::Create(Mode);
	}
}



//========================================================
//�R���X�g���N�^
//========================================================
CScene::CScene()
{

}

//========================================================
//�R���X�g���N�^
//========================================================
CScene::CScene(MODE Mode)
{
	m_mode = Mode;
}

//========================================================
//�f�X�g���N�^
//========================================================
CScene::~CScene()
{

}

//========================================================
//��������
//========================================================
CScene *CScene::Create(MODE Mode)
{
	CScene *pScene = NULL;

	//2D�I�u�W�F�N�g�̐���
	switch (Mode)
	{
	case MODE_TITLE:
		pScene = new CTitle;
		break;

	case MODE_GAME:
		pScene = new CGame;
		break;

	case MODE_RESULT:
		pScene = new CResult;
		break;

	default:
		break;
	}

	//����������
	pScene->Init();

	pScene->m_mode = Mode;

	return pScene;
}

//========================================================
//����������
//========================================================
HRESULT CScene::Init()
{

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CScene::Uninit(void)
{
	Release();
}

//========================================================
//�X�V����
//========================================================
void CScene::Update(void)
{
	
}

//========================================================
//�`�揈��
//========================================================
void CScene::Draw(void)
{

}

//========================================================
//���[�h��Ԃ��֐�
//========================================================
CScene::MODE CScene::GetMode(void)
{
	return m_mode;
}

//========================================================
//���[�h��Ԃ��֐�
//========================================================
void CScene::SetMode(MODE Mode)
{
	m_mode = Mode;
}

//========================================================
//�ʒu��Ԃ��֐�
//========================================================
D3DXVECTOR3 CScene::GetPos(void)
{
	return pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CScene::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CScene::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}