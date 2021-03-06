/*
================================================================================
Namespace: Folder_List
    Folder List for easier folder management

Main Directory:
Libraries/

Usage:
> #include "Libraries/Folder_List.h" 
> PDG_List::output      // Returns default Output Directory

Author:         Ozgur Altinok  - ozgur.altinok@tufts.edu
================================================================================
*/

#ifndef Folder_List_h
#define Folder_List_h

#include <string>

namespace Folder_List
{
    //-------------------------------------------------------------------------
    // Input Files
    //-------------------------------------------------------------------------
    // Default Folder for Input
    const std::string input = "Input/";

    // Background Constraints
    const std::string BckgConstraints = input + "BckgConstraints/" + "Weights_All_Universes.txt";
    const std::string BckgConstraints_TruthAnalysis = "../" + input + "BckgConstraints/" + "Weights_All_Universes.txt";
    
    //-------------------------------------------------------------------------
    // Data files on /minerva/data/users/oaltinok/NTupleAnalysis Disk
    //-------------------------------------------------------------------------
    const std::string rootOut = "/minerva/data/users/oaltinok/NTupleAnalysis/";
    const std::string MC = "MC/";
    const std::string Data = "Data/";
    const std::string ParticleCannon = "ParticleCannon/";
    const std::string Flux = "Flux/";
    const std::string GENIEXSec = "GENIEXSec/";
    
    const std::string analyzed = "Analyzed/";
    const std::string reduced = "Reduced/"; 

    //-------------------------------------------------------------------------
    // NTuple Analysis Output
    //-------------------------------------------------------------------------
    // Default Folder for Output
    const std::string output = "Output/";
    
    // SubFolders for Output
    const std::string textOut = "TextFiles/";
    const std::string plotOut = "Plots/";
    
    // Folder Branches
    const std::string signal = "Signal/";
    const std::string background = "Background/";
    const std::string allEvents = "AllEvents/";
    const std::string other = "Other/";

    //-------------------------------------------------------------------------
    // ROOT Dirs
    //-------------------------------------------------------------------------
    // Set Truth ROOT Dir
    const std::string rootDir_Truth_mc = rootOut + MC + analyzed + "TruthHistograms.root";
    const std::string rootDir_Truth_mc_Test = rootOut + MC + analyzed + "TruthHistograms_Test.root";
    const std::string rootDir_Truth_data = "";

    // Set Other Studies ROOT Dir
    const std::string rootDir_PC_mc = "/pnfs/minerva/persistent/users/oaltinok/NTupleAnalysis/ParticleCannon/PC_Steel.root"; 
    const std::string rootDir_PC_data = "/pnfs/minerva/persistent/users/oaltinok/NTupleAnalysis/ParticleCannon/PC_Carbon.root"; 
   
    // Set Flux File ROOT Dir
    const std::string rootDir_Flux_new = rootOut + Flux + "fhc_flux_constrained.root";
    const std::string rootDir_Flux_old = rootOut + Flux + "eroica-mipp-off-flux-nuint-minerva1-minerva13C.root";
    const std::string rootDir_GENIEXSec = rootOut + GENIEXSec + "GENIEXSec.root";
   
    // Set Side Band ROOT Dirs;
    const std::string rootDir_sideBand_Original_mc = rootOut + MC + analyzed + "CutHistograms_Original.root";
    const std::string rootDir_sideBand_Original_data = rootOut + Data + analyzed + "CutHistograms_Original.root";

    const std::string rootDir_sideBand_Michel_mc = rootOut + MC + analyzed + "CutHistograms_Michel.root";
    const std::string rootDir_sideBand_Michel_data = rootOut + Data + analyzed + "CutHistograms_Michel.root";
    
    const std::string rootDir_sideBand_pID_mc = rootOut + MC + analyzed + "CutHistograms_pID.root";
    const std::string rootDir_sideBand_pID_data = rootOut + Data + analyzed + "CutHistograms_pID.root";
    
    const std::string rootDir_sideBand_LowInvMass_mc = rootOut + MC + analyzed + "CutHistograms_LowInvMass.root";
    const std::string rootDir_sideBand_LowInvMass_data = rootOut + Data + analyzed + "CutHistograms_LowInvMass.root";
     
    const std::string rootDir_sideBand_HighInvMass_mc = rootOut + MC + analyzed + "CutHistograms_HighInvMass.root";
    const std::string rootDir_sideBand_HighInvMass_data = rootOut + Data + analyzed + "CutHistograms_HighInvMass.root";
    
    // Set MC Root Dir;
    const std::string rootDir_CrossSection_mc = rootOut + MC + analyzed + "CrossSection.root";
    const std::string rootDir_CutHists_mc = rootOut + MC + analyzed + "CutHistograms.root";
    const std::string rootDir_Interaction_mc = rootOut + MC + analyzed + "Interaction.root";
    const std::string rootDir_Muon_mc = rootOut + MC + analyzed + "Muon.root";
    const std::string rootDir_Proton_mc = rootOut + MC + analyzed + "Proton.root";
    const std::string rootDir_Pion_mc = rootOut + MC + analyzed + "Pion.root";
    const std::string rootDir_Pi0Blob_mc = rootOut + MC + analyzed + "Pi0Blob.root";

    // Set Data Root Dir
    const std::string rootDir_CrossSection_data = rootOut + Data + analyzed + "CrossSection.root";
    const std::string rootDir_CutHists_data = rootOut + Data + analyzed + "CutHistograms.root";
    const std::string rootDir_Interaction_data = rootOut + Data + analyzed + "Interaction.root";
    const std::string rootDir_Muon_data = rootOut + Data + analyzed + "Muon.root";
    const std::string rootDir_Proton_data = rootOut + Data + analyzed + "Proton.root";
    const std::string rootDir_Pion_data = rootOut + Data + analyzed + "Pion.root";
    const std::string rootDir_Pi0Blob_data = rootOut + Data + analyzed + "Pi0Blob.root";

    // Unfolding Study
    const std::string rootDir_Pion_Train = rootOut + MC + analyzed + "Pion_Sample.root";
    const std::string rootDir_Pion_Sample = rootOut + MC + analyzed + "Pion_Train.root";
    const std::string rootDir_Muon_Train = rootOut + MC + analyzed + "Muon_Sample.root";
    const std::string rootDir_Muon_Sample = rootOut + MC + analyzed + "Muon_Train.root";
    
    // Results
    const std::string rootDir_Signal_Original_MC = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_Original/MC/Analyzed/CrossSection.root";
    const std::string rootDir_Signal_Original_Data = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_Original/Data/Analyzed/CrossSection.root";

    const std::string rootDir_Signal_NoWLimit_Original_MC = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_NoWLimit_Original/MC/Analyzed/CrossSection.root";
    const std::string rootDir_Signal_NoWLimit_Original_Data = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_NoWLimit_Original/Data/Analyzed/CrossSection.root";

    const std::string rootDir_Interaction_Signal_Original_MC = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_Original/MC/Analyzed/Interaction.root";
    const std::string rootDir_Interaction_Signal_Original_Data = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_Original/Data/Analyzed/Interaction.root";

    const std::string rootDir_CutHists_Signal_Original_MC = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_Original/MC/Analyzed/CutHistograms.root";
    const std::string rootDir_CutHists_Signal_Original_Data = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_Original/Data/Analyzed/CutHistograms.root";

    const std::string rootDir_Signal_DeltaRich_MC = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_DeltaRich/MC/Analyzed/CrossSection.root";
    const std::string rootDir_Signal_DeltaRich_Data = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_DeltaRich/Data/Analyzed/CrossSection.root";

    const std::string rootDir_Signal_2Bin_DeltaRich_MC = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_2Bin_DeltaRich/MC/Analyzed/CrossSection.root";
    const std::string rootDir_Signal_2Bin_DeltaRich_Data = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_2Bin_DeltaRich/Data/Analyzed/CrossSection.root";

    const std::string rootDir_Signal_TwoTrack_MC = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_TwoTrack/MC/Analyzed/CrossSection.root";
    const std::string rootDir_Signal_TwoTrack_Data = "/minerva/data/users/oaltinok/NTupleAnalysis_Signal_TwoTrack/Data/Analyzed/CrossSection.root";

    //-------------------------------------------------------------------------
    // Plot Dirs
    //-------------------------------------------------------------------------
    // CrossSection Plot Dirs
    const std::string xsec_Delta_pi_phi = output + plotOut + "xsec_Delta_pi_phi/";
    const std::string xsec_Delta_pi_theta = output + plotOut + "xsec_Delta_pi_theta/";
    const std::string xsec_deltaInvMass = output + plotOut + "xsec_deltaInvMass/";
    const std::string xsec_Enu = output + plotOut + "xsec_Enu/";
    const std::string xsec_QSq = output + plotOut + "xsec_QSq/";
    const std::string xsec_W = output + plotOut + "xsec_W/";
    const std::string xsec_muon_P = output + plotOut + "xsec_muon_P/";
    const std::string xsec_muon_theta = output + plotOut + "xsec_muon_theta/";
    const std::string xsec_pi0_P = output + plotOut + "xsec_pi0_P/";
    const std::string xsec_pi0_KE = output + plotOut + "xsec_pi0_KE/";
    const std::string xsec_pi0_theta = output + plotOut + "xsec_pi0_theta/";

    const std::string plotDir_Check = "Check/";
    const std::string plotDir_ErrorSummary = "ErrorSummary/";
    const std::string plotDir_CrossSection = "CrossSection/";
    const std::string plotDir_Original = "Original/";
    const std::string plotDir_FluxIntegrated = "FluxIntegrated/";
    const std::string plotDir_BackgroundEstimated = "BackgroundEstimated/";
    const std::string plotDir_BackgroundSubtracted = "BackgroundSubtracted/";
    const std::string plotDir_Unfolded = "Unfolded/";
    const std::string plotDir_Efficiency = "EfficiencyCorrected/";

    // Default Plot Dirs
    const std::string plotDir_Supplement = output + plotOut + "Supplement/";
    const std::string plotDir_Paper = output + plotOut + "Paper/";
    const std::string plotDir_OtherStudies = output + plotOut + "OtherStudies/";
    const std::string plotDir_Systematics = output + plotOut + "Systematics/";
    const std::string plotDir_CutHists = output + plotOut + "CutHists/";
    const std::string plotDir_Truth = output + plotOut + "Truth/";
    const std::string plotDir_Interaction = output + plotOut + "Interaction/";
    const std::string plotDir_Muon = output + plotOut + "Muon/";
    const std::string plotDir_Proton = output + plotOut + "Proton/";
    const std::string plotDir_Pion = output + plotOut + "Pion/";
    const std::string plotDir_SideBand = output + plotOut + "SideBand/";

    // Systematics Plot Dirs
    const std::string plotDir_Systematics_Summary = plotDir_Systematics + "Summary/";
    const std::string plotDir_Systematics_GENIE = plotDir_Systematics + "GENIE/";
}

#endif 
