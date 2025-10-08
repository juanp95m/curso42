#!/bin/bash

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Contador de pruebas
PASSED=0
FAILED=0

echo -e "${YELLOW}=== INICIANDO PRUEBAS DE PIPEX ===${NC}\n"

# Compilar el proyecto
echo -e "${YELLOW}Compilando el proyecto...${NC}"
make re
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Error al compilar${NC}"
    exit 1
fi
echo -e "${GREEN}✅ Compilación exitosa${NC}\n"

# Función para ejecutar una prueba
run_test() {
    local test_name=$1
    local input_file=$2
    local cmd1=$3
    local cmd2=$4
    local expected_behavior=$5
    
    echo -e "${YELLOW}Prueba: $test_name${NC}"
    
    # Ejecutar pipex
    ./pipex "$input_file" "$cmd1" "$cmd2" outfile.txt 2>/dev/null
    pipex_exit=$?
    
    # Ejecutar equivalente en shell
    if [ -f "$input_file" ]; then
        < "$input_file" $cmd1 | $cmd2 > expected.txt 2>/dev/null
        shell_exit=$?
    else
        touch expected.txt
        shell_exit=1
    fi
    
    # Comparar resultados
    if [ -f outfile.txt ] && [ -f expected.txt ]; then
        if diff -q outfile.txt expected.txt >/dev/null; then
            echo -e "${GREEN}✅ PASÓ${NC}"
            ((PASSED++))
        else
            echo -e "${RED}❌ FALLÓ - Diferente salida${NC}"
            echo "Pipex output:"
            cat outfile.txt | head -3
            echo "Expected output:"
            cat expected.txt | head -3
            ((FAILED++))
        fi
    else
        echo -e "${RED}❌ FALLÓ - Archivo de salida no creado${NC}"
        ((FAILED++))
    fi
    
    # Limpiar archivos temporales
    rm -f outfile.txt expected.txt
    echo
}

# Preparar archivos de prueba
echo -e "Hola mundo\nSegunda línea\n42 Madrid\nCuarta línea" > test_input.txt
echo -e "zebra\napple\nbanana\ncherry" > sort_input.txt
seq 1 100 > numbers.txt
touch empty_file.txt

# PRUEBAS BÁSICAS
echo -e "${YELLOW}=== PRUEBAS BÁSICAS ===${NC}"
run_test "Cat + Grep básico" "test_input.txt" "cat" "grep mundo"
run_test "Cat + Wc líneas" "test_input.txt" "cat" "wc -l"
run_test "Cat + Sort" "sort_input.txt" "cat" "sort"
run_test "Cat + Head" "numbers.txt" "cat" "head -5"

# PRUEBAS CON ARGUMENTOS
echo -e "${YELLOW}=== PRUEBAS CON ARGUMENTOS ===${NC}"
run_test "Grep con patrón" "test_input.txt" "cat" "grep -i MADRID"
run_test "Wc palabras" "test_input.txt" "cat" "wc -w"

# PRUEBAS DE CASOS ESPECIALES
echo -e "${YELLOW}=== CASOS ESPECIALES ===${NC}"
run_test "Archivo vacío" "empty_file.txt" "cat" "wc -l"

# Prueba manual para argumentos incorrectos
echo -e "${YELLOW}Prueba: Argumentos incorrectos${NC}"
./pipex test_input.txt "cat" 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✅ PASÓ - Maneja argumentos incorrectos${NC}"
    ((PASSED++))
else
    echo -e "${RED}❌ FALLÓ - No valida argumentos${NC}"
    ((FAILED++))
fi
echo

# Prueba manual para archivo inexistente
echo -e "${YELLOW}Prueba: Archivo inexistente${NC}"
./pipex archivo_que_no_existe.txt "cat" "wc -l" outfile.txt 2>/dev/null
if [ ! -s outfile.txt ] || [ ! -f outfile.txt ]; then
    echo -e "${GREEN}✅ PASÓ - Maneja archivo inexistente${NC}"
    ((PASSED++))
else
    echo -e "${RED}❌ FALLÓ - No maneja archivo inexistente${NC}"
    ((FAILED++))
fi
rm -f outfile.txt
echo

# RESUMEN
echo -e "${YELLOW}=== RESUMEN DE PRUEBAS ===${NC}"
echo -e "Pruebas pasadas: ${GREEN}$PASSED${NC}"
echo -e "Pruebas fallidas: ${RED}$FAILED${NC}"
echo -e "Total: $((PASSED + FAILED))"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ¡TODAS LAS PRUEBAS PASARON!${NC}"
else
    echo -e "\n${RED}❌ Algunas pruebas fallaron. Revisa tu implementación.${NC}"
fi

# Limpiar archivos de prueba
rm -f test_input.txt sort_input.txt numbers.txt empty_file.txt outfile.txt expected.txt

echo -e "\n${YELLOW}=== PRUEBAS COMPLETADAS ===${NC}"