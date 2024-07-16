//========================================================
// 
// �E�C���h�E�̐����� (block3D.cpp)
// Author ���{����
// 
//========================================================
#include "block3D.h"
#include "manager.h"
#include "player3D.h"
#include "game.h"

int CBlock3D::m_nIdxTexture = 0;

//========================================================
// �R���X�g���N�^
//========================================================
CBlock3D::CBlock3D(int nPriority) : CObjectX(nPriority)
{

}

//========================================================
// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
//========================================================
CBlock3D::CBlock3D(D3DXVECTOR3 pos, int nPriority) : CObjectX(nPriority)
{
	m_pos = pos;
}

//========================================================
// �f�X�g���N�^
//========================================================
CBlock3D::~CBlock3D()
{

}

//========================================================
// ��������
//========================================================
CBlock3D *CBlock3D::Create(D3DXVECTOR3 pos)
{
	CBlock3D *pPlayer3D;

	// 2D�I�u�W�F�N�g�̐���
	pPlayer3D = new CBlock3D(pos);

	// ����������
	pPlayer3D->Init();

	return pPlayer3D;
}

//========================================================
// ����������
//========================================================
HRESULT CBlock3D::Init(void)
{
	int nNumVtx;				// ���_��
	DWORD dwSizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\box001.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	// ���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	
	// ���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;					// ���_���W�̑��

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

		pVtxBuff += dwSizeFVF;					// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();
	
	CObject::SetType(TYPE_BLOCK_3D);

	CObjectX::Init();

	return S_OK;
}

//========================================================
// �I������
//========================================================
void CBlock3D::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================================
// �X�V����
//========================================================
void CBlock3D::Update(void)
{
	CGame::GetPlayer3D()->Collision(&m_pos, m_VtxMax, m_VtxMin, CObject::GetType());
}

//========================================================
// �`�揈��
//========================================================
void CBlock3D::Draw(void)
{
	CObjectX::Draw();
}

//========================================================
// �ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CBlock3D::GetPos(void)
{
	return m_pos;
}

//=======================================
// ���f���̓����蔻��
//=======================================
bool CBlock3D::Collisionbool(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pmove, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	bool bland = true;

	// �v���C���[���u���b�N�ɂ߂荞��
	if (m_pos.x + m_VtxMin.x < pPos->x + vtxMax.x &&
		m_pos.x + m_VtxMax.x > pPos->x + vtxMin.x &&
		m_pos.y + m_VtxMin.y < pPos->y + vtxMax.y &&
		m_pos.y + m_VtxMax.y > pPos->y + vtxMin.y &&
		m_pos.z + m_VtxMin.z < pPos->z + vtxMax.z &&
		m_pos.z + m_VtxMax.z > pPos->z + vtxMin.z)
	{
		// ============================
		// ��
		// ============================
		if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
			m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
		{
			// ������Ԃ�����
			if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			// �E����Ԃ�����
			else  if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			// ���ʂ���Ԃ�����
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			// ������Ԃ�����
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->y = m_pos.y + m_VtxMin.y + vtxMin.y;
			}
		}

		// ================================
		// ��
		// ================================
		else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
			m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
		{
			// ������Ԃ�����
			if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			// �E����Ԃ�����
			else  if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			// ���ʂ���Ԃ�����
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			// ������Ԃ�����
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				bland = false;
				pPos->y = m_pos.y + m_VtxMin.y + vtxMax.y;
				pmove->y = 0.0f;
			}
		}

		// ============================
		// �E
		// ============================
		else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
			m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
		{
			// ������Ԃ�����
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			// �ォ��Ԃ�����
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			// ���ʂ���Ԃ�����
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			// ������Ԃ�����
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x + m_VtxMax.x + vtxMax.x;
				pmove->x = 0.0f;
			}
		}

		// ============================
		// ��
		// ============================
		else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
			m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
		{
			// ������Ԃ�����
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			// �ォ��Ԃ�����
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			// ���ʂ���Ԃ�����
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			// ������Ԃ�����
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x + m_VtxMin.x + vtxMin.x;
				pmove->x = 0.0f;
			}
		}

		// ============================
		// ����
		// ============================
		else if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
			m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
		{
			// ������Ԃ�����
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			// �ォ��Ԃ�����
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			// �E����Ԃ�����
			else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			// ������Ԃ�����
			else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z + m_VtxMin.z + vtxMin.z;
				pmove->z = 0.0f;
			}
		}

		// ============================
		// ��
		// ============================
		else if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
			m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
		{
			// ������Ԃ�����
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			// �ォ��Ԃ�����
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			// �E����Ԃ�����
			else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			// ������Ԃ�����
			else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z + m_VtxMax.z + vtxMax.z;
				pmove->z = 0.0f;
			}
		}
	}

	return bland;
}

//=======================================
// ���f���̓����蔻��
//=======================================
void CBlock3D::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pmove, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	// �v���C���[���u���b�N�ɂ߂荞��
	if (m_pos.x + m_VtxMin.x < pPos->x + vtxMax.x &&
		m_pos.x + m_VtxMax.x > pPos->x + vtxMin.x &&
		m_pos.y + m_VtxMin.y < pPos->y + vtxMax.y &&
		m_pos.y + m_VtxMax.y > pPos->y + vtxMin.y &&
		m_pos.z + m_VtxMin.z < pPos->z + vtxMax.z &&
		m_pos.z + m_VtxMax.z > pPos->z + vtxMin.z)
	{
		// ============================
		// ��
		// ============================
		if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
			m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
		{
			// ������Ԃ�����
			if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			// �E����Ԃ�����
			else  if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			// ���ʂ���Ԃ�����
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			// ������Ԃ�����
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->y = m_pos.y + m_VtxMin.y + vtxMin.y;
			}
		}

		// ================================
		// ��
		// ================================
		else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
			m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
		{
			// ������Ԃ�����
			if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			// �E����Ԃ�����
			else  if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			// ���ʂ���Ԃ�����
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			// ������Ԃ�����
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->y = m_pos.y + m_VtxMin.y + vtxMax.y;
				pmove->y = 0.0f;
			}
		}

		// ============================
		// �E
		// ============================
		else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
			m_pos.x + m_VtxMax.x < pPosOld->x + vtxMin.x)
		{
			// ������Ԃ�����
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			// �ォ��Ԃ�����
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			// ���ʂ���Ԃ�����
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			// ������Ԃ�����
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x + m_VtxMax.x + vtxMax.x;
				pmove->x = 0.0f;
			}
		}

		// ============================
		// ��
		// ============================
		else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
			m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
		{
			// ������Ԃ�����
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			// �ォ��Ԃ�����
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			// ���ʂ���Ԃ�����
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			// ������Ԃ�����
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x + m_VtxMin.x + vtxMin.x;
				pmove->x = 0.0f;
			}
		}

		// ============================
		// ����
		// ============================
		else if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
			m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
		{
			// ������Ԃ�����
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			// �ォ��Ԃ�����
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			// �E����Ԃ�����
			else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			// ������Ԃ�����
			else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z + m_VtxMin.z + vtxMin.z;
				pmove->z = 0.0f;
			}
		}

		// ============================
		// ��
		// ============================
		else if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
			m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
		{
			// ������Ԃ�����
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			// �ォ��Ԃ�����
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			// �E����Ԃ�����
			else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			// ������Ԃ�����
			else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z + m_VtxMax.z + vtxMax.z;
				pmove->z = 0.0f;
			}
		}
	}
}