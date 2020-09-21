#include "20170175.h"

int* NCounter() {
  int Numbers[10] = {0, };
  int N, i, page;
  scanf("%d", &N);
  for (i=1; i<N+1;i++){
    page=i;
    while(page!=0){
      Numbers[page%10]++;
      page=page/10;
    }
  }
  ResultPrinter(Numbers);
  return Numbers;
}
