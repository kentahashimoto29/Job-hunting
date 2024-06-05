//========================================================
//
//�E�C���h�E�̐����� (effect.cpp)
//Author ���{����
//
//========================================================
#include "effect.h"
#include "manager.h"
#include "input.h"

int CEffect::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CEffect::CEffect()
{
	AlphaData = 1.0f;
}

//========================================================
//�R���X�g���N�^
//========================================================
CEffect::CEffect(D3DXVECTOR3 pos)
{
	AlphaData = 1.0f;
	m_pos = pos;
}

//========================================================
//�f�X�g���N�^
//========================================================
CEffect::~CEffect()
{

}

//========================================================
//��������
//========================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos)
{
	CEffect *pEffect;

	//2D�I�u�W�F�N�g�̐���
	pEffect = new CEffect(pos);

	//����������
	pEffect->Init();

	pEffect->BindTexture(m_nIdxTexture);

	return pEffect;
}

//========================================================
//����������
//========================================================
HRESULT CEffect::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\effect000.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");
	}

	CObject2D::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_EFFECT);

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CEffect::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
//�X�V����
//========================================================
void CEffect::Update(void)
{
	AlphaData -= 0.05f;

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 20.0f, m_pos.y - 20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y - 20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 20.0f, m_pos.y + 20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 20.0f, 0.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f * AlphaData);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f * AlphaData);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f * AlphaData);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f * AlphaData);

	//���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();

	if (AlphaData <= 0.0f)
	{
		Release();
	}
}

//========================================================
//�`�揈��
//========================================================
void CEffect::Draw(void)
{
	CObject2D::Draw();
}