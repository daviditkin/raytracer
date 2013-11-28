#ifndef INTENSITY_H
#define INTENSITY_H

class Intensity
{
	public:
		float r;
		float g;
		float b;
		Intensity () : r (0), g (0), b (0) {}
		Intensity (float _r, float _g, float _b) : r (_r), g (_g), b (_b) {}
};

#endif