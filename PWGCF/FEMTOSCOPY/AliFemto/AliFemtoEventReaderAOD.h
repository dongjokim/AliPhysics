///
/// \file PWGCF/FEMTOSCOPY/AliFemto/AliFemtoEventReaderAOD.h
/// \author Adam Kisiel <kisiel@mps.ohio-state.edu>
///
/// \class AliFemtoEventReaderAOD
/// \brief The reader class for Alice AOD files
/// Reads in AOD information and converts it into internal AliFemtoEvent
///

#ifndef ALIFEMTOEVENTREADERAOD_H
#define ALIFEMTOEVENTREADERAOD_H
#include "AliFemtoEventReader.h"
#include "AliFemtoEnumeration.h"

#include <string>

#include "TTree.h"
#include "TChain.h"
#include "TBits.h"
#include "THnSparse.h"

#include "AliAODEvent.h"
//#include "AliPWG2AODTrack.h"
#include "AliAODMCParticle.h"
#include "AliFemtoV0.h"
#include "AliFemtoXi.h"
#include "AliAODpidUtil.h"
#include "AliAODHeader.h"
#include "AliAnalysisUtils.h"
#include "AliEventCuts.h"
#include "AliMultSelection.h"

class AliFemtoEvent;
class AliFemtoTrack;

class AliFemtoEventReaderAOD : public AliFemtoEventReader {
public:
  enum EventMult {kCentrality = 0, kGlobalCount = 1, kReference = 2,
                  kTPCOnlyRef = 3, kVZERO = 4, kCentralityTRK = 5,
                  kCentralityZNA = 6, kCentralityCL1 = 7, kCentralityCND = 9,
                  kCentralityV0A = 10, kCentralityV0C = 11, kCentralityZNC = 12,
                  kCentralityCL0 = 13, kCentralityFMD = 14, kCentralityTKL = 15,
                  kCentralityNPA = 16, kRefComb08 = 17
                 };
  typedef enum EventMult EstEventMult;

  AliFemtoEventReaderAOD();
  AliFemtoEventReaderAOD(const AliFemtoEventReaderAOD &aReader);
  virtual ~AliFemtoEventReaderAOD();

  AliFemtoEventReaderAOD &operator=(const AliFemtoEventReaderAOD &aReader);

  virtual AliFemtoEvent *ReturnHbtEvent();
  AliFemtoString Report();
  void SetInputFile(const char *inputfile);

  void SetFilterBit(UInt_t ibit);
  void SetFilterMask(int ibit);
  UInt_t GetTrackFilter() const {
    return fFilterBit | fFilterMask;
  }

  void SetReadMC(unsigned char a);
  bool GetReadMC() const {
    return fReadMC;
  }

  void SetReadV0(unsigned char a);
  bool GetReadV0() const {
    return fReadV0;
  }

  void SetReadCascade(unsigned char a);
  bool GetReadCascade() const {
    return fReadCascade;
  }
  void SetPreCentralityCut(double min, double max); // only set pre centrality cut
  void SetCentralityPreSelection(double min, double max);
  std::pair<double, double> GetCentralityPreSelection() const {
    return std::make_pair(fCentRange[0], fCentRange[1]);
  }
  void SetExtentV0MAcceptance(Bool_t newVal) { fExtendV0MAcceptance=newVal; };
  void SetNoCentrality(bool anocent);
  void SetAODpidUtil(AliAODpidUtil *aAODpidUtil);
  void SetAODheader(AliAODHeader *aAODheader);
  void SetMagneticFieldSign(int s);
  void SetEPVZERO(Bool_t);
  void GetGlobalPositionAtGlobalRadiiThroughTPC(const AliAODTrack *track, Float_t bfield, Float_t globalPositionsAtRadii[9][3]);

  void SetUseMultiplicity(EstEventMult aType);
  EstEventMult GetUseMultiplicity() const {
    return fEstEventMult;
  }

  void SetpA2013(Bool_t pa2013); ///< set vertex configuration for pA (2013): IsVertexSelected2013pA
  void SetAA15o(Bool_t AA15o);
  void SetUseMVPlpSelection(Bool_t mvplp);
  void SetUseOutOfBunchPlpSelection(Bool_t outOfBunchPlp);
  void SetRejectTPCPileupWithV0CentTPCnTracksCorr(Bool_t OOBV0TPC);
  void SetIsPileUpEvent(Bool_t ispileup);
  void SetCascadePileUpRemoval(Bool_t cascadePileUpRemoval);
  void SetV0PileUpRemoval(Bool_t v0PileUpRemoval);
  void SetTrackPileUpRemoval(Bool_t trackPileUpRemoval);
  void SetRejectTPCPileupWithITSTPCnCluCorr(Bool_t RejectTPCPileupWithITSTPCnCluCorr);//pileup suggested for experimentaldata 2018 PbPb 
  void SetParticleFromOutOfBunchPileupCollision(bool PileUpTrack); //injected pile-up on tracks from out of bunch (use for MC data anchored to 2018 PbPb period)
  void SetPileupInGeneratedEvent(bool PileUpEvent); //injected pile-up events (use for MC data anchored to 2018 PbPb period)
  
  void SetMinVtxContr(Int_t contr = 1) {
    fMinVtxContr = contr;
  }
  void SetMinPlpContribMV(Int_t minPlpContribMV) {
    fMinPlpContribMV = minPlpContribMV;
  }
  void SetMinPlpContribSPD(Int_t minPlpContribSPD) {
    fMinPlpContribSPD = minPlpContribSPD;
  }
  void SetDCAglobalTrack(Int_t dcagt);
  Int_t GetDCAglobalTrack() const {
    return fDCAglobalTrack;
  }

  bool RejectEventCentFlat(float MagField, float CentPercent);
  void SetCentralityFlattening(Bool_t flat);
  bool GetCentralityFlattening() const {
    return fFlatCent;
  }
  void SetShiftPosition(Double_t rad);

  void SetPrimaryVertexCorrectionTPCPoints(bool correctTpcPoints);
  bool GetPrimaryVertexCorrectionTPCPoints() const {
    return fPrimaryVertexCorrectionTPCPoints;
  }

  void SetShiftedPositions(const AliAODTrack *track ,const Float_t bfield, Float_t posShifted[3], const Double_t radius=1.25);

  void SetUseAliEventCuts(Bool_t useAliEventCuts);
  void SetReadFullMCData(Bool_t should_read=true);
  bool GetReadFullMCData() const;
  
  //ml jets--
  void SetCalcJets(Int_t jets); //0-no, 1-same, 2-diff
  bool GetCalcJets() const;
  void SetPtmaxJets(Double_t ptmax);
  //  void GetPtmaxJets() const {
  //    return fPtmax;
  //  } 

    // dowang femto
    void Set15oPass2EventReject(Int_t EventReject);
    bool Reject15oPass2Event(AliAODEvent *fAOD,Int_t yearLabel);
    void SetPbPb15Pass2MC(Int_t PbPb15Pass2MC);
  void SetppHM(Int_t aHMpp,float aCut);
  //---
  void SetRejection15opass2(Int_t rejeEv15o);
  void Set1DCorrectionsPions(TH1D *h1);
  void Set1DCorrectionsKaons(TH1D *h1);
  void Set1DCorrectionsProtons(TH1D *h1);
  void Set1DCorrectionsPionsMinus(TH1D *h1);
  void Set1DCorrectionsKaonsMinus(TH1D *h1);
  void Set1DCorrectionsProtonsMinus(TH1D *h1);

  void Set1DCorrectionsDeuterons(TH1D *h1);
  void Set1DCorrectionsTritons(TH1D *h1);
  void Set1DCorrectionsHe3s(TH1D *h1);
  void Set1DCorrectionsAlphas(TH1D *h1);
  void Set1DCorrectionsDeuteronsMinus(TH1D *h1);
  void Set1DCorrectionsTritonsMinus(TH1D *h1);
  void Set1DCorrectionsHe3sMinus(TH1D *h1);
  void Set1DCorrectionsAlphasMinus(TH1D *h1);

  void Set1DCorrectionsAll(TH1D *h1);
  void Set1DCorrectionsLambdas(TH1D *h1);
  void Set1DCorrectionsLambdasMinus(TH1D *h1);
  void Set1DCorrectionsK0s(TH1D *h1);
  void Set1DCorrectionsXiPlus(TH1D *h1);
  void Set1DCorrectionsXiMinus(TH1D *h1);

  void Set4DCorrectionsPions(THnSparse *h1);
  void Set4DCorrectionsKaons(THnSparse *h1);
  void Set4DCorrectionsProtons(THnSparse *h1);
  void Set4DCorrectionsPionsMinus(THnSparse *h1);
  void Set4DCorrectionsKaonsMinus(THnSparse *h1);
  void Set4DCorrectionsProtonsMinus(THnSparse *h1);
  void Set4DCorrectionsAll(THnSparse *h1);
  void Set4DCorrectionsLambdas(THnSparse *h1);
  void Set4DCorrectionsLambdasMinus(THnSparse *h1);

  //Special MC analysis for pi,K,p,e slected by PDG code -->
  void SetPionAnalysis(Bool_t aSetPionAna);
  void SetKaonAnalysis(Bool_t aSetKaonAna);
  void SetProtonAnalysis(Bool_t aSetProtonAna);
  void SetElectronAnalysis(Bool_t aSetElectronAna);
  void SetDeuteronAnalysis(Bool_t aSetDeuteronAna);
  void SetTritonAnalysis(Bool_t aSetTritonAna);
  void SetHe3Analysis(Bool_t aSetHe3Ana);
  void SetAlphaAnalysis(Bool_t aSetAlphaAna);
  //Special MC analysis for pi,K,p,e slected by PDG code <--

protected:
  virtual AliFemtoEvent *CopyAODtoFemtoEvent();
  virtual AliFemtoTrack *CopyAODtoFemtoTrack(const AliAODTrack *tAodTrack);
  virtual AliFemtoV0 *CopyAODtoFemtoV0(AliAODv0 *tAODv0);
  virtual AliFemtoXi *CopyAODtoFemtoXi(AliAODcascade *tAODxi);
  virtual void CopyPIDtoFemtoTrack(const AliAODTrack *tAodTrack, AliFemtoTrack *tFemtoTrack);

  int            fNumberofEvent;    ///< number of Events in AOD file
  int            fCurEvent;         ///< number of current event
  AliAODEvent   *fEvent;            ///< AOD event
  TBits          fAllTrue;          ///< Bit set with all true bits
  TBits          fAllFalse;         ///< Bit set with all false bits
  UInt_t         fFilterBit;        ///< Bitmap bit for AOD filters
  UInt_t         fFilterMask;
  //  TClonesArray*  fPWG2AODTracks;    // Link to PWG2 specific AOD information (if it exists)

  unsigned char  fReadMC;           ///< Attempt to read the MC information from the AOD
  unsigned char  fReadV0;           ///< Read V0 information from the AOD and put it into V0Collection
  unsigned char  fReadCascade;      ///< Read Cascade information from the AOD and put it into V0Collection
  unsigned char  fUsePreCent;       ///< Use centrality pre-selection to speed up analysis
  EstEventMult   fEstEventMult;     ///< Type of the event multiplicity estimator
  double         fCentRange[2];     ///< Centrality pre-selection range
  AliAODpidUtil *fAODpidUtil;
  AliAODHeader *fAODheader;
  AliAnalysisUtils *fAnaUtils;
  AliEventCuts     *fEventCuts;
  Bool_t           fUseAliEventCuts;
  
  /// Read generated particle info of "low quality" MC tracks
  /// (i.e. tracks with negative labels)
  Bool_t           fReadFullMCData;

//ML -- calculate ptmax,phimax,etamax of event
  Int_t           fjets; //0-no calc., 1-same, 2-diff
  Double_t         fPtmax; //max pT in event
 
    // dowang femto
    Int_t fEventReject;
    Int_t fPbPb15Pass2MC;
    TF1 *fCenCutLowPU;
    TF1 *fCenCutHighPU;
    TF1 *fSPDCutPU;
    TF1 *fV0CutPU;
    TF1 *fMultCutPU;

   TF1 *fCenCutLowPU2018;
    TF1 *fCenCutHighPU2018;
    TF1 *fSPDCutPU2018;
    TF1 *fV0CutPU2018;
    TF1 *fMultCutPU2018;
private:

  AliAODMCParticle *GetParticleWithLabel(TClonesArray *mcP, Int_t aLabel);

  string fInputFile;       ///< name of input file with AOD filenames
  TChain *fTree;           ///< AOD tree
  TFile *fAodFile;         ///< AOD file
  int fMagFieldSign;       ///< Magnetic field sign
  Bool_t fisEPVZ;          ///< to get event plane angle from VZERO
  Bool_t fpA2013;          ///< analysis on pA 2013 data
  Bool_t fisPileUp;        ///< pile up rejection on?
  Bool_t fCascadePileUpRemoval;//pile-up removal for cascades (its+tof hits for pos, neg and bac tracks)
  Bool_t fV0PileUpRemoval;//pile-up removal for V0s
  Bool_t fTrackPileUpRemoval;//pile-up removal for tracks (its+tof hits of tracks)
  Bool_t fRejectTPCPileupWithITSTPCnCluCorr;
  Bool_t fParticleFromOutOfBunchPileupCollision; //injected pileup for LHC20e3a PbPb over tracks 
  Bool_t fPileupInGeneratedEvent; //injected pileup for LHC20e3a PbPb over events
  Bool_t fMVPlp;           ///< multi-vertex pileup rejection?
  Bool_t fOutOfBunchPlp;   ///out-of-bunch pileup rejection
  Bool_t fOOBV0TPC;        /// Switch on/off the strong OOB pileup cut (for Pb-Pb) based on TPC tracks vs V0 mult
  Int_t fMinVtxContr;      ///< no of contributors for pA 2013 data
  Int_t fMinPlpContribMV;  ///< no of contributors for multivertex pile-up rejection
  Int_t fMinPlpContribSPD; ///< no of contributors for SPD pile-up rejection
  Int_t fDCAglobalTrack;  ///< to get DCA from global tracks instead of TPC-only
  Bool_t fFlatCent;        ///< Boolean determining if the user should flatten the centrality
  Bool_t fPrimaryVertexCorrectionTPCPoints; ///< Boolean determining if the reader should shift all TPC points to be relative to event vertex
  Double_t fShiftPosition; ///< radius at which the spatial position of the track in the shifted coordinate system is calculated
  TH1D *f1DcorrectionsPions;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsKaons;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsProtons;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsPionsMinus;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsKaonsMinus;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsProtonsMinus;    ///<file with corrections, pT dependant
  //
  TH1D *f1DcorrectionsDeuterons;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsTritons;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsHe3s;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsAlphas;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsDeuteronsMinus;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsTritonsMinus;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsHe3sMinus;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsAlphasMinus;    ///<file with corrections, pT dependant
  //
  TH1D *f1DcorrectionsAll;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsLambdas;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsLambdasMinus;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsK0s;
  TH1D *f1DcorrectionsXiPlus;    ///<file with corrections, pT dependant
  TH1D *f1DcorrectionsXiMinus;    ///<file with corrections, pT dependant

  THnSparse *f4DcorrectionsPions;    ///<file with corrections, pT dependant
  THnSparse *f4DcorrectionsKaons;    ///<file with corrections, pT dependant
  THnSparse *f4DcorrectionsProtons;    ///<file with corrections, pT dependant
  THnSparse *f4DcorrectionsPionsMinus;    ///<file with corrections, pT dependant
  THnSparse *f4DcorrectionsKaonsMinus;    ///<file with corrections, pT dependant
  THnSparse *f4DcorrectionsProtonsMinus;    ///<file with corrections, pT dependant
  THnSparse *f4DcorrectionsAll;    ///<file with corrections, pT dependant
  THnSparse *f4DcorrectionsLambdas;    ///<file with corrections, pT dependant
  THnSparse *f4DcorrectionsLambdasMinus;    ///<file with corrections, pT dependant

  //Special MC analysis for pi,K,p,e slected by PDG code -->
  Bool_t fIsKaonAnalysis; // switch for Kaon analysis
  Bool_t fIsProtonAnalysis; // switch for Proton analysis
  Bool_t fIsPionAnalysis; // switch for Pion analysis
  Bool_t fIsElectronAnalysis; // e+e- are taken (for gamma cut tuning)
  //Special MC analysis for pi,K,p,e slected by PDG code <--
  Bool_t fExtendV0MAcceptance; //switch centrality estimation
  //
  Bool_t fIsDeuteronAnalysis;
  Bool_t fIsTritonAnalysis;
  Bool_t fIsHe3Analysis;
  Bool_t fIsAlphaAnalysis;
  //
  Int_t frejeEv15o;
  Int_t HMpp;
float HMcut;

#ifdef __ROOT__
  /// \cond CLASSIMP
  ClassDef(AliFemtoEventReaderAOD, 36);
  /// \endcond
#endif

};


inline void AliFemtoEventReaderAOD::SetReadFullMCData(bool read)
  { fReadFullMCData = read; }

inline bool AliFemtoEventReaderAOD::GetReadFullMCData() const
  { return fReadFullMCData; }

#endif
