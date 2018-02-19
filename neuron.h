#ifndef NEURON_H
#define NEURON_H



typedef struct neuron_t
{
	  int nid;
	  float actv;
	  float *out_weights;
	  float *in_weights;
	 	float bias;
	  float z;

	  float dactv;
	  float *dw;
	  float *idw;
	  float db;
	  float dz;

	  // TODO: Add function pointer for destructor

} neuron;

neuron create_neuron(int num_in_weights,int num_out_weights);

#endif