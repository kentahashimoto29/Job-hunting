//========================================================
// 
// ウインドウの生成等 (item3D.h)
// Author 橋本賢太
// 
//========================================================
#ifndef _ITEMTHROW_H_
#define _ITEMTHROW_H_
#include "main.h"
#include "objectX.h"

//===================================
// プレイヤーのクラス
//===================================
class CItemThrow : public CObjectX
{
public:
	CItemThrow(int nPriority = 6);									// コンストラクタ
	CItemThrow(D3DXVECTOR3 pos, int nPriority = 6);					// オーバーライドされたコンストラクタ
	~CItemThrow();									// デストラクタ

	static CItemThrow *Create(D3DXVECTOR3 pos, int nIdx);	// 生成処理

	HRESULT Init(int nIdx);							// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

	D3DXVECTOR3 GetPos(void);					// 位置を返す

	bool CollisionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);

private:
	static int m_nIdxTexture;					// テクスチャの番号
	bool bUse;

	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_VtxMax;						// モデルの最大値
	D3DXVECTOR3 m_VtxMin;						// モデルの最小値

	int m_nIdx;
};

#endif