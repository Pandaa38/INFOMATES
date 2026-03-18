# espacio.py
import estado
import acciones

def EstadosSucesores(estado_actual: tuple) -> list:
    """
    Genera los estados sucesores válidos para un estado dado del 8-puzzle.
    
    Recibe un estado (tupla de 9 enteros) y evalúa los cuatro movimientos 
    posibles. Devuelve una lista de tuplas, donde cada tupla contiene 
    el operador aplicado y el estado resultante.
    """
    sucesores = []
    operadores = ['U', 'D', 'L', 'R']
    
    for operador in operadores:
        # Calculamos el posible nuevo estado llamando a la función de transición
        nuevo_estado = acciones.AplicaOperador(operador, estado_actual)
        
        # Si la acción es aplicable (no devuelve None), guardamos el par
        if nuevo_estado is not None:
            sucesores.append((operador, nuevo_estado))
            
    return sucesores