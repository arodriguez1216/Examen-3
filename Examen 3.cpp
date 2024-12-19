#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>

using namespace std;


int stringToInt(const string &str) {
    int result = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result;
}


class Empleado {
private:
    string cedula;
    string nombre;
    string fechaNacimiento;
    string categoria;
    double salario;
    string direccion;
    string telefono;
    string correo;
    static vector<string> correosUtilizados; 
    int calcularEdad() const {
    
        return 25; 
    }

public:
    Empleado(string c, string n, string fn, string cat, double sal = 250000, string dir = "San José", string tel = "", string cor = "") 
        : cedula(c), nombre(n), fechaNacimiento(fn), categoria(cat), salario(sal), direccion(dir), telefono(tel), correo(cor) {
        
        
        if (calcularEdad() < 18) {
            throw invalid_argument("No se pueden contratar empleados menores de edad.");
        }

        if (salario < 250000 || salario > 500000) {
            throw invalid_argument("El salario debe estar entre 250,000 y 500,000.");
        }

        if (categoria != "Administrador" && categoria != "Operario" && categoria != "Peon") {
            throw invalid_argument("La categoría debe ser 'Administrador', 'Operario' o 'Peón'.");
        }

        
        for (size_t i = 0; i < correosUtilizados.size(); ++i) {
            if (correosUtilizados[i] == correo) {
                throw invalid_argument("El correo ya está en uso.");
            }
        }

        correosUtilizados.push_back(correo);
    }

    
    string getCedula() const { return cedula; }
    string getNombre() const { return nombre; }
    string getFechaNacimiento() const { return fechaNacimiento; }
    string getCategoria() const { return categoria; }
    double getSalario() const { return salario; }
    string getDireccion() const { return direccion; }
    string getTelefono() const { return telefono; }
    string getCorreo() const { return correo; }

    void mostrarInfo() const {
        cout << "Cédula: " << cedula << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Fecha de Nacimiento: " << fechaNacimiento << endl;
        cout << "Categoría: " << categoria << endl;
        cout << "Salario: " << salario << endl;
        cout << "Dirección: " << direccion << endl;
        cout << "Teléfono: " << telefono << endl;
        cout << "Correo: " << correo << endl;
    }
};

vector<string> Empleado::correosUtilizados;  


class Proyecto {
private:
    string codigo;
    string nombre;
    string fechaInicio;
    string fechaFin;
    static vector<string> nombresProyectos;

public:
    Proyecto(string cod, string nom, string fInicio, string fFin)
        : codigo(cod), nombre(nom), fechaInicio(fInicio), fechaFin(fFin) {

        
        for (size_t i = 0; i < nombresProyectos.size(); ++i) {
            if (nombresProyectos[i] == nombre) {
                throw invalid_argument("El nombre del proyecto ya está en uso.");
            }
        }

        nombresProyectos.push_back(nombre);
    }

    
    string getCodigo() const { return codigo; }
    string getNombre() const { return nombre; }
    string getFechaInicio() const { return fechaInicio; }
    string getFechaFin() const { return fechaFin; }

    void mostrarInfo() const {
        cout << "Código: " << codigo << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Fecha de Inicio: " << fechaInicio << endl;
        cout << "Fecha de Finalización: " << fechaFin << endl;
    }
};

vector<string> Proyecto::nombresProyectos;  


class Asignacion {
private:
    Empleado* empleado;
    Proyecto* proyecto;
    string fechaAsignacion;

public:
    Asignacion(Empleado* emp, Proyecto* proy) : empleado(emp), proyecto(proy) {
        time_t now = time(0);
        char* dt = ctime(&now);
        fechaAsignacion = string(dt);
    }

    void mostrarAsignacion() const {
        cout << "Empleado: " << empleado->getNombre() << endl;
        cout << "Proyecto: " << proyecto->getNombre() << endl;
        cout << "Fecha de Asignación: " << fechaAsignacion << endl;
    }
};


int main() {
    vector<Empleado*> empleados;
    vector<Proyecto*> proyectos;
    vector<Asignacion*> asignaciones;
    
    string cedula, nombre, fechaNacimiento, categoria, direccion, telefono, correo;
    double salario;
    string codProyecto, nombreProyecto, fechaInicio, fechaFin;

    while (true) {
        int opcion;
        cout << "\n1. Ingresar empleado" << endl;
        cout << "2. Ingresar proyecto" << endl;
        cout << "3. Asignar empleado a proyecto" << endl;
        cout << "4. Ver asignaciones" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();  

        if (opcion == 1) {
            
            cout << "\nIngrese los datos del empleado:" << endl;
            cout << "Cédula: ";
            getline(cin, cedula);
            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "Fecha de nacimiento (YYYY-MM-DD): ";
            getline(cin, fechaNacimiento);
            cout << "Categoría (Administrador, Operario, Peón): ";
            getline(cin, categoria);
            cout << "Salario: ";
            cin >> salario;
            cin.ignore();
            cout << "Dirección: ";
            getline(cin, direccion);
            cout << "Teléfono: ";
            getline(cin, telefono);
            cout << "Correo: ";
            getline(cin, correo);

            try {
                Empleado* emp = new Empleado(cedula, nombre, fechaNacimiento, categoria, salario, direccion, telefono, correo);
                empleados.push_back(emp);
                cout << "Empleado ingresado exitosamente." << endl;
            } catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
        } 
        else if (opcion == 2) {
            
            cout << "\nIngrese los datos del proyecto:" << endl;
            cout << "Código del proyecto: ";
            getline(cin, codProyecto);
            cout << "Nombre del proyecto: ";
            getline(cin, nombreProyecto);
            cout << "Fecha de inicio (YYYY-MM-DD): ";
            getline(cin, fechaInicio);
            cout << "Fecha de finalización (YYYY-MM-DD): ";
            getline(cin, fechaFin);

            try {
                Proyecto* proy = new Proyecto(codProyecto, nombreProyecto, fechaInicio, fechaFin);
                proyectos.push_back(proy);
                cout << "Proyecto ingresado exitosamente." << endl;
            } catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
        } 
        else if (opcion == 3) {
            
            string cedulaEmpleado, nombreProyectoAsignado;

            cout << "\nIngrese la cédula del empleado: ";
            getline(cin, cedulaEmpleado);
            cout << "Ingrese el nombre del proyecto: ";
            getline(cin, nombreProyectoAsignado);

            Empleado* emp = NULL;
            Proyecto* proy = NULL;

            
            for (size_t i = 0; i < empleados.size(); ++i) {
                if (empleados[i]->getCedula() == cedulaEmpleado) {
                    emp = empleados[i];
                    break;
                }
            }

            
            for (size_t i = 0; i < proyectos.size(); ++i) {
                if (proyectos[i]->getNombre() == nombreProyectoAsignado) {
                    proy = proyectos[i];
                    break;
                }
            }

            if (emp != NULL && proy != NULL) {
                Asignacion* asig = new Asignacion(emp, proy);
                asignaciones.push_back(asig);
                cout << "Empleado asignado al proyecto exitosamente." << endl;
            } else {
                cout << "Empleado o proyecto no encontrados." << endl;
            }
        } 
        else if (opcion == 4) {
            
            for (size_t i = 0; i < asignaciones.size(); ++i) {
                asignaciones[i]->mostrarAsignacion();
            }
        } 
        else if (opcion == 5) {
            break;
        } 
        else {
            cout << "Opción no válida." << endl;
        }
    }

    
    for (size_t i = 0; i < empleados.size(); ++i) delete empleados[i];
    for (size_t i = 0; i < proyectos.size(); ++i) delete proyectos[i];
    for (size_t i = 0; i < asignaciones.size(); ++i) delete asignaciones[i];

    return 0;
}

