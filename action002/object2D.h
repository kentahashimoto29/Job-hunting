//========================================================
//
//ウインドウの生成等 (Object2D.h)
//Author 橋本賢太
//
//========================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "main.h"
#include "object.h"

//===================================
//オブジェクト2Dのクラス
//===================================
class CObject2D : public CObject
{
public:
	CObject2D(int nPriority = 4);					//コンストラクタ
	CObject2D(D3DXVECTOR3 Pos, int nPriority = 4);		//オーバーライドされたコンストラクタ
	~CObject2D();					//デストラクタ

	HRESULT Init(void);				//初期化処理
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理

	void BindTexture(int nTexture);							//テクスチャの番号を割り当てる
	void SetVtxBG(float aTexV);								//背景の頂点座標を設定
	void SetVtxScore(int aTexU, int nCnt);					//スコアの頂点座標を設定
	void SetVtxBlock(D3DXVECTOR3 pos);						//ブロックの頂点座標を設定
	void SetVtxResult(void);								//リザルトの頂点座標を設定
	void SetVtxTime(int aTexU, int nCnt);					//タイムの頂点座標を設定
	void SetVtxRanking(int aTexU, int nCnt, int nCnt2);		//ランキングの頂点座標を設定
	void SetVtxFade(void);									//リザルトの頂点座標を設定

	void SetColor(D3DXCOLOR col);									//リザルトの頂点座標を設定

	D3DXVECTOR3 GetPos(void);								//位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	LPDIRECT3DVERTEXBUFFER9 m_aVerBuff;			//頂点情報へのポインタ
	D3DXVECTOR3 m_pos;							//オブジェクトの位置

private:
	int m_nTexture;								//テクスチャの番号
};

#endif