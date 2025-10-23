#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct employee {
    char name[32];   // 固定長度以便二進位 I/O
    int  age;
    int  salary;     // 你要換成別的欄位也可以，但示範常見的三欄
} employee_t;

void emp_info(employee_t emp) {

    printf("%-12s age=%2d  salary=%d\n", emp.name, emp.age, emp.salary);
}

int emp_aveage_age(employee_t emp[], int n) {
    if (n <= 0) return 0;
    long sum = 0;
    for (int i = 0; i < n; ++i) sum += emp[i].age;
    return (int)(sum / n); 
}

void emp_writefile(employee_t emp[], int n) {
    FILE *fp = fopen("employee.bin", "wb");
    if (!fp) { perror("fopen employee.bin"); exit(1); }

    if (fwrite(&n, sizeof(int), 1, fp) != 1) { perror("fwrite n"); exit(1); }
    size_t wrote = fwrite(emp, sizeof(employee_t), n, fp);
    if (wrote != (size_t)n) { perror("fwrite emp"); exit(1); }

    fclose(fp);
}

void emp_readfile(employee_t emp[], int n) {
    FILE *fp = fopen("employee.bin", "rb");
    if (!fp) { perror("fopen employee.bin"); exit(1); }

    int file_n = 0;
    if (fread(&file_n, sizeof(int), 1, fp) != 1) { perror("fread n"); exit(1); }

  
    int to_read = (n < file_n) ? n : file_n;
    size_t got = fread(emp, sizeof(employee_t), to_read, fp);
    if (got != (size_t)to_read) { perror("fread emp"); exit(1); }

    fclose(fp);

    if (file_n > n) {
        fprintf(stderr, "[warn] file has %d records; buffer keeps %d.\n", file_n, n);
    }
}

int main(void) {

    employee_t staff[] = {
        { "Alice", 23, 42000 },
        { "Bob",   29, 55000 },
        { "Carol", 31, 60000 },
        { "David", 27, 48000 },
        { "Eve",   30, 59000 }
    };
    const int N = (int)(sizeof(staff)/sizeof(staff[0]));


    emp_writefile(staff, N);


    employee_t buf[16];              
    memset(buf, 0, sizeof(buf));
    emp_readfile(buf, 16);


    puts("=== employees (read back) ===");
    for (int i = 0; i < N; ++i) emp_info(buf[i]);
    printf("average age = %d\n", emp_aveage_age(buf, N));

    return 0;
}
