/*
================================================================================
Class: NTupleAnalysis
    Base Class for the NTupleAnalysis Package
    Includes Common Member Variables for all Classes
        const nTopologies
        branchDir - Output Folder
        anaMode - Signal Only, Background Only or All
        
    Author:        Ozgur Altinok  - ozgur.altinok@tufts.edu
    Last Revision: 2015_04_21
================================================================================
*/

#ifndef NTupleAnalysis_h
#define NTupleAnalysis_h

#include <iostream>
#include <cstdlib>
#include <string>

#include "../../Libraries/Folder_List.h"

using namespace std;

class NTupleAnalysis
{
    public:
        NTupleAnalysis(int nMode);
        
        static const int nTopologies = 2;
        string branchDir;
        bool isAnalysisModeSelected;
        int anaMode;
        
    private:
        void SetAnalysisMode(int nMode);
};



#endif
