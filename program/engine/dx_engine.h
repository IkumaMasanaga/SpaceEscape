#pragma once
#include "../library/t2klib.h"
#include "../system/dx_main.h"


namespace dxe {

	class Scene;

	class DxEngine final : public t2k::Singleton<DxEngine> {
	private:
		// 基底クラスで生成するため
		friend class t2k::Singleton<DxEngine>;
		// initialize, update, finalizeを呼ぶため
		friend class sys::DxMain;

		DxEngine() {}

		//====================================================================================================
		// メンバ変数

		// ゲームループフラグ
		bool is_playing_game_ = true;

		// ウィンドウの幅
		int window_width_ = 0;

		// ウィンドウの高さ
		int window_height_ = 0;

		// 現在のシーン
		std::shared_ptr<Scene> now_scene_ = nullptr;

		// 次のシーン
		std::shared_ptr<Scene> next_scene_ = nullptr;

		// Screen遷移前後のフェード用Sequence
		t2k::Sequence<DxEngine*> transition_sequence_ = t2k::Sequence<DxEngine*>(this, &DxEngine::seqFadeIn);

		// Screen遷移のアルファ値用
		t2k::TimerFluct<float> transition_controller_;

		// Screen遷移のアルファ値
		float transition_alpha_ = 1.0f;

		// Screen遷移の完了時間
		float transition_complete_time_ = 0.3f;

		// Screen遷移の色
		t2k::Color transition_color_ = t2k::Color(0);

		//====================================================================================================
		// メンバ関数

		// 初期化
		void initialize(const int window_width, const int window_hieght, std::shared_ptr<Scene> first);
		
		// 更新
		void update();
		
		// 終了処理
		void finalize();

		// Scene遷移後のフェードインSequence
		bool seqFadeIn();

		// Scene実行中Sequence
		bool seqIdle();

		// Scene遷移前のフェードアウトSequence
		bool seqFadeOut();

	public:
		~DxEngine() {}

		//====================================================================================================
		// メンバ関数

		// ウィンドウの幅の取得
		inline int getWindowWidth() const { return window_width_; }

		// ウィンドウの高さの取得
		inline int getWindowHeight() const { return window_height_; }

		// 現在のシーンの取得
		inline std::shared_ptr<Scene> getNowScene() const { return now_scene_; }

		// Scene遷移の完了時間を設定
		inline void setTransitionCompleteTime(const float complete_time) { transition_complete_time_ = complete_time; }

		// Scene遷移の色を設定
		inline void setTransitionColor(const t2k::Color color) { transition_color_ = color; }

		// Scene遷移中か
		inline bool isInTransition() const { return 0.0f < transition_alpha_; }

		// Scene実行中の経過時間を取得
		// この関数で取得できる時間はScene遷移完了後からの時間です
		// Scene遷移中は0.0fが戻り値となります
		inline float getElapsedTimeForScene() const { return isInTransition() ? 0.0f : transition_sequence_.getProgressTime(); }

		// Scene切り替え
		// 実際に切り替わるのはトランジション終了後
		inline void changeScene(std::shared_ptr<Scene> next, const float complete_time = 0.3f) {
			next_scene_ = next;
			setTransitionCompleteTime(complete_time);
			transition_sequence_.change(&DxEngine::seqFadeOut);
		}

		// Scene終了
		// 実際に終了するのはトランジション終了後
		inline void exitGame(const float complete_time = 0.3f) {
			setTransitionCompleteTime(complete_time);
			transition_sequence_.change(&DxEngine::seqFadeOut);
		}
	};

}
