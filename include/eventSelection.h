#ifndef EVENTSELECTION
#define EVENTSELECTION


bool passesEventSelection( H1Tree * t, float QCutMin = 5, float QCutMax = 100 ){

  if( ! t->eventpass_mini ) return false;
  if( t->yREC_es_mini > 0.6 || t->yREC_es_mini < 0.0375 ) return false;
  if( t->nRECtrack_mini < 2 ) return false; 
  if( t->Q2REC_es_mini < QCutMin  || t->Q2REC_es_mini > QCutMax) return false;

  return true;
}

#endif
