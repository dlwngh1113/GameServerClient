#include "Pawn.h"
Pawn::Pawn()
{
	image.Load("Resources\pawn.png");
}

Pawn::~Pawn()
{
	image.Destroy();
}