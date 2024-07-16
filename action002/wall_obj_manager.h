//========================================================
// 
// ウインドウの生成等 (wall_obj_manager.h)
// Author 橋本賢太
// 
//========================================================
#ifndef _WALL_OBJ_MANAGER_H_
#define _WALL_OBJ_MANAGER_H_
#include "main.h"
class CWallObj;

//===================================
// 敵マネージャーのクラス
//===================================
class CWallObjManager
{
public:
	CWallObjManager();							// コンストラクタ
	~CWallObjManager();							// デストラクタ

	static CWallObjManager *Create();			// 敵の生成

	HRESULT Init(void);							// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理

	void Release(int nIdx);
	void Kill(void);
	CWallObj **SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static int GetNum(void);					// 総数を返す
	CWallObj **GetWall(void);					// 敵取得

	void ReadWall();

private:

	CWallObj *m_pWall[32];					// 壁のポインタ
	static int m_nNum;						// 総数

	int m_nCreateNum;						// 総数
	D3DXVECTOR3 m_nReadPos[256];
	D3DXVECTOR3 m_nReadRot[256];
};

#endif