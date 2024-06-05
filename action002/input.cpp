//========================================================
//
//�E�C���h�E�̐����� (input.cpp)
//Author ���{����
//
//========================================================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX									(256)		//�L�[�̍ő吔

LPDIRECTINPUT8 CInput::m_pInput = NULL;
DIMOUSESTATE CInputMouse::g_CurrentMouseState;
DIMOUSESTATE CInputMouse::g_PrevMouseState;

//========================================================
//�R���X�g���N�^
//========================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//========================================================
//�f�X�g���N�^
//========================================================
CInput::~CInput()
{

}

//========================================================
//�L�[�{�[�h�̏���������
//========================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL));
	}

	return S_OK;
}

//========================================================
//�L�[�{�[�h�̏I������
//========================================================
void CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();          //�L�[�{�[�h�ւ̃A�N�Z�X����j��
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//========================================================
//�R���X�g���N�^
//========================================================
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = {};
	}
}

//========================================================
//�f�X�g���N�^
//========================================================
CInputKeyboard::~CInputKeyboard()
{

}

//========================================================
//�C���v�b�g�L�[�{�[�h�̏���������
//========================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l������
	m_pDevice->Acquire();

	return S_OK;
}

//========================================================
//�C���v�b�g�L�[�{�[�h�̏I������
//========================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//========================================================
//�C���v�b�g�L�[�{�[�h�̍X�V����
//========================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];             //�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];			//�L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];																//�L�[�{�[�h�̃v���X����ۑ�
		}
	}

	else
	{
		m_pDevice->Acquire();				//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//========================================================
//�L�[�{�[�h�̃v���X�����擾
//========================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//========================================================
//�L�[�{�[�h�̃g���K�[�����擾
//========================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//========================================================
//�R���X�g���N�^
//========================================================
CInputMouse::CInputMouse()
{
	
}

//========================================================
//�f�X�g���N�^
//========================================================
CInputMouse::~CInputMouse()
{

}

//========================================================
//�}�E�X�̏���������
//========================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l������
	m_pDevice->Acquire();

	//���Ԋu�Ńf�o�C�X�̏��𓯊������Ď擾�ł���悤�ɂ���
	m_pDevice->Poll();

	return S_OK;
}

//========================================================
//�}�E�X�̏I������
//========================================================
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}

//========================================================
//�}�E�X�̍X�V����
//========================================================
void CInputMouse::Update(void)
{
	//�ŐV�}�E�X����ۑ�����
	g_PrevMouseState = g_CurrentMouseState;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(g_CurrentMouseState), &g_CurrentMouseState)))
	{
		m_aMouseState = g_CurrentMouseState;
	}

	else
	{
		m_pDevice->Acquire();				//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}

	GetCursorPos(&Pos);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &Pos);

	Pos.x = Pos.x - 640;
	Pos.y = Pos.y - 360;
}

//========================================================
//�}�E�X�̃v���X�����擾
//========================================================
bool CInputMouse::GetPress(MOUSE_BUTTON type)
{
	return (m_aMouseState.rgbButtons[type] & 0x80) ? true : false;
}

//========================================================
//�}�E�X�̈ʒu���擾
//========================================================
POINT CInputMouse::GetPos(void)
{
	return Pos;
}

//========================================================
//�}�E�X�̈ړ��ʂ��擾
//========================================================
D3DXVECTOR2 CInputMouse::GetMouseMove(void)
{
	return D3DXVECTOR2((float)m_aMouseState.lX, (float)m_aMouseState.lY);
}

//========================================================
// �N���b�N�����u�Ԃ̔���
//========================================================
bool CInputMouse::OnMouseDown(MOUSE_BUTTON type)
{
	if (((g_PrevMouseState.rgbButtons[type] & 0x80) ? true : false) == false &&
		((g_CurrentMouseState.rgbButtons[type] & 0x80) ? true : false) == true)
	{
		return true;
	}

	return false;
}