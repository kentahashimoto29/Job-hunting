//========================================================
//
//ウインドウの生成等 (light.h)
//Author 橋本賢太
//
//========================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "main.h"

//===================================
//ライトのクラス
//===================================
class CLight
{
public:
	CLight();					//コンストラクタ
	~CLight();					//デストラクタ

	HRESULT Init(void);			//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理

private:
	D3DLIGHT9 m_Light[4];			//ライトの情報
};

#endif