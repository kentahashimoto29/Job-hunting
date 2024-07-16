//========================================================
//
//�E�C���h�E�̐����� (item_manager.h)
//Author ���{����
//
//========================================================
#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_
#include "main.h"
#include "item_throw.h"

//===================================
//�A�C�e���}�l�[�W���[�̃N���X
//===================================
class CItemManager
{
public:
	CItemManager();									//�R���X�g���N�^
	~CItemManager();								//�f�X�g���N�^

	static CItemManager *Create();				//�G�̐���

	HRESULT Init(void);							//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����

	void Release(int nIdx);
	void Kill(void);
	CItemThrow **CItemManager::SetItemThrow(D3DXVECTOR3 pos);

	static int GetNum(void);					//������Ԃ�
	CItemThrow **GetItemThrow(void);			// �G�擾

private:

	CItemThrow *m_pItemThrow[16];				//�����A�C�e���̃|�C���^
	static int m_nNum;							//�A�C�e������
};

#endif#pragma once
