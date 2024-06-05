//========================================================
//
//ウインドウの生成等 (billboard.h)
//Author 橋本賢太
//
//========================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"
#include "object.h"

//===================================
//ビルボードのクラス
//===================================
class CBillboard : public CObject
{
public:
	CBillboard(int nPriority = 4);					//コンストラクタ
	~CBillboard();					//デストラクタ

	HRESULT Init(void);				//初期化処理
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理

	static CBillboard *Create(void);		//生成処理
	D3DXVECTOR3 GetPos(void);				//位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_aVerBuff;		//頂点情報へのポインタ
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	D3DXVECTOR3 m_pos;						//位置
};

#endif