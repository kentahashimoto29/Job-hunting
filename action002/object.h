//========================================================
// 
// �E�C���h�E�̐����� (Object.h)
// Author ���{����
// 
//========================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

//===================================
// �I�u�W�F�N�g�̃N���X
//===================================
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_OBJECT_2D,
		TYPE_OBJECT_3D,
		TYPE_OBJECT_X,
		TYPE_PLATER,
		TYPE_PLAYER_3D,
		TYPE_FACE_X,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_EFFECT,
		TYPE_FIELD,
		TYPE_WALL,
		TYPE_BLOCK_3D,
		TYPE_BLOCK_DEATH,
		TYPE_BLOCK_THROUGH,
		TYPE_FADE,
		TYPE_TITLE,
		TYPE_GAME,
		TYPE_RESULT,
		TYPE_TIME,
		TYPE_MAX,
	}TYPE;

	CObject(int nPriority = 6);
	~CObject();					// �f�X�g���N�^

	virtual HRESULT Init(void) = 0;				// ����������
	virtual void Uninit(void) = 0;				// �I������
	virtual void Update(void) = 0;				// �X�V����
	virtual void Draw(void) = 0;				// �`�揈��

	static void ReleaseAll(void);				// �������I������
	static void UpdateAll(void);				// �I�u�W�F�N�g�̍X�V����
	static void DrawAll(void);					// �I�u�W�F�N�g�̕`�揈��

	void Release(void);							// n�Ԗڂ̏������I������

	void Death(void);					// �������I������

	static int GetNumAll(void);					// �I�u�W�F�N�g�̑���

	static CObject *GetTop(int nPriority);		// �擪�̃I�u�W�F�N�g�擾
	CObject *GetNext(void);						// ���̃I�u�W�F�N�g��Ԃ�

	void SetType(TYPE type);					// ��ނ�ݒ�
	TYPE GetType(void);							// ��ނ�Ԃ�
	CObject *GetObject();						// �I�u�W�F�N�g��

	virtual D3DXVECTOR3 GetPos(void) = 0;		// �I�u�W�F�N�g�̈ʒu��Ԃ�
	virtual void SetPos(D3DXVECTOR3 pos) = 0;		// �I�u�W�F�N�g�̈ʒu��ݒ�
	virtual void SetRot(D3DXVECTOR3 rot) = 0;		// �I�u�W�F�N�g�̌�����ݒ�

	D3DXVECTOR3 m_pos;							// �I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3 m_rot;							// �I�u�W�F�N�g�̈ʒu

protected:

private:
	int m_nPriority;

	static CObject *m_pTop[8];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_pCur[8];	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pPrev;							// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;							// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bflag;								// ���S�t���O

	TYPE m_type;								// �I�u�W�F�N�g�̎��
};

#endif