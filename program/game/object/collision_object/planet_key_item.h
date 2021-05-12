#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	enum class PlanetID;

	class PlanetKeyItem final : public dxe::CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<PlanetKeyItem>;
		using WeakPtr = std::weak_ptr<PlanetKeyItem>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �摜�̃t�@�C���p�X
		std::string sprite_file_path_;

		// �e�L�X�g�̃t�@�C���p�X
		std::string text_file_path_;

		// �f���ԍ�
		PlanetID planet_id_ = (PlanetID)0;

		//====================================================================================================
	public:
		PlanetKeyItem() {}
		~PlanetKeyItem() {}

		//====================================================================================================
		// �����o�֐�

		// �摜�̃t�@�C���p�X�̎擾
		inline std::string getSpriteFilePath() const { return sprite_file_path_; }

		// �e�L�X�g�̃t�@�C���p�X�̎擾
		inline std::string getTextFilePath() const { return text_file_path_; }

		// �f���ԍ��̎擾
		inline PlanetID getPlanetID() const { return planet_id_; }

		//====================================================================================================
		// static�֐�

		// ����
		static PlanetKeyItem::SharedPtr create(const std::string& sprite_path, const PlanetID planet_id, const std::string& text_path);

		//====================================================================================================
	};

}
