//========================================================
//
//�E�C���h�E�̐����� (result.cpp)
//Author ���{����
//
//========================================================
#include "result.h"
#include "result_obj2D.h"
#include "manager.h"
#include "object2D.h"
#include "fade.h"

#define OBJ_MAX (1)

//========================================================
//�ÓI�����o�ϐ�
//========================================================
CRanking *CResult::m_pRanking = NULL;
CResult_Obj2D *CResult::m_apResultObj = NULL;
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
	m_apResultObj = CResult_Obj2D::Create();
	m_pRanking = CRanking::Create();

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CResult::Uninit(void)
{
	//NULL�`�F�b�N
	if (m_apResultObj != NULL)
	{
		//�I������
		m_apResultObj->Uninit();
		m_apResultObj = NULL;
	}

	//NULL�`�F�b�N
	if (m_pRanking != NULL)
	{
		//�I������
		m_pRanking->Uninit();
		m_pRanking = NULL;
	}

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
	m_apResultObj->Draw();
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
