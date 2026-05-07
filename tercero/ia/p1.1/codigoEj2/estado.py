# estado.py

def representacion_estado(cadena: str) -> tuple:
    """
    Convierte una cadena de 9 números enteros (ej. "123456780") 
    en una tupla de 9 enteros.
    """
    return tuple(int(caracter) for caracter in cadena)

def formatear_estado(estado: tuple) -> str:
    """
    Función auxiliar que genera un string formateado de un estado (matriz 3x3).
    El 0 (casilla vacía) se representa con un espacio en blanco para mayor claridad.
    """
    lineas = []
    # Recorremos la tupla en saltos de 3 para formar las filas
    for i in range(0, 9, 3):
        fila = estado[i:i+3]
        # Formateamos cada celda, cambiando el 0 por un espacio
        fila_str = [f"[{val}]" if val != 0 else "[ ]" for val in fila]
        lineas.append(" ".join(fila_str))
    
    return "\n".join(lineas)

def mostrar_estado(estado: tuple) -> None:
    """
    Muestra por pantalla una representación visual clara de un estado.
    """
    print(formatear_estado(estado))


class Problema:
    """
    Representa un problema del 8-puzzle con su estado inicial y objetivo.
    """
    # El estado objetivo por defecto es la tupla correspondiente a "123456780"
    def __init__(self, estado_inicial: tuple, estado_objetivo: tuple = (1, 2, 3, 4, 5, 6, 7, 8, 0)):
        self.estado_inicial = estado_inicial
        self.estado_objetivo = estado_objetivo

    def representacion_problema(self) -> str:
        """
        Devuelve una cadena de texto formateada mostrando el estado inicial 
        y el estado objetivo utilizando la función de representación visual.
        """
        resultado = "Estado Inicial:\n"
        resultado += formatear_estado(self.estado_inicial)
        resultado += "\n\nEstado Objetivo:\n"
        resultado += formatear_estado(self.estado_objetivo)
        return resultado

    def es_estado_objetivo(self, estado_evaluado: tuple) -> bool:
        """
        Comprueba si el estado dado es idéntico al estado objetivo del problema.
        """
        return estado_evaluado == self.estado_objetivo


def mostrar_problema(problema: Problema) -> None:
    """
    Muestra por pantalla una representación visual clara y amigable de un
    problema completo del 8-puzzle.
    """
    print(problema.representacion_problema())