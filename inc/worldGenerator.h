#ifndef worldGenerator_H
#define worldGenerator_H

#include <iostream>
#include "PerlinNoise.h"
#include "perlin.h"
class worldGenerator
{

	private:
		int m_seed;
		int m_high;
		Perlin* noiseGen;
		Perlin* noiseColor;
		Perlin* noiseTree;
	
	public:
	worldGenerator(double p_frequency, double p_high, int p_octaves, int p_seed);
	double getNoiseHeight(int p_x, int p_z, int p_y);
	double getNoiseColor(int p_x, int p_z);
	double getTreeMap(int p_x, int p_z);


};
#endif






