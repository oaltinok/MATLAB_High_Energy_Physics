/*
================================================================================
Class: Muon -> Derived Class from Particle Base Clas
    Muon Class  inherits Particle Behaviours and 
                extends base class with muon specific parameters
                
    Author:         Ozgur Altinok  - ozgur.altinok@tufts.edu
    Last Revision: 2014_11_12
================================================================================
*/

#ifndef Muon_h
#define Muon_h

#include "../Particle/Particle.h"

class Muon : public Particle
{
    public:
        Muon();
        void initialize(int nMode);
        bool get_isMinosMatched();
        void set_isMinosMatched(bool input);
        void set_angleMuon(Particle &mu, bool isMC);
        void set_kineticEnergy(bool isMC);

        
    private:
        static const double restMass = 105.66;
        bool isMinosMatched;
        SingleBin bin_AngleBeam;
        
};

#endif