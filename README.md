# Demostración consola simple
Código demostrativo de implementación de una consola simple en C usando *fork()* + *execvp()*.

## Uso del programa
Compilar con *make* y ejecutar:
```
$ ./miconsola
Bienvenido a miconsola, tipee QUIT para terminar...
miconsola:$ 
```

## Compilación
Para compilar el programa:
```
$ make
```
Para compilar facilitando la depuración con gdb:
```
$ make debug
```
Para compilar habilitando la herramienta AddressSanitizer, facilita la depuración en tiempo de ejecución:
```
$ make sanitize
```
