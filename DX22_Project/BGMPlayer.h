#pragma once

// インクルード部
#include "GameObject.h"

// 前方宣言
class CAudio;

/// <summary>
/// BGMを再生するスピーカー用クラス
/// </summary>
class CBGMPlayer : public CGameObject
{
public:
    CBGMPlayer();
    ~CBGMPlayer();
    int Inspecter(bool isEnd = true) override;

    /// <summary>
    /// サウンドデータを読み込む
    /// </summary>
    /// <param name="inPath">
    /// 読み込むサウンドのパス
    /// </param>
    void Load(const char* inPath);

    /// <summary>
    /// 再生処理
    /// </summary>
    void Play();

    /// <summary>
    /// サウンドの停止
    /// </summary>
    void Stop();

    /// <summary>
    /// ボリュームの設定
    /// </summary>
    /// <param name="inVolume">
    /// ボリュームの値(0.0f~1.0f)
    /// </param>
    void SetVolume(float inVolume);

private:
    CAudio* m_pAudio;   // オーディオコンポーネント

    // オーディオのデータ
    struct AudioState
    {
        std::string m_sBGMName; // BGMの名前
        float m_fVolume;        // ボリューム
    }m_tState;
    
};
