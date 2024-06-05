//========================================================
//
//ウインドウの生成等 (score.h)
//Author 橋本賢太
//
//========================================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "object2D.h"

//マクロ定義
#define TIME_MAX									(3)		//スコアの桁数

//===================================
//背景のクラス
//===================================
class CTime : public CObject
{
public:
	CTime(int nPriority = 4);								//コンストラクタ
	~CTime();								//デストラクタ

	static CTime *Create();				//敵の生成

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	void SetTime(int nTime);				//設定処理
	int GetTime(void);
	int GetInitTime(void);
	D3DXVECTOR3 GetPos(void);				//位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;						//オブジェクトの位置

private:
	static int m_nIdxTexture;				//テクスチャの番号
	CObject2D *m_apObject2D[TIME_MAX];		//タイムのオブジェクト
	int m_aTexU[TIME_MAX];					//テクスチャのスコア更新用変数
	int m_nTime;							//タイム
	int m_nInitTime;						//タイムの初期値
	int m_nSecondCount;						//
};

#endif