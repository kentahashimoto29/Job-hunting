//========================================================
//
//�E�C���h�E�̐����� (enemymanager.h)
//Author ���{����
//
//========================================================
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_
#include "main.h"
#include "enemy3D.h"

//===================================
//�G�}�l�[�W���[�̃N���X
//===================================
class CEnemyManager
{
public:
	CEnemyManager();									//�R���X�g���N�^
	~CEnemyManager();								//�f�X�g���N�^

	static CEnemyManager *Create();				//�G�̐���

	HRESULT Init(void);							//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����

	void Release(int nIdx);
	void Kill(void);
	CEnemy3D **SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void SectionSpawn();

	static int GetNum(void);					//������Ԃ�
	CEnemy3D **GetEnemy(void);	// �G�擾

private:

	CEnemy3D *m_pEnemy3D[512];					//�G�l�~�[3D�̃|�C���^
	static int m_nNum;							//����

	int m_nCreCnt;
};

#endif