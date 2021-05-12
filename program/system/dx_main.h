#pragma once


namespace sys {

	class DxMain final {
	private:
		DxMain() {}
		DxMain(const DxMain&) = delete;
		DxMain& operator = (const DxMain&) = delete;

	public:

		static int update();

	};

}
