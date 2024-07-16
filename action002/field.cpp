//========================================================
//
//�E�C���h�E�̐����� (Field.cpp)
//Author ���{����
//
//========================================================
#include "Field.h"
#include "manager.h"

int CField::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CField::CField()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
}

//========================================================
//�R���X�g���N�^
//========================================================
CField::CField(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
	m_aVerBuff = NULL;
}

//========================================================
//�f�X�g���N�^
//========================================================
CField::~CField()
{

}

//========================================================
//��������
//========================================================
CField *CField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CField *pField;

	//2D�I�u�W�F�N�g�̐���
	pField = new CField(pos, rot);

	//����������
	pField->Init();

	return pField;
}

//========================================================
//�|���S���̏���������
//========================================================
HRESULT CField::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\concreat.png" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\concreat.png");
	}

	BindTexture(m_nIdxTexture);

	CObject3D::Init();

	SetVtxField();

	SetType(TYPE_FIELD);
	

	/*//���_�o�b�t�@�����b�N
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[2].pos = D3DXVECTOR3(150.0f, 0.0f, 50.0f);
	pVtx[3].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[4].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	pVtx[5].pos = D3DXVECTOR3(150.0f, 0.0f, -50.0f);
	pVtx[6].pos = D3DXVECTOR3(-50.0f, 0.0f, -150.0f);
	pVtx[7].pos = D3DXVECTOR3(50.0f, 0.0f, -150.0f);
	pVtx[8].pos = D3DXVECTOR3(150.0f, 0.0f, -150.0f);

	for (int nCntField = 0; nCntField < 9; nCntField++)
	{
		pVtx[nCntField].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCntField].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	pVtx[0].tex = D3DXVECTOR2(nCntTexX, nCntTexY);

	//�e�N�X�`�����W�̐ݒ�
	for (int nCnt1 = 0; nCnt1 < 3; nCnt1++)
	{
		for (int nCnt2 = 1; nCnt2 < 4; nCnt2++)
		{
			if (nCnt2 == 1)
			{
				nCntTexY += 1.0f;
			}

			else if (nCnt2 == 2)
			{
				if (nCntTexX == 1.0f)
				{
					nCntTexX = 0.0f;
				}

				else if (nCntTexX == 0.0f)
				{
					nCntTexX = 1.0f;
				}

				if (nCntTexY == 1.0f)
				{
					nCntTexY = 0.0f;
				}

				else if (nCntTexY == 0.0f)
				{
					nCntTexY = 1.0f;
				}
			}

			pVtx[nCnt2 + 3 * nCnt1].tex = D3DXVECTOR2(nCntTexX, nCntTexY);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;					//�C���f�b�N�X���ւ̃|�C���^

								//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();*/

	return S_OK;

	//================================================================================================================================================


	////�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//CTexture *pTexture = CManager::GetTexture();

	//bool bTexture = false;

	//for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	//{
	//	if ("data\\TEXTURE\\block000.jpg" == pTexture->GetName(nCnt))
	//	{
	//		bTexture = true;
	//		break;
	//	}
	//}

	//if (bTexture == false)
	//{
	//	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\block000.jpg");
	//}

	//SetType(TYPE_FIELD);

	////���_�o�b�t�@�𐶐�
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_3D,
	//	D3DPOOL_MANAGED,
	//	&m_aVerBuff,
	//	NULL);

	//VERTEX_3D *pVtx;

	////���_�o�b�t�@�����b�N
	//m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W�̐ݒ�
	//pVtx[0].pos3D = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	//pVtx[1].pos3D = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	//pVtx[2].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	//pVtx[3].pos3D = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	//pVtx[4].pos3D = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	//pVtx[5].pos3D = D3DXVECTOR3(150.0f, 0.0f, -50.0f);
	//pVtx[6].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -150.0f);
	//pVtx[7].pos3D = D3DXVECTOR3(50.0f, 0.0f, -150.0f);
	//pVtx[8].pos3D = D3DXVECTOR3(150.0f, 0.0f, -150.0f);

	//for (int nCntField = 0; nCntField < 4; nCntField++)
	//{
	//	pVtx[nCntField].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//	//���_�J���[�̐ݒ�
	//	pVtx[nCntField].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
	//}

	//pVtx[0].tex3D = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[1].tex3D = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[2].tex3D = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[3].tex3D = D3DXVECTOR2(0.0f, 1.0f);


	////�e�N�X�`�����W�̐ݒ�
	//for (int nCnt1 = 0; nCnt1 < 2; nCnt1++)
	//{
	//	for (int nCnt2 = 1; nCnt2 < 3; nCnt2++)
	//	{
	//		if (nCnt2 == 1)
	//		{
	//			nCntTexY = 1.0f;
	//		}

	//		else if (nCnt2 == 2)
	//		{
	//			if (nCntTexX == 1.0f)
	//			{
	//				nCntTexX = 0.0f;
	//			}

	//			else if (nCntTexX == 0.0f)
	//			{
	//				nCntTexX = 1.0f;
	//			}

	//			if (nCntTexY == 1.0f)
	//			{
	//				nCntTexY = 0.0f;
	//			}

	//			else if (nCntTexY == 0.0f)
	//			{
	//				nCntTexY = 1.0f;
	//			}
	//		}

	//		pVtx[nCnt2 + 3 * nCnt1].tex3D = D3DXVECTOR2(nCntTexX, nCntTexY);
	//	}
	//}

	////���_�o�b�t�@���A�����b�N����
	//m_aVerBuff->Unlock();

	////�C���f�b�N�X�o�b�t�@�̐���
	//pDevice->CreateIndexBuffer(sizeof(WORD) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	D3DFMT_INDEX16,
	//	D3DPOOL_MANAGED,
	//	&m_pIdxBuff,
	//	NULL);

	//WORD *pIdx;					//�C���f�b�N�X���ւ̃|�C���^

	////�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��ւ̃|�C���^���擾
	//m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	////���_�ԍ��f�[�^�̐ݒ�
	//pIdx[0] = 2;
	//pIdx[1] = 0;
	//pIdx[2] = 3;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;
	//pIdx[7] = 6;
	//pIdx[8] = 6;
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;

	////�C���f�b�N�X�o�b�t�@���A�����b�N
	//m_pIdxBuff->Unlock();

	//return S_OK;
}

//========================================================
//�|���S���̏I������
//========================================================
void CField::Uninit(void)
{
	CObject3D::Uninit();
}

//========================================================
//�|���S���̍X�V����
//========================================================
void CField::Update(void)
{
	CObject3D::Update();
}

//========================================================
//�|���S���̕`�揈��
//========================================================
void CField::Draw(void)
{
	CObject3D::Draw();
}

//========================================================
//
//========================================================
D3DXVECTOR3 CField::GetPos(void)
{
	return m_pos;
}

//========================================================
//
//========================================================
LPDIRECT3DINDEXBUFFER9 CField::GetIdxBuff(void)
{
	return m_pIdxBuff;
}