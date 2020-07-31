#include <iostream>
#include <string>
#include <vector>
#include "include/Timer.h"
#include "include/H1Tree.h"
#include "include/trackSelection.h"
#include "include/eventSelection.h"
#include "include/multTool.h"
#include "TH1D.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"

void SampleAnalyzer(){
  //Some stuff for analyzering the time the code takes to run (optional)
  Timer timer = Timer();
  timer.Start();
  timer.StartSplit("Start Up");
  TH1::SetDefaultSumw2();
 
  //needed for applying track cuts... 
  MultTool mt = MultTool();
 
  //loading file and setting up tree
  //argument of TFile will have to change depending on where you store the data....
  TFile * input = TFile::Open("/home/aab9/H1/H1SkimTree.root","read");
  TTree * inputTree = (TTree*)input->Get("miniTree");
  H1Tree t = H1Tree(inputTree, false);
  t.ActivateBranches();  

  //make an output file and define some histograms
  TFile * out = TFile::Open("outputFile.root","recreate");
  TH1D * etaHist = new TH1D("etaHist",";#eta;N",50,-5,5);
  TH1D * phiHist = new TH1D("phiHist",";#phi;N",50,-TMath::Pi(),TMath::Pi());
  TH1D * ptHist =  new TH1D("ptHist",";pT;N",50,0.15,5);

  //event loop
  //use this line to run on the whole file
  //for(int i = 0; i<inputTree->GetEntries(); i++){
  //use this line for testing on 1M events
  for(int i = 0; i<1000000; i++){
    timer.StartSplit("Loading Entries");
    if(i%100000 == 0) std::cout << "Event: " << i << "/" << inputTree->GetEntries() << std::endl;
    t.GetEntry(i);

    //check event selections and set the event weight (use a Q^2 cut of 5 GeV here but that can be changed)
    timer.StartSplit("Selections");
    float Q2Cut  = 5; 
    if( !passesEventSelection( &t, Q2Cut ) ) continue;
    float eventWeight = t.w_mini;    

    //find all tracks that pass selections and put their index into a vector
    std::vector< int > goodTrks = mt.getGoodTracks( &t );
    
    //loop over all good tracks
    timer.StartSplit("Track Loop");
    for( int j = 0; j < goodTrks.size() ; j++){
      float eta = t.etaREC_mini[ goodTrks[j] ];
      float phi = t.phiREC_mini[ goodTrks[j] ];
      float pt =  t.ptREC_mini[  goodTrks[j] ];

      //fill histograms...
      etaHist->Fill(eta,eventWeight);
      phiHist->Fill(phi,eventWeight);
      ptHist->Fill( pt,eventWeight);

      
      //any analyzer can go here....
      //
      //


    }//close track loop
  }//close event loop
 
  //write output file
  out->Write();

  //timing information (optional)
  timer.Stop();
  timer.Report();
}
