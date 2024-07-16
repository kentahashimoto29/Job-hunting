//========================================================
//
//ウインドウの生成等 (title_obj2D.h)
//Author 橋本賢太
//
//========================================================
#ifndef _TITLE_OBJ_H_
#define _TITLE_OBJ_H_
#include "main.h"
#include "manager.h"
class CObject2D;

//===================================
//タイトルロゴのクラス
//===================================
class CTitle_Obj2D : public CObject
{
public:
	CTitle_Obj2D();							//コンストラクタ
	~CTitle_Obj2D();						//デストラクタ

	static CTitle_Obj2D *Create();				//敵の生成

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	D3DXVECTOR3 GetPos(void);				//位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	void BlinkingCol();
	void EnterBlinkingCol();
	static int GetBlinkingCnt() { return BlinkingCnt; }

	D3DXVECTOR3 m_pos;						//オブジェクトの位置

private:
	float m_Alpha;
	static int BlinkingCnt;

	D3DXCOLOR m_col;
	CObject2D *m_apObject2D[3];				//タイトルのオブジェクト
	static int m_nIdxTexture;				//テクスチャの番号

	bool b;
};

#endif