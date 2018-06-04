#include "PrintTesting.h"

Print::Print(int x)
{
	intData.push_back(x);
}
Print::Print(float x)
{
	floatData.push_back(x);
}

int Print::getIntPrintSize()
{
	return intData.size();
}
int Print::getFloatPrintSie()
{
	return floatData.size();
}