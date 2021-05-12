#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class Layer;
	class Camera2D;

	// Scene抽象クラス
	// ゲーム中のSceneはこのクラスを継承して作成します
	// Screenの作成、登録
	// Layerの作成、登録
	// 作成したLayerにGameObjectの登録
	class Scene : public t2k::SharedFactory<Scene> {
	public:
		using SharedPtr = std::shared_ptr<Scene>;
		using WeakPtr = std::weak_ptr<Scene>;
	private:
		// initialize, update, renderを呼ぶため
		friend class DxEngine;
		// layers_へアクセスするため
		friend class Screen;
		// Object生成と同時にupdates_へ登録するため
		friend class Object;
		// RenderObject生成と同時にrenders_へ登録するため
		friend class RenderObject;

		//====================================================================================================
		// メンバ変数

		// 更新するObject管理リスト
		// 生成されたObjectはDxEngineのnow_scene_が持っているupdates_に自動で登録される
		std::list<std::shared_ptr<Object>> updates_;

		// 描画するRenderObject
		// 生成されたRenderObjectはDxEngineのnow_scene_が持っているrenders_に自動で登録される
		std::list<std::shared_ptr<RenderObject>> renders_;

		// 描画するScreen管理リスト
		std::list<std::shared_ptr<Screen>> screens_;

		//====================================================================================================
		// メンバ関数

		// 更新
		void update();

		// 描画
		void render();

		//====================================================================================================
	protected:
		//====================================================================================================
		// メンバ関数

		// 初期化（純粋仮想関数）
		virtual void initialize() = 0;

		// Sceneごとの更新
		// GameObjectの更新終了後に実行される
		virtual void lateUpdate() {}

		// 終了処理
		// 主にBGMの停止
		virtual void finalize() {}

		//====================================================================================================
	public:
		Scene() {}
		virtual ~Scene() {}

		//====================================================================================================
		// メンバ変数

		// GameObjectの更新フラグ
		// このフラグを降ろすと更新、物理演算、衝突判定を行わない（描画は行う）
		bool is_update_game_object_ = true;

		//====================================================================================================
		// メンバ関数

		// Scene内で管理しているGameObjectの取得
		// updates_から名前で検索して一致するものをlistで返す
		std::list<std::shared_ptr<Object>> getObjects(const std::string& name) const;

		// Screenの取得
		std::shared_ptr<Screen> getScreen(const std::string& name) const;

		// Scene内にScreenを生成
		std::shared_ptr<Screen> createScreenToScene(const std::string& screen_name, std::shared_ptr<Camera2D> camera, const int width, const int height);

		//====================================================================================================
		// static関数

		// Sceneの生成
		// テンプレート引数にはSceneクラスの派生クラスを指定する
		template<class TScene>
		static std::shared_ptr<TScene> create() { return SharedFactory::create<TScene>(); }

		//====================================================================================================
	};

}
