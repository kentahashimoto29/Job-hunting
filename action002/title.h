//========================================================
// 
// �E�C���h�E�̐����� (title.h)
// Author ���{����
// 
//========================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "main.h"
#include "manager.h"
#include "wall_obj_manager.h"
#include "field.h"
#include "wall.h"

class CObject2D;
class CTitle_Obj2D;

//===================================
// �^�C�g���̃N���X
//===================================
class CTitle : public CScene
{
public:
	CTitle();								// �R���X�g���N�^
	~CTitle();								// �f�X�g���N�^

	HRESULT Init(void);						// ����������
	void Uninit(void);						// �I������
	void Update(void);						// �X�V����
	void Draw(void);						// �`�揈��

	D3DXVECTOR3 GetPos(void);				// �ʒu��Ԃ�
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;						// �I�u�W�F�N�g�̈ʒu

private:
	CObject2D *m_apObject2D[2];				// �^�C�g���̃I�u�W�F�N�g
	static CTitle_Obj2D *m_apTitleObj;
	static CWallObjManager *m_pWallManager;	// ��3D�̃|�C���^
	CField *m_pField[256];					// �t�B�[���h�̃|�C���^
	CWall *m_pWall[256];					// �ǂ̃|�C���^

	static int m_nIdxTexture;				// �e�N�X�`���̔ԍ�
	static float m_nInitPos;

	bool b;
};

#endif