#include <stdio.h>
#include<math.h>
int main() {
  int n = 0;//項數
  int sum=0;
  int sign = 1;
for(n=0;;n++){
  sign=-sign;
  sum = sum + 4/(2*n-1);
  if(3.14159<sum<3.1416){
  break;
}
  printf("%d\n",n);
}
    return 0;
}
