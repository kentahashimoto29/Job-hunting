//========================================================
//
//ウインドウの生成等 (Object.h)
//Author 橋本賢太
//
//========================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

//===================================
//オブジェクトのクラス
//===================================
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLATER,
		TYPE_PLAYER_3D,
		TYPE_FACE_X,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_EFFECT,
		TYPE_FIELD,
		TYPE_WALL,
		TYPE_BLOCK_3D,
		TYPE_BLOCK_DEATH,
		TYPE_BLOCK_THROUGH,
		TYPE_FADE,
		TYPE_TITLE,
		TYPE_GAME,
		TYPE_RESULT,
		TYPE_TIME,
		TYPE_MAX,
	}TYPE;

	CObject(int nPriority = 6);
	~CObject();					//デストラクタ

	virtual HRESULT Init(void) = 0;				//初期化処理
	virtual void Uninit(void) = 0;				//終了処理
	virtual void Update(void) = 0;				//更新処理
	virtual void Draw(void) = 0;				//描画処理

	static void ReleaseAll(void);				//初期化終了処理
	static void UpdateAll(void);				//オブジェクトの更新処理
	static void DrawAll(void);					//オブジェクトの描画処理

	void Release(void);							//n番目の初期化終了処理

	void Death(void);					//初期化終了処理

	static int GetNumAll(void);					//オブジェクトの総数

	static CObject *GetTop(int nPriority);		// 先頭のオブジェクト取得
	CObject *GetNext(void);						//次のオブジェクトを返す

	void SetType(TYPE type);					//種類を設定
	TYPE GetType(void);							//種類を返す
	CObject *GetObject();						//オブジェクトの

	virtual D3DXVECTOR3 GetPos(void) = 0;		//オブジェクトの位置を返す
	virtual void SetPos(D3DXVECTOR3 pos) = 0;		//オブジェクトの位置を設定
	virtual void SetRot(D3DXVECTOR3 rot) = 0;		//オブジェクトの向きを設定

	D3DXVECTOR3 m_pos;							//オブジェクトの位置
	D3DXVECTOR3 m_rot;							//オブジェクトの位置

protected:

private:
	int m_nPriority;

	static CObject *m_pTop[8];	// 先頭のオブジェクトへのポインタ
	static CObject *m_pCur[8];	// 最後尾のオブジェクトへのポインタ
	CObject *m_pPrev;							//前のオブジェクトへのポインタ
	CObject *m_pNext;							//次のオブジェクトへのポインタ
	bool m_bflag;								//死亡フラグ

	TYPE m_type;								//オブジェクトの種類
};

#endif