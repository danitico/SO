struct INPUT_A{
	char *nombre_fichero;	
	char *apellido;
};

struct INPUT_B{
	char *nombre_fichero;	
	int edad;
	char *provincia;
};

program BASES_DATOS{
	version BASES_DATOS_VER{
		void a(INPUT_A buscar)=1;
		void b(INPUT_B buscar)=2;
	}=1;
}=0xA0000001;
