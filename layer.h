#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"

typedef struct layer_t
{
		int lid;
		int num_neu;
		struct neuron_t *neu;
	//	struct layer *next_lay;
 
} layer;

layer create_layer(int num_neurons);

#endif