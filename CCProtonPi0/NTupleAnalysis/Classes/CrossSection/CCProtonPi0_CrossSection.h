/*
 * =============================================================================
 * Class: CCProtonPi0_CrossSection
 *   CCProtonPi0_CrossSection Class contains ALL required methods to calculate
 *       Cross Section for CCProtonPi0 Analysis
 *  
 *   Uses ROOT and MINERvA Specific classes
 *   
 *   Author: Ozgur Altinok  - ozgur.altinok@tufts.edu
 * =============================================================================
 */
#ifndef CCProtonPi0_CrossSection_h
#define CCProtonPi0_CrossSection_h

// Classes
#include "../NTupleAnalysis/CCProtonPi0_NTupleAnalysis.h"
#include "../BinList/CCProtonPi0_BinList.h"
#include "TObjArray.h"
#include "TFractionFitter.h"
#include <MinervaUnfold/MnvUnfold.h>
#include <PlotUtils/TargetUtils.h>

using namespace PlotUtils;

struct XSec
{
    std::string name;
    bool isEv;
    bool isDeltaRich;
    
    // Style
    std::string plot_title;
    std::string plot_xlabel;
    std::string plot_ylabel;

    double smallest_bin_width;
    int nIterations;

    // ROOT Files
    TFile* f_data;
    TFile* f_mc;

    // Data Histograms
    MnvH1D* all;
    MnvH1D* bckg_subtracted;
    MnvH1D* bckg_estimated;
    MnvH1D* unfolded;
    MnvH1D* efficiency_corrected;
    MnvH1D* flux_integrated;
    MnvH1D* xsec;

    // MC Truth Histograms 
    MnvH1D* mc_truth_all_signal;
    MnvH1D* mc_truth_signal;
    MnvH1D* mc_reco_signal;
    MnvH1D* mc_reco_bckg;
    MnvH2D* response;
    MnvH1D* eff;

    // MC Truth AfterFSI 
    MnvH1D* efficiency_corrected_AfterFSI;
    MnvH1D* flux_integrated_AfterFSI;
    MnvH1D* xsec_AfterFSI;

    // MC Truth BeforeFSI
    MnvH1D* efficiency_corrected_BeforeFSI;
    MnvH1D* flux_integrated_BeforeFSI;
    MnvH1D* xsec_BeforeFSI;
    
    // MC Truth FSI Type
    std::vector<MnvH1D*> efficiency_corrected_FSIType;
    std::vector<MnvH1D*> flux_integrated_FSIType;
    std::vector<MnvH1D*> xsec_FSIType;

    // MC Truth Int Type
    std::vector<MnvH1D*> efficiency_corrected_IntType;
    std::vector<MnvH1D*> flux_integrated_IntType;
    std::vector<MnvH1D*> xsec_IntType;
};

class CCProtonPi0_CrossSection : public CCProtonPi0_NTupleAnalysis
{
    public:
        CCProtonPi0_CrossSection(bool isMC);
        void Calc_CrossSections();
    
    private:
        CCProtonPi0_BinList binList;

        bool m_isMC;
        double min_invMass;
        double max_invMass;
        std::vector<double> N_Background_Data;
        std::vector<double> N_Background_Data_DeltaRich;

        // Flux File
        MnvH1D* h_flux_minervaLE_FHC;
        MnvH1D* h_flux_rebinned;
        MnvH1D* h_flux_rebinned_BeforeFSI;
        double cv_flux_integral;
        std::vector<double> unv_flux_integral;

        //NuWro Predictions
        MnvH1D* NuWro_muon_P;
        MnvH1D* NuWro_muon_theta;
        MnvH1D* NuWro_pi0_KE;
        MnvH1D* NuWro_pi0_theta;
        MnvH1D* NuWro_QSq;
        MnvH1D* NuWro_W;
        MnvH1D* NuWro_Enu;
        MnvH1D* NuWro_deltaInvMass;
        MnvH1D* NuWro_Delta_pi_theta;
        MnvH1D* NuWro_Delta_pi_phi;

        // Pi0 Invariant Mass
        MnvH1D* invMass_all;
        MnvH1D* invMass_mc_reco_signal;
        MnvH1D* invMass_mc_reco_bckg;

        XSec muon_P;
        XSec muon_theta;
        XSec pi0_P;
        XSec pi0_KE;
        XSec pi0_theta;
        XSec QSq;
        XSec W;
        XSec Enu;
        XSec deltaInvMass;
        XSec Delta_pi_theta;
        XSec Delta_pi_phi;
        
        // Output Text File
        std::string text_out_name;
        ofstream text_out;

        // ROOT Files    
        TFile* f_out;
        TFile* f_truth;
        TFile* f_data_cutHists;
        TFile* f_mc_cutHists;
        
        std::string rootDir_out;
        
        // Functions
        void IntegrateAllFluxUniverses();
        void AddErrorBands_FluxHistogram();
        void RebinFluxHistogram();
        void RebinFluxHistogram(TH1* rebinned, TH1* reference);
        void RebinFluxHistogram_BeforeFSI(TH1* rebinned, TH1* reference);
        void Calc_CrossSection(XSec &var);
        void Calc_CrossSection_AfterFSI(XSec &var);
        void Calc_CrossSection_BeforeFSI(XSec &var);
        void Calc_CrossSection_FSIType(XSec &var);
        void Calc_CrossSection_IntType(XSec &var);
        void AddLabels_XSecHist(XSec &var);
        void Scale_XSecHist(MnvH1D* xsec_hist, double smallest_bin_width);
        void Calc_Normalized_NBackground();
        void NormalizeHistogram(TH1D* h);
        void NormalizeHistogram(MnvH1D* h);
        double GetFluxHistContent(TH1* hist, double low1, double low2);
        double GetSmallestBinWidth(MnvH1D* hist);
        void OpenRootFiles();
        void writeHistograms();
        void writeHistograms(XSec &var);
        void initHistograms();
        void initHistograms(XSec &var);
        void initHistograms_NuWro();
        void fillHistograms_NuWro();
        void initFluxHistograms();
        void initXSecs();
        void init_muon_P();
        void init_muon_theta();
        void init_pi0_P();
        void init_pi0_KE();
        void init_pi0_theta();
        void init_W();
        void init_QSq();
        void init_Enu();
        void init_deltaInvMass();
        void init_Delta_pi_theta();
        void init_Delta_pi_phi();
        MnvH1D* Subtract_Background(MnvH1D* data, MnvH1D* mc_bckg, MnvH1D* &bckg_estimated, std::string var_name);
        MnvH1D* Unfold_Data(MnvH1D* bckg_subtracted, MnvH2D* response, std::string var_name, int nIter);
        MnvH1D* Efficiency_Divide(MnvH1D* unfolded, MnvH1D* eff, std::string var_name);
        MnvH1D* Integrate_Flux(MnvH1D* data_efficiency_corrected, std::string var_name, std::string hist_name);
        MnvH1D* Calc_FinalCrossSection(MnvH1D* flux_integrated, std::string var_name, std::string hist_name);
};


#endif


