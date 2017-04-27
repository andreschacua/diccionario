#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*---------------------------------------------------------------------------------------*/
struct Dict {
	char palIngles  [50];
	char palEspanol [50];
};
typedef struct Dict tipoDict;
/*---------------------------------------------------------------------------------------*/
struct Nodo {
	tipoDict info;
	struct Nodo *siguiente;
};

typedef struct Nodo tipoNodo;
/*---------------------------------------------------------------------------------------*/
tipoNodo *lista=NULL;
/*---------------------------------------------------------------------------------------*/
tipoNodo *crearNodo (tipoDict dict) {
	tipoNodo *nodo = (tipoNodo *)malloc (sizeof (tipoNodo));

	strcpy (nodo->info.palIngles, dict.palIngles);
	strcpy (nodo->info.palEspanol, dict.palEspanol);
	

	nodo->siguiente = NULL;
	return nodo;
}
/*---------------------------------------------------------------------------------------*/
int buscar_posicion (char *palabra, tipoNodo *lista){
	int posicion = 0;

	if (lista == NULL){
		printf("La lista no tiene ninguna palabra.\n");
	}

	else{
		tipoNodo *aptNodo = lista;

		while(aptNodo != NULL){
			
			if (strcmp(palabra, aptNodo -> info.palIngles) > 0){
				posicion ++;
				aptNodo = aptNodo -> siguiente;
			}
			else{
				break;
			}
		}
	}

	return posicion;
}
/*---------------------------------------------------------------------------------------*/
tipoNodo* adicionarLista (tipoDict dict, tipoNodo *lista) {
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
/*---------------------------------------------------------------------------------------*/
void imprimirLista (tipoNodo *lista) {
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		printf ("<%s>::<%s>\n", aptNodo->info.palIngles, aptNodo->info.palEspanol);
		aptNodo = aptNodo->siguiente;
	}
}
/*---------------------------------------------------------------------------------------*/
tipoNodo* cargarDictToLista (char *nombreArchivoBin, tipoNodo *lista) {
	FILE *manejadorBin;
	manejadorBin = fopen (nombreArchivoBin, "r"); 
	tipoDict dictTmp;
	int longitudBytes = sizeof (tipoDict);

	while (fread (&dictTmp, longitudBytes, 1, manejadorBin) == 1) {
		lista = adicionarLista (dictTmp, lista);
	}
	fclose (manejadorBin);
	return lista;
}
/*---------------------------------------------------------------------------------------*/
tipoNodo *insertarlista(tipoNodo *lista, int posicion, tipoDict elemento){
    tipoNodo *temporal = crearNodo(elemento);
    tipoNodo *palabra = lista;
    int cont = 1;
    
    if(posicion == 1){
            temporal->siguiente = lista;
            lista = temporal;
    }

    else{
        
        while(cont < posicion-1){
            cont++;
            palabra = palabra->siguiente;
        }

    	temporal->siguiente = palabra->siguiente;
    	palabra->siguiente = temporal;
    }

 	return lista;
}
/*---------------------------------------------------------------------------------------*/
char busqueda_palabra(tipoNodo *lista, char *pal_buscar){
	tipoNodo *palabra;
	char* pal_ing = (char*) malloc ((sizeof(char)) *50);
	char* pal_esp = (char*) malloc ((sizeof(char)) *50);

	if (lista == NULL){
		printf("La plabra no existe en el diccionario.\n");
	}

	else{
		palabra = lista;

		while(palabra != NULL){
			strcpy(pal_ing, palabra ->info.palIngles);
			strcpy(pal_esp, palabra ->info.palEspanol);

			if (strcmp (pal_buscar, pal_ing) == 0){
				printf("%s\n", pal_esp);
			}

			if(strcmp(pal_buscar, pal_esp) == 0){
				printf("%s\n", pal_ing);
			}

			else{
				palabra = palabra -> siguiente;
			}
		}
		printf("La palabra no existe en el diccionario.\n");
	}
}
/*---------------------------------------------------------------------------------------*/
tipoNodo* adicionar_palabra(tipoNodo*lista, char *pal_esp, char *pal_ing){
	tipoDict nueva_pal;
	tipoNodo *palabra;
	int cont;

	strcpy(nueva_pal.palIngles, pal_ing);
	strcpy(nueva_pal.palEspanol, pal_esp);

	palabra = crearNodo(nueva_pal);
	cont = buscar_posicion(pal_ing, lista);
	tipoNodo* igual = insertarlista(lista, cont, nueva_pal);
	
	return igual;
}
/*---------------------------------------------------------------------------------------*/
tipoNodo *modificar_palabra(tipoNodo *lista, char *palabra){
	int posicion = buscar_posicion(palabra,lista);
	tipoNodo *p_nodo = lista;
	int cont = 1;
	char nueva_trad[100];
    
    printf("Inserte el nuevo significado de la palabra:\n");
    scanf("%s",nueva_trad);

	if(posicion == 1){
        strcpy(lista->info.palEspanol, nueva_trad);
	}

	else{
    
        while (cont <= posicion-1){
            cont++;
            p_nodo=p_nodo->siguiente;
        }

        strcpy(p_nodo->info.palEspanol, nueva_trad);
    }

	return lista;
}
/*---------------------------------------------------------------------------------------*/
tipoNodo* eliminar_palabra(char* palabra, tipoNodo* lista){
	tipoNodo* temporal;
	tipoNodo *a;
	int posicion = buscar_posicion(palabra, lista);
	
	if (posicion == 1){
	    lista = lista->siguiente;
        temporal = lista;
        return temporal;
	}

	else{
		int cont = 1;  
		temporal = lista;
		
		while(cont < posicion-1){
			cont++;
			temporal = temporal->siguiente;
		}

		a= temporal->siguiente;
		temporal->siguiente=temporal->siguiente->siguiente;
		free(a);
	}

	return temporal;
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
void menu(tipoNodo *lista){

    int numero;
    char palabra[50];
    char traduccion;
    
    tipoDict elemento;
    char palabra_ingles[50];
    char palabra_espanol[50];
    int cont;
    
    char pal_eliminar[50];
    
    char pal_modificar[50];

    printf("\n MENU \n");
    printf(" 1. Busqueda exacta de una palabra.\n 2. Adicionar una palabra.\n 3. Eliminar una palabra.\n 4. Modificar una palabra.\n 5. Salir del programa.\n");
	printf("\n Escoja una opcion: ");
	scanf("%d",&numero);
	
    if (numero == 1){
    	printf(" Ingrese una palabra:\n");
        scanf("%s",&palabra);
        traduccion = busqueda_palabra(lista, palabra);
        printf("\n Su traduccion es: %s %s\n", palabra, traduccion);
    }
	
    if (numero == 2){
		printf(" Ingrese una palabra en Ingles: ");
        scanf("%s", palabra_ingles);
        printf(" Ingrese una palabra en Español: ");
        scanf("%s", palabra_espanol);

        lista = adicionar_palabra(lista, palabra_espanol, palabra_ingles);
	}
	
	if (numero == 3){
		printf(" Ingrese la palabra que desea eliminar: ");
        scanf("%s", pal_eliminar);
		lista = eliminar_palabra(pal_eliminar, lista);
	}

	if (numero == 4){
		printf(" Ingrese la palabra a modificar: ");
        scanf("%s",pal_modificar);
        lista = modificar_palabra(lista, pal_modificar);
    }

	if (numero == 5){
		printf("\n Salio \n");

	}

	if (numero == 6){
		printf("Modificar Inteligente");

	}

    else{
    	printf("\n Numero invalido, intente de nuevo. ");
    }
}
/*---------------------------------------------------------------------------------------*/
int main(){
    tipoNodo *lista;
	tipoDict dict;

	lista = crearNodo(dict);
	lista = cargarDictToLista ("palabras.bin", lista);
    int opcion;

    printf(" Diccionario por Andres Fernando Chacua Villota \n");
    printf(" La forma de interaccion puede ser sin opciones o con opciones,\n");
    printf(" ingrese 1 se quiere ir a la forma sin opciones o ingrese 2 si quiere ir a la forma con opciones.\n");
    scanf("%d",&opcion);
/*---------------------------------------------------------------------------------------
    if(opcion == 1){

        FILE * Diccionario = fopen("palabras.dict","r");
        char guardar[50];
        char palabra[50];
        printf("Digite la palabra que desea buscar: ");
        gets(palabra);
        
        if(Diccionario==NULL){
            printf("No se pudo leer la palabra.");
            exit(0);
        }

        else{
            
            while(!feof(Diccionario)){
            	fgets(guardar, 50, Diccionario);
                char *a;
                a = strstr(guardar, palabra);
                
                if (strstr(guardar, palabra) != NULL){
                    strtok(a, " : ");
                    strtok(NULL, " ");
                    printf("%s\n", a);
                }
            }
        }
        
        fclose(Diccionario);

    }
/*---------------------------------------------------------------------------------------*/
    menu(lista);
	return 0;
}