#pragma once
#include <string>
#include "shared_factory.h"
#include "shared_flyweight_map.h"

namespace t2k{

	class Texture final : public SharedFactory<Texture>, public SharedFlyweightMapInterface<std::string, Texture> {
	public:
		typedef std::shared_ptr<Texture> SharedPtr;
		typedef std::weak_ptr<Texture> WeakPtr;
	private:
		// fromFlyWeightLoader, finalize���ĂԂ���
		friend class SharedFlyweightMapInterface<std::string, Texture>;

		int image_ = 0;
		int size_w_ = 0;
		int size_h_ = 0;
		std::string file_path_;

		// SharedFlyWeightMap �p�̃��[�_�[
		static Texture::SharedPtr fromFlyWeightLoader(const std::string& key, const std::string& file_name);

		// SharedFlyWeightMap �p�̏I������
		void finalize() final override;

	public:
		Texture() {}
		~Texture(){}

		inline int getImage() const { return image_; }
		inline int getWidth() const { return size_w_; }
		inline int getHeight() const { return size_h_; }

		// �e�N�X�`������͈͂��w�肵�ĐV�����e�N�X�`���𐶐�����
		Texture::SharedPtr partiallyCreatedFromTexture( const int src_left_up_x, const int src_left_up_y, const int width, const int height ) const;

		// �`��e�N�X�`���̐���
		static Texture::SharedPtr createRenderTexture( const int width, const int height );

		// ���\�[�X�t�@�C������e�N�X�`���𐶐�
		static Texture::SharedPtr createFromFile(const std::string& file_path);

		// ���\�[�X�t�@�C������e�N�X�`����vector�𐶐�
		static std::vector<Texture::SharedPtr> createVectorFromFile(const std::string& file_path, const int all_num, const int x_num, const int y_num, const int width, const int height);
	};

}
