#pragma once
#include "../../engine/dxe.h"


class DebugCommand final : public dxe::Object {
public:
	using SharedPtr = std::shared_ptr<DebugCommand>;
	using WeakPtr = std::weak_ptr<DebugCommand>;
private:
	//====================================================================================================
	// �����o�֐�

	// ������
	void onCreated() final override;

	// �X�V
	void update() final override;

	//====================================================================================================
public:
	DebugCommand() {}
	~DebugCommand() {}
};
