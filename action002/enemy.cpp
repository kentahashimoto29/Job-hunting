//========================================================
//
//ウインドウの生成等 (enemy.cpp)
//Author 橋本賢太
//
//========================================================
#include "enemy.h"
#include "manager.h"

int CEnemy::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CEnemy::CEnemy()
{

}

//========================================================
//コンストラクタ
//========================================================
CEnemy::CEnemy(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//デストラクタ
//========================================================
CEnemy::~CEnemy()
{

}

//========================================================
//生成処理
//========================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy *pEnemy;

	//2Dオブジェクトの生成
	pEnemy = new CEnemy(pos);

	//初期化処理
	pEnemy->Init();

	pEnemy->BindTexture(m_nIdxTexture);

	return pEnemy;
}

//========================================================
//初期化処理
//========================================================
HRESULT CEnemy::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\enemy000.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\enemy000.jpg");
	}

	CObject2D::Init();

	//種類の設定
	CObject::SetType(TYPE_ENEMY);

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CEnemy::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
//更新処理
//========================================================
void CEnemy::Update(void)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ

								//頂点バッファをロックする
	CObject2D::m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y + 50.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロックする
	CObject2D::m_aVerBuff->Unlock();
}

//========================================================
//描画処理
//========================================================
void CEnemy::Draw(void)
{
	CObject2D::Draw();
}

//D3DXVECTOR3 CEnemy::GetPos(void)
//{
//	return m_pos;
//}