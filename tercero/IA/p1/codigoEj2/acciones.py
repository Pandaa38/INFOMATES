# acciones.py
import estado  # Importamos el módulo previo para poder usarlo en pruebas si es necesario

# ==========================================
# PRECONDICIONES (Condiciones de aplicabilidad)
# ==========================================

def EsAplicableU(estado: tuple) -> bool:
    """Devuelve True si el 0 NO está en la primera fila (índices 0, 1, 2)."""
    indice_cero = estado.index(0)
    return indice_cero not in (0, 1, 2)

def EsAplicableD(estado: tuple) -> bool:
    """Devuelve True si el 0 NO está en la última fila (índices 6, 7, 8)."""
    indice_cero = estado.index(0)
    return indice_cero not in (6, 7, 8)

def EsAplicableL(estado: tuple) -> bool:
    """Devuelve True si el 0 NO está en la primera columna (índices 0, 3, 6)."""
    indice_cero = estado.index(0)
    return indice_cero not in (0, 3, 6)

def EsAplicableR(estado: tuple) -> bool:
    """Devuelve True si el 0 NO está en la última columna (índices 2, 5, 8)."""
    indice_cero = estado.index(0)
    return indice_cero not in (2, 5, 8)


# ==========================================
# EFECTOS (Funciones de estado resultante)
# ==========================================

def _intercambiar(estado_actual: tuple, idx1: int, idx2: int) -> tuple:
    """
    Función auxiliar para intercambiar dos posiciones.
    Como las tuplas son inmutables, convertimos a lista, intercambiamos y volvemos a tupla.
    """
    lista_estado = list(estado_actual)
    lista_estado[idx1], lista_estado[idx2] = lista_estado[idx2], lista_estado[idx1]
    return tuple(lista_estado)

def EfectoU(estado: tuple) -> tuple:
    """Mueve el 0 hacia Arriba: intercambia con el índice - 3."""
    indice_cero = estado.index(0)
    return _intercambiar(estado, indice_cero, indice_cero - 3)

def EfectoD(estado: tuple) -> tuple:
    """Mueve el 0 hacia Abajo: intercambia con el índice + 3."""
    indice_cero = estado.index(0)
    return _intercambiar(estado, indice_cero, indice_cero + 3)

def EfectoL(estado: tuple) -> tuple:
    """Mueve el 0 hacia la Izquierda: intercambia con el índice - 1."""
    indice_cero = estado.index(0)
    return _intercambiar(estado, indice_cero, indice_cero - 1)

def EfectoR(estado: tuple) -> tuple:
    """Mueve el 0 hacia la Derecha: intercambia con el índice + 1."""
    indice_cero = estado.index(0)
    return _intercambiar(estado, indice_cero, indice_cero + 1)


# ==========================================
# FUNCIÓN DE TRANSICIÓN (Dinámica del mundo)
# ==========================================

def AplicaOperador(operador: str, estado: tuple) -> tuple | None:
    """
    Evalúa y aplica un operador ('U', 'D', 'L', 'R') a un estado.
    Si el operador es aplicable, devuelve la nueva tupla del estado.
    Si no es aplicable, devuelve None.
    """
    if operador == 'U':
        if EsAplicableU(estado):
            return EfectoU(estado)
            
    elif operador == 'D':
        if EsAplicableD(estado):
            return EfectoD(estado)
            
    elif operador == 'L':
        if EsAplicableL(estado):
            return EfectoL(estado)
            
    elif operador == 'R':
        if EsAplicableR(estado):
            return EfectoR(estado)
            
    # Si el operador no es válido o no es aplicable
    return None