//Pablo Garcia Bravo

#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_

#include "../P1/cadena.hpp"
#include "tarjeta.hpp"

#include <iostream>
#include <map>                  //Mapa de tarjetas
#include <unordered_map>        //Mapa de articulos
#include <unordered_set>        //Set de usuarios

using std::map;
using std::unordered_map;
using std::unordered_set;
using std::ostream;

//Declaraciones adelantadas
class Tarjeta;
class Numero;
class Articulo;


////////////////////CLASE CLAVE/////////////////

class Clave{
    public:
        //Contructor
        Clave(const char* c= ""); 

        //Método Observador
        Cadena clave() const;

        //Verificar
        bool verifica(const char* c) const;

        //Clase Incorrectay Razon
        enum Razon {CORTA, ERROR_CRYPT};
        class Incorrecta{
            public:
                Incorrecta(Razon razon): razon_(razon){}
                Razon razon() const noexcept{return razon_;}
            private:
                Razon razon_;
        };
        
    private:
        Cadena clave_; 
};
//Metodos inline
inline Cadena Clave::clave() const {return clave_;}

////////////////CLASE USUARIO/////////////////
class Usuario{
    public:
        //Definicion de los mapas de tarjetas y articulos
        typedef std::map<Numero,Tarjeta*> Tarjetas;
        typedef std::unordered_map<Articulo*,unsigned int> Articulos; 

        //Constructores
        Usuario(const Cadena& id, const Cadena& nom, const Cadena& apel, const Cadena& dir, const Clave& con);
        //Suprimimos el constructor de copia y el operador de asignacion
        Usuario(const Usuario&) = delete;
        void operator = (const Usuario&) = delete;

        //Métodos observadores
        const Cadena& id() const noexcept;
        const Cadena& nombre() const noexcept;
        const Cadena& apellidos() const noexcept;
        const Cadena& direccion() const noexcept;
        const Tarjetas& tarjetas() const noexcept;
        const Articulos& compra() const noexcept;

        //Metodos de compra
        void compra(const Articulo& art, unsigned int cantidad = 1);
        void vaciar_carro();
        unsigned int n_articulos() const;

        //Relaciones con la clase Tarjeta
        void es_titular_de(const Tarjeta& tarjeta);
        void no_es_titular_de(const Tarjeta& tarjeta);

        ////Hacemos la funcion std friend para acceder a la parte privada y para mostrar el carro
        friend ostream& operator <<(ostream& os, const Usuario& user);
        friend ostream& mostrar_carro(ostream& os, const Usuario& user);
        
        //Clase Id_duplicado
        class Id_duplicado{
        public:
            Id_duplicado(Cadena dup):id_(dup){}
            Cadena idd() const{return id_;}
        private: 
            Cadena id_;
        };

        //Destructor
        ~Usuario();
        
    private:
        const Cadena id_, nombre_, apellidos_, direccion_;
        Clave contrasena_;
        //Declaramos una cariable con cada mapa
        Articulos articulos_;
        Tarjetas tarjetas_;

        //Set en el que guardamos los usuarios
        static std::unordered_set<Cadena> usuarios_;
};

//Métodos observadores
inline const Cadena& Usuario::id() const noexcept{return id_;}
inline const Cadena& Usuario::nombre() const noexcept{return nombre_;}
inline const Cadena& Usuario::apellidos() const noexcept{return apellidos_;}
inline const Cadena& Usuario::direccion() const noexcept{return direccion_;}
inline const Usuario::Tarjetas& Usuario::tarjetas() const noexcept{return tarjetas_;}
inline const Usuario::Articulos& Usuario::compra() const noexcept{return articulos_;}

//Asociaciones con tarjeta inline
inline void Usuario::es_titular_de(const Tarjeta& t){
    if(t.titular() == this) //Si la tarjeta es del usuario la añadimos
        tarjetas_[t.numero()]= const_cast<Tarjeta*>(&t); 
}

inline void Usuario::no_es_titular_de(const Tarjeta& t){
    tarjetas_.erase(t.numero()); //Borramos la tarjeta del usuario
}
//Vaciar carro
inline void Usuario::vaciar_carro(){articulos_.clear();}

//Numero de articulos
inline unsigned int Usuario::n_articulos() const{return articulos_.size();}

#endif // _USUARIO_HPP_