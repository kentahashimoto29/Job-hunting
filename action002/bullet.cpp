//========================================================
//
//ウインドウの生成等 (bullet.cpp)
//Author 橋本賢太
//
//========================================================
#include "bullet.h"
#include "manager.h"
#include "input.h"
#include "effect.h"
#include "score.h"

#define MAX_OBJECT							(128)		//オブジェクトの最大数

int CBullet::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CBullet::CBullet()
{
	
}

//========================================================
//コンストラクタ
//========================================================
CBullet::CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_nLife = 200;
	m_pos = pos;
	m_move = move;
}

//========================================================
//デストラクタ
//========================================================
CBullet::~CBullet()
{

}

//========================================================
//生成処理
//========================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos)
{
	CBullet *pBullet;

	//2Dオブジェクトの生成
  	pBullet = new CBullet(pos, D3DXVECTOR3(0.0f, -2.0f, 0.0f));

	//初期化処理
	pBullet->Init();

	pBullet->BindTexture(m_nIdxTexture);

	return pBullet;
}

//========================================================
//初期化処理
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

	//種類の設定
	CObject::SetType(TYPE_BULLET);

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CBullet::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
//更新処理
//========================================================
void CBullet::Update(void)
{
	CEffect::Create(m_pos);

	m_pos += m_move;

	m_nLife--;

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックする
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 20.0f, m_pos.y - 20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y - 20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 20.0f, m_pos.y + 20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 20.0f, 0.0f);

	//頂点バッファをアンロックする
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
//描画処理
//========================================================
void CBullet::Draw(void)
{
	CObject2D::Draw();
}

//========================================================
//敵と弾との当たり判定
//========================================================
bool CBullet::CollisionEnemy(D3DXVECTOR3 pos)
{
	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	CObject *pObj;

	//	//オブジェクトの取得
	//	pObj = CObject::GetObject(nCnt);

	//	if (pObj != NULL)
	//	{
	//		TYPE type;

	//		//種類を取得
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