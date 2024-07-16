//========================================================
// 
// �E�C���h�E�̐����� (motion.h)
// Author ���{����
// 
//========================================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"
#include "model.h"
#include <stdio.h>
#include <string.h>

//===================================
// ���f���̃N���X
//===================================
class CMotion
{
public:
	// ���[�V�����̎��
	typedef enum
	{
		TYPE_STAND = 0,
		TYPE_MOVE,
		TYPE_JUMP,
		TYPE_LAND,
		TYPE_RUBBING,
		TYPE_DASH,
		TYPE_END
	}TYPE;

	// �L�[�̍\����
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

	// �L�[���̍\����
	typedef struct
	{
		float nFrame;				// �Đ��t���[��
		KEY aKey[15];				// �e���f���̃L�[�v�f
	}KEY_INFO;

	// ���[�V�������̍\����
	typedef struct
	{
		bool bLoop;					// ���[�v���邩�ǂ���
		int nNumKey;				// �L�[�̑���
		KEY_INFO aKeyInfo[16];		// �L�[���
		TYPE nType;					// ���[�V�����̎��
		int m_nType;
	}INFO;

	CMotion();						// �R���X�g���N�^
	~CMotion();						// �f�X�g���N�^

	void Init(int nType);
	void Set(int nType);
	void Load(void);
	void Updata(void);
	int GetType(void);
	bool IsFinish(void);

	void SetInfo(INFO info);
	void SetType(TYPE nType);
	void SetModel(CModel **ppModel, int nNumModel);

private:
	INFO m_aInfo[6];
	int m_nNumAll;
	int m_nType;
	int m_nTypeOld;
	int m_bLoop[6];
	int m_nNumKey;
	int m_nKey[16];
	float m_nCounter;
	bool m_bFinish;			// �I���������ǂ���

	CModel **m_ppModel;		// ���f���ւ̃|�C���^
	int m_nNumModel;		// ���f���̑���

	int m_nKeyCurrent;
	int m_nKeyTarget;
};
#endif