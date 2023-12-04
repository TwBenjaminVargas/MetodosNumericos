/**
 * Solucion de sistemas de Ecuaciones diferenciales ordinarias a traves de diferentes metodos numericos
 * para 2 ecuaciones
 * @author Benjamin Vargas
 * @version 1.0
*/
#define PRECISION 6 //cantidad de decimales a imprimir
#include<iostream>
#include<cmath>
#include <iomanip>
#include <fstream>
using namespace std;


double f1(double,double,double);
double f2(double,double,double);
void euler(void);
void rk4(void);

int main()
{
    cout<<"Sistemas de EDOS:\n";
    int op=0;
    do
    {
        cout<<"\nSelecciona una opcion:\n";
        cout<<"1.Resolver sistema 2 ecuaciones Euler\n";
        cout<<"2.Resolver sistema 2 ecuaciones RK4\n";
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
            rk4();
            break;
        default:
            cout<<"Opcion invalida!\n";
            break;
        }

    } while (op !=0);
    
    
    return 0;
}

void euler(void)
{
    double xf, xv, y1, h,y2;
    int n;


    cout<<"Ingrese el valor inicial (x0) \n";
    cin>>xv;
    cout<<"Ingrese el valor final (xf) \n";
    cin>>xf;
    cout<<"Ingrese el dato inicial (y1.0) \n";
    cin>>y1;
    cout<<"Ingrese el dato inicial (y2.0)\n";
    cin>>y2;
    cout<<"Ingrese la cantidad de subintervalos (n) \n";
    cin>>n;

    h = (xf - xv) / n;

    //Abre el archivo "Sistema.txt" en modo de escritura.
    ofstream outputFile("Sistema.txt",ios::app);


    cout<<"resultados:\n";
    cout<<"x\ty1\ty2\n";
    for (int i = 0; i <= n; ++i) 
    {

        // Escribe la cadena en el archivo.
        outputFile <<xv<<"\t"<<y1<<"\t"<<y2<<"\n";
        cout<<setprecision(PRECISION)<<xv<<"\t"<<setprecision(PRECISION)<<y1<<"\t"<<setprecision(PRECISION)<<y2<<"\n";

        y1 = y1 + h * f1(xv,y1,y2);
        y2= y2 + h*f2(xv,y1,y2);
        xv = xv + h;
    }
    // Cierra el archivo.
    outputFile.close();
    cout<<"Datos registrados en Sistema.txt\n";
}

void rk4(void)
{
    double xf, x, y1,y2, h, k11, k21, k31, k41,k12,k22,k32,k42;
    int n;


    cout<<"Ingrese el valor inicial (x0) \n";
    cin>>x;
    cout<<"Ingrese el valor final (xf) \n";
    cin>>xf;
    cout<<"Ingrese el dato inicial (y1.0) \n";
    cin>>y1;
    cout<<"Ingrese el dato inicial (y2.0)\n";
    cin>>y2;
    cout<<"Ingrese la cantidad de subintervalos (n) \n";
    cin>>n;

    h = (xf - x) / n;

    //Abre el archivo "Sistema.txt" en modo de escritura.
    ofstream outputFile("Sistema.txt",ios::app);


    cout<<"resultados:\n";
    cout<<"x\ty1\ty2\n";
    for (int i = 0; i <= n; ++i) 
    {

        // Escribe la cadena en el archivo.
        outputFile <<x<<"\t"<<y1<<"\t"<<y2<<"\n";
        cout<<setprecision(PRECISION)<<x<<"\t"<<setprecision(PRECISION)<<y1<<"\t"<<setprecision(PRECISION)<<y2<<"\n";

        k11=f1(x,y1,y2);
        k12=f2(x,y1,y2);

        k21 = f1(x + h, y1 + k11 * h * 1 / 2,y2 + k11 * h * 1 / 2);
        k22 = f2(x + h, y1 + k11 * h * 1 / 2,y2 + k12 * h * 1 / 2);

        k31 = f1(x + h / 2, y1 + k21 * h * 1 / 2,y2 + k22 * h * 1 / 2);
        k32 = f2(x + h / 2, y1 + k21 * h * 1 / 2,y2 + k22 * h * 1 / 2);

        k41 = f1(x + h, y1 + k31 * h,y2 + k32 * h);
        k42 = f2(x + h, y1 + k31 * h,y2 + k32 * h);


        y1 = y1 + h * (k11 + 2 * k21 + 2 * k31 + k41) * 1 / 6;

        y2 = y2 + h * (k12 + 2 * k22 + 2 * k32 + k42) * 1 / 6;

        x = x + h;

    }
    // Cierra el archivo.
    outputFile.close();
    cout<<"Datos registrados en Sistema.txt\n";
}
double f1(double x,double y1,double y2)
{
    return 3*x+y2;
}

double f2(double x,double y1,double y2)
{
    return pow(x,2)-y1-1;
}