miconsola: main.c
	gcc -o miconsola main.c $(DFLAGS)

# Compila usando la opción -g para facilitar la depuración con gdb.
.PHONY: debug
debug: DFLAGS = -g
debug: clean miconsola

# Compila habilitando la herramienta AddressSanitizer para
# facilitar la depuración en tiempo de ejecución.
.PHONY: sanitize
sanitize: DFLAGS = -fsanitize=address,undefined
sanitize: clean miconsola

.PHONY: clean
clean:
	rm -rf miconsola

.PHONY: run
run: miconsola
	./miconsola
