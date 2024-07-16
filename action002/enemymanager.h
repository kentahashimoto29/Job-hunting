//========================================================
//
//ウインドウの生成等 (enemymanager.h)
//Author 橋本賢太
//
//========================================================
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_
#include "main.h"
#include "enemy3D.h"

//===================================
//敵マネージャーのクラス
//===================================
class CEnemyManager
{
public:
	CEnemyManager();									//コンストラクタ
	~CEnemyManager();								//デストラクタ

	static CEnemyManager *Create();				//敵の生成

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理

	void Release(int nIdx);
	void Kill(void);
	CEnemy3D **SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void SectionSpawn();

	static int GetNum(void);					//総数を返す
	CEnemy3D **GetEnemy(void);	// 敵取得

private:

	CEnemy3D *m_pEnemy3D[512];					//エネミー3Dのポインタ
	static int m_nNum;							//総数

	int m_nCreCnt;
};

#endif