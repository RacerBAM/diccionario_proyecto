/*diccionario.c*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *traduccion(char palabra[20]) {
	char trad[20];
	char *S1;
	char *S2;
	char cad[20];
	FILE *manejadorArch;
	manejadorArch = fopen("palabras.dict", "r");
	if (manejadorArch == NULL) {
		printf("Error. No se pudo abrir el archivo.\n");
		exit(0);
	}
	else {
		S1 = strtok(cad, ";");
		if (S1 == palabra) {
			S2 = strtok(NULL, ":");
			return S2;
		}
	}
}

int main() {
	char palIngles[80], palEspanol[80];
	FILE *manejadorEscritura = fopen("dic.txt", "w");
	FILE *manejadorArch;
	char cadena[250];
	manejadorArch = fopen("palabras.dict", "r");
	if (manejadorArch == NULL) {
		printf("Error. No se pudo abrir el archivo.\n");
		exit(0);
	}
	else {
		while (!feof(manejadorArch)) {
			fgets(cadena, 250, manejadorArch);
			printf("%s", cadena);
			strcpy(palIngles, strtok(cadena, " : "));
			strcpy(palEspanol,  strtok(NULL, "")); // para proyecto
			// CON NULL, de la misma cadena trae el siguiente
			fputs(cadena, manejadorEscritura);
		}
		fclose(manejadorArch);
		fclose(manejadorEscritura);
	}
	return 0;
}