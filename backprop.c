#include "common.h"
#include "backprop.h"
#include "layer.h"
#include "neuron.h"


//TODO: Put these in Network Structure 
layer *lay = NULL;
int num_layers;
int *num_neurons;
float alpha =0.1;
float *cost;
float full_cost;
float **input;
float **desired_outputs;
int num_training_ex;
int n=1;
//int extra =0;

int main(void)
{
		
		int i;


		printf("Enter the number of Layers in Neural Network:\n");
		scanf("%d",&num_layers);

		num_neurons = (int*) malloc(num_layers * sizeof(int));
		memset(num_neurons,0,num_layers *sizeof(int));

		// Get number of neurons per layer
		for(i=0;i<num_layers;i++)
		{
			printf("Enter number of neurons in layer[%d]: \n",i+1);
			scanf("%d",&num_neurons[i]);
		}

		printf("\n");

		// Initialize the neural network module
		if(init()!= SUCCESS_INIT)
		{
			printf("Error in Initialization...\n");
			exit(0);
		}

		printf("Enter the number of training examples: \n");
		scanf("%d",&num_training_ex);

		input = (float**) malloc(num_training_ex * sizeof(float*));
		for(i=0;i<num_training_ex;i++)
		{
			input[i] = (float*)malloc(num_neurons[0] * sizeof(float));
		}

		desired_outputs = (float**) malloc(num_training_ex* sizeof(float*));
		for(i=0;i<num_training_ex;i++)
		{
			desired_outputs[i] = (float*)malloc(num_neurons[num_layers-1] * sizeof(float));
		}

		cost = (float *) malloc(num_neurons[num_layers-1] * sizeof(float));
		memset(cost,0,num_neurons[num_layers-1]*sizeof(float));

		get_inputs();

		get_desired_outputs();
		
//	printf("Enter the learning rate: \n");
//	scanf("%f",&alpha);

		train_neural_net();

		if(dinit()!= SUCCESS_DINIT)
		{
			printf("Error in Dinitialization...\n");
		}
		

		return 0;
}


int init()
{
		if(create_architecture() != SUCCESS_CREATE_ARCHITECTURE)
		{
			printf("Error in creating architecture...\n");
			return ERR_INIT;
		}

		return SUCCESS_INIT;
}


//Get Inputs
void  get_inputs()
{
	int i,j;

		for(i=0;i<num_training_ex;i++)
		{
			printf("Enter the Input Activations for training example[%d]:\n",i);

			for(j=0;j<num_neurons[0];j++)
			{
				scanf("%f",&input[i][j]);
				
			}

		}
}


//Get Desired Outputs
void get_desired_outputs()
{
		int i,j;
		
		for(i=0;i<num_training_ex;i++)
		{
			for(j=0;j<num_neurons[num_layers-1];j++)
			{
				printf("Enter the desired outputs for training example[%d]...\n",i);
				scanf("%f",&desired_outputs[i][j]);
				printf("You entered: %f \n",desired_outputs[i][j]);
			}
		}
}


int feed_input(int i)
{
	int j;

	for(j=0;j<num_neurons[0];j++)
	{
		lay[0].neu[j].actv = input[i][j];
		printf("Activation: %f\n",lay[0].neu[j].actv);
	}

//	extra = extra +2;

	return 1;

}



int create_architecture()
{
		int i=0,j=0;
		lay = (layer*) malloc(num_layers * sizeof(layer));
 
		for(i=0;i<num_layers;i++)
		{
			lay[i] = create_layer(num_neurons[i]);		
			lay[i].lid = i+1;
			lay[i].num_neu = num_neurons[i];
			printf("lid: %d\n", lay[i].lid);
			printf("num_neu: %d\n\n", lay[i].num_neu);

			for(j=0;j<num_neurons[i];j++)
			{
				if(i > 0 && i < (num_layers-1)) 
				{
					lay[i].neu[j] = create_neuron(num_neurons[i-1],num_neurons[i+1]);
				}

				else if(i == 0)
				{
					lay[i].neu[j] = create_neuron(0,num_neurons[i+1]);
				}

				else if(i == (num_layers-1))
				{
					lay[i].neu[j]  = create_neuron(num_neurons[i-1],0);
				}

				lay[i].neu[j].nid = j+1;
				printf("Neuron %d in Layer %d created\n",lay[i].neu[j].nid,lay[i].lid);	
			}
		}

		printf("\n\n\n\n");

		#ifndef TESTCODE
		// Initialize the weights
		if(initialize_weights() != SUCCESS_INIT_WEIGHTS)
		{
			printf("Error Initilizing weights...\n");
			return ERR_CREATE_ARCHITECTURE;
		}

		#endif

		#ifdef TESTCODE
		initialize_dummy_weights();
		#endif

		return SUCCESS_CREATE_ARCHITECTURE;
}


int initialize_weights(void)
{
		int i,j,k;

		if(lay == NULL)
		{
			printf("No layers in Neural Network...\n");
			return ERR_INIT_WEIGHTS;
		}

		printf("Initializing weights...\n");

		for(i=0;i<num_layers-1;i++)
		{
			
			for(j=0;j<num_neurons[i];j++)
			{
				for(k=0;k<num_neurons[i+1];k++)
				{
					// Initialize Output Weights
						lay[i].neu[j].out_weights[k] = (double)rand() / (double)RAND_MAX;
					//printf("O: Neuron: %d in Layer: %d\n",lay[i].neu[j].nid,lay[i].lid);
						printf("w[%d][%d]: %f\n",i,j, lay[i].neu[j].out_weights[k]);
						lay[i].neu[j].dw[k] = 0.0; //**********************************************************
					 	printf("dw[%d][%d]: %f\n",i,j, lay[i].neu[j].dw[k]);

				// Initialize Input Weights for Next Layer
						lay[i+1].neu[k].in_weights[j] = lay[i].neu[j].out_weights[k];
			//			printf("I: Neuron: %d in Layer: %d\n",lay[i+1].neu[k].nid,lay[i+1].lid);
			//			printf("%f\n", lay[i+1].neu[k].in_weights[j]);

				}
			}
		}	

		return SUCCESS_INIT_WEIGHTS;
}

#ifdef TESTCODE
int initialize_dummy_weights(void)
{
		int i,j,k;

		if(lay == NULL)
		{
			printf("No layers in Neural Network...\n");
			return ERR_INIT_WEIGHTS;
		}

		printf("Initializing weights...\n");


		lay[0].neu[0].out_weights[0] = 0.15;
		lay[0].neu[0].out_weights[1] = 0.20;
		lay[0].neu[1].out_weights[0] = 0.25;
		lay[0].neu[1].out_weights[1] = 0.30;
		lay[1].neu[0].out_weights[0] = 0.40;
		lay[1].neu[0].out_weights[1] = 0.45;
		lay[1].neu[1].out_weights[0] = 0.50;
		lay[1].neu[1].out_weights[1] = 0.55;

		lay[1].neu[0].bias = 0.35;
		lay[1].neu[1].bias = 0.35;
		lay[2].neu[0].bias = 0.60;
		lay[2].neu[1].bias = 0.60;
		

		for(i=0;i<num_layers-1;i++)
		{
			
			for(j=0;j<num_neurons[i];j++)
			{
				for(k=0;k<num_neurons[i+1];k++)
				{
			//	printf("O: Neuron: %d in Layer: %d\n",lay[i].neu[j].nid,lay[i].lid);
					printf("w[%d][%d]: %f\n",i,j, lay[i].neu[j].out_weights[k]);
					lay[i].neu[j].dw[k] = 0.0; //**********************************************************
				 	printf("dw[%d][%d]: %f\n",i,j, lay[i].neu[j].dw[k]);

				// Initialize Input Weights for Next Layer
						lay[i+1].neu[k].in_weights[j] = lay[i].neu[j].out_weights[k];
			//			printf("I: Neuron: %d in Layer: %d\n",lay[i+1].neu[k].nid,lay[i+1].lid);
			//			printf("%f\n", lay[i+1].neu[k].in_weights[j]);

				}
			}
		}	

		return SUCCESS_INIT_WEIGHTS;
}
#endif


void train_neural_net(void)
{
	int i;
	int it=0;

	// Gradient Descent
	for(i=0;i<num_training_ex;i++)
	{
		for(it=0;it<1000;it++)
		{
			feed_input(i);
			forward_prop();
			compute_cost(i);
			back_prop(i);
			update_weights();
		}
		it = 0;
	}


	// Test the trained network
	printf("\n\n\nTesting1:\n\n");
	lay[0].neu[0].actv = 0;
	printf("Activation: %f\n",lay[0].neu[0].actv);
	lay[0].neu[1].actv = 1;
	printf("Activation: %f\n",lay[0].neu[1].actv);

	forward_prop();

	printf("\n\n\nTesting2:\n\n");
	lay[0].neu[0].actv = 1;
	printf("Activation: %f\n",lay[0].neu[0].actv);
	lay[0].neu[1].actv = 1;
	printf("Activation: %f\n",lay[0].neu[1].actv);

	forward_prop();
		
}



void update_weights(void)
{
		int i,j,k;

		printf("\n\nUpdating weights...\n");

		for(i=0;i<num_layers-1;i++)
		{
			for(j=0;j<num_neurons[i];j++)
			{
				for(k=0;k<num_neurons[i+1];k++)
				{
					// Update Output Weights
					printf("my dw[%d][%d]: %f\n",i,j, lay[i].neu[j].dw[k]);
					printf("Adding to weight[%d][%d]: %f\n",i,j,lay[i].neu[j].out_weights[k]);
					lay[i].neu[j].out_weights[k] = (lay[i].neu[j].out_weights[k])- (alpha * lay[i].neu[j].dw[k]);
					printf("O: Neuron: %d in Layer: %d\n",lay[i].neu[j].nid,lay[i].lid);
					printf("%f\n", lay[i].neu[j].out_weights[k]);

				// 	Update Input Weights for Next Layer
					lay[i+1].neu[k].in_weights[j] = lay[i].neu[j].out_weights[k];
		//				printf("I: Neuron: %d in Layer: %d\n",lay[i+1].neu[k].nid,lay[i+1].lid);
	//					printf("%f\n", lay[i+1].neu[k].in_weights[j]);

				}
				
			//	lay[i].neu[j].bias = lay[i].neu[j].bias - alpha * lay[i].neu[j].db;
			}
		}	
}


void forward_prop(void)
{
		int i,j,k;

		// Clear previous values
		for(i=1;i<num_layers;i++)
		{	
			for(j=0;j<num_neurons[i];j++)
			{
				lay[i].neu[j].z = 0;
				lay[i].neu[j].dz = 0;
				lay[i].neu[j].actv = 0;
				lay[i].neu[j].dactv = 0;
			}
		}

		for(i=1;i<num_layers;i++)
		{	
			for(j=0;j<num_neurons[i];j++)
			{
				for(k=0;k<num_neurons[i-1];k++)
				{
			//		lay[i].neu[j].z  = lay[i].neu[j].z + ((lay[i-1].neu[k].out_weights[j])* (lay[i-1].neu[k].actv));

					lay[i].neu[j].z = lay[i].neu[j].z + ((lay[i].neu[j].in_weights[k]) * (lay[i-1].neu[k].actv));
				}

				// Add Bias:
				lay[i].neu[j].z = lay[i].neu[j].z + lay[i].neu[j].bias;
				printf("z: %f\n", lay[i].neu[j].z);

				// Relu Activation Function for Hidden Layers
				if(i < num_layers-1)
				{
					if((lay[i].neu[j].z) < 0)
					{
						lay[i].neu[j].actv = 0;
					}

					else
					{
						lay[i].neu[j].actv = lay[i].neu[j].z;
					}
					printf("actv: %f\n", lay[i].neu[j].actv);
				}
				
				// Sigmoid Activation function for Output Layer
				else
				{
					lay[i].neu[j].actv = 1/(1+(exp(-lay[i].neu[j].z)));
					printf("OUTPUT: %f\n", lay[i].neu[j].actv);
				}

			  
			}

		}
}



void compute_cost(int i)
{
		int j;
		float tmpcost=0;
		float tcost=0;
	
		for(j=0;j<num_neurons[num_layers-1];j++)
		{
		//	printf("dop: %f\n", desired_outputs[i]);
		//	printf("act: %f\n", lay[num_layers-1].neu[i].actv);
		//	cost1 = log(lay[num_layers-1].neu[i].actv);
			
		//	printf("cost1: %f\n",cost1);
			tmpcost = desired_outputs[i][j] - lay[num_layers-1].neu[j].actv;
		//	cost[j] = ((desired_outputs[i][j]-1) * log(1-lay[num_layers-1].neu[j].actv)) - ((desired_outputs[i][j]) * log(lay[num_layers-1].neu[j].actv));
			cost[j] = (tmpcost * tmpcost)/2;
			tcost = tcost + cost[j];
			printf("tmpcost[%d]: %f\n",j,tmpcost);
			printf("Cost[%d]: %f\n",j, cost[j]);
		}	

		full_cost = (full_cost + tcost)/n;
		n++;

	//	printf("Full Cost for training example (%d): %f\n",i,full_cost);

}



void back_prop(int p)
{
		int i,j,k;


		// Sigmoid for Final Layer
		for(j=0;j<num_neurons[num_layers-1];j++)
		{
			
	//		lay[num_layers-1].neu[j].dactv = (desired_outputs[p][j] -1)/(lay[num_layers-1].neu[j].actv -1) - (desired_outputs[p][j]/lay[num_layers-1].neu[j].actv);
			lay[num_layers-1].neu[j].dz = (lay[num_layers-1].neu[j].actv - desired_outputs[p][j]) * (lay[num_layers-1].neu[j].actv) * (1- lay[num_layers-1].neu[j].actv);
	//		printf("dactv of lay[%d]: %f\n",num_layers-1, lay[num_layers-1].neu[j].dactv);
			printf("dz[%d][%d]: %f\n",num_layers-1,j, lay[num_layers-1].neu[j].dz);

			for(k=0;k<num_neurons[num_layers-2];k++)
			{
				if(lay[num_layers-2].neu[k].out_weights[j]==lay[num_layers-1].neu[j].in_weights[k])
				{	
					lay[num_layers-2].neu[k].dw[j] = (lay[num_layers-1].neu[j].dz * lay[num_layers-2].neu[k].actv);
					printf("outer dw[%d][%d]: %f\n",num_layers-2,j, lay[num_layers-2].neu[k].dw[j]);
				}
				lay[num_layers-2].neu[k].dactv = lay[num_layers-2].neu[k].dactv + lay[num_layers-2].neu[k].out_weights[j] * lay[num_layers-1].neu[j].dz;
		//	printf("dactv of lay[%d]: %f\n",num_layers-2, lay[num_layers-2].neu[k].dactv);
			}

				lay[num_layers-1].neu[j].db = lay[num_layers-1].neu[j].dz;
	//		printf("db[%d][%d]: %f\n",num_layers-1,j, lay[num_layers-1].neu[j].db);
			
		}

		//Relu for Hidden Layer
		for(i=num_layers-2;i>0;i--)
		{
			for(j=0;j<num_neurons[i];j++)
			{

				// Relu for Hidden Layers
				if(lay[i].neu[j].z >= 0)
				{
					lay[i].neu[j].dz = lay[i].neu[j].dactv;
				}

				else
				{
					lay[i].neu[j].dz = 0;
				}
/*
				// For Sigmoid
				lay[i].neu[j].dz = lay[i].neu[j].dactv * lay[i].neu[j].actv * (1- lay[i].neu[j].actv);

*/

				printf("dz[%d][%d]: %f\n",i,j, lay[i].neu[j].dz);

				for(k=0;k<num_neurons[i-1];k++)
				{
					if(lay[i-1].neu[k].out_weights[j]==lay[i].neu[j].in_weights[k])
					{
						lay[i-1].neu[k].dw[j] = lay[i].neu[j].dz * lay[i-1].neu[k].actv;
						printf("inner dw[%d][%d]: %f\n",i-1,j, lay[i-1].neu[k].dw[j]);
					}
					
					if(i>1)
					{
						lay[i-1].neu[k].dactv = lay[i-1].neu[k].dactv + lay[i-1].neu[k].out_weights[j] * lay[i].neu[j].dz;
//							printf("dactv of lay[%d]: %f\n",i-1, lay[i-1].neu[k].dactv);						
					}
					
				}

				lay[i].neu[j].db = lay[i].neu[j].dz;
//				printf("db[%d][%d]: %f\n",i,j, lay[i].neu[j].db);
			}
		}
}



//void activation_functions

int dinit(void)
{
		// TODO:
		// Free up all the structures

		return SUCCESS_DINIT;
}