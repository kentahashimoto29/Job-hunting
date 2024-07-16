//========================================================
// 
// �E�C���h�E�̐����� (wall.cpp)
// Author ���{����
// 
//========================================================
#include "wall.h"
#include "manager.h"

int CWall::m_nIdxTexture = 0;

//========================================================
// �R���X�g���N�^
//========================================================
CWall::CWall()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
}

//========================================================
// �R���X�g���N�^
//========================================================
CWall::CWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
	m_aVerBuff = NULL;
}

//========================================================
// �f�X�g���N�^
//========================================================
CWall::~CWall()
{

}

//========================================================
// ��������
//========================================================
CWall *CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CWall *pWall;

	// 2D�I�u�W�F�N�g�̐���
	pWall = new CWall(pos, rot);

	// ����������
	pWall->Init();

	return pWall;
}

//========================================================
// �|���S���̏���������
//========================================================
HRESULT CWall::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\block000.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			m_nIdxTexture = nCnt;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\block000.jpg");
	}

	BindTexture(m_nIdxTexture);

	CObject3D::Init();

	SetVtxWall();

	SetType(TYPE_WALL);

	return S_OK;
}

//========================================================
// �|���S���̏I������
//========================================================
void CWall::Uninit(void)
{
	CObject3D::Uninit();
}

//========================================================
// �|���S���̍X�V����
//========================================================
void CWall::Update(void)
{

}

//========================================================
// �|���S���̕`�揈��
//========================================================
void CWall::Draw(void)
{
	CObject3D::Draw();
}

//========================================================
// �ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CWall::GetPos(void)
{
	return m_pos;
}

//========================================================
// �C���f�b�N�X�o�b�t�@�̃|�C���^��Ԃ�
//========================================================
LPDIRECT3DINDEXBUFFER9 CWall::GetIdxBuff(void)
{
	return m_pIdxBuff;
}