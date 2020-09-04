#include "King.h"
King::King()
{
	image.Load("Resources\\King.jpg");
}

King::~King()
{
	image.Destroy();
}