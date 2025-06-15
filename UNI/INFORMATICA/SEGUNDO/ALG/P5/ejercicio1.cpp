#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Empresa {
    int acciones;
    double precio;
    double beneficio; //(porcentaje)
    double comision;
};

struct Solucion {
    double beneficioMax;
    vector<int> accionesCompradas; 
};

class AgenteFinanciero {
private:
    vector<Empresa> empresas;
    int dinero;
    int numEmpresas;
    vector<vector<double>> dp;
    vector<vector<int>> decision; // para recuperar solución

public:
    AgenteFinanciero(int dinero, vector<Empresa> emp) : dinero(dinero), empresas(emp) {
        numEmpresas = empresas.size();
        dp.assign(numEmpresas+1, vector<double>(dinero+1, 0));
        decision.assign(numEmpresas+1, vector<int>(dinero+1, 0));
    }

    Solucion resolver() {

        for (int i = 1; i <= numEmpresas; i++) {
            for (int j = 0; j <= dinero; j++) {
                // Posibilidad de no comprar acciones de esa empresa
                // (tabla iguaal a paso anterior)
                dp[i][j] = dp[i-1][j];
                decision[i][j] = 0;

                // Miramos si es posible y optimo comprar
                double costoAccion = empresas[i-1].precio + empresas[i-1].comision;
                double beneficioAccion = empresas[i-1].beneficio * empresas[i-1].precio;

                int maxAcciones = min(empresas[i-1].acciones, (int)(j / costoAccion));

                for (int k = 1; k <= maxAcciones; k++) {
                    double costo = k * costoAccion;
                    double beneficio = k * beneficioAccion;

                    if (j >= costo) {
                        double nuevoBeneficio = dp[i-1][j - (int)costo] + beneficio;
                        if (nuevoBeneficio > dp[i][j]) {
                            dp[i][j] = nuevoBeneficio;
                            decision[i][j] = k;
                        }
                    }
                }
            }
        }
        return recuperarSolucion();
    }

private:
    Solucion recuperarSolucion() {
        Solucion sol;
        sol.beneficioMax = dp[numEmpresas][dinero];
        sol.accionesCompradas.assign(numEmpresas, 0);

        int i = numEmpresas, j = dinero;
        while (i > 0 && j > 0) {
            int accionesCompradas = decision[i][j];
            sol.accionesCompradas[i-1] = accionesCompradas;

            if (accionesCompradas > 0) {
                double costoAccion = empresas[i-1].precio + empresas[i-1].comision;
                j -= (int)(accionesCompradas * costoAccion);
            }
            i--;
        }

        return sol;
    }

public:
    void mostrarTabla() {
        cout << "Tabla DP:" << endl;
        for (int i = 0; i <= numEmpresas; i++) {
            for (int j = 0; j <= min(20, dinero); j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Ejemplo de uso
    vector<Empresa> empresas = {
        {5, 10.0, 0.15, 2.0},  // 5 acciones, 10€/acción, 15% beneficio, 2€ comisión
        {3, 20.0, 0.25, 3.0},  // 3 acciones, 20€/acción, 25% beneficio, 3€ comisión
        {4, 15.0, 0.20, 1.5}   // 4 acciones, 15€/acción, 20% beneficio, 1.5€ comisión
    };

    AgenteFinanciero inversion(100, empresas);
    Solucion sol = inversion.resolver();

    cout << "Beneficio máximo: " << sol.beneficioMax << " euros" << endl;
    cout << "Acciones a comprar por empresa:" << endl;
    for (int i = 0; i < empresas.size(); i++) {
        cout << "Empresa " << i+1 << ": " << sol.accionesCompradas[i] << " acciones" << endl;
    }

    return 0;
}