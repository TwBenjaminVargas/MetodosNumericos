/**
 * Regresion polinomial
 * @author Benjamin Vargas
 * @version 1.1
*/
#define PRESICION 3 //cantidad de decimales a imprimir
#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;

double* Gauss(double**,double*,int);
void printmatrix(double**,int);


int main()
{
    cout<<"Metodo de regresion Polinomial\n";
    cout<<"Recuerda modificar \"nodes.txt\" que cuenta con los puntos a utilizar\n";

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
    int p =0;

    do
    {
        cout<<"\nIngresa el grado del polinomio:\n";
        cin>>p;
        if(p<=0)
            cout<<"Grado debe ser mayor a cero!\n";
        if(n<p)
            cout<<"Datos insuficientes para el grado del polinomio";

    } while (p <=0 && p>n);

    p++;

    //armado de matriz y vector

    double** matrixA = (double**)malloc(p*sizeof(double*));
    for(int i=0;i<p;i++)
        matrixA[i] = (double*)malloc(p*sizeof(double));

    double* vectorb = (double*)malloc(p*sizeof(double));

    //carga de valores
    for(int l=0;l<p;l++)//recorrer filas cuidado condicion
    {
        double sumaxy=0;//para b
        for(int i =0;i<n;i++)
            sumaxy+=pow(nodes[i][0],l)*nodes[i][1];
        vectorb[l]=sumaxy;
        for(int m=0;m<p;m++) //recorrer columnas
        {
            double sumax=0;//para A
            for(int i=0;i<n;i++)
                sumax+=pow(nodes[i][0],l+m);
            matrixA[l][m]=sumax;
        }
    }

    //obtener soluciones
    double *a=Gauss(matrixA,vectorb,p);


    //impresion de f(x):
    cout<<"\nf(x) que ajusta los datos:\n\n";
    cout<<"f(x)=";
    for(int ii=0;ii<p;ii++)
    {
        if(ii==0)
        {
            cout<<"("<<setprecision(PRESICION)<<a[ii]<<")+";
        }
        else if(ii<p-1 && ii>0)
        {
            cout<<"("<<setprecision(PRESICION)<<a[ii]<<")*(x)^"<<ii<<"+";

        }
        else if(ii==p-1)
        {
            cout<<"("<<setprecision(PRESICION)<<a[ii]<<")*(x)^"<<ii;
        }
    }
    cout<<"\n";
    

    //calculo de coeficiente de correlacion
    
    //ymed
    double ymed=0;
    for(int i=0;i<n;i++)
        ymed+=nodes[i][1];
    ymed =ymed/n;

    //st^2
    double st2=0;
    for(int i=0;i<n;i++)
        st2 += pow(ymed-nodes[i][1],2);

    //sr2
    double sr2=0;
    for(int i=0;i<n;i++)
    {
        double f=0;
        for(int j =0;j<p;j++)
            f+=a[j]*pow(nodes[i][0],j);
        sr2+=pow(nodes[i][1]-f,2);
    }

    double r = sqrt((st2-sr2)/st2);
    cout<<"Coeficiente de correlacion r="<<setprecision(PRESICION)<<r<<"\n";
    return 0;
}


/**
 * Metodo que implementa Eliminacion Gaussiana para la solucion del sistema
 * requiere metodo printMatrix();
 * @param matrixA matriz de coeficientes
 * @param vectorb vector de soluciones
 * @param n numero de ecuaciones
*/
double* Gauss(double** matrixA, double* vectorb,int n)
{
    //1. TRIANGULACION
    for(int j=0; j<(n-1);j++)
    {
        //PIVOTEO
        int p=j;
        double swap;
        if(fabs(matrixA[j][j]) < 10e-5)
        {
            for(int i=j+1;i<n;i++)
                if(fabs(matrixA[i][j])>fabs(matrixA[j][j]))
                    p=i;
            for(int m=0;m<n;m++)
            {
                swap = matrixA[p][m];
                matrixA[p][m] = matrixA[j][m];
                matrixA[j][m] = swap;
            }
            swap = vectorb[p];
            vectorb[p] = vectorb[j];
            vectorb[j] = swap;
        }
        //FIN PIVOTEO

        for(int i = j+1;i<n;i++)
        {
            if(matrixA[j][j] == 0)
                cout<<"\nADVERTENCIA: 0 en denominador de factor\n";
            double factor= (-matrixA[i][j]/matrixA[j][j]);
            for(int k=j;k<n;k++)
            {
                matrixA[i][k]= matrixA[i][k] + factor * matrixA[j][k];
            }
            vectorb[i]=vectorb[i] + factor*vectorb[j];
        }
    }

    //printear la matriz para control
    //cout<<"\nMatriz triangulada\n";
    //printmatrix(matrixA,n);

    /*cout<<"Vector b despues de triangulacion:\n";
    for(int i=0;i<n;i++)
        cout<<vectorb[i]<<"\t";*/

    //DETERMINANTE
    double det=1;
    for(int i =0;i<n;i++)
        det *= matrixA[i][i];

    if(det == 0)
    {
        cout<<"\nMatriz singular\n";
        exit(1);
    }

    //RETROSUSTITUCION
    //vector de soluciones
    double *x = (double*)malloc(n*sizeof(double));
    
    x[n-1]= vectorb[n-1]/matrixA[n-1][n-1];
    for(int i=n-2;i>-1;i--)
        {
            double suma = vectorb[i];
            for(int k = i+1;k<n;k++)
            {
                suma = suma - matrixA[i][k]*x[k];
            }
            x[i] = suma/matrixA[i][i];
        }

        cout<<"\n\nResultados: \n";
        for(int ii=0;ii<n;ii++)
        {
            cout<<" a"<<ii<<" = "<<setprecision(PRESICION)<<x[ii]<<"\n";
        }
        return x;
}


/**
 * Metodo de impresion matrices cuadradas nxn
 * @param matrix matriz
 * @param n numero de filas/columnas
*/
void printmatrix(double **matrix,int n)
{
    for(int ii=0;ii<n;ii++)
    {
        for(int jj=0;jj<n;jj++)
            cout<<matrix[ii][jj]<<"\t";
        cout<<"\n";
    }
}