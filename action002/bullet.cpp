//========================================================
//
//�E�C���h�E�̐����� (bullet.cpp)
//Author ���{����
//
//========================================================
#include "bullet.h"
#include "manager.h"
#include "input.h"
#include "effect.h"
#include "score.h"

#define MAX_OBJECT							(128)		//�I�u�W�F�N�g�̍ő吔

int CBullet::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CBullet::CBullet()
{
	
}

//========================================================
//�R���X�g���N�^
//========================================================
CBullet::CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_nLife = 200;
	m_pos = pos;
	m_move = move;
}

//========================================================
//�f�X�g���N�^
//========================================================
CBullet::~CBullet()
{

}

//========================================================
//��������
//========================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos)
{
	CBullet *pBullet;

	//2D�I�u�W�F�N�g�̐���
  	pBullet = new CBullet(pos, D3DXVECTOR3(0.0f, -2.0f, 0.0f));

	//����������
	pBullet->Init();

	pBullet->BindTexture(m_nIdxTexture);

	return pBullet;
}

//========================================================
//����������
//========================================================
HRESULT CBullet::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\bullet000.png" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\bullet000.png");
	}

	CObject2D::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_BULLET);

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CBullet::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
//�X�V����
//========================================================
void CBullet::Update(void)
{
	CEffect::Create(m_pos);

	m_pos += m_move;

	m_nLife--;

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 20.0f, m_pos.y - 20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y - 20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 20.0f, m_pos.y + 20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 20.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();

	bool bCollision = CollisionEnemy(m_pos);

	if (bCollision == FALSE)
	{
		if (m_nLife <= 0)
		{
			//CExplosion::Create(m_pos);
			Release();
		}

		else if (m_pos.x >= SCREEN_WIDTH || m_pos.x <= 0 || m_pos.y >= SCREEN_HEIGHT || m_pos.y <= 0)
		{
			//CExplosion::Create(m_pos);
			Release();
		}
	}
}

//========================================================
//�`�揈��
//========================================================
void CBullet::Draw(void)
{
	CObject2D::Draw();
}

//========================================================
//�G�ƒe�Ƃ̓����蔻��
//========================================================
bool CBullet::CollisionEnemy(D3DXVECTOR3 pos)
{
	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	CObject *pObj;

	//	//�I�u�W�F�N�g�̎擾
	//	pObj = CObject::GetObject(nCnt);

	//	if (pObj != NULL)
	//	{
	//		TYPE type;

	//		//��ނ��擾
	//		type = pObj->GetType();

	//		if (type == TYPE_ENEMY)
	//		{
	//			if (pos.x > pObj->GetPos().x - 50.0f
	//				&& pos.x < pObj->GetPos().x + 50.0f
	//				&& pos.y > pObj->GetPos().y - 50.0f
	//				&& pos.y < pObj->GetPos().y + 50.0f)
	//			{
	//				pObj->Uninit();
	//				//CExplosion::Create(m_pos);
	//				Uninit();

	//				//CScore *pScore = CManager::GetScore();
	//				//pScore->AddScore(100);
	//				return TRUE;
	//			}
	//		}
	//	}
	//}
	return FALSE;
}