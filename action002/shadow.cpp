//========================================================
// 
// �e�̏��� (shadow.cpp)
// Author ���{����
// 
//========================================================
#include "shadow.h"
#include "manager.h"
#include "game.h"

int CShadow::m_nIdxTexture = 0;

//========================================================
// �R���X�g���N�^
//========================================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
}

//========================================================
// �R���X�g���N�^
//========================================================
CShadow::CShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority) : CObject3D(nPriority)
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
	m_nIdxTexture = SetTex("data\\TEXTURE\\shadow000.jpg");
	BindTexture(m_nIdxTexture);
	CObject3D::Init();
	SetVtxShadow();
	SetType(TYPE_SHADOW);

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