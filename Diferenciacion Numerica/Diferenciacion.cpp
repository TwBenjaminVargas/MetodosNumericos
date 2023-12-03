/**
 * Diferenciacion a traves de diferentes metodos numericos
 * @author Benjamin Vargas
 * @version 1.0
*/
#define PRECISION 6 //cantidad de decimales a imprimir
#include<iostream>
#include<cmath>
#include <iomanip>
#include <fstream>
using namespace std;

double f(double);
void diferenciacionAdelante(void);
void diferenciacionAdelante(double**,int);
void diferenciacionCentrada(void);
void diferenciacionCentrada(double**,int);
void diferenciacionAtras(void);
void diferenciacionAtras(double**,int);

void diferenciacionMixta(void);
void diferenciacionMixta(double**,int);
double f (double x)
{
    return pow(x,2)/2;
}


int main()
{
    cout<<"Metodos de  Diferenciacion\n";
    cout<<"Recuerda modificar \"nodes.txt\" que cuenta con los puntos a utilizar\nRecuerda que los puntos deben ser equidistantes!\n";

    //obtencion de nodos
    int n =1;
    FILE *file;

    file = fopen("nodes.txt","r");

    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    //obtener n
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            n++;
        }
    }
    cout<<"\nn="<<n<<endl;

    fclose(file);

    //generar matriz con nodos[x][y]

    double** nodes = (double**)malloc(n*sizeof(double*));
    for(int i=0;i<n;i++)
        nodes[i] = (double*)malloc(2*sizeof(double));
    

    // cargar matriz con datos del archivo
    file = fopen("nodes.txt","r");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            fscanf(file, "%lf", &nodes[i][j]);
        }
    }
    fclose(file);


    cout<<"Nodos cargados en sistema:\n";
    for(int i =0;i<n;i++)
            cout<<nodes[i][0]<<"\t"<<nodes[i][1]<<"\n";
    int op =0;

    do
    {
        cout<<"\nSelecciona una opcion:\n";
        cout<<"1.Operador de diferencias hacia adelante con f(x)\n";
        cout<<"2.Operador de diferencias hacia adelante usando nodos\n";
        cout<<"3.Operador de diferencias centradas con f(x)\n";
        cout<<"4.Operador de diferencias centradas usando nodos\n";
        cout<<"5.Operador de diferencias hacia atras con f(x)\n";
        cout<<"6.Operador de diferencias hacia atras usando nodos\n";
        cout<<"7.Derivada mixta(Extremos con operador hacia adelante y atras, puntos internos con centrada) usando f(x)\n";
        cout<<"8.Derivada mixta(Extremos con operador hacia adelante y atras, puntos internos con centrada) usando nodos\n";
        cout<<"0.Salir\n";
        cin>>op;
        switch (op)
        {
        case 0:
            break;
        case 1:
            diferenciacionAdelante();
            break;
        case 2:
            diferenciacionAdelante(nodes,n);
            break;
        case 3:
            diferenciacionCentrada();
            break;
        case 4:
            diferenciacionCentrada(nodes,n);
            break;
        case 5:
            diferenciacionAtras();
            break;
        case 6:
            diferenciacionAtras(nodes,n);
            break;
        case 7:
            diferenciacionMixta();
            break;
        case 8:
            diferenciacionMixta(nodes,n);
            break;
        default:
            cout<<"Opcion invalida!\n";
            break;
        }

    } while (op !=0);
    
    
    return 0;
}

void diferenciacionAdelante(void)
{
    double a, b, x;
    int intervals;
    double derivative = 0;
     cout<<"Ingrese el valor inicial\n";
    cin>>a;
    cout<<"Ingrese el valor final\n";
    cin>>b;
    cout<<"Ingrese la cantidad de subintervalos\n";
    cin>>intervals;
    double h = (b - a) / intervals;

    cout<<"Derivadas hacia adelante: \n";
    cout<<"Puedes cambiar a un metodo mas preciso descomentando el codigo!\n";

    // Abre el archivo "interpolados.txt" en modo de escritura.
    ofstream outputFile("derivadas.txt",ios::app);



    for (int i = 0; i < intervals; i++) {
        x = a + i * h;
        //forma vista en clase:
        derivative = (f(x+h)-f(x))/h;
        //forma mas precisa
        //derivative = (-f(x + 2 * h) + 4 * f(x + h) - 3 * f(x)) / (2 * h);

        // Escribe la cadena en el archivo.
        outputFile <<x<<"\t"<<derivative<<"\n";
        cout<<setprecision(PRECISION)<<x<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";
    }

    // Cierra el archivo.
    outputFile.close();
    cout<<"Recuerda que el operador de diferencias finitas hacia adelante no puede valuarse en el extremo xn\n";
    cout<<"Error de orden h\n";
    cout<<"Datos registrados en derivadas.txt\n";
}

void diferenciacionAdelante(double** nodes,int n)
{
    double a=nodes[0][0], b=nodes[n-1][0];
    int intervals=n-1;
    double derivative = 0;
    cout<<"Valor inicial: "<<a<<"\n";
    cout<<"Valor final: "<<b<<"\n";
    double h = (b - a) / intervals;

    cout<<"h = "<<h<<"\n";

    cout<<"Derivadas hacia adelante usando nodos cargados: \n";

    // Abre el archivo "interpolados.txt" en modo de escritura.
    ofstream outputFile("derivadas.txt",ios::app);



    for (int i = 0; i < intervals; i++) {
        //forma vista en clase:
        derivative = ((nodes[i + 1][1]-nodes[i][1])/h);
        // Escribe la cadena en el archivo.
        outputFile <<nodes[i][0]<<"\t"<<derivative<<"\n";
        cout<<setprecision(PRECISION)<<nodes[i][0]<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";
    }

    // Cierra el archivo.
    outputFile.close();
    cout<<"Recuerda que el operador de diferencias finitas hacia adelante no puede valuarse en el extremo xn\n";
    cout<<"Error de orden h\n";
    cout<<"Datos registrados en derivadas.txt\n";
}

void diferenciacionCentrada(void)
{
    double a, b, x;
    int intervals;
    double derivative = 0;
     cout<<"Ingrese el valor inicial\n";
    cin>>a;
    cout<<"Ingrese el valor final\n";
    cin>>b;
    cout<<"Ingrese la cantidad de subintervalos\n";
    cin>>intervals;
    double h = (b - a) / intervals;

    cout<<"Derivadas centradas: \n";
    cout<<"Puedes cambiar a un metodo mas preciso descomentando el codigo!\n";

    // Abre el archivo "interpolados.txt" en modo de escritura.
    ofstream outputFile("derivadas.txt",ios::app);



    for (int i = 1; i < intervals; i++) {
       x = a + i * h;
        //forma vista en clase:
        derivative = (f(x+h)-f(x-h))/(2*h);
        //Forma mas precisa
        //derivative = (-f(x + 2 * h) + 8 * f(x + h) - 8 * f(x - h) + f(x - 2 * h)) / (12 * h);

        // Escribe la cadena en el archivo.
        outputFile <<x<<"\t"<<derivative<<"\n";
        cout<<setprecision(PRECISION)<<x<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";
    }

    // Cierra el archivo.
    outputFile.close();
    cout<<"Recuerda que el operador de diferencias finitas centradas no puede valuarse en los extremo xn y x0\n";
    cout<<"Error de orden h²\n";
    cout<<"Datos registrados en derivadas.txt\n"; 
}

void diferenciacionCentrada(double** nodes,int n)
{
    double a=nodes[0][0], b=nodes[n-1][0];
    int intervals=n-1;
    double derivative = 0;
    cout<<"Valor inicial: "<<a<<"\n";
    cout<<"Valor final: "<<b<<"\n";
    double h = (b - a) / intervals;

    cout<<"h = "<<h<<"\n";
    
    cout<<"Derivadas centradas: \n";

    // Abre el archivo "derivadas.txt" en modo de escritura.
    ofstream outputFile("derivadas.txt",ios::app);



    for (int i = 1; i < intervals; i++) {
        //forma vista en clase:
        derivative = (nodes[i+1][1]-nodes[i-1][1])/(2*h);

        // Escribe la cadena en el archivo.
        outputFile <<nodes[i][0]<<"\t"<<derivative<<"\n";
        cout<<setprecision(PRECISION)<<nodes[i][0]<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";
    }

    // Cierra el archivo.
    outputFile.close();
    cout<<"Recuerda que el operador de diferencias finitas centradas no puede valuarse en los extremo xn y x0\n";
    cout<<"Error de orden h²\n";
    cout<<"Datos registrados en derivadas.txt\n"; 
}


void diferenciacionAtras(void)
{
    double a, b, x;
    int intervals;
    double derivative = 0;
     cout<<"Ingrese el valor inicial\n";
    cin>>a;
    cout<<"Ingrese el valor final\n";
    cin>>b;
    cout<<"Ingrese la cantidad de subintervalos\n";
    cin>>intervals;
    double h = (b - a) / intervals;

    cout<<"Derivadas hacia atras: \n";
    cout<<"Puedes cambiar a un metodo mas preciso descomentando el codigo!\n";

    // Abre el archivo "interpolados.txt" en modo de escritura.
    ofstream outputFile("derivadas.txt",ios::app);



    for (int i = intervals; i >0; i--) {
        x = a + i * h;
        //forma vista en clase:
       //forma vista en clase:
        derivative = (f(x)-f(x-h))/h;
        //Forma mas precisa
        //derivative = (3 * f(x) - 4 * f(x - h) + f(x - 2 * h)) / (2 * h);

        // Escribe la cadena en el archivo.
        outputFile <<x<<"\t"<<derivative<<"\n";
        cout<<setprecision(PRECISION)<<x<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";
    }

    // Cierra el archivo.
    outputFile.close();
    cout<<"Recuerda que el operador de diferencias finitas hacia atras no puede valuarse en el extremo x0\n";
    cout<<"Error de orden h\n";
    cout<<"Datos registrados en derivadas.txt\n";
}


void diferenciacionAtras(double** nodes,int n)
{
    double a=nodes[0][0], b=nodes[n-1][0];
    int intervals=n-1;
    double derivative = 0;
    cout<<"Valor inicial: "<<a<<"\n";
    cout<<"Valor final: "<<b<<"\n";
    double h = (b - a) / intervals;

    cout<<"h = "<<h<<"\n";

    cout<<"Derivadas hacia atras usando nodos cargados: \n";

    // Abre el archivo "interpolados.txt" en modo de escritura.
    ofstream outputFile("derivadas.txt",ios::app);



    for (int i = intervals;  i>0; i--) {
        //forma vista en clase:
        derivative = ((nodes[i][1]-nodes[i-1][1])/h);
        // Escribe la cadena en el archivo.
        outputFile <<nodes[i][0]<<"\t"<<derivative<<"\n";
        cout<<setprecision(PRECISION)<<nodes[i][0]<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";
    }

    // Cierra el archivo.
    outputFile.close();
    cout<<"Recuerda que el operador de diferencias finitas hacia atras no puede valuarse en el extremo x0\n";
    cout<<"Error de orden h\n";
    cout<<"Datos registrados en derivadas.txt\n";
}


void diferenciacionMixta(void)
{
    double a, b, x;
    int intervals;
    double derivative = 0;
     cout<<"Ingrese el valor inicial\n";
    cin>>a;
    cout<<"Ingrese el valor final\n";
    cin>>b;
    cout<<"Ingrese la cantidad de subintervalos\n";
    cin>>intervals;
    double h = (b - a) / intervals;

    cout<<"Derivadas usando Derivacion hacia adelante y hacia atras en los extremos, y centrada en los puntos internos: \n";
    cout<<"Puedes cambiar a un metodo mas preciso descomentando el codigo!\n";

    // Abre el archivo "interpolados.txt" en modo de escritura.
    ofstream outputFile("derivadas.txt",ios::app);


    //x0
     //forma vista en clase:
    derivative = (f(a+h)-f(a))/h;
    //forma mas precisa
    //derivative = (-f(x + 2 * h) + 4 * f(x + h) - 3 * f(x)) / (2 * h);
    outputFile <<a<<"\t"<<derivative<<"\n";
    cout<<setprecision(PRECISION)<<a<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";

    //puntos internos

    for (int i = 1; i < intervals; i++) {
       x = a + i * h;
        //forma vista en clase:
        derivative = (f(x+h)-f(x-h))/(2*h);
        //Forma mas precisa
        //derivative = (-f(x + 2 * h) + 8 * f(x + h) - 8 * f(x - h) + f(x - 2 * h)) / (12 * h);

        // Escribe la cadena en el archivo.
        outputFile <<x<<"\t"<<derivative<<"\n";
        cout<<setprecision(PRECISION)<<x<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";
    }


    //xn
    //forma vista en clase:
    derivative = (f(b)-f(b-h))/h;
    //Forma mas precisa
    //derivative = (3 * f(x) - 4 * f(x - h) + f(x - 2 * h)) / (2 * h);

    // Escribe la cadena en el archivo.
    outputFile <<b<<"\t"<<derivative<<"\n";
    cout<<setprecision(PRECISION)<<b<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";


    // Cierra el archivo.
    outputFile.close();
    cout<<"Datos registrados en derivadas.txt\n";
}

void diferenciacionMixta(double** nodes,int n)
{
    double a=nodes[0][0], b=nodes[n-1][0];
    int intervals=n-1;
    double derivative = 0;
    cout<<"Valor inicial: "<<a<<"\n";
    cout<<"Valor final: "<<b<<"\n";
    double h = (b - a) / intervals;

    cout<<"h = "<<h<<"\n";

    cout<<"Derivadas usando Derivacion hacia adelante y hacia atras en los extremos, y centrada en los puntos internos con nodos: \n";
    cout<<"Puedes cambiar a un metodo mas preciso descomentando el codigo!\n";

    // Abre el archivo "derivadas.txt" en modo de escritura.
    ofstream outputFile("derivadas.txt",ios::app);


    //x0
     //forma vista en clase:
    derivative = ((nodes[1][1]-nodes[0][1])/h);
    outputFile <<a<<"\t"<<derivative<<"\n";
    cout<<setprecision(PRECISION)<<a<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";

    //puntos internos
    for (int i = 1; i < intervals; i++) {
        //forma vista en clase:
        derivative = (nodes[i+1][1]-nodes[i-1][1])/(2*h);

        // Escribe la cadena en el archivo.
        outputFile <<nodes[i][0]<<"\t"<<derivative<<"\n";
        cout<<setprecision(PRECISION)<<nodes[i][0]<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";
    }
    


    //xn
    //forma vista en clase:
    derivative = ((nodes[n-1][1]-nodes[n-2][1])/h);
    //Forma mas precisa
    //derivative = (3 * f(x) - 4 * f(x - h) + f(x - 2 * h)) / (2 * h);

    // Escribe la cadena en el archivo.
    outputFile <<b<<"\t"<<derivative<<"\n";
    cout<<setprecision(PRECISION)<<b<<"\t"<<setprecision(PRECISION)<<derivative<<"\n";


    // Cierra el archivo.
    outputFile.close();
    cout<<"Datos registrados en derivadas.txt\n";
}