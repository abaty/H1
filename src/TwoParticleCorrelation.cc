#include <iostream>
#include "include/trackSelection.h"
#include "include/eventSelection.h"
#include "include/multTool.h"
#include "include/H1Tree.h"
#include "include/Timer.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"

void twoParticleCorrelation(){
  Timer timer = Timer();
  timer.Start();
  timer.StartSplit("Start Up");
  TH1::SetDefaultSumw2();
  
  //loading file and setting up tree
  TFile * input = TFile::Open("/home/zt7/H1/data_highE_0607_noReweight_Tree_forCorrelation.root","read");
  TTree * inputTree = (TTree*)input->Get("miniTree");
  H1Tree t = H1Tree(inputTree, false);
  t.ActivateBranches();  
  MultTool mt = MultTool();

  //Setting up some output stuff
  TFile * out = TFile::Open("output.root","Recreate");
  
  TH2D * twoParticleCorr[mt.nMultBins];
  for( int i = 0; i<mt.nMultBins; i++){
    twoParticleCorr[i] = new TH2D(Form("twoParticleCorr_%d_%d",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]),"",28, 0, 2.8, 28, 0, TMath::Pi()); 
  }

  //event loop
  timer.StartSplit("Loading Entries");
  //for(int i = 0; i<inputTree->GetEntries(); i++){
  for(int i = 0; i<500000; i++){
    if(i%100000 == 0) std::cout << "Event: " << i << "/" << inputTree->GetEntries() << std::endl;
    t.GetEntry(i);

    //check event selections
    timer.StartSplit("Selections");
    if( !passesEventSelection( &t ) ) continue;
    float eventWeight = t.w_mini;    

    //find all tracks that pass selections and put their index into a vector
    std::vector< int > goodTrks;
    for( int j = 0; j < t.nRECtrack_mini; j++){
      if( ! passesTrackSelection( &t, j ) ) continue;
      goodTrks.push_back( j );
    }
  
    int mult = goodTrks.size();
    if( mult < 2 ) continue;
    std::vector< int > multBins = mt.getMultBins( mult );

    //signal loop over all pairs
    timer.StartSplit("Signal Correlations");
    for( int j = 0; j < goodTrks.size() ; j++){
      for(int k = j+1; k < goodTrks.size(); k++){
        float dEta = TMath::Abs( t.etaREC_mini[ goodTrks[j] ] - t.etaREC_mini[goodTrks[k] ] );
        float dPhi = TMath::ACos( TMath::Cos( t.phiREC_mini[ goodTrks[j] ] - t.phiREC_mini[ goodTrks[k] ] ) );
 
        for( int b = 0; b<multBins.size(); b++)  twoParticleCorr[ multBins[b] ]->Fill( dEta, dPhi, eventWeight); 
      }
    }

  }
  timer.StartSplit("Writing output file");
  out->Write();

  timer.Stop();
  timer.Report();
}

int main(int argc, const char* argv[]){

  twoParticleCorrelation();

  /*
  if(argc != 4)
  {
    std::cout << "Usage: HGPythia <nEvents> <jobNumber> <outputName>" << std::endl;
    return 1;
  }  

  int nEvents = std::atoi(argv[1]); 
  int RNGoffset = std::atoi(argv[2]); 
  std::string outputName = argv[3];
  */

  return 1;
}
