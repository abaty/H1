#ifndef HISTTOOLS
#define HISTTOOLS

#include "TH2D.h"
#include "TMath.h"

void mirroredTPCFill(TH2D * h, float dEta, float dPhi, float weight){

  h->Fill(dEta,dPhi, weight);
  h->Fill(-dEta,dPhi,weight);

  if(dPhi < TMath::Pi()/2.0){
    h->Fill(dEta,-dPhi, weight);
    h->Fill(-dEta,-dPhi,weight);
  }else{
    h->Fill(dEta, 2*TMath::Pi() - dPhi, weight);
    h->Fill(-dEta, 2*TMath::Pi() - dPhi, weight);
  }
}

#endif
