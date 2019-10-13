// author: Yiang Lu
// Date created: 13/Oct/2019
#include "TurnBoard.h"

bool TurnBoard::IsTurnEnd()
{
	return spaceX == spaceY == (SIZE - 1) ? true : false;
}
