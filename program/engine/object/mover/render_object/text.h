#pragma once
#include "render_object.h"


namespace dxe {

	// x軸方向揃え列挙定数
	enum class AlignModeX {
		LEFT,	// 左揃え
		CENTER,	// 中央揃え
		RIGHT	// 右揃え
	};

	// y軸方向揃え列挙定数
	enum class AlignModeY {
		TOP,	// 上揃え
		MIDDLE,	// 中央揃え
		BOTTOM	// 下揃え
	};

	class Text final : public RenderObject {
	public:
		using SharedPtr = std::shared_ptr<Text>;
		using WeakPtr = std::weak_ptr<Text>;
	private:
		//====================================================================================================
		// メンバ変数

		// 文字列
		std::vector<std::string> text_;

		//====================================================================================================
		// メンバ関数

		// 描画
		void render(std::shared_ptr<Screen> screen) final override;

		//====================================================================================================
	public:
		Text() {}
		~Text() {}

		//====================================================================================================
		// メンバ変数

		// x軸方向揃え
		AlignModeX align_mode_x_ = AlignModeX::LEFT;

		// y軸方向揃え
		AlignModeY align_mode_y_ = AlignModeY::TOP;

		// フォントサイズ
		int font_size_ = 20;

		// 行間
		int interval_ = 0;

		// 文字列の色
		t2k::Color color_;

		//====================================================================================================
		// メンバ関数

		// 文字列の変更
		void changeText(const std::string& text);

		// リソースファイル（テキストファイル）から文字列の変更
		void changeTextFromFile(const std::string& file_path);

		//====================================================================================================
		// static関数

		// 生成
		static Text::SharedPtr create(const std::string& text);

		// リソースファイル（テキストファイル）から生成
		static Text::SharedPtr createFromFile(const std::string& file_path);

		//====================================================================================================
	};

}
