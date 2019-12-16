#ifndef MULTTOOL
#define MULTTOOL

#include <vector>

class MultTool{
  
public:

  static const int nMultBins = 6;
  static constexpr int multBinLowerBoundary[nMultBins] = {2, 6, 10, 15, 20, 0};
  static constexpr int multBinUpperBoundary[nMultBins] = {6, 10, 15, 20, 999, 999};

  std::vector< int > getMultBins( int mult );

};

std::vector< int > MultTool::getMultBins( int mult ){
  std::vector< int > indexes;

  for(int i = 0; i < nMultBins; i++){
    if( mult >= multBinLowerBoundary[i] && mult < multBinUpperBoundary[i] ) indexes.push_back(i);
  } 
  return indexes;
}

#endif
