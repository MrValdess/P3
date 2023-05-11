//Pablo Garcia Bravo

#ifndef _PEDIDO_HPP
#define _PEDIDO_HPP

#include <iostream>
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

//Declaraciones adelantadas
class Tarjeta;
class Numero;
class Fecha;
class Articulo;
class Usuario_Pedido;
class Pedido_Articulo;


///////////////CLASE PEDIDO/////////////
class Pedido{
    public:
        //Constructores
        Pedido(Usuario_Pedido& userped, Pedido_Articulo& pedart, Usuario& user, const Tarjeta& tar, const Fecha& fech = Fecha {});

        //Metodos observadores
        int numero() const noexcept;
        const Tarjeta* tarjeta() const noexcept;
        const Fecha& fecha() const noexcept;
        double total() const noexcept;
        static int n_total_pedidos() noexcept;

        //Clases de excepcion
        class Vacio{
            public:
                Vacio(const Usuario& us);
                const Usuario& usuario() const;
            private:
                const Usuario* user_;
        };

        class Impostor{
            public:
                Impostor(const Usuario& us);
                const Usuario& usuario() const;
            private:
                const Usuario* user_;
        };

        class SinStock{
            public:
                SinStock(const Articulo& a);
                const Articulo& articulo() const;
            private:
                const Articulo* art_;
        };

    private:
        //Variables
        int numero_;
        const Tarjeta* tarjeta_;
        Fecha fecha_;
        double total_;
        static int n_pedidos;
};
//Operador de insercion flujo
std::ostream& operator <<(std::ostream& os, const Pedido& ped);

//Metodos inline
//Metodos observadores
inline int Pedido::numero() const noexcept{return numero_;}
inline const Tarjeta* Pedido::tarjeta() const noexcept{return tarjeta_;}
inline const Fecha& Pedido::fecha() const noexcept{return fecha_;}
inline double Pedido::total() const noexcept{return total_;}
inline int Pedido::n_total_pedidos() noexcept{return n_pedidos;}
//Clases de excepcion//
//Clase Vacio
inline Pedido::Vacio::Vacio(const Usuario& us): user_{&us}{}
inline const Usuario& Pedido::Vacio::usuario() const{return *user_;}
//Clase Impostor
inline Pedido::Impostor::Impostor(const Usuario& us): user_{&us}{}
inline const Usuario& Pedido::Impostor::usuario() const{return *user_;}
//Clase SinStock
inline Pedido::SinStock::SinStock(const Articulo& a): art_{&a}{}
inline const Articulo& Pedido::SinStock::articulo() const{return *art_;}

#endif // _PEDIDO_HPP_