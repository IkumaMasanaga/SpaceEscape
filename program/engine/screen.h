#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class Camera2D;

	// 設定した幅、高さの範囲内にLayerを描画するクラス
	// 範囲内にLayerの描画
	class Screen final : public t2k::SharedFactory<Screen> {
	public:
		using SharedPtr = std::shared_ptr<Screen>;
		using WeakPtr = std::weak_ptr<Screen>;
	private:
		// renderToTexture, renderを呼ぶため、Screen生成と同時にscene_を設定するため
		friend class Scene;

		//====================================================================================================
		// メンバ変数

		// 自身の登録名
		std::string registered_name_;

		// 自身が所属しているScene
		std::weak_ptr<Scene> scene_;
		
		// Screenを描画しているCamera2DComponent
		std::shared_ptr<Camera2D> camera_ = nullptr;

		// 描画Texture
		// 実際にLayerを描画する場所
		t2k::Texture::SharedPtr texture_ = nullptr;

		// Screenの中心座標
		// ウィンドウの中心が原点
		t2k::Vector3 position_ = t2k::Vector3(0, 0, 0);

		//====================================================================================================
		// メンバ関数

		// 自身が持っている描画TextureにLayerを描画
		void renderToTexture();

		// 自身が持っている描画Textureを描画
		void render() const;

		// 自身が所属しているSceneを取得
		inline std::shared_ptr<Scene> getScene() const { return (scene_.expired()) ? nullptr : scene_.lock(); }

		//====================================================================================================
		// static関数

		// Screenの作成
		static Screen::SharedPtr create(std::shared_ptr<Camera2D> camera, const int width, const int height);

		//====================================================================================================
	public:
		Screen() {}
		~Screen() {}

		//====================================================================================================
		// メンバ変数

		// Screenの描画優先度
		// 小さいほうが先に描画される
		float priority_ = 0.0f;

		//====================================================================================================
		// メンバ関数

		// Camera2Dの切り替え
		inline void changeCamera2D(std::shared_ptr<Camera2D> camera) { camera_ = camera; }

		// Camera2Dの取得
		inline const std::shared_ptr<Camera2D> getCamera2D() const { return camera_; }
		
		// Screenの中心座標の設定
		inline void setPosition(const t2k::Vector3& position) { position_ = position; }

		// Screenの中心座標の取得
		inline t2k::Vector3 getPosition() const { return position_; }

		// Screenの幅を取得
		inline int getWidth() const { return texture_->getWidth(); }
		
		// Screenの高さを取得
		inline int getHeight() const { return texture_->getHeight(); }

		// 自身の登録名の取得
		inline std::string getRegisteredName() const { return registered_name_; }

		//====================================================================================================
	};
	
}
