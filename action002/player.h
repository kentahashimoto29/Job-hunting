//========================================================
//
//ウインドウの生成等 (player.h)
//Author 橋本賢太
//
//========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "object2D.h"

//===================================
//プレイヤーのクラス
//===================================
class CPlayer : public CObject2D
{
public:
	CPlayer();									//コンストラクタ
	CPlayer(D3DXVECTOR3 pos);					//オーバーライドされたコンストラクタ
	~CPlayer();									//デストラクタ

	static CPlayer *Create(D3DXVECTOR3 pos);	//生成処理

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	bool CollisionBlock(void);					//ブロックとの当たり判定

	D3DXVECTOR3 GetPos(void);					//位置を返す

private:
	static int m_nIdxTexture;					//テクスチャの番号
	D3DXVECTOR3 m_move;							//移動量
	int GravityCnt;								//重力調整のカウント

	int m_nCntAnim;								//アニメーションのカウント
	int m_nPtnAnim;								//アニメーションのパターン（X軸）
	int m_nPtnAnim2;							//アニメーションのパターン２（Y軸）
};

#endif