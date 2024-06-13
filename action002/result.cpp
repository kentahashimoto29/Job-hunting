//========================================================
//
//�E�C���h�E�̐����� (score.cpp)
//Author ���{����
//
//========================================================
#include "result.h"
#include "manager.h"
#include "object2D.h"
#include "fade.h"

//========================================================
//�ÓI�����o�ϐ�
//========================================================
CRanking *CResult::m_pRanking = NULL;
int CResult::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CResult::CResult()
{

}

//========================================================
//�f�X�g���N�^
//========================================================
CResult::~CResult()
{

}

//========================================================
//����������
//========================================================
HRESULT CResult::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\Goal001.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Goal001.jpg");
	}

	m_apObject2D[0] = new CObject2D;

	m_apObject2D[0]->BindTexture(m_nIdxTexture);

	m_apObject2D[0]->Init();

	m_apObject2D[0]->SetVtxResult();

	m_pRanking = CRanking::Create();

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CResult::Uninit(void)
{
	m_apObject2D[0]->Uninit();
	m_pRanking->Uninit();
	CScene::Uninit();
}

//========================================================
//�X�V����
//========================================================
void CResult::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�}�E�X�̎擾
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	 if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		 if (CManager::GetInstance()->GetFade()->GetState() == CFade::FADE_NONE)
		 {
			 CManager::GetInstance()->GetFade()->SetFade(CManager::GetInstance()->GetScene()->MODE_TITLE);
			 b = true;
		 }
	}
}

//========================================================
//�`�揈��
//========================================================
void CResult::Draw(void)
{
	m_apObject2D[0]->Draw();
	m_pRanking->Draw();
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CResult::GetPos(void)
{
	return m_pos;
}

//========================================================
//�����L���O�̃|�C���^��Ԃ��֐�
//========================================================
CRanking *CResult::GetRanking(void)
{
	return m_pRanking;
}
