//========================================================
// 
// �E�C���h�E�̐����� (input.h)
// Author ���{����
// 
//========================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//===================================
// ���͂̃N���X
//===================================
class CInput
{
public:
	CInput();						// �R���X�g���N�^
	virtual ~CInput();				// �f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// ����������
	virtual void Uninit(void);									// �I������
	virtual void Update(void) = 0;								// �X�V����

protected:
	static LPDIRECTINPUT8 m_pInput;			// �L�[�{�[�h�̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;			// �f�o�C�X�̃|�C���^
};

//===================================
// �L�[�{�[�h�̃N���X
//===================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();				// �R���X�g���N�^
	~CInputKeyboard();				// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	bool GetPress(int nKey);							// �L�[�{�[�h�̃v���X�����擾
	bool GetTrigger(int nKey);							// �L�[�{�[�h�̃g���K�[�����擾
	bool GetOldSPress(int nKey);						// �ЂƂO�̃L�[�{�[�h�̃v���X�����擾
	bool GetOldSTrigger(int nKey);						// �ЂƂO�̃L�[�{�[�h�̃g���K�[�����擾

private:
	BYTE m_aKeyState[256];								// �L�[�{�[�h�̏��
	BYTE m_aKeyStateTrigger[256];						// �L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyOldState[256];							// �ЂƂO�̃L�[�{�[�h�̏��
	BYTE m_aKeyOldStateTrigger[256];					// �ЂƂO�̃L�[�{�[�h�̃g���K�[���
};

//===================================
// �}�E�X�̃N���X
//===================================
class CInputMouse : public CInput
{
public:
	typedef enum
	{
		TYPE_LEFT = 0,
		TYPE_RIGHT,
		TYPE_WHEEL,
		TYPE_MAX,
	}MOUSE_BUTTON;

	CInputMouse();				// �R���X�g���N�^
	~CInputMouse();				// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	bool GetPress(MOUSE_BUTTON type);					// �L�[�{�[�h�̃v���X�����擾
	POINT GetPos(void);
	D3DXVECTOR2 GetMouseMove(void);

	bool OnMouseDown(MOUSE_BUTTON type);

private:
	static DIMOUSESTATE g_CurrentMouseState;
	static DIMOUSESTATE g_PrevMouseState;

	DIMOUSESTATE m_aMouseState;
	POINT Pos;
};
#endif