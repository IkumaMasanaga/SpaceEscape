#pragma once
#include "../library/t2klib.h"


namespace dxe {

	// �␳�����񋓒萔
	enum class CorrectDirection {
		NONE,	// �␳�Ȃ�
		UP,		// ��ɕ␳
		DOWN,	// ���ɕ␳
		LEFT,	// ���ɕ␳
		RIGHT	// �E�ɕ␳
	};

	// �Փ˔���N���X
	// �������ꂽColliisionObject�͎����I�ɂ��̃N���X�ɓo�^����܂�
	// �Փ˔�����s
	// �Փ˔����`�`��i�f�o�b�O�p�j
	class CollisionManager final : public t2k::Singleton<CollisionManager> {
	private:
		// ���N���X�Ő������邽��
		friend class t2k::Singleton<CollisionManager>;
		// updatePrevPosition, collision���ĂԂ���
		friend class Scene;
		// renderDebugArea���ĂԂ���
		friend class Screen;
		// �����ƂƂ���collision_objects_�ɓo�^���邽��
		friend class CollisionObject;

		CollisionManager() {}

		//====================================================================================================
		// �����o�ϐ�

		// CollisionObject�ꊇ�Ǘ��p���X�g
		std::list<std::shared_ptr<CollisionObject>> collision_objects_;

		//====================================================================================================
		// �����o�֐�

		// update�O��GameObject�̍��W���X�V
		void updatePrevPosition();

		// �Փ˔��菈�����s
		void collision();

		// �Փ˔����`�̕`��i�f�o�b�O�p�j
		void renderDebugArea(std::shared_ptr<Screen> screen) const;

		//====================================================================================================
	public:
		~CollisionManager() {}

		//====================================================================================================
		// �����o�ϐ�

		// �Փ˔����`�̕`��t���O�i�f�o�b�O�p�j
		bool is_render_debug_area_ = false;

		//====================================================================================================
	};

}
