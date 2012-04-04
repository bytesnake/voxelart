/**
 * Bsb_Vector ist die Vektorklasse fuer die bresicbit-Engine
 * 
 * @author bitowl, CaptnKartoffel
 * @version 14.02.2012
 * 
 * TODO :
 * Ausschreiben, an den stellen
 */
#include "../../inc/bsb_engine/bsb_vector.h"
	Bsb_Vector::Bsb_Vector(){
		x=0.0f;	
		y=0.0f;
		z=0.0f;
	}
    /**
     * Konstruktor
     * @param p_x X Richtung
     * @param p_y Y Richtung
     * @param p_z Z Richtung
     */
	Bsb_Vector::Bsb_Vector(float p_x,float p_y,float p_z){
        x=p_x;
        y=p_y;
        z=p_z;
    }

    /**
     * Addiert den Vector b zu diesem Vector
     * @param b der Vector der zu diesem hinzugerechnet wird...
     */
    void Bsb_Vector::add(Bsb_Vector* b){
        x+=b->x;
        y+=b->y;
        z+=b->z;
    }
    
    /**
     * Erzeugt einen neuen Vector, der aus den beiden Vectoren a und b addiert wird...
     * @return der neue Vector
     */
	 static Bsb_Vector* add(Bsb_Vector* a,Bsb_Vector* b){
        return new Bsb_Vector(a->x+b->x,a->y+b->y,a->z+b->z);
    }

    /**
     * subtrahiert Vektor b von diesem Vektor
     * @param b der Vector der zu diesem hinzugerechnet wird...
     */
    void Bsb_Vector::sub(Bsb_Vector* b){
        x-=b->x;
        y-=b->y;
        z-=b->z;
    }

    /**
     * substrahiert Vektor a von Vektor b und gibt diesen zurück 
     * @return der neue Vector
     */
    static Bsb_Vector* sub(Bsb_Vector* a,Bsb_Vector* b){
        return new Bsb_Vector(a->x-b->x,a->y-b->y,a->z-b->z);
    }


    /**
     * Multipliziert den Vector b zu diesem Vector
     * @param b der Vector der zu diesem hinzugerechnet wird->->->
     */
     void Bsb_Vector::mul(Bsb_Vector* b){
        x*=b->x;
        y*=b->y;
        z*=b->z;
    }

    /**
     * Multipliziert den Vector b zum Vector a und gibt diesen zurück
     * @return der neue Vector
     */
     static Bsb_Vector* mul(Bsb_Vector* a,Bsb_Vector* b){
        return new Bsb_Vector(a->x*b->x,a->y*b->y,a->z*b->z);
    }

    /**
     * dividiert diesen Vektor durch Vektor b
     * @param b der Vector der zu diesem hinzugerechnet wird->->->
     */
     void Bsb_Vector::div(Bsb_Vector* b){
        x/=b->x;
        y/=b->y;
        z/=b->z;
    }

    /**
     * dividiert Vektor a durch diesen Vektor
     */
     static Bsb_Vector* div(Bsb_Vector* a,Bsb_Vector* b){
        return new Bsb_Vector(a->x/b->x,a->y/b->y,a->z/b->z);
    }

    /**
     * multipliziert den Vektor mit einem Skalar
     */
     void Bsb_Vector::mul(float c){
        x*=c;
        y*=c;
        z*=c;
    }

    /**
     * multipliziert den Vektor mit einem Skalar
     */
     static Bsb_Vector* mul(Bsb_Vector* a,float c){
        return new Bsb_Vector(a->x*c,a->y*c,a->z*c);
    }

    /**
     * dividiert den Vektor durch einen Skalar
     */
     void Bsb_Vector::div(float c){
        x/=c;
        y/=c;
        z/=c;
    }

    /**
     * dividiert den Vektor durch einem Skalar
     */
     static Bsb_Vector* div(Bsb_Vector* a,float c){
        return new Bsb_Vector(a->x/c,a->y/c,a->z/c);
    }    

    /**
     * gibt das Skalarprodukt von zwei Vektoren zurück
     */
     float Bsb_Vector::scal_prod(Bsb_Vector* b){
        return x*b->x+y*b->y+z*b->z;
    }

    /**
     * gibt das Skalarprodukt von zwei Vektoren zurück
     */
     static float scal_prod(Bsb_Vector* a,Bsb_Vector* b){
        return a->x*b->x+a->y*b->y+a->z*b->z;
    }

    /**
     * berechnet die Länge des Vektors
     */
     float Bsb_Vector::length(){
        return (float)sqrt(x*x+y*y+z*z);
    }

    /**
     * berechnet die Länge des Vektors
     */
     static float length(Bsb_Vector* a){
        return (float)sqrt(a->x*a->x+a->y*a->y+a->z*a->z);
    }

    /**
     * berechnet das Quadrat der Länge des Vektors
     */
     float Bsb_Vector::length_sq(){
        return x*x+y*y+z*z;
    }

    /**
     * berechnet das Quadrat der Länge des Vektors
     */
     static float length_sq(Bsb_Vector* a){
        return a->x*a->x+a->y*a->y+a->z*a->z;
    }    

    /**
     * normalisiert diesen Vektor
     * TODO sicherstellen, dass length!=0
     */
     void Bsb_Vector::normalize(){
        div(length());//TODO ausschreiben
    }

    /**
     * normalisiert Vektor a
     */
     static Bsb_Vector* normalize(Bsb_Vector* a){
        return div(a,length(a));//TODO ausschreiben
    }

    /**
     * berechnet das Kreuzprodukt zwischen diesem Vektor und Vektor b
     */
     Bsb_Vector* Bsb_Vector::cross(Bsb_Vector* b){
        return new Bsb_Vector(y*b->z - z*b->y, z*b->x-x*b->z,x*b->y-y*b->x);
    }

    /**
     * berechnet das Kreuzprodukt zwischen Vektor a und Vektor b
     */
     static Bsb_Vector* cross(Bsb_Vector* a,Bsb_Vector* b){
        return new Bsb_Vector(a->y*b->z - a->z*b->y, a->z*b->x-a->x*b->z,a->x*b->y-a->y*b->x);
    }

    /**
     * berechnet das Punktprodukt
     */
     float Bsb_Vector::dot(Bsb_Vector* b){
        return x*b->x+y*b->y+z*b->z;
    }

    /**
     * berechnet das Punktprodukt
     */
     static float dot(Bsb_Vector* a,Bsb_Vector* b){
        return a->x*b->x+a->y*b->y+a->z*b->z;
    }

    /**
     * berechnet den Winkel zwischen den beiden Vektoren
     */
     float Bsb_Vector::angle(Bsb_Vector* b){
        return (float)acos((x*b->x+y*b->y+z*b->z)/
            sqrt((x*x+y*y+z*z)*
                (b->x*b->x+b->y*b->y+b->z*b->z)));
    }    

    /**
     * berechnet den Winkel zwischen den beiden Vektoren
     */
     static float angle(Bsb_Vector* a,Bsb_Vector* b){
        return (float)acos((a->x*b->x+a->y*b->y+a->z*b->z)/
            sqrt((a->x*a->x+a->y*a->y+a->z*a->z)*
                (b->x*b->x+b->y*b->y+b->z*b->z)));
    }
