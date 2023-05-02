//Pablo Garcia Bravo

#include "pedido_articulo.hpp"

///////////////CLASE LINEAPEDIDO/////////////////////
//Operador de insercion en flujo
std::ostream& operator <<(std::ostream& os, const LineaPedido& lp){
    std::locale::global(std::locale(""));
    os << std::fixed << std::setprecision(2) << lp.precio_venta() << " €    " << lp.cantidad();
    return os;
}


///////////////CLASE PEDIDO_ARTICULO/////////////////