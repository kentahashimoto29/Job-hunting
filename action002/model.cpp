//========================================================
//
//ウインドウの生成等 (model.cpp)
//Author 橋本賢太
//
//========================================================
#include "Model.h"
#include "manager.h"
#include "camera.h"
#include "bullet3D.h"

//========================================================
//コンストラクタ
//========================================================
CModel::CModel()
{
	
}

//========================================================
//コンストラクタ
//========================================================
CModel::CModel(D3DXVECTOR3 pos)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = pos;
}

//========================================================
//コンストラクタ
//========================================================
CModel::~CModel()
{

}

//========================================================
//生成処理
//========================================================
CModel *CModel::Create(const char *pFilename, D3DXVECTOR3 pos)
{
	CModel *pModel;

	//モデルの生成
	pModel = new CModel(pos);

	//初期化処理
	pModel->Init(pFilename);

	return pModel;
}

//========================================================
//親モデルの設定
//========================================================
void CModel::SetParent(CModel *pModel)
{
	m_pModel = pModel;
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

//========================================================
//向きを返す
//========================================================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//========================================================
//マトリックスを返す
//========================================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//========================================================
//位置を設定
//========================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//向きを設定
//========================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================================================
//モデルの初期化処理
//========================================================
HRESULT CModel::Init(const char *pFilename)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	return S_OK;
}

//========================================================
//モデルの終了処理
//========================================================
void CModel::Uninit(void)
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

}

//========================================================
//モデルの更新処理
//========================================================
void CModel::Update(void)
{

}

//========================================================
//モデルの描画処理
//========================================================
void CModel::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		//計算用マトリックス
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

	//親がNULLじゃなかった場合
	if (m_pModel != NULL)
	{
		mtxParent = m_pModel->GetMtxWorld();
	}

	//親がNULLだった場合
	else if (m_pModel == NULL)
	{
		/*CPlayer3D *pPlayer3D = CManager::GetPlayer3D();

		mtxParent = pPlayer3D->GetMtxWorld();

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);*/

		//現在(最新)のマトリックスを取得する
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//親のマトリックスと掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}