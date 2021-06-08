#pragma once
#include "object.h"


namespace dxe {

	// BGMクラス
	// このクラス単体では生成しません
	// BGMManagerを通してください
	// ループ再生の設定
	// ボリュームの設定
	class BGM final : public Object {
	public:
		using SharedPtr = std::shared_ptr<BGM>;
		using WeakPtr = std::weak_ptr<BGM>;
	private:
		// createを呼ぶため
		friend class BGMManager;

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

		// リソースファイルからBGMの生成
		static BGM::SharedPtr create(const std::string& file_path);

		//====================================================================================================
	public:
		BGM() {}
		~BGM() {}

		//====================================================================================================
		// メンバ変数

		// ループ再生フラグ
		bool is_loop_ = true;

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
