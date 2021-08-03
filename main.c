#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 1024

char **parse_comando(char *linea, char *delim);

int main(int argc, char **argv)
{
	char *linea_consola = (char *) calloc(1, MAXLINE);
	char **argumentos;
	size_t max = MAXLINE;
	ssize_t l = 0;
	int status;
	pid_t pid;

	printf("Bienvenido a miconsola, tipee QUIT para terminar...\n");
	printf("miconsola:$ ");
	l = getline(&linea_consola, &max, stdin); //lee desde consola
	linea_consola[l-1] = '\0'; //Sobreescribe el salto de línea
	while(l > 0){
		argumentos = parse_comando(linea_consola, " ");

		//Detecta "QUIT" y termina
		if(strcmp(argumentos[0], "QUIT") == 0){
			printf("Bye!\n");
			break;
		}

		if(argumentos){
			if((pid = fork()) == 0){
				if(execvp(argumentos[0], argumentos) < 0){
					fprintf(stderr, "Comando desconocido...\n");
					exit(1);
				}
			}

			//Espera a que el proceso hijo termine su ejecución
			waitpid(pid, &status, 0);

			/*Libera argumentos y su contenido
			para evitar fugas de memoria */
			for(int i = 0; argumentos[i]; i++)
				free(argumentos[i]);
			free(argumentos);
		}

		//Volver a leer desde consola
		printf("miconsola:$ ");
		l = getline(&linea_consola, &max, stdin);
		linea_consola[l-1] = '\0'; //Sobreescribe el salto de línea
	}

	return 0;
}

/**
 * Función que crea argv separando una cadena de caracteres en
 * "tokens" delimitados por la cadena de caracteres delim.cd r
 *
 * @param linea Cadena de caracteres a separar en tokens.
 * @param delim Cadena de caracteres a usar como delimitador.
 *
 * @return Puntero a argv en el heap, es necesario liberar esto después de uso.
 *	Retorna NULL si linea está vacía.
 */
char **parse_comando(char *linea, char *delim)
{
	char *token;
	char *linea_copy;
	int i, num_tokens = 0;
	char **argv = NULL;

	linea_copy = (char *) malloc(strlen(linea) + 1);
	strcpy(linea_copy, linea);

	/* Obtiene un conteo del número de argumentos */
	token = strtok(linea_copy, delim);
	/* recorre todos los tokens */
	while( token != NULL ) {
		token = strtok(NULL, delim);
		num_tokens++;
	}
	free(linea_copy);

	/* Crea argv en el heap, extrae y copia los argumentos */
	if(num_tokens > 0){

		/* Crea el arreglo argv */
		argv = (char **) malloc((num_tokens + 1) * sizeof(char **));

		/* obtiene el primer token */
		token = strtok(linea, delim);
		/* recorre todos los tokens */
		for(i = 0; i < num_tokens; i++){
			argv[i] = (char *) malloc(strlen(token)+1);
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
	}

	return argv;
}