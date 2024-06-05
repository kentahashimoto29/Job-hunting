//========================================================
//
//ウインドウの生成等 (model.h)
//Author 橋本賢太
//
//========================================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"

//===================================
//モデルのクラス
//===================================
class CModel
{
public:
	CModel();						//コンストラクタ
	CModel(D3DXVECTOR3 pos);		//オーバーライドされたコンストラクタ
	~CModel();						//デストラクタ

	static CModel *Create(const char *pFilename, D3DXVECTOR3 pos);		//生成処理
	void SetParent(CModel *pModel);										//親モデルの設定
	D3DXVECTOR3 GetPos(void);											//位置を返す
	D3DXVECTOR3 GetRot(void);											//向きを返す
	D3DXMATRIX GetMtxWorld(void);										//マトリックスを返す

	void SetPos(D3DXVECTOR3 pos);										//位置を設定
	void SetRot(D3DXVECTOR3 rot);										//向きを設定

	HRESULT Init(const char *pFilename);								//初期化処理
	void Uninit(void);													//終了処理
	void Update(void);													//更新処理
	void Draw(void);													//描画処理

private:
	LPD3DXMESH m_pMesh;				//メッシュへのポインタ
	LPD3DXBUFFER m_pBuffMat;		//マテリアルへのポインタ
	DWORD m_dwNumMat;				//マテリアルの数

	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_rot;				//向き
	D3DXMATRIX m_mtxWorld;			//ワールドマトリックス
	CModel *m_pModel;				//親モデルへのポインタ
};
#endif