//========================================================
// 
// �E�C���h�E�̐����� (model.cpp)
// Author ���{����
// 
//========================================================
#include "Model.h"
#include "Xmodel.h"
#include "manager.h"
#include "camera.h"
#include "bullet3D.h"

//========================================================
// �R���X�g���N�^
//========================================================
CModel::CModel()
{
	
}

//========================================================
// �R���X�g���N�^
//========================================================
CModel::CModel(D3DXVECTOR3 pos)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = pos;
}

//========================================================
// �R���X�g���N�^
//========================================================
CModel::~CModel()
{

}

//========================================================
// ��������
//========================================================
CModel *CModel::Create(const char *pFilename, D3DXVECTOR3 pos)
{
	CModel *pModel;

	// ���f���̐���
	pModel = new CModel(pos);

	// ����������
	pModel->Init(pFilename);

	return pModel;
}

//========================================================
// �e���f���̐ݒ�
//========================================================
void CModel::SetParent(CModel *pModel)
{
	m_pModel = pModel;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

//========================================================
// ������Ԃ�
//========================================================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//========================================================
// �}�g���b�N�X��Ԃ�
//========================================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//========================================================
// �ʒu��ݒ�
//========================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// ������ݒ�
//========================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================================================
// ���f���̏���������
//========================================================
HRESULT CModel::Init(const char *pFilename)
{
	CTexture *pT = CManager::GetInstance()->GetTexture();


	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// CManager::GetInstance()->GetXmodel()->Regist(pFilename);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();							// 

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{
			for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
			{
				if (pTexture->GetName(nCnt) != NULL)
				{
					if (strcmp(pMat[nCntMat].pTextureFilename, pTexture->GetName(nCnt)) == 0)
					{
						m_IdxTexture[nCntMat] = nCnt;
						bTexture = true;
						break;
					}
				}
			}
		}

		if (bTexture == false)
		{
			m_IdxTexture[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}

	}


	return S_OK;
}

//========================================================
// ���f���̏I������
//========================================================
void CModel::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

}

//========================================================
// ���f���̍X�V����
//========================================================
void CModel::Update(void)
{

}

//========================================================
// ���f���̕`�揈��
//========================================================
void CModel::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// 
	D3DXMATERIAL *pMat;							// 

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �e��NULL����Ȃ������ꍇ
	if (m_pModel != NULL)
	{
		mtxParent = m_pModel->GetMtxWorld();
	}

	// �e��NULL�������ꍇ
	else if (m_pModel == NULL)
	{
		/*CPlayer3D *pPlayer3D = CManager::GetPlayer3D();

		mtxParent = pPlayer3D->GetMtxWorld();

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);*/

		// ����(�ŐV)�̃}�g���b�N�X���擾����
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// �e�̃}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		if (m_IdxTexture[nCntMat] != -1)
		{
			pDevice->SetTexture(0, pTexture->GetAddress(m_IdxTexture[nCntMat]));
		}

		else
		{
			pDevice->SetTexture(0, NULL);
		}

		// ���f��(�p�[�c)���`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}