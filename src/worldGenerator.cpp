#include "../inc/worldGenerator.h"

worldGenerator::worldGenerator(double p_frequency, double p_high, int p_octaves, int p_seed) 
{
	noiseGen = new Perlin(p_octaves, p_frequency, p_high, p_seed);
	noiseColor = new Perlin(13, 0.07, 32, p_seed);
	noiseTree = new Perlin(1, 0.01, 32, p_seed);
	noiseCaves = new Perlin(1, 0.04, 32 , p_seed);

	m_high = p_high;
	m_seed = p_seed;
}

double worldGenerator::getNoiseHeight(int p_x, int p_z, int p_y) {
	return noiseGen->Get3(p_x,p_y, p_z);
}

double worldGenerator::getNoiseColor(int p_x, int p_z) {
	return noiseColor->Get2(p_x, p_z);
}
double worldGenerator::getTreeMap(int p_x, int p_z) {
	return noiseTree->Get2(p_x, p_z);
}
double worldGenerator::getCavesMap(int p_x, int p_z,  int p_y) {
	return noiseCaves->Get3(p_x, p_y, p_z);
}
