#pragma once
#include "render_object.h"


namespace dxe {

	// x�����������񋓒萔
	enum class AlignModeX {
		LEFT,	// ������
		CENTER,	// ��������
		RIGHT	// �E����
	};

	// y�����������񋓒萔
	enum class AlignModeY {
		TOP,	// �㑵��
		MIDDLE,	// ��������
		BOTTOM	// ������
	};

	class Text final : public RenderObject {
	public:
		using SharedPtr = std::shared_ptr<Text>;
		using WeakPtr = std::weak_ptr<Text>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// ������
		std::vector<std::string> text_;

		//====================================================================================================
		// �����o�֐�

		// �`��
		void render(std::shared_ptr<Screen> screen) final override;

		//====================================================================================================
	public:
		Text() {}
		~Text() {}

		//====================================================================================================
		// �����o�ϐ�

		// x����������
		AlignModeX align_mode_x_ = AlignModeX::LEFT;

		// y����������
		AlignModeY align_mode_y_ = AlignModeY::TOP;

		// �t�H���g�T�C�Y
		int font_size_ = 20;

		// �s��
		int interval_ = 0;

		// ������̐F
		t2k::Color color_;

		//====================================================================================================
		// �����o�֐�

		// ������̕ύX
		void changeText(const std::string& text);

		// ���\�[�X�t�@�C���i�e�L�X�g�t�@�C���j���當����̕ύX
		void changeTextFromFile(const std::string& file_path);

		//====================================================================================================
		// static�֐�

		// ����
		static Text::SharedPtr create(const std::string& text);

		// ���\�[�X�t�@�C���i�e�L�X�g�t�@�C���j���琶��
		static Text::SharedPtr createFromFile(const std::string& file_path);

		//====================================================================================================
	};

}
