#pragma once
#include "Filter.h"

namespace imaging {

	class FilterLinear : public Filter {
	private:
	protected:
		Color a;
		Color c;
		vector<Color> linearBuffer;
	public:
		FilterLinear();
		FilterLinear(Color a, Color c);
		FilterLinear(const FilterLinear &src);

		Image operator<<(const Image &image);
	};
}