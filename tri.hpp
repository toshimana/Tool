#ifndef TRI_H
#define TRI_H

#define _USE_MATH_DEFINES
#include <math.h>

namespace tri
{
	const double RAD_PER_DEG = 1.7453292519943295e-2; // RAD_PER_DEG = M_PI / 180
	const double DEG_PER_RAD = 57.29577951308232;     // DEG_PER_RAD = 180 / M_PI

	double deg2rad( double deg ){ return deg * RAD_PER_DEG; }
	double rad2deg( double rad ){ return rad * DEG_PER_RAD; }

	double sind( double deg ){ return sin( deg2rad( deg ) ); }
	double cosd( double deg ){ return cos( deg2rad( deg ) ); }
	double tand( double deg ){ return tan( deg2rad( deg ) ); }

	double asind( double val ){ return rad2deg( asin( val ) ); }
	double acosd( double val ){	return rad2deg( acos( val ) ); }
	double atand( double val ){	return rad2deg( atan( val ) ); }
};

#endif // TRI_H