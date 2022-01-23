#ifndef NEURON_H
#define NEURON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<time.h>

typedef struct neuron_t
{
	float actv;
	float *out_weights;
	float bias;
	float z;

	float dactv;
	float *dw;
	float dbias;
	float dz;

	// TODO: Add function pointer for destructor

} neuron;

neuron create_neuron(int num_out_weights);

#endif