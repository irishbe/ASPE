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
	string corregir_min, corregir_seg;
	
	if(x.minutos<10){
		corregir_min = "0" + to_string(x.minutos);
	}else{
		corregir_min = to_string(x.minutos);
	}
	
	if(x.seg<10){
		corregir_seg = "0" + to_string(x.seg);
	}else{
		corregir_seg = to_string(x.seg);
	}
	return (to_string(x.horas) + ":" + corregir_min + ":" + corregir_seg);
}