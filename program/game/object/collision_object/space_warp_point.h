#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class SpaceWarpPoint final : public dxe::CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<SpaceWarpPoint>;
		using WeakPtr = std::weak_ptr<SpaceWarpPoint>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// ���[�v���CSV�t�H���_
		std::string warp_csv_folder_;

		// �f���̉摜
		dxe::Sprite::SharedPtr planet_ = nullptr;

		// ���[�v�摜
		dxe::AnimationSprite::SharedPtr warp_ = nullptr;

		// �L�[�摜
		dxe::AnimationSprite::SharedPtr key_ = nullptr;

		// �V�[���փ��[�v�V�O�i�����΂��p
		bool is_warp_ = false;

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update() final override;

		// �Փˎ�
		void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		//====================================================================================================
	public:
		SpaceWarpPoint() {}
		~SpaceWarpPoint() {}

		//====================================================================================================
		// �����o�֐�

		// ���[�v���CSV�t�@�C���̃p�X
		inline std::string getWarpDestination() const { return warp_csv_folder_; }

		// �V�[���փV�O�i�����΂��p
		inline bool isWarp() const { return is_warp_; }

		//====================================================================================================
		// static�֐�

		// ����
		static SpaceWarpPoint::SharedPtr create(const std::string& csv_folder);

		//====================================================================================================
	};

}
