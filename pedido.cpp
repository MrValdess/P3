//Pablo Garcia Bravo

#include "pedido.hpp"

/////////////CLASE PEDIDO////////////////
//Constructor
Pedido::Pedido(Usuario_Pedido& userped, Pedido_Articulo& pedart, Usuario& user, Tarjeta& tar, const Fecha& fech){}


//Operador de flujo
std::ostream& operator <<(std::ostream& os, Pedido ped){
    os << "Num. pedido: " << ped.numero() << endl;
    os << "Fecha:       " << ped.fecha() << endl;
    os << "Pagado con:  " << ped.tarjeta()->tipo() << "n.º: " << ped.tarjeta()->numero() << endl;
    os << "Importe:     " << ped.total() << " €" << endl;
    return os;
}