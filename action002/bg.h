//========================================================
//
//ウインドウの生成等 (bg.h)
//Author 橋本賢太
//
//========================================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object2D.h"

//===================================
//背景のクラス
//===================================
class CBG : public CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BG000,
		TYPE_BG001,
		TYPE_BG002,
		TYPE_MAX,
	}TYPE;

	CBG();						//コンストラクタ
	~CBG();						//デストラクタ

	static CBG *Create();		//敵の生成

	HRESULT Init(void);			//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void Draw(void);			//描画処理

	D3DXVECTOR3 GetPos(void);	//位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;			//オブジェクトの位置

private:
	static int m_nIdxTexture[3];	//テクスチャの番号
	CObject2D *m_apObject2D[3];		//背景のオブジェクト
	float m_aTexV[3];				//テクスチャのスクロール用
	TYPE m_type[3];					//テクスチャの種類
};

#endif