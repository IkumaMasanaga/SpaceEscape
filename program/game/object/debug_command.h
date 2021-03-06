#pragma once
#include "../../engine/dxe.h"


class DebugCommand final : public dxe::Object {
public:
	using SharedPtr = std::shared_ptr<DebugCommand>;
	using WeakPtr = std::weak_ptr<DebugCommand>;
private:
	//====================================================================================================
	// メンバ関数

	// 生成時
	void onCreated() final override;

	// 更新
	void update() final override;

	//====================================================================================================
public:
	DebugCommand() {}
	~DebugCommand() {}
};
