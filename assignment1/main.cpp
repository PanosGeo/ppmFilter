#include "Color.h"
#include "Image.h"
#include "../ppm/ppm.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace imaging;

	int main(int argc, char **argv) {

		Image *mainImage = new Image();
		string filename;
		bool loadVar = false;
		bool saveVar = false;
		
		if (argc == 2) {
			filename = argv[1];
			loadVar = mainImage->load(filename, "ppm");
			if (loadVar) {
				cout << "Image loaded successfully!" << endl;
			}
			else {
				system("pause");
				return -1;
			}
		}

		else {
			cout << "Give the name of the image you want: ";
			getline(cin, filename);
			loadVar = mainImage->load(filename, "ppm");
			if (loadVar) {
				cout << "Image loaded successfully!" << endl;
			}
			else {
				return -1;
			}

		}

		cout << "Image dimensions are: " << mainImage->getWidth() << " x " << mainImage->getHeight() << endl;

		/*
		Calculation of negative color
		*/
		Color neg(1.0, 1.0, 1.0);
		unsigned int index = 0;
		for (unsigned int i = 0; i < (mainImage->getHeight()); i++) {
			for (unsigned int j = 0; j < (mainImage->getWidth()); j++) {
				mainImage->setPixel(j, i, neg - mainImage->getPixel(j, i));
			}
		}

		cout << "Give the name of the negative image you want: ";
		getline(cin, filename);
		
		saveVar = mainImage->save(filename.c_str(), "ppm");
		if (saveVar) {
			cout << "New image saved successfully!" << endl;
		}
		else {
			return -1;
		}

		delete mainImage;
		system("pause");
		return 0;
	}
