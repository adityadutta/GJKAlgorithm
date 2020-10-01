#include "GameManager.h"
#include<memory>
#include <iostream>

int main(int argc, char* args[])
{
	auto ptr = std::unique_ptr<GameManager>(new GameManager());
	bool status = ptr->onCreate();
	if (status == true) {
		ptr->Run();
	}
	else if (status == false) {
		/// You should have learned about stderr (std::cerr) in Operating Systems 
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;
	}

	return 0;
}