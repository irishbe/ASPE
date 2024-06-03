#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

struct Fecha{
	long segreales;
	short dias, meses, anios, minutos, horas, seg;
};

string to_string(short x) {
    ostringstream oss;
    oss << x;
    return oss.str();
}

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
	aux.segreales = time(NULL) + d*86400 + h*3600 + m*60 + s;
	return (aux);
}

string formato_fecha(Fecha x){
	return (to_string(x.dias) + "/" + to_string(x.meses) + "/" + to_string(x.anios));
}

string formato_hora(Fecha x){
	string corregir_min;
	
	if(x.minutos<10){
		corregir_min = "0" + to_string(x.minutos);
	}else{
		corregir_min = to_string(x.minutos);
	}
	
	return (to_string(x.horas) + ":" + corregir_min);
}
