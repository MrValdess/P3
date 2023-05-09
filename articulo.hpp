//Pablo Garcia Bravo

#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_

#include <iostream>
#include <iomanip>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

using namespace std;

class Articulo{
public:
    //Constructor
    Articulo(Cadena r,Cadena t, Fecha f, double p, size_t st = 0);
    
    //Métodos observadores
    Cadena referencia() const noexcept{ return referencia_;}
    Cadena titulo() const noexcept {return titulo_;}
    Fecha f_publi() const noexcept {return f_publi_;}
    double precio() const noexcept {return precio_;};
    double& precio(){return precio_;}
    size_t stock() const noexcept {return stock_;}
    size_t& stock (){return stock_;}

    //Clase amiga de Pedido
    friend class Pedido;

    //Destructor por defecto
    ~Articulo() = default;

private:
    //Variables de la clase
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha f_publi_;
    size_t stock_;
    double precio_;
};

//Operador de insercion de flujo
ostream& operator <<(ostream&, const Articulo&);

#endif // _ARTICULO_HPP_