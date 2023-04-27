//Pablo Garcia Bravo

#include "usuario.hpp"

#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <random>
#include <time.h>
#include "tarjeta.hpp"
#include "articulo.hpp"

using namespace std;

////////////////CLASE CLAVE/////////////////
//Declaraciones anticipadas//
//Set usuarios
std::unordered_set<Cadena> Usuario::usuarios_;

//Constructores//
Clave::Clave(const char* c)
{   
    //Comprobamos longitud
    if (strlen(c)<5) throw Clave::Incorrecta(CORTA);

    //Seleccionamos aleatoriamente caracteres dentro de un string que almacene todos los caracteres para salt
    //srand(time(nullptr)); //Inicializar semilla
    const char* salt_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789./";
    char salt[3];
    salt[0] = salt_chars[rand()%strlen(salt_chars)];
    salt[1] = salt_chars[rand()%strlen(salt_chars)];
    salt[2] = '\0';
    //Encriptamos la cadena. En el caso de que sea NULL(de error), lanzamos un error de encriptacion
    if(crypt(c, salt) == NULL) throw Clave::Incorrecta(ERROR_CRYPT);
    //Si no da error, almacenamos la clave en clave_
    clave_ = crypt(c, salt);
}

//Comprueba si la encriptacion es correcta
bool Clave::verifica(const char* c) const
{
    const char* cifrado = crypt(c,(const char*) clave_);
    return cifrado == clave_;
}

////////////////CLASE USUARIO/////////////////
std::unordered_set<Cadena> usuarios_; //declaracion adelantada

//Constructores//
Usuario::Usuario(const Cadena& ident, const Cadena& nombre,const Cadena& apell, const Cadena& dir, const Clave& clave):
id_(ident), nombre_(nombre), apellidos_(apell), direccion_(dir), contrasena_(clave){
    //Recorremos el mapa de tarjetas y comprobamos su id para ver si esta repetidos
    typedef unordered_set<Cadena>::iterator it;
    std::pair<it, bool> res = usuarios_.insert(id_); // Insertar el id
    if(!res.second){ //Inserción fallida
       throw Usuario::Id_duplicado(id_);
    }
}

//Relacion con Articulo: compra()
void Usuario::compra(const Articulo& art, unsigned int cantidad){
    auto artCesta = articulos_.find(const_cast<Articulo*>(&art));
    if (artCesta == articulos_.end()){  //Si encontramos el articulo en la cesta añadimos al carrito
        if(cantidad > 0){       //Si no es 0 asignamos al stock el valor de la cantidad
            articulos_.insert(std::make_pair(const_cast<Articulo*>(&art), cantidad)) ;
        }
    }
    else{   //Si el articulo esta en cesta
        if (cantidad > 0){
            artCesta->second = cantidad;
        }
        else{   //Si la cantidad es 0 entonces lo eliminamos
            articulos_.erase(artCesta);
        }
    }
}


//Sobrecarga de operador de flujo
std::ostream& operator <<(std::ostream& os, const Usuario& user){
    setlocale(LC_ALL,"");
    os<< user.id()<<" ["<<user.contrasena_.clave()<<"] "<<user.nombre()<<user.apellidos()<<endl;
    os<<user.direccion()<<endl;
    os<<"Tarjetas: "<<endl;
    for(auto& tarjeta: user.tarjetas()){
        os<< *tarjeta.second <<endl;
    }
    return os;
}

//Mostrar carro
ostream& mostrar_carro(ostream& os, const Usuario& user){
    //Almacenamos en flujo los datos del usuario
    os<<"Carrito de compra de "<<user.id()<<" [Artículos: "<<user.n_articulos()<<"]"<<endl;
    os<<"Cant. \tArt."<<endl;
    os<<"==========================================================="<<endl;
    //Almacenamos los datos de cada compra
    for(auto art: user.compra()){
        os<<"["<<art.second<<"] "<<*art.first<<endl;
    }
    return os;
}


//Destructor
Usuario::~Usuario(){
    for(auto t: tarjetas_){ 
        t.second->anular_titular();
        }
    Usuario::usuarios_.erase(id_);
}