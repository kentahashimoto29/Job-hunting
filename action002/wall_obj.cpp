//========================================================
//
//ウインドウの生成等 (bullet.cpp)
//Author 橋本賢太
//
//========================================================
#include "wall_obj.h"
#include "wall_obj_manager.h"
#include "game.h"
#include "Player3D.h"
#include "block3D.h"
#include "item_throw.h"

//========================================================
//コンストラクタ
//========================================================
CWallObj::CWallObj(int nPriority) : CObjectX(nPriority)
{
}

//========================================================
//オーバーライドされたコンストラクタ
//========================================================
CWallObj::CWallObj(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority) : CObjectX(nPriority)
{
	m_pos = pos;
	m_rot = rot;
	bCollision = false;
}

//========================================================
//デストラクタ
//========================================================
CWallObj::~CWallObj()
{

}

//========================================================
//生成処理
//========================================================
CWallObj *CWallObj::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx)
{
	CWallObj *pEnemy3D;

	//2Dオブジェクトの生成
	pEnemy3D = new CWallObj(pos, rot);

	//初期化処理
	pEnemy3D->Init(nIdx);

	return pEnemy3D;
}

//========================================================
//初期化処理
//========================================================
HRESULT CWallObj::Init(int nIdx)
{
	int nNumVtx;				//頂点数
	DWORD dwSizeFVF;			//頂点フォーマットのサイズ
	BYTE *pVtxBuff;				//頂点バッファへのポインタ

								//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\wall.x",
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

	ReguVtx();

	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	CObjectX::Init();

	CObject::SetType(TYPE_WALL);

	m_nIdx = nIdx;

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CWallObj::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================================
//更新処理
//========================================================
void CWallObj::Update(void)
{

	CScene::MODE mode = CManager::GetInstance()->GetScene()->GetMode();

	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		//プレイヤーの情報を取得
		CPlayer3D *pPlayer = CGame::GetPlayer3D();

		//投げアイテムの情報を取得
		CItemThrow **ppItemThrow = CGame::GetItemManager()->GetItemThrow();
		CItemThrow *pItemThrow = *ppItemThrow;

		bCollision = CWallObj::Collision(pPlayer, pItemThrow);

		if (bCollision == true)
		{
			return;
		}
	}
}

//========================================================
//描画処理
//========================================================
void CWallObj::Draw(void)
{
	CObjectX::Draw();
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CWallObj::GetPos(void)
{
	return m_pos;
}

//========================================================
//敵のダメージ処理
//========================================================
void CWallObj::HitEnemy(void)
{
	m_nLife -= 1;
}

//=======================================
//モデルの当たり判定
//=======================================
bool CWallObj::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 OldPos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	bool b = false;

	//プレイヤーがブロックにめり込む
	if (pPos->x + vtxMin.x < m_pos.x + m_VtxMax.x &&
		pPos->x + vtxMax.x > m_pos.x + m_VtxMin.x &&
		pPos->y + vtxMin.y < m_pos.y + m_VtxMax.y &&
		pPos->y + vtxMax.y > m_pos.y + m_VtxMin.y &&
		pPos->z + vtxMin.z < m_pos.z + m_VtxMax.z &&
		pPos->z + vtxMax.z > m_pos.z + m_VtxMin.z)
	{
		//============================
		//下
		//============================
		if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
			OldPos.y + vtxMin.y >= m_pos.y + m_VtxMax.y)
		{
			//左からぶつかった
			if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				OldPos.x + vtxMin.x >= m_pos.x + m_VtxMax.x)
			{
			}

			//右からぶつかった
			else  if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				OldPos.x + vtxMax.x <= m_pos.x + m_VtxMin.x)
			{
			}

			//正面からぶつかった
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				OldPos.z + vtxMin.z >= m_pos.z + m_VtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
				OldPos.z + vtxMax.z <= m_pos.z + m_VtxMin.z)
			{
			}

			else
			{
				pPos->y = m_pos.y - vtxMin.y - m_VtxMax.y;
				b = true;
			}
		}

		//================================
		//上
		//================================
		if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
			OldPos.y + vtxMax.y <= m_pos.y + m_VtxMin.y)
		{
			//左からぶつかった
			if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				OldPos.x + vtxMin.x >= m_pos.x + m_VtxMax.x)
			{
			}

			//右からぶつかった
			else  if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				OldPos.x + vtxMax.x <= m_pos.x + m_VtxMin.x)
			{
			}

			//正面からぶつかった
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				OldPos.z + vtxMin.z >= m_pos.z + m_VtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
				OldPos.z + vtxMax.z <= m_pos.z + m_VtxMin.z)
			{
			}

			else
			{
				pPos->y = m_pos.y - vtxMax.y;
				b = true;
			}
		}

		//============================
		//右
		//============================
		if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
			OldPos.x + vtxMax.x <= m_pos.x + m_VtxMin.x)
		{
			//下からぶつかった
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				OldPos.y + vtxMin.y >= m_pos.y + m_VtxMax.y)
			{
			}

			//上からぶつかった
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				OldPos.y + vtxMax.y <= m_pos.y + m_VtxMin.y)
			{
			}

			//正面からぶつかった
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				OldPos.z + vtxMin.z >= m_pos.z + m_VtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (pPos->z + vtxMax.z >= pPos->z + m_VtxMin.z &&
				OldPos.z + vtxMax.z <= m_pos.z + m_VtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x - vtxMax.x + m_VtxMin.x;
				b = true;
			}
		}

		//============================
		//左
		//============================
		if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
			OldPos.x + vtxMin.x >= m_pos.x + m_VtxMax.x)
		{
			//下からぶつかった
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				OldPos.y + vtxMin.y >= m_pos.y + m_VtxMax.y)
			{
			}

			//上からぶつかった
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				OldPos.y + vtxMax.y <= m_pos.y + m_VtxMin.y)
			{
			}

			//正面からぶつかった
			else  if (pPos->z + vtxMin.z <= pPos->z + m_VtxMax.z &&
				OldPos.z + vtxMin.z >= m_pos.z + m_VtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (pPos->z + vtxMax.z >= pPos->z + m_VtxMin.z &&
				OldPos.z + vtxMax.z <= m_pos.z + m_VtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x - vtxMin.x + m_VtxMax.x;
				b = true;
			}
		}

		//============================
		//正面
		//============================
		if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
			OldPos.z + vtxMin.z >= m_pos.z + m_VtxMax.z)
		{
			//下からぶつかった
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				OldPos.y + vtxMin.y >= m_pos.y + m_VtxMax.y)
			{
			}

			//上からぶつかった
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				OldPos.y + vtxMax.y <= m_pos.y + m_VtxMin.y)
			{
			}

			//右からぶつかった
			else if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				OldPos.x + vtxMax.x <= m_pos.x + m_VtxMin.x)
			{
			}

			//左からぶつかった
			else if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				OldPos.x + vtxMin.x >= m_pos.x + m_VtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z - vtxMin.z + m_VtxMax.z;
				b = true;
			}
		}

		//============================
		//裏
		//============================
		if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
			OldPos.z + vtxMax.z <= m_pos.z + m_VtxMin.z)
		{
			//下からぶつかった
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				OldPos.y + vtxMin.y >= m_pos.y + m_VtxMax.y)
			{
			}

			//上からぶつかった
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				OldPos.y + vtxMax.y <= m_pos.y + m_VtxMin.y)
			{
			}

			//右からぶつかった
			else if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				OldPos.x + vtxMax.x <= m_pos.x + m_VtxMin.x)
			{
			}

			//左からぶつかった
			else if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				OldPos.x + vtxMin.x >= m_pos.x + m_VtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z - vtxMax.z + m_VtxMin.z;
				b = true;
			}
		}
	}

	return b;
}

//========================================================
//当たり判定の処理
//========================================================
bool CWallObj::Collision(CPlayer3D *pPlayer, CItemThrow *pItemThrow)
{
	bool b = false;

	if (pPlayer != NULL)
	{
		pPlayer->Collisionbool(&m_pos, m_VtxMax, m_VtxMin, TYPE_WALL);
	}

	return b;
}

//========================================================
//当たり判定の処理
//========================================================
void CWallObj::ReguVtx()
{
	D3DXVECTOR3 keepMin = m_VtxMin;
	D3DXVECTOR3 keepMax = m_VtxMax;


	m_VtxMin.x = cosf(m_rot.y) * keepMin.x + sinf(m_rot.y) * keepMin.z;
	m_VtxMin.z = cosf(m_rot.y) * keepMin.z + sinf(m_rot.y) * keepMin.x;

	m_VtxMax.x = cosf(m_rot.y) * keepMax.x + sinf(m_rot.y) * keepMax.z;
	m_VtxMax.z = cosf(m_rot.y) * keepMax.z + sinf(m_rot.y) * keepMax.x;

}