#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "Point.h"

typedef struct CanonicalVolume
{
	double uMin;
	double uMax;
	double vMin;
	double vMax;
	double zMin;  // Front place
	double zMax;  //  Back clipping plane
} CanonicalVolume;

typedef struct VRC
{
	Point vpn;   // Normalized vector
	Point prp;   // expressed in VRC coordinates
	Point vup;   // Normalized vector
	Point vrp;   // Expressed in global coordinates
} VRC;

#endif