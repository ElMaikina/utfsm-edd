En nuestro caso utilizamos Visual Studio Code con la terminal nativa de Ubuntu para 
compilar y ejecutar el código. para compilar, se debe usar la terminal. 
Se utiliza el comando g++ (nombre del archivo) -Wall -o ejecutable.out
para ejecutar el archivo desde la terminal debemos utilizar el comando 
./ejecutable.out

El main de nuestro programa es tarea3.cpp, especificaremos abajo los demas detalles.

Cambiamos el nombre de las variables de los structs al inglés, sin embargo el funcionamiento
es el mismo, esto lo hicimos con el final de acortar las lineas de codigo y facilitar la lectura
ya que el inglés tiene palabras más cortas, además nos facilitó a la hora de trabajar en equipo
ya que las variables eran intuitivas a la vista y el condigo era menos denso.

Dividimos el trabajo en tres headers distintos, para que el programa se ejecute deben
estar "codes.cpp", "h_discount.cpp" y "h_product.cpp". Además de esto, deben estar los
archivos "productos.dat", "ofertas.dat" y "compras.txt", el programa solo acepta esos
nombres. Una vez ejecutado el programa, se creará un archivo "boletas.txt", con el numero
de boletas creadas, y siguiendole sus respectivos precios finales correspondientes a cada
cliente. 

Además agregar que el programa imprime por pantalla las tablas de Hashing para
productos y descuentos por separado y el seguimiento de la cuota completa y los descuentos.
