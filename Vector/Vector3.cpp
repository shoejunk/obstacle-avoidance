#include "Vector3.h"

// Scalar multiplied by a vector:
CF32Vector3 operator*( f32 fLhs, const CF32Vector3& krRhs )
{
	return( krRhs * fLhs );
}
