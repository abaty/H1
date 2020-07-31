#ifndef MULTTOOL
#define MULTTOOL

#include <vector>


class MultTool{
  
public:

  static const int nMultBins = 39;
  static constexpr int multBinLowerBoundary[nMultBins] = {2, 6, 10, 15, 20, 0, 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34};
  static constexpr int multBinUpperBoundary[nMultBins] = {6, 10, 15, 20, 999, 999, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};

  bool matchingMults( int multSig, int multBkg);
  std::vector< int > getGoodTracks( H1Tree * t );
  std::vector< int > getMultBins( int mult );
};

bool MultTool::matchingMults( int multSig, int multBkg){
  if(multSig < 25){
    if(multSig == multBkg) return true;
    else return false;
  }
  if(multSig<30){
    if(multSig == multBkg || multSig == multBkg+1 || multSig == multBkg-1) return true;
    else return false;
  }
  if(multSig>=30){
    if(multBkg>=30) return true;
    else return false;
  }
  return false;
}

std::vector< int > MultTool::getGoodTracks( H1Tree * t ){
  std::vector< int > goodTracks;
  for( int j = 0; j < t->nRECtrack_mini; j++){
    if( ! passesTrackSelection( t, j ) ) continue;
    goodTracks.push_back( j );
  }
  
  return goodTracks;
}


std::vector< int > MultTool::getMultBins( int mult ){
  std::vector< int > indexes;

  for(int i = 0; i < nMultBins; i++){
    if( mult >= multBinLowerBoundary[i] && mult < multBinUpperBoundary[i] ) indexes.push_back(i);
  } 
  return indexes;
}

#endif
