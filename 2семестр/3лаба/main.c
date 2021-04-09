#include <stdio.h>
#include <string.h>

int main(void) {
  char str1[128];
  char str2[128];

  char resulting_str[256];

  // пункт 4.1
  printf("Введите первую строку: ");
  scanf("%[^\n]%*c", str1);

  
  printf("Введите вторую строку: ");
  scanf("%[^\n]%*c", str2);

  //пункт 4.2
  char str1_len = 0, str2_len = 0;
  for (;*(str1+ ++str1_len););
  for (;(++str2_len)[str2];);

  printf("Длина первой строки: %d\n", str1_len);
  printf("Длина второй строки: %d\n", str2_len);

  //пункт 4.3
  char *s1 = str1, *s2 = str2, *r = resulting_str;
  do {} while (((*r++)=(*s1?* (s1++):* (s2++))) !=' '?* (r- 1):* (--r));
  printf("Обьединённая строка без пробелов: %s\n", resulting_str);

  //пункт 4.4
  char с = 0;
  r = resulting_str;

  while (*(r+   1)== *r?* (r+1)&&(* (r++)='+')&&(++с)&&( с^4):* (r++));

  //пункт 4.5
  printf("Итоговая обработанная строка: %s\n", resulting_str);

  return 0;
}
