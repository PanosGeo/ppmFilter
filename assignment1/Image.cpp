#include "Image.h"
#include <iostream>

using namespace std;

namespace imaging {

	/*
	Constructors
	*/
	Image::Image() : Array(0, 0) {
		buffer.resize(width*height);
	}

	Image::Image(unsigned int width, unsigned int height) : Array(width, height) {
		buffer.resize(width*height);
	}

	Image::Image(unsigned int width, unsigned int height, const vector<Color> &data_ptr) : Array(width, height)
	{
		setData(data_ptr);
	}

	/*
	Copy Constructor
	*/
	Image::Image(const Image &src) : Array(src.width, src.height)
	{
		setData(src.buffer);
	}

	//Destructor
	Image::~Image()
	{
		Array::~Array();
	}

	bool Image::load(const string &filename, const string &format)
	{
		int imageWidth = 0;
		int imageHeight = 0;
		float *floatBuffer = nullptr;
		if (filename.size() > format.size()) {
			if (filename.compare(filename.size() - format.size(), format.size(), format) == 0) {
				floatBuffer = ReadPPM(filename.c_str(), &imageWidth, &imageHeight);
				if (floatBuffer == nullptr) {
					cerr << "Buffer is empty. Program will exit!" << endl;
					return false;
				}
				else {
					this->width = imageWidth;
					this->height = imageHeight;
					unsigned int size = this->width*this->height;
					this->buffer.resize(size); //allocates enough memory for the image buffer to push data from buffer returned by ReadPPM()
					unsigned int index = 0;
					for (unsigned int i = 0; i < buffer.size(); i++) {
						buffer[i].r = floatBuffer[index++];
						buffer[i].g = floatBuffer[index++];
						buffer[i].b = floatBuffer[index++];
					}
					return true;
				}
			}
			else {
				cerr << "Wrong suffix!!!" << endl;
				cerr << "Image could not be saved!" << endl;
				system("pause");
				return false;
			}
		}
		else {
			cerr << "Invalid image name!" << endl;
			system("pause");
			return false;
		}

	}

	bool Image::save(const string &filename, const string &format)
	{
		unsigned int size = this->width*this->height;
		float *floatBuffer = new float[3 * size];
		unsigned int index = 0;

		for (unsigned int i = 0; i < size; i++) {
			floatBuffer[index++] = buffer[i].r;
			floatBuffer[index++] = buffer[i].g;
			floatBuffer[index++] = buffer[i].b;
		}

		if (filename.size() > format.size()) {
			string substr = filename.substr(0, filename.size() - 4); // string = Image0x
			const_cast<string&>(filename) = "filtered_" + substr + filename.substr(filename.size() - 4, 4);
			if (filename.compare(filename.size() - format.size(), format.size(), format) == 0) {
				bool imgCreation = WritePPM(floatBuffer, this->getWidth(), this->getHeight(), filename.c_str());
				if (imgCreation) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				cerr << "Wrong suffix!!!" << endl;
				cerr << "Image could not be saved!" << endl;
				return false;
			}
		}
		else {
			cerr << "Invalid negative image name!" << endl;
			system("pause");
			return false;
		}
	}
}
