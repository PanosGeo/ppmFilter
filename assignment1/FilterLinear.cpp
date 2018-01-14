#include "FilterLinear.h"
#include <iostream>

namespace imaging {

	FilterLinear::FilterLinear() {}

	FilterLinear::FilterLinear(Color a, Color c){
		this->a = a;
		this->c = c;
	}

	FilterLinear::FilterLinear(const FilterLinear &src) {
		a = src.a;
		c = src.c;
	}

	Image FilterLinear::operator<<(const Image &image)
	{
		unsigned int index = 0;
		linearBuffer.resize(image.getWidth()*image.getHeight());

		for (unsigned int i = 0; i < image.getWidth(); i++) {
			for (unsigned int j = 0; j < image.getHeight(); j++) {
				/*
				p`(x,y) = a*p(x,y)+c
				*/
				linearBuffer[index] = a * image.getElement(i, j) + c;
				/*
				efarmozei gia kathe rgb enan elegxo an einai panw apo 1.0 i timi tou na tin boundarei sto 1.0
				ki an einai katw apo 0.0 na tin boundarei sto 0.0
				oi clampToUpperBound kai clampToLowerBound einai etoimes stin Vec3.h
				*/
				linearBuffer[index] = linearBuffer[index].clampToUpperBound(1.0);
				linearBuffer[index] = linearBuffer[index].clampToLowerBound(0.0);
				index++;
			}
		}
		/*
		dimiourgia neas eikonas gia na epistrepsoume autin
		meta tin efarmogi tou gamma filtrou
		*/
		Image temp(image.getWidth(), image.getHeight());
		temp.setData(linearBuffer);
		return temp;
	}
}