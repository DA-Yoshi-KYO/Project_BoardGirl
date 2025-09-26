#pragma once

// インクルード部
#include "GameObject.h"
#include "Job.h"
#include "BillboardRenderer.h"

/// <summary>
/// ジョブ選択画面のジョブを描画するクラス
/// </summary>
class CSelectJobs : public CGameObject
{
public:
    CSelectJobs();
    void Init() override;
    void Update() override;
    void Draw() override;
    virtual int Inspecter(bool isEnd = true);

    /// <summary>
    /// 選択したジョブの取得
    /// </summary>
    /// <returns>
    /// (JobKind)ジョブの種類の列挙子
    /// </returns>
    static JobKind GetSelectedJob() { return m_eSelectedJob; }

private:
    CBillboardRenderer* m_pRenderer[(int)JobKind::Max]; // 描画用コンポーネント
    RendererParam m_tJobsParam[(int)JobKind::Max];      // 描画用パラメータ
    RendererParam m_tTempParam[(int)JobKind::Max];      // 移動前の描画用パラメータ
    bool m_bMove;   // 選択を動かしているか
    bool m_bNext;   // 選択が次か前か
    bool m_bEnd;    // 選択が完了したか
    bool m_bTransition; // トランジション中か

    static JobKind m_eSelectedJob;  // 選択したジョブ

};
