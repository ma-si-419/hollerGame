#pragma once
#include "SceneBase.h"
#include <memory>
class Player;
class Camera;
class Enemy;
class SceneGame : public SceneBase
{
private:
	//シェーダに渡すデータ構造体
	struct LightData
	{
		float PLightPos[3];

		float pad1;

		float PLightColor[3];

		float PLightPower;

		float DLightDir[3];

		float pad2;

		float DLightColor[3];

		float pad3;

		float SpLightPos[3];

		float pad4;

		float SpLightColor[3];

		float SpLightPower;

		float SpLightDir[3];

		float SpLightAngle;

		float CameraPos[3];

		float pad5;
	};
public:
	SceneGame(SceneManager& sceneManager);
	~SceneGame();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(MyEngine::Input input);
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 終了処理
	/// </summary>
	void End();
private:
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;
	//シェーダーハンドル
	int m_psHandle;
	int m_vsHandle;

	//Cバッファ
	int m_cBuff;
	//シェーダに送るライトのデータ
	LightData* m_lightData;
};

