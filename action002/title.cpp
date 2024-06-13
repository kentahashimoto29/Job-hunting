//========================================================
//
//�E�C���h�E�̐����� (score.cpp)
//Author ���{����
//
//========================================================
#include "title.h"
#include "title_obj2D.h"
#include "object2D.h"
#include "fade.h"

//========================================================
//�ÓI�����o�ϐ�
//========================================================
CTitle_Obj2D *CTitle::m_apTitleObj = NULL;
int CTitle::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CTitle::CTitle()
{
	b = false;
}

//========================================================
//�f�X�g���N�^
//========================================================
CTitle::~CTitle()
{

}

//========================================================
//����������
//========================================================
HRESULT CTitle::Init(void)
{
	m_apTitleObj = CTitle_Obj2D::Create();

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CTitle::Uninit(void)
{
	m_apTitleObj->Uninit();
	CScene::Uninit();
}

//========================================================
//�X�V����
//========================================================
void CTitle::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�}�E�X�̎擾
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	 if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (b != true)
		{
			if (CManager::GetInstance()->GetFade()->GetState() == CFade::FADE_NONE)
			{
				CManager::GetInstance()->GetFade()->SetFade(CManager::GetInstance()->GetScene()->MODE_GAME);
				b = true;
			}
		}
	}
}

//========================================================
//�`�揈��
//========================================================
void CTitle::Draw(void)
{
	m_apTitleObj->Draw();
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CTitle::GetPos(void)
{
	return m_pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CTitle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CTitle::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}