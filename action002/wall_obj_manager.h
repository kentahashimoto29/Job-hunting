//========================================================
// 
// �E�C���h�E�̐����� (wall_obj_manager.h)
// Author ���{����
// 
//========================================================
#ifndef _WALL_OBJ_MANAGER_H_
#define _WALL_OBJ_MANAGER_H_
#include "main.h"
class CWallObj;

//===================================
// �G�}�l�[�W���[�̃N���X
//===================================
class CWallObjManager
{
public:
	CWallObjManager();							// �R���X�g���N�^
	~CWallObjManager();							// �f�X�g���N�^

	static CWallObjManager *Create();			// �G�̐���

	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����

	void Release(int nIdx);
	void Kill(void);
	CWallObj **SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static int GetNum(void);					// ������Ԃ�
	CWallObj **GetWall(void);					// �G�擾

	void ReadWall();

private:

	CWallObj *m_pWall[32];					// �ǂ̃|�C���^
	static int m_nNum;						// ����

	int m_nCreateNum;						// ����
	D3DXVECTOR3 m_nReadPos[256];
	D3DXVECTOR3 m_nReadRot[256];
};

#endif