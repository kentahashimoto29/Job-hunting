//========================================================
//
//�E�C���h�E�̐����� (Object.cpp)
//Author ���{����
//
//========================================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"

//�}�N����`
#define MAX_PLAYER							(2)			//�v���C���[�̍ő吔

CObject *CObject::m_pTop[8] = {};
CObject *CObject::m_pCur[8] = {};

//========================================================
//�R���X�g���N�^
//========================================================
CObject::CObject(int nPriority)
{
	if (nPriority < 0 || nPriority >= 8)
	{// �͈͊O��������

		return;
	}

	if (m_pTop[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;				//�������g����
		m_pCur[nPriority] = m_pTop[nPriority];			//�������g����
	}

	else if (m_pTop[nPriority] != NULL)
	{
		CObject *obj = m_pCur[nPriority];

		m_pCur[nPriority]->m_pNext = this;
		m_pCur[nPriority] = m_pCur[nPriority]->m_pNext;
		m_pCur[nPriority]->m_pPrev = obj;
		m_pCur[nPriority]->m_pNext = NULL;
	}

	m_nPriority = nPriority;	// �D�揇��

	m_type = TYPE_NONE;				//
	m_bflag = false;
}

//========================================================
//�f�X�g���N�^
//========================================================
CObject::~CObject()
{

}

//========================================================
//�������I������
//========================================================
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < 8; nCntPriority++)
	{
		CObject *pObject = m_pTop[nCntPriority];

		while (pObject != NULL)
		{
			CObject *pObjectNext = pObject->m_pNext;

			pObject->Uninit();

			pObject = pObjectNext;
		}
	}
}

//========================================================
//�I�u�W�F�N�g�̍X�V����
//========================================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < 8; nCntPriority++)
	{

		CObject *pObject = m_pTop[nCntPriority];

		while (pObject != NULL)
		{
			CObject *pObjectNext = pObject->m_pNext;

			pObject->Update();

			pObject = pObjectNext;
		}


		for (int nCntPriorityDeath = 0; nCntPriorityDeath < 8; nCntPriorityDeath++)
		{
			// �擪��ۑ�
			pObject = m_pTop[nCntPriorityDeath];

			while (pObject != NULL)
			{// NULL������܂Ŗ������[�v

			 // ���̃I�u�W�F�N�g���ꎞ�ۑ�
				CObject *pObjNext = pObject->m_pNext;

				if (pObject->m_bflag == true)
				{// ���S�t���O�������Ă�����

				 // ���S���S����
					pObject->Death();
				}

				// ���̃I�u�W�F�N�g����
				pObject = pObjNext;
			}
		}
	}
}

//========================================================
//�I�u�W�F�N�g�̕`�揈��
//========================================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	//�J�����̐ݒ�
	pCamera->SetCamera();

	for (int nCntPriority = 0; nCntPriority < 8; nCntPriority++)
	{
		CObject *pObject = m_pTop[nCntPriority];

		while (pObject != NULL)
		{
			CObject *pObjectNext = pObject->m_pNext;

			pObject->Draw();

			pObject = pObjectNext;
		}
	}
}

//========================================================
//n�Ԗڂ̏������I������
//========================================================
void CObject::Release(void)
{
	m_bflag = true;
}

//========================================================
//
//========================================================
void CObject::Death(void)
{
	// ����̔ԍ��ۑ�
	int nPriority = m_nPriority;

	CObject *pObject = this;

	CObject *pObjectNext = pObject->m_pNext;
	CObject *pObjectPrev = pObject->m_pPrev;


	//this�g�� (delete this;)
	//�q��������Next��Next�܂Ŏg��
	if (pObject != m_pCur[nPriority])
	{
		pObjectNext->m_pPrev = pObjectPrev;

		if (pObject != m_pTop[nPriority])
		{
			pObjectPrev->m_pNext = pObjectNext;
		}

		else
		{
			m_pTop[nPriority] = pObjectNext;
		}
	}

	else
	{
		if (pObject != m_pTop[nPriority])
		{
			pObjectPrev->m_pNext = NULL;
			m_pCur[nPriority] = pObjectPrev;
		}

		else
		{
			m_pTop[nPriority] = NULL;
		}
	}

	delete pObject;

	pObject = NULL;
}

//========================================================
//�I�u�W�F�N�g�̍ŏ���Ԃ�
//========================================================
CObject *CObject::GetTop(int nPriority)
{
	return m_pTop[nPriority];
}

//========================================================
//���̃I�u�W�F�N�g��Ԃ�
//========================================================
CObject *CObject::GetNext(void)
{
	return m_pNext;
}

//========================================================
//�I�u�W�F�N�g�̎�ނ�ݒ�
//========================================================
void CObject::SetType(TYPE type)
{
	m_type = type;
}

//========================================================
//�I�u�W�F�N�g�̎�ނ�Ԃ��֐�
//========================================================
CObject::TYPE CObject::GetType(void)
{
	return m_type;
}

//========================================================
//�I�u�W�F�N�g��Ԃ��֐�
//========================================================
CObject *CObject::GetObject()
{
	return this;
}