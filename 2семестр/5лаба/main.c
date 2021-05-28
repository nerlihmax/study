/* пункт 1
#include <stdio.h>
#include <limits.h>

const unsigned char dbSize = 3;
const unsigned char string_size = CHAR_MAX;

struct detail {
  char name[string_size];
  unsigned short year;
  unsigned int price;
  unsigned int count;
};

int main(void) {
  struct detail db[dbSize];

  for (int i = 0; i < dbSize; i++) {
    struct detail d;

    printf("Введите название детали, год выпуска, цену, количество\n");
    scanf("%s %d %d %d", &d.name, &d.year, &d.price, &d.count);
    
    db[i] = d;
  }

  for (int i = 0; i < dbSize; i++) {
    printf("Название детали %s\n", db[i].name);
    printf("Год выпуска %d\n", db[i].year);
    printf("Цена %d\n", db[i].price);
    printf("Количество %d\n", db[i].count);
    printf("\n\n");
  }
  
  return 0;
}
*/

/* пункт 2
#include <stdio.h>
#include <limits.h>

const unsigned char dbSize = 3;
const unsigned char string_size = CHAR_MAX;

struct detail {
  char name[string_size];
  unsigned short year;
  unsigned int price;
  unsigned int count;
};

int main(void) {
  struct detail **db = malloc(sizeof(struct detail*) * dbSize);

  for (int i = 0; i < dbSize; i++) {
    struct detail *d = malloc(sizeof(struct detail));

    printf("Введите название детали, год выпуска, цену, количество\n");
    scanf("%s %d %d %d", &d->name, &d->year, &d->price, &d->count);
    
    db[i] = d;
  }

  for (char i = 0; i < dbSize - 1; i++) {
    for (char j = 0; j < dbSize - 1; j++) {
      if (db[j]->price > db[j+1]->price) {
        struct detail *buffer = db[j];
        db[j] = db[j+1];
        db[j+1] = buffer;
      }
    }
  }

  for (int i = 0; i < dbSize; i++) {
    printf("Название детали %s\n", db[i]->name);
    printf("Год выпуска %d\n", db[i]->year);
    printf("Цена %d\n", db[i]->price);
    printf("Количество %d\n", db[i]->count);
    printf("\n\n");
  }
  
  return 0;
}
*/
