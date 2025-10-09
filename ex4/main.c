#include <stdio.h>
int main() {
    FILE* fp;
    int   a[] = {0,1,2};
    char  b[] = "ABC";
    float c[] = {1.1,1.2,1.3};
    int   ra[3];
    char  rb[3];
    float rc[3];

    fp = fopen("cj.txt", "wb");
    fwrite(a, sizeof(int),   3, fp);
    fwrite(b, sizeof(char),  3, fp);
    fwrite(c, sizeof(float), 3, fp);
    fclose(fp);


    fp = fopen("cj.txt", "rb");
    fread(ra, sizeof(int),   3, fp);
    fread(rb, sizeof(char),  3, fp);
    fread(rc, sizeof(float), 3, fp);
    fclose(fp);

    for (int i = 0; i < 3; ++i) printf("%d ", ra[i]);  printf("\n");
    for (int i = 0; i < 3; ++i) printf("%c ", rb[i]);  printf("\n");
    for (int i = 0; i < 3; ++i) printf("%f ", rc[i]);  printf("\n");

    fp = fopen("a.bin", "w");
    fprintf(fp, "Integer array:\n");
    for (int i = 0; i < 3; ++i) fprintf(fp, "%d ", ra[i]);
    fprintf(fp, "\n\n");

    fprintf(fp, "Character array:\n");
    for (int i = 0; i < 3; ++i) fprintf(fp, "%c ", rb[i]);
    fprintf(fp, "\n\n");

    fprintf(fp, "Float array:\n");
    for (int i = 0; i < 3; ++i) fprintf(fp, "%.6f ", rc[i]);
    fprintf(fp, "\n");
    fclose(fp);

    return 0;
}
