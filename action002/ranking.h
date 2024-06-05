//========================================================
//
//ウインドウの生成等 (score.h)
//Author 橋本賢太
//
//========================================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "main.h"
#include "object2D.h"

//マクロ定義
#define SCORE_NUM									(3)		//スコアの桁数
#define RANKING_MAX									(5)		//スコアの桁数
#define NUMBER_MAX									(15)		//スコアの桁数


//===================================
//ランキングのクラス
//===================================
class CRanking : public CObject
{
public:
	CRanking();								//コンストラクタ
	~CRanking();								//デストラクタ

	static CRanking *Create();				//敵の生成

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	void SetScore(int nScore, int nCntR);	//設定処理
	D3DXVECTOR3 GetPos(void);				//位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;						//オブジェクトの位置

private:
	static int m_nIdxTexture;				//テクスチャの番号
	CObject2D *m_apObject2D[NUMBER_MAX];		//スコアのオブジェクト
	int m_aTexU[SCORE_NUM];					//テクスチャのスコア更新用変数
	int m_nRankingScore[RANKING_MAX];		//スコア

	bool b;
};

#endif