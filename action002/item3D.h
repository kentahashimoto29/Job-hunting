//========================================================
//
//ウインドウの生成等 (item3D.h)
//Author 橋本賢太
//
//========================================================
#ifndef _ITEM3D_H_
#define _ITEM3D_H_
#include "main.h"
#include "objectX.h"

//===================================
//プレイヤーのクラス
//===================================
class CItem3D : public CObjectX
{
public:
	CItem3D(int nPriority = 6);									//コンストラクタ
	CItem3D(D3DXVECTOR3 pos, int nPriority = 6);					//オーバーライドされたコンストラクタ
	~CItem3D();									//デストラクタ

	static CItem3D *Create(D3DXVECTOR3 pos);	//生成処理

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	D3DXVECTOR3 GetPos(void);					//位置を返す

private:
	static int m_nIdxTexture;					//テクスチャの番号
};

#endif