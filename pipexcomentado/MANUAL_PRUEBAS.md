# MANUAL DE PRUEBAS PARA PIPEX

## Pruebas Básicas (ejecutar una por una)

# 1. Preparar archivo de entrada
echo -e "Hola mundo\nSegunda línea\n42 Madrid" > infile

# 2. Prueba simple
./pipex infile "cat" "grep mundo" outfile.txt
cat outfile.txt
# Resultado esperado: Hola mundo

# 3. Verificar con equivalente de shell
< infile cat | grep mundo
# Debe dar el mismo resultado

# 4. Prueba con wc
./pipex infile "cat" "wc -l" outfile.txt
cat outfile.txt
# Resultado esperado: 3

# 5. Prueba con sort
echo -e "zebra\napple\nbanana" > infile
./pipex infile "cat" "sort" outfile.txt
cat outfile.txt
# Resultado esperado: apple, banana, zebra (ordenado)

## Pruebas de Error

# 6. Comando inexistente
./pipex infile "comando_falso" "cat" outfile.txt
# Debe mostrar error

# 7. Archivo inexistente
./pipex archivo_falso.txt "cat" "wc -l" outfile.txt
# Debe mostrar error

# 8. Argumentos incorrectos
./pipex infile "cat"
# Debe mostrar: "Uso: ./pipex infile cmd1 cmd2 outfile"

## Pruebas Avanzadas

# 9. Múltiples argumentos
echo -e "file.c\nfile.h\nfile.txt\ntest.py" > infile
./pipex infile "cat" "grep -E '\.(c|h)$'" outfile.txt
cat outfile.txt
# Debe mostrar solo file.c y file.h

# 10. Números y head
seq 1 20 > infile
./pipex infile "cat" "head -5" outfile.txt
cat outfile.txt
# Debe mostrar números 1-5

## Verificar que no hay memory leaks
valgrind --leak-check=full ./pipex infile "cat" "wc -l" outfile.txt

## Comparar con comportamiento esperado del shell
# Para cualquier comando, puedes comparar:
< infile cmd1 | cmd2 > expected.txt
./pipex infile "cmd1" "cmd2" outfile.txt
diff expected.txt outfile.txt
# No debe haber diferencias