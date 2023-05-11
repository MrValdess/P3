//Pablo Garcia Bravo

#include "pedido-articulo.hpp"

///////////////CLASE LINEAPEDIDO/////////////////////
//Operador de insercion en flujo
std::ostream& operator <<(std::ostream& os, const LineaPedido& lp){
    std::locale::global(std::locale(""));
    os << std::fixed << std::setprecision(2) << lp.precio_venta() << " €\t" << lp.cantidad();
    return os;
}


///////////////CLASE PEDIDO_ARTICULO/////////////////
//Metodos pedir
void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double precio, unsigned cantidad){
    //Con el make_pair() podemos hacer una tupla para almacenar los datos en el mapa
    pa[&ped].insert(std::make_pair(&art, LineaPedido(precio, cantidad)));  
    ap[&art].insert(std::make_pair(&ped, LineaPedido(precio, cantidad)));
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& ped, double precio, unsigned cantidad){
    pedir(ped, art, precio, cantidad);
}

//Resto de metodos
Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(const Pedido& ped) const{
    //Creamos una variable i para que encuentre el pedido
    auto i = pa.find((Pedido*)&ped);
    if(i != pa.end()){  //Si lo encuentra devuelve el elemento asociado en el mapa
        return i->second;
    }
    else{   //Si no lo encuentra crea una instancia nueva de ItemsPedido vacia que la devolvemos
        return ItemsPedido{};
    }
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(const Articulo& art) const{
    //Creamos una variable i para que encuentre el articulo
    auto i = ap.find((Articulo*)&art);
    if(i != ap.end()){  //Si lo encuentra devuelve el elemmento asociado en el mapa
        return i->second;
    }
    else{   //Si no lo encuentra crea una instancia nueva de Pedidos vacia que la devolvemos
        return Pedidos{};
    }
}

//Metodos mostrar
//Detalles de los pedidos
void Pedido_Articulo::mostrarDetallePedidos(std::ostream& os) const noexcept{
    int cont = 1;
    double precio = 0;
    for(auto i:pa){
        os << "Pedido num. " << cont << std::endl; 
        cont++;
        os << "Cliente: " << i.first->tarjeta()->titular()->nombre() << "\t" << "Fecha: " << i.first->fecha() << std::endl;
        os << detalle(*i.first);
        precio += i.first->total();
    }
    os << "TOTAL VENTAS \t" << precio << " €" << std::endl;
}

//Ventas de los articulos
void Pedido_Articulo::mostrarVentasArticulos(std::ostream& os) const noexcept{
    for (auto i:ap){    //Impromimos los datos de cada libro uno a uno
        os << "Ventas de [" << i.first->referencia() << "]\t" << i.first->titulo() << std::endl;
        os << ventas(*i.first);
    }
}

//Operadores de insercion en flujo
//Insercion en ItemsPedido
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& Iped){
    //Declaracion variables auxiliares
    double total = 0; 
    //Insercion en flujo
    os << "PVP\tCantidad\tArticulo" << std::endl;
    os << std::setfill('=') << std::setw(75) << " " << std::endl;
    //Imprimimos el resto del contenido con un bucle
    for(auto& i:Iped){
        total += (i.second.precio_venta() * i.second.cantidad());
        os << i.second << "\t\t";
        os << "[" << i.first->referencia() << "] " << i.first->titulo() << std::endl;
    }
    os << std::setfill('=') << std::setw(75) << " " << std::endl;
    os << "Total\t" << total << " €" << std::endl;
    return os;
}

//Insercion en Pedidos
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& ped){
    //Declaracion variables auxiliares
    double total = 0;
    unsigned cantidad = 0;
    //Insercion en flujo
    os << "[Pedidos: " << ped.size() << "]" << std::endl;
    os << std::setfill('=') << std::setw(75) << " " << std::endl;
    os << "PVP\tCantidad\tArticulo" << std::endl;
    os << std::setfill('=') << std::setw(75) << " " << std::endl;
    //Imprimimos el contenido con el bucle
    for(auto& i:ped){
        total += (i.second.precio_venta() * i.second.cantidad());
        cantidad += i.second.cantidad();
        os << i.second << "\t\t" << i.first->fecha() << std::endl;
    }
    os << std::setfill('=') << std::setw(75) << " " <<std::endl;
    os << total << " €\t" << cantidad << std::endl;
    return os;
}

//Funciones de OrdenaArticulos y OrdenaPedidos
bool OrdenaArticulos::operator()(const Articulo* a1, const Articulo* a2)const noexcept{return a1->referencia() < a2->referencia();}
bool OrdenaPedidos::operator()(const Pedido* p1, const Pedido* p2)const noexcept{return p1->numero() < p2->numero();}