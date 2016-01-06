/*
    See CutList.h header for Class Information
*/
#ifndef CCProtonPi0_CutList_cpp
#define CCProtonPi0_CutList_cpp

#include "CCProtonPi0_CutList.h"

using namespace PlotUtils;

CCProtonPi0_CutList::CCProtonPi0_CutList(bool isModeReduce, bool isMC) : CCProtonPi0_NTupleAnalysis()
{
    cout<<"Initializing CCProtonPi0_CutList"<<endl;
    
    if(isModeReduce){
        // File Locations
        if (isMC) rootDir = Folder_List::rootOut + Folder_List::MC + Folder_List::analyzed + "CutHistograms_" + version + ".root";
        else rootDir = Folder_List::rootOut + Folder_List::Data + Folder_List::analyzed + "CutHistograms_" + version + ".root";
        
        cout<<"\tRoot File: "<<rootDir<<endl;

        // Create Root File 
        f = new TFile(rootDir.c_str(),"RECREATE");
        if (!f->IsOpen()){
            cout<<"File already exists! Exiting!..."<<endl;
            exit(1);
        }
        
        nTrueSignal = 240237;
        SetCutNames();
        OpenTextFiles(isMC);
        
        initHistograms();
    }else{
        cout<<"\tNTuple Analysis Mode -- Will not create ROOT & Text Files"<<endl;
    }

    cout<<"Done!"<<endl;
}

/*
 *  Histograms
 *      See Following Page for Histogram Indices
 *          https://cdcvs.fnal.gov/redmine/projects/minerva/wiki/Ozgur's_scratch_page
 * */
void CCProtonPi0_CutList::initHistograms()
{
    MnvH1D* temp = NULL;

    for (int i = 0; i < nHistograms; i++){
        // --------------------------------------------------------------------
        // Common
        // --------------------------------------------------------------------
        temp = new MnvH1D( Form("%s_%d","hCut_nVertices",i),Form("%d",i),binList.multiplicity.get_nBins(), binList.multiplicity.get_min(), binList.multiplicity.get_max() );
        temp->GetXaxis()->SetTitle("N(Vertex)");
        temp->GetYaxis()->SetTitle("N(Events)");
        hCut_nVertices.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_nTracks",i),Form("%d",i),binList.multiplicity.get_nBins(), binList.multiplicity.get_min(), binList.multiplicity.get_max() );
        temp->GetXaxis()->SetTitle("N(Tracks)");
        temp->GetYaxis()->SetTitle("N(Events)");
        hCut_nTracks.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_nTracks2",i),Form("%d",i),binList.multiplicity.get_nBins(), binList.multiplicity.get_min(), binList.multiplicity.get_max() );
        temp->GetXaxis()->SetTitle("N(Tracks_Close) + N(Tracks_Far) - should be same with nTracks");
        temp->GetYaxis()->SetTitle("N(Events)");
        hCut_nTracks2.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_nTracks_Close",i),Form("%d",i),binList.multiplicity.get_nBins(), binList.multiplicity.get_min(), binList.multiplicity.get_max() );
        temp->GetXaxis()->SetTitle("N(Tracks_Close)");
        temp->GetYaxis()->SetTitle("N(Events)");
        hCut_nTracks_Close.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_nTracks_Far",i),Form("%d",i),binList.multiplicity.get_nBins(), binList.multiplicity.get_min(), binList.multiplicity.get_max() );
        temp->GetXaxis()->SetTitle("N(Tracks_Far)");
        temp->GetYaxis()->SetTitle("N(Events)");
        hCut_nTracks_Far.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_nTracks_Discarded",i),Form("%d",i),binList.multiplicity.get_nBins(), binList.multiplicity.get_min(), binList.multiplicity.get_max() );
        temp->GetXaxis()->SetTitle("N(Tracks_Discarded)");
        temp->GetYaxis()->SetTitle("N(Events)");
        hCut_nTracks_Discarded.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_Michel",i),Form("%d",i),binList.true_false.get_nBins(), binList.true_false.get_min(), binList.true_false.get_max() );
        temp->GetXaxis()->SetTitle("0 = No Michel, 1 = Michel");
        temp->GetYaxis()->SetTitle("N(Events)");
        hCut_Michel.push_back(temp);

        // --------------------------------------------------------------------
        // 1 Track
        // --------------------------------------------------------------------

        temp = new MnvH1D( Form("%s_%d","hCut_1Track_eVis_nuclearTarget",i),"Visible Energy in Nuclear Target",binList.eVis_nuclearTarget.get_nBins(), binList.eVis_nuclearTarget.get_min(), binList.eVis_nuclearTarget.get_max() );
        temp->GetXaxis()->SetTitle("Visible Energy in Nuclear Target [MeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f ",binList.eVis_nuclearTarget.get_width()));
        hCut_1Track_eVis_nuclearTarget.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_1Track_eVis_other",i),"Visible Energy in Tracker + ECAL + HCAL",binList.eVis_other.get_nBins(), binList.eVis_other.get_min(), binList.eVis_other.get_max() );
        temp->GetXaxis()->SetTitle("Visible Energy in Tracker + ECAL + HCAL [MeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f ",binList.eVis_other.get_width()));
        hCut_1Track_eVis_other.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_1Track_gamma1ConvDist",i),"Leading Photon Conversion Distance",binList.bin_photonConvLength.get_nBins(), binList.bin_photonConvLength.get_min(), binList.bin_photonConvLength.get_max() );
        temp->GetXaxis()->SetTitle("Leading Photon Conversion Distance");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f [cm]",binList.bin_photonConvLength.get_width()));
        hCut_1Track_gamma1ConvDist.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_1Track_gamma2ConvDist",i),"Second Photon Conversion Distance",binList.bin_photonConvLength.get_nBins(), binList.bin_photonConvLength.get_min(), binList.bin_photonConvLength.get_max() );
        temp->GetXaxis()->SetTitle("Second Photon Conversion Distance");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f [cm]",binList.bin_photonConvLength.get_width()));
        hCut_1Track_gamma2ConvDist.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_1Track_pi0invMass",i),"Reconstructed Pi0 Invariant Mass",binList.pi0_invMass.get_nBins(), binList.pi0_invMass.get_min(), binList.pi0_invMass.get_max() );
        temp->GetXaxis()->SetTitle("Reconstructed Pi0 Invariant Mass [MeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f [MeV]",binList.pi0_invMass.get_width()));
        hCut_1Track_pi0invMass.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_1Track_pi0invMass_1",i),"Reconstructed Pi0 Invariant Mass New 1",binList.pi0_invMass.get_nBins(), binList.pi0_invMass.get_min(), binList.pi0_invMass.get_max() );
        temp->GetXaxis()->SetTitle("Reconstructed Pi0 Invariant Mass [MeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f [MeV]",binList.pi0_invMass.get_width()));
        hCut_1Track_pi0invMass_1.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_1Track_pi0invMass_2",i),"Reconstructed Pi0 Invariant Mass New 2",binList.pi0_invMass.get_nBins(), binList.pi0_invMass.get_min(), binList.pi0_invMass.get_max() );
        temp->GetXaxis()->SetTitle("Reconstructed Pi0 Invariant Mass [MeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f [MeV]",binList.pi0_invMass.get_width()));
        hCut_1Track_pi0invMass_2.push_back(temp);
        
        temp = new MnvH1D( Form("%s_%d","hCut_1Track_neutrinoE",i),"Reconstructed Beam Energy",binList.beamE.get_nBins(), binList.beamE.get_min(), binList.beamE.get_max() );
        temp->GetXaxis()->SetTitle("Reconstructed Beam Energy [GeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f ",binList.beamE.get_width()));
        hCut_1Track_neutrinoE.push_back(temp);

        // --------------------------------------------------------------------
        // 2 Track
        // --------------------------------------------------------------------
        temp = new MnvH1D( Form("%s_%d","hCut_2Track_eVis_nuclearTarget",i),"Visible Energy in Nuclear Target",binList.eVis_nuclearTarget.get_nBins(), binList.eVis_nuclearTarget.get_min(), binList.eVis_nuclearTarget.get_max() );
        temp->GetXaxis()->SetTitle("Visible Energy in Nuclear Target [MeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f ",binList.eVis_nuclearTarget.get_width()));
        hCut_2Track_eVis_nuclearTarget.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_2Track_eVis_other",i),"Visible Energy in Tracker + ECAL + HCAL",binList.eVis_other.get_nBins(), binList.eVis_other.get_min(), binList.eVis_other.get_max() );
        temp->GetXaxis()->SetTitle("Visible Energy in Tracker + ECAL + HCAL [MeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f ",binList.eVis_other.get_width()));
        hCut_2Track_eVis_other.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_2Track_gamma1ConvDist",i),"Leading Photon Conversion Distance",binList.bin_photonConvLength.get_nBins(), binList.bin_photonConvLength.get_min(), binList.bin_photonConvLength.get_max() );
        temp->GetXaxis()->SetTitle("Leading Photon Conversion Distance");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f [cm]",binList.bin_photonConvLength.get_width()));
        hCut_2Track_gamma1ConvDist.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_2Track_gamma2ConvDist",i),"Second Photon Conversion Distance",binList.bin_photonConvLength.get_nBins(), binList.bin_photonConvLength.get_min(), binList.bin_photonConvLength.get_max() );
        temp->GetXaxis()->SetTitle("Second Photon Conversion Distance");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f [cm]",binList.bin_photonConvLength.get_width()));
        hCut_2Track_gamma2ConvDist.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_2Track_pi0invMass",i),"Reconstructed Pi0 Invariant Mass",binList.pi0_invMass.get_nBins(), binList.pi0_invMass.get_min(), binList.pi0_invMass.get_max() );
        temp->GetXaxis()->SetTitle("Reconstructed Pi0 Invariant Mass [MeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f [MeV]",binList.pi0_invMass.get_width()));
        hCut_2Track_pi0invMass.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_2Track_pi0invMass_1",i),"Reconstructed Pi0 Invariant Mass New 1",binList.pi0_invMass.get_nBins(), binList.pi0_invMass.get_min(), binList.pi0_invMass.get_max() );
        temp->GetXaxis()->SetTitle("Reconstructed Pi0 Invariant Mass [MeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f [MeV]",binList.pi0_invMass.get_width()));
        hCut_2Track_pi0invMass_1.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_2Track_pi0invMass_2",i),"Reconstructed Pi0 Invariant Mass New 2",binList.pi0_invMass.get_nBins(), binList.pi0_invMass.get_min(), binList.pi0_invMass.get_max() );
        temp->GetXaxis()->SetTitle("Reconstructed Pi0 Invariant Mass [MeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f [MeV]",binList.pi0_invMass.get_width()));
        hCut_2Track_pi0invMass_2.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_2Track_neutrinoE",i),"Reconstructed Beam Energy",binList.beamE.get_nBins(), binList.beamE.get_min(), binList.beamE.get_max() );
        temp->GetXaxis()->SetTitle("Reconstructed Beam Energy [GeV]");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f ",binList.beamE.get_width()));
        hCut_2Track_neutrinoE.push_back(temp);
        
        temp = new MnvH1D( Form("%s_%d","hCut_2Track_protonScore_pIDDiff",i),"Proton Score - Pion Score",binList.particleScoreDiff.get_nBins(), binList.particleScoreDiff.get_min(), binList.particleScoreDiff.get_max() );
        temp->GetXaxis()->SetTitle("Proton Score - Pion Score");
        temp->GetYaxis()->SetTitle("N(Events)");
        hCut_2Track_protonScore_pIDDiff.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_2Track_protonScore_LLR",i),"proton_protonScore_LLR",binList.particleScore_LLR.get_nBins(), binList.particleScore_LLR.get_min(), binList.particleScore_LLR.get_max() );
        temp->GetXaxis()->SetTitle("proton_protonScore_LLR");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f ",binList.particleScore_LLR.get_width()));
        hCut_2Track_protonScore_LLR.push_back(temp);

        temp = new MnvH1D( Form("%s_%d","hCut_2Track_deltaInvMass",i),"deltaInvMass",binList.deltaInvMass.get_nBins(), binList.deltaInvMass.get_min(), binList.deltaInvMass.get_max() );
        temp->GetXaxis()->SetTitle("hCut_2Track_deltaInvMass");
        temp->GetYaxis()->SetTitle(Form("Candidates / %3.2f ",binList.deltaInvMass.get_width()));
        hCut_2Track_deltaInvMass.push_back(temp);
    }

    // MC Only Histograms
    mc_w_DIS = new TH1D( "mc_w_DIS","True W for DIS",binList.mc_w.get_nBins(), binList.mc_w.get_min(), binList.mc_w.get_max() );
    mc_w_DIS->GetXaxis()->SetTitle("True W for DIS [GeV]");
    mc_w_DIS->GetYaxis()->SetTitle(Form("Candidates / %3.2f ",binList.mc_w.get_width()));
    
    mc_w_RES = new TH1D( "mc_w_RES","True W for RES",binList.mc_w.get_nBins(), binList.mc_w.get_min(), binList.mc_w.get_max() );
    mc_w_RES->GetXaxis()->SetTitle("True W for RES [GeV]");
    mc_w_RES->GetYaxis()->SetTitle(Form("Candidates / %3.2f ",binList.mc_w.get_width()));
    
    mc_w_CCQE = new TH1D( "mc_w_CCQE","True W for CCQE",binList.mc_w.get_nBins(), binList.mc_w.get_min(), binList.mc_w.get_max() );
    mc_w_CCQE->GetXaxis()->SetTitle("True W for CCQE [GeV]");
    mc_w_CCQE->GetYaxis()->SetTitle(Form("Candidates / %3.2f ",binList.mc_w.get_width()));

    // Pi0 Invariant Mass - Used for Correction Fit
    pi0_invMass_1Track = new TH1D("pi0_invMass_1Track","#pi^{0} Invariant Mass 1 Track",binList.pi0_invMass.get_nBins(), binList.pi0_invMass.get_min(), binList.pi0_invMass.get_max() );
    pi0_invMass_2Track = new TH1D("pi0_invMass_2Track","#pi^{0} Invariant Mass 2 Track",binList.pi0_invMass.get_nBins(), binList.pi0_invMass.get_min(), binList.pi0_invMass.get_max() );
}

void CCProtonPi0_CutList::SetCutNames()
{
    nCut_All.set_Name("All");
    nCut_Vertex_None.set_Name("Vertex_None");
    nCut_Vertex_Not_Reconstructable.set_Name("Vertex_Not_Reconstructable"); 
    nCut_Vertex_Not_Fiducial.set_Name("Vertex_Not_Fiducial");
    nCut_Muon_None.set_Name("Muon_None");              
    nCut_Muon_Charge.set_Name("Muon_Charge");
    nCut_Vertex_Michel_Exist.set_Name("Vertex_Michel_Exist"); 
    nCut_EndPoint_Michel_Exist.set_Name("EndPoint_Michel_Exist");
    nCut_secEndPoint_Michel_Exist.set_Name("secEndPoint_Michel_Exist");
    nCut_Particle_None.set_Name("Particle_None");
    nCut_Proton_None.set_Name("Proton_None");            
    nCut_Proton_Bad.set_Name("Proton_Bad");            
    nCut_ProtonScore.set_Name("Proton_Score");
    nCut_PreFilter_Pi0.set_Name("PreFilter_Pi0");
    nCut_ConeBlobs.set_Name("ConeBlobs");
    nCut_BlobDirectionBad.set_Name("BlobDirectionBad");
    nCut_Photon1DistanceLow.set_Name("Photon1DistanceLow");
    nCut_Photon2DistanceLow.set_Name("Photon2DistanceLow");
    nCut_Pi0_invMass.set_Name("Pi0_invMass");
    nCut_beamEnergy.set_Name("beamEnergy");

    // 1Track
    nCut_1Track_All.set_Name("All_1Track");
    nCut_1Track_PreFilter_Pi0.set_Name("PreFilter_Pi0");
    nCut_1Track_ConeBlobs.set_Name("ConeBlobs");
    nCut_1Track_BlobDirectionBad.set_Name("BlobDirectionBad");
    nCut_1Track_Photon1DistanceLow.set_Name("Photon1DistanceLow");
    nCut_1Track_Photon2DistanceLow.set_Name("Photon2DistanceLow");
    nCut_1Track_Pi0_invMass.set_Name("Pi0_invMass");
    nCut_1Track_beamEnergy.set_Name("beamEnergy");

    // 2 Track
    nCut_2Track_All.set_Name("All_2Track");
    nCut_2Track_Proton_Bad.set_Name("Proton_Bad");
    nCut_2Track_ProtonScore.set_Name("Proton_Score");
    nCut_2Track_PreFilter_Pi0.set_Name("PreFilter_Pi0");
    nCut_2Track_ConeBlobs.set_Name("ConeBlobs");
    nCut_2Track_BlobDirectionBad.set_Name("BlobDirectionBad");
    nCut_2Track_Photon1DistanceLow.set_Name("Photon1DistanceLow");
    nCut_2Track_Photon2DistanceLow.set_Name("Photon2DistanceLow");
    nCut_2Track_Pi0_invMass.set_Name("Pi0_invMass");
    nCut_2Track_beamEnergy.set_Name("beamEnergy");
}

void CCProtonPi0_CutList::OpenTextFiles(bool isMC)
{
    std::string type;

    if (isMC) type = "CutTable_MC_";
    else type = "CutTable_Data_";

    // File Names
    std::string f_all = Folder_List::output + Folder_List::textOut + type + "All_" + version + ".txt";
    std::string f_1Track = Folder_List::output + Folder_List::textOut + type + "1Track_" + version + ".txt";
    std::string f_2Track = Folder_List::output + Folder_List::textOut + type + "2Track_" + version + ".txt";
    
    OpenTextFile(f_all,cutText_All);
    OpenTextFile(f_1Track,cutText_1Track);
    OpenTextFile(f_2Track,cutText_2Track);
}

void CCProtonPi0_CutList::writeCutTableHeader(ofstream &file)
{
    file<<std::left;
    file.width(35); file<<"Cut"<<" "; 
    file.width(12); file<<"N(Events)"<<" ";    
    file.width(12); file<<"N(Signal)"<<" ";      
    file.width(12); file<<"Eff(All)"<<" ";      
    file.width(12); file<<"Eff(MINOS)"<<" ";      
    file.width(12); file<<"Purity"<<" ";
    file<<endl;
}

double CCProtonPi0_CutList::getCutEfficiency(CCProtonPi0_Cut& currentCut, CCProtonPi0_Cut& effBase) const
{
    double nSignal_current = currentCut.nSignal.getCount();
    double nSignal_effBase = effBase.nSignal.getCount(); 
    double eff = (nSignal_current / nSignal_effBase) * 100.0;
    return eff;   
}

double CCProtonPi0_CutList::getCutEfficiency(CCProtonPi0_Cut& currentCut, double effBase) const
{
    double nSignal_current = currentCut.nSignal.getCount();
    double nSignal_effBase = effBase; 
    double eff = (nSignal_current / nSignal_effBase) * 100.0;
    return eff;   
}

double CCProtonPi0_CutList::getCutPurity(CCProtonPi0_Cut& currentCut) const
{
    double nSignal_current = currentCut.nSignal.getCount();
    double nEvents_current = currentCut.nEvent.getCount();
    double purity  = (nSignal_current / nEvents_current) * 100.0;
    return purity;   
}

void CCProtonPi0_CutList::formCutVectors()
{   
    nCutVector_All.push_back(nCut_All);
    nCutVector_All.push_back(nCut_Vertex_None);
    nCutVector_All.push_back(nCut_Vertex_Not_Reconstructable); 
    nCutVector_All.push_back(nCut_Vertex_Not_Fiducial);
    nCutVector_All.push_back(nCut_Muon_None);              
    nCutVector_All.push_back(nCut_Muon_Charge);
    nCutVector_All.push_back(nCut_Vertex_Michel_Exist); 
    nCutVector_All.push_back(nCut_EndPoint_Michel_Exist);
    nCutVector_All.push_back(nCut_secEndPoint_Michel_Exist);
    nCutVector_All.push_back(nCut_Particle_None);
    nCutVector_All.push_back(nCut_Proton_None);
    nCutVector_All.push_back(nCut_Proton_Bad);
    nCutVector_All.push_back(nCut_ProtonScore);
    nCutVector_All.push_back(nCut_PreFilter_Pi0);
    nCutVector_All.push_back(nCut_ConeBlobs);
    nCutVector_All.push_back(nCut_BlobDirectionBad);
    nCutVector_All.push_back(nCut_Photon1DistanceLow);
    nCutVector_All.push_back(nCut_Photon2DistanceLow);
    nCutVector_All.push_back(nCut_Pi0_invMass);
    nCutVector_All.push_back(nCut_beamEnergy);

    // 1 Track
    nCutVector_1Track.push_back(nCut_1Track_All);
    nCutVector_1Track.push_back(nCut_1Track_PreFilter_Pi0);
    nCutVector_1Track.push_back(nCut_1Track_ConeBlobs);
    nCutVector_1Track.push_back(nCut_1Track_BlobDirectionBad);
    nCutVector_1Track.push_back(nCut_1Track_Photon1DistanceLow);
    nCutVector_1Track.push_back(nCut_1Track_Photon2DistanceLow);
    nCutVector_1Track.push_back(nCut_1Track_Pi0_invMass);
    nCutVector_1Track.push_back(nCut_1Track_beamEnergy);

    // 2 Track
    nCutVector_2Track.push_back(nCut_2Track_All);
    nCutVector_2Track.push_back(nCut_2Track_Proton_Bad);
    nCutVector_2Track.push_back(nCut_2Track_ProtonScore);
    nCutVector_2Track.push_back(nCut_2Track_PreFilter_Pi0);
    nCutVector_2Track.push_back(nCut_2Track_ConeBlobs);
    nCutVector_2Track.push_back(nCut_2Track_BlobDirectionBad);
    nCutVector_2Track.push_back(nCut_2Track_Photon1DistanceLow);
    nCutVector_2Track.push_back(nCut_2Track_Photon2DistanceLow);
    nCutVector_2Track.push_back(nCut_2Track_Pi0_invMass);
    nCutVector_2Track.push_back(nCut_2Track_beamEnergy);
}

void CCProtonPi0_CutList::writeCutTable()
{
    formCutVectors();
    
    writeAllCuts(); 
    write1TrackCuts();
    write2TrackCuts();
}

void CCProtonPi0_CutList::writeAllCuts()
{
    writeCutTableHeader(cutText_All);
    writeCutTableRows(cutText_All, nCutVector_All, true);
}

void CCProtonPi0_CutList::write1TrackCuts()
{
    writeCutTableHeader(cutText_1Track);
    writeCutTableRows(cutText_1Track, nCutVector_1Track, false);
}

void CCProtonPi0_CutList::write2TrackCuts()
{
    writeCutTableHeader(cutText_2Track);
    writeCutTableRows(cutText_2Track, nCutVector_2Track, false);
}

void CCProtonPi0_CutList::writeCutTableRows(ofstream &file, vector<CCProtonPi0_Cut> &nCutVector, bool isAll)
{
    // First Element on the nCutVector is the All Events
    CCProtonPi0_Cut eff_base_all = nCutVector[0];
    CCProtonPi0_Cut eff_base_MINOS;
    if (isAll){
        eff_base_MINOS = nCutVector_All[4];
    }else{
        eff_base_MINOS = nCutVector[0];
    }
    
    
    for( unsigned int i = 0; i < nCutVector.size(); i++){
        writeSingleRow(file, nCutVector[i], eff_base_all, eff_base_MINOS);    
    }
}

void CCProtonPi0_CutList::writeSingleRow(ofstream &file, CCProtonPi0_Cut& currentCut, CCProtonPi0_Cut &eff_base_all, CCProtonPi0_Cut &eff_base_MINOS)
{
    double eff_AllSignal;
    double eff_MINOS;
    double purity;    

    eff_AllSignal = getCutEfficiency(currentCut, eff_base_all);
    eff_MINOS = getCutEfficiency(currentCut, eff_base_MINOS);
    purity = getCutPurity(currentCut);
            
    file.width(35); file<<currentCut.get_Name()<<" ";
    file.width(12); file<<currentCut.nEvent.getCount()<<" ";
    
    // Total Signal
    file.width(12); file<<currentCut.nSignal.getCount()<<" ";

    // Efficiency
    if ( eff_AllSignal <= 100){
        file.width(12); file<<eff_AllSignal<<" ";
    }else{
        file.width(12); file<<"N/A"<<" ";    
    }
 
    // Efficiency
    if ( eff_MINOS <= 100){
        file.width(12); file<<eff_MINOS<<" ";
    }else{
        file.width(12); file<<"N/A"<<" ";    
    }
   
    // Purity
    file.width(12); file<<purity<<" ";

    file<<endl;
}

CCProtonPi0_CutList::~CCProtonPi0_CutList()
{
    cutText_All.close();
    cutText_1Track.close();
    cutText_2Track.close();
}

void CCProtonPi0_CutList::writeHistograms()
{
    std::cout<<">> Writing "<<rootDir<<std::endl;
    f->cd();
    for (int i = 0; i < nHistograms; i++){
        // Common
        hCut_nVertices[i]->Write();
        hCut_nTracks[i]->Write();
        hCut_nTracks2[i]->Write();
        hCut_nTracks_Close[i]->Write();
        hCut_nTracks_Far[i]->Write();
        hCut_nTracks_Discarded[i]->Write();
        hCut_Michel[i]->Write();
        
        // 1 Track
        hCut_1Track_eVis_nuclearTarget[i]->Write();
        hCut_1Track_eVis_other[i]->Write();
        hCut_1Track_pi0invMass[i]->Write();
        hCut_1Track_pi0invMass_1[i]->Write();
        hCut_1Track_pi0invMass_2[i]->Write();
        hCut_1Track_gamma1ConvDist[i]->Write();
        hCut_1Track_gamma2ConvDist[i]->Write();
        hCut_1Track_neutrinoE[i]->Write();
       
        // 2 Track 
        hCut_2Track_eVis_nuclearTarget[i]->Write();
        hCut_2Track_eVis_other[i]->Write();
        hCut_2Track_pi0invMass[i]->Write();
        hCut_2Track_pi0invMass_1[i]->Write();
        hCut_2Track_pi0invMass_2[i]->Write();
        hCut_2Track_gamma1ConvDist[i]->Write();
        hCut_2Track_gamma2ConvDist[i]->Write();
        hCut_2Track_neutrinoE[i]->Write();
        hCut_2Track_protonScore_pIDDiff[i]->Write();
        hCut_2Track_protonScore_LLR[i]->Write();
        hCut_2Track_deltaInvMass[i]->Write();
    }

    // MC Only
    mc_w_DIS->Write();
    mc_w_RES->Write();
    mc_w_CCQE->Write();
    
    pi0_invMass_1Track->Write();
    pi0_invMass_2Track->Write();

    f->Close();
}

#endif

