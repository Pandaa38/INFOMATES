#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class AsignadorArbitros {
private:
    int n;                          // Número de equipos
    int m;                          // Número de árbitros
    vector<vector<int>> preferencias; // Matriz de preferencias p[equipo][arbitro]
    vector<pair<int, int>> partidos; // Lista de emparejamientos (partidos)

    vector<bool> arbitro_usado;     // Control de árbitros ya asignados
    vector<int> asignacion_actual;  // Asignación actual de árbitros a partidos
    vector<int> mejor_asignacion;   // Mejor asignación encontrada
    int mejor_valor;                // Mejor valor de la función objetivo encontrado

public:
    AsignadorArbitros() : mejor_valor(-1) {}

    void datosIniciales() {
        n = 4;
        m = 4;

        preferencias = {
            {1, 9, 3, 7}, // Preferencias del equipo 0
            {2, 6, 8, 5}, // Preferencias del equipo 1
            {9, 1, 4, 3}, // Preferencias del equipo 2
            {5, 2, 7, 10} // Preferencias del equipo 3
        };

        partidos = {{0, 1}, {2, 3}}; // Partidos: (0,1) y (2,3)

        // Inicializar estructuras para la búsqueda
        arbitro_usado.assign(m, false);
        asignacion_actual.resize(n/2);
        mejor_asignacion.resize(n/2);
        mejor_valor = -1;
    }
    void resolver() {
        asignarArbitrosBB(0, 0);
    }
    void mostrarResultados() {
        if (mejor_valor == -1) {
            cout << "No se encontró ninguna solución válida." << endl;
            return;
        }

        cout << "\n===== RESULTADOS =====" << endl;
        cout << "Mejor puntuación total: " << mejor_valor << endl;
        cout << "\nAsignación de árbitros:" << endl;

        for (int k = 0; k < partidos.size(); k++) {
            int equipo1 = partidos[k].first;
            int equipo2 = partidos[k].second;
            int arbitro = mejor_asignacion[k];

            cout << "Partido " << k << ": Equipo " << equipo1 << " vs Equipo " << equipo2
                 << " -> Árbitro " << arbitro << endl;
            cout << "   Preferencias: Equipo " << equipo1 << ": " << preferencias[equipo1][arbitro]
                 << ", Equipo " << equipo2 << ": " << preferencias[equipo2][arbitro] << endl;
            cout << "   Contribución: " << preferencias[equipo1][arbitro] * preferencias[equipo2][arbitro] << endl;
        }

        cout << "\nVerificación del resultado:" << endl;
        int suma = 0;
        for (int k = 0; k < partidos.size(); k++) {
            int equipo1 = partidos[k].first;
            int equipo2 = partidos[k].second;
            int arbitro = mejor_asignacion[k];

            suma += preferencias[equipo1][arbitro] * preferencias[equipo2][arbitro];
        }
        cout << "Suma total de productos: " << suma << " (debe ser igual a " << mejor_valor << ")" << endl;
    }

private:
    int calcularCotaSuperior(int k, int valor_parcial) {
        int cota = valor_parcial;

        for (int i = k; i < partidos.size(); i++) {
            int equipo1 = partidos[i].first;
            int equipo2 = partidos[i].second;
            int mejor_producto = 0;

            for (int arb = 0; arb < m; arb++) {
                if (!arbitro_usado[arb]) {
                    int producto = preferencias[equipo1][arb] * preferencias[equipo2][arb];
                    mejor_producto = max(mejor_producto, producto);
                }
            }
            cota += mejor_producto;
        }
        return cota;
    }

    void asignarArbitrosBB(int k, int valor_parcial) {
        /////////////////////////////////////////////////////
        // Caso base:
        if (k == partidos.size()) {
            if (valor_parcial > mejor_valor) {
                mejor_valor = valor_parcial;
                mejor_asignacion = asignacion_actual;
            }
            return;
        }
        /////////////////////////////////////////////////////

        int cota = calcularCotaSuperior(k, valor_parcial);
        if (cota <= mejor_valor) {
            return; // Poda: no hay posibilidad de mejorar la solución actual
        }

        // Intentamos asignar un árbitro libre al partido k
        int equipo1 = partidos[k].first;
        int equipo2 = partidos[k].second;

        vector<pair<int, int>> productos; // (producto, árbitro)
        for (int arb = 0; arb < m; arb++) {
            if (!arbitro_usado[arb]) {
                int producto = preferencias[equipo1][arb] * preferencias[equipo2][arb];
                productos.push_back({producto, arb});
            }
        }

        sort(productos.rbegin(), productos.rend());

        for (const auto& [producto, arb] : productos) {
            arbitro_usado[arb] = true;
            asignacion_actual[k] = arb;

            asignarArbitrosBB(k + 1, valor_parcial + producto);

            arbitro_usado[arb] = false;
        }
    }
};

int main() {
    AsignadorArbitros asignador;

    asignador.datosIniciales();

    asignador.resolver();
    asignador.mostrarResultados();

    return 0;
}
