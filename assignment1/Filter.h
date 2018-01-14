#pragma once
#include "Image.h"

namespace imaging {

	class Filter {
	
	public:
		virtual Image operator<<(const Image &image) = 0;
		Filter() {}
		Filter(const Filter &src) {}
	};
}