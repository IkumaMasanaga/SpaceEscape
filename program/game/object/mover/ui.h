#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class UI final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<UI>;
		using WeakPtr = std::weak_ptr<UI>;
	private:
		//====================================================================================================
		// メンバ変数

		// エネルギーバーの開始X座標
		float energy_start_x_ = 0.0f;

		// 惑星数
		// GOODエンドでクリアしている場合に変化する
		int planet_num_ = 0;

		// 経過時間
		dxe::Text::SharedPtr time_ = nullptr;

		// HP（あり）のテクスチャ
		t2k::Texture::SharedPtr hp_;

		// HP（なし）のテクスチャ
		t2k::Texture::SharedPtr hp_none_;

		// HP
		std::vector<dxe::Sprite::SharedPtr> hp_sprites_;

		// エネルギーバー
		dxe::RectRenderer::SharedPtr energy_bar_ = nullptr;

		// 仮消費エネルギーバー
		dxe::RectRenderer::SharedPtr temp_energy_bar_ = nullptr;

		// アイテム
		std::vector<dxe::Sprite::SharedPtr> item_sprites_;

		//====================================================================================================
		// メンバ関数

		// 更新
		void update() final override;

		//====================================================================================================
	public:
		UI() {}
		~UI() {}

		//====================================================================================================
		// static関数

		// 生成
		static UI::SharedPtr create(const std::string& csv_folder);

		//====================================================================================================
	};

}
