//========================================================
//
//�E�C���h�E�̐����� (score.cpp)
//Author ���{����
//
//========================================================
#include "fade.h"
#include "manager.h"

int CFade::m_nIdxTexture = 0;


//========================================================
//�R���X�g���N�^
//========================================================
CFade::CFade()
{
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pObject2D = NULL;
	m_fade = FADE_NONE;
}

//========================================================
//�f�X�g���N�^
//========================================================
CFade::~CFade()
{

}

//========================================================
//����������
//========================================================
HRESULT CFade::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\black_000.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\black_000.jpg");
	}

	m_pObject2D = new CObject2D(7);

	m_pObject2D->BindTexture(m_nIdxTexture);

	m_pObject2D->Init();

	m_pObject2D->SetVtxFade();

	m_pObject2D->SetColor(m_color);

	m_pObject2D->SetType(CObject::TYPE_FADE);

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CFade::Uninit(void)
{
	m_pObject2D->Uninit();
}

//========================================================
//�X�V����
//========================================================
void CFade::Update(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (m_fade != FADE_NONE)
	{
		//�t�F�[�h�C�����
		if (m_fade == FADE_IN)
		{
			//����L�[(ENTER�L�[)��������܂���
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				CScene::MODE aMode;				//��ʂ̃��[�h�̏��

				aMode = CManager::GetInstance()->GetScene()->GetMode();

				//�^�C�g����ʂȂ�t�F�[�h���X�L�b�v����
				if (aMode == CScene::MODE_TITLE)
				{
					m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				}
			}

			m_color.a -= 0.025f;

			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}

		//�t�F�[�h�A�E�g���
		if (m_fade == FADE_OUT)
		{
			m_color.a += 0.025f;

			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;

				// ���̉�ʂ�
				CManager::GetInstance()->SetMode(m_modenext);
				m_fade = FADE_IN;			//�t�F�[�h�C�����
			}
		}

		m_pObject2D->SetColor(m_color);
	}
}

//========================================================
//�`�揈��
//========================================================
void CFade::Draw(void)
{
	m_pObject2D->Draw();
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CFade::SetFade(CScene::MODE mode)
{

	if (m_fade == FADE_NONE)
	{// �������Ă��Ȃ��Ƃ�

	 // ���̃��[�h�ݒ�
		m_modenext = mode;
		m_fade = FADE_OUT;	// �t�F�[�h�A�E�g��Ԃɐݒ�

									// �F�ݒ�
		m_pObject2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CFade::SetFadeFirst(CScene::MODE mode)
{
	if (m_fade == FADE_NONE)
	{// �������Ă��Ȃ��Ƃ�

	 // ���̃��[�h�ݒ�
		m_modenext = mode;
		m_fade = FADE_IN;	// �t�F�[�h�A�E�g��Ԃɐݒ�

							// �F�ݒ�
		m_pObject2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}


//========================================================
//��ӂ̏��
//========================================================
CFade::FADE CFade::GetState(void)
{
	return m_fade;
}