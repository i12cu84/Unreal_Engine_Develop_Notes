#include <stdio.h>

#define CODE "\
#include <stdio.h>%c%c\
#define CODE %c%s%c%c\
int main() {%c\
    printf(CODE, 10, 10, 34, CODE, 34, 10, 10, 10, 10);%c\
        return 0;%c\
        }%c"

int main()
{
    printf(CODE, 10, 10, 34, CODE, 34, 10, 10, 10, 10);
    return 0;
}

/*
#include <iostream>

#define QUINE "#include <iostream>%c#define QUINE %c%s%c%cint main() {%c    printf(QUINE, 10, 34, QUINE, 34, 10, 10);%c    return 0;%c}%c"

int main() {
    printf(QUINE, 10, 34, QUINE, 34, 10, 10);
    return 0;
}
*/