//========================================================
//
//�E�C���h�E�̐����� (score.cpp)
//Author ���{����
//
//========================================================
#include "title.h"
#include "manager.h"
#include "object2D.h"
#include "fade.h"

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
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\�C���F���J�[�i.png" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\�C���F���J�[�i.png");
	}

	m_apObject2D[0] = new CObject2D;

	m_apObject2D[0]->BindTexture(m_nIdxTexture);

	m_apObject2D[0]->Init();

	m_apObject2D[0]->SetVtxResult();

	m_apObject2D[0]->SetType(CObject::TYPE_TITLE);

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CTitle::Uninit(void)
{
	m_apObject2D[0]->Uninit();
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
	m_apObject2D[0]->Draw();
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