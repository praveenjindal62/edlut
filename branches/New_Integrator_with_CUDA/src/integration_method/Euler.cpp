/***************************************************************************
 *                           Euler.cpp                                     *
 *                           -------------------                           *
 * copyright            : (C) 2013 by Francisco Naveros                    *
 * email                : fnaveros@atc.ugr.es                              *
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "../../include/integration_method/Euler.h"
#include "../../include/neuron_model/TimeDrivenNeuronModel.h"


Euler::Euler(int N_neuronStateVariables, int N_differentialNeuronState, int N_timeDependentNeuronState, int N_CPU_thread):FixedStep("Euler",N_neuronStateVariables, N_differentialNeuronState, N_timeDependentNeuronState, N_CPU_thread, false, false){
	AuxNeuronState = new float [N_NeuronStateVariables*N_CPU_thread];
}

Euler::~Euler(){
	free (AuxNeuronState);
}
		
void Euler::NextDifferentialEcuationValue(int index, TimeDrivenNeuronModel * Model, float * NeuronState, double elapsed_time, int CPU_thread_index){
	float * offset_AuxNeuronState=AuxNeuronState+(N_NeuronStateVariables*CPU_thread_index);
	
	Model->EvaluateDifferentialEcuation(NeuronState, offset_AuxNeuronState);

	for (int j=0; j<N_DifferentialNeuronState; j++){
		NeuronState[j]+=elapsed_time*offset_AuxNeuronState[j];
	}

	Model->EvaluateTimeDependentEcuation(NeuronState, elapsed_time);
}

ostream & Euler::PrintInfo(ostream & out){
	out << "Integration Method Type: " << this->GetType() << endl;

	return out;
}	