//========================================================
// 
// �E�C���h�E�̐����� (item3D.cpp)
// Author ���{����
// 
//========================================================
#include "item3D.h"
#include "manager.h"
#include "input.h"
#include "bullet3D.h"

int CItem3D::m_nIdxTexture = 0;

//========================================================
// �R���X�g���N�^
//========================================================
CItem3D::CItem3D(int nPriority) : CObjectX(nPriority)
{

}

//========================================================
// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
//========================================================
CItem3D::CItem3D(D3DXVECTOR3 pos, int nPriority) : CObjectX(nPriority)
{
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
}

//========================================================
// �f�X�g���N�^
//========================================================
CItem3D::~CItem3D()
{

}

//========================================================
// ��������
//========================================================
CItem3D *CItem3D::Create(D3DXVECTOR3 pos)
{
	CItem3D *pPlayer3D;

	// 2D�I�u�W�F�N�g�̐���
	pPlayer3D = new CItem3D(pos);

	// ����������
	pPlayer3D->Init();

	return pPlayer3D;
}

//========================================================
// ����������void
//========================================================
HRESULT CItem3D::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\voltaction000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	CObjectX::Init();

	// CObject::SetType(TYPE_FACE_X);

	return S_OK;
}

//========================================================
// �I������
//========================================================
void CItem3D::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================================
// �X�V����
//========================================================
void CItem3D::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	/*if (pInputKeyboard->GetTrigger(DIK_SPACE) == TRUE)
	{
		CBullet3D::Create(m_pos, m_rot);
	}*/
}

//========================================================
// �`�揈��
//========================================================
void CItem3D::Draw(void)
{
	CObjectX::Draw();
}

//========================================================
// �ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CItem3D::GetPos(void)
{
	return m_pos;
}