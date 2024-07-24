//========================================================
// 
// �e�̏��� (shadow.cpp)
// Author ���{����
// 
//========================================================
#include "shadow.h"
#include "manager.h"

int CShadow::m_nIdxTexture = 0;

//========================================================
// �R���X�g���N�^
//========================================================
CShadow::CShadow()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
}

//========================================================
// �R���X�g���N�^
//========================================================
CShadow::CShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
	m_aVerBuff = NULL;
}

//========================================================
// �f�X�g���N�^
//========================================================
CShadow::~CShadow()
{

}

//========================================================
// ��������
//========================================================
CShadow *CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CShadow *pField;

	// 2D�I�u�W�F�N�g�̐���
	pField = new CShadow(pos, rot);

	// ����������
	pField->Init();

	return pField;
}

//========================================================
// �|���S���̏���������
//========================================================
HRESULT CShadow::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\shadow000.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\shadow000.jpg");
	}

	BindTexture(m_nIdxTexture);

	CObject3D::Init();

	SetVtxShadow();

	SetType(TYPE_FIELD);

	return S_OK;
}

//========================================================
// �|���S���̏I������
//========================================================
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//========================================================
// �|���S���̍X�V����
//========================================================
void CShadow::Update(void)
{
	CObject3D::Update();
}

//========================================================
// �|���S���̕`�揈��
//========================================================
void CShadow::Draw(void)
{
	CObject3D::Draw();
}

//========================================================
// 
//========================================================
D3DXVECTOR3 CShadow::GetPos(void)
{
	return m_pos;
}

//========================================================
// 
//========================================================
LPDIRECT3DINDEXBUFFER9 CShadow::GetIdxBuff(void)
{
	return m_pIdxBuff;
}