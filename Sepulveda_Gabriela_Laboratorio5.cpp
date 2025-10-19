// Programa: Laboratorio 5 - Árbol AVL para términos GO (sin clases)
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Implementa un árbol AVL que almacena términos Gene Ontology (GO). Cada nodo guarda: codigoGO (string), funcion (string), score (float) y FE (int).
// Operaciones: inserción balanceada, eliminación balanceada, búsqueda, recorridos, carga desde CSV (hasta 12 términos), y generación de grafo DOT para Graphviz.

#include <iostream>
#include <fstream>
#include <cstdlib>        
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <iomanip>

// Estructura del nodo: Puntero izquierdo, derecho, codigoGO, funcion, score y FE.
using namespace std;
typedef struct NODO {
    NODO* izq;
    NODO* der;
    string codigoGO;
    string funcion;
    float score;
    int FE;
} NODO;

// Prototipo de funciones, donde se implementan todas las funcionalidades del árbol AVL.
void InsercionBalanceado(NODO** nodocabeza, bool* BO, const string& codigo, const string& funcion, float score);
void BusquedaImprimir(NODO* nodo, const string& codigo);
bool existeCodigo(NODO* raiz, const string& codigo);
void Restructura1(NODO** nodocabeza, bool* BO);
void Restructura2(NODO** nodocabeza, bool* BO);
void Borra(NODO** aux1, NODO** otro1, bool* BO);
void EliminacionBalanceado(NODO** nodocabeza, bool* BO, const string& codigo);
int Menu();
void GenerarGrafo(NODO* p);
void PreOrden(NODO* a, ofstream& fp);
void asignarIds(NODO* nodo, unordered_map<NODO*, string>& mapaIds, int &contador);
void liberarArbol(NODO* raiz);
void cargarCSV(NODO*& raiz, const string& nombreArchivo, bool limitar12 = true);
void imprimirInorden(NODO* raiz);
void imprimirPreorden(NODO* raiz);
void imprimirPosorden(NODO* raiz);
string formatoScore(float s);

// Main, punto de entrada del programa donde se muestra el menú y se gestiona la interacción.
int main(int argc, char** argv) {
    NODO* raiz = nullptr;
    int opcion;
    bool inicio;

    // Cargar archivo pasado por línea de comandos (si existe)
    if (argc >= 2) {
        string archivo = argv[1];
        cout << "Cargando archivo: " << archivo << "\n";
        cargarCSV(raiz, archivo, true); // limitar a 12 por enunciado
        cout << "Carga inicial completada.\n";
    }

    // Bucle principal del menú interactivo
    do {
        opcion = Menu();
        switch (opcion) {
            case 1: {
                // Insertar término GO manual 
                string codigo, funcion;
                float score;
                cout << "Ingrese codigo GO (ej. GO:0090398): ";
                cin >> ws;
                getline(cin, codigo);
                if (codigo.empty()) { cout << "Codigo vacio, intente de nuevo.\n"; break; }
                cout << "Ingrese nombre de la funcion (puede contener espacios): ";
                getline(cin, funcion);
                cout << "Ingrese score: ";
                if (!(cin >> score)) {
                    cout << "Score invalido, intente de nuevo.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                inicio = false;
                InsercionBalanceado(&raiz, &inicio, codigo, funcion, score);
                cout << "Insercion finalizada.\n";
                if (inicio) {
                    cout << "Nodo insertado:\n";
                    BusquedaImprimir(raiz, codigo);
                } else {
                    cout << "Error al insertar el nodo, intente de nuevo.\n";
                }
                break;
            }
            case 2: {
                // Buscar por codigoGO, y en el caso de encontrarlo, imprimir todos sus datos.
                string codigo;
                cout << "Ingrese codigo GO a buscar: ";
                cin >> ws;
                getline(cin, codigo);
                BusquedaImprimir(raiz, codigo);
                break;
            }
            case 3: {
                // Eliminar por codigoGO, incluyendo reequilibrio del árbol.
                string codigo;
                cout << "Ingrese codigo GO a eliminar: ";
                cin >> ws;
                getline(cin, codigo);
                inicio = false;
                EliminacionBalanceado(&raiz, &inicio, codigo);
                break;
            }
            case 4:
                // Generar grafo DOT y llamar a dot para crear PNG
                if (!raiz) {
                    cout << "Arbol vacio, inserte elementos antes de generar el grafo.\n";
                } else {
                    GenerarGrafo(raiz);
                    cout << "Grafo generado en grafo.txt -> grafo.png.\n";
                }
                break;
            case 5: {
                // Cargar desde archivo CSV.
                string archivo;
                cout << "Ingrese ruta a archivo CSV (Funciones_GO_minimal.csv): ";
                cin >> ws;
                getline(cin, archivo);
                cargarCSV(raiz, archivo, true);
                break;
            }
            case 6:
                // Mostrar recorridos del árbol: Inorden, Preorden, Posorden.
                if (!raiz) {
                    cout << "Arbol vacio.\n";
                } else {
                    cout << "\n- INORDEN -\n";
                    imprimirInorden(raiz);
                    cout << "\n- PREORDEN -\n";
                    imprimirPreorden(raiz);
                    cout << "\n- POSORDEN -\n";
                    imprimirPosorden(raiz);
                }
                break;
            case 7:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida, intente de nuevo.\n";
        }
    } while (opcion != 7);

    // Liberar memoria antes de salir del programa.
    liberarArbol(raiz);
    return 0;
}

// Menú intercativo: muestra diversas opciones y lee la selección del usuario.
int Menu() {
    int Op;
    cout << "\n--------------------\n";
    cout << "1) Insertar termino GO\n";
    cout << "2) Buscar termino GO\n";
    cout << "3) Eliminar termino GO\n";
    cout << "4) Generar grafo (Graphviz)\n";
    cout << "5) Cargar desde CSV\n";
    cout << "6) Mostrar recorridos (Inorden-Preorden-Posorden)\n";
    cout << "7) Salir\n";
    cout << "Opcion: ";

    if (!(cin >> Op)) {
        // Si la entrada no es un entero, limpiar el error y devolver 0.
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }
    return Op;
}

// Implementación de las funciones del árbol AVL
// InsercionBalanceado: Inserta un nodo manteniendo el balance AVL
void InsercionBalanceado(NODO** nodocabeza, bool* BO, const string& codigo, const string& funcion, float score) {
    NODO* nodo = *nodocabeza;
    NODO* nodo1;
    NODO* nodo2;

    if (nodo != nullptr) {
        if (codigo < nodo->codigoGO) {
            // Insertar en subárbol izquierdo
            InsercionBalanceado(&(nodo->izq), BO, codigo, funcion, score);
            if (*BO) {
                switch (nodo->FE) {
                    case 1:
                        nodo->FE = 0;
                        *BO = false;
                        break;
                    case 0:
                        nodo->FE = -1;
                        break;
                    case -1:
                        // Desbalance por izquierda: aplicar rotaciones II o ID 
                        nodo1 = nodo->izq;
                        if (nodo1->FE <= 0) { // Rotación II
                            nodo->izq = nodo1->der;
                            nodo1->der = nodo;
                            nodo->FE = 0;
                            nodo = nodo1;
                        } else { // Rotación ID
                            nodo2 = nodo1->der;
                            nodo->izq = nodo2->der;
                            nodo2->der = nodo;
                            nodo1->der = nodo2->izq;
                            nodo2->izq = nodo1;

                            if (nodo2->FE == -1)
                                nodo->FE = 1;
                            else
                                nodo->FE = 0;

                            if (nodo2->FE == 1)
                                nodo1->FE = -1;
                            else
                                nodo1->FE = 0;
                            nodo = nodo2;
                        }
                        nodo->FE = 0;
                        *BO = false;
                        break;
                }
            }
        } else if (codigo > nodo->codigoGO) {
            // Insertar en subárbol derecho
            InsercionBalanceado(&(nodo->der), BO, codigo, funcion, score);
            if (*BO) {
                switch (nodo->FE) {
                    case -1:
                        nodo->FE = 0;
                        *BO = false;
                        break;
                    case 0:
                        nodo->FE = 1;
                        break;
                    case 1:
                        // Desbalance por derecha: rotaciones DD o DI
                        nodo1 = nodo->der;
                        if (nodo1->FE >= 0) { // Rotación DD
                            nodo->der = nodo1->izq;
                            nodo1->izq = nodo;
                            nodo->FE = 0;
                            nodo = nodo1;
                        } else { // Rotación DI
                            nodo2 = nodo1->izq;
                            nodo->der = nodo2->izq;
                            nodo2->izq = nodo;
                            nodo1->izq = nodo2->der;
                            nodo2->der = nodo1;

                            if (nodo2->FE == 1)
                                nodo->FE = -1;
                            else
                                nodo->FE = 0;

                            if (nodo2->FE == -1)
                                nodo1->FE = 1;
                            else
                                nodo1->FE = 0;

                            nodo = nodo2;
                        }
                        nodo->FE = 0;
                        *BO = false;
                        break;
                }
            }
        } else {
            // Código ya existe, no insertar duplicados.
            *BO = false;
        }
    } else {
        // Crear nuevo nodo hoja
        nodo = new NODO();
        nodo->izq = nullptr;
        nodo->der = nullptr;
        nodo->codigoGO = codigo;
        nodo->funcion = funcion;
        nodo->score = score;
        nodo->FE = 0;
        *BO = true; // altura del subárbol ha aumentado
    }

    *nodocabeza = nodo;
}


// BusquedaImprimir: Busca un nodo por codigoGO e imprime sus datos si lo encuentra.
void BusquedaImprimir(NODO* nodo, const string& codigo) {
    if (nodo != nullptr) {
        if (codigo < nodo->codigoGO)
            BusquedaImprimir(nodo->izq, codigo);
        else if (codigo > nodo->codigoGO)
            BusquedaImprimir(nodo->der, codigo);
        else {
            cout << "Término encontrado con éxito:\n";
            cout << "- Código: " << nodo->codigoGO << "\n";
            cout << "- Función: " << nodo->funcion << "\n";
            cout << "- Score: " << formatoScore(nodo->score) << "\n";
            cout << "- FE: " << nodo->FE << "\n";
        }
    } else {
        cout << "El término NO se encuentra en el árbol\n";
    }
}


// existeCodigo: Comprueba si un codigoGO ya existe en el árbol (iterativo), devuelve true si existe, false si no.
bool existeCodigo(NODO* raiz, const string& codigo) {
    NODO* cur = raiz;
    while (cur) {
        if (codigo < cur->codigoGO) cur = cur->izq;
        else if (codigo > cur->codigoGO) cur = cur->der;
        else return true;
    }
    return false;
}


//Restructura1 y Restructura2: Funciones auxiliares para reequilibrar el árbol luego de una eliminación, aplicando las rotaciones necesarias.
void Restructura1(NODO** nodocabeza, bool* BO) {
    NODO *nodo, *nodo1, *nodo2;
    nodo = *nodocabeza;
    if (*BO) {
        switch (nodo->FE) {
            case -1:
                nodo->FE = 0;
                break;
            case 0:
                nodo->FE = 1;
                *BO = false;
                break;
            case 1:
                nodo1 = nodo->der;
                if (nodo1->FE >= 0) { // Rotación Derecha-Derecha (DD)
                    nodo->der = nodo1->izq;
                    nodo1->izq = nodo;
                    switch (nodo1->FE) {
                        case 0:
                            nodo->FE = 1;
                            nodo1->FE = -1;
                            *BO = false;
                            break;
                        case 1:
                            nodo->FE = 0;
                            nodo1->FE = 0;
                            *BO = false;
                            break;
                    }
                    nodo = nodo1;
                } else { // Rotación Derecha-Izquierda (DI)
                    nodo2 = nodo1->izq;
                    nodo->der = nodo2->izq;
                    nodo2->izq = nodo;
                    nodo1->izq = nodo2->der;
                    nodo2->der = nodo1;
                    if (nodo2->FE == 1)
                        nodo->FE = -1;
                    else
                        nodo->FE = 0;
                    if (nodo2->FE == -1)
                        nodo1->FE = 1;
                    else
                        nodo1->FE = 0;
                    nodo = nodo2;
                    nodo2->FE = 0;
                }
                break;
        }
    }
    *nodocabeza = nodo;
}

void Restructura2(NODO** nodocabeza, bool* BO) {
    NODO *nodo, *nodo1, *nodo2;
    nodo = *nodocabeza;
    if (*BO) {
        switch (nodo->FE) {
            case 1:
                nodo->FE = 0;
                break;
            case 0:
                nodo->FE = -1;
                *BO = false;
                break;
            case -1:
                nodo1 = nodo->izq;
                if (nodo1->FE <= 0) { // Rotación Izquierda-Izquierda (II)
                    nodo->izq = nodo1->der;
                    nodo1->der = nodo;
                    switch (nodo1->FE) {
                        case 0:
                            nodo->FE = -1;
                            nodo1->FE = 1;
                            *BO = false;
                            break;
                        case -1:
                            nodo->FE = 0;
                            nodo1->FE = 0;
                            *BO = false;
                            break;
                    }
                    nodo = nodo1;
                } else { // Rotación Izquierda-Derecha (ID)
                    nodo2 = nodo1->der;
                    nodo->izq = nodo2->der;
                    nodo2->der = nodo;
                    nodo1->der = nodo2->izq;
                    nodo2->izq = nodo1;
                    if (nodo2->FE == -1)
                        nodo->FE = 1;
                    else
                        nodo->FE = 0;
                    if (nodo2->FE == 1)
                        nodo1->FE = -1;
                    else
                        nodo1->FE = 0;
                    nodo = nodo2;
                    nodo2->FE = 0;
                }
                break;
        }
    }
    *nodocabeza = nodo;
}

// Borra: Función auxiliar utilizada por la eliminación para encontrar el predecesor o sucesor, copiar sus campos y ajustar punteros.
void Borra(NODO** aux1, NODO** otro1, bool* BO) {
    NODO *aux, *otro;
    aux = *aux1;
    otro = *otro1;
    if (aux->der != nullptr) {
        Borra(&(aux->der), &otro, BO);
        Restructura2(&aux, BO);
    } else {
        // Copiar datos del predecesor/sucesor a "otro" y ajustar punteros.
        otro->codigoGO = aux->codigoGO;
        otro->funcion = aux->funcion;
        otro->score = aux->score;
        aux = aux->izq;
        *BO = true;
    }
    *aux1 = aux;
    *otro1 = otro;
}

//EliminacionBalanceado: Elimina un nodo por codigoGO y mantiene el balance AVL. 
void EliminacionBalanceado(NODO** nodocabeza, bool* BO, const string& codigo) {
    NODO *nodo, *otro;
    nodo = *nodocabeza;
    if (nodo != nullptr) {
        if (codigo < nodo->codigoGO) {
            EliminacionBalanceado(&(nodo->izq), BO, codigo);
            Restructura1(&nodo, BO);
        } else if (codigo > nodo->codigoGO) {
            EliminacionBalanceado(&(nodo->der), BO, codigo);
            Restructura2(&nodo, BO);
        } else {
            // Encontrado: tres casos
            otro = nodo;
            if (otro->der == nullptr) {
                nodo = otro->izq;
                *BO = true;
                delete otro;
            } else if (otro->izq == nullptr) {
                nodo = otro->der;
                *BO = true;
                delete otro;
            } else {
                // Dos hijos: en este caso, usar el predecesor (mayor en subárbol izquierdo).
                Borra(&(otro->izq), &otro, BO);
                Restructura1(&nodo, BO);
                delete otro;
            }
        }
    } else {
        cout << "El nodo no se encuentra en el arbol\n";
    }
    *nodocabeza = nodo;
}

// asignarIds: Asigna IDs únicos a cada nodo para referenciarlos en el archivo DOT.
void asignarIds(NODO* nodo, unordered_map<NODO*, string>& mapaIds, int &contador) {
    if (!nodo) return;
    mapaIds[nodo] = "n" + to_string(contador++);
    asignarIds(nodo->izq, mapaIds, contador);
    asignarIds(nodo->der, mapaIds, contador);
}

//GenerarGrafo: Genera el archivo DOT con la estructura del árbol y llama a dot para crear un PNG.
void GenerarGrafo(NODO* ArbolInt) {
    if (!ArbolInt) {
        cout << "Arbol vacio: no se ha podido generar grafo.\n";
        return;
    }
    ofstream fp("grafo.txt");
    fp << "digraph G {\n";
    fp << "  node [style=filled fillcolor=\"#ffd6e7\" shape=box];\n";
    fp << "  rankdir=TB;\n";

    unordered_map<NODO*, string> mapaIds;
    int contador = 1;
    asignarIds(ArbolInt, mapaIds, contador);

    // Se definen nodos con etiquetas personalizadas
    for (auto &p : mapaIds) {
        NODO* nd = p.first;
        string id = p.second;
        ostringstream ss;
        ss << nd->codigoGO << "\\n" << nd->funcion << "\\n" << formatoScore(nd->score) << "\\nFE=" << nd->FE;
        string label = ss.str();
        fp << "  " << id << " [label=\"" << label << "\"];\n";
    }

    // Se definen las aristas entre nodos, incluyendo nodos nulos.
    int contadorNulos = 1;
    for (auto &p : mapaIds) {
        NODO* nd = p.first;
        string id = p.second;
        if (nd->izq) {
            fp << "  " << id << " -> " << mapaIds[nd->izq] << ";\n";
        } else {
            string idNulo = "null" + to_string(contadorNulos++);
            fp << "  " << idNulo << " [shape=point];\n";
            fp << "  " << id << " -> " << idNulo << ";\n";
        }
        if (nd->der) {
            fp << "  " << id << " -> " << mapaIds[nd->der] << ";\n";
        } else {
            string idNulo = "null" + to_string(contadorNulos++);
            fp << "  " << idNulo << " [shape=point];\n";
            fp << "  " << id << " -> " << idNulo << ";\n";
        }
    }

    fp << "}\n";
    fp.close();

    // Ejecutar dot para generar PNG.
    int rc = system("dot -Tpng -ografo.png grafo.txt");
    if (rc != 0) {
        cout << "Aviso: Comando dot devolvio codigo " << rc << ". Verifica que Graphviz este instalado correctamente.\n";
    } else {
        cout << "grafo.png generado correctamente.\n";
    }
}

// liberarArbol: Libera la memoria de todo el árbol de forma recursiva.
void liberarArbol(NODO* raiz) {
    if (!raiz) return;
    liberarArbol(raiz->izq);
    liberarArbol(raiz->der);
    delete raiz;
}

//formatoScore: Utilidad para formatear el score a 2 decimales como string.
string formatoScore(float s) {
    ostringstream ss;
    ss << fixed << setprecision(2) << s;
    return ss.str();
}

//cargarCSV: Carga términos GO desde un archivo CSV, con validaciones y límites según el enunciado.
void cargarCSV(NODO*& raiz, const string& nombreArchivo, bool limitar12) {
    ifstream ifs(nombreArchivo);
    if (!ifs.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << "\n";
        return;
    }
    string linea;
    bool primero = true;
    int cont = 0;

    int cont_insertados = 0;
    int cont_duplicado_codigo = 0;
    int cont_duplicado_score = 0;
    int cont_invalidas = 0;
    unordered_set<string> scores_vistos;

    while (getline(ifs, linea)) {
        if (linea.empty()) continue;
        // Saltar cabecera si existe (detectar "GO" o "Function")
        if (primero) {
            primero = false;
            string tmp = linea;
            for (auto &c : tmp) c = tolower(c);
            if (tmp.find("go") != string::npos && (tmp.find("function") != string::npos || tmp.find("score") != string::npos)) {
                continue;
            }
        }

        // Detecta separadores del archivo (coma o tabulación).
        char sep = ',';
        if (linea.find('\t') != string::npos) sep = '\t';

        string codigo, funcion, scoreStr;
        stringstream ss(linea);
        if (sep == ',') {
            if (!getline(ss, codigo, ',')) { cont_invalidas++; continue; }
            if (!getline(ss, funcion, ',')) { cont_invalidas++; continue; }
            if (!getline(ss, scoreStr, ',')) { cont_invalidas++; continue; }
        } else {
            if (!getline(ss, codigo, '\t')) { cont_invalidas++; continue; }
            if (!getline(ss, funcion, '\t')) { cont_invalidas++; continue; }
            if (!getline(ss, scoreStr, '\t')) { cont_invalidas++; continue; }
        }

        auto trim = [&](string &s) {
            while (!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin());
            while (!s.empty() && isspace((unsigned char)s.back())) s.pop_back();
        };
        trim(codigo); trim(funcion); trim(scoreStr);

        if (codigo.empty() || funcion.empty() || scoreStr.empty()) {
            cont_invalidas++;
            continue;
        }

        float score = 0.0f;
        try {
            score = stof(scoreStr);
        } catch (...) {
            cont_invalidas++;
            continue;
        }

        string scoreKey;
        {
            ostringstream oss; oss << fixed << setprecision(2) << score;
            scoreKey = oss.str();
        }

        // Evitar duplicado por score
        if (scores_vistos.find(scoreKey) != scores_vistos.end()) {
            cont_duplicado_score++;
            continue;
        }

        // Evitar duplicado por codigo
        if (existeCodigo(raiz, codigo)) {
            cont_duplicado_codigo++;
            continue;
        }

        // Insertar el nodo si es válido y no duplicado
        bool inicio_local = false;
        InsercionBalanceado(&raiz, &inicio_local, codigo, funcion, score);
        if (inicio_local) {
            cont_insertados++;
            scores_vistos.insert(scoreKey);
        } else {
            cont_duplicado_codigo++;
        }

        cont++;
        if (limitar12 && cont_insertados >= 12) break; // max 12 terminos
    }
    ifs.close();
    cout << "Carga finalizada. Insertados: " << cont_insertados
         << ", duplicados (codigo): " << cont_duplicado_codigo
         << ", duplicados (score): " << cont_duplicado_score
         << ", invalidas: " << cont_invalidas << "\n";
}

// Recorridos del árbol: Inorden, Preorden, Posorden. Se imprimen todos los nodos con sus campos para validación.
void imprimirInorden(NODO* raiz) {
    if (!raiz) return;
    imprimirInorden(raiz->izq);
    cout << raiz->codigoGO << " | " << raiz->funcion << " | " << formatoScore(raiz->score) << " | FE=" << raiz->FE << "\n";
    imprimirInorden(raiz->der);
}
void imprimirPreorden(NODO* raiz) {
    if (!raiz) return;
    cout << raiz->codigoGO << " | " << raiz->funcion << " | " << formatoScore(raiz->score) << " | FE=" << raiz->FE << "\n";
    imprimirPreorden(raiz->izq);
    imprimirPreorden(raiz->der);
}
void imprimirPosorden(NODO* raiz) {
    if (!raiz) return;
    imprimirPosorden(raiz->izq);
    imprimirPosorden(raiz->der);
    cout << raiz->codigoGO << " | " << raiz->funcion << " | " << formatoScore(raiz->score) << " | FE=" << raiz->FE << "\n";
}

// PreOrden: Recorrido preorden que genera aristas simples para el grafo DOT.
void PreOrden(NODO* a, ofstream& fp) {
    if (a != nullptr) {
        if (a->izq != nullptr)
            fp << a->codigoGO << " -> " << a->izq->codigoGO << ";\n";
        else
            fp << a->codigoGO << " -> " << "\"" << a->codigoGO << "i" << "\"" << " [shape=point];\n";
        if (a->der != nullptr)
            fp << a->codigoGO << " -> " << a->der->codigoGO << ";\n";
        else
            fp << a->codigoGO << " -> " << "\"" << a->codigoGO << "d" << "\"" << " [shape=point];\n";

        PreOrden(a->izq, fp);
        PreOrden(a->der, fp);
    }
}