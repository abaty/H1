#include <iostream>
#include "include/histTools.h"
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
  const int nBinsdEta = 2*28;
  const int nBinsdPhi = 2*28;
  const float maxdEta =  2.8;
  float differentialElement = 2*maxdEta/nBinsdEta * 2 * TMath::Pi() / nBinsdPhi;
  TFile * out = TFile::Open("output.root","Recreate");
  TH2D * twoParticleCorrSig[mt.nMultBins];
  TH2D * twoParticleCorrBkg[mt.nMultBins];
  TH2D * twoParticleCorrRat[mt.nMultBins];
  for( int i = 0; i<mt.nMultBins; i++){
    twoParticleCorrSig[i] = new TH2D(Form("twoParticleCorrSig_%d_%d",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]),"",nBinsdEta, -maxdEta, maxdEta, nBinsdPhi, -1*TMath::Pi()/2.0, 3*TMath::Pi()/2.0); 
    twoParticleCorrBkg[i] = new TH2D(Form("twoParticleCorrBkg_%d_%d",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]),"",nBinsdEta, -maxdEta, maxdEta, nBinsdPhi, -1*TMath::Pi()/2.0, 3*TMath::Pi()/2.0); 
  }
  float nEventsPerMult[ mt.nMultBins ] = {0};

  //event loop
  for(int i = 0; i<inputTree->GetEntries(); i++){
    timer.StartSplit("Loading Entries");
  //for(int i = 0; i<500000; i++){
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
    for( int b = 0; b<multBins.size(); b++)  nEventsPerMult[ multBins[b] ] += eventWeight; 

    //signal loop over all pairs
    timer.StartSplit("Signal Correlations");
    for( int j = 0; j < goodTrks.size() ; j++){
      for(int k = j+1; k < goodTrks.size(); k++){
        float dEta = TMath::Abs( t.etaREC_mini[ goodTrks[j] ] - t.etaREC_mini[goodTrks[k] ] );
        float dPhi = TMath::ACos( TMath::Cos( t.phiREC_mini[ goodTrks[j] ] - t.phiREC_mini[ goodTrks[k] ] ) );
 
        for( int b = 0; b<multBins.size(); b++)  mirroredTPCFill( twoParticleCorrSig[ multBins[b] ], dEta, dPhi, eventWeight / differentialElement / mult); 
      }
    }

    //search for a mix event (ugly here)
    int mixOffset = 1;
    std::vector< int > goodTrksMix;
    timer.StartSplit("Looking for a mixed event");
    while(true){
      bool isValidMix = true;
      tMix.GetEntry(i + mixOffset);

      if( !passesEventSelection( &tMix ) ) isValidMix = false;
      else goodTrksMix = mt.getGoodTracks( &tMix );
      
      int multMix = goodTrksMix.size();
      if( multMix < 2 ) isValidMix = false;

      if( isValidMix && mt.matchingMults( mult, multMix) ) break;

      mixOffset++;
      if( i + mixOffset == inputTreeMix->GetEntries() ) mixOffset = -i;//need to go back to beginning of file
      if(mixOffset == -1){
        std::cout << "Warning! No Mixed event found!" << std::endl;
        break;//no event found, break infinite loop and just take the previous event
      }
    } 

    
    timer.StartSplit("Mixed Event Correlations");
    for( int j = 0; j < goodTrks.size() ; j++){
      for(int k = 0; k < goodTrksMix.size(); k++){
        float dEta = TMath::Abs( t.etaREC_mini[ goodTrks[j] ] - tMix.etaREC_mini[goodTrksMix[k] ] );
        float dPhi = TMath::ACos( TMath::Cos( t.phiREC_mini[ goodTrks[j] ] - tMix.phiREC_mini[ goodTrksMix[k] ] ) );
  
        for( int b = 0; b<multBins.size(); b++)  mirroredTPCFill( twoParticleCorrBkg[ multBins[b] ], dEta, dPhi, eventWeight / differentialElement / mult);
      }
    }

  }
  timer.StartSplit("Writing output file");

  for( int i = 0; i<mt.nMultBins; i++){
    twoParticleCorrSig[i]->Scale(1.0/nEventsPerMult[i]);
    twoParticleCorrBkg[i]->Scale(1.0/nEventsPerMult[i]);
    
    twoParticleCorrRat[i] = (TH2D*) twoParticleCorrSig[i]->Clone(Form("twoParticleCorrRat_%d_%d",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]));
    twoParticleCorrRat[i]->Divide(twoParticleCorrBkg[i]);
    twoParticleCorrRat[i]->Scale(twoParticleCorrBkg[i]->GetBinContent(twoParticleCorrBkg[i]->FindBin(0,0)));
  }

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
