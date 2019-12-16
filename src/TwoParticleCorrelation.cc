#include <iostream>
#include "include/trackSelection.h"
#include "include/eventSelection.h"
#include "include/H1Tree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"

void twoParticleCorrelation(){
  TH1::SetDefaultSumw2();
  
  //loading file and setting up tree
  TFile * input = TFile::Open("/home/zt7/H1/data_highE_0607_noReweight_Tree_forCorrelation.root","read");
  TTree * inputTree = (TTree*)input->Get("miniTree");
  H1Tree t = H1Tree(inputTree);

  //event loop
  //for(int i = 0; i<inputTree->GetEntries(); i++){
  for(int i = 0; i<100; i++){
    t.GetEntry(i);

    if( !passesEventSelection( &t ) ) continue;
    
    //track loop
    for( int j = 0; j < t.nRECtrack_mini; j++){
      if( ! passesTrackSelection( &t, j ) ) continue;
    }
  }
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
