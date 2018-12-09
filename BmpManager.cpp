#include "pch.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <math.h>

using namespace std;

struct rgb {
	unsigned char b, g, r;
}
pixel;

char Header[54]; //Cabecera que contiene tipo de archivo y bits de la imágen

int width = 0;
int height = 0;

ifstream in; //BMP en color
ofstream out; //BMP blanco y negro

int main() {
	char infile[] = "image.bmp";
	char outfile[] = "imageInGreyScale.bmp";

	//Abrir imágenes
	in.open(infile, ios::in | ios::binary);
	out.open(outfile, ios::out | ios::binary);

	//Copiar cabecera
	in.read((char *)(&Header), sizeof(Header));
	out.write((char *)(&Header), sizeof(Header));

	//Usamos la funcion seekg para ir a la posicion de offset del
	//bmp 18 que es el width en pixeles de la imagen
	in.seekg(0x0012);
	in.read((char *)&width, 4);

	//Ahora vamos a la posicion del height
	in.seekg(0x0016);
	in.read((char *)&height, 4);

	cout << "Height: " << height << endl;
	cout << "Width: " << width << endl;

	//Ahora nos posicionamos de la tabla de colores
	in.seekg(0x0036);

	//Mientras no llegue al final
	while (!in.eof()) {
		in.read((char *)(&pixel), sizeof(pixel)); //Lee la composición del color (r, g, b)
		char grayColor = (pixel.b, pixel.g, pixel.r); //Variable que establece el color en 8 bits
		out << grayColor << grayColor << grayColor; //Asigna el nuevo color a r, g, b
	}
	in.close();
	out.close();
}