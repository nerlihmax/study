// пункт 4.1
#include <stdio.h>

int main() {
    char a[128];
    scanf("%s", a);

    printf("задание 1\n");
    int i = 0;
    char c = a[i];

    loop1:
        if (c >= 65 && c <= 90) {
            c -= 'A' - 'a';
        }
        printf("%c", c);
        i++;
        if ((c = a[i]) != 0) goto loop1;

    printf("\n");

    printf("\nзадание2\n");
    i = 0;
    c = a[i];
    loop2:
        if (c >= 65 && c <= 90) {
            c -= 'A' - 'a';
        }
        if (c == 'a') {
            c = 'e';
        }
        if (c == 'b') {
            c = 'k';
        }
        if (c == 'x') {
            c = 'm';
        }
        if (c == 'z') {
            c = 'p';
        }
        printf("%c", c);
        i++;
        if ((c = a[i]) != 0) goto loop2;
}

//пункт 4.2
#include <stdio.h>

int main() {
    char a[128];
    scanf("%s", a);

    printf("задание 1\n");
    int i = 0;
    char c = a[i];
    loop1:
        if (c >= 65 && c <= 90) {
            c -= 'A' - 'a';
        }
        printf("%c", c);
        i++;
        if ((c = a[i]) != 0) goto loop1;

    printf("\n");

    printf("\nзадание2\n");
    i = 0;
    c = a[i];
    loop2:
        if (c >= 65 && c <= 90) {
            c -= 'A' - 'a';
        }
        else if (c == 'a') {
            c = 'e';
        }
        else if (c == 'b') {
            c = 'k';
        }
        else if (c == 'x') {
            c = 'm';
        }
        else if (c == 'z') {
            c = 'p';
        }
        printf("%c", c);
        i++;
        if ((c = a[i]) != 0) goto loop2;
}

// пункт 4.3
#include <stdio.h>

int main() {
    char a[128];
    scanf("%s", a);

    printf("задание 1\n");
    int i = 0;
    char c = a[i];
    loop1:
        if (c >= 65 && c <= 90) {
            c -= 'A' - 'a';
        }
        printf("%c", c);
        i++;
        if ((c = a[i]) != 0) goto loop1;

    printf("\n");

    printf("\nзадание2\n");
    i = 0;
    c = a[i];
    loop2:
        if (c >= 65 && c <= 90) {
            c -= 'A' - 'a';
        }
        switch (c) {
            case 'a':
                c = 'e';
                break;
            case 'b':
                c = 'k';
                break;
            case 'x':
                c = 'm';
                break;
            case 'z':
                c = 'p';
                break;
        }
        printf("%c", c);
        i++;
        if ((c = a[i]) != 0) goto loop2;
}