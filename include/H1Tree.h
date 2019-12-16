//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Dec 15 18:28:42 2019 by ROOT version 6.12/07
// from TTree miniTree/miniTree
// found on file: /home/zt7/H1/data_highE_0607_noReweight_Tree_forCorrelation.root
//////////////////////////////////////////////////////////

#ifndef H1Tree_h
#define H1Tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>

// Header file for the classes stored in the TTree if any.

class H1Tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         w_mini;
   Float_t         vertex_mini[3];
   Float_t         yMC_es_mini;
   Float_t         Q2MC_es_mini;
   Float_t         eGammaPhiMC_mini;
   Float_t         phoEpzMC_mini;
   Float_t         sumPtMC_mini;
   Int_t           isQEDComptonMC_mini;
   Int_t           nMCtrack_mini;
   Float_t         pxMC_mini[1];   //[nMCtrack_mini]
   Float_t         pyMC_mini[1];   //[nMCtrack_mini]
   Float_t         pzMC_mini[1];   //[nMCtrack_mini]
   Float_t         etaMC_mini[1];   //[nMCtrack_mini]
   Float_t         ptStarMC_mini[1];   //[nMCtrack_mini]
   Float_t         etaStarMC_mini[1];   //[nMCtrack_mini]
   Int_t           totalMultMC_mini;
   Float_t         hfsEREC_mini;
   Float_t         hfsPtREC_mini;
   Float_t         hfsPzREC_mini;
   Float_t         elecEREC_mini;
   Float_t         elecPtREC_mini;
   Float_t         elecPzREC_mini;
   Int_t           elecChargeREC_mini;
   Float_t         xREC_es_mini;
   Float_t         yREC_es_mini;
   Float_t         Q2REC_es_mini;
   Int_t           eventpass_mini;
   Int_t           eventpassTight_mini;
   Int_t           eventpassLoose_mini;
   Int_t           nRECtrack_mini;
   Float_t         EpzREC_mini;
   Int_t           totalMultREC_mini;
   Float_t         eElectronBeam_mini;
   Float_t         pxREC_mini[58];   //[nRECtrack_mini]
   Float_t         pyREC_mini[58];   //[nRECtrack_mini]
   Float_t         ptREC_mini[58];   //[nRECtrack_mini] not a tree branch, updated in GetEntry
   Float_t         pzREC_mini[58];   //[nRECtrack_mini]
   Float_t         etaREC_mini[58];   //[nRECtrack_mini]
   Float_t         phiREC_mini[58];   //[nRECtrack_mini]
   Float_t         ptStarREC_mini[58];   //[nRECtrack_mini]
   Float_t         etaStarREC_mini[58];   //[nRECtrack_mini]
   Float_t         phiStarREC_mini[58];   //[nRECtrack_mini]
   Float_t         nucliaREC_mini[58];   //[nRECtrack_mini]
   Int_t           passREC_mini[58];   //[nRECtrack_mini]
   Int_t           passTightREC_mini[58];   //[nRECtrack_mini]
   Int_t           passLooseREC_mini[58];   //[nRECtrack_mini]

   // List of branches
   TBranch        *b_w_mini;   //!
   TBranch        *b_vertex_mini;   //!
   TBranch        *b_yMC_es_mini;   //!
   TBranch        *b_Q2MC_es_mini;   //!
   TBranch        *b_eGammaPhiMC_mini;   //!
   TBranch        *b_phoEpzMC_mini;   //!
   TBranch        *b_sumPtMC_mini;   //!
   TBranch        *b_isQEDComptonMC_mini;   //!
   TBranch        *b_nMCtrack_mini;   //!
   TBranch        *b_pxMC_mini;   //!
   TBranch        *b_pyMC_mini;   //!
   TBranch        *b_pzMC_mini;   //!
   TBranch        *b_etaMC_mini;   //!
   TBranch        *b_ptStarMC_mini;   //!
   TBranch        *b_etaStarMC_mini;   //!
   TBranch        *b_totalMultMC_mini;   //!
   TBranch        *b_hfsEREC_mini;   //!
   TBranch        *b_hfsPtREC_mini;   //!
   TBranch        *b_hfsPzREC_mini;   //!
   TBranch        *b_elecEREC_mini;   //!
   TBranch        *b_elecPtREC_mini;   //!
   TBranch        *b_elecPzREC_mini;   //!
   TBranch        *b_elecChargeREC_mini;   //!
   TBranch        *b_xREC_es_mini;   //!
   TBranch        *b_yREC_es_mini;   //!
   TBranch        *b_Q2REC_es_mini;   //!
   TBranch        *b_eventpass_mini;   //!
   TBranch        *b_eventpassTight_mini;   //!
   TBranch        *b_eventpassLoose_mini;   //!
   TBranch        *b_nRECtrack_mini;   //!
   TBranch        *b_EpzREC_mini;   //!
   TBranch        *b_totalMultREC_mini;   //!
   TBranch        *b_eElectronBeam_mini;   //!
   TBranch        *b_pxREC_mini;   //!
   TBranch        *b_pyREC_mini;   //!
   TBranch        *b_pzREC_mini;   //!
   TBranch        *b_etaREC_mini;   //!
   TBranch        *b_phiREC_mini;   //!
   TBranch        *b_ptStarREC_mini;   //!
   TBranch        *b_etaStarREC_mini;   //!
   TBranch        *b_phiStarREC_mini;   //!
   TBranch        *b_nucliaREC_mini;   //!
   TBranch        *b_passREC_mini;   //!
   TBranch        *b_passTightREC_mini;   //!
   TBranch        *b_passLooseREC_mini;   //!

   H1Tree(TTree *tree=0);
   virtual ~H1Tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
//   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

H1Tree::H1Tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/zt7/H1/data_highE_0607_noReweight_Tree_forCorrelation.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/zt7/H1/data_highE_0607_noReweight_Tree_forCorrelation.root");
      }
      f->GetObject("miniTree",tree);

   }
   Init(tree);
}

H1Tree::~H1Tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t H1Tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   Int_t returnValue = fChain->GetEntry(entry); 

   for(int i = 0; i<nRECtrack_mini; i++){
     ptREC_mini[i] = TMath::Sqrt( pxREC_mini[i] * pxREC_mini[i] + pyREC_mini[i] * pyREC_mini[i] );
   }

   return returnValue;
}
Long64_t H1Tree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void H1Tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("w_mini", &w_mini, &b_w_mini);
   fChain->SetBranchAddress("vertex_mini", vertex_mini, &b_vertex_mini);
   fChain->SetBranchAddress("yMC_es_mini", &yMC_es_mini, &b_yMC_es_mini);
   fChain->SetBranchAddress("Q2MC_es_mini", &Q2MC_es_mini, &b_Q2MC_es_mini);
   fChain->SetBranchAddress("eGammaPhiMC_mini", &eGammaPhiMC_mini, &b_eGammaPhiMC_mini);
   fChain->SetBranchAddress("phoEpzMC_mini", &phoEpzMC_mini, &b_phoEpzMC_mini);
   fChain->SetBranchAddress("sumPtMC_mini", &sumPtMC_mini, &b_sumPtMC_mini);
   fChain->SetBranchAddress("isQEDComptonMC_mini", &isQEDComptonMC_mini, &b_isQEDComptonMC_mini);
   fChain->SetBranchAddress("nMCtrack_mini", &nMCtrack_mini, &b_nMCtrack_mini);
   fChain->SetBranchAddress("pxMC_mini", &pxMC_mini, &b_pxMC_mini);
   fChain->SetBranchAddress("pyMC_mini", &pyMC_mini, &b_pyMC_mini);
   fChain->SetBranchAddress("pzMC_mini", &pzMC_mini, &b_pzMC_mini);
   fChain->SetBranchAddress("etaMC_mini", &etaMC_mini, &b_etaMC_mini);
   fChain->SetBranchAddress("ptStarMC_mini", &ptStarMC_mini, &b_ptStarMC_mini);
   fChain->SetBranchAddress("etaStarMC_mini", &etaStarMC_mini, &b_etaStarMC_mini);
   fChain->SetBranchAddress("totalMultMC_mini", &totalMultMC_mini, &b_totalMultMC_mini);
   fChain->SetBranchAddress("hfsEREC_mini", &hfsEREC_mini, &b_hfsEREC_mini);
   fChain->SetBranchAddress("hfsPtREC_mini", &hfsPtREC_mini, &b_hfsPtREC_mini);
   fChain->SetBranchAddress("hfsPzREC_mini", &hfsPzREC_mini, &b_hfsPzREC_mini);
   fChain->SetBranchAddress("elecEREC_mini", &elecEREC_mini, &b_elecEREC_mini);
   fChain->SetBranchAddress("elecPtREC_mini", &elecPtREC_mini, &b_elecPtREC_mini);
   fChain->SetBranchAddress("elecPzREC_mini", &elecPzREC_mini, &b_elecPzREC_mini);
   fChain->SetBranchAddress("elecChargeREC_mini", &elecChargeREC_mini, &b_elecChargeREC_mini);
   fChain->SetBranchAddress("xREC_es_mini", &xREC_es_mini, &b_xREC_es_mini);
   fChain->SetBranchAddress("yREC_es_mini", &yREC_es_mini, &b_yREC_es_mini);
   fChain->SetBranchAddress("Q2REC_es_mini", &Q2REC_es_mini, &b_Q2REC_es_mini);
   fChain->SetBranchAddress("eventpass_mini", &eventpass_mini, &b_eventpass_mini);
   fChain->SetBranchAddress("eventpassTight_mini", &eventpassTight_mini, &b_eventpassTight_mini);
   fChain->SetBranchAddress("eventpassLoose_mini", &eventpassLoose_mini, &b_eventpassLoose_mini);
   fChain->SetBranchAddress("nRECtrack_mini", &nRECtrack_mini, &b_nRECtrack_mini);
   fChain->SetBranchAddress("EpzREC_mini", &EpzREC_mini, &b_EpzREC_mini);
   fChain->SetBranchAddress("totalMultREC_mini", &totalMultREC_mini, &b_totalMultREC_mini);
   fChain->SetBranchAddress("eElectronBeam_mini", &eElectronBeam_mini, &b_eElectronBeam_mini);
   fChain->SetBranchAddress("pxREC_mini", pxREC_mini, &b_pxREC_mini);
   fChain->SetBranchAddress("pyREC_mini", pyREC_mini, &b_pyREC_mini);
   fChain->SetBranchAddress("pzREC_mini", pzREC_mini, &b_pzREC_mini);
   fChain->SetBranchAddress("etaREC_mini", etaREC_mini, &b_etaREC_mini);
   fChain->SetBranchAddress("phiREC_mini", phiREC_mini, &b_phiREC_mini);
   fChain->SetBranchAddress("ptStarREC_mini", ptStarREC_mini, &b_ptStarREC_mini);
   fChain->SetBranchAddress("etaStarREC_mini", etaStarREC_mini, &b_etaStarREC_mini);
   fChain->SetBranchAddress("phiStarREC_mini", phiStarREC_mini, &b_phiStarREC_mini);
   fChain->SetBranchAddress("nucliaREC_mini", nucliaREC_mini, &b_nucliaREC_mini);
   fChain->SetBranchAddress("passREC_mini", passREC_mini, &b_passREC_mini);
   fChain->SetBranchAddress("passTightREC_mini", passTightREC_mini, &b_passTightREC_mini);
   fChain->SetBranchAddress("passLooseREC_mini", passLooseREC_mini, &b_passLooseREC_mini);
   Notify();
}

Bool_t H1Tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void H1Tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t H1Tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif 
