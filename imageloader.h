#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED
//Clase que ayuda a cargar las Imagenes como Texturas

class Image {
	public:
		Image(char* ps, int w, int h);
		~Image();

		char* pixels;
		int width;
		int height;
};

//lee el bitmap de la imagen.
Image* loadBMP(const char* filename);

#endif
