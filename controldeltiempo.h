#include <iostream>
#include <ctime>
using namespace std;


struct Fecha{
	long segundos;
	int dias, meses, anios, minutos, horas, seg;
};

Fecha definir_fecha(short d, short h, short m, short s){
	Fecha aux;
	time_t hoy = time(NULL) + d*86400 + h*3600 + m*60 + s;
	struct tm *f = localtime(&hoy);
	
	aux.dias = f->tm_mday;
	aux.meses = f->tm_mon+1;
	aux.anios = f->tm_year+1900;
	aux.minutos = f->tm_min;
	aux.horas = f->tm_hour;
	aux.seg = f->tm_sec;
	return (aux);
}

string formato_fecha(Fecha x){
	return (to_string(x.dias) + "/" + to_string(x.meses) + "/" + to_string(x.anios));
}

string formato_hora(Fecha x){
	return (to_string(x.horas) + ":" + to_string(x.minutos) + ":" + to_string(x.seg));
}