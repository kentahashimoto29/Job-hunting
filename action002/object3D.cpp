//========================================================
// 
// �E�C���h�E�̐����� (Object3D.cpp)
// Author ���{����
// 
//========================================================
#include "object3D.h"
#include "manager.h"

#define SHADOW_SIZE (15.0f)

//========================================================
// �R���X�g���N�^
//========================================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
	m_nTexture = 0;
}

//========================================================
// �R���X�g���N�^
//========================================================
CObject3D::~CObject3D()
{

}

//========================================================
// �|���S���̏���������
//========================================================
HRESULT CObject3D::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_aVerBuff,
		NULL);

	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();

	return S_OK;
}

//========================================================
// �|���S���̏���������
//========================================================
HRESULT CObject3D::Init(int nWidth)
{
	m_nWidth = nWidth;
	m_nNumVtx = nWidth * 4;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * m_nWidth,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_aVerBuff,
		NULL);

	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWidth = 0; nCntWidth < m_nWidth; nCntWidth++)
	{// ���̒��_�����J��Ԃ�
		 // ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();

	return S_OK;
}

//========================================================
// �|���S���̏I������
//========================================================
void CObject3D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_aVerBuff != NULL)
	{
		m_aVerBuff->Release();
		m_aVerBuff = NULL;
	}

	Release();
}

//========================================================
// �|���S���̍X�V����
//========================================================
void CObject3D::Update(void)
{

}

//========================================================
// �|���S���̕`�揈��
//========================================================
void CObject3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans;    // �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, m_aVerBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexture));

	if (GetType() == TYPE_SHADOW)
	{
		//���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// �`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,				// �v���~�e�B�u�̎��
		0,									// �ŏ��̒��_�C���f�b�N�X
		2);									// �v���~�e�B�u��

	if (GetType() == TYPE_SHADOW)
	{
		//�ʏ�̍����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//========================================================
// �e�N�X�`���̔ԍ������蓖�Ă�
//========================================================
void CObject3D::BindTexture(int nTexture)
{
	m_nTexture = nTexture;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CObject3D::GetPos(void)
{
	return m_pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================================================
// �e�N�X�`����ݒ�
//========================================================
int CObject3D::SetTex(const char TexName[64])
{
	if (TexName == NULL)
	{
		return -1;
	}

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	int nIdxTexture = 0;
	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if (TexName == pTexture->GetName(nCnt))
		{
			nIdxTexture = nCnt;
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		nIdxTexture = pTexture->Regist(TexName);
	}

	return nIdxTexture;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CObject3D::SetVtxField(void)
{
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}


//========================================================
// �ʒu��Ԃ�
//========================================================
void CObject3D::SetVtxShadow(void)
{
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-SHADOW_SIZE, 0.0f, SHADOW_SIZE);
	pVtx[1].pos = D3DXVECTOR3(SHADOW_SIZE, 0.0f, SHADOW_SIZE);
	pVtx[2].pos = D3DXVECTOR3(-SHADOW_SIZE, 0.0f, -SHADOW_SIZE);
	pVtx[3].pos = D3DXVECTOR3(SHADOW_SIZE, 0.0f, -SHADOW_SIZE);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CObject3D::SetVtxWall()
{
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-50.0f, 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-50.0f, -50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0f, -50.0f, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}