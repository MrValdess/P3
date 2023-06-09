//Pablo Garcia Bravo

#ifndef _PEDIDO_ARTICULO_HPP
#define _PEDIDO_ARTICULO_HPP

#include <iostream>
#include <iomanip>
#include <map>

#include "articulo.hpp"
#include "pedido.hpp"

//Declaraciones adelantadas
class Pedido;
class Articulo;

///////////////CLASE LINEAPEDIDO/////////////////////
class LineaPedido{
    public:
        //Constructores
        LineaPedido(double pv, int cv = 1);

        //Metodos observadores
        double precio_venta() const noexcept;
        unsigned int cantidad() const noexcept;

    private:
        //Definicion variables
        double precioVenta_;
        unsigned int cantidadVendida_;
};
//Operador de insercion de flujo
std::ostream& operator <<(std::ostream& os, const LineaPedido& Lp);

//Metodos inline
inline LineaPedido::LineaPedido(double pv, int cv): precioVenta_(pv), cantidadVendida_(cv){}
inline double LineaPedido::precio_venta() const noexcept {return precioVenta_;}
inline unsigned int LineaPedido::cantidad() const noexcept {return cantidadVendida_;}


///////////////CLASE PEDIDO_ARTICULO/////////////////
//Declaraciones adelantadas
class OrdenaArticulos: public std::binary_function<Articulo*, Articulo*, bool>{
    public: 
        bool operator ()(const Articulo* art1, const Articulo* art2) const noexcept;
};
class OrdenaPedidos: public std::binary_function<Articulo*, Articulo*, bool>{
    public: 
        bool operator ()(const Pedido* ped1, const Pedido* ped2) const noexcept;
};

class Pedido_Articulo{
    public:
        //Definiciones de variables y mapas publicos
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
        
        //Metodos pedir sobrecargados
        void pedir(Pedido& ped, Articulo& art, double precio, unsigned cantidad = 1);
        void pedir(Articulo& art, Pedido& ped, double precio, unsigned cantidad = 1);

        //Resto de metodos
        ItemsPedido detalle(const Pedido& ped) const;
        Pedidos ventas(const Articulo& art) const;

        //Metodos observadores del flujo
        void mostrarDetallePedidos(std::ostream& os) const noexcept;
        void mostrarVentasArticulos(std::ostream& os) const noexcept;

    private:
        //Definicion de diccionarios
        typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedArt;
        PedArt pa;
        typedef std::map<Articulo*, Pedidos, OrdenaArticulos> ArtPed;
        ArtPed ap;

};
//Operadores de insercion en flujo
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& Iped);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& ped);

#endif //_PEDIDO_ARTICULO_HPP