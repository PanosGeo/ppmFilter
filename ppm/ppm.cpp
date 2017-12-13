#include "ppm.h"
#include "../assignment1/Image.h"
#include "../assignment1/Color.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace imaging {

	float* ReadPPM(const char *filename, int *w, int *h)
	{
		ifstream imgFile(filename, ios_base::binary);
		string header[4];  //array that contains the header pieces(subs), ends with space or '\n'

		if (!imgFile.is_open()) {
			cerr << "Error opening image!" << endl;
			return nullptr;
		}
		else {
			string line;
			bool endOfHeader = false;
			int index = 0;

			while (getline(imgFile, line)) {
				istringstream iss(line);    //makes the string(line) a stream to cut it into pieces(subs)
				do {
					string sub;
					iss >> sub;
					if (sub.empty()) continue; //an diavaseis keno sinexise
					if (sub == "255") {
						endOfHeader = true;
					}
					header[index++] = sub; //vale to kathe element tou image header ston pinaka header
				} while (iss);
				if (endOfHeader) {
					break;
				}
			}
		}

		if (header[0].compare("P6") != 0 || header[3].compare("255") != 0 || (atoi(header[3].c_str()) > 255) || w == nullptr || h == nullptr) {
			cerr << "Error opening image!" << endl;
			return nullptr;
		}

		*w = atoi(header[1].c_str()); //makes the argument(string) "width" an integer
		*h = atoi(header[2].c_str()); //makes the argumet(string) "height" an integer

		unsigned int size = 3*(*w)*(*h);
		component_t *imgBuffer = new component_t[size]; //buffer to store image (binary) data
		for (unsigned int i = 0; i < size; i++) {
			imgBuffer[i] = (unsigned int)imgFile.get() / 255.0f;
		}

		imgFile.close();
		return imgBuffer;
	}


	bool WritePPM(const float* data, int w, int h, const char* filename)
	{
		ofstream newImage(filename, ios_base::binary);
		bool imgCreation = false;
		if (!newImage.is_open()) {
			cerr << "Error opening/creating image file!" << endl;
			return imgCreation;
		}
		else {
			string header = "P6\n" + to_string(w) + "\n" + to_string(h) + "\n255\n";
			unsigned int size = 3*w*h;
			char *imgBuffer = new char[size];

			for (unsigned int i = 0; i < size; i++) {
				imgBuffer[i] = data[i] * 255.0f;
			}
			newImage.write(header.c_str(), header.size()); //write header in the new image file
			newImage.write(imgBuffer, size);			  //write binary data in the new image file
			newImage.flush();
			imgCreation = true;
			newImage.close();
		}
		return imgCreation;
	}
}
