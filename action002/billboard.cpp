//========================================================
//
//�E�C���h�E�̐����� (billboard.cpp)
//Author ���{����
//
//========================================================
#include "billboard.h"
#include "manager.h"

//========================================================
//�R���X�g���N�^
//========================================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
	m_pTexture = NULL;
}

//========================================================
//�R���X�g���N�^
//========================================================
CBillboard::~CBillboard()
{

}

//========================================================
//��������
//========================================================
CBillboard *CBillboard::Create()
{
	CBillboard *pObject3D;

	//2D�I�u�W�F�N�g�̐���
	pObject3D = new CBillboard;

	//����������
	pObject3D->Init();

	return pObject3D;
}

//========================================================
//�|���S���̏���������
//========================================================
HRESULT CBillboard::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\iwa000.png",
		&m_pTexture);

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_aVerBuff,
		NULL);

	m_pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();

	return S_OK;
}

//========================================================
//�|���S���̏I������
//========================================================
void CBillboard::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (m_aVerBuff != NULL)
	{
		m_aVerBuff->Release();
		m_aVerBuff = NULL;
	}

}

//========================================================
//�|���S���̍X�V����
//========================================================
void CBillboard::Update(void)
{

}

//========================================================
//�|���S���̕`�揈��
//========================================================
void CBillboard::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxTrans;    //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;     //�r���[�}�g���b�N�X�擾

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);           //�t�s������߂�
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, m_aVerBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,                  //�v���~�e�B�u�̎��
		0,                                    //�ŏ��̒��_�C���f�b�N�X
		2);                                   //�v���~�e�B�u��

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//========================================================
//
//========================================================
D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_pos;
}


//========================================================
//�ʒu��Ԃ�
//========================================================
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}