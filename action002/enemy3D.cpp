//========================================================
//
//�E�C���h�E�̐����� (bullet.cpp)
//Author ���{����
//
//========================================================
#include "enemy3D.h"
#include "enemymanager.h"
#include "game.h"
#include "Player3D.h"
#include "block3D.h"
#include "item_throw.h"
#include "wall_obj.h"

//========================================================
//�R���X�g���N�^
//========================================================
CEnemy3D::CEnemy3D(int nPriority) : CObjectX(nPriority)
{
}

//========================================================
//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
//========================================================
CEnemy3D::CEnemy3D(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority) : CObjectX(nPriority)
{
	m_pos = pos;
	m_rot = rot;
	m_nLife = 3;
	bCollision = false;
}

//========================================================
//�f�X�g���N�^
//========================================================
CEnemy3D::~CEnemy3D()
{

}

//========================================================
//��������
//========================================================
CEnemy3D *CEnemy3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx)
{
	CEnemy3D *pEnemy3D;

	//2D�I�u�W�F�N�g�̐���
	pEnemy3D = new CEnemy3D(pos, rot);

	//����������
	pEnemy3D->Init(nIdx);

	return pEnemy3D;
}

//========================================================
//����������
//========================================================
HRESULT CEnemy3D::Init(int nIdx)
{
	int nNumVtx;				//���_��
	DWORD dwSizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\ghost.x",
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

	CObjectX::Init();

	m_VtxMax = D3DXVECTOR3(10.0f, 20.0f, 10.0f);
	m_VtxMin = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);

	CObject::SetType(TYPE_ENEMY);

	m_nIdx = nIdx;

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CEnemy3D::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================================
//�X�V����
//========================================================
void CEnemy3D::Update(void)
{
	float fDistance;

	//�v���C���[�̏����擾
	CPlayer3D *pPlayer = CGame::GetPlayer3D();

	//�����A�C�e���̏����擾
	//CItemThrow **ppItemThrow = CGame::GetItemManager()->GetItemThrow();
	//CItemThrow *pItemThrow = *ppItemThrow;

	//�u���b�N3D�̎擾
	CBlock3D *pBlock = CGame::GetBlock3D();

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	m_Oldpos = m_pos;

	//�Ίp���̒������Z�o
	fDistance = sqrtf((m_pos.x - pPlayer->GetPos().x) * (m_pos.x - pPlayer->GetPos().x)
		+ (m_pos.z - pPlayer->GetPos().z) * (m_pos.z - pPlayer->GetPos().z));

	if (fDistance <= 200.0f)
	{
		//�Ίp���̊p�x���Z�o
		m_rot.y = atan2f(m_pos.x - pPlayer->GetPos().x, m_pos.z - pPlayer->GetPos().z) - D3DX_PI;

		m_move.x = -sinf(D3DX_PI * 0.0f + m_rot.y) * 2.0f;
		m_move.z = -cosf(D3DX_PI * 0.0f + m_rot.y) * 2.0f;

		m_pos += m_move;
	}

	/*if (pInputKeyboard->GetTrigger(DIK_U) == TRUE)
	{
		CBullet3D::Create(m_pos, m_rot, 1.0f);
	}*/

	//pBlock->Collision(&m_pos, &m_Oldpos, &m_move, m_VtxMax, m_VtxMin);

	
	bCollision = Collision();

	if (bCollision == true)
	{
		return;
	}



	if (m_pos.x <= -50.0f + m_VtxMax.z)
	{
		m_pos.x = -50.0f + m_VtxMax.z;
		m_move.x = 0.0f;
	}

	if (m_pos.x >= CGame::GetInitPos() - m_VtxMax.z)
	{
		m_pos.x = CGame::GetInitPos() - m_VtxMax.z;
		m_move.x = 0.0f;
	}

	if (m_pos.z <= -50.0f + m_VtxMax.z)
	{
		m_pos.z = -50.0f + m_VtxMax.z;
		m_move.z = 0.0f;
	}

	if (m_pos.z >= CGame::GetInitPos() - m_VtxMax.z)
	{
		m_pos.z = CGame::GetInitPos() - m_VtxMax.z;
		m_move.z = 0.0f;
	}




	if (m_nLife <= 0)
	{
		Release();
	}
}

//========================================================
//�`�揈��
//========================================================
void CEnemy3D::Draw(void)
{
	CObjectX::Draw();
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CEnemy3D::GetPos(void)
{
	return m_pos;
}

//========================================================
//�G�̃_���[�W����
//========================================================
void CEnemy3D::HitEnemy(void)
{
	 m_nLife -= 1;
}

//========================================================
//�����蔻��̏���
//========================================================
bool CEnemy3D::Collision()
{
	//�v���C���[�̏����擾
	CPlayer3D *pPlayer = CGame::GetPlayer3D();

	//�����A�C�e���̏����擾
	CItemThrow **ppItemThrow = CGame::GetItemManager()->GetItemThrow();
	CItemThrow *pItemThrow = *ppItemThrow;

	CWallObj **ppWall = CGame::GetWallManager()->GetWall();
	CWallObj *pWall = *ppWall;

	bool b = false;

	if (pPlayer != NULL)
	{
		if (pPlayer->CollisionEnemy(m_pos, m_VtxMax, m_VtxMin) == true)
		{
			CGame::GetScore()->AddScore(1);

			Release();

			CEnemyManager *p = CGame::GetEnemyManager();
			p->Release(m_nIdx);

			b = true;

			return b;
		}
	}

	if (pItemThrow != NULL)
	{
		if (pItemThrow->CollisionEnemy(m_pos, m_VtxMax, m_VtxMin) == true)
		{
			Release();

			CEnemyManager *p = CGame::GetEnemyManager();

			p->Release(m_nIdx);

			b = true;

			return b;
		}
	}

	if (pWall != NULL)
	{
		do
		{
			if (pWall->Collision(&m_pos,m_Oldpos, m_VtxMax, m_VtxMin) == true)
			{
				b = true;

				return b;
			}

			ppWall++;
			pWall = *ppWall;
		} while (pWall != NULL);
	}

	return b;
}