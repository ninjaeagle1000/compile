#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void compile_c(char *src, char *out);
void compile_go(char *src, char *out);
void compile_java(char *src, char *out);

int main(int argc, char **argv) {
	if (argc == 1) {
		printf("Usage: compile <file> (<more files>)\n");
		return 1;
	}

	regex_t reg_c;
	regcomp(&reg_c, "\\.c", 0);
	regex_t reg_go;
	regcomp(&reg_go, "\\.go", 0);
	regex_t reg_java;
	regcomp(&reg_java, "\\.java", 0);

	for (int i = 1; i < argc; i++) {
		int len = strlen(argv[i]);
		char *out = malloc(++len);
		strcpy(out, argv[i]);
		for (int i = len; i > 0; i--) 
			if (out[i] == '.') {
				out[i] = '\0';
				break;
			}
	
		// If source file is c, compile it
		if (!regexec(&reg_c, argv[i], 0, NULL, 0))
			compile_c(argv[i], out);
		// If source file is go, compile it
		else if (!regexec(&reg_go, argv[i], 0, NULL, 0))
			compile_go(argv[i], out);
		// If source file is java, compile it
		else if (!regexec(&reg_java, argv[i], 0, NULL, 0))
			compile_java(argv[i], out);
		else
			fprintf(stderr, "File type for file \"%s\" not supported\n", argv[i]);

		free(out);
	}

	return 0;
}

void compile_c(char *src, char *out) {
	// Execute gcc
	char *cmd;
	asprintf(&cmd, "gcc -o ~/bin/%s %s", out, src);
	system(cmd);
	free(cmd);
	free(out);

	return;
}

void compile_go(char *src, char *out) {
	char *cmd;
	asprintf(&cmd, "go build -o ~/bin/%s %s", out, src);
	system(cmd);
	free(cmd);

	return;
}

void compile_java(char *src, char *out) {
	char *cmd;
	asprintf(&cmd, "javac -d ~/bin/%s %s", out, src);
	system(cmd);
	free(cmd);

	return;
}
