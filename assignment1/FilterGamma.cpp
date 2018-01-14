#include "FilterGamma.h"
#include <iostream>
#include <cmath>

namespace imaging {

	FilterGamma::FilterGamma() {}

	FilterGamma::FilterGamma(float exp) {
		this->exp = exp;
	}

	FilterGamma::FilterGamma(const FilterGamma &src) {
		this->exp = src.exp;
	}

	Image FilterGamma::operator<<(const Image &image) {

		gammaBuffer.resize(image.getWidth()*image.getHeight());
		unsigned int index = 0;

		if (exp >= 0.5 && exp <= 2.0) {
			for (unsigned int i = 0; i < image.getWidth(); i++) {
				for (unsigned int j = 0; j < image.getHeight(); j++) {
					/*
					p`(x,y) = p(x,y)^exp
					*/
					gammaBuffer[index].r = pow(image.getElement(i, j).r, exp);
					gammaBuffer[index].g = pow(image.getElement(i, j).g, exp);
					gammaBuffer[index].b = pow(image.getElement(i, j).b, exp);
					/*
					efarmozei gia kathe rgb enan elegxo an einai panw apo 1.0 i timi tou na tin boundarei sto 1.0
					ki an einai katw apo 0.0 na tin boundarei sto 0.0
					oi clampToUpperBound kai clampToLowerBound einai etoimes stin Vec3.h
					*/
					gammaBuffer[index] = gammaBuffer[index].clampToUpperBound(1.0);
					gammaBuffer[index] = gammaBuffer[index].clampToLowerBound(0.0);
					index++;
				}
			}
			/*
			dimiourgia neas eikonas gia na epistrepsoume autin
			meta tin efarmogi tou gamma filtrou
			*/
			Image temp(image.getWidth(), image.getHeight());
			temp.setData(gammaBuffer);
			return temp;
		}
		else {
			cerr << "Out of bounds FilterGamma exponent value!" << endl;
			cerr << "Gamma filter won't be applied!" << endl;
			return image;
		}
	}
}