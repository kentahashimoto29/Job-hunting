//========================================================
//
//�E�C���h�E�̐����� (objectX.cpp)
//Author ���{����
//
//========================================================
#include "objectX.h"
#include "manager.h"
#include "camera.h"
#include "manager.h"

//========================================================
//�R���X�g���N�^
//========================================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================================================
//�R���X�g���N�^
//========================================================
CObjectX::~CObjectX()
{

}

//========================================================
//���f���̏���������
//========================================================
HRESULT CObjectX::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
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
//���f���̏I������
//========================================================
void CObjectX::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	Release();
}

//========================================================
//���f���̍X�V����
//========================================================
void CObjectX::Update(void)
{
	
}

//========================================================
//���f���̕`�揈��
//========================================================
void CObjectX::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//
	D3DMATERIAL9 matDef;						//
	D3DXMATERIAL *pMat;							//

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		if (m_IdxTexture[nCntMat] != -1)
		{
			pDevice->SetTexture(0, pTexture->GetAddress(m_IdxTexture[nCntMat]));
		}

		else
		{
			pDevice->SetTexture(0, NULL);
		}

		//���f��(�p�[�c)���`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================================================
//
//========================================================
D3DXVECTOR3 CObjectX::GetPos(void)
{
	return m_pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//========================================================
//�ʒu��Ԃ�
//========================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}