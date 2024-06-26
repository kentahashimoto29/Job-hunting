//========================================================
//
//ウインドウの生成等 (enemy3D.h)
//Author 橋本賢太
//
//========================================================
#ifndef _WALLOBJ_H_
#define _WALLOBJ_H_
#include "main.h"
#include "objectX.h"

class CPlayer3D;
class CItemThrow;

//===================================
//敵のクラス
//===================================
class CWallObj : public CObjectX
{
public:
	CWallObj(int nPriority = 6);									//コンストラクタ
	CWallObj(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority = 6);					//オーバーライドされたコンストラクタ
	~CWallObj();								//デストラクタ

	static CWallObj *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx);	//敵の生成

	HRESULT Init(int nIdx);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	D3DXVECTOR3 GetPos(void);					//位置を返す

	void HitEnemy(void);						//敵のダメージ処理
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);
	bool Collision(CPlayer3D *pPlayer, CItemThrow *pItemThrow);

private:

	D3DXVECTOR3 m_VtxMax;						//モデルの最大値
	D3DXVECTOR3 m_VtxMin;						//モデルの最小値

	D3DXVECTOR3 m_Oldpos;						//

	int m_nLife;								//体力
	int m_nIdx;

	bool bCollision;
};

#endif