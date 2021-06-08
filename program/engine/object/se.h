#pragma once
#include "object.h"


namespace dxe {

	// SEクラス
	// このクラス単体では生成しません
	// SEManagerを通してください
	// ループ再生の設定
	// ボリュームの設定
	class SE final : public Object {
	public:
		using SharedPtr = std::shared_ptr<SE>;
		using WeakPtr = std::weak_ptr<SE>;
	private:
		// createを呼ぶため
		friend class SEManager;

		//====================================================================================================
		// メンバ変数

		// Audioハンドル
		mylib::Audio::SharedPtr audio_ = nullptr;

		// ボリューム
		float volume_ = 1.0f;

		// 一時停止中か
		bool is_pause_ = false;

		//====================================================================================================
		// static関数

		// リソースファイルからSEの生成
		static SE::SharedPtr create(const std::string& file_path);

		//====================================================================================================
	public:
		SE() {}
		~SE() {}

		//====================================================================================================
		// メンバ変数

		// ループ再生フラグ
		bool is_loop_ = false;

		//====================================================================================================
		// メンバ関数

		// Audioの取得（参照用）
		inline const mylib::Audio::SharedPtr getAudio() const { return audio_; }

		// ボリュームの取得
		inline float getVolume() const { return volume_; }

		// ボリュームの設定
		void setVolume(const float volume);

		//====================================================================================================
	};

}
