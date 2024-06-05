//========================================================
//
//ウインドウの生成等 (Object2D.cpp)
//Author 橋本賢太
//
//========================================================
#include "object2D.h"
#include "manager.h"
#include "player.h"
#include "block.h"

//========================================================
//コンストラクタ
//========================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_nTexture = 0;
	m_aVerBuff = NULL;
}

//========================================================
//コンストラクタ
//========================================================
CObject2D::CObject2D(D3DXVECTOR3 Pos, int nPriority) : CObject(nPriority)
{
	m_nTexture = 0;
	m_aVerBuff = NULL;
	m_pos = Pos;
}

//========================================================
//デストラクタ
//========================================================
CObject2D::~CObject2D()
{

}

//========================================================
//初期化処理
//========================================================
HRESULT CObject2D::Init(void)
{
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_aVerBuff,
		NULL);

	VERTEX_2D *pVtx;         //頂点情報へのポインタ

	//頂点バッファをロックする
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_aVerBuff->Unlock();

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CObject2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_aVerBuff != NULL)
	{
		m_aVerBuff->Release();
		m_aVerBuff = NULL;
	}

	Release();
}

//========================================================
//更新処理
//========================================================
void CObject2D::Update(void)
{

}

//========================================================
//描画処理
//========================================================
void CObject2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, m_aVerBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, CManager::GetInstance()->GetTexture()->GetAddress(m_nTexture));

	//if (GetType() == TYPE_EFFECT)
	//{
	//	//αブレンディングを加算合成に設定
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//}

	//描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,				//プリミティブの種類
		0,									//最初の頂点インデックス
		2);									//プリミティブ数

	//if (GetType() == TYPE_EFFECT)
	//{
	//	//αブレンディングを加算合成に設定
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//}
}

//========================================================
//テクスチャの番号を割り当てる
//========================================================
void CObject2D::BindTexture(int nTexture)
{
	m_nTexture = nTexture;
}

//========================================================
//背景の頂点座標を設定
//========================================================
void CObject2D::SetVtxBG(float aTexV)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックする
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, aTexV);
	pVtx[1].tex = D3DXVECTOR2(1.0f, aTexV);
	pVtx[2].tex = D3DXVECTOR2(0.0f, aTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, aTexV + 1.0f);

	//頂点バッファをアンロックする
	m_aVerBuff->Unlock();
}

//========================================================
//スコアの頂点座標を設定
//========================================================
void CObject2D::SetVtxScore(int aTexU, int nCnt)
{
	VERTEX_2D *pVtx;         //頂点情報へのポインタ

	//頂点バッファをロックする
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(nCnt * 40 + 850.0f, 20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(nCnt * 40 + 890.0f, 20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(nCnt * 40 + 850.0f, 70.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(nCnt * 40 + 890.0f, 70.0f, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(aTexU * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(aTexU * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 1.0f);

	//頂点バッファをアンロックする
	m_aVerBuff->Unlock();
}

//========================================================
//ブロックの頂点座標を設定
//========================================================
void CObject2D::SetVtxBlock(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;         //頂点情報へのポインタ

	//頂点バッファをロックする
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + BLOCK_WIDTH, pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + BLOCK_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + BLOCK_WIDTH, pos.y + BLOCK_HEIGHT, 0.0f);

	//頂点バッファをアンロックする
	m_aVerBuff->Unlock();
}

//========================================================
//ブロックの頂点座標を設定
//========================================================
void CObject2D::SetVtxResult()
{
	VERTEX_2D *pVtx;         //頂点情報へのポインタ

							 //頂点バッファをロックする
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_aVerBuff->Unlock();
}

//========================================================
//ブロックの頂点座標を設定
//========================================================
void CObject2D::SetVtxTime(int aTexU, int nCnt)
{
	VERTEX_2D *pVtx;         //頂点情報へのポインタ

							 //頂点バッファをロックする
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(nCnt * 40 + 450.0f, 20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(nCnt * 40 + 490.0f, 20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(nCnt * 40 + 450.0f, 70.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(nCnt * 40 + 490.0f, 70.0f, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(aTexU * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(aTexU * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 1.0f);

	//頂点バッファをアンロックする
	m_aVerBuff->Unlock();
}

//========================================================
//ランキングの頂点座標を設定
//========================================================
void CObject2D::SetVtxRanking(int aTexU, int nCnt, int nCnt2)
{
	VERTEX_2D *pVtx;         //頂点情報へのポインタ

							 //頂点バッファをロックする
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(nCnt * 40 + 580.0f, nCnt2 * 50 + 20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(nCnt * 40 + 620.0f, nCnt2 * 50 + 20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(nCnt * 40 + 580.0f, nCnt2 * 50 + 70.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(nCnt * 40 + 620.0f, nCnt2 * 50 + 70.0f, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(aTexU * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(aTexU * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 1.0f);

	//頂点バッファをアンロックする
	m_aVerBuff->Unlock();
}

//========================================================
//ブロックの頂点座標を設定
//========================================================
void CObject2D::SetVtxFade()
{
	VERTEX_2D *pVtx;         //頂点情報へのポインタ

							 //頂点バッファをロックする
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	//頂点バッファをアンロックする
	m_aVerBuff->Unlock();
}

//==========================================================================
// 色設定
//==========================================================================
void CObject2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;         //頂点情報へのポインタ

	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_aVerBuff->Unlock();
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CObject2D::GetPos(void)
{
	return m_pos;
}

//========================================================
//位置を返す
//========================================================
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//位置を返す
//========================================================
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
