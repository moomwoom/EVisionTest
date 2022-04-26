#include "main.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Mechanics.cpp"
using namespace std;


pros::Controller master(pros::E_CONTROLLER_MASTER);

// values acquired from the vision utility
pros::vision_signature_s_t YELLOW_SIG =
	pros::Vision::signature_from_utility(1, -1, 2245, 1122, -4291, -575, -2433, 1.100, 0);
pros::vision_signature_s_t BLUE_SIG =
	pros::Vision::signature_from_utility(2, -3735, -2107, -2921, 4959, 14005, 9482, 1.300, 0);
pros::vision_signature_s_t RED_SIG =
	pros::Vision::signature_from_utility(3, 575, 9969, 5272, -967, 81, -443, 1.100, 0);

pros::Vision FrontVision(4);

static int VisionReader = 1;
static const int MaxVisionReader = 3;
pros::vision_object_s_t rtn = FrontVision.get_by_sig(0, VisionReader);

void ChangeVisionReader(){
	VisionReader++;
	if (VisionReader > MaxVisionReader){VisionReader -= VisionReader;}
	FrontVision.set_signature(1, &YELLOW_SIG);
	FrontVision.set_signature(2, &BLUE_SIG);
	FrontVision.set_signature(3, &RED_SIG);
}

void initialize() {
	pros::lcd::initialize();
  FrontVision.clear_led();
  pros::lcd::register_btn1_cb(ChangeVisionReader);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}


void opcontrol() {


	
	

	// pros::vision_signature_s_t sig = FrontVision.get_signature(x);
	// pros::Vision::print_signature(sig);

	if(VisionReader == 1)pros::lcd::print(0, "Yellow W %d, H %d, A %d, X %d, Y %d, Sig %d", rtn.width, rtn.height, rtn.x_middle_coord, rtn.y_middle_coord, FrontVision.get_signature(1));
    else if(VisionReader == 2)pros::lcd::print(1, "Blue W %d, H %d, A %d, X %d, Y %d, Sig %d", rtn.width, rtn.height, rtn.x_middle_coord, rtn.y_middle_coord, FrontVision.get_signature(2));
    else if(VisionReader == 3)pros::lcd::print(2, "Yellow W %d, H %d, A %d, X %d, Y %d, Sig %d", rtn.width, rtn.height, rtn.x_middle_coord, rtn.y_middle_coord, FrontVision.get_signature(3));

	
	while (true) {


		// pros::vision_object_s_t rtn = FrontVision.get_by_sig(0, x);
	/*	pros::lcd::print;
		pros::lcd::print(1, "Red W %d, H %d, A %d, X %d, Y %d, Sig %d", rtn.width, rtn.height, rtn.x_middle_coord, rtn.y_middle_coord, FrontVision.get_signature(2));
		pros::lcd::print(2, "W %d, H %d, A %d, X %d, Y %d, Sig %d", rtn.width, rtn.height, rtn.x_middle_coord, rtn.y_middle_coord, FrontVision.get_signature(3));
	*/	/*
		pros::lcd::print(1, "Height %d", rtn.height);
		pros::lcd::print(2, "Angle %d", rtn.angle);
		pros::lcd::print(3, "Middle X %d", rtn.x_middle_coord);
		pros::lcd::print(4, "Middle Y %d", rtn.y_middle_coord);
		pros::lcd::print(5, "Signature %d", FrontVision.get_signature(1));
*/


		ofstream Vision_File("Vision_Info.csv");
		Vision_File << rtn.width << "," << rtn.height << "," << rtn.x_middle_coord << "," << rtn.y_middle_coord << '\n';
		Vision_File.close();
		pros::lcd::print(6, "signature %d", rtn.signature);
		if (rtn.signature == 255) pros::lcd::print(7, "signature %d", rtn.signature << errno);

		// Gets the largest object of the EXAMPLE_SIG signature
		// std::cout << "sig: " << rtn.YELLOW_SIG << std::endl;
		// std::cout << "sig: " << rtn.BLUE_SIG << std::endl;
		// std::cout << "sig: " << rtn.RED_SIG << std::endl;
		// Prints "sig: 1"
		pros::delay(200);
	}
}
