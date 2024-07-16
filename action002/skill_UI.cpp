//========================================================
//
//�E�C���h�E�̐����� (skill_UI.cpp)
//Author ���{����
//
//========================================================
#include "skill_UI.h"
#include "manager.h"
#include "object2D.h"

int CSkill_UI::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CSkill_UI::CSkill_UI()
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	b = false;
}

//========================================================
//�f�X�g���N�^
//========================================================
CSkill_UI::~CSkill_UI()
{

}

//========================================================
//��������
//========================================================
CSkill_UI *CSkill_UI::Create()
{
	CSkill_UI *pTitleObj;

	//2D�I�u�W�F�N�g�̐���
	pTitleObj = new CSkill_UI();

	//����������
	pTitleObj->Init();

	return pTitleObj;
}

//========================================================
//����������
//========================================================
HRESULT CSkill_UI::Init(void)
{
	//m_apObject2D = new CObject2D;
	//m_nIdxTexture = m_apObject2D->SetTex("data\\TEXTURE\\�C���F���J�[�i.png");
	//m_apObject2D->BindTexture(m_nIdxTexture);
	//m_apObject2D->Init();
	//m_apObject2D->SetPos(D3DXVECTOR3(150.0f, 650.0f, 0.0f));
	//m_apObject2D->SetVtxSkillUI();
	//m_apObject2D->SetType(CObject::TYPE_OBJECT_2D);

	m_apObjectGauge2D = new CObject2D;
	m_nIdxTexture = m_apObjectGauge2D->SetTex(NULL);
	m_apObjectGauge2D->BindTexture(m_nIdxTexture);
	m_apObjectGauge2D->Init();
	m_apObjectGauge2D->SetPos(D3DXVECTOR3(150.0f, 650.0f, 0.0f));
	m_apObjectGauge2D->SetColor(D3DXCOLOR(0.2f, 0.8f, 0.2f, 1.0f));
	m_apObjectGauge2D->SetGaugeMax(180.0f);
	m_apObjectGauge2D->SetVtxGaugeUI();
	m_apObjectGauge2D->SetType(CObject::TYPE_OBJECT_2D);

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CSkill_UI::Uninit(void)
{
	if (m_apObject2D != NULL)
	{
		m_apObject2D->Uninit();
	}

	if (m_apObjectGauge2D != NULL)
	{
		m_apObjectGauge2D->Uninit();
	}
	Release();
}

//========================================================
//�X�V����
//========================================================
void CSkill_UI::Update(void)
{
	if (m_apObjectGauge2D != NULL)
	{
		m_apObjectGauge2D->SetVtxGaugeUI();
	}
}

//========================================================
//�`�揈��
//========================================================
void CSkill_UI::Draw(void)
{
	if (m_apObjectGauge2D != NULL)
	{
		m_apObjectGauge2D->Draw();
	}
	if (m_apObject2D != NULL)
	{
		m_apObject2D->Draw();
	}
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CSkill_UI::GetPos(void)
{
	return m_pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CSkill_UI::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CSkill_UI::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}