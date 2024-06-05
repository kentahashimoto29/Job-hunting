//========================================================
//
//�E�C���h�E�̐����� (main.cpp)
//Author ���{����
//
//========================================================
#include "main.h"
#include "object.h"
#include "renderer.h"
#include "manager.h"

//�}�N����`
#define WINDOW_NAME				"3D�A�N�V�����V���[�e�B���O"			//�E�C���h�E�̖��O
#define ID_BUTTON_FINISH		(101)									//�I���{�^����ID

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);		//�E�C���h�E�v���V�[�W��

//�O���[�o���ϐ�
int g_nCountFPS;

//========================================================
//���C���֐�
//========================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	CManager *pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),									//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,											//�E�C���h�E�̃X�^�C��
		WindowProc,											//�E�C���h�E�v���V�[�W��
		0,													//0�ɂ���
		0,													//0�ɂ���
		hInstance,											//�C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION),					//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),						//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),							//�N���C�A���g�̈�̔w�i�F
		NULL,												//���j���[�o�[
		CLASS_NAME,											//�E�C���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)						//�t�@�C���A�C�R��
	};
	HWND hWnd;												//�E�C���h�E�n���h��
	MSG msg;												//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };		//��ʃT�C�Y�̍\����

															//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(
		0,								//�g���E�C���h�E�X�^�C��
		CLASS_NAME,						//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,					//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,			//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,					//�E�C���h�E�̍���X���W
		CW_USEDEFAULT,					//�E�C���h�E�̍���Y���W
		(rect.right - rect.left),		//�E�C���h�E�̕�
		(rect.bottom - rect.top),		//�E�C���h�E�̍���
		NULL,							//�e�E�C���h�E�̃n���h��
		NULL,							//���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,						//�C���X�^���X�n���h��
		NULL);							//�E�C���h�E�쐬�f�[�^

										//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//NULL�`�F�b�N
	pManager = CManager::GetInstance();

	pManager->Init(hInstance, hWnd, TRUE);

	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;                                       //�t���[���J�E���g
	DWORD dwFPSLastTime;                                      //�Ō��FPS���v����������

	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windous�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}

			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
		}

		else
		{//DirectX�̏���

			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
			 //FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;                    //
				dwFrameCount = 0;                                 //
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				if (pManager != NULL)
				{
					//�X�V����
					pManager->Update();

					//�`�揈��
					pManager->Draw();

					dwFrameCount++;                            //
				}
			}
		}
 	}

	//NULL�`�F�b�N
	if (pManager != NULL)
	{
		//�I������
		pManager->Uninit();

		delete pManager;

		pManager = NULL;
	}

	timeEndPeriod(1);

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//========================================================
//�E�C���h�E�v���V�[�W��
//========================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;					//�Ԃ�l���i�[

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:			//�L�[�����Ƀ��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:			//[ESC]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
			break;
		}

	case WM_COMMAND:			//�R�}���h���s�̃��b�Z�[�W
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{//�I���{�^���������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
		}
		break;

	case WM_CLOSE:				//����{�^�������̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}

		else
		{
			return 0;			//�E�B���h�E���I�����Ȃ��悤�ɂ���
		}
		break;

	case WM_LBUTTONDOWN:		//�}�E�X���N���b�N

								//�ΏۃE�B���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//========================================================
//�E�C���h�E�v���V�[�W��
//========================================================
int GetFPSCount(void)
{
	return g_nCountFPS;
}