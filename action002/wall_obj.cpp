//========================================================
//
//�E�C���h�E�̐����� (bullet.cpp)
//Author ���{����
//
//========================================================
#include "wall_obj.h"
#include "wall_obj_manager.h"
#include "game.h"
#include "Player3D.h"
#include "block3D.h"
#include "item_throw.h"

//========================================================
//�R���X�g���N�^
//========================================================
CWallObj::CWallObj(int nPriority) : CObjectX(nPriority)
{
}

//========================================================
//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
//========================================================
CWallObj::CWallObj(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority) : CObjectX(nPriority)
{
	m_pos = pos;
	m_rot = rot;
	bCollision = false;
}

//========================================================
//�f�X�g���N�^
//========================================================
CWallObj::~CWallObj()
{

}

//========================================================
//��������
//========================================================
CWallObj *CWallObj::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx)
{
	CWallObj *pEnemy3D;

	//2D�I�u�W�F�N�g�̐���
	pEnemy3D = new CWallObj(pos, rot);

	//����������
	pEnemy3D->Init(nIdx);

	return pEnemy3D;
}

//========================================================
//����������
//========================================================
HRESULT CWallObj::Init(int nIdx)
{
	int nNumVtx;				//���_��
	DWORD dwSizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^

								//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\wall.x",
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

	ReguVtx();

	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();

	CObjectX::Init();

	CObject::SetType(TYPE_WALL);

	m_nIdx = nIdx;

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CWallObj::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================================
//�X�V����
//========================================================
void CWallObj::Update(void)
{

	CScene::MODE mode = CManager::GetInstance()->GetScene()->GetMode();

	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		//�v���C���[�̏����擾
		CPlayer3D *pPlayer = CGame::GetPlayer3D();

		//�����A�C�e���̏����擾
		CItemThrow **ppItemThrow = CGame::GetItemManager()->GetItemThrow();
		CItemThrow *pItemThrow = *ppItemThrow;

		bCollision = CWallObj::Collision(pPlayer, pItemThrow);

		if (bCollision == true)
		{
			return;
		}
	}
}

//========================================================
//�`�揈��
//========================================================
void CWallObj::Draw(void)
{
	CObjectX::Draw();
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CWallObj::GetPos(void)
{
	return m_pos;
}

//========================================================
//�G�̃_���[�W����
//========================================================
void CWallObj::HitEnemy(void)
{
	m_nLife -= 1;
}

//=======================================
//���f���̓����蔻��
//=======================================
bool CWallObj::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 OldPos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	bool b = false;

	//�v���C���[���u���b�N�ɂ߂荞��
	if (pPos->x + vtxMin.x < m_pos.x + m_VtxMax.x &&
		pPos->x + vtxMax.x > m_pos.x + m_VtxMin.x &&
		pPos->y + vtxMin.y < m_pos.y + m_VtxMax.y &&
		pPos->y + vtxMax.y > m_pos.y + m_VtxMin.y &&
		pPos->z + vtxMin.z < m_pos.z + m_VtxMax.z &&
		pPos->z + vtxMax.z > m_pos.z + m_VtxMin.z)
	{
		//============================
		//��
		//============================
		if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
			OldPos.y + vtxMin.y >= m_pos.y + m_VtxMax.y)
		{
			//������Ԃ�����
			if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				OldPos.x + vtxMin.x >= m_pos.x + m_VtxMax.x)
			{
			}

			//�E����Ԃ�����
			else  if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				OldPos.x + vtxMax.x <= m_pos.x + m_VtxMin.x)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				OldPos.z + vtxMin.z >= m_pos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
				OldPos.z + vtxMax.z <= m_pos.z + m_VtxMin.z)
			{
			}

			else
			{
				pPos->y = m_pos.y - vtxMin.y - m_VtxMax.y;
				b = true;
			}
		}

		//================================
		//��
		//================================
		if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
			OldPos.y + vtxMax.y <= m_pos.y + m_VtxMin.y)
		{
			//������Ԃ�����
			if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				OldPos.x + vtxMin.x >= m_pos.x + m_VtxMax.x)
			{
			}

			//�E����Ԃ�����
			else  if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				OldPos.x + vtxMax.x <= m_pos.x + m_VtxMin.x)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				OldPos.z + vtxMin.z >= m_pos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
				OldPos.z + vtxMax.z <= m_pos.z + m_VtxMin.z)
			{
			}

			else
			{
				pPos->y = m_pos.y - vtxMax.y;
				b = true;
			}
		}

		//============================
		//�E
		//============================
		if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
			OldPos.x + vtxMax.x <= m_pos.x + m_VtxMin.x)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				OldPos.y + vtxMin.y >= m_pos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				OldPos.y + vtxMax.y <= m_pos.y + m_VtxMin.y)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				OldPos.z + vtxMin.z >= m_pos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= pPos->z + m_VtxMin.z &&
				OldPos.z + vtxMax.z <= m_pos.z + m_VtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x - vtxMax.x + m_VtxMin.x;
				b = true;
			}
		}

		//============================
		//��
		//============================
		if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
			OldPos.x + vtxMin.x >= m_pos.x + m_VtxMax.x)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				OldPos.y + vtxMin.y >= m_pos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				OldPos.y + vtxMax.y <= m_pos.y + m_VtxMin.y)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= pPos->z + m_VtxMax.z &&
				OldPos.z + vtxMin.z >= m_pos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= pPos->z + m_VtxMin.z &&
				OldPos.z + vtxMax.z <= m_pos.z + m_VtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x - vtxMin.x + m_VtxMax.x;
				b = true;
			}
		}

		//============================
		//����
		//============================
		if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
			OldPos.z + vtxMin.z >= m_pos.z + m_VtxMax.z)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				OldPos.y + vtxMin.y >= m_pos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				OldPos.y + vtxMax.y <= m_pos.y + m_VtxMin.y)
			{
			}

			//�E����Ԃ�����
			else if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				OldPos.x + vtxMax.x <= m_pos.x + m_VtxMin.x)
			{
			}

			//������Ԃ�����
			else if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				OldPos.x + vtxMin.x >= m_pos.x + m_VtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z - vtxMin.z + m_VtxMax.z;
				b = true;
			}
		}

		//============================
		//��
		//============================
		if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
			OldPos.z + vtxMax.z <= m_pos.z + m_VtxMin.z)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				OldPos.y + vtxMin.y >= m_pos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				OldPos.y + vtxMax.y <= m_pos.y + m_VtxMin.y)
			{
			}

			//�E����Ԃ�����
			else if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				OldPos.x + vtxMax.x <= m_pos.x + m_VtxMin.x)
			{
			}

			//������Ԃ�����
			else if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				OldPos.x + vtxMin.x >= m_pos.x + m_VtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z - vtxMax.z + m_VtxMin.z;
				b = true;
			}
		}
	}

	return b;
}

//========================================================
//�����蔻��̏���
//========================================================
bool CWallObj::Collision(CPlayer3D *pPlayer, CItemThrow *pItemThrow)
{
	bool b = false;

	if (pPlayer != NULL)
	{
		pPlayer->Collisionbool(&m_pos, m_VtxMax, m_VtxMin, TYPE_WALL);
	}

	return b;
}

//========================================================
//�����蔻��̏���
//========================================================
void CWallObj::ReguVtx()
{
	D3DXVECTOR3 keepMin = m_VtxMin;
	D3DXVECTOR3 keepMax = m_VtxMax;


	m_VtxMin.x = cosf(m_rot.y) * keepMin.x + sinf(m_rot.y) * keepMin.z;
	m_VtxMin.z = cosf(m_rot.y) * keepMin.z + sinf(m_rot.y) * keepMin.x;

	m_VtxMax.x = cosf(m_rot.y) * keepMax.x + sinf(m_rot.y) * keepMax.z;
	m_VtxMax.z = cosf(m_rot.y) * keepMax.z + sinf(m_rot.y) * keepMax.x;

}