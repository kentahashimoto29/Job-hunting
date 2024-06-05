//========================================================
//
//ウインドウの生成等 (item3D.cpp)
//Author 橋本賢太
//
//========================================================
#include "item_throw.h"
#include "item_manager.h"
#include "manager.h"
#include "input.h"
#include "player3D.h"
#include "game.h"

int CItemThrow::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CItemThrow::CItemThrow(int nPriority) : CObjectX(nPriority)
{

}

//========================================================
//オーバーライドされたコンストラクタ
//========================================================
CItemThrow::CItemThrow(D3DXVECTOR3 pos, int nPriority) : CObjectX(nPriority)
{
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
}

//========================================================
//デストラクタ
//========================================================
CItemThrow::~CItemThrow()
{

}

//========================================================
//生成処理
//========================================================
CItemThrow *CItemThrow::Create(D3DXVECTOR3 pos, int nIdx)
{
	CItemThrow *p;

	//2Dオブジェクトの生成
	p = new CItemThrow(pos);

	//初期化処理
	p->Init(nIdx);

	return p;
}

//========================================================
//初期化処理void
//========================================================
HRESULT CItemThrow::Init(int nIdx)
{
	int nNumVtx;				//頂点数
	DWORD dwSizeFVF;			//頂点フォーマットのサイズ
	BYTE *pVtxBuff;				//頂点バッファへのポインタ

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\voltaction000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//頂点数を取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());


	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;					//頂点座標の代入

		if (m_VtxMin.x > vtx.x)
		{
			m_VtxMin.x = vtx.x;
		}

		else if (m_VtxMax.x < vtx.x)
		{
			m_VtxMax.x = vtx.x;
		}

		if (m_VtxMin.y > vtx.y)
		{
			m_VtxMin.y = vtx.y;
		}

		else if (m_VtxMax.y < vtx.y)
		{
			m_VtxMax.y = vtx.y;
		}

		if (m_VtxMin.z > vtx.z)
		{
			m_VtxMin.z = vtx.z;
		}

		else if (m_VtxMax.z < vtx.z)
		{
			m_VtxMax.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;					//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObjectX::Init();

	m_nIdx = nIdx;

	//CObject::SetType(TYPE_FACE_X);

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CItemThrow::Uninit(void)
{
	CObjectX::Uninit();

	/*Release();*/
}

//========================================================
//更新処理
//========================================================
void CItemThrow::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_B) == TRUE)
	{
		bUse = true;

		CPlayer3D *pPlayer = CGame::GetPlayer3D();

		m_pos = pPlayer->GetPos();
		m_rot = pPlayer->GetRot();


		m_move.x = -sinf(m_rot.y) * 8.0f;
		m_move.z = -cosf(m_rot.y) * 8.0f;
	}





	if (m_pos.x <= -50.0f + m_VtxMax.z ||
		m_pos.x >= CGame::GetInitPos() - m_VtxMax.z ||
		m_pos.z <= -50.0f + m_VtxMax.z ||
		m_pos.z >= CGame::GetInitPos() - m_VtxMax.z)
	{
		Release();

		CItemManager *p = CGame::GetItemManager();

		p->Release(m_nIdx);
	}



	m_pos += m_move;
}

//========================================================
//描画処理
//========================================================
void CItemThrow::Draw(void)
{
	if (bUse == false)
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
		if (CGame::GetPlayer3D()->GetModel(8) != NULL)
		{
			mtxParent = CGame::GetPlayer3D()->GetModel(8)->GetMtxWorld();
		}

		//親がNULLだった場合
		else if (CGame::GetPlayer3D()->GetModel(8) == NULL)
		{
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
	
	if (bUse == true)
	{
		CObjectX::Draw();
	}
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CItemThrow::GetPos(void)
{
	return m_pos;
}

//========================================================
//敵とプレイヤーとの当たり判定
//========================================================
bool CItemThrow::CollisionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	for (int nCntPriority = 0; nCntPriority < 8; nCntPriority++)
	{
		CObject *pObject = GetTop(nCntPriority);

		TYPE type;

		while (pObject != NULL)
		{
			CObject *pObjectNext = pObject->GetNext();

			//種類を取得
			type = pObject->GetType();

			if (type == TYPE_ENEMY)
			{
				if (pos.x + vtxMin.x < m_pos.x + m_VtxMax.x * cosf(m_rot.y) + m_VtxMin.z * sinf(m_rot.y)
					&& pos.x + vtxMax.x > m_pos.x + m_VtxMax.x * cosf(m_rot.y) + m_VtxMin.z * sinf(m_rot.y)
					&& pos.z + vtxMin.z < m_pos.z + m_VtxMax.x * sinf(m_rot.y) + m_VtxMin.z * cosf(m_rot.y)
					&& pos.z + vtxMax.z > m_pos.z + m_VtxMax.x * sinf(m_rot.y) + m_VtxMin.z * cosf(m_rot.y))
				{
					return true;
				}
			}

			pObject = pObjectNext;
		}
	}

	return false;
}