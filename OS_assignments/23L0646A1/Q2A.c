#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, num;
    FILE *file;

    printf("Enter the number of elements (n): ");
    scanf("%d", &n);
    file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Error!");
    }

    printf("Enter %d numbers between 0 and 255:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        while (num < 0 || num > 255) {
            printf("enter a valid number ");
            scanf("%d", &num);
        }

        // Write to the file
        fprintf(file, "%d\n", num);
    }

    fclose(file);
    printf("Task done\n");
    return 0;
}