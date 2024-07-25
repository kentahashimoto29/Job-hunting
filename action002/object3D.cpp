//========================================================
// 
// ウインドウの生成等 (Object3D.cpp)
// Author 橋本賢太
// 
//========================================================
#include "object3D.h"
#include "manager.h"

#define SHADOW_SIZE (15.0f)

//========================================================
// コンストラクタ
//========================================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
	m_nTexture = 0;
}

//========================================================
// コンストラクタ
//========================================================
CObject3D::~CObject3D()
{

}

//========================================================
// ポリゴンの初期化処理
//========================================================
HRESULT CObject3D::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_aVerBuff,
		NULL);

	VERTEX_3D *pVtx;

	// 頂点バッファをロック
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_aVerBuff->Unlock();

	return S_OK;
}

//========================================================
// ポリゴンの初期化処理
//========================================================
HRESULT CObject3D::Init(int nWidth)
{
	m_nWidth = nWidth;
	m_nNumVtx = nWidth * 4;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * m_nWidth,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_aVerBuff,
		NULL);

	VERTEX_3D *pVtx;

	// 頂点バッファをロック
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWidth = 0; nCntWidth < m_nWidth; nCntWidth++)
	{// 横の頂点数分繰り返す
		 // 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	m_aVerBuff->Unlock();

	return S_OK;
}

//========================================================
// ポリゴンの終了処理
//========================================================
void CObject3D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_aVerBuff != NULL)
	{
		m_aVerBuff->Release();
		m_aVerBuff = NULL;
	}

	Release();
}

//========================================================
// ポリゴンの更新処理
//========================================================
void CObject3D::Update(void)
{

}

//========================================================
// ポリゴンの描画処理
//========================================================
void CObject3D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans;    // 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, m_aVerBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexture));

	if (GetType() == TYPE_SHADOW)
	{
		//減算合成の設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// 描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,				// プリミティブの種類
		0,									// 最初の頂点インデックス
		2);									// プリミティブ数

	if (GetType() == TYPE_SHADOW)
	{
		//通常の合成に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//========================================================
// テクスチャの番号を割り当てる
//========================================================
void CObject3D::BindTexture(int nTexture)
{
	m_nTexture = nTexture;
}

//========================================================
// 位置を返す
//========================================================
D3DXVECTOR3 CObject3D::GetPos(void)
{
	return m_pos;
}

//========================================================
// 位置を返す
//========================================================
void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// 位置を返す
//========================================================
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================================================
// テクスチャを設定
//========================================================
int CObject3D::SetTex(const char TexName[64])
{
	if (TexName == NULL)
	{
		return -1;
	}

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	int nIdxTexture = 0;
	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if (TexName == pTexture->GetName(nCnt))
		{
			nIdxTexture = nCnt;
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		nIdxTexture = pTexture->Regist(TexName);
	}

	return nIdxTexture;
}

//========================================================
// 位置を返す
//========================================================
void CObject3D::SetVtxField(void)
{
	VERTEX_3D *pVtx;

	// 頂点バッファをロック
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_aVerBuff->Unlock();
}


//========================================================
// 位置を返す
//========================================================
void CObject3D::SetVtxShadow(void)
{
	VERTEX_3D *pVtx;

	// 頂点バッファをロック
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-SHADOW_SIZE, 0.0f, SHADOW_SIZE);
	pVtx[1].pos = D3DXVECTOR3(SHADOW_SIZE, 0.0f, SHADOW_SIZE);
	pVtx[2].pos = D3DXVECTOR3(-SHADOW_SIZE, 0.0f, -SHADOW_SIZE);
	pVtx[3].pos = D3DXVECTOR3(SHADOW_SIZE, 0.0f, -SHADOW_SIZE);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_aVerBuff->Unlock();
}

//========================================================
// 位置を返す
//========================================================
void CObject3D::SetVtxWall()
{
	VERTEX_3D *pVtx;

	// 頂点バッファをロック
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-50.0f, 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-50.0f, -50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0f, -50.0f, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_aVerBuff->Unlock();
}