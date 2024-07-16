//========================================================
// 
// �E�C���h�E�̐����� (Object3D.cpp)
// Author ���{����
// 
//========================================================
#include "mesh_object3D.h"
#include "manager.h"


//========================================================
// �R���X�g���N�^
//========================================================
CMeshObject3D::CMeshObject3D(int nPriority) : CObject3D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
	m_nTexture = 0;
}

//========================================================
// �R���X�g���N�^
//========================================================
CMeshObject3D::~CMeshObject3D()
{

}

//========================================================
// �|���S���̏���������
//========================================================
CMeshObject3D *CMeshObject3D::Create()
{
	//  �����p�̃I�u�W�F�N�g
	CMeshObject3D *pObject3D = NULL;

	if (pObject3D == NULL)
	{//  NULL��������

	 //  �������̊m��
		pObject3D = new CMeshObject3D();

		if (pObject3D != NULL)
		{//  �������̊m�ۂ��o���Ă�����

		 //  ����������
			pObject3D->Init();

			//  �ʒu�E����
			// pObject3D->SetPosition(pos);
			// pObject3D->SetOriginPosition(pos);
			// pObject3D->SetRotation(rot);
		}

		return pObject3D;
	}

	return NULL;
}

//========================================================
// �|���S���̏���������
//========================================================
CMeshObject3D *CMeshObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nHeight, TYPE type, int nPriority)
{
	//  �����p�̃I�u�W�F�N�g
	CMeshObject3D *pObject3D = NULL;

	if (pObject3D == NULL)
	{//  NULL��������

	 //  �������̊m��
		pObject3D = new CMeshObject3D(nPriority);

		if (pObject3D != NULL)
		{//  �������̊m�ۂ��o���Ă�����

		 //  �����̏���n��
			pObject3D->m_nWidth = nWidth;
			pObject3D->m_nHeight = nHeight;


			//  �ʒu�E����
			// pObject3D->SetPosition(pos);
			// pObject3D->SetOriginPosition(pos);
			// pObject3D->SetRotation(rot);

			//  ����������
			pObject3D->Init();
		}

		return pObject3D;
	}

	return NULL;
}

//========================================================
// �|���S���̏���������
//========================================================
HRESULT CMeshObject3D::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	m_nNumVertex = (m_nWidth + 1) * (m_nHeight + 1);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_aVerBuff,
		NULL);

	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (m_type)
	{
	case TYPE_FIELD:
		//  ���_���̐ݒ�
		for (int nCntHeight = 0; nCntHeight < m_nHeight + 1; nCntHeight++)
		{// �c�̒��_�����J��Ԃ�

			for (int nCntWidth = 0; nCntWidth < m_nWidth + 1; nCntWidth++)
			{//  ���̒��_�����J��Ԃ�

			 //  ���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(
					(100 * nCntWidth) - ((100 * m_nWidth) * 0.5f),
					0,
					-((100 * nCntHeight) - ((100 * m_nHeight) * 0.5f)));

				pVtx += 1;
			}
		}
		break;
	}

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




	// // ���_�o�b�t�@�𐶐�
	// pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
	// 	D3DUSAGE_WRITEONLY,
	// 	FVF_VERTEX_3D,
	// 	D3DPOOL_MANAGED,
	// 	&m_aVerBuff,
	// 	NULL);

	// VERTEX_3D *pVtx;

	// // ���_�o�b�t�@�����b�N
	// m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// // ���_���W�̐ݒ�
	// pVtx[0].pos3D = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	// pVtx[1].pos3D = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	// pVtx[2].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	// pVtx[3].pos3D = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	// pVtx[4].pos3D = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	// pVtx[5].pos3D = D3DXVECTOR3(150.0f, 0.0f, -50.0f);
	// pVtx[6].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -150.0f);
	// pVtx[7].pos3D = D3DXVECTOR3(50.0f, 0.0f, -150.0f);
	// pVtx[8].pos3D = D3DXVECTOR3(150.0f, 0.0f, -150.0f);

	// for (int nCntField = 0; nCntField < 4; nCntField++)
	// {
	// 	pVtx[nCntField].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 	// ���_�J���[�̐ݒ�
	// 	pVtx[nCntField].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
	// }

	// pVtx[0].tex3D = D3DXVECTOR2(1.0f, 0.0f);
	// pVtx[1].tex3D = D3DXVECTOR2(1.0f, 1.0f);
	// pVtx[2].tex3D = D3DXVECTOR2(0.0f, 0.0f);
	// pVtx[3].tex3D = D3DXVECTOR2(0.0f, 1.0f);


	// // �e�N�X�`�����W�̐ݒ�
	// for (int nCnt1 = 0; nCnt1 < 2; nCnt1++)
	// {
	// 	for (int nCnt2 = 1; nCnt2 < 3; nCnt2++)
	// 	{
	// 		if (nCnt2 == 1)
	// 		{
	// 			nCntTexY = 1.0f;
	// 		}

	// 		else if (nCnt2 == 2)
	// 		{
	// 			if (nCntTexX == 1.0f)
	// 			{
	// 				nCntTexX = 0.0f;
	// 			}

	// 			else if (nCntTexX == 0.0f)
	// 			{
	// 				nCntTexX = 1.0f;
	// 			}

	// 			if (nCntTexY == 1.0f)
	// 			{
	// 				nCntTexY = 0.0f;
	// 			}

	// 			else if (nCntTexY == 0.0f)
	// 			{
	// 				nCntTexY = 1.0f;
	// 			}
	// 		}

	// 		pVtx[nCnt2 + 3 * nCnt1].tex3D = D3DXVECTOR2(nCntTexX, nCntTexY);
	// 	}
	// }

	// // ���_�o�b�t�@���A�����b�N����
	// m_aVerBuff->Unlock();

	// // �C���f�b�N�X�o�b�t�@�̐���
	// pDevice->CreateIndexBuffer(sizeof(WORD) * 4,
	// 	D3DUSAGE_WRITEONLY,
	// 	D3DFMT_INDEX16,
	// 	D3DPOOL_MANAGED,
	// 	&m_pIdxBuff,
	// 	NULL);

	// WORD *pIdx;					// �C���f�b�N�X���ւ̃|�C���^

	// // �C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��ւ̃|�C���^���擾
	// m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// // ���_�ԍ��f�[�^�̐ݒ�
	// pIdx[0] = 2;
	// pIdx[1] = 0;
	// pIdx[2] = 3;
	// pIdx[3] = 1;
	// pIdx[4] = 5;
	// pIdx[5] = 2;
	// pIdx[6] = 2;
	// pIdx[7] = 6;
	// pIdx[8] = 6;
	// pIdx[9] = 3;
	// pIdx[10] = 7;
	// pIdx[11] = 4;
	// pIdx[12] = 8;
	// pIdx[13] = 5;

	// // �C���f�b�N�X�o�b�t�@���A�����b�N
	// m_pIdxBuff->Unlock();

	// return S_OK;

	return S_OK;
}

//========================================================
// �|���S���̏I������
//========================================================
void CMeshObject3D::Uninit(void)
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
void CMeshObject3D::Update(void)
{

}

//========================================================
// �|���S���̕`�揈��
//========================================================
void CMeshObject3D::Draw(void)
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

	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,                  // �v���~�e�B�u�̎��
		0,                                    // �ŏ��̒��_�C���f�b�N�X
		2);                                   // �v���~�e�B�u��
}

//========================================================
// �e�N�X�`���̔ԍ������蓖�Ă�
//========================================================
void CMeshObject3D::BindTexture(int nTexture)
{
	m_nTexture = nTexture;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CMeshObject3D::GetPos(void)
{
	return m_pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CMeshObject3D::SetVtxField(void)
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