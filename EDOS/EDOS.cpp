/**
 * Aproximacion de Ecuaciones diferenciales ordinarias a traves de diferentes metodos numericos
 * @author Benjamin Vargas
 * @version 1.0
*/
#define PRECISION 6 //cantidad de decimales a imprimir
#include<iostream>
#include<cmath>
#include <iomanip>
#include <fstream>
using namespace std;

double f(double,double);
void euler();
void heun();
void puntomedio();
void rk4();
double f(double x, double y) {
    return -2*x*y;
}

int main()
{
    cout<<"EDOS:\n";
    int op=0;
    do
    {
        cout<<"\nSelecciona una opcion:\n";
        cout<<"1.Euler\n";
        cout<<"2.Heun\n";
        cout<<"3.Punto medio\n";
        cout<<"4.RK4\n";
        cout<<"0.Salir\n";
        cin>>op;
        switch (op)
        {
        case 0:
            break;
        case 1:
            euler();
            break;
        case 2:
            heun();
            break;
        case 3:
            puntomedio();
            break;
        case 4:
            rk4();
            break;
        default:
            cout<<"Opcion invalida!\n";
            break;
        }

    } while (op !=0);
    
    
    return 0;
}

void euler()
{
    double xf, xv, y, h;
    int n;


    cout<<"Ingrese el valor inicial (x0) \n";
    cin>>xv;
    cout<<"Ingrese el valor final (xf) \n";
    cin>>xf;
    cout<<"Ingrese el dato inicial (y0) \n";
    cin>>y;
    cout<<"Ingrese la cantidad de subintervalos (n) \n";
    cin>>n;

    h = (xf - xv) / n;

    //Abre el archivo "Euler.txt" en modo de escritura.
    ofstream outputFile("Euler.txt",ios::app);


    cout<<"resultados:\n";
    for (int i = 0; i <= n; ++i) 
    {

        // Escribe la cadena en el archivo.
        outputFile <<xv<<"\t"<<y<<"\n";
        cout<<setprecision(PRECISION)<<xv<<"\t"<<setprecision(PRECISION)<<y<<"\n";

        y = y + h * f(xv,y);
        xv = xv + h;
    }
    // Cierra el archivo.
    outputFile.close();
    cout<<"Datos registrados en Euler.txt\n";
}


void heun()
{
    double xf, xv, y, h,yt,xn;
    int n;


    cout<<"Ingrese el valor inicial (x0) \n";
    cin>>xv;
    cout<<"Ingrese el valor final (xf) \n";
    cin>>xf;
    cout<<"Ingrese el dato inicial (y0) \n";
    cin>>y;
    cout<<"Ingrese la cantidad de subintervalos (n) \n";
    cin>>n;

    h = (xf - xv) / n;

    //Abre el archivo "Heun.txt" en modo de escritura.
    ofstream outputFile("Heun.txt",ios::app);


    cout<<"resultados:\n";
    for (int i = 0; i <= n; ++i) 
    {
        // Escribe la cadena en el archivo.
        outputFile <<xv<<"\t"<<y<<"\n";
        cout<<setprecision(PRECISION)<<xv<<"\t"<<setprecision(PRECISION)<<y<<"\n";
        yt = y + h * f(xv, y);
        xn = xv + h;
        y = y + h * (f(xv, y) + f(xn, yt)) / 2;
        xv = xn;
    }
    // Cierra el archivo.
    outputFile.close();
    cout<<"Datos registrados en Heun.txt\n";
}

void puntomedio()
{
    double xf, xv, y, h,ym,xm;
    int n;


    cout<<"Ingrese el valor inicial (x0) \n";
    cin>>xv;
    cout<<"Ingrese el valor final (xf) \n";
    cin>>xf;
    cout<<"Ingrese el dato inicial (y0) \n";
    cin>>y;
    cout<<"Ingrese la cantidad de subintervalos (n) \n";
    cin>>n;

    h = (xf - xv) / n;

    //Abre el archivo "puntomedio.txt" en modo de escritura.
    ofstream outputFile("puntomedio.txt",ios::app);


    cout<<"resultados:\n";
    for (int i = 0; i <= n; ++i) 
    {
        // Escribe la cadena en el archivo.
        outputFile <<xv<<"\t"<<y<<"\n";
        cout<<setprecision(PRECISION)<<xv<<"\t"<<setprecision(PRECISION)<<y<<"\n";
       ym = y + f(xv, y) * h / 2;
        xm = xv + h / 2;
        y = y + h * f(xm, ym);
        xv = xv + h;
    }
    // Cierra el archivo.
    outputFile.close();
    cout<<"Datos registrados en puntomedio.txt\n";
}


void rk4()
{
    double xf, x, y, h, k1, k2, k3, k4;
    int n;


    cout<<"Ingrese el valor inicial (x0) \n";
    cin>>x;
    cout<<"Ingrese el valor final (xf) \n";
    cin>>xf;
    cout<<"Ingrese el dato inicial (y0) \n";
    cin>>y;
    cout<<"Ingrese la cantidad de subintervalos (n) \n";
    cin>>n;

    h = (xf - x) / n;

    //Abre el archivo "RK4.txt" en modo de escritura.
    ofstream outputFile("RK4.txt",ios::app);


    cout<<"resultados:\n";
    for (int i = 0; i <= n; ++i) 
    {
        // Escribe la cadena en el archivo.
        outputFile <<x<<"\t"<<y<<"\n";
        cout<<setprecision(PRECISION)<<x<<"\t"<<setprecision(PRECISION)<<y<<"\n";
        k1 = f(x, y);
        k2 = f(x + h, y + k1 * h * 1 / 2);
        k3 = f(x + h / 2, y + k2 * h * 1 / 2);
        k4 = f(x + h, y + k3 * h);

        y = y + h * (k1 + 2 * k2 + 2 * k3 + k4) * 1 / 6;
        x = x + h;
    }
    // Cierra el archivo.
    outputFile.close();
    cout<<"Datos registrados en RK4.txt\n";
}

