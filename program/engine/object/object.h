#pragma once
#include <typeinfo>
#include "../../library/t2klib.h"


namespace dxe {

	// ���ׂĂ�Object�̊��N���X
	// �����m�F
	// ���O�̐ݒ�
	// �X�V
	class Object : public t2k::SharedFactory<Object> {
	public:
		using SharedPtr = std::shared_ptr<Object>;
		using WeakPtr = std::weak_ptr<Object>;
	private:
		// �V�[���؂�ւ�����instancs_count_��0�ɏ��������邽��
		friend class DxEngine;
		// shared_from_this_constructor���ĂԂ���
		friend class t2k::SharedFactory<Object>;
		// �����Ɠ�����updates_�ɓo�^���邽��
		friend class Scene;

		//====================================================================================================
		// �����o�ϐ�

		// ���O
		std::string name_ = "unknown";

		// �����t���O
		bool is_alive_ = true;

		// �L���t���O
		bool is_active_ = true;

		// Object�B��̃C���X�^���XID
		unsigned int instance_id_;

		//====================================================================================================
		// static�ϐ�

		// Scene���ō��܂Ő������Ă���Object�̐�
		inline static unsigned int instance_count_ = 0;

		//====================================================================================================
		// �����o�֐�

		// shared_from_this���g����R���X�g���N�^�i�����t���j
		void shared_from_this_constructor_exist_argument(std::any a) final override {}

		//====================================================================================================
	protected:
		//====================================================================================================
		// �����o�֐�

		// shared_from_this���g����R���X�g���N�^
		virtual void shared_from_this_constructor() override;

		// �X�V
		virtual void update() {}

		// ������ɌĂ΂��
		virtual void onCreated() {}

		//====================================================================================================
	public:
		Object() {
			instance_id_ = instance_count_;
			++instance_count_;
		}
		virtual ~Object() {}

		//====================================================================================================
		// �����o�ϐ�

		// �X�V�D��x
		// �������ق�����ɍX�V�����
		float update_priority_ = 0.0f;

		// ��ɍX�V����t���O
		// �L���ł������X�V�����
		bool is_update_always_ = false;

		//====================================================================================================
		// �����o�֐�

		// ���O�̐ݒ�
		inline void setName(const std::string& name) { name_ = name; }

		// ���g�̍폜
		inline void destroy() { is_alive_ = false; }

		// ���g�̗L���t���O�̐ݒ�
		inline void setActive(const bool is_active) { is_active_ = is_active; }

		// ���O�̎擾
		inline std::string getName() const { return name_; }

		// �����t���O�̎擾
		inline bool isAlive() const { return is_alive_; }

		// �L���t���O�̎擾
		inline bool isActive() const { return is_active_; }

		// Object�B��̃C���X�^���XID�̎擾
		inline unsigned int getInstanceId() const { return instance_id_; }

		// �N���X�ŗL��ID�̎擾
		inline unsigned int getHashCode() const { return typeid(*this).hash_code(); }

		//====================================================================================================
		// static�֐�

		// Scene���Ő������Ă���Object�̑������擾
		inline static unsigned int getInstanceCount() { return instance_count_; }

		// �N���X�ŗL��ID�̎擾
		template <class TObject>
		inline static unsigned int getHashCode() { return typeid(TObject).hash_code(); }

		//====================================================================================================
	};

}
