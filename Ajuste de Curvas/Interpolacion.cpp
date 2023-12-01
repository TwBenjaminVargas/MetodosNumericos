/**
 * Interpolacion a traves de diferentes metodos numericos
 * @author Benjamin Vargas
 * @version 2.0
*/
#define PRECISION 6 //cantidad de decimales a imprimir
#include<iostream>
#include<cmath>
#include <iomanip>
#include <fstream>
using namespace std;

double* Gauss(double**,double*,int);
double* GaussmodSpline(double**,double*,int);
void printmatrix(double**,int);
void LaGrange(double**,int);
void splineCubica(double**,int);

int main()
{
    cout<<"Metodos de  Interpolacion\n";
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
    int op =0;

    do
    {
        cout<<"\nSelecciona una opcion:\n";
        cout<<"1.La Grange\n";
        cout<<"2.Spline Cubica\n";
        cout<<"0.Salir\n";
        cin>>op;
        switch (op)
        {
        case 0:
            break;
        case 1:
            LaGrange(nodes,n);
            break;
        case 2:
            splineCubica(nodes,n);
            break;
        default:
            cout<<"Opcion invalida!\n";
            break;
        }

    } while (op !=0);
    
    
    return 0;
}

void LaGrange(double **nodes, int n)
{

    double xi=0,suma=0;
    cout<<"\n\nIngresa valor a interpolar: ";
    cin>>xi;
    //calculo de P(x)
    for(int k=0;k<n;k++)
    {
        double producto=1;
        //calculo Cnk
        for(int j=0;j<n;j++)
            if(j != k)
                producto *= (xi - nodes[j][0])/(nodes[k][0]-nodes[j][0]);
        suma += (nodes[k][1]*producto);
    }


    // Abre el archivo "interpolados.txt" en modo de escritura.
    ofstream outputFile("interpolados.txt",ios::app);

    // Escribe la cadena en el archivo.
    outputFile <<xi<<"\t"<<suma<<"\n";

    // Cierra el archivo.
    outputFile.close();   

    //obtener polinomio interpolador:

    //crear matrix A y vector b

    double** matrixA = (double**)malloc(n*sizeof(double*));
    for(int i=0;i<n;i++)
        matrixA[i] = (double*)malloc(n*sizeof(double));

    double* vectorb = (double*)malloc(n*sizeof(double));

    //cargar valores
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            matrixA[i][j]=pow(nodes[i][0],j);
        }
        vectorb[i]=nodes[i][1];
    }

    double* a=Gauss(matrixA,vectorb,n);

    cout<<"\nValor interpolado para x="<<xi<<" es y="<<suma<<"\n\n";
    
    //impresion de polinomio:
    cout<<"\nPolinomio interpolador:\n\n";
    cout<<"P(x)=";
    for(int ii=0;ii<n;ii++)
    {
        if(ii==0)
        {
            cout<<"("<<setprecision(PRECISION)<<a[ii]<<")+";
        }
        else if(ii<n-1 && ii>0)
        {
            cout<<"("<<setprecision(PRECISION)<<a[ii]<<")*(x)^"<<ii<<"+";

        }
        else if(ii==n-1)
        {
            cout<<"("<<setprecision(PRECISION)<<a[ii]<<")*(x)^"<<ii;
        }
    }
    cout<<"\n";

    //valuacion del polinomio
    cout<<"\nPolinomio valuado en xi="<<xi<<"\n\n";
    suma =0;
    for(int i =0;i<n;i++)
        suma+=a[i]*pow(xi,i);

    cout<<"P("<<xi<<")="<<suma<<"\n";
    cout<<"Valores cargados a \"interpolados.txt\" podras graficar si lo deseas\n";

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
        double swap=0;
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
            cout<<" a"<<ii<<" = "<<setprecision(PRECISION)<<x[ii]<<"\n";
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


void splineCubica(double** nodes,int n)
{
    
    //determinacion de intervalo
    int inter=-1;
    double xi=0;
    do
    {
        cout<<"\n\nIngresa valor a interpolar: ";
        cin>>xi;
        for (int i=0;i<n-1;i++){
            if(xi>nodes[i][0]&&xi<nodes[i+1][0]){
                inter=i;
            }
        }

        if(inter < 0)
            cout<<"Valor no encontrado en ningun sub intervalo o es un nodo.\nSi es el segundo caso, se podra interpolar con cualquiera de sus funciones limitrofes";
        else
            cout<<"Valor localizado en el sub-intervalo = "<<inter<<"\n";
    }while (inter < 0);

    //crear matrix A y vector b
    double** matrixA = (double**)malloc(4*(n-1)*sizeof(double*));
    for(int i=0;i<4*(n-1);i++)
        matrixA[i] = (double*)malloc(4*(n-1)*sizeof(double));

    double* vectorb = (double*)malloc(4*(n-1)*sizeof(double));


    //primeras 2n filas, rellenado de matrices f0(x0)=f1(x0)
    //z[3k]=ak,z[3k+1]=bk,z[3k+2]=ck
        for(int k=0;k<((n-1));k++){
           for(int j=0;j<=3;j++){
            matrixA[2*k][4*k+j]=pow(nodes[k][0],3-j);
            matrixA[2*k+1][4*k+j]=pow(nodes[k+1][0],3-j);
           }
           vectorb[2*k]=nodes[k][1];
           vectorb[2*k+1]=nodes[k+1][1];
        }

    int k=0;
    //Derivadas primeras(n-1 puntos interiores)
    for(int i=2*(n-1);i<=3*(n-1)-2;i++){
       // for(int k=0;k<=(n-1)-2;k++){
            for(int j=0;j<=2;j++){
                matrixA[i][4*k+j]=(3-j)*pow(nodes[k+1][0],2-j);
                matrixA[i][4*(k+1)+j]=-(3-j)*pow(nodes[k+1][0],2-j);
            }
       // }
       k++;
    		if(k > ((n-1)-2)){
    			break;
    		}
        vectorb[i]=0;
    }
    //Derivadas seugndas (n-1 puntos)
    k = 0;
    for(int i =3*(n-1)-1;i<=4*(n-1)-3;i++){
        //for(int k=0;k<=(n-1)-2;k++){
            matrixA[i][4*k]=6*nodes[k+1][0];
            matrixA[i][4*k+1]=2;
            matrixA[i][4*(k+1)]=-6*nodes[k+1][0];
            matrixA[i][4*(k+1)+1]=-2;
        //}
        k++;
    		if(k > ((n-1)-2)){
    			break;
    		}
        vectorb[i]=0;
    }
    matrixA[4*(n-1)-2][0]=3*nodes[0][0];
    matrixA[4*(n-1)-2][1]=1;
    matrixA[4*(n-1)-1][4*(n-1)-4]=3*nodes[(n-1)][0];
    matrixA[4*(n-1)-1][4*(n-1)-3]=1;
    vectorb[4*(n-1)-2]=0;
    vectorb[4*(n-1)-1]=0;

    
    double *a = GaussmodSpline(matrixA,vectorb,4*(n-1));
    
    //impresion de funcion
    cout<<"\nfuncion a utilizar para interpolar valor(Sub intervalo "<<inter<<"):\n";
    cout<<"\nf(x)=("<<a[4*inter]<<")*(x)³+("<<a[4*inter+1]<<")*(x)²+("<<a[4*inter+2]<<")*(x)+("<<a[4*inter+3]<<")\n";




    //valuamos la funcion:

    double resultado=a[4*inter]*pow(xi,3)+a[4*inter+1]*pow(xi,2)+a[4*inter+2]*xi+a[4*inter+3];

    cout<<"\nValor interpolado para x = "<<xi<<" y = "<<resultado<<"\n\n";
    
    //registro de valores

    // Abre el archivo "interpolados.txt" en modo de escritura.
    ofstream outputFile("interpolados.txt",ios::app);

    // Escribe la cadena en el archivo.
    outputFile <<xi<<"\t"<<resultado<<"\n";

    // Cierra el archivo.
    outputFile.close();  
    cout<<"Valores cargados a \"interpolados.txt\" podras graficar si lo deseas\n";
}


double* GaussmodSpline(double** matrixA,double*vectorb,int n)
{
    //1. TRIANGULACION
    for(int j=0; j<(n-1);j++)
    {
        //PIVOTEO
        int p=j;
        double swap=0;
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
        for(int ii=0;ii<n/4;ii++)
        {
            cout<<" a"<<ii<<" = "<<setprecision(PRECISION)<<x[4*ii]<<"\n";
            cout<<" b"<<ii<<" = "<<setprecision(PRECISION)<<x[4*ii+1]<<"\n";
            cout<<" c"<<ii<<" = "<<setprecision(PRECISION)<<x[4*ii+2]<<"\n";
            cout<<" d"<<ii<<" = "<<setprecision(PRECISION)<<x[4*ii+3]<<"\n\n";
        }
        return x;
}