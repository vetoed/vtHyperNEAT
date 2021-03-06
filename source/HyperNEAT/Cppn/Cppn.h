/* Copyright (C) 2017 Wlodzimierz Samborski */

#pragma once

#include "CppnNeuron.h"
#include "CppnSynapse.h"
#include "Genotype.h"
#include "Solution.h"
#include "Substrate.h"



namespace vt {

/*
CPPN will be used to generate weights for the output network.
For the 2D representation of the network there will be:
 - 5 inputs: bias, x1, y1, x2, y2,
 - 4 outputs: weightExpression, weight, biasExpression, bias
Regular weigths:
 - from: x1, y1
 - to: x2, y2
 - if weightExpression > 0 then create link with value weight
Biases:
 - position: x1, y1
 - x2 = y2 = 0
 - if biasExpression > 0 then create bias with value bias
*/
class Cppn {
public:
    /*
    Returns the amount of links. Useful for weight cost.
    */
    int getLinksAmount();

    /*
    Sets the substrate to be used for generating connections.
    */
    void setSubstrate(
        const Substrate& substrate);

    /*
    Queries the CPPN for connection weights.
    */
    const Solution& query(
        const Genotype& genes);



private:
    /*
    Creates nodes and links from the given genotype.
    */
    void createFromGenotype(
        const Genotype& genes);

    /*
    Helper function for adding neurons from genotype.
    */
    void createNeuronIfAbsent(
        int neuronId,
        const Genotype& genes);
    
    /*
    Produces a collection of synapses for the given substrate.
    */
    void generateConnections();

    /*
    Resets neurons and fires neurons *depth* times.
    */
    void process(Float* inputs);



    //IO
    Solution output;
    Substrate substrate;

    //Neurons of the CPPN. Format: innovation number, neuron data.
    std::map<int, CppnNeuron> nodes;
    std::vector<CppnSynapse> links;

    //Fire depth-1 times.
    int depth;

    //inputs & outputs
    int numInputs = 5;
    int numOutputs = 4;
    int numIONodes = 9;
};

#include "Cppn.hpp"

}//namespace
