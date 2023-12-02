/**
 * Integracion a traves de diferentes metodos numericos
 * @author Benjamin Vargas
 * @version 2.0
*/
#define PRECISION 6 //cantidad de decimales a imprimir
#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;

double f(double);
void trapecio(double**, int);
void trapecio();
void simpson();
void simpson(double**, int);

double f (double x)
{
    return pow(x,2)/2;
}


int main()
{
    cout<<"Metodos de  Integracion\n";
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
        cout<<"1.Trapecio compuesto f(x)\n";
        cout<<"2.Trapecio compuesto nodes\n";
        cout<<"3.Simpson compuesto f(x)\n";
        cout<<"4.Simpson compuesto nodes\n";
        cout<<"0.Salir\n";
        cin>>op;
        switch (op)
        {
        case 0:
            break;
        case 1:
            trapecio();
            break;
        case 2:
            trapecio(nodes,n);
            break;
        case 3:
            simpson();
            break;
        case 4:
            simpson(nodes,n);
            break;
        default:
            cout<<"Opcion invalida!\n";
            break;
        }

    } while (op !=0);
    
    
    return 0;
}

void trapecio(double** nodes, int n) {
    cout<<"\nTrapecio compuesto utilizando nodos\n";
    cout<<"ADVERTENCIA: SE INTEGRA TODO EL INTERVALO DADO POR LOS NODOS x0 Y Xn\n";
    double a, b;
    int intervals = n - 1;

    a = nodes[0][0];
    b = nodes[n-1][0];

    cout<<"Limite inferior: a = "<<a<<"\n"<<"Limite superior: b = "<<b<<"\n";

    double h = (b - a) / intervals;
    cout<<"valor de h: "<<h<<"\n";

    //Metodo de trapecio compuesto original

    //double sum = f(a) + f(b);
    double sum = nodes[0][1] + nodes[n-1][1];
    for (int i = 1; i < intervals; ++i) {
        //sum = sum + 2 * f(a + i * h);
        sum += 2 * nodes[i][1];
    }
    sum *= (h / 2);


   cout<<"\nValor de la integral: "<<setprecision(PRECISION)<<sum<<"\n";

}

void trapecio() {

    cout<<"trapecio compuesto utilizando f(x) definida\n";
    double a, b;
    int intervals;
    cout<<"Ingrese el limite de integracion inferior\n";
    cin>>a;
    cout<<"Ingrese el limite de integracion superior\n";
    cin>>b;
    cout<<"Ingrese la cantidad de intervalos\n";
    cin>>intervals;

    double h = (b - a) / intervals;

    double sum = f(a) + f(b);
    for (int i = 1; i < intervals; ++i) {
        sum += 2 * f(a + i * h);
    }
    sum = sum * (h / 2);

    cout<<"Valor de la integral: "<<setprecision(PRECISION)<<sum<<"\n";
    

}

void simpson() {

    cout<<"Simpson 1/3 compuesto utilizando f(x) definida\n";
    double a, b;
    int intervals;
    cout<<"\nIngrese el limite de integracion inferior\n";
    cin>>a;
    cout<<"Ingrese el limite de integracion superior\n";
    cin>>b;
    cout<<"Ingrese la cantidad de intervalos\n";
    cin>>intervals;
    

    if (intervals % 2 != 0) 
    {
        cout<<"El numero de intervalos debe ser par\n";
    }
    else
    {
        double h = (b - a) / intervals;
        double sum = f(a) + f(b);

        for (int i = 1; i < (intervals / 2); ++i) {
            double x = a + 2 * i * h;
            sum = sum + 2 * f(x) + 4 * f(x - h);
        }

        sum = (h / 3) * (sum + 4 * f(b - h));

        cout<<"El valor de la integral es de:"<<setprecision(PRECISION)<<sum<<"\n";

    }

}



void simpson(double** nodes, int n) {

     cout<<"\nSimpson 1/3 compuesto utilizando nodos\n";
    cout<<"ADVERTENCIA: SE INTEGRA TODO EL INTERVALO DADO POR LOS NODOS x0 Y Xn\n";
    double a, b;
    int intervals = n - 1;

    a = nodes[0][0];
    b = nodes[n-1][0];

    cout<<"Limite inferior: a = "<<a<<"\n"<<"Limite superior: b = "<<b<<"\n";

    double h = (b - a) / intervals;
    cout<<"valor de h: "<<h<<"\n";

    if (intervals % 2 != 0)
    {
        cout<<"El numero de intervalos debe ser par\n";
    }
    else
    {
        //double sum = f(a) + f(b);
        double sum = nodes[0][1] + nodes[n - 1][1];

        for (int i = 1; i < (intervals / 2); ++i) {
            //x = a + 2*i*h;
            //sum = sum + 2 * f(x) + 4 * f(x - h);
            sum = sum + 2 * nodes[2 * i][1] + 4 * nodes[2 * i - 1][1];
        }

        //sum = (h / 3) * (sum + 4 * f(b - h));
        sum = (h / 3) * (sum + 4 * nodes[n - 2][1]);

        cout<<"El valor de la integral es de:"<<setprecision(PRECISION)<<sum<<"\n";

    }

}