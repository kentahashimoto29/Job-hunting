//========================================================
//
//ウインドウの生成等 (goal.h)
//Author 橋本賢太
//
//========================================================
#ifndef _GOAL_H_
#define _GOAL_H_
#include "main.h"
#include "object2D.h"

//===================================
//ゴールのクラス
//===================================
class CGoal : public CObject2D
{
public:
	CGoal();								//コンストラクタ
	~CGoal();								//デストラクタ

	static CGoal *Create();					//敵の生成

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	D3DXVECTOR3 GetPos(void);				//位置を返す

	D3DXVECTOR3 m_pos;						//オブジェクトの位置

private:
	static int m_nIdxTexture;				//テクスチャの番号
};

#endif