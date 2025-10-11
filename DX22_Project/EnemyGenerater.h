#pragma once

// 敵のID
enum class EnemyID
{
    Slime,
    Ghost,
    Dragon
};

/// <summary>
/// Enemyの生成を行うシングルトンクラス
/// </summary>
class CEnemyGenerater
{
private:
    // デフォルトのコンストラクタを無効
    CEnemyGenerater();

public:
    // コピーを禁止
    CEnemyGenerater(const CEnemyGenerater&) = delete;
    CEnemyGenerater& operator=(const CEnemyGenerater&) = delete;

    /// <summary>
    /// CEnemyGeneraterクラスのシングルトンインスタンスを取得
    /// </summary>
    /// <returns>
    /// CEnemyGeneraterクラスのポインタ
    /// </returns>
    static CEnemyGenerater* GetInstance();

    /// <summary>
    /// インスタンスを解放
    /// </summary>
    void ReleaseInstance();

    /// <summary>
    /// 敵の生成を行う
    /// </summary>
    /// <param name="enemyID">
    /// 敵のID
    /// </param>
    /// <param name="position">
    /// 生成位置
    /// </param>
    void GenerateEnemy(EnemyID enemyID, const DirectX::XMFLOAT3& position);

private:
    static CEnemyGenerater* m_pInstance;    // インスタンス

};
