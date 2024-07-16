//========================================================
// 
// �E�C���h�E�̐����� (enemy.cpp)
// Author ���{����
// 
//========================================================
#include "enemy.h"
#include "manager.h"

int CEnemy::m_nIdxTexture = 0;

//========================================================
// �R���X�g���N�^
//========================================================
CEnemy::CEnemy()
{

}

//========================================================
// �R���X�g���N�^
//========================================================
CEnemy::CEnemy(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// �f�X�g���N�^
//========================================================
CEnemy::~CEnemy()
{

}

//========================================================
// ��������
//========================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy *pEnemy;

	// 2D�I�u�W�F�N�g�̐���
	pEnemy = new CEnemy(pos);

	// ����������
	pEnemy->Init();

	pEnemy->BindTexture(m_nIdxTexture);

	return pEnemy;
}

//========================================================
// ����������
//========================================================
HRESULT CEnemy::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\enemy000.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\enemy000.jpg");
	}

	CObject2D::Init();

	// ��ނ̐ݒ�
	CObject::SetType(TYPE_ENEMY);

	return S_OK;
}

//========================================================
// �I������
//========================================================
void CEnemy::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
// �X�V����
//========================================================
void CEnemy::Update(void)
{
	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

								// ���_�o�b�t�@�����b�N����
	CObject2D::m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y + 50.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	CObject2D::m_aVerBuff->Unlock();
}

//========================================================
// �`�揈��
//========================================================
void CEnemy::Draw(void)
{
	CObject2D::Draw();
}

// D3DXVECTOR3 CEnemy::GetPos(void)
// {
// 	return m_pos;
// }
