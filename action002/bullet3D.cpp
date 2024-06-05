//========================================================
//
//�E�C���h�E�̐����� (bullet.cpp)
//Author ���{����
//
//========================================================
#include "bullet3D.h"
#include "manager.h"
#include "input.h"
#include "effect.h"
#include "score.h"
#include "enemy3D.h"
#include "sound.h"

#define MAX_OBJECT							(128)		//�I�u�W�F�N�g�̍ő吔

//========================================================
//�R���X�g���N�^
//========================================================
CBullet3D::CBullet3D(int nPriority) : CObjectX(nPriority)
{

}

//========================================================
//�R���X�g���N�^
//========================================================
CBullet3D::CBullet3D(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Mag, int nPriority) : CObjectX(nPriority)
{
	m_nLife = 200;
	m_rot = rot;
	m_pos.x = pos.x - sinf(rot.y) * 33;
	m_pos.z = pos.z - cosf(rot.y) * 33;
	m_move = D3DXVECTOR3(0.0f , 0.0f, 0.0f);

	m_move.x = -sinf(m_rot.y) * Mag;
	m_move.z = -cosf(m_rot.y) * Mag;
}

//========================================================
//�f�X�g���N�^
//========================================================
CBullet3D::~CBullet3D()
{

}

//========================================================
//��������
//========================================================
CBullet3D *CBullet3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Mag)
{
	CBullet3D *pBullet3D;

	//2D�I�u�W�F�N�g�̐���
	pBullet3D = new CBullet3D(pos, rot, Mag);

	//����������
	pBullet3D->Init();

	pBullet3D->SetType(TYPE_BULLET);

	return pBullet3D;
}

//========================================================
//����������
//========================================================
HRESULT CBullet3D::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\bullet000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	CObjectX::Init();

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CBullet3D::Uninit(void)
{
}

//========================================================
//�X�V����
//========================================================
void CBullet3D::Update(void)
{
	//CEnemy3D *pEnemy3D = CManager::GetEnemy3D();

	m_pos += m_move;

	m_nLife--;

	if (CBullet3D::CollisionEnemy(m_pos) == true)
	{
		//pEnemy3D->HitEnemy();

		Release();
	}

	else if (m_nLife <= 0)
	{
		Release();
		//CManager::GetSound()->StopSound(CSound::SOUND_LABEL_SE_SHOT);
	}
}

//========================================================
//�`�揈��
//========================================================
void CBullet3D::Draw(void)
{
	CObjectX::Draw();
}

//========================================================
//�G�ƒe�Ƃ̓����蔻��
//========================================================
bool CBullet3D::CollisionEnemy(D3DXVECTOR3 pos)
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
				if (pos.x > pObject->GetPos().x - 20.0f
					&& pos.x < pObject->GetPos().x + 20.0f
					&& pos.z > pObject->GetPos().z - 20.0f
					&& pos.z < pObject->GetPos().z + 20.0f)
				{
					return true;
				}
			}

			pObject = pObjectNext;
		}
	}

	return false;
}