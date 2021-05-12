#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <cstdint>
#include <vector>
#include <string>

namespace t2k{

    const float PI = 3.14159265358979f;

	#define safeDelete( p ){ if(p){ delete p ; p = nullptr ; } }
	inline int ARGB8( int a, int r, int g, int b ) { return ( a << 24 | r << 16 | g << 8 | b ); }
	inline int RGBA8( int r, int g, int b, int a = 255 ) { return ( r << 24 | g << 16 | b << 8 | a ); }
	inline int ABGR8(int a, int b, int g, int r) { return (a << 24 | b << 16 | g << 8 | r); }

	//----------------------------------------------------------------------------------------------
	// CSV Loader
	std::vector<std::vector<std::string>> loadCsv( const std::string& file_name );

	//----------------------------------------------------------------------------------------------
	// ラジアンからデグリーへの変換
	inline float toDegree(float radian) {
		return (radian / PI * 180.0f );
	}

	//----------------------------------------------------------------------------------------------
	// デグリーからラジアンへの変換
	inline float toRadian(float degree) {
		return (PI / 180.0f * degree );
	}

	//----------------------------------------------------------------------------------------------
	// デバッグコンソールへの出力
	inline void debugTrace(const char* _str, ...) {
    #if _DEBUG
		char buff[255] = { 0 };
		va_list argptr;
		va_start(argptr, _str);
		vsprintf_s(buff, _str, argptr);
		va_end(argptr);
		OutputDebugString(buff);
    #endif
	}

	//----------------------------------------------------------------------------------------------
	// 警告出力
    #define warningMassage( m ){                            \
        t2k::debugTrace("\n↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓\n") ;      \
        t2k::debugTrace( m ) ; t2k::debugTrace("\n") ;                \
        t2k::debugTrace("%s", __FILE__) ; t2k::debugTrace("\n") ;         \
        t2k::debugTrace("行番号 : %d", __LINE__) ; t2k::debugTrace("\n") ;\
        t2k::debugTrace("\n↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑\n\n") ;    \
    }

	//----------------------------------------------------------------------------------------------
	// 下位ビット 0 から 指定桁のビットが有効な数値を作る
	inline int onBit(int n) { return (1 << n); }

	//----------------------------------------------------------------------------------------------
	// １ビットづつ間隔を開ける
	int spaceBit32(int n);

	//----------------------------------------------------------------------------------------------
	// 有効なビットをカウントする
	int countBit8(const uint8_t v);
	int countBit16(const uint16_t v);
	int countBit32(const uint32_t v);
	int countBit64(const uint64_t v);

	//----------------------------------------------------------------------------------------------
	// 最大有効ビット数（MSB：Most Significant Bit）
	// 全てのビットが 0 なら false が帰る
	// 例) value が 0xFF なら out には value の Bit数-1 が入る uint8_t なら 7
	bool mostBit8(const uint8_t value, int& out);
	bool mostBit16(const uint16_t value, int& out);
	bool mostBit32(const uint32_t value, int& out);
	bool mostBit64(const uint64_t value, int& out);

	//----------------------------------------------------------------------------------------------
	// 最小有効ビット数（LSB：Least Significant Bit）
	// 全てのビットが 0 なら false が帰る
	// 例) value が 0x01 なら out には 0 が入る
	bool leastBit8(const uint8_t value, int& out);
	bool leastBit16(const uint16_t value, int& out);
	bool leastBit32(const uint32_t value, int& out);
	bool leastBit64(const uint64_t value, int& out);

	//----------------------------------------------------------------------------------------------
	// フォーマット指定対応string
	template <class ... Args>
	inline std::string formatToString(const std::string& fmt, Args ... args) {
		size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args ...);
		std::vector<char> buf(len + 1);
		std::snprintf(&buf[0], len + 1, fmt.c_str(), args ...);
		return std::string(&buf[0], &buf[0] + len);
	}

	//----------------------------------------------------------------------------------------------
	// 文字列を指定文字で区切ったvectorを返す
	std::vector<std::string> split(const std::string& str, const char ch);

	//----------------------------------------------------------------------------------------------
	// 範囲内の乱数の取得
	int randomRangeI(const int min, const int max);
	float randomRangeF(const float min, const float max);
}