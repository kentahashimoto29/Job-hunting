//========================================================
// 
// ウインドウの生成等 (title.h)
// Author 橋本賢太
// 
//========================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "main.h"
#include "manager.h"
#include "wall_obj_manager.h"
#include "field.h"
#include "wall.h"

class CObject2D;
class CTitle_Obj2D;

//===================================
// タイトルのクラス
//===================================
class CTitle : public CScene
{
public:
	CTitle();								// コンストラクタ
	~CTitle();								// デストラクタ

	HRESULT Init(void);						// 初期化処理
	void Uninit(void);						// 終了処理
	void Update(void);						// 更新処理
	void Draw(void);						// 描画処理

	D3DXVECTOR3 GetPos(void);				// 位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 m_pos;						// オブジェクトの位置

private:
	CObject2D *m_apObject2D[2];				// タイトルのオブジェクト
	static CTitle_Obj2D *m_apTitleObj;
	static CWallObjManager *m_pWallManager;	// 壁3Dのポインタ
	CField *m_pField[256];					// フィールドのポインタ
	CWall *m_pWall[256];					// 壁のポインタ

	static int m_nIdxTexture;				// テクスチャの番号
	static float m_nInitPos;

	bool b;
};

#endif