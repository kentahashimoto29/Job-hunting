//========================================================
//
//ウインドウの生成等 (texture.h)
//Author 橋本賢太
//
//========================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "main.h"

#define TEXTURE_MAX									(1024)	//テクスチャの最大数

//===================================
//テクスチャのクラス
//===================================
class CTexture
{
public:
	CTexture();									//コンストラクタ
	~CTexture();								//デストラクタ

	HRESULT Load(void);							//テクスチャの生成
	void Unload(void);							//テクスチャの破棄

	int Regist(const char *pFilename);			//指定テクスチャの読み込み
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);	//指定のテクスチャを返す
	const char *GetName(int nIdx);				//指定のテクスチャの名前を返す

private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];	//テクスチャのポインタ
	const char *m_aFilename[TEXTURE_MAX];			//テクスチャの名前
	static int m_nNumAll;							//テクスチャの総数
};

#endif