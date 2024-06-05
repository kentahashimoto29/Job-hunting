//========================================================
//
//ウインドウの生成等 (ObjectX.cpp)
//Author 橋本賢太
//
//========================================================
#include "objectX.h"
#include "manager.h"
#include "camera.h"

//========================================================
//コンストラクタ
//========================================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================================================
//コンストラクタ
//========================================================
CObjectX::~CObjectX()
{

}

//========================================================
//モデルの初期化処理
//========================================================
HRESULT CObjectX::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	

	return S_OK;
}

//========================================================
//モデルの終了処理
//========================================================
void CObjectX::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//頂点バッファの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	Release();
}

//========================================================
//モデルの更新処理
//========================================================
void CObjectX::Update(void)
{
	
}

//========================================================
//モデルの描画処理
//========================================================
void CObjectX::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//
	D3DMATERIAL9 matDef;						//
	D3DXMATERIAL *pMat;							//

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

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデル(パーツ)も描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//========================================================
//
//========================================================
D3DXVECTOR3 CObjectX::GetPos(void)
{
	return m_pos;
}

//========================================================
//位置を返す
//========================================================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//========================================================
//位置を返す
//========================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}