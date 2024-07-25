//========================================================
// 
// ウインドウの生成等 (object2D.h)
// Author 橋本賢太
// 
//========================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "main.h"
#include "object.h"

//===================================
// オブジェクト2Dのクラス
//===================================
class CObject2D : public CObject
{
public:
	CObject2D(int nPriority = 4);					// コンストラクタ
	CObject2D(D3DXVECTOR3 Pos, int nPriority = 4);		// オーバーライドされたコンストラクタ
	~CObject2D();					// デストラクタ

	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理

	void BindTexture(int nTexture);							// テクスチャの番号を割り当てる
	void SetVtx(D3DXVECTOR3 pos, float sizeX, float sizeY);	// 頂点座標を設定
	void SetVtxBG(float aTexV);								// 背景の頂点座標を設定
	void SetVtxScore(int aTexU, int nCnt);					// スコアの頂点座標を設定
	void SetVtxBlock(D3DXVECTOR3 pos);						// ブロックの頂点座標を設定
	void SetVtxResult(void);								// リザルトの頂点座標を設定
	void SetVtxTitleStart(void);							// タイトルENTERの頂点座標を設定
	void SetVtxTitle(void);									// タイトルの頂点座標を設定
	void SetVtxTime(int aTexU, int nCnt);					// タイムの頂点座標を設定
	void SetVtxRankingScore(int aTexU, int nCnt, int nCnt2);// ランキングスコアの頂点座標を設定
	void SetVtxRanking(int aTexU, int nCnt);				// 順位の頂点座標を設定
	void SetVtxSkillUI(void);								// スキルUIの頂点座標を設定
	void SetVtxGaugeUI(void);								// ゲージUIの頂点座標を設定
	void SetVtxFade(void);									// リザルトの頂点座標を設定

	D3DXVECTOR3 GetPos(void);								// 位置を返す
	void SetPos(D3DXVECTOR3 pos);							// 位置を設定
	void SetRot(D3DXVECTOR3 rot);							// 向きを設定
	float GetSizeX() { return m_sizeX; }					// X方向の大きさを返す
	float GetSizeY() { return m_sizeY; }					// Y方向の大きさを返す
	void SetSizeX(float sizeX) { m_sizeX = sizeX; }			// X方向の大きさを設定
	void SetSizeY(float sizeY) { m_sizeY = sizeY; }			// Y方向の大きさを設定
	void SetColor(D3DXCOLOR col);							// 色を設定
	int SetTex(const char TexName[64]);						// テクスチャを設定

	void AlphaTestValid();
	void AlphaTestInvalid();

	void AlphaBlendValid();
	void AlphaBlendInvalid();

	void SetGauge(float nGauge) { m_nGauge = nGauge; }
	void SetGaugeMax(float nGaugeMax) { m_nGaugeMax = nGaugeMax;}
	float GetGauge() { return m_nGauge; }
	float GetGaugeMax() { return m_nGaugeMax; }

	LPDIRECT3DVERTEXBUFFER9 m_aVerBuff;			// 頂点情報へのポインタ
	D3DXVECTOR3 m_pos;							// オブジェクトの位置
	float m_sizeX;								// オブジェクトの大きさ
	float m_sizeY;								// オブジェクトの大きさ

private:
	int m_nTexture;								// テクスチャの番号

	float m_nGauge;
	float m_nGaugeMax;
};

#endif