/*
 * testeVector.cpp
 *
 *  Created on: Dec 8, 2008
 *      Author: emilio
 */

#include "../eVectorSpace/Vector2D.h"
#include "../eVectorSpace/Vector3D.h"
#include "../eVectorSpace/primitive_const.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>


void display2D( void )
{
	Vector2D T1( 1. , 0. ), T2( 0. , 1.) , T3( 1. , -1. ) , T4( 1. , 1.) ;

	Vector2D T5(.1*T1*(-5.));

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f( 1.0 , 1.0 , 1.0);
	T1.display();
	T5.display();
	T2.display();

	glColor3f( 1.0 , 0.0 , 1.0);

	T3.display();
	T4.display();

	glColor3f( 1.0 , 1.0 , 0.0);

	T3.display(T1);
	T4.display(T2);

	glFlush();
}

void display3D( void )
{
	Vector3D T1( 1. , 0. , 0. ), T2( 0. , 1. , 0. ) , T3( 0. , 0. , 1.) , T4( .5 , 1.5 , 1. ) ;

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( 0.0, 0.0, 0.0, 3.0 , 2.0, 3.0, 0.0, 0.0, 1.0 );


	glColor3f( 1.0 , 1.0 , 1.0);

	T1.display();
	T2.display();
	T3.display();

	glColor3f( 1.0 , 0.0 , 1.0);

	T4.display();

	glColor3f( 1.0 , 1.0 , 0.0);

	T3.display(T1);
	T4.display(T2);

	glFlush();
}


void init2D( void )
{
	glClearColor( 0.0 , 0.0 , 0.0, 0.0 );
	glColor3f( 1.0 , 1.0 , 1.0 );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D( -3.0, 3.0, -3.0, 3.0);
}


void init3D( void )
{
	glClearColor( 0.0 , 0.0 , 0.0, 0.0 );
	glColor3f( 1.0 , 1.0 , 1.0 );
}


void reshape( int w , int h )
{
	glViewport( 0, 0, w, h );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( -2.0 , 2.0, -2.0, 2.0, -2.0, 2.0 );
}


int main( int argc , char** argv )
{
// VECTOR2D TEST

	Vector2D T1, T2( 1 , 2) ;

	std::cout << T1 << T2*3.2 << 2.1*(T1+T2) << std::endl ;

	T2 = Vector2D(1 , 1);

	T1.set( 10 , 20) ;

	std::cout << T1 << T2 << T1 - T2 << std::endl ;

	T1 += 2*T2 ;
	T2 -= .5*T1;

	std::cout << T1 << T2 << T1.dot(T2) << " -- X = " << (T1+T2).x()
                                            << " -- y = " << (T1+T2).y() << std::endl ;

	T1 -= (PI/3)*T2 ;

	std::cout << T1 << T1.normQuad() << " +++ " << T1.norm() << std::endl ;

	std::cout << T1 << T2 << T1.cosTheta(T2) << " +++ " << T1.theta(T2) << std::endl ;

	if (T1 == T2)	printf("deu pau\n");
	else printf("FALSO\n");

	if (T1 != T2)	printf("Verdadeiro\n");
	else printf("deu pau\n");

	T1 = T2;

	if (T1 == T2)	printf("VERDADE\n");
	else printf("FALSO\n");

	T2.set( T1.x() , .4 );

	if (T1 != T2)	printf("VERDADE\n");
	else printf("FALSO\n");

	glutInit( &argc , argv );

	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize( 500 , 500 );
	glutInitWindowPosition( 0 , 0 );
	glutCreateWindow("Vector2D");
	glutDisplayFunc(display2D);
	init2D();

// VECTOR3D TEST

	Vector3D Ta, Tb( 10. , 2. , .5 ) ;

	Vector3D Ts( 1. , 2. , 3. );

	Ts = Ta+Tb;

	std::cout << 2.1*Ts << Tb << (Ts*2.1)+Tb << std::endl ;

	Ta = Vector3D( 1 , 1 , 10 );

	std::cout << Ta << Tb << Ta.cross(Tb) << std::endl ;

	Tb.set( 10 , 20 , 1.5 ) ;

	std::cout << Ta << Tb << Ta - Tb << std::endl ;

	Ta += 2*Tb ;
	Tb -= .5*Ta;

	std::cout << Ta << Tb << Ta.dot(Tb) << " -- X = " << (Ta+Tb).x()
                  << " -- y = " << (Ta+Tb).y() << " -- z = " << (Ta+Tb).z() << std::endl ;

	Ta -= (PI/3)*Tb ;

	std::cout << Ta << Ta.normQuad() << " +++ " << Ta.norm() << std::endl ;

	std::cout << Ta << Tb << Ta.cosTheta(Tb) << " +++ " << Ta.theta(Tb) << std::endl ;

	if (Ta == Tb)	printf("deu pau\n");
	else printf("FALSO\n");

	if (Ta != Tb)	printf("Verdadeiro\n");
	else printf("deu pau\n");

	Ta = Tb;

	if (Ta == Tb)	printf("VERDADE\n");
	else printf("FALSO\n");

	Tb.set( Ta.x() , .4 , Ta.z() );

	if (Ta != Tb)	printf("VERDADE\n");
	else printf("FALSO\n");

	Vector3D R1(0, 1, 0), R2(0, 0, 1), R3(1, 0, 1);

	std::cout << Tb << Tb.transform(R1 , R2, R3) << std::endl;

	Vector3D S(2, 3, 4);

	std::cout << Tb << Tb.scale(S) << Tb.translate(S) << std::endl;

	glutInitWindowSize( 500 , 500 );
	glutInitWindowPosition( 510 , 0 );
	glutCreateWindow("Vector3D");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display3D);
	init3D();
	glutMainLoop();


	return 0;
}
