/******************************************************************************
 *
 * Jarryd Semmens					ManagerBase						COSC2140
 *
 * Math methods not included in the default libraries
 *
 *****************************************************************************/
#pragma once

#include <cmath>

class MathHelper
{
public:
	static int CantorPair(int in_X, int in_Y);
	static void CantorPairReverse(int in_Cantor, int& in_X, int& in_Y);
};
