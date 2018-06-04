#pragma once

#ifndef PRINTTESTING
#define PRINTTESTING

#include <vector>

class Print
{
	private:
		std::vector<int> intData;
		std::vector<float> floatData;

	public:
		Print(int x);
		Print(float x);

		int getIntPrintSize();
		int getFloatPrintSie();


};
	





#endif