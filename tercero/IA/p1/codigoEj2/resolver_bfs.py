# resolver_bfs.py
from collections import deque
import estado
import espacio

# ==========================================
# GESTIÓN DE LA FRONTERA (Modularidad)
# ==========================================

def iniciar_frontera() -> deque:
    """Crea y devuelve la estructura de datos para la frontera de exploración."""
    return deque()

def insertar_en_frontera(frontera: deque, nodo: tuple) -> None:
    """Inserta un nuevo nodo en la frontera."""
    frontera.append(nodo)

def extraer_de_frontera(frontera: deque) -> tuple:
    """
    Extrae un nodo de la frontera.
    Al usar popleft(), implementamos una Cola (FIFO) para Búsqueda en Anchura (BFS).
    Si quisieras cambiar a Búsqueda en Profundidad (DFS), solo tendrías que 
    cambiar esta línea por: return frontera.pop() (Pila / LIFO).
    """
    return frontera.popleft()

def frontera_vacia(frontera: deque) -> bool:
    """Comprueba si la frontera está vacía."""
    return len(frontera) == 0

# ==========================================
# ALGORITMO DE BÚSQUEDA
# ==========================================

def Soluciona8Puzzle(problema: estado.Problema) -> list | None:
    """
    Resuelve el problema del 8-puzzle utilizando Búsqueda en Anchura (BFS).
    
    Recibe una instancia de la clase Problema.
    Devuelve una lista de cadenas con la secuencia de operadores solución
    (ej. ['U', 'L', 'D', 'R']) o None si no se encuentra solución.
    """
    # 1. Comprobación inicial: ¿Es el estado inicial ya la solución?
    if problema.es_estado_objetivo(problema.estado_inicial):
        return []
        
    # 2. Inicializamos la frontera y el conjunto de estados visitados
    frontera = iniciar_frontera()
    # Un nodo es una tupla: (estado_actual, lista_de_operadores_hasta_aqui)
    nodo_inicial = (problema.estado_inicial, [])
    insertar_en_frontera(frontera, nodo_inicial)
    
    # Usamos un 'set' para búsquedas O(1). 
    # Guardamos el estado inicial como visitado desde el principio.
    visitados = set()
    visitados.add(problema.estado_inicial)
    
    # 3. Bucle principal de exploración
    while not frontera_vacia(frontera):
        # Extraemos el siguiente nodo según la política de la frontera (FIFO para BFS)
        estado_actual, camino_actual = extraer_de_frontera(frontera)
        
        # Generamos los sucesores para el estado actual
        sucesores = espacio.EstadosSucesores(estado_actual)
        
        for operador, estado_sucesor in sucesores:
            # Si no hemos visitado este estado antes, lo exploramos
            if estado_sucesor not in visitados:
                nuevo_camino = camino_actual + [operador]
                
                # Comprobación de estado objetivo al generar (Early Goal Test)
                if problema.es_estado_objetivo(estado_sucesor):
                    return nuevo_camino
                
                # Marcamos como visitado y lo añadimos a la frontera para futura expansión
                visitados.add(estado_sucesor)
                nodo_sucesor = (estado_sucesor, nuevo_camino)
                insertar_en_frontera(frontera, nodo_sucesor)
                
    # Si la frontera se vacía y no hemos devuelto nada, no hay solución posible
    return None