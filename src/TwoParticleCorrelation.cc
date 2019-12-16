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
  MultTool mt = MultTool();
  
  //loading file and setting up tree
  TFile * input = TFile::Open("/home/aab9/H1/H1SkimTree.root","read");
  TTree * inputTree = (TTree*)input->Get("miniTree");
  H1Tree t = H1Tree(inputTree, false);
  t.ActivateBranches();  

  //separate structure for mixed events
  TFile * inputMix = TFile::Open("/home/aab9/H1/H1SkimTree.root","read");
  TTree * inputTreeMix = (TTree*)inputMix->Get("miniTree");
  H1Tree tMix = H1Tree(inputTreeMix, false);
  tMix.ActivateBranches();  

  //Setting up some output stuff
  TFile * out = TFile::Open("output.root","Recreate");
  TH2D * twoParticleCorrSig[mt.nMultBins];
  TH2D * twoParticleCorrBkg[mt.nMultBins];
  for( int i = 0; i<mt.nMultBins; i++){
    twoParticleCorrSig[i] = new TH2D(Form("twoParticleCorrSig_%d_%d",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]),"",28, 0, 2.8, 28, 0, TMath::Pi()); 
    twoParticleCorrBkg[i] = new TH2D(Form("twoParticleCorrBkg_%d_%d",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]),"",28, 0, 2.8, 28, 0, TMath::Pi()); 
  }

  //event loop
  timer.StartSplit("Loading Entries");
  //for(int i = 0; i<inputTree->GetEntries(); i++){
  for(int i = 0; i<40000; i++){
    if(i%100000 == 0) std::cout << "Event: " << i << "/" << inputTree->GetEntries() << std::endl;
    t.GetEntry(i);

    //check event selections
    timer.StartSplit("Selections");
    if( !passesEventSelection( &t ) ) continue;
    float eventWeight = t.w_mini;    

    //find all tracks that pass selections and put their index into a vector
    std::vector< int > goodTrks = mt.getGoodTracks( &t );
    
    //do some bookkeeping with the multiplicity, including the vector of mult histograms to fill 
    int mult = goodTrks.size();
    if( mult < 2 ) continue;
    std::vector< int > multBins = mt.getMultBins( mult );

    //signal loop over all pairs
    timer.StartSplit("Signal Correlations");
    for( int j = 0; j < goodTrks.size() ; j++){
      for(int k = j+1; k < goodTrks.size(); k++){
        float dEta = TMath::Abs( t.etaREC_mini[ goodTrks[j] ] - t.etaREC_mini[goodTrks[k] ] );
        float dPhi = TMath::ACos( TMath::Cos( t.phiREC_mini[ goodTrks[j] ] - t.phiREC_mini[ goodTrks[k] ] ) );
 
        for( int b = 0; b<multBins.size(); b++)  twoParticleCorrSig[ multBins[b] ]->Fill( dEta, dPhi, eventWeight); 
      }
    }

    //search for a mix event (ugly here)
    int mixOffset = 1;
    std::vector< int > goodTrksMix = std::vector< int >();
    timer.StartSplit("Looking for a mixed event");
    while(true){
      bool isValidMix = true;
      tMix.GetEntry(i + mixOffset);

      if(i%1000 == 0) std::cout << i << " " << i+mixOffset << " " << mult << std::endl;

      if( !passesEventSelection( &tMix ) ) isValidMix = false;
      else goodTrksMix = mt.getGoodTracks( &tMix );
      
      int multMix = goodTrksMix.size();
      if( multMix < 2 ) isValidMix = false;

      if( isValidMix && mt.matchingMults( mult, multMix) ) break;

      mixOffset++;
      if( i + mixOffset > inputTreeMix->GetEntries() ) mixOffset = -i;//need to go back to beginning of file
      if(mixOffset == 0){
        std::cout << "Warning! No Mixed event found!" << std::endl;
        break;//no event found, break infinite loop and just take the next event
      }
    } 

    timer.StartSplit("Mixed Event Correlations");
    for( int j = 0; j < goodTrks.size() ; j++){
      for(int k = 0; k < goodTrksMix.size(); k++){
        float dEta = TMath::Abs( t.etaREC_mini[ goodTrks[j] ] - tMix.etaREC_mini[goodTrks[k] ] );
        float dPhi = TMath::ACos( TMath::Cos( t.phiREC_mini[ goodTrks[j] ] - tMix.phiREC_mini[ goodTrks[k] ] ) );
 
        for( int b = 0; b<multBins.size(); b++)  twoParticleCorrBkg[ multBins[b] ]->Fill( dEta, dPhi, eventWeight); 
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
