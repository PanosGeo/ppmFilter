#pragma once
#include <vector>
#include "Vec3.h"
#include "../ppm/ppm.h"

using namespace std;

namespace math {

	template<typename T>
	class Array
	{
	private:

	protected:
		vector<T> buffer;
		unsigned int width,
			height;

	public:

		const unsigned int getWidth() const { return width; }
		const unsigned int getHeight() const { return height; }

		vector<T>& getRawDataPtr() {
			return this->buffer;
		}

		T getElement(unsigned int x, unsigned int y) const {
			T t;
			if (x >= width || y >= height) {
				cerr << "Pixel location out of bounds, will not be get!" << endl;
				return t;
			}
			else {
				t = buffer[x * height + y]; //place buffer[i] in color
				return t;
			}
		}

		void setElement(unsigned int x, unsigned int y, T &value) {
			if (x >= width || y >= height) {
				cerr << "Pixel location out of bounds, will not be set!" << endl;
			}
			else {
				buffer[x * height + y] = value; //put value in buffer[i]  
			}
		}

		void setData(const vector<T> &data_ptr) {
			buffer.resize(width*height);
			for (unsigned int i = 0; i < width*height; i++) {
				buffer[i] = data_ptr[i];
			}
		}

		Array() {
			width = 0;
			height = 0;
			buffer.resize(width*height);
		}

		Array(unsigned int w, unsigned int h) {
			this->width = w;
			this->height = h;
			buffer.resize(this->width*this->height);
		}

		Array(unsigned int w, unsigned int h, const vector<T> &data_ptr) : width(w), height(h) {
			setData(data_ptr);
		}

		Array(const Array &src) {
			width = src.width;
			height = src.height;
			setData(src.buffer);
		}

		virtual ~Array() {}

		Array& operator= (const Array &right) {
			if (&right == this) {
				return *this;
			}
			if (!buffer.empty()) {
				buffer.clear();
			}
			width = right.width;
			height = right.height;
			setData(right.buffer);
			return *this;
		}

		Array& operator() (unsigned int x, unsigned int y) {
			return buffer[x * height + y];
		}
	};
}