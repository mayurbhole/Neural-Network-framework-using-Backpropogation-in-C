#include "common.h"
#include "layer.h"


layer create_layer(int number_of_neurons)
{
		layer lay;

		lay.lid = -1;
		lay.num_neu = -1;
	  lay.neu = (struct neuron_t *) malloc(number_of_neurons * sizeof(struct neuron_t));
	//	lay->next_lay = NULL;


		return lay;

}

// TODO:
// Add destructor
