//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���{����
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	//*****************************************************************************
	// �T�E���h�ꗗ
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,			// BGM0
		SOUND_LABEL_SE_SHOT,			// �e�̔��ˉ�
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();				//�R���X�g���N�^
	~CSound();				//�f�X�g���N�^

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:

	//*****************************************************************************
	// �T�E���h���̍\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);		// �`�����N�̃`�F�b�N
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);		// �`�����N�f�[�^�̓ǂݍ���

	IXAudio2 *g_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	// �T�E���h�̏��
	SOUNDINFO g_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/bgm000.wav", -1 },		// BGM0
		{ "data/SE/shot000.wav", 0 },	// �ˌ���
	};
};


#endif
