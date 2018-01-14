#include "Image.h"
#include "FilterLinear.h"
#include "FilterGamma.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace imaging;

int main(int argc, char **argv) {

	Image mainImage;
	string filename;
	bool loadVar = false;
	bool saveVar = false;
	unsigned int linearCount = 0;
	unsigned int gammaCount = 0;

	filename = argv[argc - 1];
	if (filename.find("Image") != string::npos) {
		loadVar = mainImage.load(filename, "ppm");
		if (loadVar) {
			cout << filename << " loaded successfully!" << endl;
		}
		else {
			system("pause");
			return -1;
		}
	}
	else {
		cerr << "No image was given. Program will exit now!" << endl;
		system("pause");
		return -1;
	}

	unsigned int index = 0;
	for (unsigned int i = 1; i < argc - 1; i++) {
		index = i;
		/*
		ean to argv[i] einai -f tote ksekinaei filtro
		opote an to argv[++i] einai gamma mpes stis prwti if
		kai efarmose to gamma filtro stin mainImage
		eidallws efarmose to linear filtro stin deuteri if
		*/
		if (string(argv[index]) == "-f") {
			index++;
			if (string(argv[index]) == "gamma") {
				gammaCount++;
				int gcounter = 0;
				float exp;
				if (isdigit(*argv[++index])) {
					exp = atof(argv[index]);
					gcounter++;
				}
				if (gcounter == 1) {
					FilterGamma filter(exp);
					mainImage = filter << mainImage;
				}
				else {
					cerr << "Gamma value is missing. Gamma filter won't be applied!" << endl;
				}
			}
			else if(string(argv[index]) == "linear"){
				linearCount++;
				int lcounter = 0;
				float aR, aG, aB, cR, cG, cB;
				if (isdigit(*argv[++index])) {
					aR = atof(argv[index]);
					lcounter++;
				}
				if (isdigit(*argv[++index])) {
					aG = atof(argv[index]);
					lcounter++;
				}
				if (isdigit(*argv[++index])) {
					aB = atof(argv[index]);
					lcounter++;
				}
				if (isdigit(*argv[++index])) {
					cR = atof(argv[index]);
					lcounter++;
				}
				if (isdigit(*argv[++index])) {
					cG = atof(argv[index]);
					lcounter++;
				}
				if (isdigit(*argv[++index])) {
					cB = atof(argv[index]);
					lcounter++;
				}
				if (lcounter == 6) {
					FilterLinear filter(Color(aR, aG, aB), Color(cR, cG, cB));
					mainImage = filter << mainImage;
				}
				else {
					cerr << "Filter values are missing. Linear filter won't be applied!" << endl;
				}
			}
		}
	}

	if (linearCount == 0 && gammaCount == 0) {
		cerr << "No filters were given. Program will exit now!" << endl;
		system("pause");
		return -1;
	}

	saveVar = mainImage.save(filename.c_str(), "ppm");
	if (saveVar) {
		cout << "filtered_" << filename << " saved successfully!" << endl;
	}
	else {
		return -1;
	}

	system("pause");
	return 0;
}