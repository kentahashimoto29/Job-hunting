//========================================================
//
// �E�C���h�E�̐����� (result_obj2D.cpp)
// Author ���{����
//
//========================================================
#include "result_obj2D.h"
#include "manager.h"
#include "object2D.h"
#include "fade.h"

#define OBJ_MAX (3)

int CResult_Obj2D::m_nIdxTexture = 0;

//========================================================
// �R���X�g���N�^
//========================================================
CResult_Obj2D::CResult_Obj2D()
{
	b = false;
}

//========================================================
// �f�X�g���N�^
//========================================================
CResult_Obj2D::~CResult_Obj2D()
{

}

//========================================================
// ��������
//========================================================
CResult_Obj2D *CResult_Obj2D::Create()
{
	CResult_Obj2D *pTitleObj;

	//2D�I�u�W�F�N�g�̐���
	pTitleObj = new CResult_Obj2D();

	//����������
	pTitleObj->Init();

	return pTitleObj;
}

//========================================================
// ����������
//========================================================
HRESULT CResult_Obj2D::Init(void)
{
	for (int i = 0; i < OBJ_MAX; i++)
	{
		switch (i)
		{
			// �w�i
		case 0:
			m_apObject2D[i] = new CObject2D;

			m_nIdxTexture = m_apObject2D[i]->SetTex("data\\TEXTURE\\result02.jpg");

			m_apObject2D[i]->BindTexture(m_nIdxTexture);

			m_apObject2D[i]->Init();

			m_apObject2D[i]->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

			m_apObject2D[i]->SetVtxResult();

			m_apObject2D[i]->SetType(CObject::TYPE_TITLE);
			break;

			// ENTER���S
		case 1:
			m_apObject2D[i] = new CObject2D;

			m_nIdxTexture = m_apObject2D[i]->SetTex("data\\TEXTURE\\black_000.jpg");

			m_apObject2D[i]->BindTexture(m_nIdxTexture);

			m_apObject2D[i]->Init();

			m_apObject2D[i]->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

			m_apObject2D[i]->SetsizeX(200.0f);
			m_apObject2D[i]->SetsizeY(280.0f);

			m_apObject2D[i]->SetVtx(m_apObject2D[i]->GetPos(), m_apObject2D[i]->GetsizeX(), m_apObject2D[i]->GetsizeY());

			m_apObject2D[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			m_apObject2D[i]->SetType(CObject::TYPE_TITLE);
			break;

		case 2:
			//m_apObject2D[i] = new CObject2D;

			//m_nIdxTexture = m_apObject2D[i]->SetTex("data\\TEXTURE\\gametitle.png");

			//m_apObject2D[i]->BindTexture(m_nIdxTexture);

			//m_apObject2D[i]->Init();

			//m_apObject2D[i]->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

			//m_apObject2D[i]->SetVtxTitle();

			//m_apObject2D[i]->SetType(CObject::TYPE_TITLE);
			break;
		}
	}

	return S_OK;
}

//========================================================
// �I������
//========================================================
void CResult_Obj2D::Uninit(void)
{
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != NULL)
		{
			m_apObject2D[nCnt]->Uninit();
		}
	}
	Release();
}

//========================================================
// �X�V����
//========================================================
void CResult_Obj2D::Update(void)
{	

}

//========================================================
// �`�揈��
//========================================================
void CResult_Obj2D::Draw(void)
{
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != NULL)
		{
			m_apObject2D[nCnt]->Draw();
		}
	}
}
//========================================================
// �ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CResult_Obj2D::GetPos(void)
{
	return m_pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CResult_Obj2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CResult_Obj2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}