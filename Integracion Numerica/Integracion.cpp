/**
 * Integracion a traves de diferentes metodos numericos
 * @author Benjamin Vargas
 * @version 3.0
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
void cuadraturaGauss();
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
        cout<<"5.Cuadratura Gauss con f(x)\n";
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
        case 5:
            cuadraturaGauss();
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

void cuadraturaGauss()
{
    int points;
    double integral, a, b;


    cout<<"Cuadratura de Gauss utilizando f(x) definida\n";

    //Factores de ponderacion y argumentos de funcion
    double two[] = {1, 1, -0.577350269, 0.577350269};
    
    double three[] = {0.5555556, 0.8888889, 0.5555556, -0.774596669, 0.0, 0.774596669};
    
    double four[] = {0.3478548, 0.6521452, 0.6521452, 0.3478548, -0.861136312, -0.339981044, 0.339981044, 0.861136312};
    
    double five[] = {0.2369269, 0.4786287, 0.5688889, 0.4786287, 0.2369269, -0.906179846, -0.538469310, 0.0,
                     0.538469310, 0.906179846};
    
    double six[] = {0.1713245, 0.3607616, 0.4679139, 0.4679139, 0.3607616, 0.1713245, -0.932469514, -0.661209386,
                    -0.238619186, 0.238619186, 0.661209386, 0.932469514};



    cout<<"Ingrese el valor del limite de integracion inferior\n";
    cin>>a;
    cout<<"Ingrese el valor del limite de integracion superior\n";
    cin>>b;

    do {
        cout<<"Ingrese la cantidad de puntos (recuerde que dicho valor esta entre 2 y 6). Ingrese 0 para volver al menu\n";
        cin>>points;
        cout<<"\n\n";
        switch (points) {
            case 0:
                break;
            case 2:
                integral = ((b - a) / 2) *
                           (two[0] * f(((b - a) * two[2] + b + a) / 2) + two[1] * f(((b - a) * two[3] + b + a) / 2));
                cout<<"El valor de la integral es: "<<integral<<"\n";
                cout<<"Ajusta de manera exacta hasta grado 3";
                break;
            case 3:
                integral = ((b - a) / 2) *
                           (three[0] * f(((b - a) * three[3] + b + a) / 2) +
                            three[1] * f(((b - a) * three[4] + b + a) / 2) +
                            three[2] * f(((b - a) * three[5] + b + a) / 2));
                
                cout<<"El valor de la integral es: "<<integral<<"\n";
                cout<<"Ajusta de manera exacta hasta grado 5";
                break;
            case 4:
                integral = ((b - a) / 2) *
                           (four[0] * f(((b - a) * four[4] + b + a) / 2) +
                            four[1] * f(((b - a) * four[5] + b + a) / 2) +
                            four[2] * f(((b - a) * four[6] + b + a) / 2) +
                            four[3] * f(((b - a) * four[7] + b + a) / 2));
                cout<<"El valor de la integral es: "<<integral<<"\n";
                cout<<"Ajusta de manera exacta hasta grado 7";
                break;
            case 5:
                integral = ((b - a) / 2) *
                           (five[0] * f(((b - a) * five[5] + b + a) / 2) +
                            five[1] * f(((b - a) * five[6] + b + a) / 2) +
                            five[2] * f(((b - a) * five[7] + b + a) / 2) +
                            five[3] * f(((b - a) * five[8] + b + a) / 2) +
                            five[4] * f(((b - a) * five[9] + b + a) / 2));
                cout<<"El valor de la integral es: "<<integral<<"\n";
                cout<<"Ajusta de manera exacta hasta grado 9";
                break;
            case 6:
                integral = ((b - a) / 2) *
                           (six[0] * f(((b - a) * six[6] + b + a) / 2) +
                            six[1] * f(((b - a) * six[7] + b + a) / 2) +
                            six[2] * f(((b - a) * six[8] + b + a) / 2) +
                            six[3] * f(((b - a) * six[9] + b + a) / 2) +
                            six[4] * f(((b - a) * six[10] + b + a) / 2) +
                            six[5] * f(((b - a) * six[11] + b + a) / 2));
                cout<<"El valor de la integral es: "<<integral<<"\n";
                cout<<"Ajusta de manera exacta hasta grado 11";
                break;
            default:
                printf("La opcion ingresada no es valida. Porfavor ingrese una opcion valida\n");
                break;
        }
    } while (points != 0);
}