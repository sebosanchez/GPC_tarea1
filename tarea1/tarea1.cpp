//
//  tarea1.cpp
//  tarea1
//
//  Created by Sebastian Sanchez Alcala on 31/08/17.
//  Copyright © 2017 Sebastian Sanchez Alcala. All rights reserved.
//

// planos.cpp : Defines the entry point for the console application.
//

/* En este cÛdigo usted debe agregar las sentencias
 necesarias ( funciones, operadores y script de pruebas )
 para:
 // EJER 1) operador de entrada del clsVector3D
 // EJER 2) operador Producto Cruz de dos clsVector3D
 // EJER 3) Construir el plano a partir de los tres puntos v1, v2 y v3.
 // EJER 4) ImpresiÛn del plano A * x + B * y + C * z + D = 0.
 // EJER 5) Lectura del plano como A * x + B * y + c * z + D = 0.
 // EJER 6) Obtener el punto que resulta de la intersecciÛn de tres planos
 
 En los casos de los operadores de lectura agregue lectura de input streams
 definidos en base a cadenas de caracteres, de tal forma que pueda probar
 de manera r·pida sus operadores.
 
 */
#include <iostream>
#include <fstream>
#include <strstream>
using namespace std;
// ============================================
class clsVector3D
{
private:
    double dbl_x, dbl_y, dbl_z ;
public:
    clsVector3D()
    {
        dbl_x = dbl_y = dbl_z = 0.0;
    }
    void x( double unX ) { dbl_x = unX; }
    double x() { return dbl_x; }
    
    void y( double unY ) { dbl_y = unY; }
    double y() { return dbl_y; }
    
    void z( double unZ ) { dbl_z = unZ; }
    double z() { return dbl_z; }
    
    friend ostream& operator <<( ostream& os, clsVector3D& p )
    {
        os << "( " << p.x() << "," << p.y() << "," << p.z() << " )";
        return os;
    }
    
    friend clsVector3D operator +( clsVector3D a, clsVector3D b )
    {
        clsVector3D s;
        s.x( a.x() + b.x() );
        s.y( a.y() + b.y() );
        s.z( a.z() + b.z() );
        
        return s;
    }
    
    friend clsVector3D operator * ( double esc, clsVector3D v )
    {
        clsVector3D w;
        
        w.x( esc * v.x() );
        w.y( esc * v.y() );
        w.z( esc * v.z() );
        
        return w;
    }
    
    friend clsVector3D operator * ( clsVector3D v, double esc )
    {
        return esc * v;
    }
    
    // EJER 1) operador de entrada del clsVector3D:
    friend istream& operator >>( istream& is, clsVector3D& v ){
        enum edo { S0, S1, S2, S3, S4, S5, SF, SError };
        enum edo s = S0;
        char c;
        int n;
        
        while ((s != SF) && (s != SError))
        {
            //f >> c;
            //f.eatwhite();
            is.get(c);
            cout << c;
            if (is.eof()) c = '\0';
            switch (s)
            {
                case S0:if (c == '[')
                    s = S1;
                else
                    s = SError;
                    break;
                case S1:
                case S5:
                    if (c == '(')
                    {
                        //s = S2;
                        is >> n;
                        s = S3;
                    }
                    else
                        if (c == ']')
                            s = SF;
                        else
                            s = SError;
                    break;
                case S2:if ('0' <= c  && c <= '9')
                {
                    //d = c;
                    s = S3;
                }
                else
                    s = SError;
                    break;
                case S3:if (c == ')')
                {
                    s = S4;
                    cout << "Se agrega el nodo con id " << n << endl;
                }
                else
                    s = SError;
                    break;
                case S4:if (c == ']')
                    s = SF;
                else
                    if (c == ',')
                        s = S5;
                    else
                        s = SError;
                    break;
                    /*		case S5:if( c == '(' )
                     s = S2;
                     else
                     s = SError;
                     break;
                     */
                    
            }
        }
        if (s == SF)
            cout << "todo ok\n";
        else
        {
            cout << "error en la cadena\n";
            throw 5;
        }
        // por lo pronto solo es un dummy que regresa el (0,1.0,2.0)
        clsVector3D w;
        w.y(1.0);
        w.z(2.0);
        
        v = w;
        return is;
    }
    // EJER 2) operador Producto Cruz de dos clsVector3D
//    ya está
    friend clsVector3D operator *( clsVector3D& a, clsVector3D& b )
    {
        
        // por lo pronto un dummy que regresa el ( -1.0,-2.0,-3.0 )
        clsVector3D w;
        w.x( a.y() * b.z() - a.z() * b.y());
        w.y( a.z() * b.x() - a.x() * b.z() );
        w.z( a.x() * b.y() - a.y() * b.x());
        
        return w;
    }
};
// =============================================
class clsPlano3D
{
private:
    double dbl_A, dbl_B, dbl_C, dbl_D; // representa el plano Ax + By + Cz + D = 0.
public:
    clsPlano3D()
    {
        dbl_A = dbl_B = dbl_C = dbl_D = 0.0;
    }
    
    // EJER 3)  Construir el plano a partir de los tres puntos v1, v2 y v3.
    clsPlano3D( clsVector3D v1, clsVector3D v2, clsVector3D v3 )
    {  // por lo pronto un dummy que entrega el 5x + 5y + 5z + 5 = 0.
        dbl_A = ((v2.y() - v1.y()) * (v3.z() - v1.z())) - ((v3.y() - v1.y()) * (v2.z() - v1.z()));
        dbl_B = ((v2.z() - v1.z()) * (v3.x() - v1.x())) - ((v3.z() - v1.z()) * (v2.x() - v1.x()));
        dbl_C = ((v2.x() - v1.x()) * (v3.y() - v1.y())) - ((v3.x() - v1.x()) * (v2.y() - v1.y()));
        dbl_D = dbl_A * -v1.x() + dbl_B * -v1.y() + dbl_C * -v1.z();
    }
    
    void A( double unA ) { dbl_A = unA; }
    double A() { return dbl_A; }
    
    void B( double unB ) { dbl_B = unB; }
    double B() { return dbl_B; }
    
    void C( double unC ) { dbl_C = unC; }
    double C() { return dbl_C; }
    
    void D( double unD ) { dbl_D = unD; }
    double D() { return dbl_D; }
    
    // EJER 4) ImpresiÛn del plano A * x + B * y + c * z + D = 0.
    friend ostream& operator <<( ostream& os, clsPlano3D& p )
    {
        os << "Este es el dummy de la impresiÛn del plano..." << endl;
        return os;
    }
    
    // EJER 5) Lectura del plano como A * x + B * y + c * z + D = 0.
    friend istream& operator >>( istream& is, clsPlano3D& p )
    {
        clsPlano3D w;
        p = w;
        return is;
    }
    
    // EJER 6) Obtener el punto que resulta de la intersecciÛn de tres planos
    friend clsVector3D interseccion( clsPlano3D P1, clsPlano3D P2, clsPlano3D P3 )
    {
        // va el dummy con el ( 100.0 ,200.0, 300.0)
        clsVector3D a;
        a.x( 100.0 );
        a.y( 200.0 );
        a.z( 300.0 );
        return a;
    }
};
// =============================================
int main()
{
    clsVector3D a,b,c;
    
    a.x( 1.0 );
    a.y( 2.0 );
    a.z( 3.0 );
    
    b.x( -2.0 );
    b.y( -5.0 );
    b.z( -7.0 );
    
    c= a * b;
    
    //cout << "producto cruz:" << c.x() << "," << c.y() << "," << c.z();
    
    //cout << a << " + " << b << " = " << a + b << endl;
    
    //cout << 5.0 << " * " << a << " = " << 5.0 * a << endl;
    
    //cout << a << " * " << 5.0 << " = " << a * 5.0 << endl;
    
//    cin >> c;
    
//    cout << "c = " << c << endl;
    
    //cout << " a * b = " << a << " * " << b << " = " << a * b << endl;
    
    clsPlano3D q1,q2,q3;
    
    
    
    a.x( 3.0 );
    a.y( 2.0 );
    a.z( 1.0 );
    
    b.x( -4.0 );
    b.y( -1.0 );
    b.z( 1.0 );
    
    c.x( -5.0 );
    c.y( -3.0 );
    c.z( -1.0 );
    
    q1=clsPlano3D(a, b, c);
    
    cout << "plano: " << q1.A() << "x" << q1.B() << "y" << q1.C() << "z" << q1.D();
//    cout << q1 << endl;
    
//    cout << "Interseccion " << interseccion( q1,q2,q3 ) << endl;
    
    return 0;
    
}
// ========================================================

