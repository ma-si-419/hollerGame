#pragma once
#include "MyEngine.h"
class CharacterBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CharacterBase(const TCHAR* model, const TCHAR* graph);
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

	/// <summary>
	/// ミニマップに表示する画像ハンドルを返す
	/// </summary>
	/// <returns>画像ハンドル</returns>
	int GetGraphHandle() { return m_graphHandle; }
protected:
	//表示座標
	MyEngine::Vector3 m_pos;
	//モデルハンドル
	int m_modelHandle;
	//ミニマップに表示する画像ハンドル
	int m_graphHandle;
};

