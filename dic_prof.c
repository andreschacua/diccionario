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

tipoNodo *lista=NULL;

tipoNodo *crearNodo (tipoDict dict) {
	tipoNodo *nodo = (tipoNodo *)malloc (sizeof (tipoNodo));

	strcpy (nodo->info.palIngles, dict.palIngles);
	strcpy (nodo->info.palEspanol, dict.palEspanol);
	

	nodo->siguiente = NULL;
	return nodo;
}

tipoNodo* adicionarLista (tipoNodo *lista, tipoDict dict) {
	tipoNodo *nuevoNodo = crearNodo (dict);

	if (lista==NULL) {
		lista = nuevoNodo;
	}else {
		tipoNodo *aptNodo = lista;
		while (aptNodo->siguiente != NULL) {
			aptNodo = aptNodo->siguiente;
		}
		aptNodo->siguiente = nuevoNodo;
	}
	return lista;
}

void imprimirLista (tipoNodo *lista) {
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		printf ("<%s>::<%s>\n", aptNodo->info.palIngles, aptNodo->info.palEspanol);
		aptNodo = aptNodo->siguiente;
	}
}

tipoNodo* cargarDictToLista (char *nombreArchivoBin, tipoNodo *lista) {
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

char busqueda_palabra(char *pal_buscar, tipoNodo *lista){
	tipoNodo *palabra;
	char pal_ing[100];
	char pal_esp[100];

	if (lista == NULL){
		return 0;
	}

	else{
		palabra = lista;

		while(palabra != NULL){
			strcpy(pal_ing,palabra ->info.palIngles);
			strcpy(pal_esp,palabra ->info.palEspanol);

			if (strcmp (pal_buscar,pal_ing) == 0){
				printf("%s\n",pal_esp);
			}

			if(strcmp(pal_buscar,pal_esp) == 0){
				printf("%s\n",pal_ing);
			}

			else{
				palabra = palabra -> siguiente;
			}
		}
		printf("La palabra no existe en el diccionario.\n");
	}
}

/*---------------------------------------------------------------------------------------

tipoNodo* insertar_palabra(tipoNodo*lista, int pos, tipoDict pal_adicionar){
	tipoNodo *aptNodo = lista;
	tipoNodo *nodoTmp = crearNodo(palabra);
	int cont;

	if (pos == 1){
		nodoTmp -> siguiente = lista;
		lista = nodoTmp;
	}

	else{
		cont = 1;
		
		while(cont < pos -1){
			cont++;
			aptNodo = aptNodo -> siguiente;
		}

		nodoTmp -> siguiente = aptNodo -> siguiente;
		aptNodo -> siguiente = nodoTmp;
	}

	return lista;
}
---------------------------------------------------------------------------------------*/

tipoNodo *modificar_pal(tipoNodo *lista, char*palabra){
	int posiciontipoNodo *pal_mod = lista;
	int cont = 1;
	
	while(i < po){

	 }
}

/*---------------------------------------------------------------------------------------*/

void guardar_lista_a_archivo(tipoNodo *lista, char *nombre_archivo){
	FILE *archivo_bin = fopen(arc_binario, "wb");
	FILE *archivo_txt = fopen("backup.txt", "wb");
	char cadena[150];
	tipoNodo *palabra = lista;
	tipoDict *tmpInfo;
	
	while(palabra != NULL){
		tmpInfo = palabra -> info;
		fwrite(tmpInfo,sizeof(tipoDict),1,archivo_bin);
		sprintf(cadena, "<%s>:<%s>\n", tmpInfo -> palIngles, tmpInfo -> palEspanol);
		fputs(cadena,archivo_txt);
		palabra = palabra -> siguiente;
	}
	fclose(archivo_txt);
	fclose(archivo_bin);
}
/*---------------------------------------------------------------------------------------*/
int main (int argc, char * argv[]){
	tipoNodo *lista = NULL;
	lista = cargarDictToLista ("palabras.bin", lista);
		
	printf("Ingrese la opcion que corresponda:\n\n");
	printf("1. Salir -> S\n");
	printf("2. Busqueda Exacta -> B\n");
	printf("3. Adicionar Palabra -> A\n");
	printf("4. Eliminar -> E\n");
	printf("5. Modificar -> M\n");
	printf("6. Busqueda Inteligente -> I\n");
	
	return 0;
}