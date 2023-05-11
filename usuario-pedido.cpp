//Pablo Garcia Bravo

#include "usuario-pedido.hpp"

//Metodos asocia
void Usuario_Pedido::asocia(Usuario& user, Pedido& ped){
    //Insertamos los valores directamente a los diccionarios 
    up[&user].insert((Pedido*)&ped);  
    pu[&ped] = (Usuario*)&user;
}

void Usuario_Pedido::asocia(Pedido& ped, Usuario& user){
    asocia(user, ped);
}

//Resto de metodos
Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(const Usuario& user) const noexcept{
    auto i = up.find((Usuario*)&user);
    if(i != up.end()){  //Si lo encuentra devuelve el elemento asociado en el mapa
        return i->second;
    }
    else{   //Si no lo encuentra crea una instancia nueva de Pedidos vacia que la devolvemos
        return Usuario_Pedido::Pedidos{};
    }
} 

const Usuario* Usuario_Pedido::cliente(const Pedido& ped) const noexcept{
    auto i = pu.find((Pedido*)&ped);
    if(i != pu.end()){  //Si lo encuentra devuelve el elemento asociado en el mapa
        return i->second;
    }
    else{   //Si no lo encuentra devovemos nullptr
        return nullptr;
    }
}