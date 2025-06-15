// myshell.h  
// Nesreen & Dima
#ifndef MYSHELL_H
#define MYSHELL_H

void shell_loop(void);               // حلقة الشل الرئيسية
void execute_command(char **args);  // تنفيذ الأوامر
char **parse_input(char *line);     // تحليل السطر المُدخل
char *read_input(void);             // قراءة سطر من المستخدم

#endif
