//========================================================
//
//�E�C���h�E�̐����� (Player.cpp)
//Author ���{����
//
//========================================================
#include "explosion.h"
#include "manager.h"
#include "input.h"

int CExplosion::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CExplosion::CExplosion()
{

}

//========================================================
//�R���X�g���N�^
//========================================================
CExplosion::CExplosion(D3DXVECTOR3 pos)
{
	m_nCntrAnim = 0;
	m_nPtnAnim = 0;
	m_pos = pos;
}

//========================================================
//�f�X�g���N�^
//========================================================
CExplosion::~CExplosion()
{

}

//========================================================
//��������
//========================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pBullet;

	//2D�I�u�W�F�N�g�̐���
	pBullet = new CExplosion(pos);

	//����������
	pBullet->Init();

	pBullet->BindTexture(m_nIdxTexture);

	return pBullet;
}

//========================================================
//����������
//========================================================
HRESULT CExplosion::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\explosion000.png");

	CObject2D::Init();

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CExplosion::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
//�X�V����
//========================================================
void CExplosion::Update(void)
{
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

								//���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y + 50.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f + m_nPtnAnim * 0.125f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f + m_nPtnAnim * 0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_nPtnAnim * 0.125f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f + m_nPtnAnim * 0.125f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();

	//�e�N�X�`�����W�̍X�V
	m_nCntrAnim++;

	if ((m_nCntrAnim % 20) == 0)
	{
		m_nCntrAnim = 0;			//�J�E���^�[�������l�ɖ߂�
		m_nPtnAnim++;				//�p�^�[��No.�����s����

		if (m_nPtnAnim > 7)
		{
			m_nPtnAnim = 0;        //�p�^�[��No.�������l�ɖ߂�
			Release();
		}
	}
}

//========================================================
//�`�揈��
//========================================================
void CExplosion::Draw(void)
{
	CObject2D::Draw();
}