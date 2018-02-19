#include "common.h"
#include "neuron.h"


neuron create_neuron(int num_in_weights,int num_out_weights)
{
	neuron neu;

	neu.nid = -1;
	neu.actv = 0.0;
	neu.in_weights = (float*) malloc(num_in_weights * sizeof(float));
// TODO: memset
	neu.out_weights = (float*) malloc(num_out_weights * sizeof(float));
	neu.bias=0.0;
	neu.z = 0.0;

	neu.dactv = 0.0;
	neu.dw = (float*) malloc(num_out_weights * sizeof(float));
	neu.idw = (float*) malloc(num_out_weights * sizeof(float));
	neu.db = 0.0;
	neu.dz = 0.0;

	return neu;

}

// TODO:
// Add destructor