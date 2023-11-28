/**
 * Localizacion de raices a traves de diferentes metodos numericos
 * @author Benjamin Vargas
 * @version 4.0
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
void newtonRaphson(void);
double df(double x);
void secante(void);

double df(double x)
{
    return 2*x;
}

double f(double x)
{
    return pow(x,2)-2;
}

double g(double x)
{
    return exp(-x);
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
        cout<<"3.Punto Fijo\n";
        cout<<"4.Newton - Raphson\n";
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
        case 3:
            puntoFijo();
            break;
        case 4:
            newtonRaphson();
            break;
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
            //e = fabs(c-cv)/fabs(c);

            //error porcentual aproximado
            //e = (fabs(c-cv)/fabs(c))*100;

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
            //e = fabs(c-cv)/fabs(c);

            //error porcentual aproximado
            //e = (fabs(c-cv)/fabs(c))*100;

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
    cout<<"Recuerda modificar correctamente la funcion g(x)=x\n";
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
            //e = fabs(xn-xv)/fabs(xn);

            //error porcentual aproximado
            //e = (fabs(xn-xv)/fabs(xn))*100;

        }
        xv = xn;
        i++;
    } while (e > tol);
    cout<<"\nPunto fijo = "<<setprecision(PRESICION)<<xn<<"\nError= "<<setprecision(PRESICION)<<e<<"\nIteraciones: "<<i<<"\n";
}

void newtonRaphson(void)
{
    double xv=0,xn=0,e=0,tol=0;
    int ii=1, flag=0;
    cout<<"Recuerda definir correctamente f(x) y f'(x), y un limite de iteraciones\n";
    cout<<"Ingresa un punto: ";
    cin>>xv;
    cout<<"\nIngresa tolerancia: ";
    cin>>tol;
    
    do
    {
        if(ii>10000)
        {
            cout<<"Mas de 10 mil iteraciones!\n";
            flag=1;
            break;
        }
        if(fabs(df(xv))< 1e-5)
        {
            cout<<"\nderivada muy pequeña";
            flag =1;
            break;
        }
        else
        {
            xn = xv - (f(xv)/df(xv));

            //error absoluto aproximado
            e = fabs(xv-xn);

            //error relativo aproximado
            //e = fabs(xn-xv)/fabs(xn);

            //error porcentual aproximado
            //e = (fabs(xn-xv)/fabs(xn))*100;

            xv=xn;
        }
        ii++;
    }
    while(e>tol);
    if(!flag)
    {
        cout<<"\nRaiz = "<<setprecision(PRESICION)<<xn<<"\nError= "<<setprecision(PRESICION)<<e<<"\nIteraciones: "<<ii;
    }   
}

void secante(void)
{}