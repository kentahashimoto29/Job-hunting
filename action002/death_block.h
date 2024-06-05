//========================================================
//
//ウインドウの生成等 (block3D.h)
//Author 橋本賢太
//
//========================================================
#ifndef _DEATHBLOCK_H_
#define _DEATHBLOCK_H_
#include "main.h"
#include "objectX.h"

//===================================
//デスブロックのクラス
//===================================
class CDeathBlock : public CObjectX
{
public:
	CDeathBlock(int nPriority = 6);									//コンストラクタ
	CDeathBlock(D3DXVECTOR3 pos, int nPriority = 6);					//オーバーライドされたコンストラクタ
	~CDeathBlock();									//デストラクタ

	static CDeathBlock *Create(D3DXVECTOR3 pos);	//生成処理

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	D3DXVECTOR3 GetPos(void);					//位置を返す
private:
	static int m_nIdxTexture;					//テクスチャの番号
	D3DXVECTOR3 m_VtxMax;						//モデルの最大値
	D3DXVECTOR3 m_VtxMin;						//モデルの最小値
};

#endif