#ifndef EVENTSELECTION
#define EVENTSELECTION

#include "include/H1Tree.h"

bool passesEventSelection( H1Tree * t ){

  if( ! t->eventpass_mini ) return false;
  if( t->nRECtrack_mini < 2 ) return false; 
  if( t->Q2REC_es_mini < 5 ) return false;

  return true;
}

#endif
