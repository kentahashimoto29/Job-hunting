//========================================================
//
//ウインドウの生成等 (Object3D.cpp)
//Author 橋本賢太
//
//========================================================
#include "mesh_object3D.h"
#include "manager.h"


//========================================================
//コンストラクタ
//========================================================
CMeshObject3D::CMeshObject3D(int nPriority) : CObject3D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
	m_nTexture = 0;
}

//========================================================
//コンストラクタ
//========================================================
CMeshObject3D::~CMeshObject3D()
{

}

//========================================================
//ポリゴンの初期化処理
//========================================================
CMeshObject3D *CMeshObject3D::Create()
{
	// 生成用のオブジェクト
	CMeshObject3D *pObject3D = NULL;

	if (pObject3D == NULL)
	{// NULLだったら

	 // メモリの確保
		pObject3D = new CMeshObject3D();

		if (pObject3D != NULL)
		{// メモリの確保が出来ていたら

		 // 初期化処理
			pObject3D->Init();

			// 位置・向き
			//pObject3D->SetPosition(pos);
			//pObject3D->SetOriginPosition(pos);
			//pObject3D->SetRotation(rot);
		}

		return pObject3D;
	}

	return NULL;
}

//========================================================
//ポリゴンの初期化処理
//========================================================
CMeshObject3D *CMeshObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nHeight, TYPE type, int nPriority)
{
	// 生成用のオブジェクト
	CMeshObject3D *pObject3D = NULL;

	if (pObject3D == NULL)
	{// NULLだったら

	 // メモリの確保
		pObject3D = new CMeshObject3D(nPriority);

		if (pObject3D != NULL)
		{// メモリの確保が出来ていたら

		 // 引数の情報を渡す
			pObject3D->m_nWidth = nWidth;
			pObject3D->m_nHeight = nHeight;


			// 位置・向き
			//pObject3D->SetPosition(pos);
			//pObject3D->SetOriginPosition(pos);
			//pObject3D->SetRotation(rot);

			// 初期化処理
			pObject3D->Init();
		}

		return pObject3D;
	}

	return NULL;
}

//========================================================
//ポリゴンの初期化処理
//========================================================
HRESULT CMeshObject3D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	m_nNumVertex = (m_nWidth + 1) * (m_nHeight + 1);

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_aVerBuff,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (m_type)
	{
	case TYPE_FIELD:
		// 頂点情報の設定
		for (int nCntHeight = 0; nCntHeight < m_nHeight + 1; nCntHeight++)
		{//縦の頂点数分繰り返す

			for (int nCntWidth = 0; nCntWidth < m_nWidth + 1; nCntWidth++)
			{// 横の頂点数分繰り返す

			 // 頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(
					(100 * nCntWidth) - ((100 * m_nWidth) * 0.5f),
					0,
					-((100 * nCntHeight) - ((100 * m_nHeight) * 0.5f)));

				pVtx += 1;
			}
		}
		break;
	}

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




	////頂点バッファを生成
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_3D,
	//	D3DPOOL_MANAGED,
	//	&m_aVerBuff,
	//	NULL);

	//VERTEX_3D *pVtx;

	////頂点バッファをロック
	//m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	////頂点座標の設定
	//pVtx[0].pos3D = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	//pVtx[1].pos3D = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	//pVtx[2].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	//pVtx[3].pos3D = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	//pVtx[4].pos3D = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	//pVtx[5].pos3D = D3DXVECTOR3(150.0f, 0.0f, -50.0f);
	//pVtx[6].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -150.0f);
	//pVtx[7].pos3D = D3DXVECTOR3(50.0f, 0.0f, -150.0f);
	//pVtx[8].pos3D = D3DXVECTOR3(150.0f, 0.0f, -150.0f);

	//for (int nCntField = 0; nCntField < 4; nCntField++)
	//{
	//	pVtx[nCntField].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//	//頂点カラーの設定
	//	pVtx[nCntField].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
	//}

	//pVtx[0].tex3D = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[1].tex3D = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[2].tex3D = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[3].tex3D = D3DXVECTOR2(0.0f, 1.0f);


	////テクスチャ座標の設定
	//for (int nCnt1 = 0; nCnt1 < 2; nCnt1++)
	//{
	//	for (int nCnt2 = 1; nCnt2 < 3; nCnt2++)
	//	{
	//		if (nCnt2 == 1)
	//		{
	//			nCntTexY = 1.0f;
	//		}

	//		else if (nCnt2 == 2)
	//		{
	//			if (nCntTexX == 1.0f)
	//			{
	//				nCntTexX = 0.0f;
	//			}

	//			else if (nCntTexX == 0.0f)
	//			{
	//				nCntTexX = 1.0f;
	//			}

	//			if (nCntTexY == 1.0f)
	//			{
	//				nCntTexY = 0.0f;
	//			}

	//			else if (nCntTexY == 0.0f)
	//			{
	//				nCntTexY = 1.0f;
	//			}
	//		}

	//		pVtx[nCnt2 + 3 * nCnt1].tex3D = D3DXVECTOR2(nCntTexX, nCntTexY);
	//	}
	//}

	////頂点バッファをアンロックする
	//m_aVerBuff->Unlock();

	////インデックスバッファの生成
	//pDevice->CreateIndexBuffer(sizeof(WORD) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	D3DFMT_INDEX16,
	//	D3DPOOL_MANAGED,
	//	&m_pIdxBuff,
	//	NULL);

	//WORD *pIdx;					//インデックス情報へのポインタ

	////インデックスバッファをロックし、頂点番号へのポインタを取得
	//m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	////頂点番号データの設定
	//pIdx[0] = 2;
	//pIdx[1] = 0;
	//pIdx[2] = 3;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;
	//pIdx[7] = 6;
	//pIdx[8] = 6;
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;

	////インデックスバッファをアンロック
	//m_pIdxBuff->Unlock();

	//return S_OK;

	return S_OK;
}

//========================================================
//ポリゴンの終了処理
//========================================================
void CMeshObject3D::Uninit(void)
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
//ポリゴンの更新処理
//========================================================
void CMeshObject3D::Update(void)
{

}

//========================================================
//ポリゴンの描画処理
//========================================================
void CMeshObject3D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans;    //計算用マトリックス

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, m_aVerBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexture));

	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,                  //プリミティブの種類
		0,                                    //最初の頂点インデックス
		2);                                   //プリミティブ数
}

//========================================================
//テクスチャの番号を割り当てる
//========================================================
void CMeshObject3D::BindTexture(int nTexture)
{
	m_nTexture = nTexture;
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CMeshObject3D::GetPos(void)
{
	return m_pos;
}

//========================================================
//位置を返す
//========================================================
void CMeshObject3D::SetVtxField(void)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

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
}