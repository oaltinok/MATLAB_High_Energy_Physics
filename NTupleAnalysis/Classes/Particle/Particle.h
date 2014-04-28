/*
================================================================================
Class: Particle
    Particle Class defines a particle which will be used in the analysis
    Contains analysis specific information such as 4-Momentum and Angle wrt Beam
   
    Uses ROOT Specific classes
    
    Last Revision: 2014_04_16
================================================================================
*/

#ifndef PARTICLE_H
#define PARTICLE_H

#include <TMath.h>
#include <TH1.h>
#include <TH2.h>

#include "Classes/BinList/BinList.cpp"
#include "Libraries/Folder_List.h"


class Particle
{
    public:
        // Two Data Data Types
        // type = 0 -- Reco -- Reconstructed 
        // type = 1 -- True -- Monte Carlo
        // type = 2 -- Error -- (True - Reco) / True
        static const int N_DATA_TYPE = 3;
        
        // Monte Carlo(MC) and Reconstructed(Reco)
        TLorentzVector p4[N_DATA_TYPE];     // 4-Momentum of the Particle (Px,Py,Pz,E)
        double momentum[N_DATA_TYPE];       // 3 Momentum of the Particle (P)
        double kineticEnergy[N_DATA_TYPE];  // Kinetic energy of the Particle
        double angleBeam[N_DATA_TYPE];      // Angle wrt Beam in rads
        double angleMuon[N_DATA_TYPE];      // Angle wrt Muon in rads
        
        // MC Only
        int ind;                // indice for MC truth information (mc_FSPart)
        
        // Reco Only
        double particleScore;       // Particle Score from Reconstructed Values
        double trackLength;         // Track Length in [mm]
        
        TFile* f;
        
        // Histograms
        TH1F* partScore;
        
        TH1F* P_mc;
        TH1F* P_reco;
        TH1F* P_error;
        TH2F* P_reco_mc;
        
        TH1F* KE_mc;
        TH1F* KE_reco;
        TH1F* KE_error;
        TH2F* KE_reco_mc;
        
        TH1F* angleBeam_mc;
        TH1F* angleBeam_reco;
        TH1F* angleBeam_error;
        TH2F* angleBeam_reco_mc;
        
        TH1F* angleMuon_mc;
        TH1F* angleMuon_reco;
        TH1F* angleMuon_error;
        TH2F* angleMuon_reco_mc;
        
        // Bins for Histograms
        SingleBin bin_error;
        SingleBin bin_P;
        SingleBin bin_KE;
        SingleBin bin_angle;
        SingleBin bin_partScore;
        
        
        // File Locations
        string rootDir;
        string plotDir;
        
        
        // Functions
        Particle();
        ~Particle();
        int getDataType(bool isMC); // Returns the indice of arrays reco = 0, mc = 1
        virtual void set_angleMuon(Particle &mu, bool isMC);
        virtual void set_kineticEnergy(bool isMC) = 0;
        void set_angleBeam(TVector3 beamp3, bool isMC);
        void set_p4(double px, double py, double pz, double E, bool isMC);
        void set_errors();
        void fill_Histograms();
        void write_RootFile();
        void plot_data();
        
        
        // Other
        double calc_error(double trueValue, double recoValue);
        
       
        
    
    protected:
        double restMass;
        
        

};


#endif 