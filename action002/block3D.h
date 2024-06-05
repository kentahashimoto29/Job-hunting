//========================================================
//
//ウインドウの生成等 (block3D.h)
//Author 橋本賢太
//
//========================================================
#ifndef _BLOCK3D_H_
#define _BLOCK3D_H_
#include "main.h"
#include "objectX.h"

//===================================
//プレイヤーのクラス
//===================================
class CBlock3D : public CObjectX
{
public:
	CBlock3D(int nPriority = 6);									//コンストラクタ
	CBlock3D(D3DXVECTOR3 pos, int nPriority = 6);					//オーバーライドされたコンストラクタ
	~CBlock3D();									//デストラクタ

	static CBlock3D *Create(D3DXVECTOR3 pos);	//生成処理

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	bool Collisionbool(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pmove, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pmove, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);
	D3DXVECTOR3 GetPos(void);					//位置を返す

private:
	static int m_nIdxTexture;					//テクスチャの番号
	D3DXVECTOR3 m_VtxMax;						//モデルの最大値
	D3DXVECTOR3 m_VtxMin;						//モデルの最小値
};

#endif