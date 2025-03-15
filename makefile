# Makefile para compilar archivos en el directorio actual
# Nombre del ejecutable, deseable en mayúsculas

TARGET = RUN

# Bibliotecas incluidas, la biblioteca math.h es una muy común
LIBS = -lm

# Compilador utilizado, por ej icc, pcc, gcc
CC = g++

# Banderas del compilador, por ej -DDEBUG -O2 -O3 -Wall -g
CFLAGS = -g

# Palabras que usa el Makefile que podrían ser el nombre de un programa
.PHONY: default all clean

# Compilación por defecto
default: $(TARGET)
all: default

# Incluye los archivos .o y .c que están en el directorio actual
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# Incluye los archivos .h que están en el directorio actual
HEADERS = $(wildcard *.h)

# Compila automáticamente solo archivos fuente que se han modificado
# $< es el primer prerrequisito, generalmente el archivo fuente
# $@ es el nombre del archivo que se está generando, archivo objeto
%.o: %.cpp $(HEADERS)
        $(CC) $(CFLAGS) -c $< -o $@

# Preserva archivos intermedios
.PRECIOUS: $(TARGET) $(OBJECTS)

# Enlaza objetos y crea el ejecutable
$(TARGET): $(OBJECTS)
        $(CC) $(OBJECTS) $(LIBS) -o $@

# Borra archivos .o
clean:
        rm -f *.o $(TARGET)
#borra archivos .o y el ejecutable
cleanall: clean
	-rm -f $(TARGET)