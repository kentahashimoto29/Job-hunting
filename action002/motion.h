//========================================================
// 
// ウインドウの生成等 (motion.h)
// Author 橋本賢太
// 
//========================================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"
#include "model.h"
#include <stdio.h>
#include <string.h>

//===================================
// モデルのクラス
//===================================
class CMotion
{
public:
	// モーションの種類
	typedef enum
	{
		TYPE_STAND = 0,
		TYPE_MOVE,
		TYPE_JUMP,
		TYPE_LAND,
		TYPE_RUBBING,
		TYPE_DASH,
		TYPE_END
	}TYPE;

	// キーの構造体
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

	// キー情報の構造体
	typedef struct
	{
		float nFrame;				// 再生フレーム
		KEY aKey[15];				// 各モデルのキー要素
	}KEY_INFO;

	// モーション情報の構造体
	typedef struct
	{
		bool bLoop;					// ループするかどうか
		int nNumKey;				// キーの総数
		KEY_INFO aKeyInfo[16];		// キー情報
		TYPE nType;					// モーションの種類
		int m_nType;
	}INFO;

	CMotion();						// コンストラクタ
	~CMotion();						// デストラクタ

	void Init(int nType);
	void Set(int nType);
	void Load(void);
	void Updata(void);
	int GetType(void);
	bool IsFinish(void);

	void SetInfo(INFO info);
	void SetType(TYPE nType);
	void SetModel(CModel **ppModel, int nNumModel);

private:
	INFO m_aInfo[6];
	int m_nNumAll;
	int m_nType;
	int m_nTypeOld;
	int m_bLoop[6];
	int m_nNumKey;
	int m_nKey[16];
	float m_nCounter;
	bool m_bFinish;			// 終了したかどうか

	CModel **m_ppModel;		// モデルへのポインタ
	int m_nNumModel;		// モデルの総数

	int m_nKeyCurrent;
	int m_nKeyTarget;
};
#endif