#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<iostream>
#include <exception>
#include <string>

class Neurona {
private:
    int id;
    float voltaje;
    int posicion_x, posicion_y;
    int red;
    int green, blue;
public:

    Neurona(): id(0), voltaje(0.0), posicion_x(0), posicion_y(0), red(0) ,green(0), blue(0){};

    void print(){
        std::cout<<"informacion id: " << id <<"-"<< voltaje<<std::endl;

        std::cout<<"informacion voltaje: " << posicion_x<<"-"<< posicion_y << std::endl;

        std::cout<<"colores rojo, azul y verde: " <<"-"<<red <<"-"<< green; std::cout<<","<< blue << std::endl;
    }

    std::string toString(){
        std::string resultado;

        resultado += std::to_string(id);
            resultado += " | ";
        resultado += std::to_string(voltaje);
             resultado += " | ";
        resultado += std::to_string(posicion_x);
            resultado += " | ";
        resultado += std::to_string(posicion_y);
            resultado += " | ";
        resultado += std::to_string(red);
            resultado += " | ";
        resultado += std::to_string(green);
            resultado += " | ";
        resultado += std::to_string(blue);
            resultado += " |";
        return resultado;

    }

    void setId(int id_1){
        id = id_1;
    }

    void setPosicionX(int x){
        posicion_x = x;
    }

    void setPosicionY(int y){
        posicion_y = y;
    }

    void setRed(int red_1){
        red = red_1;
    }

    void setBlue(int blue_1){
        blue = blue_1;
    }


    void setGreen(int green_1){
        green = green_1;
    }

    void setVoltaje(float voltaje_1){
        voltaje = voltaje_1;
    }

    int getId(){
        return id;

    }

    float getVoltaje(){
        return voltaje;
    }

    int getPosicionX(){
        return posicion_x;

    }

    int getPosicionY(){
        return posicion_y;

    }

    int getRed(){
        return red;
    }

    int getGreen(){
        return green;
    }

    int getBlue(){
        return blue;
    }
};





template <class T>
    class Administrar{

        class Node; // Forward Declaration

    public:

        class Exception : public std::exception { // Clase anidada
            private:
                std::string msg;
            public:
                explicit Exception(const char* message) : msg(message) { }
                explicit Exception(const std::string& message): msg(message) { }
                virtual ~Exception() throw() { }
                virtual const char* what() const throw ( ) {
                    return msg.c_str();
                    }
            };

        typedef Node* position; //Elgancia en programacion en ves de recibir un Node* recibimos una posicion

    private:
        class Node { // Clase anidada
            private:
                T data;
                position next;
            public:
                Node();
                Node(const T&);

                T getData();
                position getNext() const;

                void setData(const T&);
                void setNext(position);

            };
        position anchor;

        void copyAll(const Administrar<T>&);

        bool isValidPos(const position&) const;

    public:

        Administrar();
        Administrar(const Administrar&);


        bool isEmpty() const;
        void insertData(const position&,const T&);


        void deleteData(const position&);

        position findData(const T&) const;
        T retrieve(position) const;

        position getFirstPos() const;
        position getLastPos() const;
        position getPrevPost(position) const;
        position getNextPos(position) const;


        void deleteAll();

        void toString() const;

        Administrar& operator = (const Administrar&);


    };

// inicio de node

template <class T>
Administrar<T>::Node::Node() : next(nullptr) {}

template <class T>
Administrar<T>::Node::Node (const T& e) : data(e), next(nullptr) {}

template <class T>
T Administrar<T>::Node::getData()  {
    return data;
    }

template <class T>
typename Administrar<T>::position Administrar<T>::Node::getNext() const {
    return next;
    }

template <class T>
void Administrar<T>::Node::setData(const T& e) {
    data = e;
    }

template <class T>
void Administrar<T>::Node::setNext(position p) {
    next = p;
    }

// final de node

using namespace std;

template <class T>

Administrar<T>::Administrar() : anchor(nullptr) {}

template <class T>
Administrar<T>::Administrar(const Administrar& l) {
    copyAll(l);
    }


template <class T>
bool Administrar<T>::isValidPos(const position& p) const {
    position aux(anchor);

    while(aux != nullptr) { //mientras no llegue al final

        if(aux == p) { //revisa si es esa posicion
            return true;
            }
        aux = aux->getNext(); // se va recorriendo
        }
    return false; // si no la encuentra
    }


template <class T>
bool Administrar<T>::isEmpty() const {
    return anchor == nullptr;
    }


    template <class T>
    void Administrar<T>::insertData(const position& p, const T& e) { //dependiendo la posicion que damos es donde se inserta
    //es un metodo general para insertar, donde dependiendo la instruccion (posicion) se inserta ahi

        if(p != nullptr and !isValidPos(p)) {
        throw Exception("Posicion invalida, insertada");
        }

        position aux (new Node(e));

        if(aux == nullptr) {
        throw Exception("Memoria no disponible, insertData");
        }
        if(p == nullptr) { //insertar al principio
        aux->setNext(anchor);
        anchor = aux;
        }
        else { // insertamos en otro lugar
        aux->setNext(p->getNext());
        p->setNext(aux); // insercion despues del punto de interes
        }
    }


template <class T>
void Administrar<T>::deleteData(const position& p) {
    if(!isValidPos(p)) {
        throw Exception("Posicion invalida, deleteData");
        }

    if(p == anchor) { // primer elemento
        anchor = p->getNext();
        }
    else {
        getPrevPost(p)->setNext(p->getNext());
        }

    delete p;
    }

template <class T>
typename Administrar<T>::position Administrar<T>::findData(const T& e) const {
        position aux(anchor);

        while( aux != nullptr and aux->getData() != e){
            aux = aux->getNext();
        }
        return aux;
    }

template <class T>
T Administrar<T>::retrieve(position p) const {
    if(!isValidPos(p)){
        throw Exception("Posicion invalida, retrieve");
    }

    return p->getData();
    }

template <class T>
typename Administrar<T>::position Administrar<T>::getLastPos() const {
    if(isEmpty()) {
        return nullptr;
        }
    position aux(anchor);

    while(aux->getNext() != nullptr) {
        aux = aux->getNext();
        }

    return aux;
    }

template <class T>
typename Administrar<T>::position Administrar<T>::getFirstPos() const {
    return anchor;
    }

template <class T>
typename Administrar<T>::position Administrar<T>::getNextPos( position p) const {
    if(!isValidPos()) {
        return nullptr;
        }
    return p->getNext();
    }

template <class T>
typename Administrar<T>::position Administrar<T>::getPrevPost( position p) const {
    if(p == anchor) {
        return nullptr;
        }
    position aux(anchor);

    while(aux != nullptr and aux->getNext() != p) {
        aux = aux->getNext();
        }

    return aux;
    }
template <class T>
void Administrar<T>::toString() const {

    position aux(anchor);

    while(aux != nullptr) {
        std::cout<<aux->getData().toString() <<endl;

        aux = aux->getNext();
    }

}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    Neurona n;
    Administrar<Neurona> lista;

};
#endif // MAINWINDOW_H
