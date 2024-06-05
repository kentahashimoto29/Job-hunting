//========================================================
//
//ウインドウの生成等 (Object3D.h)
//Author 橋本賢太
//
//========================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_
#include "main.h"
#include "object.h"

//===================================
//オブジェクト3Dのクラス
//===================================
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 6);					//コンストラクタ
	~CObject3D();					//デストラクタ

	HRESULT Init(void);				//初期化処理
	HRESULT Init(int nWidth);				//初期化処理
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理

	void BindTexture(int nTexture);				//テクスチャの番号を割り当てる
	void SetVtxField(void);						//フィールドの頂点座標を設定
	void SetVtxWall();						//壁の頂点座標を設定

	D3DXVECTOR3 GetPos(void);		//位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;							//オブジェクトの位置
	LPDIRECT3DVERTEXBUFFER9 m_aVerBuff;		//頂点情報へのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			//インデックスバッファのポインタ
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	D3DXVECTOR3 m_rot;			//向き

private:
	int m_nTexture;							//テクスチャの番号

	int m_nWidth;
	int m_nNumVtx;
};
#endif