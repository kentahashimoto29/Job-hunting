//========================================================
//
//ウインドウの生成等 (Player.h)
//Author 橋本賢太
//
//========================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "object2D.h"

//===================================
//爆発のクラス
//===================================
class CExplosion : public CObject2D
{
public:
	CExplosion();									//コンストラクタ
	CExplosion(D3DXVECTOR3 pos);					//オーバーライドされたコンストラクタ
	~CExplosion();									//デストラクタ

	static CExplosion *Create(D3DXVECTOR3 pos);		//爆発の生成

	HRESULT Init(void);								//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理

private:
	static int m_nIdxTexture;		//テクスチャの番号				
	int m_nCntrAnim;				//アニメーションのカウント
	int m_nPtnAnim;					//アニメーションのパターン
};

#endif