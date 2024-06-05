//========================================================
//
//ウインドウの生成等 (block.h)
//Author 橋本賢太
//
//========================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "main.h"
#include "object2D.h"

//マクロ定義
#define BLOCK_MAX									(32)		//ブロックの最大数
#define BLOCK_WIDTH									(80.0f)		//ブロックの幅
#define BLOCK_HEIGHT								(80.0f)		//ぶの高さ


//===================================
//背景のクラス
//===================================
class CBlock : public CObject2D
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_MAX,
	}TYPE;

	CBlock();										//コンストラクタ
	CBlock(D3DXVECTOR3 pos);						//オーバーライドされたコンストラクタ
	~CBlock();										//デストラクタ

	static CBlock *Create(D3DXVECTOR3 pos);			//生成処理

	HRESULT Init(void);								//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理

private:
	static int m_nIdxTexture;
};

#endif