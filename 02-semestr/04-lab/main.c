#include <stdio.h>
#include <string.h>
#include <limits.h>

short inp_str(char *str, short maxlen){
  scanf("%s", str);
  return (short)strlen(str);
}

void out_str(char strs[][CHAR_MAX], short len, short number){
  printf("%d - %s\n", number, strs[number]);
}

void swap(char strs[][CHAR_MAX], short strsLen, short *swaps, short *biggestStrLen) {
  for (char i = 0; i < strsLen - 1; i++) {
    for (char j = 0; j < strsLen - 1; j++) {
      if (strlen(strs[j]) < strlen(strs[j+1])) {
        char buffer[CHAR_MAX];
        strcpy(buffer, strs[j]);
        strcpy(strs[j], strs[j+1]);
        strcpy(strs[j+1], buffer);
        *swaps = *swaps + 1;
      }
    }
  }
  *biggestStrLen = strlen(strs[0]);
}

int main(void){
  const short strsLen = 3;

  char strs[strsLen][CHAR_MAX];
  char strsLens[strsLen];

  for(short i = 0; i < strsLen; i++){
    strsLens[i] = inp_str(strs[i], CHAR_MAX);
  }

  short swaps = 0;
  short biggestStrLen = 0;
  swap(strs, strsLen, &swaps, &biggestStrLen);

  printf("Sorted with %d swaps. Length of longest string is %d.\n", swaps, biggestStrLen);

  for(short i = 0; i < strsLen; i++){
    out_str(strs, strlen(strs[i]), i);
  }
}
