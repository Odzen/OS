# Se importan las librerias
import argparse
import threading
import time
import random

# Se define variables
estadoFilosofo = None
candados = []
CANTIDAD_FILOSOFOS = 0 
MAXIMO_INTENTOS_FALLIDOS = 10 
RAFAGA_COMER = 0
TOTAL_TIEMPO_COMER = 0   

ESTADO_FILOSOFEANDO = "F"
ESTADO_HAMBRIENTO = "H"
ESTADO_COMIENDO = "C"
ESTADO_SATISFECHO = "S"
ESTADO_MUERTO = "M"

# Función para que los filosofos tomen los palillos
def agarrarPalillos(id_filosofo):
    """Trata de tomar los palillos izquierdo y derecho (en ese orden) y 
       devuelve True si ha podido adquirir ambos y False de lo contrario"""

    palillo_izq = candados[id_filosofo] # palillo izquierdo
    palillo_der = candados[(id_filosofo - 1) % CANTIDAD_FILOSOFOS] # palillo derecho

    palillo_izq.acquire() # el palillo izquierdo adquiere un semaforo

    # Si el palillo derecho se invoca con blocking fijado en falso
    # entonces no se bloquea y devuelve true, es decir lo adquiere 
    if palillo_der.acquire(blocking=False):
        return True
    else:
        # caso contrario se libera el semaforo palillo izquierdo
        palillo_izq.release()
        return False


# Funcion para liberar los palillos adyacentes a los filosofos
def liberarPalillos(id_filosofo):
    """Liberación de los palillos adyacentes al filosofo"""
    candados[id_filosofo].release()  #palillo izquierdo
    candados[(id_filosofo - 1) % CANTIDAD_FILOSOFOS].release() #palillo derecho

# Función para la simulación de cada filosofo que son los hilos-------------------
def iniciarSimulacion(id_filosofo):
    """Función que va ejecutar cada filosofo(hilo)"""

    intentos_fallidos = 0
    tiempo_comiendo = 0

    while tiempo_comiendo < TOTAL_TIEMPO_COMER:
        if agarrarPalillos(id_filosofo):
            # Limpiar los intentos, ya que ha terminado de comer
            intentos_fallidos = 0

            #### Acción de comer
            tiempo_comer = min(RAFAGA_COMER, TOTAL_TIEMPO_COMER - tiempo_comiendo)
            tiempo_comiendo += tiempo_comer
            # Se imprime el filosofo y el tiempo comiendo
            print(f"[+] Filosofo {id_filosofo} comiendo [{tiempo_comer} seg.]")

            # Se pausa o suspende la ejecución del hilo de llamada durante el tiempo_comiendo
            time.sleep(tiempo_comiendo) 
            liberarPalillos(id_filosofo)

            ####  Filosofar
            estadoFilosofo[id_filosofo] = ESTADO_FILOSOFEANDO

            # Se genera número aleatorios de 0 a 5
            tiempo_filosofar = random.uniform(0, 5)

            # Se imprime el filosofo y el tiempo filosofando
            print(f"[*] Filosofo {id_filosofo} filosofando[{tiempo_filosofar:.2f} seg.]")
                     
              # Se pausa o suspende la ejecución del hilo de llamada durante el tiempo_filosofar
            time.sleep(tiempo_filosofar)
        else:
            # Cuando el estado del filosofo es hambriento ya tiene un intento fallido
            estadoFilosofo[id_filosofo] = ESTADO_HAMBRIENTO
            intentos_fallidos += 1

            # Cuando el número de intentos fallidos es mayor o igual al maximo de intentos,
            # el estado es muerto
            if intentos_fallidos >= MAXIMO_INTENTOS_FALLIDOS:
                estadoFilosofo[id_filosofo] = ESTADO_MUERTO

            # Se imprime el filosofo y esta muerto por falta de alimentos
                print(f"[-] Filosofo {id_filosofo} muerto por inanición")
                return
            
            tiempo_reintentar = random.uniform(0, 3)
            print(f"[ ] Filosofo {id_filosofo} esperando tenedores"
                  f" Intento {intentos_fallidos} [{tiempo_reintentar:.2f} seg.]")

            # Se pausa o suspende la ejecución del hilo de llamada durante el tiempo_reintentar
            time.sleep(tiempo_reintentar)
    

def obtenerArgumentos():
    """Función que lee los argumentos pasados por la línea de comandos"""

    # argparse genera automaticamente mensajes de ayuda, uso y muestra errores
    # si se dan parametros incorrectos

    # ArgumentParser tiene toda la información necesaria para analizar la línea de comandos
    parser = argparse.ArgumentParser()

    # Se añaden argumentos con el método add_argument
    parser.add_argument("-n", "--num_filosofos", 
                        type=int, default=5, help="Número de filósofos (hilos)")
    parser.add_argument("-r", "--rafaga_comer", 
                        type=int, default=4, help="Ráfaga de comer de los filósofos")
    parser.add_argument("-t", "--tiempo_total", 
                        type=int, default=10, help="Tiempo total que requiere comer un filosofo para estar satisfecho")
    parser.add_argument("-i", "--num_intentos", 
                        type=int, default=10, help="Cantidad de intentos antes de que el filósofo muera de inanición")
    
    # con parse_args se analiza los argumentos
    return parser.parse_args()


if __name__ == '__main__':
    args = obtenerArgumentos()

    # Establecer los argumentos leídos por línea de comandos
    CANTIDAD_FILOSOFOS = args.num_filosofos
    RAFAGA_COMER = args.rafaga_comer
    TOTAL_TIEMPO_COMER = args.tiempo_total
    MAXIMO_INTENTOS_FALLIDOS = args.num_intentos

    estadoFilosofo = CANTIDAD_FILOSOFOS * [ESTADO_FILOSOFEANDO]

    # Inicialización de candados
    for _ in range(CANTIDAD_FILOSOFOS):
        # threading.RLock() crea un bloqueo recursivo (múltiples bloqueos)
        # Se agrega los bloqueos en candados
        candados.append(threading.RLock()) 

    hilos = []
    for i in range(args.num_filosofos):
        nuevo_hilo = threading.Thread(target=iniciarSimulacion, args=(i,))
        # agrega el hilo al arreglo llamado hilos
        hilos.append(nuevo_hilo)
    
    # Iniciar ejecución de los hilos
    for hilo in hilos:
        hilo.start()

    # Esperar a que terminen todos los hilos
    for hilo in hilos:
        hilo.join()