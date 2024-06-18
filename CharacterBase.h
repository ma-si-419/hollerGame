#pragma once
#include "MyEngine.h"
class CharacterBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CharacterBase(const TCHAR* model);
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CharacterBase();

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;
protected:
	//表示座標
	MyEngine::Vector3 m_pos;
	//モデルハンドル
	int m_handle;
};

