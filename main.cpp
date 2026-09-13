#include <iostream> 
//vector < tipo_de_los_valores > nombre_de_la_variable( tamaño 

int main(){
    std::cout<<"introduce el total de valores del arreglo:";
    int x; 
    int y;
    std::cin>> x;

    //La longitud del arreglo es establecida por el usuario
    int vector [x];
    
    //int tamano = sizeof(vector) / sizeof(vector[0]);
    for(int i=0 ; i < x; i++){
        std::cout<< "Introduce un elemento para la posición: "<<i+1<<"\n";
        std::cin>> y;
        vector[i]=y;
        std::cout<< "El valor para la posición "<<i+1<<" es: "<<y<<"\n";
        
    }
    system("clear");
    ///recorremos cada elemento del arreglo y lo mostramos
    for(int i=0 ; i < x; i++){
        if(i==1){
            vector[i] = 10;
        }
        std::cout<< "El valor para la posición "<<i+1<<" es: "<<vector[i]<<"\n";
    }

}

/*

Last in First out
First in First out


*/