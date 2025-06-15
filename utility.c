// utility.c
// Nesreen & Dima
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "myshell.h"

#define MAX_LINE 1024
#define MAX_ARGS 64

void shell_loop(void) {
    char *line;
    char **args;

    while (1) {
        printf("myshell> ");
        line = read_input();          // اقرأ أمر المستخدم
        args = parse_input(line);    // حلله إلى كلمات
        execute_command(args);       // نفّذ الأمر
        free(line);
        free(args);
    }
}

char *read_input(void) {
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin); // نقرأ من المستخدم
    return line;
}

char **parse_input(char *line) {
    int bufsize = MAX_ARGS;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    int position = 0;

    token = strtok(line, " \t\r\n");
    while (token != NULL) {
        tokens[position++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    tokens[position] = NULL;
    return tokens;
}

void execute_command(char **args) {
    if (args[0] == NULL) return;

    if (strcmp(args[0], "cd") == 0) {
        if (args[1]) {
            chdir(args[1]);  // تغيير المجلد
        } else {
            printf("يرجى تحديد مسار.\n");
        }
        return;
    }

    if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
        printf("خروج من myshell.\n");
        exit(0);
    }

    pid_t pid = fork(); // إنشاء عملية جديدة
    if (pid == 0) {
        // العملية الفرعية تنفذ الأمر
        if (execvp(args[0], args) == -1) {
            perror("خطأ في exec");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("فشل fork");
    } else {
        wait(NULL); // ننتظر انتهاء العملية الفرعية
    }
}
