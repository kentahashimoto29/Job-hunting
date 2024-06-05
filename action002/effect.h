//========================================================
//
//ウインドウの生成等 (effect.h)
//Author 橋本賢太
//
//========================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include "object2D.h"

//===================================
//エフェクトのクラス
//===================================
class CEffect : public CObject2D
{
public:
	CEffect();									//コンストラクタ
	CEffect(D3DXVECTOR3 pos);					//オーバーライドされたコンストラクタ
	~CEffect();									//デストラクタ

	static CEffect *Create(D3DXVECTOR3 pos);	//爆発の生成

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

private:
	static int m_nIdxTexture;			//テクスチャの番号
	float AlphaData;					//α値
};

#endif