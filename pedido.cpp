//Pablo Garcia Bravo

#include "pedido.hpp"
#include <unordered_map>

/////////////CLASE PEDIDO////////////////
//Constructor
int Num_pedidos = 0;    
Pedido::Pedido(Usuario_Pedido& userped, Pedido_Articulo& pedart, Usuario& user, const Tarjeta& tar,const Fecha& fech):numero_{Num_pedidos + 1}, tarjeta_{&tar}, fecha_(fech), total_(0.){
    //Comprobamos si se da alguna de las excepciones:
    //Tarjeta caducada
    if(tar.caducidad() < fech){
        throw Tarjeta::Caducada(tar.caducidad());
    }

    //Tarjeta desactivada
    if(!tar.activa()){
        throw Tarjeta::Desactivada(); 
    }

    //Pedido Impostor
    if(&user!= tar.titular()){
        throw Pedido::Impostor(user);
    }

    //Pedido Vacio
    if(user.n_articulos() == 0){
        throw Pedido::Vacio(user);
    }

    //Sin stock del articulo
    auto it = user.compra().begin();
    while(it != user.compra().end()){
        if(it->first->stock() < it->second){
            Pedido::SinStock nost{*it->first};
            const_cast<Usuario::Articulos&>(user.compra()).clear();
            throw nost;
        }
        it++;
    }
    
    //En el caso de que no se de ninguna excepcion realizamos los siguientes procedimientos:
    userped.asocia(user, *this);
    while(!user.compra().empty()){
        auto i = user.compra().begin();
        //Actualizamos el stock,
        i->first->stock() -= i->second;
        //Sumamos el precio al total
        total_ += i->second * i->first->precio();
        //Llamamos a pedir
        pedart.pedir(*i->first, *this, i->first->precio(), i->second);
        user.compra(*i->first, 0);
    }

    //Actualizamos el numero del pedido
    Num_pedidos++;
}


//Operador de flujo
std::ostream& operator <<(std::ostream& os, const Pedido& ped){
    os << "Núm. pedido: " << ped.numero() << std::endl;
    os << "Fecha: " << ped.fecha() << std::endl;
    if(ped.tarjeta()->tipo() == Tarjeta::Otro){
        os << "Pagado con: "<< "Tipo indeterminado " << " n.º: " << ped.tarjeta()->numero() << std::endl;
    }
    else{
        os << "Pagado con: " << ped.tarjeta()->tipo() << " n.º: " << ped.tarjeta()->numero() << std::endl;
    }
    os << "Importe: " << ped.total() << " €" << std::endl;
    return os;
}