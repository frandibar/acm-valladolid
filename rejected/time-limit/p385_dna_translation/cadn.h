//
// cadn.h
//

#if !defined( __CADN_H_ )
#define __CADN_H_

#include <afx.h>		// para interceptar una tecla presionada	

#define MAX_LEN		255

class CAdn
{
private:
	CString m_tbl_sintesis[4][4][4];
	CString m_sADN;
	CString m_sComplemento;
	CString m_sRNA;
	CString m_sProteina;

protected:
	void	init_tbl_sintesis();
	CString Complemento(CString adn = "");
	CString RNA(CString complemento);
	CString Hallar_Proteina(CString rna);
	CString identificar_codon(CString codon);
	int		indice_letra(char letra);
public:
	CAdn();
	CAdn(CString adn);
	CString Proteina();

};


#endif	// __CADN_H_