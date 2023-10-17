# Risk-Estructura-de-Datos
Risk clase estructura de datos


##  Descripción del problema
Risk® es un juego de mesa basado en turnos, cuyo objetivo es la conquista de territorios a través de representaciones de ejércitos, eliminando jugadores oponentes en el proceso. Cada jugador inicia con una cierta cantidad
de unidades de ejército ubicadas en algunos territorios del tablero. Para cumplir el objetivo, cada jugador debe
atacar territorios vecinos, intentando ocuparlos en el ataque, lo cual se decide con el lanzamiento de dados. El
juego termina cuando un jugador ha cumplido con su misión (que puede ser la ocupación de territorios específicos
o incluso la ocupación de todos los territorios del tablero)


http://www.hasbro.com/common/instruct/risk.pdf


# Running App
```
sh ejecutar_programa.sh
```

# Dummy Data
Puedes copiar todos los renglones de input.txt y pegarlos en la terminal despues de correr el programa para inicializar algunos valores de prueba.


# Running tests (Not developed yet)
Install the google test library
```
sudo apt update
sudo apt install libgtest-dev -y
cd /usr/src/gtest && sudo  cmake CMakeLists.txt && sudo make
sudo cp /usr/src/googletest/googletest/lib/libgtest.a /usr/src/googletest/googletest/lib/lib
gtest_main.a /usr/lib
g++ -o test tests.cpp -lgtest -lpthread
./tests
```