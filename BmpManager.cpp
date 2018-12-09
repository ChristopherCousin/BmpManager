#include "pch.h"
#include <iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<math.h>

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

	//Copiar cabezera
	in.read((char *)(&Header), sizeof(Header));
	out.write((char *)(&Header), sizeof(Header));

	//Tamaño imagen
	in.seekg(0x0012);
	in.read((char *)&width, 4);
	in.read((char *)&height, 4); //0x0016

	in.seekg(0x0036); //Ir directamente a la tabla de colores (Saltar cabezera)

	//Ejecutar mientras el archivo tenga contenido
	while (!in.eof()) {
		in.read((char *)(&pixel), sizeof(pixel)); //Lee la composición del color (r, g, b)
		char grayColor = (pixel.b, pixel.g, pixel.r); //Variable que establece el color en 8 bits
		out << grayColor << grayColor << grayColor; //Asigna el nuevo color a r, g, b
	}
	in.close();
	out.close();
}