//========================================================
//
//ウインドウの生成等 (goal.h)
//Author 橋本賢太
//
//========================================================
#ifndef _GOAL_H_
#define _GOAL_H_
#include "main.h"
#include "manager.h"
class CObject2D;

//===================================
//タイトルのクラス
//===================================
class CTitle : public CScene
{
public:
	CTitle();								//コンストラクタ
	~CTitle();								//デストラクタ

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	D3DXVECTOR3 GetPos(void);				//位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;						//オブジェクトの位置

private:
	CObject2D *m_apObject2D[1];				//タイトルのオブジェクト
	static int m_nIdxTexture;				//テクスチャの番号

	bool b;
};

#endif