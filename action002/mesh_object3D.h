//========================================================
//
//ウインドウの生成等 (Object3D.h)
//Author 橋本賢太
//
//========================================================
#ifndef _MESH_OBJECT3D_H_
#define _MESH_OBJECT3D_H_
#include "main.h"
#include "object3D.h"

//===================================
//メッシュオブジェクト3Dのクラス
//===================================
class CMeshObject3D : public CObject3D
{
public:
	CMeshObject3D(int nPriority = 6);					//コンストラクタ
	~CMeshObject3D();					//デストラクタ

	static CMeshObject3D *Create();
	static CMeshObject3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nHeight, TYPE type, int nPriority = 6);

	HRESULT Init(void);				//初期化処理
	HRESULT Init(TYPE type);
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理

	void BindTexture(int nTexture);				//テクスチャの番号を割り当てる
	void SetVtxField(void);								//背景の頂点座標を設定

	D3DXVECTOR3 GetPos(void);		//位置を返す

	D3DXVECTOR3 m_pos;							//オブジェクトの位置
	LPDIRECT3DVERTEXBUFFER9 m_aVerBuff;		//頂点情報へのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			//インデックスバッファのポインタ
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	D3DXVECTOR3 m_rot;			//向き

private:
	int m_nTexture;							//テクスチャの番号

	D3DXVECTOR3 *m_pVtxPos;	// 頂点座標
	D3DXVECTOR3 *m_pVtxNor;	// 頂点法線
	D3DXCOLOR *m_pVtxCol;	// 頂点カラー
	D3DXVECTOR2 *m_pVtxTex;	// 頂点テクスチャ座標

	int m_nNumIndex;		// インデックス数
	int m_nNumVertex;		// 頂点数
	int m_nWidth;			// 横分割数
	int m_nHeight;			// 縦分割数

	TYPE m_type;						// メッシュのタイプ

};
#endif