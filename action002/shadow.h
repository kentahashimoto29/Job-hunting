//========================================================
// 
// 影の処理 (shadow.h)
// Author 橋本賢太
// 
//========================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"
#include "object3D.h"

//===================================
// フィールドのクラス
//===================================
class CShadow : public CObject3D
{
public:
	CShadow(int nPriority = 8);										// コンストラクタ
	CShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority = 8);	// オーバーライドされたコンストラクタ
	~CShadow();									// デストラクタ

	HRESULT Init(void);							// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

	static CShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// 生成処理
	D3DXVECTOR3 GetPos() { return m_pos; }							// 位置を返す
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }					// 位置を設定
	D3DXVECTOR3 GetRot() { return m_rot; }							// 位置を返す
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }					// 位置を設定
	LPDIRECT3DINDEXBUFFER9 GetIdxBuff() { return m_pIdxBuff; }		// インデックスバッファのポインタを返す

private:
	static int m_nIdxTexture;					// テクスチャの番号
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			// インデックスバッファのポインタ
};

#endif