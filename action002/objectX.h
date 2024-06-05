//========================================================
//
//ウインドウの生成等 (ObjectX.h)
//Author 橋本賢太
//
//========================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_
#include "main.h"
#include "object.h"

//===================================
//オブジェクトXのクラス
//===================================
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = 6);						//コンストラクタ
	~CObjectX();					//デストラクタ

	HRESULT Init(void);				//初期化処理
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理

	D3DXVECTOR3 GetPos(void);		//位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	LPD3DXMESH m_pMesh;				//メッシュへのポインタ
	LPD3DXBUFFER m_pBuffMat;		//マテリアルへのポインタ
	D3DXMATRIX m_mtxWorld;			//ワールドマトリックス
	DWORD m_dwNumMat;				//マテリアルの数

	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_rot;				//向き

private:
};
#endif