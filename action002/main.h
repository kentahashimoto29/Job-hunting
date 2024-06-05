//========================================================
//
//�E�C���h�E�̐����� (main.h)
//Author ���{����
//
//========================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#include <windows.h>
#include "d3dx9.h"
#include <stdio.h>
#define DIRECTINPUT_VERSION (0x0800)			//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"								//���͏����ɕK�v
#include "xaudio2.h"

//���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib") 
#pragma comment(lib, "dinput8.lib")									//���͏����ɕK�v

//�}�N����`
#define CLASS_NAME           "WindowClass"								//�E�C���h�E�N���X�̖��O
#define SCREEN_WIDTH			(1280)									//�E�C���h�E�̕�
#define SCREEN_HEIGHT			(720)									//�E�C���h�E�̍���
#define FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D			(D3DFVF_XYZ | D3DFVF_NORMAL |  D3DFVF_DIFFUSE | D3DFVF_TEX1)          //���_�t�H�[�}�b�g3D

//���_���̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_3D;

//���_���̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;			//���_���W
	float rhw;					//���W�ϊ��t�n��
	D3DCOLOR col;				//���_�J���[
	D3DXVECTOR2 tex;			//�e�N�X�`���̍��W
}VERTEX_2D;

int GetFPSCount(void);

#endif