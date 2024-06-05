//========================================================
//
//ウインドウの生成等 (billboard.cpp)
//Author 橋本賢太
//
//========================================================
#include "billboard.h"
#include "manager.h"

//========================================================
//コンストラクタ
//========================================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
	m_pTexture = NULL;
}

//========================================================
//コンストラクタ
//========================================================
CBillboard::~CBillboard()
{

}

//========================================================
//生成処理
//========================================================
CBillboard *CBillboard::Create()
{
	CBillboard *pObject3D;

	//2Dオブジェクトの生成
	pObject3D = new CBillboard;

	//初期化処理
	pObject3D->Init();

	return pObject3D;
}

//========================================================
//ポリゴンの初期化処理
//========================================================
HRESULT CBillboard::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\iwa000.png",
		&m_pTexture);

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_aVerBuff,
		NULL);

	m_pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

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
//ポリゴンの終了処理
//========================================================
void CBillboard::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//頂点バッファの破棄
	if (m_aVerBuff != NULL)
	{
		m_aVerBuff->Release();
		m_aVerBuff = NULL;
	}

}

//========================================================
//ポリゴンの更新処理
//========================================================
void CBillboard::Update(void)
{

}

//========================================================
//ポリゴンの描画処理
//========================================================
void CBillboard::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxTrans;    //計算用マトリックス
	D3DXMATRIX mtxView;     //ビューマトリックス取得

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);           //逆行列を求める
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, m_aVerBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,                  //プリミティブの種類
		0,                                    //最初の頂点インデックス
		2);                                   //プリミティブ数

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//========================================================
//
//========================================================
D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_pos;
}


//========================================================
//位置を返す
//========================================================
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//位置を返す
//========================================================
void CBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}