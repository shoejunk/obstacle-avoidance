#include "Vector2.h"

// Scalar multiplied by a vector:
CF32Vector2 operator*( f32 fLhs, const CF32Vector2& krRhs )
{
	return( krRhs * fLhs );
}
