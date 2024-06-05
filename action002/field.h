//========================================================
//
//ウインドウの生成等 (Field.h)
//Author 橋本賢太
//
//========================================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "main.h"
#include "object3D.h"

#define FIElD_MAX							(4)		//地面の最大数

//===================================
//フィールドのクラス
//===================================
class CField : public CObject3D
{
public:
	CField();									//コンストラクタ
	CField(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//オーバーライドされたコンストラクタ
	~CField();									//デストラクタ

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	static CField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				//生成処理
	D3DXVECTOR3 GetPos(void);												//位置を返す
	LPDIRECT3DINDEXBUFFER9 GetIdxBuff(void);								//

private:
	static int m_nIdxTexture;					//テクスチャの番号
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			//インデックスバッファのポインタ
};

#endif