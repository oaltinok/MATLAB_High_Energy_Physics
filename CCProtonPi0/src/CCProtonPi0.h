/*
================================================================================
CCProtonPi0

    Reconstruction Package:
        Exclusive Channel for muon,proton,pi0 on the final state
        Uses Nightly Build
    
    Main Package:
        AnalysisFramework/Ana/CCProtonPi0/
        
    Setup:
        > getpack -u Ana/CCProtonPi0
        > cmt config
        > cmt make
        
    Usage:
        There is a corresponding Options file under Tools/SystemTests
        Use Tools/ProductionScripts/ana_scripts/ProcessAna.py

    
    Author:         Ozgur Altinok  - ozgur.altinok@tufts.edu
================================================================================
*/
#ifndef CCPROTONPI0_H 
#define CCPROTONPI0_H 1

#include <utility>
#include <fstream>

// ineritance
#include "AnaUtils/MinervaAnalysisTool.h"

//-- Forward Declarations
#include "Event/MinervaEventFwd.h"

class IAnchoredTrackFormation;
class IBlobCreatorUtils;
class ICalorimetryUtils;
class IConeUtilsTool;
class IEnergyCorrectionTool;
class IExtraEnergyTool;
class IGeomUtilSvc;
class IGetCalAttenuation;
class IGetDeadTime;
class IGiGaGeomCnvSvc;
class IHitTaggerTool;
class IHoughBlob;
class IHoughTool;
class IIDAnchoredBlobCreator;
class IMichelTool;
class IMinervaCoordSysTool;
class IMinervaMathTool;
class IMinervaObjectAssociator;
class IODProngClassificationTool;
class IParticleMakerTool;
class IParticleTool;
class IProtonUtils;
class IRecoObjectTimeTool;
class IVertexEnergyStudyTool;
class IVertexFitter;
class TRandom3;

namespace Minerva {
  class DeDetector;
  class DeOuterDetector;
}

//! This class is for Reconstruct Pi0 using muon match vertex
class CCProtonPi0 : public MinervaAnalysisTool
{
    private:
        typedef std::vector<Minerva::NeutrinoInt*> NeutrinoVect;
        
    public:
        
        //! Standard constructor
        CCProtonPi0(const std::string& type, 
                    const std::string& name, 
                    const IInterface* parent );
        
        //! Destructor (mandatory for inheritance)
        virtual ~CCProtonPi0(){};
        
        StatusCode initialize();
        StatusCode finalize();
        
        //! Reconstruct the event (mandatory for inheritance)
        StatusCode reconstructEvent(Minerva::PhysicsEvent* event, 
                                    Minerva::GenMinInteraction* truthEvent = NULL ) const;
        
        //! Attach an interpretations to the event (mandatory for inheritance)
        StatusCode interpretEvent(  const Minerva::PhysicsEvent* event, 
                                    const Minerva::GenMinInteraction* truthEvent, 
                                    NeutrinoVect& interaction_hyp ) const;
        
        StatusCode tagTruth( Minerva::GenMinInteraction* truthEvent ) const;
        
        bool truthIsPlausible( const Minerva::PhysicsEvent*) const;
        
    private:
        // mutable Member Variables which can be modified by const functions
        mutable Gaudi::LorentzVector m_muon_4P;
        mutable Gaudi::LorentzVector m_proton_4P;
        mutable Gaudi::LorentzVector m_pi0_4P;
        mutable SmartRef<Minerva::Vertex>   m_PrimaryVertex;
        mutable SmartRef<Minerva::Prong>    m_MuonProng;
        mutable SmartRef<Minerva::Particle> m_MuonParticle;
        mutable SmartRef<Minerva::IDBlob>   m_Pi0Blob1;
        mutable SmartRef<Minerva::IDBlob>   m_Pi0Blob2;
        mutable Minerva::ProngVect    m_ProtonProngs;
        mutable Minerva::ParticleVect m_ProtonParticles;

        // Counters for Functions - Debugging Purposes
        mutable double N_tagTruth;
        mutable double N_reconstructEvent;

        std::vector<std::string>   m_dedx_uncertainties;
        
        // Fiducial Volume
        double m_fidHexApothem;
        double m_fidUpStreamZ;
        double m_fidDownStreamZ;
        
        // Analyzable Volume
        double m_recoHexApothem;
        double m_recoUpStreamZ;
        double m_recoDownStreamZ;
        
        double m_beamAngleBias;
        
        // Algorihm Flow
        bool m_writeFSParticle_Table;
        bool m_store_all_events;
        bool m_DoPlausibilityCuts;
        bool m_DoTruthMatch;
        bool m_applyExtraMichelCuts;
            
        // Prong and Cluster Colors
        int m_Color_muonProng;
        int m_Color_protonProng;
        int m_Color_primaryVertex;
        int m_Color_secondaryVertex;
        int m_Color_endPointVertex;
        int m_Color_unattachedProng;
        int m_Color_Gamma1Prong;
        int m_Color_Gamma2Prong;
        int m_Color_GammaOtherProng;
        int m_Color_clusterUnused;
        int m_Color_clusterUsed;
        int m_Color_VertexFila;
        int m_Color_VertexSphere;
        int m_Color_RejectedBlob;
             
        // VertexBlob
        bool 	 m_sphereVertex;
        double  m_maxSearchD;
        double  m_maxStartingD;
        double  m_maxSearchGap;		
        bool	 m_filamentVertex;
        double  m_maxSearchDFila;
        double  m_maxStartingDFila;
        double  m_maxSearchGapFila;
        bool    fSkipLowEnergyClusterVtxEnergy;
        bool    fThresholdVertexEnergy;
        
        // ConeBlobs
        double m_energyHoughlimit;     ///< Energy limit to start using Hough T.
        double m_rejectedClustersTime; ///< window time  to allow clusters
        
        bool m_TrytoRecoverBlobReco;
        bool m_ApplyAttenuationCorrection;
        
        bool   m_AllowUVMatchWithMoreTolerance;
        double m_UVMatchTolerance;
        double m_UVMatchMoreTolerance;
  
        TRandom3*                 m_randomGen;
        unsigned long int         m_randomSeed;
        
        Minerva::DeDetector*        m_InnerDetector;
        Minerva::DeOuterDetector*   m_OuterDetector;
        
        // Duplicated variables -- will fix in future
        const Minerva::DeDetector*      m_idDet;                ///< Inner detector
        const Minerva::DeOuterDetector* m_odDet;                ///< Outer detector
        
        IAnchoredTrackFormation* m_anchoredTracker;
        IBlobCreatorUtils* m_blobUtils;
        ICalorimetryUtils* m_caloUtils;
        IConeUtilsTool* m_coneUtilsTool;
        IEnergyCorrectionTool* m_energyCorrectionTool;
        IExtraEnergyTool* m_extraEnergyTool;
        IGeomUtilSvc* m_GeomUtilSvc;
        IGetCalAttenuation* m_AttenuationCorrectionTool;
        IGetDeadTime* m_getDeadTimeTool;
        IGiGaGeomCnvSvc* m_gigaCnvSvc;
        IHitTaggerTool* m_hitTagger;
        IHoughBlob* m_idHoughBlob;
        IHoughTool* m_idHoughTool;
        IIDAnchoredBlobCreator* m_stopPointBlobTool;
        IMichelTool* m_michelTrkTool;
        IMichelTool* m_michelVtxTool;
        IMinervaCoordSysTool* m_coordSysTool;
        IMinervaMathTool* m_mathTool;
        IMinervaObjectAssociator* m_objectAssociator;
        IODProngClassificationTool* m_odMatchTool;
        IParticleMakerTool* m_particleMaker;
        IParticleTool* m_LikelihoodPIDTool;
        IProtonUtils* m_protonUtils;
        IRecoObjectTimeTool* m_recoTimeTool;
        IVertexEnergyStudyTool* m_vertexEnergyStudyTool;
        IVertexFitter* m_vertexFitter;

        //! Private Functions
        SmartRefVector<Minerva::IDCluster> FilterInSphereClusters( Minerva::PhysicsEvent *event, const SmartRefVector<Minerva::IDCluster>& clusters, const double sphereRadius, std::vector<double>& radii) const;

        StatusCode HoughBlob( SmartRefVector<Minerva::IDCluster> idClusters, std::vector<Minerva::IDBlob*>& outBlobs) const;
        StatusCode ODActivity( Minerva::PhysicsEvent *event, std::vector<Minerva::IDBlob*> idBlobs ) const;
        StatusCode getNearestPlane( double z, int & module_return, int & plane_return) const;
        StatusCode interpretFailEvent( Minerva::PhysicsEvent* event ) const;
        bool ConeBlobs( Minerva::PhysicsEvent *event ) const;
        bool PreFilterPi0( Minerva::PhysicsEvent *event ) const;
        bool AreBlobsDirectionGood() const;
        bool AreBlobsGood() const;
        void VertexBlob( Minerva::PhysicsEvent *event ) const;
        bool checkMichel(Minerva::GenMinInteraction* truthEvent) const;
        bool checkPionAbsorption(Minerva::GenMinInteraction* truthEvent) const;
        void correctProtonProngEnergy(  SmartRef<Minerva::Prong>& protonProng, double& p_calCorrection, double& p_visEnergyCorrection ) const;
        bool createTrackedParticles(Minerva::PhysicsEvent *event ) const;
        bool getProtonProng(Minerva::PhysicsEvent *event ) const;
        bool isBackgroundQELike(Minerva::GenMinInteraction* truthEvent) const;
        bool isMichelProngGood(Minerva::Prong &michelProng) const;
        bool isMotherPrimary(std::vector<int>& motherList, int mother ) const;
        bool setMuonData( Minerva::NeutrinoInt* nuInt ) const;
        bool setPi0Data( Minerva::NeutrinoInt* nuInt ) const;
        bool setProtonData( Minerva::NeutrinoInt* nuInt ) const;
        bool tagSignal( Minerva::GenMinInteraction* truthEvent) const;
        double Calc_QSq(double Enu) const;
        double Calc_WSq(double Enu, double QSq) const;
        double Calc_Enu_Cal(double hadronEnergy) const;
        double Calc_Enu_1Track() const;
        double Calc_Enu_2Track() const;
        double Calc_Longitudinal_Momentum(Gaudi::LorentzVector particle_4P) const;
        double Calc_Px_wrt_Beam(Gaudi::LorentzVector particle_4P) const;
        double Calc_Py_wrt_Beam(Gaudi::LorentzVector particle_4P) const;
        double CalcMinBlobSeparation( const Minerva::IDBlob* blob) const;
        double calcDistance( double x1, double y1, double z1,double x2, double y2, double z2) const;
        double getClusterEnergy( Minerva::PhysicsEvent* event, std::string input_clusterType) const;
        int getMichelPion(std::vector<int>& piList, int ID ) const;
        std::pair<int,double> OneParLineFitBlob(const Minerva::IDBlob* blob) const;
        std::vector<double> GetBlobClusterEnergy( const Minerva::IDBlob* blob ) const;
        void ApplyAttenuationCorrection(Minerva::IDBlob* blob) const;
        void Calculate_dEdx( const Minerva::IDBlob* blob, Minerva::PhysicsEvent* event, unsigned int blob_number) const;
        void SetSignalKinematics(Minerva::GenMinInteraction* truthEvent) const;
        void processBlobs( Minerva::PhysicsEvent *event, std::vector<Minerva::IDBlob*> idBlobs) const;
        void saveMichelElectron(Minerva::GenMinInteraction* truthEvent, int muon_ID) const;
        void saveMichelProngToNTuple(Minerva::PhysicsEvent* event, Minerva::Prong &michelProng) const;
        void setBlobData(Minerva::PhysicsEvent* event) const;
        void setEventKinematics(Minerva::NeutrinoInt* nuInt, double hadronVisibleEnergy) const;
        void setPi0GenieRecord(Minerva::GenMinInteraction* truthEvent) const;
        void setTargetMaterial(Minerva::GenMinInteraction* truthEvent) const;
        void setTrackProngTruth( Minerva::NeutrinoInt* neutrino, Minerva::ProngVect& prongs ) const;
        void setVertexData( Minerva::NeutrinoInt* nuInt, const Minerva::PhysicsEvent* event ) const;
        void tagBackground(Minerva::GenMinInteraction* truthEvent) const;
        void writeBackgroundType(Minerva::GenMinInteraction* truthEvent) const;
        void writeEventRecord(Minerva::GenMinInteraction* truthEvent, bool isSignal) const;
        void writeFSParticleTable(bool isSignal) const;
        void setTrackDirection( Minerva::Track* track, Minerva::Vertex* vertex ) const;
        Minerva::IDClusterVect getClusters( Minerva::PhysicsEvent* event ) const;
        bool createdAnchoredShortTracks( Minerva::PhysicsEvent* event, Minerva::Vertex* vertex, bool make_primary_short_tracks ) const;
        void SetVertexCount(Minerva::PhysicsEvent *event) const;
        void RefitVertex_Using_AnchoredShortTracks(Minerva::PhysicsEvent *event) const;
        bool vertexInFiducialVolume(Minerva::PhysicsEvent *event) const;
        bool vertexInRecoVolume(Minerva::PhysicsEvent *event) const;
        bool hasEventVertex(Minerva::PhysicsEvent *event) const;
        bool ShouldReconstructEvent( Minerva::PhysicsEvent *event, Minerva::GenMinInteraction* truthEvent ) const;
        bool isMuonPlausible(Minerva::PhysicsEvent *event) const;
        bool hasEventMinosMatchedMuon(Minerva::PhysicsEvent *event) const;
        bool isMuonChargeNegative(Minerva::PhysicsEvent *event) const;
        void tagPrimaryMuon(Minerva::PhysicsEvent *event) const;
        bool VertexHasMichels(Minerva::PhysicsEvent *event) const;
        bool TrackEndPointHasMichels(Minerva::PhysicsEvent *event) const;
        void SaveEventTime(Minerva::PhysicsEvent *event) const;
        void ColorUnusedIDClusters(Minerva::PhysicsEvent *event) const;
        void SaveEventVisibleEnergy(Minerva::PhysicsEvent *event) const;
        int GetNPrimaryProngs(Minerva::PhysicsEvent *event) const;
};

#endif // CCPROTONPI0_H 

