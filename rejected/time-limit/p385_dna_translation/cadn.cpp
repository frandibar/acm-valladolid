//
// cadn.cpp
//

#include "cadn.h"
#include <afx.h>

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
CAdn::CAdn(CString adn)
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
CString CAdn::Complemento(CString adn)
{
	CString comp = adn;
	// intercambiar A y T
	comp.Replace("A","t");
	comp.Replace("T","A");
	comp.Replace("t","T");
	// intercambiar C y G
	comp.Replace("C","g");
	comp.Replace("G","C");
	comp.Replace("g","G");
	return comp;
}

/*****************************************************************************/
CString CAdn::RNA(CString complemento)
{
	CString rna = complemento;
	// cambiar T por U
	rna.Replace("T","U");
	return rna;
}

/*****************************************************************************/
CString CAdn::Hallar_Proteina(CString rna)
{
	// buscar el codon de comienzo
	int com = rna.Find(CODON_COM,0);
	if (com == -1) {
		// buscar el codon de comienzo al reves
		com = rna.Find(CODON_COM_I,0);
		if (com == -1)
			return MENSAJE_FRACASO;
		else {
			rna.MakeReverse();
			com = rna.Find(CODON_COM,0);
		}
	}
	// buscar el codon de fin (busca la primera ocurrencia)
	// si hay mas de un codon de fin, me quedo con el mayor que sea mayor que com
	int aux;
	int fin1 = rna.Find(CODON_FIN1, com + LONG_CODON);
	if (fin1 != -1) {
		aux = fin1;
		while (aux != -1) {
			aux = rna.Find(CODON_FIN1, aux + 1);
			if (aux != -1) fin1 = aux;
		}
	}
	int fin2 = rna.Find(CODON_FIN2, com + LONG_CODON);
	if (fin2 != -1) {
		aux = fin2;
		while (aux != -1) {
			aux = rna.Find(CODON_FIN2, aux + 1);
			if (aux != -1) fin2 = aux;
		}
	}
	int fin3 = rna.Find(CODON_FIN3, com + LONG_CODON);
	if (fin3 != -1) {
		aux = fin3;
		while (aux != -1) {
			aux = rna.Find(CODON_FIN3, aux + 1);
			if (aux != -1) fin3 = aux;
		}
	}
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
	CString proteina;
	for (int i = com+3; i < fin; i += LONG_CODON) {
		CString codon = rna.Mid(i, LONG_CODON);
		CString prot;
		if ((prot = identificar_codon(codon)) == "")
			return MENSAJE_FRACASO;
		if (proteina != "") proteina += "-";
		proteina += prot;
	}

	return proteina;
}

/*****************************************************************************/
CString CAdn::identificar_codon(CString codon)
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
	}
}

/*****************************************************************************/
CString CAdn::Proteina()
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


/******************************************************************************

  PROCEDIMIENTO PARA HALLAR LA PROTEINA:

OBSERVACION:
 
   la cadena TTAATACGACATAATTAT puede devolver dos valores Leu-Tyr o Ser-Tyr (leida al reves)

******************************************************************************/

