struct CLIENTE{
	char *nombrecompleto;
	int edad;
	char *provincia;
};

struct INPUT_A{
	char *nombre_fichero;	
	char *apellido;
};

struct INPUT_B{
	char *nombre_fichero;	
	int edad;
	char *provincia;
};

struct OUTPUT_A_B{
	CLIENTE a<>;
};	

program BASES_DATOS{
	version BASES_DATOS_VER{
		OUTPUT_A_B A(INPUT_A buscar)=1;
		OUTPUT_A_B B(INPUT_B buscar)=2;
	}=1;
}=0x33;
