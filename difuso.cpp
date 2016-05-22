/*
  program:5
  Name: difuso.cpp
  Author: josue acevedo maldonado
  Date: 20/05/16
  Description:
*/
#include <math.h>
#include <stdio.h>

double temperatura, humedad,tmb,tb,tn,ta,tma,hmb,hb,hn,ha,hma,bg,bn,bp,m,sp,sn,sg;

double AND(double a, double b){
	return (((a) < (b)) ? (a) : (b));
	}

double OR(double a, double b){
		return (((a) > (b)) ? (a) : (b));
	}

double NOT(double a){
	return 1.0-a;
	}



double FuncionGrado(double x, double x0, double x1){
	if(x<=x0) return 0.0;
	else if(x>x0 && x<x1) return (x/(x1-x0))-(x0/(x1-x0));
	else if(x>=x1) return 1.0;
	return 0.0;
		}

double FuncionGradoInversa(double x, double x0, double x1){

	if(x<=x0) return 1.0;
	else if(x>x0 && x<x1) return -(x/(x1-x0))+(x1/(x1-x0));
	else if(x>=x1) return 0.0;
	return 0.0;
		}


double FuncionTriangulo( double x,double x0, double  x1, double x2){

	if(x<=x0) return 0.0;
	else if(x>x0 && x<=x1) return (x/(x1-x0))-(x0/(x1-x0));
	else if(x>x1 && x<=x2) return (-(x/(x2-x1))+(x2/(x2-x1)));
	else if(x>x2) return 0.0;
	return 0.0;
}

double FuncionTrapezoide(double x,double x0,double x1,double x2,double x3){
	if(x<=x0) return 0.0;
	else if(x>x0 && x<=x1) return (x/(x1-x0))-(x0/(x1-x0));
  else if(x>x1 && x<=x2) return 1.0;
  else if(x>x2 && x<=x3) return -(x/(x3-x2))+(x3/(x3-x2));
  else if(x>x3) return 0.0;
	return 0.0;
}

int main(){
  printf("\t\tControl difuso de la calefaccion \n");
	printf("\tvalor de la temperatura: ");
	scanf_s("%lf",&temperatura );
	printf("\tvalor de la humedad: ");
	scanf_s("%lf",&humedad );
	//printf("\ntemperatura %f",temperatura);
	//printf("\nhumedad %f",humedad);

	tmb=FuncionGradoInversa(temperatura, 10.0,15.0);
	tb=FuncionTriangulo(temperatura,10.0,16.0,20.0);
	tn=FuncionTriangulo(temperatura,18.0,20.0,22.0);
	ta=FuncionTriangulo(temperatura,20.0,25.0,30.0);
	tma=FuncionGrado(temperatura,25.0,30.0);

	hmb=FuncionGradoInversa(humedad, 10.0,20.0);
	hb=FuncionTriangulo(humedad,10.0,25.0,40.0);
	hn=FuncionTriangulo(humedad,30.0,40.0,50.0);
	ha=FuncionTriangulo(humedad,40.0,55.0,70.0);
	hma=FuncionGrado(humedad,60.0,70.0);

	printf("\n\t\ttmb: %lf",tmb);
	printf("\thmb: %lf",hmb);
	printf("\n\t\ttb: %lf ",tb);
	printf("\thb: %lf ",hb);
	printf("\n\t\ttn: %lf ",tn);
	printf("\thn: %lf ",hn);
	printf("\n\t\tta: %lf ",ta);
	printf("\tha: %lf ",ha);
	printf("\n\t\ttma: %lf",tma);
	printf("\thma: %lf",hma);

bg=sqrt(pow(AND(tma,ha),2)+pow(AND(tma,hma),2));
bn=sqrt(pow(AND(tma,hb),2)+pow(AND(tma,hn),2)+pow(AND(ta,hma),2));
bp=sqrt(pow(AND(ta,hn),2)+pow(AND(ta,ha),2)+pow(AND(tn,hma),2)+pow(AND(tma,hmb),2));
m=sqrt(pow(AND(tb,hmb),2)+pow(AND(tb,hb),2)+pow(AND(tn,hmb),2)+pow(AND(tn,hb),2)+pow(AND(tn,ha),2)+pow(AND(ta,hmb),2)+pow(AND(ta,hb),2)+pow(AND(tn,hn),2));
sp=sqrt(pow(AND(tb,hn),2)+pow(AND(tb,ha),2));
sn=sqrt(pow(AND(tmb,hmb),2)+pow(AND(tmb,hb),2)+pow(AND(tb,hma),2));
sg=sqrt(pow(AND(tmb,hn),2)+pow(AND(tmb,ha),2)+pow(AND(tmb,hma),2));

printf("\n\n\n\n\t\t\tbg: %lf",bg);
printf("\n\t\t\tbn: %lf",bn);
printf("\n\t\t\tbp: %lf",bp);
printf("\n\t\t\tm: %lf",m);
printf("\n\t\t\tsp: %lf",sp);
printf("\n\t\t\tsn: %lf",sn);
printf("\n\t\t\tsg: %lf",sg);



printf("\n\n\n\n\tdesfuzzyficacion centroide:\n");

 //resultado=((bg*(-15))+((bg*(-7.5))+(bn*(-10))+(bn*(-2.5))+(bp*(-7.5))+(bp*(0))+(m*-1)+(m*1)+(sp*0)+(sp*7.5)+(sn*2.5)+(sn*10)+(sg*7.5))+(sg*15))/(bg*2+bn*2+bp*2+m*2+sp*2+sn*2+sg*2);

//double resultado=((bg*(-10))+(bn*(-5))+(bp*(-2.5))+(m*0)+(sp*2.5)+(sn*5)+(sg*10))/(bg+bn+bp+m+sp+sn+sg);
double resultado=((bg==1?-10:(bg*(-15)))+(bn*(-8.4+((bg-bn)==-1?3.4:(bg-bn))))+(bp*(-4.1+((bn-bp)==-1?1.59:((bn-bp)*2.85))))+(m*(-0.7+((bp-m)==-1?0.7:(bp-m))))+(sp*(0.7+((m-sp)==-1?1.8:(m-sp))))+(sn*(4.2+((sp-sn)==-1?0.8:(sp-sn)*2.85)))+(sg*(8.3+((sn-sg)==-1?1.69:(sn-sg)))))/(bg+bn+bp+m+sp+sn+sg);

printf("\t <%lf>",resultado);
if(resultado >=0){
	printf("\t %c Subir la calefaccion ", (char) 286);
}else{
	printf("\t %c Bajar la calefaccion ",(char) 287 );
	resultado*=-1;
}
printf("%lf",resultado);
printf(" %cc\n",(char) 167);

/*


*/
 	return 0;
 }
