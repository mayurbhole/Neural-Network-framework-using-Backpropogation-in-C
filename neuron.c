#include "neuron.h"


neuron create_neuron(int num_out_weights)
{
	neuron neu;

	neu.actv = 0.0;
	neu.out_weights = (float*) malloc(num_out_weights * sizeof(float));
	neu.bias=0.0;
	neu.z = 0.0;

	neu.dactv = 0.0;
	neu.dw = (float*) malloc(num_out_weights * sizeof(float));
	neu.dbias = 0.0;
	neu.dz = 0.0;

	return neu;
}

// TODO:
// Add destructor