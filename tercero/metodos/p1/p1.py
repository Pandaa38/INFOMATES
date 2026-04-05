import numpy as np
import matplotlib.pyplot as plt

### EJ1 

# 1. Definir la malla de puntos en el cuadrado [-2, 2] x [-2, 2]
x = np.linspace(-2, 2, 500)
y = np.linspace(-2, 2, 500)
X, Y = np.meshgrid(x, y)

# 2. Definir las funciones f(x, y) y g(x, y) dadas en el sistema
def f(x, y):
    return 2*x**5 - 20*x**3*y**2 - 4*x**3*y + 10*x*y**4 + 4*x*y**3 - 2*x

def g(x, y):
    return 10*x**4*y + x**4 - 20*x**2*y**3 - 6*x**2*y**2 + 2*y**5 + y**4 - 2*y - 1

# 3. Evaluar las funciones en la malla bidimensional
Z_f = f(X, Y)
Z_g = g(X, Y)

# 4. Crear la representación gráfica
plt.figure(figsize=(8, 8))

# Dibujar f(x,y) = 0 en azul y g(x,y) = 0 en rojo
plt.contour(X, Y, Z_f, levels=[0], colors='blue', linewidths=2)
plt.contour(X, Y, Z_g, levels=[0], colors='red', linewidths=2)

# TRUCO CORREGIDO (Proxy artists): Crear líneas vacías solo para la leyenda
plt.plot([], [], color='blue', linewidth=2, label='f(x,y) = 0')
plt.plot([], [], color='red', linewidth=2, label='g(x,y) = 0')

# Detalles estéticos de la gráfica
plt.title('Puntos de corte de las curvas implícitas')
plt.xlabel('x')
plt.ylabel('y')
plt.axhline(0, color='black', linewidth=1, linestyle='--') # Eje X
plt.axvline(0, color='black', linewidth=1, linestyle='--') # Eje Y
plt.grid(True, linestyle=':', alpha=0.7)
plt.legend(loc='upper right')
plt.xlim([-2, 2])
plt.ylim([-2, 2])

# Mostrar la gráfica
plt.show()

## EJ2


