#include "Image.h"
#include "../ppm/ppm.h"
#include <iostream>


using namespace std;

namespace imaging {

	Color* Image::getRawDataPtr()
	{
		return this->buffer;
	}

	Color Image::getPixel(unsigned int x, unsigned int y) const
	{
		Color color; //Object color(0,0,0)

		if (x >= width || y >= height) {
			cerr << "Pixel location out of bounds: Pixel won't load!" << endl;
			return color;
		}
		else {
			color = buffer[(y * width + x)]; //place buffer[i].r in r
			return color;
		}
	}

	void Image::setPixel(unsigned int x, unsigned int y, Color &value)
	{
		if (x >= width || y >= height) {
			cerr << "Pixel location out of bounds: Pixel will not be set!" << endl;
		}
		else {
			buffer[(y * width + x)] = value; //put value.r in buffer[i].r  
		}
	}

	void Image::setData(const Color *&data_ptr)
	{
		for (unsigned int i = 0; i < width*height; i++) {
			buffer[i] = data_ptr[i];
		}
	}

	/*
	Constructors
	*/
	Image::Image()
	{
		this->width = 0;
		this->height = 0;
		this->buffer = nullptr;
	
	}

	Image::Image(unsigned int width, unsigned int height)
	{
		this->width = width;
		this->height = height;
		this->buffer = new Color[width*height];
	}

	Image::Image(unsigned int width, unsigned int height, const Color *data_ptr) : width(width), height(height), buffer(new Color[width*height])
	{
		setData(data_ptr);
	}

	/*
	Copy Constructor
	*/
	Image::Image(const Image &src)
	{
		width = src.width;
		height = src.height;
		buffer = new Color[width*height];
		memcpy(buffer, src.buffer, width*height);
	}

	//Destructor
	Image::~Image()
	{
		delete buffer;
	}

	//Copy assignment operator
	Image& Image::operator=(const Image &right)
	{
		//if the objects are the same (for some reason)
		if (&right == this) {
			return *this;
		}
		if (buffer != nullptr) {
			delete buffer;
		}
		width = right.width;
		height = right.height;
		buffer = new Color[width*height];
		memcpy(buffer, right.buffer, width*height);
		return *this;
	}

	bool Image::load(const string &filename, const string &format)
	{
		int imageWidth = 0;
		int imageHeight = 0;
		component_t *floatBuffer = nullptr;
		if (filename.size() > format.size()) {
			if (filename.compare(filename.size() - format.size(), format.size(), format) == 0) {
				floatBuffer = ReadPPM(filename.c_str(), &imageWidth, &imageHeight);
				if (floatBuffer == nullptr) {
					cerr << "Buffer is empty. Program will exit!" << endl;
					system("pause");
					return false;
				}
				else {
					this->width = imageWidth;
					this->height = imageHeight;
					unsigned int size = this->width*this->height;
					this->buffer = new Color[size];
					unsigned int index = 0;

					for (unsigned int i = 0; i < size; i++) {
						this->buffer[i].r = floatBuffer[index++];
						this->buffer[i].g = floatBuffer[index++];
						this->buffer[i].b = floatBuffer[index++];
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
		component_t *floatBuffer = new component_t[3 * size];
		unsigned int index = 0;

		for (unsigned int i = 0; i < size; i++) {
			floatBuffer[index++] = this->buffer[i].r;
			floatBuffer[index++] = this->buffer[i].g;
			floatBuffer[index++] = this->buffer[i].b;
		}

		if (filename.size() > format.size()) {
			string substr = filename.substr(0, filename.size() - 4); // string = Image0x
			const_cast<string&>(filename) = substr + "_neg" + filename.substr(filename.size() - 4, 4);
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
