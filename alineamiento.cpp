// Proyecto Unidad 3 - Alineamiento Global de Secuencias
// Integrantes: Ivonne Cancino - Gabriela Sepúlveda
// Descripción: Implementación del algoritmo de Needleman-Wunsch para el alineamiento global de secuencias.
// Compilación y ejecución: g++ alineamiento.cpp -o alineamiento && ./alineamiento -C1 cad1.txt -C2 cad2.txt -U funU.txt -V -1

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <filesystem>
#include <iomanip>
#include <set>

using namespace std;
namespace fs = std::filesystem;


static int GAP_SCORE = -1;
static int U[256][256];  
static const string OUTPUT_DIR = "Resultados_Alineamiento";
const int BLOCK_SIZE = 50;
const int CORNER = 15;

inline int idx(char c){ return (unsigned char)c; }

// Función para leer la secuencia desde un archivo (FASTA o texto plano)
string leer_secuencia(const string &ruta){
    ifstream f(ruta);
    if(!f.good()){ cerr<<"Error, no se puede abrir "<<ruta<<"\n"; exit(1); }

    string linea, seq;
    while(getline(f, linea)){
        if(!linea.empty() && linea[0]=='>') continue;
        for(char c: linea){
            if(!isspace((unsigned char)c)){
                seq.push_back( toupper((unsigned char)c) );
            }
        }
    }
    return seq;
}

// Función para leer la matriz de similitud U desde un archivo.
void leer_matriz_U(const string &ruta){
    ifstream f(ruta);
    if(!f.good()){ cerr<<"Error, no se puede abrir matriz U\n"; exit(1); }

    for(int i=0;i<256;i++)
        for(int j=0;j<256;j++)
            U[i][j]=0;

    string linea;
    getline(f, linea);

    vector<char> cols;
    string tok;
    stringstream ss(linea);

    while(ss >> tok){
        if(tok.size()==1){
            char c = toupper((unsigned char)tok[0]);
            cols.push_back(c);
        }
    }

    while(getline(f, linea)){
        if(linea.empty()) continue;
        stringstream s2(linea);
        string rowTok;
        s2 >> rowTok;
        char r = toupper((unsigned char)rowTok[0]);

        for(size_t c=0;c<cols.size();c++){
            int val;
            s2 >> val;
            U[idx(r)][idx(cols[c])] = val;
        }
    }
}

// Extraer el alfabeto usado en la matriz U, es decir, los caracteres con valores distintos de 0.
set<char> obtener_alfabeto_U(){
    set<char> letras;
    for(int i=0;i<256;i++){
        for(int j=0;j<256;j++){
            if(U[i][j] != 0){
                letras.insert((char)i);
                letras.insert((char)j);
            }
        }
    }
    return letras;
}

// Función para validar que la secuencia solo use letras presentes en el alfabeto de U.
void validar_secuencia(const string &seq, const string &nombre, const set<char> &alf){
    for(char c: seq){
        if(alf.count(c) == 0){
            cerr<<"Aviso: Letra '"<<c<<"' en secuencia "<<nombre
                <<" NO aparece en el alfabeto de U. Se interpretará como similitud 0.\n";
        }
    }
}

// Construir la tabla DP para el alineamiento global, usando la matriz U y el puntaje de gap.
vector<vector<int>> construir_dp(const string &S, const string &T){
    int n=S.size(), m=T.size();
    vector<vector<int>> f(n+1, vector<int>(m+1,0));

    for(int i=1;i<=n;i++) f[i][0]=f[i-1][0]+GAP_SCORE;
    for(int j=1;j<=m;j++) f[0][j]=f[0][j-1]+GAP_SCORE;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int arriba=f[i-1][j]+GAP_SCORE;
            int izq   =f[i][j-1]+GAP_SCORE;
            int diag  =f[i-1][j-1] + U[idx(S[i-1])][idx(T[j-1])];
            f[i][j]=max({arriba, izq, diag});
        }
    }
    return f;
}

// Taceback para reconstruir el alineamiento óptimo desde la tabla DP, devuelve las dos secuencias alineadas.
pair<string,string> traceback(const vector<vector<int>> &f, const string &S, const string &T){
    int i=S.size(), j=T.size();
    string aS="", aT="";

    while(i>0 || j>0){
        if(i>0 && j>0 &&
           f[i][j]==f[i-1][j-1]+U[idx(S[i-1])][idx(T[j-1])]){
            aS.push_back(S[i-1]);
            aT.push_back(T[j-1]);
            i--; j--;
        }
        else if(i>0 && f[i][j]==f[i-1][j]+GAP_SCORE){
            aS.push_back(S[i-1]);
            aT.push_back('-');
            i--;
        }
        else{
            aS.push_back('-');
            aT.push_back(T[j-1]);
            j--;
        }
    }

    reverse(aS.begin(), aS.end());
    reverse(aT.begin(), aT.end());
    return {aS,aT};
}

// Función para generar la línea de concordancia y calcular similitud, usada en la salida TXT y terminal.
string linea_concord(const string &aS,const string &aT){
    string l;
    l.reserve(aS.size());
    for(size_t i=0;i<aS.size();i++){
        if(aS[i]!='-' && aT[i]!='-' && aS[i]==aT[i]) l.push_back('|');
        else l.push_back('.');
    }
    return l;
}

// Calcular el porcentaje de similitud entre dos secuencias alineadas.
double similitud(const string &aS,const string &aT){
    int matches=0, comp=0;
    for(size_t i=0;i<aS.size();i++){
        if(aS[i]=='-'||aT[i]=='-') continue;
        comp++;
        if(aS[i]==aT[i]) matches++;
    }
    if(comp==0) return 0.0;
    return 100.0*static_cast<double>(matches)/static_cast<double>(comp);
}

// Asegurar que el directorio de salida exista, en este caso "Resultados_Alineamiento".
void asegurar_salida(){
    if(!fs::exists(OUTPUT_DIR)) fs::create_directories(OUTPUT_DIR);
}

// Función para escribir el alineamiento y detalles en un archivo TXT, incluyendo bloques y esquinas de la tabla DP.
void escribir_txt(const string &nombre, const vector<vector<int>> &f,
                  const string &aS,const string &aT){

    asegurar_salida();
    string ruta=OUTPUT_DIR+"/"+nombre;
    ofstream out(ruta);
    if(!out.good()){ cerr<<"Error,no escribe txt\n"; return; }

    size_t L=aS.size();
    string conc=linea_concord(aS,aT);
    double sim=similitud(aS,aT);

    out<<left;
    out<<"=== Alineamiento global (Needleman-Wunsch) ===\n\n";
    out<<"Largo alineamiento: "<<L<<"\n";

    int comp=0;
    for(size_t i=0;i<L;i++) if(aS[i]!='-' && aT[i]!='-') comp++;
    out<<"Posiciones comparadas: "<<comp<<"\n";

    out<<fixed<<setprecision(4);
    out<<"Similitud: "<<sim<<" %\n\n";

    for(size_t start=0; start<L; start+=BLOCK_SIZE){
        size_t end=min(start+BLOCK_SIZE,L);

        // Uso de secuencia S
        out<<setw(6)<<start+1<<"  "<<aS.substr(start,end-start)<<"\n";
        out<<setw(6)<<""<<"  "<<conc.substr(start,end-start)<<"\n";
        // Uso de secuencia T
        out<<setw(6)<<start+1<<"  "<<aT.substr(start,end-start)<<"\n\n";
    }

    int score=f[f.size()-1][f[0].size()-1];
    out<<"Puntaje final: "<<score<<"\n\n";

    out<<"=== Matriz DP esquina superior ===\n";
    for(int i=0;i<min(CORNER,(int)f.size());i++){
        for(int j=0;j<min(CORNER,(int)f[0].size());j++)
            out<<f[i][j]<<"\t";
        out<<"\n";
    }

    out<<"\n=== Matriz DP esquina inferior ===\n";
    int n=f.size()-1, m=f[0].size()-1;
    int si=max(0,n-CORNER+1), sj=max(0,m-CORNER+1);
    for(int i=si;i<=n;i++){
        for(int j=sj;j<=m;j++) out<<f[i][j]<<"\t";
        out<<"\n";
    }

    cout<<"Archivo creado con éxito: "<<ruta<<"\n";
}

// Función para escribir el alineamiento en formato DOT y generar una imagen JPG usando Graphviz.
void escribir_dot(const string &nombre_base,
                  const string &aS,const string &aT){

    asegurar_salida();
    string dot=OUTPUT_DIR+"/"+nombre_base+".dot";
    string img=OUTPUT_DIR+"/"+nombre_base+".jpg";
    ofstream g(dot);
    if(!g.good()){ cerr<<"[ERROR] No dot\n"; return; }

    g<<"digraph A { rankdir=TB; node [shape=plaintext];\n";
    g<<"labelloc=\"t\";\n";
    g<<"label=<<FONT POINT-SIZE=\"24\"><B>Alineamiento Global – Needleman–Wunsch</B></FONT>>;\n";

    // Leyenda de colores, donde consideramos: match verde, mismatch rojo y gaps en gris.
    g<<"legend [label=<"
      "<TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"white\">"
      "<TR><TD COLSPAN=\"2\"><B>Leyenda</B></TD></TR>"
      "<TR><TD BGCOLOR=\"lightgreen\"> </TD><TD>Match</TD></TR>"
      "<TR><TD BGCOLOR=\"lightcoral\"> </TD><TD>Mismatch</TD></TR>"
      "<TR><TD BGCOLOR=\"lightgray\"> </TD><TD>Gap</TD></TR>"
      "</TABLE>>];\n";

    g<<"{ rank=same; legend }\n\n";

    g<<"alignment [label=<\n";
    g<<"<TABLE BORDER=\"0\" CELLBORDER=\"0\" CELLSPACING=\"25\">\n";

    size_t L=aS.size();
    int block=1;

    for(size_t start=0; start<L; start+=BLOCK_SIZE){
        size_t end=min(start+BLOCK_SIZE,L);

        g<<"<TR><TD><FONT POINT-SIZE=\"18\"><B>&lt; BLOQUE "
         <<block++<<" ("<<start+1<<"–"<<end<<") &gt;</B></FONT></TD></TR>\n";

        g<<"<TR><TD><TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n";

        g<<"<TR>";
        for(size_t i=start;i<end;i++){
            string col="lightgray";
            if(aS[i]!='-' && aT[i]!='-')
                col=(aS[i]==aT[i]?"lightgreen":"lightcoral");
            g<<"<TD BGCOLOR=\""<<col<<"\">"<<(aS[i]=='-'?"-":string(1,aS[i]))<<"</TD>";
        }
        g<<"</TR>\n";

        g<<"<TR>";
        for(size_t i=start;i<end;i++){
            string col="lightgray";
            if(aS[i]!='-' && aT[i]!='-')
                col=(aS[i]==aT[i]?"lightgreen":"lightcoral");
            g<<"<TD BGCOLOR=\""<<col<<"\">"<<(aT[i]=='-'?"-":string(1,aT[i]))<<"</TD>";
        }
        g<<"</TR>\n";

        g<<"</TABLE></TD></TR>\n";
    }

    g<<"</TABLE>>];\n";
    g<<"}\n";
    g.close();

    // Se genera la imagen JPG usando Graphviz
    string cmd="dot -Tjpg "+dot+" -o "+img+" 2>/dev/null";
    int r=system(cmd.c_str());
    if(r==0) cout<<"Imagen generada con éxito: "<<img<<"\n";
    else cout<<"[WARN] Dot no disponible\n";
}

// Función para imprimir el alineamiento y detalles en la terminal.
void imprimir_terminal(const string &aS,const string &aT){
    size_t L=aS.size();
    string conc=linea_concord(aS,aT);
    double sim=similitud(aS,aT);

    cout<<"\n--- Alineamiento óptimo ---\n";
    cout<<"Largo: "<<L<<"\n";

    int comp=0;
    for(size_t i=0;i<L;i++) if(aS[i]!='-'&&aT[i]!='-') comp++;
    cout<<"Comparadas: "<<comp<<"\n";

    cout<<fixed<<setprecision(4);
    cout<<"Similitud: "<<sim<<" %\n\n";

    for(size_t start=0;start<L;start+=BLOCK_SIZE){
        size_t end=min(start+BLOCK_SIZE,L);
        cout<<aS.substr(start,end-start)<<"\n";
        cout<<conc.substr(start,end-start)<<"\n";
        cout<<aT.substr(start,end-start)<<"\n\n";
    }
}

// Función para mostrar el uso correcto del programa, en caso de argumentos incorrectos.
void uso(const string &p){
    cerr<<"Uso: "<<p<<" -C1 seq1 -C2 seq2 -U matriz -V gap\n";
}

// Función principal, maneja argumentos, lee archivos, ejecuta el alineamiento y genera salidas.
int main(int argc,char*argv[]){
    if(argc!=9){ uso(argv[0]); return 1; }

    string f1,f2,fU;
    for(int i=1;i<argc;i++){
        if(!strcmp(argv[i],"-C1")) {
            if(i+1<argc) f1=argv[++i];
            else { uso(argv[0]); return 1; }
        }
        else if(!strcmp(argv[i],"-C2")) {
            if(i+1<argc) f2=argv[++i];
            else { uso(argv[0]); return 1; }
        }
        else if(!strcmp(argv[i],"-U")) {
            if(i+1<argc) fU=argv[++i];
            else { uso(argv[0]); return 1; }
        }
        else if(!strcmp(argv[i],"-V")) {
            if(i+1<argc) GAP_SCORE=stoi(argv[++i]);
            else { uso(argv[0]); return 1; }
        }
        else { uso(argv[0]); return 1; }
    }

    // Leer matriz U y secuencias desde archivos especificados.
    leer_matriz_U(fU);
    string S=leer_secuencia(f1);
    string T=leer_secuencia(f2);

    if(S.empty()||T.empty()){ cerr<<"Error, secuencia vacía\n"; return 1; }

    cout<<"- Secuencia 1 ("<<S.size()<<")\n";
    cout<<"- Secuencia 2 ("<<T.size()<<")\n";
    cout<<"- GAP = "<<GAP_SCORE<<"\n";

    // Se obtiene el alfabeto de la matriz U, para validación de secuencias.
    auto A = obtener_alfabeto_U();
    if(A.empty()){
        cerr<<"Error, la matriz U parece no contener valores distintos de 0. "
             <<"Verifica el formato de la matriz U.\n";
        return 1;
    }

    cout<<"- Alfabeto detectado en U: { ";
    for(char c : A) cout<<c<<" ";
    cout<<"}\n";

    // Se validan las secuencias contra el alfabeto de U, mostrando advertencias si hay caracteres no presentes.
    validar_secuencia(S,"1",A);
    validar_secuencia(T,"2",A);

    // Se construye la tabla DP y se realiza el traceback para obtener el alineamiento óptimo.
    auto dp = construir_dp(S,T);
    auto aln = traceback(dp,S,T);
    string aS=aln.first, aT=aln.second;

    imprimir_terminal(aS,aT);
    escribir_txt("alineamiento.txt",dp,aS,aT);
    escribir_dot("alineamiento",aS,aT);

    cout<<"\nPrograma finalizado con éxito, ver carpeta '"<<OUTPUT_DIR<<"'.\n";
    return 0;
}
