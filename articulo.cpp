//Pablo Garcia Bravo

#include "articulo.hpp"

////////////CONSTRUCTORES/////////
//Constructor por defecto
Articulo::Articulo(Cadena r, Cadena t, Fecha f, double p, size_t st):
referencia_(r), titulo_(t), f_publi_(f), stock_(st), precio_(p) {}


//////////////OPERADOR DE FLUJO/////////////////
ostream& operator <<(ostream& os, const Articulo& art){
    os<<"["<< art.referencia() << "] \""<< art.titulo()<< "\", "<<art.f_publi().anno()<<". "<<
    setprecision(2)<<fixed << art.precio()<<" €"<<endl;
    return os;
}