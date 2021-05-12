#pragma once


namespace t2k {

	class Color final {
	public:
		Color() {}
		Color(const float white) : r_(white), g_(white), b_(white) {}
		Color(const float r, const float g, const float b) : r_(r), g_(g), b_(b) {}
		~Color() {}

		float r_ = 1.0f;
		float g_ = 1.0f;
		float b_ = 1.0f;

		inline void set(const float white) { r_ = g_ = b_ = white; }
		inline void set(const float r, const float g, const float b) { r_ = r; g_ = g; b_ = b; }
		inline unsigned int toInt() const { return (int)(r_ * 255) << 16 | (int)(g_ * 255) << 8 | (int)(b_ * 255); }

		inline static unsigned int toInt(const float white) { return (int)(white * 255) << 16 | (int)(white * 255) << 8 | (int)(white * 255); }
		inline static unsigned int toInt(const float r, const float g, const float b) { return (int)(r * 255) << 16 | (int)(g * 255) << 8 | (int)(b * 255); }

	};

}
