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
	// crea un Nodo a partir de un Dict
	tipoNodo *nodo = (tipoNodo *) malloc(sizeof (tipoNodo));

	strcpy (nodo->info.palIngles, dict.palIngles);
	strcpy (nodo->info.palEspanol, dict.palEspanol);

	nodo->siguiente = NULL;
	return nodo;
}

tipoNodo *adicionarLista (tipoNodo *lista, tipoDict dict) {
	// agrega nodos al final de una lista
	// los nodos finales se crean a partir de un Dict
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
	// imprime los elementos/nodos de una lista
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		printf ("<%s>::<%s>\n", aptNodo->info.palIngles, aptNodo->info.palEspanol);
		aptNodo = aptNodo->siguiente;
	}
}

tipoNodo *cargarDictToLista (char *nombreArchivoBin, tipoNodo *lista) {
	// el diccionario entero se guarda en una lista
	FILE *manejadorBin;
	manejadorBin = fopen(nombreArchivoBin, "r"); 
	tipoDict dictTmp;
	int longitudBytes = sizeof (tipoDict);

	while (fread (&dictTmp, longitudBytes, 1, manejadorBin) == 1) {
		//printf ("<%s>:<%s>\n", dictTmp.palIngles, dictTmp.palEspanol);
		lista = adicionarLista (lista, dictTmp);
	}
	fclose (manejadorBin);
	return lista;
}

int elementosEnLista(tipoNodo *lista) {
	// retorna un numero equivalente al numero
	// de elementos en la lista
	int num = 0;
	tipoNodo *tmpLista;
	tmpLista = lista;
	while (tmpLista->siguiente != NULL) {
		num = num + 1;
		tmpLista = tmpLista->siguiente; 
	}
	return num;
}

void *cargarListaToDict (char *nombreArchivoBin, tipoNodo *lista) {
	// opuesto a cargarDictToLista
	// actualiza el diccionario con la lista
	// sirve para actualizar palabras.bin si se
	// ha eliminado una palabra de la lista
	FILE *manejadorBin = fopen(nombreArchivoBin, "w");
	tipoDict dictTmp;
	int elms = elementosEnLista(lista);
	int longitudBytes = sizeof(tipoDict);
	fwrite(lista, longitudBytes, elms, manejadorBin);
	fclose(manejadorBin);
}

void *guardarListaAArchivo(tipoNodo *lst, char *nombreArch) {
	FILE *archBin = fopen(nombreArch, "wb");
	FILE *archTxt = fopen("backup.txt", "w");
	char cadena[150];
	tipoNodo *p = lst;
	tipoDict *tmpInfo;
	while (p != NULL) {
		tmpInfo = &(p->info);
		fwrite(tmpInfo, sizeof(tipoDict), 1, archBin);
		sprintf(cadena, "<%s>::<%s>\n", tmpInfo->palIngles, tmpInfo->palEspanol);
		fputs(cadena, archTxt);
		p = p->siguiente;
	}
	fclose(archBin);
	fclose(archTxt);
}

tipoNodo *insertarLista(tipoNodo *lst, int pos, tipoDict elemento) {
	// inserta un Dict a la posicion dada de la lista
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

tipoNodo *agregarPalabra(tipoNodo *lst, tipoDict elemento) {
	// agrega lexicograficamente
	// tipoNodo *nodoTmp = crearNodo(elemento);
	tipoNodo *p = lst;
	int c = 0;
	
	while (p->siguiente != NULL) {
		if (strcmp(elemento.palIngles, p.info.palIngles) > 0 && strcmp(elemento.palIngles, p->siguiente.info.palIngles) < 0) {
			insertarLista(lst, c, elemento);
			return lst;
		}
		else if (strcmp(elemento.palEspanol, p.info.palEspanol) > 0 && strcmp(elemento.palEspanol, p->siguiente.info.palEspanol) < 0) {
			insertarLista(lst, c, elemento);
			return lst;
		}
		else {
			int c++;
			p = p->siguiente;
		}
	}
	printf("No se pudo agregar las palabras.\n");
	return lst;
}

int buscarPos(tipoNodo *lista, char *palabra) {
	// retorna el numero de la linea en la cual
	// se encuentra la palabra especificada
	int pos = 0;
	printf("implis: %s", lista->info.palIngles);
	if (lista == NULL) printf("Lista vacia.\n");
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

tipoDict buscarPalabra (tipoNodo *lista, char *palabra) {
	// retorna un tipoDict con la palabra y su traduccion
	if (lista == NULL)
		printf("Lista vacía.");
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		if (strcmp(palabra, aptNodo->info.palIngles) == 1) {
			printf("<%s>::<%s>\n", aptNodo->info.palIngles, aptNodo->info.palEspanol);
			return (aptNodo->info);
		}
		else if (strcmp(palabra, aptNodo->info.palEspanol) == 1) {
			printf("<%s>::<%s>\n", aptNodo->info.palIngles, aptNodo->info.palEspanol);
			return (aptNodo->info);
		}
		else
			aptNodo = aptNodo->siguiente;
	}
}

tipoNodo *cambiarPalabra(tipoNodo *lista, char *palVieja, char *palNueva, char *leng) {
	// cambia una palabra en la lista
	// entradas son la lista, la palabra a cambiar,
	// la palabra que se desea insertar para cambiarla,
	// y el lenguaje de las palabras a cambiar
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		if (leng == "ingles") {
			if (strcmp(palVieja, aptNodo->info.palIngles) == 1) {
				strcpy(aptNodo->info.palIngles, palNueva);
				// destination, string to copy
			}
		}
		else if (leng == "espanol") {
			if (strcmp(palVieja, aptNodo->info.palEspanol) == 1) {
				strcpy(aptNodo->info.palIngles, palNueva);
			}
		}
		else
			aptNodo = aptNodo->siguiente;
	}
	return lista;
}

void cerrarPrograma() {
	// incluido con <stdio.h>
	exit(0);
}

tipoNodo *eliminarPalabra(tipoNodo *lista, char palabra[]) {
	// elimina una palabra especificada de la lista
	if (lista == NULL)
		printf("Lista vacía.\n");
	tipoNodo *aptNodo = lista;
	while (aptNodo->siguiente != NULL) {
		if (strcmp(palabra, aptNodo->info.palIngles) == 1) {
			free(aptNodo->info.palIngles);
			free(aptNodo->info.palEspanol);
			printf("La palabra y su traduccion fueron eliminadas.\n");
		}
		else if (strcmp(palabra, aptNodo->info.palEspanol) == 1) {
			free(aptNodo->info.palIngles);
			free(aptNodo->info.palEspanol);
			printf("La palabra y su traduccion fueron eliminadas.\n");
		}
		else
			aptNodo = aptNodo->siguiente;
	}
	if (aptNodo->siguiente == NULL)
		printf("La palabra no esta en el diccionario.\n");
	return aptNodo;
}

char busquedaInteligente(tipoNodo *lista, char palabra[50]) {
	char string[50];
	tipoNodo *p = lst;
	int compar = 0;
	int i = 0;
	int conta = 0;
	while (p->siguiente != NULL) {
		i = 0;
		conta = 0;
    		for(i = 0; i < strlen(palabra); i++) {
        		if (palabra[i] == p.info.palIngles[i]) {
            			conta++;
        		}
    		}
		if (compar < conta) {
			string = p.info.palIngles;
			compar = conta;
		}
		p = p->siguiente;
	}
	printf("Quizas querias buscar %s?\n", string);
	return string;
}


int main() {
	// funcion principal que recibe comandos del usuario por scanf
	tipoNodo *lista;
	lista = cargarDictToLista("palabras.bin", lista);
	printf("INSTRUCCIONES DE USO:\n");
	printf("Escriba 'cerrar' parar cerrar el programa.\n");
	printf("Escriba 'buscar' para buscar una palabra.\n");
	printf("Escriba 'eliminar' para borrar una palabra.\n");
	printf("Escriba 'modificar' para cambiar la traduccion de una palabra.\n");
	printf("Escriba 'agregar' para agregar una palabra y su traduccion.\n");

	char argv[11]; // comando o funcion a ejecutar
	char palab[50]; // palabra para buscar o eliminar
	printf("Comando? ");
	scanf("%s", argv);

	if (strcmp(argv, "cerrar") == 0) {
		printf("Cerrando el programa...");
		cerrarPrograma();
	}

	else if (strcmp(argv, "buscar") == 0) {
		printf("Escriba la palabra que desea buscar: ");
		scanf("%s\n", palab);
		// imprimirLista(lista);
		int pos = buscarPos(lista, palab);
		tipoDict palabras = buscarPalabra(lista, palab);
		printf("La palabra '%s' esta en la posición (línea) '%d'.\n", palab, pos);
		printf("Linea %d -> <%s>::<%s>\n", pos, palabras.palIngles, palabras.palEspanol);
		return 0;
	}

	else if (strcmp(argv, "eliminar") == 0) {
		printf("Escriba la palabra que desea eliminar: ");
		scanf("%s\n", palab);
		lista = eliminarPalabra(lista, palab);
		// cargarListaToDict("palabras.bin", lista);
		guardarListaAArchivo(lista, "palabras.bin");
		// "palabras.bin" se actualiza con las palabras eliminadas
		return 0;
	}

	else if (strcmp(argv, "modificar") == 0) {
		printf("Escriba la palabra que desea modificar: ");
		scanf("%s\n", palab);
		int pos = buscarPos(lista, palab);
		tipoDict palabras = buscarPalabra(lista, palab);
		printf("Linea %d -> <%s>::<%s>\n", pos, palabras.palIngles, palabras.palEspanol);
		char leng[9];
		char mod[50];
		printf("Quieres cambiar la palabra en Ingles o Español?\n");
		scanf("%s\n", leng);
		printf("Escriba la modificacion que deseas: ");
		scanf("%s\n", mod);
		cambiarPalabra(lista, palab, mod, leng);
		guardarListaAArchivo(lista, "palabras.bin"); // actualiza
		return 0;
	}

	else if (strcmp(argv, "agregar") == 0) {
		printf("Escriba la palabra en ingles que desea agregar: ");
		scanf("%s\n", palab);
		char pES[50];
		printf("Escriba la palabra en español que desea agregar: ");
		scanf("%s\n", pES);
		int ps;
		printf("Escriba la posicion en la cual desea agregar las palabras: ");
		scanf("%d\n", &ps);
		tipoDict di;
		strcpy(di.palIngles, palab);
		strcpy(di.palEspanol, pES);
		lista = insertarLista(lista, ps, di);
		guardarListaAArchivo(lista, "palabras.bin"); // actualiza
	}

	else {
		printf("El comando que escribiste no existe. Cerrando el programa...\n");
		return 0;
	}
}
