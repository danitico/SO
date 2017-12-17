const MAXIMO=10;

struct INPUT_A_B{
	int vector[MAXIMO];
	int n;
};

struct OUTPUT_A{
	float media;
};

struct OUTPUT_B{
	int maximo;
};

struct INPUT_OUTPUT_C{
	int factorial;
};

program CALCULADORA{
	version CALCULADORA_VER{
		OUTPUT_A a(INPUT_A_B res)=1;
		OUTPUT_B b(INPUT_A_B res)=2;
		INPUT_OUTPUT_C c(INPUT_OUTPUT_C res)=3;
	}=1;
}=0xAB000003;
