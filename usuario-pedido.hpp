//Pablo Garcia Bravo

#ifndef _USUARIO_PEDIDO_HPP
#define _USUARIO_PEDIDO_HPP

#include <iostream>
#include <set>
#include <map>

#include "usuario.hpp"
#include "pedido.hpp"

//Declaraciones adelantadas
class Pedido;
class Usuario;

///////////////CLASE USUARIO_PEDIDO/////////////////
class Usuario_Pedido{
    public:
        //Tipo Pedidos
        typedef std::set<Pedido*> Pedidos;

        //Metodos asocia
        void asocia(Usuario& user, Pedido& ped);
        void asocia(Pedido& ped, Usuario& user);
        //Resto de metodos
        Pedidos pedidos(const Usuario& user) const noexcept;
        const Usuario* cliente(const Pedido& ped) const noexcept;

    private:
        //Mapas 
        typedef std::map<Usuario*,Pedidos> UserPed;
        UserPed up;
        typedef std::map<Pedido*, Usuario*> PedUser;
        PedUser pu;
};

#endif //_USUARIO_PEDIDO_HPP