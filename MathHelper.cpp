#include "MathHelper.h"

int MathHelper::CantorPair(int in_X, int in_Y)
{
	int retVal = (((in_X + in_Y) * (in_X + in_Y + 1)) / 2) + in_Y;
	return retVal;
}

void MathHelper::CantorPairReverse(int in_Cantor, int& in_X, int& in_Y)
{
	int t = static_cast<int>(std::floor((-1 + std::sqrt(1 + 8 * in_Cantor)) / 2));
	in_X = t * (t + 3) / 2 - in_Cantor;
	in_Y = in_Cantor - t * (t + 1) / 2;
}
