#pragma once
#include "Filter.h"

namespace imaging{

	class FilterGamma : public Filter {
	private:
	protected:
		float exp;
		vector<Color> gammaBuffer;
	public:
		FilterGamma();
		FilterGamma(float exp);
		FilterGamma(const FilterGamma &src);
		Image operator<<(const Image &image);
	};
}

