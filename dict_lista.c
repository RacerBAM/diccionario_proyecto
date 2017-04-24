#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dict {
	char palIngles  [50];
	char palEspanol [50];
};

typedef struct Dict tipoDict;

struct Nodo {
	tipoDict info;
	struct Nodo *siguiente;
};

typedef struct Nodo tipoNodo;

//tipoNodo *lista=NULL;

tipoNodo *crearNodo (tipoDict dict) {
	tipoNodo *nodo = (tipoNodo *) malloc(sizeof (tipoNodo));

	strcpy (nodo->info.palIngles, dict.palIngles);
	strcpy (nodo->info.palEspanol, dict.palEspanol);

	nodo->siguiente = NULL;
	return nodo;
}

tipoNodo *adicionarLista (tipoNodo *lista, tipoDict dict) {
	tipoNodo *nuevoNodo = crearNodo (dict);

	if (lista==NULL) {
		lista = nuevoNodo;
	}
	else {
		tipoNodo *aptNodo = lista;
		while (aptNodo->siguiente != NULL) { // while (aptNodo != NULL) {
			aptNodo = aptNodo->siguiente;
		}
		aptNodo->siguiente = nuevoNodo;
	}
	return lista; // return aptnodo; ??
}

void imprimirLista (tipoNodo *lista) {
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		printf ("<%s>::<%s>\n", aptNodo->info.palIngles, aptNodo->info.palEspanol);
		aptNodo = aptNodo->siguiente;
	}
}

tipoNodo *cargarDictToLista (char *nombreArchivoBin, tipoNodo *lista) {
	FILE *manejadorBin;
	manejadorBin = fopen (nombreArchivoBin, "r"); 
	tipoDict dictTmp;
	int longitudBytes = sizeof (tipoDict);

	while (fread (&dictTmp, longitudBytes, 1, manejadorBin) == 1) {
		//printf ("<%s>:<%s>\n", dictTmp.palIngles, dictTmp.palEspanol);
		lista = adicionarLista (lista, dictTmp);
	}
	fclose (manejadorBin);
	return lista;
}

tipoNodo *insertarLista(tipoNodo *lst, int pos, tipoDict elemento) {
	tipoNodo *p = lst;
	tipoNodo *nodoTmp = crearNodo(elemento);
	int cont;

	if (pos == 1) {
		nodoTmp->siguiente = lst;
		lst = nodoTmp;
	}
	else {
		cont = 1;
		while (cont < pos-1) {
			cont++;
			p = p->siguiente;
		}
		nodoTmp->siguiente = p->siguiente;
		p = nodoTmp;
	}
	return lst;
}

int buscarPos(tipoNodo *lista, char *palabra) {
	int pos = 0;
	printf("implis: %s", lista->info.palIngles);
	if (lista == NULL) printf("Lista vacia.");
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		if (strcmp(palabra, aptNodo->info.palIngles) > 0) {
			pos++;
			aptNodo = aptNodo->siguiente;
		}
		else
			break;
	}
	return pos;
}

char buscarPalabra (tipoNodo *lista, char *palabra) {
	if (lista == NULL)
		printf("Lista vacía.");
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		if (strcmp(palabra, aptNodo->info.palIngles) == 1)
			printf("%s : %s", aptNodo->info.palIngles, aptnodo->info.palEspanol);
		else if (strcmp(palabra, aptNodo->info.palEspanol) == 1)
			printf("%s : %s", aptNodo->info.palIngles, aptnodo->info.palEspanol);
		else
			aptNodo = aptNodo->siguiente;
	}
}

void cerrarPrograma() {
	exit(0);
}

lista eliminarPalabra(tipoNodo *lista, char palabra[]) {
	if (lista == NULL)
		printf("Lista vacía.");
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		if (strcmp(palabra, aptNodo->info.palIngles) == 1) {
			free(aptNodo->info.palIngles)
			free(aptNodo->info.palEspanol)
		}
		else if (strcmp(palabra, aptNodo->info.palEspanol) == 1) {
			free(aptNodo->info.palIngles)
			free(aptnodo->info.palEspanol);
		}
		else
			aptNodo = aptNodo->siguiente;
	}
	return aptNodo;
}



int main (int argc, char * argv[]){
	printf("Escriba 0 y cerrar parar cerrar el programa.");
	if (argc == 0 && argv == "cerrar")
		cerrarPrograma()
	tipoNodo *lista;
	lista = cargarDictToLista ("palabras.bin", lista);
	imprimirLista(lista);
	return 0;
}