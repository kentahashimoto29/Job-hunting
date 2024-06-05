//========================================================
//
//�E�C���h�E�̐����� (item3D.cpp)
//Author ���{����
//
//========================================================
#include "item_throw.h"
#include "item_manager.h"
#include "manager.h"
#include "input.h"
#include "player3D.h"
#include "game.h"

int CItemThrow::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CItemThrow::CItemThrow(int nPriority) : CObjectX(nPriority)
{

}

//========================================================
//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
//========================================================
CItemThrow::CItemThrow(D3DXVECTOR3 pos, int nPriority) : CObjectX(nPriority)
{
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
}

//========================================================
//�f�X�g���N�^
//========================================================
CItemThrow::~CItemThrow()
{

}

//========================================================
//��������
//========================================================
CItemThrow *CItemThrow::Create(D3DXVECTOR3 pos, int nIdx)
{
	CItemThrow *p;

	//2D�I�u�W�F�N�g�̐���
	p = new CItemThrow(pos);

	//����������
	p->Init(nIdx);

	return p;
}

//========================================================
//����������void
//========================================================
HRESULT CItemThrow::Init(int nIdx)
{
	int nNumVtx;				//���_��
	DWORD dwSizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\voltaction000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());


	//���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;					//���_���W�̑��

		if (m_VtxMin.x > vtx.x)
		{
			m_VtxMin.x = vtx.x;
		}

		else if (m_VtxMax.x < vtx.x)
		{
			m_VtxMax.x = vtx.x;
		}

		if (m_VtxMin.y > vtx.y)
		{
			m_VtxMin.y = vtx.y;
		}

		else if (m_VtxMax.y < vtx.y)
		{
			m_VtxMax.y = vtx.y;
		}

		if (m_VtxMin.z > vtx.z)
		{
			m_VtxMin.z = vtx.z;
		}

		else if (m_VtxMax.z < vtx.z)
		{
			m_VtxMax.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;					//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();

	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObjectX::Init();

	m_nIdx = nIdx;

	//CObject::SetType(TYPE_FACE_X);

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CItemThrow::Uninit(void)
{
	CObjectX::Uninit();

	/*Release();*/
}

//========================================================
//�X�V����
//========================================================
void CItemThrow::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_B) == TRUE)
	{
		bUse = true;

		CPlayer3D *pPlayer = CGame::GetPlayer3D();

		m_pos = pPlayer->GetPos();
		m_rot = pPlayer->GetRot();


		m_move.x = -sinf(m_rot.y) * 8.0f;
		m_move.z = -cosf(m_rot.y) * 8.0f;
	}





	if (m_pos.x <= -50.0f + m_VtxMax.z ||
		m_pos.x >= CGame::GetInitPos() - m_VtxMax.z ||
		m_pos.z <= -50.0f + m_VtxMax.z ||
		m_pos.z >= CGame::GetInitPos() - m_VtxMax.z)
	{
		Release();

		CItemManager *p = CGame::GetItemManager();

		p->Release(m_nIdx);
	}



	m_pos += m_move;
}

//========================================================
//�`�揈��
//========================================================
void CItemThrow::Draw(void)
{
	if (bUse == false)
	{
		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		D3DXMATRIX mtxRot, mtxTrans, mtxParent;		//�v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef;						//
		D3DXMATERIAL *pMat;							//

													//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//�e��NULL����Ȃ������ꍇ
		if (CGame::GetPlayer3D()->GetModel(8) != NULL)
		{
			mtxParent = CGame::GetPlayer3D()->GetModel(8)->GetMtxWorld();
		}

		//�e��NULL�������ꍇ
		else if (CGame::GetPlayer3D()->GetModel(8) == NULL)
		{
			//����(�ŐV)�̃}�g���b�N�X���擾����
			pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
		}

		//�e�̃}�g���b�N�X�Ɗ|�����킹��
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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
			pDevice->SetTexture(0, NULL);

			//���f��(�p�[�c)�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
	
	if (bUse == true)
	{
		CObjectX::Draw();
	}
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CItemThrow::GetPos(void)
{
	return m_pos;
}

//========================================================
//�G�ƃv���C���[�Ƃ̓����蔻��
//========================================================
bool CItemThrow::CollisionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	for (int nCntPriority = 0; nCntPriority < 8; nCntPriority++)
	{
		CObject *pObject = GetTop(nCntPriority);

		TYPE type;

		while (pObject != NULL)
		{
			CObject *pObjectNext = pObject->GetNext();

			//��ނ��擾
			type = pObject->GetType();

			if (type == TYPE_ENEMY)
			{
				if (pos.x + vtxMin.x < m_pos.x + m_VtxMax.x * cosf(m_rot.y) + m_VtxMin.z * sinf(m_rot.y)
					&& pos.x + vtxMax.x > m_pos.x + m_VtxMax.x * cosf(m_rot.y) + m_VtxMin.z * sinf(m_rot.y)
					&& pos.z + vtxMin.z < m_pos.z + m_VtxMax.x * sinf(m_rot.y) + m_VtxMin.z * cosf(m_rot.y)
					&& pos.z + vtxMax.z > m_pos.z + m_VtxMax.x * sinf(m_rot.y) + m_VtxMin.z * cosf(m_rot.y))
				{
					return true;
				}
			}

			pObject = pObjectNext;
		}
	}

	return false;
}