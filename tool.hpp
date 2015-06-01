#pragma once

namespace tool 
{ 
	// stackoverflow.com/questions/4229870/c-algorithm-to-calculate-least-common-multiple-for-multiple-numbers	
	static int
	gcm( int a, int b )
	{
		while( 1 )
		{
			if (a == 0) return b;
			b %= a;
			if (b == 0) return a;
			a %= b;
		}
	}

	static int
	lcm( int a, int b )
	{
		int temp = gcm(a, b);
		return temp ? (a / temp * b) : 0;
	}
};