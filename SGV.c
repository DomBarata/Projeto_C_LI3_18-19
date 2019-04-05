#define NUMFILIAIS 3

struct sgv
{
	CatProdutos cp;
	CatClientes ccli;
	Facturacao fact;
	Filial filiais[NUMFILIAIS];
};

SGV 
	CriaSGV(CatProdutos catp, CatClientes catc, 
		Facturacao f, Filial fil1, Filial fil2, Filial fil3)
	{
		SGV interface = malloc(sizeof(struct sgv));
		interface->cp = catp;
		interface->ccli = catc;
		interface->fact = f;
		interface->fil[0] = fil1;
		interface->fil[1] = fil2;
		interface->fil[2] = fil3;

		return interface;
	}