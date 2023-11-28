/**
 * Localizacion de raices a traves de diferentes metodos numericos
 * @author Benjamin Vargas
 * @version 3.0
*/
#define PRESICION 24 //cantidad de decimales a imprimir
#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;

double f(double);
double g(double);
void biseccion(void);
void regularFalsi(void);
void puntoFijo(void);

double f(double x)
{
    return (x-1)*(x-1)*(x-1);
}

double g(double x)
{
    return 0;
}


int main()
{
    cout<<"Metodos de localizacion de raices\n";
    cout<<"Recuerda modificar las funciones definidas en el codigo, asi como el tipo de error!\n";
    int op =0;

    do
    {
        cout<<"\nSelecciona una opcion:\n";
        cout<<"1.Biseccion\n";
        cout<<"2.Regular Falsi\n";
        cout<<"0.Salir\n";
        cin>>op;
        switch (op)
        {
        case 0:
            break;
        case 1:
            biseccion();
            break;
        case 2:
            regularFalsi();
            break;
        default:
            cout<<"Opcion invalida!\n";
            break;
        }

    } while (op !=0);
    
    
    return 0;
}

void biseccion (void)
{
    double a=0, b=0,c=0, cv=0,tol = 0, e=0;
    int i=1;

    //Obtener valores
    cout<<"\nIngresa el valor a del intervalo: ";
    cin>>a;
    cout<<"\nIngresa el valor b del intervalo: ";
    cin>>b;
    cout<<"\nIngresa el valor de tolerancia (Recuerda que dependera del tipo de error a usar):";
    cin>>tol;
    cout<<"\nIngresa el valor a inicial del error(grande): ";
    cin>>e;

    if(f(a)*f(b)>0)
    {
        cout<<"No hay raiz o hay un numero par de ellas en el intervalo ingresado";
    }
    else
    {
        //inicio de metodo:
        do
        {
            c=(a+b)/2;
            if(f(a)*f(c)>0) //raiz se encuentra en sector (c,b)
            {
                a=c;
            }
            else if (f(a)*f(c)<0) //raiz se encuentra en sector (a,c)
            {
                b=c;
            }
            else if(f(a)*f(c)==0)//raiz es c
            {
                cout<<"Raiz localizada en c!\n";

            }

            //calculo de error

            //error biseccion clasico
            e = (b-a)/2;

            //otro tipo de errores
            //primera iteracion
            if(i==1)
            {
               cv=a; 
            }

            //error relativo aproximado
            //e = fabs(c-cv)/fabs(cv);

            //error porcentual aproximado
            //e = (fabs(c-cv)/fabs(cv))*100;

            //error absoluto aproximado
            //e = fabs(c-cv);


            cv=c;
            i++; //iteraciones

        }while(e > tol);
        
        cout<<"\nRaiz = "<<setprecision(PRESICION) << c<<"\nError: "<<setprecision(PRESICION) << e<<"\nIteraciones:"<<i<<"\n";
    }

}

void regularFalsi(void)
{
    double a=0, b=0,c=0, cv=0,tol = 0, e=0;
    int i=1;

    //Obtener valores
    cout<<"\nIngresa el valor a del intervalo: ";
    cin>>a;
    cout<<"\nIngresa el valor b del intervalo: ";
    cin>>b;
    cout<<"\nIngresa el valor de tolerancia (Recuerda que dependera del tipo de error a usar):";
    cin>>tol;
    cout<<"\nIngresa el valor a inicial del error(grande): ";
    cin>>e;

    if(f(a)*f(b)>0)
    {
        cout<<"No hay raiz o hay un numero par de ellas en el intervalo ingresado";
    }
    else
    {
        //inicio de metodo:
        do
        {
            c=(a*f(b)-b*f(a))/(f(b)-f(a));

            if(f(a)*f(c)>0) //raiz se encuentra en sector (c,b)
            {
                a=c;
            }
            else if (f(a)*f(c)<0) //raiz se encuentra en sector (a,c)
            {
                b=c;
            }
            else if(f(a)*f(c)==0)//raiz es c
            {
                cout<<"Raiz localizada en c!\n";

            }

            //calculo de error

            //otro tipo de errores
            //primera iteracion
            if(i==1)
            {
               cv=a; 
            }

            //error relativo aproximado
            //e = fabs(c-cv)/fabs(cv);

            //error porcentual aproximado
            //e = (fabs(c-cv)/fabs(cv))*100;

            //error absoluto aproximado
            e = fabs(c-cv);


            cv=c;
            i++; //iteraciones

        }while(e > tol);
        
        cout<<"\nRaiz = "<<setprecision(PRESICION) << c<<"\nError: "<<setprecision(PRESICION) << e<<"\nIteraciones:"<<i<<"\n";
    }
}

void puntoFijo(void)
{
    double xn = 0,e=1, tol=0, xv=0;
    int i =1;

    cout<<"Ingresa un punto(Puede ser cualquiera): ";
    cin>>xv;
    cout<<"\nIngresa tolerancia: ";
    cin>>tol;
    do
    {
        if(fabs((g(xv + 0.001)-g(xv))/0.001) >= 1)//calculo de derivada
        {
            cout<<"No se cumple criterio de convergencia g'(x) >= 1 \n g'(x) = "<<fabs((g(xv + 0.001)-g(xv))/0.001);
            break;
        }
        else
        {
            xn = g(xv); 

            //error absoluto aproximado
            e = fabs(xv-xn);

            //error relativo aproximado
            //e = fabs(c-cv)/fabs(cv);

            //error porcentual aproximado
            //e = (fabs(c-cv)/fabs(cv))*100;

        }
        xv = xn;
        i++;
    } while (e > tol);
    cout<<"\nPunto fijo = "<<setprecision(PRESICION)<<xn<<"\nError= "<<setprecision(PRESICION)<<e<<"\nIteraciones: "<<i<<"\n";
}