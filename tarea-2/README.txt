En nuestro caso utilizamos visual studio code con la terminal WSL para 
compilar y ejecutar el código.
para compilar, se debe usar el comando: 

	g++ (nombre del archivo) -Wall -o ejecutable.out

luego, para ejecutar el código ya compilado debemos utilizar el comando: 

	./ejecutable.out

en la pregunta 1 y 2 incluimos un ejemplo.txt, el cual se lee por defecto. Si desease leer otro
archivo de nombre distino, deberá modificar el codigo fuente o usar un archivo de mismo nombre.
En la seccion de operaciones (COEFICIENTE o EVLUAR), si la operacion no calza no habrá mayor
inconveniente, sin embargo, si el string y los numeros no tienen el mismo formato el codigo es 
propenso a errores y bugs. Finalmente, el programa no esta diseñado para leer monomios de mismo 
exponente, sin embargo consideramos que dejaria de ser un polinomio y suponemos que eso no ocurrirá