#include "Vector.h"

// Scalar multiplied by a vector:
CF32Vector operator*( f32 fLhs, const CF32Vector& krRhs )
{
	return( krRhs * fLhs );
}
