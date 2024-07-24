//========================================================
// 
// �E�C���h�E�̐����� (skill_UI.cpp)
// Author ���{����
// 
//========================================================
#include "skill_UI.h"
#include "manager.h"
#include "object2D.h"

#define UI_MAX (2)	// UI�̐�

int CSkill_UI::m_nIdxTexture = 0;

//========================================================
// �R���X�g���N�^
//========================================================
CSkill_UI::CSkill_UI()
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	b = false;
}

//========================================================
// �f�X�g���N�^
//========================================================
CSkill_UI::~CSkill_UI()
{

}

//========================================================
// ��������
//========================================================
CSkill_UI *CSkill_UI::Create()
{
	CSkill_UI *pTitleObj;

	// 2D�I�u�W�F�N�g�̐���
	pTitleObj = new CSkill_UI();

	// ����������
	pTitleObj->Init();

	return pTitleObj;
}

//========================================================
// ����������
//========================================================
HRESULT CSkill_UI::Init(void)
{
	for (int i = 0; i < UI_MAX; i++)
	{
		switch (i)
		{
			// �g
		case 0:
			m_apObject2D[i] = new CObject2D;
			m_nIdxTexture = m_apObject2D[i]->SetTex("data\\TEXTURE\\Skill_UI_Frame.png");
			m_apObject2D[i]->BindTexture(m_nIdxTexture);
			m_apObject2D[i]->Init();
			m_apObject2D[i]->SetPos(D3DXVECTOR3(113.0f + 32.5f, 600.0f - 70.0f, 0.0f));
			m_apObject2D[i]->SetSizeX(32.5f);
			m_apObject2D[i]->SetSizeY(70.0f);
			m_apObject2D[i]->SetVtx(m_apObject2D[i]->GetPos(), m_apObject2D[i]->GetSizeX(), m_apObject2D[i]->GetSizeY());
			m_apObject2D[i]->SetType(CObject::TYPE_OBJECT_2D);
			break;

			// �_�b�V��UI
		case 1:
			m_apObject2D[i] = new CObject2D;
			m_nIdxTexture = m_apObject2D[i]->SetTex("data\\TEXTURE\\Skill_UI.png");
			m_apObject2D[i]->BindTexture(m_nIdxTexture);
			m_apObject2D[i]->Init();
			m_apObject2D[i]->SetPos(D3DXVECTOR3(140.0f, 660.0f, 0.0f));
			m_apObject2D[i]->SetSizeX(80.0f);
			m_apObject2D[i]->SetSizeY(48.0f);
			m_apObject2D[i]->SetVtx(m_apObject2D[i]->GetPos(), m_apObject2D[i]->GetSizeX(), m_apObject2D[i]->GetSizeY());
			m_apObject2D[i]->SetType(CObject::TYPE_OBJECT_2D);
			break;
		}
	}

	m_apObjectGauge2D = new CObject2D;
	m_nIdxTexture = m_apObjectGauge2D->SetTex(NULL);
	m_apObjectGauge2D->BindTexture(m_nIdxTexture);
	m_apObjectGauge2D->Init();
	m_apObjectGauge2D->SetPos(D3DXVECTOR3(113.0f, 600.0f, 0.0f));
	m_apObjectGauge2D->SetColor(D3DXCOLOR(0.2f, 0.8f, 0.2f, 1.0f));
	m_apObjectGauge2D->SetGaugeMax(180.0f);
	m_apObjectGauge2D->SetVtxGaugeUI();
	m_apObjectGauge2D->SetType(CObject::TYPE_OBJECT_2D);

	return S_OK;
}

//========================================================
// �I������
//========================================================
void CSkill_UI::Uninit(void)
{
	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != NULL)
		{
			m_apObject2D[nCnt]->Uninit();
		}
	}

	if (m_apObjectGauge2D != NULL)
	{
		m_apObjectGauge2D->Uninit();
	}
	Release();
}

//========================================================
// �X�V����
//========================================================
void CSkill_UI::Update(void)
{
	if (m_apObjectGauge2D != NULL)
	{
		m_apObjectGauge2D->SetVtxGaugeUI();
	}
}

//========================================================
// �`�揈��
//========================================================
void CSkill_UI::Draw(void)
{
	if (m_apObjectGauge2D != NULL)
	{
		m_apObjectGauge2D->Draw();
	}

	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
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
D3DXVECTOR3 CSkill_UI::GetPos(void)
{
	return m_pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CSkill_UI::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CSkill_UI::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}