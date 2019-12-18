#ifndef TRKSELECTIONS
#define TRKSELECTIONS

#include "H1Tree.h"

bool passesTrackSelection( H1Tree * t , int trkIndx){

  if( ! t->passREC_mini[trkIndx] ) return false;
  if( t->ptREC_mini[trkIndx] < 0.15 ) return false;
  if( t->etaREC_mini[trkIndx] < -1.6 || t->etaREC_mini[trkIndx] > 1.6 ) return false;
  return true;
}

#endif

