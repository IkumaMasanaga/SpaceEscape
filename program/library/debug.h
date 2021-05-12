#pragma once
#include <string>
#include "DxLib.h"


namespace t2k {

	class Debug final {
	private:
		Debug() {}
		Debug(const Debug&) = delete;
		Debug& operator = (const Debug&) = delete;

	public:
		template <class ... Args>
		inline static void log(const std::string& string, Args ... args) {
			size_t len = std::snprintf(nullptr, 0, string.c_str(), args ...);
			std::vector<char> buf(len + 1);
			std::snprintf(&buf[0], len + 1, string.c_str(), args ...);
			printfDx("Debug::log > %s\n", std::string(&buf[0], &buf[0] + len).c_str());
		}

		static void clearLog() {
			clsDx();
		}
	};

}
