//========================================================
//
//ウインドウの生成等 (goal.h)
//Author 橋本賢太
//
//========================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"
#include "object2D.h"

//===================================
//フェードのクラス
//===================================
class CFade
{
public:

	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;


	CFade();								//コンストラクタ
	~CFade();								//デストラクタ

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	void SetFade(CScene::MODE mode);
	void SetFadeFirst(CScene::MODE mode);

	FADE GetState(void);	// 状態取得

private:

	static int m_nIdxTexture;

	CObject2D *m_pObject2D;				//フェードのポリゴン

	CScene::MODE m_modenext;				//次の画面
	D3DXCOLOR m_color;						//ポリゴンの色
	FADE m_fade;
};

#endif