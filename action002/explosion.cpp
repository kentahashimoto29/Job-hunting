//========================================================
//
//ウインドウの生成等 (Player.cpp)
//Author 橋本賢太
//
//========================================================
#include "explosion.h"
#include "manager.h"
#include "input.h"

int CExplosion::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CExplosion::CExplosion()
{

}

//========================================================
//コンストラクタ
//========================================================
CExplosion::CExplosion(D3DXVECTOR3 pos)
{
	m_nCntrAnim = 0;
	m_nPtnAnim = 0;
	m_pos = pos;
}

//========================================================
//デストラクタ
//========================================================
CExplosion::~CExplosion()
{

}

//========================================================
//生成処理
//========================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pBullet;

	//2Dオブジェクトの生成
	pBullet = new CExplosion(pos);

	//初期化処理
	pBullet->Init();

	pBullet->BindTexture(m_nIdxTexture);

	return pBullet;
}

//========================================================
//初期化処理
//========================================================
HRESULT CExplosion::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\explosion000.png");

	CObject2D::Init();

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CExplosion::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
//更新処理
//========================================================
void CExplosion::Update(void)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ

								//頂点バッファをロックする
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y + 50.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f + m_nPtnAnim * 0.125f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f + m_nPtnAnim * 0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_nPtnAnim * 0.125f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f + m_nPtnAnim * 0.125f, 1.0f);

	//頂点バッファをアンロックする
	m_aVerBuff->Unlock();

	//テクスチャ座標の更新
	m_nCntrAnim++;

	if ((m_nCntrAnim % 20) == 0)
	{
		m_nCntrAnim = 0;			//カウンターを初期値に戻す
		m_nPtnAnim++;				//パターンNo.を実行する

		if (m_nPtnAnim > 7)
		{
			m_nPtnAnim = 0;        //パターンNo.を初期値に戻す
			Release();
		}
	}
}

//========================================================
//描画処理
//========================================================
void CExplosion::Draw(void)
{
	CObject2D::Draw();
}