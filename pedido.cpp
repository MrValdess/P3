//Pablo Garcia Bravo

#include "pedido.hpp"

/////////////CLASE PEDIDO////////////////
//Constructor
int Num_pedidos = 0;
Pedido::Pedido(Usuario_Pedido& userped, Pedido_Articulo& pedart, Usuario& user, Tarjeta& tar,const Fecha& fech):numero_{Num_pedidos + 1}, tarjeta_{&tar}, fecha_(fech), total_(0.){
    //Comprobamos si se da alguna de las excepciones:
    //Tarjeta caducada
    if(tar.caducidad() < fech){
        throw Tarjeta::Caducada(fech);
    }

    //Tarjeta desactivada
    if(!tar.activa()){
        throw Tarjeta::Desactivada(); 
    }

    //Pedido Impostor
    if(this->tarjeta()->titular()!= tar.titular()){
        throw Pedido::Impostor(user);
    }

    //Pedido Vacio
    if(this->n_total_pedidos() == 0){
        throw Pedido::Vacio(user);
    }

    //Sin stock del articulo
    for(auto it:pedart.detalle(*this)){
        if(it.second.cantidad() > it.first->stock()){
            user.vaciar_carro();
            throw Pedido::SinStock(it.first);
        }
    }
    //En el caso de que no se de ninguna excepcion realizamos los siguientes procedimientos:
    //Actualizamos el stock, llamamos a pedir y sumamos el precio al total
    for(auto it:pedart.detalle(*this)){
        it.first->stock_ -= it.second.cantidad(); //???????
        pedart.pedir(*this, *it.first, it.first->precio_, it.second.cantidad());
        total_ +=  it.first->precio_;
        Num_pedidos++;
    }

    //Vaciamos el carro
    user.vaciar_carro();

    //Actualizamos el numero del pedido
    numero_ = Num_pedidos;
}


//Operador de flujo
std::ostream& operator <<(std::ostream& os, Pedido ped){
    os << "Num. pedido: " << ped.numero() << endl;
    os << "Fecha:       " << ped.fecha() << endl;
    os << "Pagado con:  " << ped.tarjeta()->tipo() << "n.º: " << ped.tarjeta()->numero() << endl;
    os << "Importe:     " << ped.total() << " €" << endl;
    return os;
}