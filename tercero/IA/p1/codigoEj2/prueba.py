# prueba.py
import estado
import acciones
import resolver_bfs
import time

def probar_8_puzzle():
    # =================================================================
    # 1. DEFINE AQUÍ TU ESTADO INICIAL
    # =================================================================
    # Modifica esta cadena para probar diferentes configuraciones.
    # Recuerda: deben ser los números del 0 al 8 sin repetir.
    # Ejemplos de prueba:
    # "123456780" -> Ya es el objetivo (0 pasos)
    # "123456708" -> A 1 paso (R)
    # "123406758" -> A 2 pasos (D, R)
    # "283164705" -> Requiere varios pasos
    
    cadena_inicial = "123456870" 
    
    print(f"--- INICIANDO PRUEBA CON ESTADO: {cadena_inicial} ---\n")
    
    # Convertimos la cadena a la representación interna (tupla)
    est_inicial = estado.representacion_estado(cadena_inicial)
    
    # =================================================================
    # 2. CREACIÓN DEL PROBLEMA Y BÚSQUEDA DE SOLUCIÓN
    # =================================================================
    
    # Instanciamos el problema (el objetivo por defecto es 123456780)
    mi_problema = estado.Problema(est_inicial)
    
    # Mostramos el planteamiento
    estado.mostrar_problema(mi_problema)
    print("\nBuscando solución mediante BFS (Búsqueda en Anchura)...")
    
    # Medimos el tiempo que tarda (opcional pero útil)
    inicio_tiempo = time.time()
    
    # Llamamos a nuestro solucionador
    solucion = resolver_bfs.Soluciona8Puzzle(mi_problema)
    
    fin_tiempo = time.time()
    tiempo_transcurrido = fin_tiempo - inicio_tiempo
    
    # =================================================================
    # 3. MOSTRAR RESULTADOS Y VISUALIZAR PASO A PASO
    # =================================================================
    
    if solucion is not None:
        print(f"\n¡Solución encontrada en {len(solucion)} movimientos!")
        print(f"Tiempo de resolución: {tiempo_transcurrido:.4f} segundos")
        print("Secuencia de operadores:", solucion)
        
        estado_actual = est_inicial
        print("\nESTADO INICIAL:")
        estado.mostrar_estado(estado_actual)
        
        for paso, operador in enumerate(solucion, 1):
            print(f"\n--- Paso {paso}: Aplicando movimiento '{operador}' ---")
            # Aplicamos la acción usando nuestra función de transición
            estado_actual = acciones.AplicaOperador(operador, estado_actual)
            estado.mostrar_estado(estado_actual)
            time.sleep(0.5) # Pausa medio segundo para un efecto visual agradable
            
        print("\n¡Objetivo alcanzado!")
            
    else:
        print("\nNo se ha encontrado ninguna solución. (Nota: La mitad de los estados del 8-puzzle no tienen solución matemática válida).")

if __name__ == "__main__":
    probar_8_puzzle()