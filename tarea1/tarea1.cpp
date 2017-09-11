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
friend istream& operator >>(istream& is, clsVector3D& v)
{
        v.leeVector(&is);
        return is;
	}

	void leeVector(istream *f)
	{
		enum edo { S0, S1, S2, S3, SF, SError };
		enum edo s = S0;
		char c;
		string n;

		while ((s != SF) && (s != SError)){
			do (*f).get(c); while (c == ' ');
			if ((*f).eof()) c = '\0';

			switch (s){

			case S0:if (c == '(')
				s = S1;
					else
						s = SError;
				break;

			case S1:
				if (('0' <= c  && c <= '9') || c=='-')
					n.push_back(c);
				else
                    if(c==','){
                        dbl_x=stod(n);
                        n="";
                        s = S2;
                    }
                    else
                        s = SError;
				break;

			case S2:if (('0' <= c  && c <= '9')|| c=='-')
                    n.push_back(c);
				else
                    if(c==','){
                        dbl_y=stod(n);
                        n="";
                        s = S3;
                    }
                    else
                        s = SError;
				break;

			case S3:if (('0' <= c  && c <= '9')|| c=='-')
					n.push_back(c);
				else
                    if(c==')'){
                        dbl_z=stod(n);
                        n="";
                        s = SF;
                    }
                    else
                        s = SError;
				break;
			}
		}

		if (s == SF)
			cout << "Vector Leido\n";
		else
			cout << "Error en la cadena\n";
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
        string x = (p.B()<0) ? "x " : "x +";
        string y = (p.C()<0) ? "y " : "y +";
        string z = (p.D()<0) ? "z " : "z +";
        os << "plano: " << p.A() << x << p.B() << y << p.C() << z << p.D() << " = 0\n";
        return os;
    }
    
    // EJER 5) Lectura del plano como A * x + B * y + c * z + D = 0.
   friend istream& operator >>(istream& is, clsPlano3D& p)
   {
        p.leePlano(&is);
		return is;
	}

	void leePlano(istream *f)
	{
		enum edo { S0, S1, S2, S3, SF, SError };
		enum edo s = S0;
		char c;
		string pl;

		while ((s != SF) && (s != SError)){
			do (*f).get(c); while (c == ' ');
			if ((*f).eof()) c = '\0';

			switch (s){

			case S0:
			    if (('0' <= c  && c <= '9') || c=='-')
				pl.push_back(c);
				else
                    if(c=='x' || c=='X'){
                        dbl_A=stod(pl);
                        pl="";
                        s = S1;
                    }
                    else
                        if (c=='*' || c=='+')
                            ;
                        else
                            s = SError;
				break;

			case S1:
				if (('0' <= c  && c <= '9') || c=='-' || c=='+')
					pl.push_back(c);
				else
                    if(c=='y' || c=='Y'){
                        dbl_B=stod(pl);
                        pl="";
                        s = S2;
                    }
                    else
                        if (c=='*')
                            ;
                        else
                            s = SError;
				break;

			case S2:
			    if (('0' <= c  && c <= '9') || c=='-')
					pl.push_back(c);
				else
                    if(c=='z' || c=='Z'){
                        dbl_C=stod(pl);
                        pl="";
                        s = S3;
                    }
                    else
                        if (c=='*' || c=='+')
                            ;
                        else
                            s = SError;
				break;

			case S3:
			    if (('0' <= c  && c <= '9') || c=='-')
					pl.push_back(c);
				else
                    if(c=='='){
                        dbl_D=stod(pl);
                        pl="";
                        s = SF;
                    }
                    else
                        if (c=='+')
                            ;
                        else
                            s = SError;
				break;
			}
		}
		if (s == SF)
			cout << "Plano Leido\n";
		else
			cout << "Error en la cadena\n";
	}
    
    // EJER 6) Obtener el punto que resulta de la intersecciÛn de tres planos
    friend clsVector3D interseccion( clsPlano3D P1, clsPlano3D P2, clsPlano3D P3 )
    {
		clsVector3D a;
		double planos[3][3]={{P1.A(),P1.B(),P1.C()},{P2.A(),P2.B(),P2.C()},{P3.A(),P3.B(),P3.C()}};
		double aux1[3][3];
		double aux2[3][3];
		double aux3[3][3];
		double d[3]={P1.D(),P2.D(),P3.D()};
		double detP=det(planos);

		for(int j=0;j<3;j++)
            for(int k=0;k<3;k++){
                aux1[j][k]=planos[j][k];
                aux2[j][k]=planos[j][k];
                aux3[j][k]=planos[j][k];
            }

        for(int i=0;i<3;i++){
            aux1[i][0]=-d[i];
            aux2[i][1]=-d[i];
            aux3[i][2]=-d[i];
        }
        a.x(det(aux1)/detP);
        a.y(det(aux2)/detP);
        a.z(det(aux3)/detP);

		return a;
    }
	
	static double det(double m[3][3])
		{
        return ((m[0][0]*m[1][1]*m[2][2])+(m[0][1]*m[1][2]*m[2][0])+(m[0][2]*m[1][0]*m[2][1]))-
        ((m[0][2]*m[1][1]*m[2][0])+(m[0][1]*m[1][0]*m[2][2])+(m[0][0]*m[1][2]*m[2][1]));
	}
};
// =============================================
int main()
{
    clsVector3D a,b,c,d;
     //Ejercicio 1
    istrstream sin("(-36,15,12)");
    sin>>a;
    cout<<a<<endl;
	
    a.x( 1.0 );
    a.y( 2.0 );
    a.z( 3.0 );
    
    b.x( -2.0 );
    b.y( -5.0 );
    b.z( -7.0 );
    
    c= a * b;
	cout<<c;
    
    
	
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
    
    cout << q1;

    istrstream plano1("1*x-3*y+2*z+3=0");
    istrstream plano2("5*x+6*y-1*z-13=0");
    istrstream plano3("4*x-1*y+3*z-8=0");
    plano1>>q1;
    plano2>>q2;
    plano3>>q3;
    d=interseccion(q1,q2,q3);
    cout<<d<<endl;
	
    return 0;
    
}
// ========================================================