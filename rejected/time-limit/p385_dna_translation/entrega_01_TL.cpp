
/* @JUDGE_ID:  40922FK  385  C++  */
    
/******************************************************************************
 Solution to Problem 385 - DNA Translation
 by: Francisco Dibar
 date: Jan-04-2004
******************************************************************************/

#include <iostream>
#include <string>
#include <fstream>		// manejo de archivos

#define FIN_INPUT	"*"

using namespace std;

/*****************************************************************************
*	DEFINICION de CAdn
******************************************************************************/
class CAdn
{
private:
	string m_tbl_sintesis[4][4][4];
	string m_sADN;
	string m_sComplemento;
	string m_sRNA;
	string m_sProteina;

protected:
	void	init_tbl_sintesis();
	string	Complemento(string adn = "");
	string	RNA(string complemento);
	string	Hallar_Proteina(string rna);
	string	identificar_codon(string codon);
	string	intercambiar(string str, string s1, string s2);
	int		indice_letra(char letra);

public:
	CAdn();
	CAdn(string adn);
	string Proteina();

};

/*****************************************************************************
*	IMPLEMENTACION de CAdn
******************************************************************************/

#include <algorithm>		// funcion reverse

#define U	0
#define C	1
#define A	2
#define G	3
#define T	4

#define LONG_CODON		3

#define CODON_COM		"AUG"
#define CODON_COM_I		"GUA"

#define CODON_FIN1		"UAA"
#define CODON_FIN2		"UAG"
#define CODON_FIN3		"UGA"

#define MENSAJE_FRACASO		"*** No translatable DNA found ***"

/*****************************************************************************/
CAdn::CAdn(string adn)
{
	init_tbl_sintesis();
	m_sADN = adn;
	m_sComplemento = Complemento(m_sADN);
	m_sRNA = RNA(m_sComplemento);
	m_sProteina = Hallar_Proteina(m_sRNA);
	if (m_sProteina == MENSAJE_FRACASO) {
		// reemplazar el ADN por su complemento
		m_sADN = m_sComplemento;
		m_sComplemento = Complemento(m_sADN);
		m_sRNA = RNA(m_sComplemento);
		m_sProteina = Hallar_Proteina(m_sRNA);
	}
}

/*****************************************************************************/
string CAdn::Complemento(string adn)
{
	string comp = adn;
	// intercambiar A y T
	comp = intercambiar(comp,"A","T");
	// intercambiar C y G
	comp = intercambiar(comp,"C","G");
	return comp;
}

/*****************************************************************************/
string CAdn::RNA(string complemento)
{
	string rna = complemento;
	// cambiar T por U
	rna = intercambiar(rna,"T","U");
	return rna;
}

/*****************************************************************************/
string CAdn::intercambiar(string str, string s1, string s2)
{
	string aux("_");
	int i;
	// reemplazar s1 por aux
	while ((i = str.find(s1)) != -1) 
		str.replace(i,1,aux);
	// reemplazar s2 por s1
	while ((i = str.find(s2)) != -1) 
		str.replace(i,1,s1);
	// reemplazar aux por s2
	while ((i = str.find(aux)) != -1) 
		str.replace(i,1,s2);
	return str;
}

/*****************************************************************************/
string CAdn::Hallar_Proteina(string rna)
{
	// buscar el codon de comienzo
	int com = rna.find(CODON_COM);
	if (com == -1) {
		// buscar el codon de comienzo al reves
		com = rna.find(CODON_COM_I);
		if (com == -1)
			return MENSAJE_FRACASO;
		else {
			// invertir rna
			reverse(rna.begin(),rna.end());
			com = rna.find(CODON_COM);
		}
	}
	// buscar el codon de fin (busca la primera ocurrencia)
	// si hay mas de un codon de fin, me quedo con el mayor que sea mayor que com
	int fin1 = rna.rfind(CODON_FIN1);
	int fin2 = rna.rfind(CODON_FIN2);
	int fin3 = rna.rfind(CODON_FIN3);
	int fin;
	if ((fin1 != -1) || (fin2 != -1) || (fin3 != -1)) {
		if ((fin1 >= fin2) && (fin1 >= fin3))
			fin = fin1;
		else if ((fin2 >= fin1) && (fin2 >= fin3))
			fin = fin2;
		else if ((fin3 >= fin1) && (fin3 >= fin2))
			fin = fin3;
	} else
		return MENSAJE_FRACASO;

	if ((fin - com) % 3 != 0)
		return MENSAJE_FRACASO;

	// encontre el codon de comienzo y fin, ahora identifico cada codon
	string proteina;
	for (int i = com+3; i < fin; i += LONG_CODON) {
		string codon = rna.substr(i, LONG_CODON);
		string prot;
		if ((prot = identificar_codon(codon)) == "")
			return MENSAJE_FRACASO;
		if (proteina != "") proteina += "-";
		proteina += prot;
	}

	return proteina;
}

/*****************************************************************************/
string CAdn::identificar_codon(string codon)
{
	// busca el codon en la tabla m_tbl_sintesis
	int i = indice_letra(codon[0]);
	int j = indice_letra(codon[1]);
	int k = indice_letra(codon[2]);

	return m_tbl_sintesis[i][j][k];
}

/*****************************************************************************/
int CAdn::indice_letra(char letra)
{
	switch(letra) {
		case 'U': return U;
		case 'C': return C;
		case 'A': return A;
		case 'G': return G;
		default: return -1;
	}
}

/*****************************************************************************/
string CAdn::Proteina()
{
	return m_sProteina;
}

/*****************************************************************************/
void CAdn::init_tbl_sintesis()
{
	m_tbl_sintesis[U][U][U] = "Phe";
	m_tbl_sintesis[U][U][C] = "Phe";
	m_tbl_sintesis[U][U][A] = "Leu";
	m_tbl_sintesis[U][U][G] = "Leu";
	m_tbl_sintesis[U][C][U] = "Ser";
	m_tbl_sintesis[U][C][C] = "Ser";
	m_tbl_sintesis[U][C][A] = "Ser";
	m_tbl_sintesis[U][C][G] = "Ser";
	m_tbl_sintesis[U][A][U] = "Tyr";
	m_tbl_sintesis[U][A][C] = "Tyr";
	m_tbl_sintesis[U][A][A] = "-";
	m_tbl_sintesis[U][A][G] = "-";
	m_tbl_sintesis[U][G][U] = "Cys";
	m_tbl_sintesis[U][G][C] = "Cys";
	m_tbl_sintesis[U][G][A] = "-";
	m_tbl_sintesis[U][G][G] = "Trp";
	m_tbl_sintesis[C][U][U] = "Leu";
	m_tbl_sintesis[C][U][C] = "Leu";
	m_tbl_sintesis[C][U][A] = "Leu";
	m_tbl_sintesis[C][U][G] = "Leu";
	m_tbl_sintesis[C][C][U] = "Pro";
	m_tbl_sintesis[C][C][C] = "Pro";
	m_tbl_sintesis[C][C][A] = "Pro";
	m_tbl_sintesis[C][C][G] = "Pro";
	m_tbl_sintesis[C][A][U] = "His";
	m_tbl_sintesis[C][A][C] = "His";
	m_tbl_sintesis[C][A][A] = "Gln";
	m_tbl_sintesis[C][A][G] = "Gln";
	m_tbl_sintesis[C][G][U] = "Arg";
	m_tbl_sintesis[C][G][C] = "Arg";
	m_tbl_sintesis[C][G][A] = "Arg";
	m_tbl_sintesis[C][G][G] = "Arg";
	m_tbl_sintesis[A][U][U] = "Ile";
	m_tbl_sintesis[A][U][C] = "Ile";
	m_tbl_sintesis[A][U][A] = "Ile";
	m_tbl_sintesis[A][U][G] = "Met";
	m_tbl_sintesis[A][C][U] = "Thr";
	m_tbl_sintesis[A][C][C] = "Thr";
	m_tbl_sintesis[A][C][A] = "Thr";
	m_tbl_sintesis[A][C][G] = "Thr";
	m_tbl_sintesis[A][A][U] = "Asn";
	m_tbl_sintesis[A][A][C] = "Asn";
	m_tbl_sintesis[A][A][A] = "Lys";
	m_tbl_sintesis[A][A][G] = "Lys";
	m_tbl_sintesis[A][G][U] = "Ser";
	m_tbl_sintesis[A][G][C] = "Ser";
	m_tbl_sintesis[A][G][A] = "Arg";
	m_tbl_sintesis[A][G][G] = "Arg";
	m_tbl_sintesis[G][U][U] = "Val";
	m_tbl_sintesis[G][U][C] = "Val";
	m_tbl_sintesis[G][U][A] = "Val";
	m_tbl_sintesis[G][U][G] = "Val";
	m_tbl_sintesis[G][C][U] = "Ala";
	m_tbl_sintesis[G][C][C] = "Ala";
	m_tbl_sintesis[G][C][A] = "Ala";
	m_tbl_sintesis[G][C][G] = "Ala";
	m_tbl_sintesis[G][A][U] = "Asp";
	m_tbl_sintesis[G][A][C] = "Asp";
	m_tbl_sintesis[G][A][A] = "Glu";
	m_tbl_sintesis[G][A][G] = "Glu";
	m_tbl_sintesis[G][G][U] = "Gly";
	m_tbl_sintesis[G][G][C] = "Gly";
	m_tbl_sintesis[G][G][A] = "Gly";
	m_tbl_sintesis[G][G][G] = "Gly";
}


/*****************************************************************************
*	PROGRAMA PRINCIPAL
******************************************************************************/
void main(int argc, char* argv[])
{
	string linea;
	// recorrer el archivo de entrada
	getline(cin, linea);		// leer la linea
	while (!cin.eof() && (linea != FIN_INPUT)) {
		CAdn adn(linea);
		linea = adn.Proteina();		
		cout.write(linea.data(), linea.length());
		cout.put('\n');
		getline(cin, linea);		// leer la linea
	}
}

