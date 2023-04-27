#ifndef _TARJETA_HPP
#define _TARJETA_HPP


#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <set>
#include <iostream>
#include <locale>
#include <algorithm>

using std::set;
using std::endl;

class Usuario;

/////////CLASE NUMERO//////////////
class Numero{
    public:
        //Constructor
        Numero(const Cadena& num);

        //Operador de conversion a const char
        operator const char*() const;

        //Clase Incorrecto y enum Razon
        enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
        class Incorrecto{
            public:
                Incorrecto(Razon razon): razon_(razon){}
                Numero::Razon razon() const{return razon_;}
            private:
                Numero::Razon razon_;
        };

    private:
        Cadena numero_;
};

//Operador de conversión 
inline Numero::operator const char*() const{ 
    return (const char*) numero_;
}


//Operador menor que
inline bool operator < (const Numero& num1, const Numero& num2){
    return strcmp(static_cast<const char*>(num1), static_cast<const char*>(num2)) < 0;
}

////////////CLASE TARJETA///////////////
class Tarjeta{
    public:
        //Constructor y eliminación de copia
        Tarjeta(const Numero& num, Usuario& titular, const Fecha& cad); 
        Tarjeta(const Tarjeta& ) = delete;
        Tarjeta& operator =(const Tarjeta&) = delete;

        //Enum de Tipo
        enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
        
        //Métodos observadores
        const Numero& numero() const;
        Usuario* titular() const;
        const Fecha& caducidad() const;
        bool activa() const ;
        bool activa(bool estado);
        Tipo tipo() const noexcept;

        //Hacemos friend al operador de insercion para acceder a la parte privada
        friend std::ostream& operator <<(std::ostream& os, const Tarjeta& tar);
        friend std::ostream& operator <<(std::ostream& os, const Tipo& tipo);

        //Titular Facial
        Cadena titular_facial() const;
        
        //Clase Caducada
        class Caducada{
            public:
                Caducada(Fecha fecha):fecha_(fecha){}
                Fecha cuando() const {return fecha_;}
            private:
                Fecha fecha_;
        };

        //Clase Num_duplicado
        class Num_duplicado{
            public:
                Num_duplicado(const Numero& duplicado):duplicado_(duplicado){}
                Numero que() const {return duplicado_;}
            private:
                Numero duplicado_;
        };

        //Destructor
        ~Tarjeta();
    private:
        //Variables
        const Numero numero_;
        Usuario* const titular_; //enlace con objeto usuario
        const Fecha caducidad_;
        bool activa_;
        static set<Numero> tarjetas_;

        //Anular Tarjeta
        friend class Usuario;
        void anular_titular();
};

//Métodos observadores
inline const Numero& Tarjeta::numero() const{return numero_;}
inline Usuario* Tarjeta::titular() const {return titular_;}
inline const Fecha& Tarjeta::caducidad() const {return caducidad_;}
inline bool Tarjeta::activa() const {return activa_;}
//Sobrecarga
inline bool Tarjeta::activa(bool estado){
    activa_ = estado;
    return activa_;
}
//Anular tarjeta
inline void Tarjeta::anular_titular(){
    activa(false);
    const_cast<Usuario*&>(titular_)=nullptr;
}


//Operador menor que
bool operator <(const Tarjeta& tar1, const Tarjeta& tar2);

inline bool operator <(const Tarjeta& tar1, const Tarjeta& tar2){
    return tar1.numero() < tar2.numero();
}

#endif //_TARJETA_HPP_