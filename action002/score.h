//========================================================
//
//ウインドウの生成等 (score.h)
//Author 橋本賢太
//
//========================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "object2D.h"

//マクロ定義
#define SCORE_MAX									(8)		//スコアの桁数

//===================================
//背景のクラス
//===================================
class CScore : public CObject
{
public:
	CScore();								//コンストラクタ
	~CScore();								//デストラクタ

	static CScore *Create();				//敵の生成

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	void SetScore(int nScore);				//設定処理
	void AddScore(int nValae);				//スコアの加算
	D3DXVECTOR3 GetPos(void);				//位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;						//オブジェクトの位置

private:
	static int m_nIdxTexture;				//テクスチャの番号
	CObject2D *m_apObject2D[SCORE_MAX];		//スコアのオブジェクト
	int m_aTexU[SCORE_MAX];					//テクスチャのスコア更新用変数
	int m_nScore;							//スコア
};

#endif