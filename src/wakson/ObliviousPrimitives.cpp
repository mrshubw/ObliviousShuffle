
#ifndef BEFTS_MODE
  #include <cstdint>
  #include <stddef.h>
  #include "wakson/oasm_lib.h"
  #include "wakson/ObliviousPrimitives.hpp"
#endif

/* 
void TightCompact_v2(unsigned char *buffer, size_t N, size_t block_size, bool *selected_list) {
  if(block_size==8){
    TightCompact<OSWAP_8>(buffer, N, block_size, selected_list);
  }
  else if(block_size%16==0){
    //isCorrect16x(256);
    TightCompact<OSWAP_16X>(buffer, N, block_size, selected_list);
  } 
  else{
    //isCorrect8_16x(24);
    TightCompact<OSWAP_8_16X>(buffer, N, block_size, selected_list);
  } 
}


void TightCompact_v2_parallel(unsigned char *buffer, size_t N, size_t block_size, bool *selected_list, size_t nthreads) {
  if(block_size==8){
    TightCompact_parallel<OSWAP_8>(buffer, N, block_size, selected_list, nthreads);
  }
  else if(block_size%16==0){
    //isCorrect16x(256);
    TightCompact_parallel<OSWAP_16X>(buffer, N, block_size, selected_list, nthreads);
  }
  else{
    //isCorrect8_16x(24);
    TightCompact_parallel<OSWAP_8_16X>(buffer, N, block_size, selected_list, nthreads);
  }
}
 */
#ifndef BEFTS_MODE
void OP_TightCompact_v2(unsigned char *buffer, size_t N, size_t block_size, bool *selected_list) {
  if(block_size==8){
    OP_TightCompact<OSWAP_8>(buffer, N, block_size, selected_list);
  }
  else if(block_size%16==0){
    OP_TightCompact<OSWAP_16X>(buffer, N, block_size, selected_list);
  } 
  else{
    OP_TightCompact<OSWAP_8_16X>(buffer, N, block_size, selected_list);
  } 
}
#endif
