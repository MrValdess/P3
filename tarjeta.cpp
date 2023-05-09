//Pablo  Garcia Bravo

//Añadimos cabeceras
#include "tarjeta.hpp"
#include "usuario.hpp"
#include <locale>
#include <functional>

using std::isspace;
using std::isdigit;


// Declaracion antocipadas//
//Algoritmo de Luhn
bool luhn(const Cadena& numero);
//Todas las tarjetas
std::set<Numero> Tarjeta::tarjetas_;

////////////////CLASE NUMERO/////////////////
struct EsDigito{
    bool operator()(char c)const{return isdigit(c);}
    char c_;
};

struct EsBlanco{
    bool operator()(char c)const{return isspace(c);}
    char c_;
};

//Constructor por defecto
Numero::Numero(const Cadena& num){
    //Le quitamos los espacios
    Cadena aux;
    auto it = std::remove_if(aux.begin(), aux.end(), EsBlanco());
    //Comprobamos que todo sea digito
    auto it2 = std::find_if(aux.begin(), aux.end(), std::not_fn(EsDigito()));
    if(it2 == aux.end()){
        //Verificamos que sea correcta
        if(aux.length() < 13 || aux.length() > 19){ //Si la cadena esta fuera de la longitud valida lanzamos un error
            throw Numero::Incorrecto(LONGITUD);
        }
        else if(!luhn(aux)){    //Si la cadena no cumple el algoritmo de luhn, da error
            throw Numero::Incorrecto(NO_VALIDO);
        }
        //Si cumple ambos criterios, copiamos la cadena sin espacios ni caracteres invalidos
        numero_= aux;
    }
    else{
        throw Numero::Incorrecto(DIGITOS);
    }
}

////////////////CLASE TARJETA/////////////////
Tarjeta::Tarjeta(const Numero& num, Usuario& user, const Fecha& fech): numero_(num), titular_(&user), caducidad_(fech), activa_(true){
    //Comprobamos que la fecha no sea anterior a la del dia de hoy
    Fecha f_actual;
    if(f_actual > caducidad_){
        throw Tarjeta::Caducada(caducidad_);
    }   //Comprobamos que no este duplicada
    else if(!(tarjetas_.insert(numero_).second)){
        throw Num_duplicado{numero_};
    }
    titular()->es_titular_de(*this);
}

//Observador del tipo de la tarjeta
Tarjeta::Tipo Tarjeta::tipo()const noexcept {
    //Creamos una cadena de tamaño 2 con los ultimos caracteres
    Cadena digitos(2);
    digitos[0] = numero_[0];
    digitos[1] = numero_[1];
    //Dependemos del valor de ambos caracteres para devolver un tipo
    if(digitos[0] == '3' && (digitos[1] == '4' || digitos[1] == '7')){
        return Tipo::AmericanExpress;
    }
    else switch(digitos[0]){
        case '3': return Tarjeta::JCB; break;
        case '4': return Tarjeta::VISA; break;
        case '5': return Tarjeta::Mastercard; break;
        case '6': return Tarjeta::Maestro; break;
        default: return Tarjeta::Otro; break;
    }
}

//Destructor
Tarjeta::~Tarjeta(){
    if(titular_){
        const_cast<Usuario*&>(titular_)->no_es_titular_de(*this);
        const_cast<Usuario*&>(titular_)=nullptr;
    }
    //Borramos tarjeta
    tarjetas_.erase(numero());
}

//Operadores de insercion en flujo//
//Insercion sobrecargada de Tipo
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo){
    switch(tipo){
        case Tarjeta::Otro: os << "Otro"; break;
        case Tarjeta::Maestro: os << "Maestro"; break;
        case Tarjeta::Mastercard: os << "Mastercard"; break;
        case Tarjeta::VISA: os << "VISA"; break;
        case Tarjeta::JCB: os << "JCB"; break;
        case Tarjeta::AmericanExpress: os << "American Express"; break;
        default: os <<"Error Tipo tarjeta";
    }
    return os;
}

//Insercion Tarjeta
std::ostream& operator <<(std::ostream& os, const Tarjeta& tar){
    //Insertamos los tipos uno a uno en el os tal y como indica el enunciado
    os << tar.tipo() << std::endl;
    os << tar.numero() << std::endl;
    //Cadena para mostrar el nombre en mayusculas
    Cadena cad_mostrar = tar.titular()->nombre() + " " + tar.titular()->apellidos();
    for(auto& x:cad_mostrar){   //Con x dentro de cad_mostrar cambiamos todas las letras a mayusculas
        if(islower(x)){
            x = toupper(x);
        }
    }
    os << cad_mostrar << std::endl; //Imprimimos la cadena en mayusculas
    //Fecha de caducidad formateada(año de 2 cifras)
    os << "Caduca: " << endl;
    if (tar.caducidad().mes() < 10) {
        os << "0";
    }
    os << (tar.caducidad().mes()) << "/" << (tar.caducidad().anno()%100) << std::endl;
    return os;
}

//Titular facial
Cadena Tarjeta::titular_facial() const {
    Cadena facial = titular()->nombre() + Cadena(" ") + titular()->apellidos();
    for(auto& c: facial){ //Convertir en mayúsculas
        c = std::toupper(c);
    }
    return facial;
}


