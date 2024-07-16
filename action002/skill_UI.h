//========================================================
//
//ウインドウの生成等 (skill_UI.h)
//Author 橋本賢太
//
//========================================================
#ifndef _SKILL_UI_H_
#define _SKILL_UI_H_
#include "main.h"
#include "manager.h"
class CObject2D;

//===================================
// スキルUIのクラス
//===================================
class CSkill_UI : public CObject
{
public:
	CSkill_UI();							//コンストラクタ
	~CSkill_UI();							//デストラクタ

	static CSkill_UI *Create();				//敵の生成

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	D3DXVECTOR3 GetPos(void);				//位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	CObject2D *GetObjectGauge2D() { return m_apObjectGauge2D; }

	D3DXVECTOR3 m_pos;						//オブジェクトの位置

private:
	D3DXCOLOR m_col;
	CObject2D *m_apObject2D;				//タイトルのオブジェクト
	CObject2D *m_apObjectGauge2D;			//タイトルのオブジェクト
	static int m_nIdxTexture;				//テクスチャの番号

	bool b;
};

#endif