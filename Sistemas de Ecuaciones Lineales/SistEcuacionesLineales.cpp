/**
 * Solucion de sistemas de ecuaciones lineales a traves de diferentes metodos numericos
 * @author Benjamin Vargas
 * @version 3.2
*/
#define PRECISION 10 //cantidad de decimales a imprimir
#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;

double* Gauss(double**,double*,int);
void printmatrix(double**,int);
double* jacobi(double**,double*,int);
double* gaussSeidel(double**,double*,int);
int main()
{
    cout<<"\nMetodos de solucion de sistemas de ecuaciones lineales\n";
    cout<<"Recuerda modificar el documento \"Matrix.txt\" que contiene la matriz  cuadrada del sistema\n";

    //recuperacion de datos y creacion de matriz A y vector b
    int n =1;
    FILE *file;

    file = fopen("matrix.txt","r");

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

    //crear matrix A y vector b

    double** matrixA = (double**)malloc(n*sizeof(double*));
    for(int i=0;i<n;i++)
        matrixA[i] = (double*)malloc(n*sizeof(double));

    double* vectorb = (double*)malloc(n*sizeof(double));


    //obtener elementos de matrizA y vectorb

    file = fopen("matrix.txt","r");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%lf", &matrixA[i][j]);
        }
        fscanf(file, "%lf", &vectorb[i]);
    }
    fclose(file);

    //matrices y vectores obtenidos:
    cout<<"Matriz obtenida:\n";

    printmatrix(matrixA,n);
    cout<<"Vector B obtenido:\n";
    for(int i=0;i<n;i++)
        cout<<vectorb[i]<<"\t";

    


    //MENU
    int op =0;
    do
    {
        cout<<"\n\nSelecciona una opcion:\n";
        cout<<"1.Eliminacion Gaussiana\n";
        cout<<"2.Jacobi\n";
        cout<<"3.Gauss-Seidel\n";
        cout<<"0.Salir\n";
        cin>>op;
        switch (op)
        {
        case 0:
            break;
        case 1:
            Gauss(matrixA,vectorb,n);
            cout<<"ADVERTENCIA: el metodo eliminacion gaussiana modifica la matrizA(Triangulacion), por ello se recomienda reiniciar sistema";
            break;
        case 2:
            jacobi(matrixA,vectorb,n);
            break;
        case 3:
            gaussSeidel(matrixA,vectorb,n);
            break;
        default:
            cout<<"Opcion invalida!\n";
            break;
        }

    } while (op !=0);
    
    //liberacion de memoria
    for(int i=0;i<n;i++)
        free(matrixA[i]);
    free(matrixA);
    free(vectorb);

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
    cout<<"\nMatriz triangulada\n";
    printmatrix(matrixA,n);

    cout<<"Vector b despues de triangulacion:\n";
    for(int i=0;i<n;i++)
        cout<<vectorb[i]<<"\t";

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
            cout<<" x"<<ii+1<<" = "<<setprecision(PRECISION)<<x[ii]<<"\n";
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

double* jacobi(double** matrixA,double* vectorb,int n )
{
    //verificar A diagonalmente dominante
    for(int i=0;i<n;i++)
    {
        double suma = 0;
        for(int j=0;j<n;j++)
        {
            if(j!=i)
            {
                suma += fabs(matrixA[j][i]);
            }
        }
        if(fabs(matrixA[i][i]) < suma)
            cout<<"\nADVERTENCIA: Matriz no es diagonalmente dominante\n";
        if(matrixA[i][i]==0)
        {
            cout<<"\nCero en la diagonal";
            exit(1);
        }
    }

    //JACOBI
    double *xn = (double*)malloc(n*sizeof(double));

    double *xv = (double*)malloc(n*sizeof(double));

    //definimos vector x0=(0,0,...,0)

    for(int i =0;i<n;i++)
        xv[i]=0;

    double e=1,tol=0;
    cout<<"Ingresa una tolerancia: ";
    cin>>tol; 
    int iter=1;
    do
    {
        for(int i = 0; i<n;i++)
        {
            double suma = 0;
            for(int j = 0; j<n;j++)
                if(j!=i)
                    suma += matrixA[i][j] * xv[j];
            xn[i]=(vectorb[i]-suma)/matrixA[i][i];
        }

        //calculo del error(Absoluto)
        double suma =0;
        for(int i=0;i<n;i++)
            suma += pow(xn[i]-xv[i],2);
        e=sqrt(suma);

        //actualizar vector
        for(int i=0;i<n;i++)
            xv[i]=xn[i];
        iter++;
    } while (e>tol && iter<1000);
    
    //impresion
    cout<<"Resultados:\n";
    for(int i=0;i<n;i++)
        cout<<"X"<<i+1<<" = "<<setprecision(PRECISION)<<xn[i]<<"\n";
    cout<<"Error abs estimado: "<<setprecision(PRECISION)<<e<<"\n";
    cout<<"Iteraciones: "<<iter<<"\n\n";

    return xn;

}
double* gaussSeidel(double** matrixA,double* vectorb,int n)
{
    //verificar A diagonalmente dominante
    for(int i=0;i<n;i++)
    {
        double suma = 0;
        for(int j=0;j<n;j++)
        {
            if(j!=i)
            {
                suma += fabs(matrixA[j][i]);
            }
        }
        if(fabs(matrixA[i][i]) < suma)
            cout<<"\nADVERTENCIA: Matriz no es diagonalmente dominante\n";
        if(matrixA[i][i]==0)
        {
            cout<<"\nCero en la diagonal";
            exit(1);
        }
    }

    double *xn = (double*)malloc(n*sizeof(double));

    double *xv = (double*)malloc(n*sizeof(double));

    //definimos vector x0=(0,0,...,0)

    for(int i =0;i<n;i++)
        xv[i]=0;

    double e=1,tol=0;
    cout<<"Ingresa una tolerancia: ";
    cin>>tol; 
    int iter=1;
    do
    {
        for(int i = 0; i<n;i++)
        {
            double suma = 0;
            if(i == 0)
            {
                for(int j = 1; j<n;j++)
                    suma += matrixA[i][j] * xv[j];
                xn[i]=(vectorb[i]-suma)/matrixA[i][i];

            }
            else
            {
                for(int j=0;j<i;j++)
                    suma+=matrixA[i][j]*xn[j];
                for(int j=i+1;j<n;j++)
                    suma+=matrixA[i][j]*xv[j];
                xn[i]=(vectorb[i]-suma)/matrixA[i][i];

            }
        }

        //calculo del error(Absoluto)
        double suma =0;
        for(int i=0;i<n;i++)
            suma += pow(xn[i]-xv[i],2);
        e=sqrt(suma);

        //actualizar vector
        for(int i=0;i<n;i++)
            xv[i]=xn[i];
        iter++;
    } while (e>tol && iter<10000);
     //impresion
    cout<<"Resultados:\n";
    for(int i=0;i<n;i++)
        cout<<"X"<<i+1<<" = "<<setprecision(PRECISION)<<xn[i]<<"\n";
    cout<<"Error abs estimado: "<<setprecision(PRECISION)<<e<<"\n";
    cout<<"Iteraciones: "<<iter<<"\n\n";
    return xn;
}