El comando: ls | grep .c | wc -l
(Traducido: Lista los archivos -> Filtra solo los que terminan en .c -> Cuenta cuántas líneas son)

Imagina que tienes 3 trabajadores (procesos hijos) en una cadena de montaje.

Hijo 1 (ls): Genera datos (nombres de archivos).
Hijo 2 (grep): Recibe datos, filtra y pasa los resultados.
Hijo 3 (wc): Recibe datos, cuenta y muestra el resultado final en pantalla.
El padre (picoshell) es el capataz que organiza las mesas (tuberías) entre ellos.

Paso a Paso (Vuelta por Vuelta del Bucle)
Variable clave: last_fd (Guardará el conector de lectura para el siguiente trabajador). Empieza en -1.

🔄 Vuelta 1: ls (El primer comando)
1. ¿Hay siguiente comando? Sí (grep).

    - Acción: El padre crea una Tubería A (pipe(fd)).
        Estado: Tenemos un tubo A. Escribes por fd[1], lees por fd[0].

fork() -> Nace Hijo 1 (ls)

2. Hijo 1 dice:

    - Manejo error por si fork falla
        - (Si fallara) Compruebo si el pipe fue creado (sí, hay grep).
            -Cierro fds
        - Retorno 1

    - Si el hijo se creo bien (PID == 0)
        - Si tengo un last_fd ?? NO
        - Si hay siguiente comando? SI GREP
            - cierro el extremo de escritura del pipe actual fd[0].
            - redirijo mi salida al extremo escritura (fd[1])
                - si falla hago exit 1
            - cierro last_fd
        - Ejecuto: ls. (Mis datos viajan por la Tubería A).
        - si hay error salgo con exit 1

    - Padre dice si tengo una tuberia abierta?? NO
    - si hay un siguiente comando?? si grep
        - cerramos el extremo escritura
        - guardamos el extremo de lectura en last_fd
    - iteramos i++


🔄 Vuelta 2: grep .c (El comando del medio)
1. ¿Hay siguiente comando? Sí (grep).

    - Acción: El padre crea una Tubería B (pipe(fd)).
        Estado: Tenemos un tubo B nuevo. Last_fd  apunta a la lectura del tubo A.

fork() -> Nace Hijo 2 (grep)

2. Hijo 2 dice:
    - Manejo error por si fork falla
        - Compruebo si el pipe fue creado
            -Cierro fds (fd[0] y fd[1])
        - Retorno 1

    - Si el hijo se creo bien (PID == 0)
        - Si tengo un last_fd?(Lectura Tubo A)
            - redirijo mi entrada a last fd
                - si falla hago exit 1
            - cierro last_fd
        - Si hay siguiente comando? si (wc)
            - cierro el extremo de escritra del pipe actual (fd[0], Tubo B)
            - redirijo mi salida al extremo escritura (fd[1], Tubo B) 
                - si falla hago exit 1
            - cierro last_fd
        - Ejecuto: grep .c  (Leo de A, escribo en B).
        - si hay error salgo con exit 1

    - Padre dice si tengo una tuberia abierta? Sí (Tubo A).
        - la cierro
    - si hay un siguiente comando si (wc)
        - cerramos el extremo escritura (fd[1], Tubo B)
        - guardamos el extremo de lectura en last_fd ahora apunta al Tubo B.
    - iteramos i++

🔄 Vuelta 3: wc -l (El ultimo comando)
1. ¿Hay siguiente comando? No (cmds[3] es NULL)

    - Acción: No se crea ninguna tubería nueva.
        Estado: No hay tubo nuevo. last_fd apunta a la lectura del tubo B

fork() -> Nace Hijo 3 (wc)

2. Hijo 3 dice:
    - Manejo error por si fork falla
        - (Si fallara) Compruebo si el pipe fue creado (NO)
            - NO Cierro fds (fd[0] y fd[1])
        - Retorno 1

    - Si el hijo se creo bien (PID == 0)
        - Si tengo un last_fd?(Lectura Tubo B)
            - redirijo mi entrada a last fd
                - si falla hago exit 1
            - cierro last_fd
        - Si hay siguiente comando? NO
        - Ejecuto: wc -l .
        - si hay error salgo con exit 1

    - Padre dice si tengo una tuberia abierta? Sí (Tubo B).
        - la cierro
    - si hay un siguiente comando? NO
    - iteramos i++

FIN DEL BUCLE WHILE:
Esperamos a que todos los hijos terminen (wait) y si terminan de forma inesperada o con error (status != 0), hacemos exit_code = 1 y salimos retornando ese código.

