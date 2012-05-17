
/* @JUDGE_ID:  40922FK  197  C++  */
    
/******************************************************************************
 Solution to Problem 197 - Cube
 by: Francisco Dibar
 date: Mar-15-2004
******************************************************************************/

#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <algorithm>
#include <cmath>

#define LADO	3
#define DIM		27	// LADO*LADO*LADO

#define DEC		-1
#define INC		1

#define V		'.'
#define VACIO		"..........................."

#define PIEZA_A		'a'
#define PIEZA_B		'b'
#define PIEZA_C		'c'
#define PIEZA_D		'd'
#define PIEZA_E		'e'
#define PIEZA_F		'f'
#define PIEZA_G		'g'

#define CUBITOS_PIEZA_A		4
#define CUBITOS_PIEZA_B		3
#define CUBITOS_PIEZA_C		4
#define CUBITOS_PIEZA_D		4
#define CUBITOS_PIEZA_E		4
#define CUBITOS_PIEZA_F		4
#define CUBITOS_PIEZA_G		4

#define POSICIONES_PIEZA_A		6
#define POSICIONES_PIEZA_B		144
#define POSICIONES_PIEZA_C		72
#define POSICIONES_PIEZA_D		72
#define POSICIONES_PIEZA_E		64
#define POSICIONES_PIEZA_F		96
#define POSICIONES_PIEZA_G		96

using namespace std;
enum ejes { X = 0, Y, Z };

__int32 pos_pieza_a[] = {	0x6900000,
							0x3480000,
							0x0034800,
							0x001A400,
							0x00001A4,
							0x00000D2 };

__int32 pos_pieza_b[] = {	0x6800000,
							0x3400000,
							0x0D00000,
							0x0034000,
							0x0020180,
							0x1208000,
							0x0980000,
							0x0000026,
							0x00000C8,
							0x02C0000,
							0x0180800,
							0x0020120,
							0x3200000,
							0x0680000,
							0x001A000,
							0x00100C0,
							0x0009040,
							0x4C00000,
							0x0000013,
							0x0000190,
							0x0580000,
							0x00C0400,
							0x4024000,
							0x0640000,
							0x0006800,
							0x4030000,
							0x0241000,
							0x04C0000,
							0x0000130,
							0x0000019,
							0x1600000,
							0x0000C04,
							0x0004024,
							0x6400000,
							0x00001A0,
							0x0004030,
							0x2410000,
							0x0004C00,
							0x0019000,
							0x0001600,
							0x0C04000,
							0x0010090,
							0x6020000,
							0x0000824,
							0x3008000,
							0x0000203,
							0x00080C0,
							0x0008048,
							0x0000209,
							0x0900800,
							0x0240200,
							0x00C0200,
							0x000000B,
							0x0000806,
							0x4820000,
							0x0003400,
							0x2018000,
							0x0001208,
							0x2600000,
							0x0000098,
							0x0000032,
							0x2C00000,
							0x0000602,
							0x0804800,
							0x0C80000,
							0x00000D0,
							0x0002018,
							0x0012080,
							0x0026000,
							0x0002600,
							0x0032000,
							0x0002C00,
							0x0602000,
							0x2012000,
							0x0003200,
							0x0030100,
							0x0004120,
							0x6010000,
							0x0000406,
							0x1018000,
							0x0001009,
							0x0041200,
							0x0004804,
							0x1201000,
							0x0000601,
							0x0000034,
							0x0000058,
							0x0100C00,
							0x0904000,
							0x0806000,
							0x0482000,
							0x000B000,
							0x0006020,
							0x0002012,
							0x3010000,
							0x0104800,
							0x0018040,
							0x0040600,
							0x0010180,
							0x1009000,
							0x0001048,
							0x4804000,
							0x0001201,
							0x0180400,
							0x0000016,
							0x0000403,
							0x0024100,
							0x0000412,
							0x0601000,
							0x0001018,
							0x0480400,
							0x000001A,
							0x0403000,
							0x0002410,
							0x0013000,
							0x0006400,
							0x0016000,
							0x0003010,
							0x0402400,
							0x0018080,
							0x0824000,
							0x0030080,
							0x0080C00,
							0x2030000,
							0x0201200,
							0x0209000,
							0x0024020,
							0x0009008,
							0x0000C02,
							0x00000B0,
							0x0080600,
							0x0004820,
							0x0002090,
							0x0C02000,
							0x0002030,
							0x0203000,
							0x0082400,
							0x0002402,
							0x2402000,
							0x0003008,
							0x0412000,
							0x0006010,
							0x0406000,
							0x0012010 };

__int32 pos_pieza_c[] = {	0x4D00000,
							0x2680000,
							0x0026800,
							0x4030100,
							0x1241000,
							0x05C0000,
							0x0000134,
							0x0000059,
							0x1640000,
							0x0100C04,
							0x0004124,
							0x7400000,
							0x0013400,
							0x2018080,
							0x0009208,
							0x2E00000,
							0x000009A,
							0x00000B2,
							0x2C80000,
							0x0080602,
							0x0824800,
							0x0E80000,
							0x0806020,
							0x2482000,
							0x0002E00,
							0x000B200,
							0x0002092,
							0x003A000,
							0x7010000,
							0x0104804,
							0x1018040,
							0x0040601,
							0x00101C0,
							0x1009040,
							0x0001049,
							0x4904000,
							0x0041201,
							0x01C0400,
							0x00001D0,
							0x0000017,
							0x0000407,
							0x4024100,
							0x0403010,
							0x0012410,
							0x0017000,
							0x0016400,
							0x0412400,
							0x0007400,
							0x0038080,
							0x0824020,
							0x2030080,
							0x0080C02,
							0x2038000,
							0x0201208,
							0x0209200,
							0x0024820,
							0x0209008,
							0x0000E02,
							0x000003A,
							0x00000B8,
							0x0080E00,
							0x0804820,
							0x0E02000,
							0x0082402,
							0x0203008,
							0x0002038,
							0x2012080,
							0x0007010,
							0x0412010,
							0x0406010,
							0x0407000,
							0x0402410 };

__int32 pos_pieza_d[] = {	0x2D00000,
							0x1680000,
							0x0016800,
							0x4030080,
							0x0249000,
							0x0CC0000,
							0x0000132,
							0x0000099,
							0x0080C04,
							0x0024024,
							0x6600000,
							0x000B400,
							0x2018040,
							0x0001248,
							0x0040602,
							0x4804800,
							0x00000B4,
							0x0806010,
							0x0492000,
							0x0006600,
							0x0026400,
							0x0013200,
							0x0406020,
							0x0012012,
							0x0033000,
							0x3030000,
							0x0104820,
							0x0018180,
							0x1009008,
							0x0201201,
							0x0180600,
							0x00000F0,
							0x000001E,
							0x0000C03,
							0x0824100,
							0x000005A,
							0x0403008,
							0x0002490,
							0x0203010,
							0x2402400,
							0x0100C02,
							0x0924000,
							0x0000033,
							0x4C80000,
							0x2640000,
							0x2030100,
							0x0009009,
							0x0000198,
							0x0606000,
							0x0082410,
							0x0003030,
							0x2012010,
							0x0402402,
							0x0C03000,
							0x001E000,
							0x0003C00,
							0x0006018,
							0x0412080,
							0x0080601,
							0x0004920,
							0x1018080,
							0x1201200,
							0x00C0C00,
							0x0041208,
							0x0000606,
							0x4024020,
							0x0804804,
							0x6018000,
							0x3C00000,
							0x0780000,
							0x00300C0,
							0x0209040 };

__int32 pos_pieza_e[] = {	0x6820000,
							0x3410000,
							0x0D04000,
							0x0034100,
							0x00201A0,
							0x3208000,
							0x0980800,
							0x0000826,
							0x00080C8,
							0x02C0200,
							0x0682000,
							0x001A080,
							0x00100D0,
							0x0019040,
							0x4C04000,
							0x0000413,
							0x0010190,
							0x0580400,
							0x04C0400,
							0x4034000,
							0x0641000,
							0x0006820,
							0x0004130,
							0x0001019,
							0x1601000,
							0x0004C04,
							0x0004034,
							0x6410000,
							0x0104C00,
							0x1019000,
							0x0001601,
							0x000020B,
							0x0003410,
							0x201A000,
							0x0003208,
							0x2602000,
							0x0002098,
							0x0002032,
							0x2C02000,
							0x0002602,
							0x0806800,
							0x0C82000,
							0x000201A,
							0x0032080,
							0x0026020,
							0x0082600,
							0x2032000,
							0x0002C02,
							0x0000416,
							0x0041600,
							0x0001058,
							0x0826000,
							0x0203200,
							0x000B008,
							0x0403400,
							0x0006410,
							0x0013010,
							0x0413000,
							0x0406400,
							0x0016010,
							0x0082C00,
							0x020B000,
							0x00020B0,
							0x0416000 };

__int32 pos_pieza_f[] = {	0x6804000,
							0x3402000,
							0x0D00800,
							0x0034020,
							0x0024180,
							0x1608000,
							0x0980400,
							0x0004026,
							0x00010C8,
							0x02C1000,
							0x0184800,
							0x0020130,
							0x3210000,
							0x0680400,
							0x001A010,
							0x00120C0,
							0x000B040,
							0x4C02000,
							0x0002013,
							0x0002190,
							0x0582000,
							0x00C2400,
							0x4026000,
							0x0642000,
							0x0006804,
							0x4830000,
							0x04C0200,
							0x0000219,
							0x0000C24,
							0x6420000,
							0x0004830,
							0x2C10000,
							0x0004C02,
							0x0804C00,
							0x0219000,
							0x0001608,
							0x0C24000,
							0x0010098,
							0x0019080,
							0x3009000,
							0x0001203,
							0x00080D0,
							0x0018048,
							0x0240600,
							0x00101A0,
							0x000040B,
							0x0000816,
							0x0003402,
							0x2418000,
							0x2601000,
							0x0000432,
							0x0000612,
							0x0C84000,
							0x0002418,
							0x0016080,
							0x0026010,
							0x0402600,
							0x0432000,
							0x0002C10,
							0x0612000,
							0x2013000,
							0x0003210,
							0x0032100,
							0x0006120,
							0x6012000,
							0x0002406,
							0x101A000,
							0x0003009,
							0x0043200,
							0x1203000,
							0x0002601,
							0x0002034,
							0x0002058,
							0x0102C00,
							0x0906000,
							0x0601200,
							0x0009018,
							0x000101A,
							0x0030090,
							0x0480C00,
							0x2034000,
							0x0081600,
							0x00040B0,
							0x0483000,
							0x0013008,
							0x0086400,
							0x0003090,
							0x0006420,
							0x0C02400,
							0x0012030,
							0x0203400,
							0x0006012,
							0x2406000,
							0x0406800,
							0x040B000,
							0x0816000 };

__int32 pos_pieza_g[] = {	0x6810000,
							0x3408000,
							0x0D02000,
							0x0034080,
							0x0020190,
							0x1218000,
							0x0984000,
							0x0000426,
							0x00100C8,
							0x02C0400,
							0x0580800,
							0x0030120,
							0x3201000,
							0x0681000,
							0x001A040,
							0x00090C0,
							0x4C20000,
							0x0000213,
							0x6024000,
							0x0640200,
							0x0006810,
							0x4032000,
							0x0243000,
							0x04C2000,
							0x0002130,
							0x0002019,
							0x1602000,
							0x0002C04,
							0x0006024,
							0x6402000,
							0x0004032,
							0x2430000,
							0x0004C20,
							0x0084C00,
							0x2019000,
							0x0001602,
							0x2C04000,
							0x0018090,
							0x0019008,
							0x0000834,
							0x0008058,
							0x0000609,
							0x0900C00,
							0x00C1200,
							0x00041A0,
							0x000100B,
							0x0004806,
							0x0003408,
							0x0001218,
							0x2610000,
							0x0001098,
							0x0C04800,
							0x0C80400,
							0x0012180,
							0x0026100,
							0x0042600,
							0x3012000,
							0x0003201,
							0x0806400,
							0x0486000,
							0x0002610,
							0x0426000,
							0x0403200,
							0x000B010,
							0x0016020,
							0x0003012,
							0x0032010,
							0x0106800,
							0x100B000,
							0x0003048,
							0x4806000,
							0x0182400,
							0x00020D0,
							0x0002016,
							0x0002403,
							0x000041A,
							0x00100B0,
							0x0000C12,
							0x0480600,
							0x0609000,
							0x0834000,
							0x0201600,
							0x0024030,
							0x0002430,
							0x0013080,
							0x0213000,
							0x0602400,
							0x0006402,
							0x0083400,
							0x2016000,
							0x0006090,
							0x2403000,
							0x0C12000,
							0x041A000,
							0x0402C00,
							0x0012018 };


////////////////////////////////////////////////////////////////////////////////
int cubitos(char pieza) 
{
	switch (pieza) {
		case PIEZA_A: return CUBITOS_PIEZA_A; break;
		case PIEZA_B: return CUBITOS_PIEZA_B; break;
		case PIEZA_C: return CUBITOS_PIEZA_C; break;
		case PIEZA_D: return CUBITOS_PIEZA_D; break;
		case PIEZA_E: return CUBITOS_PIEZA_E; break;
		case PIEZA_F: return CUBITOS_PIEZA_F; break;
		case PIEZA_G: return CUBITOS_PIEZA_G; break;
		default: return 0; break;
	}
}	

////////////////////////////////////////////////////////////////////////////////
string trasladar(string cubo, ejes e, int inc, char pieza)
{
	string nuevo = cubo;
	int i;
	switch (e) {
	case X:
		switch (inc) {
		case -1:
			for (i = 0; i < DIM; i++) 
				if ((i - 2) % LADO != 0) 
					nuevo[i] = cubo[i + 1];
				else
					nuevo[i] = V;
			break;

		case 1:
			for (i = 0; i < DIM; i++) 
				if (i % LADO != 0) 
					nuevo[i] = cubo[i - 1];
				else
					nuevo[i] = V;
			break;

		default:
			break;
		}
		break;

	case Y:
		switch (inc) {
		case -1:
			for (i = 0*LADO; i < 2*LADO; i++) 
				nuevo[i] = cubo[i + LADO];
			for (i = 2*LADO; i < 3*LADO; i++) 
				nuevo[i] = V;
			for (i = 3*LADO; i < 5*LADO; i++) 
				nuevo[i] = cubo[i + LADO];
			for (i = 5*LADO; i < 6*LADO; i++) 
				nuevo[i] = V;
			for (i = 6*LADO; i < 8*LADO; i++) 
				nuevo[i] = cubo[i + LADO];
			for (i = 8*LADO; i < 9*LADO; i++) 
				nuevo[i] = V;
			break;

		case 1:
			for (i = 0*LADO; i < 1*LADO; i++) 
				nuevo[i] = V;
			for (i = 1*LADO; i < 3*LADO; i++) 
				nuevo[i] = cubo[i - LADO];
			for (i = 3*LADO; i < 4*LADO; i++) 
				nuevo[i] = V;
			for (i = 4*LADO; i < 6*LADO; i++) 
				nuevo[i] = cubo[i - LADO];
			for (i = 6*LADO; i < 7*LADO; i++) 
				nuevo[i] = V;
			for (i = 7*LADO; i < 9*LADO; i++) 
				nuevo[i] = cubo[i - LADO];
			break;

		default:
			break;
		}
		break;

	case Z:
		int i;
		switch (inc) {
		case -1:
			for (i = 0*LADO; i < 6*LADO; i++) 
				nuevo[i] = cubo[i + 3*LADO];
			for (i = 6*LADO; i < 9*LADO; i++) 
				nuevo[i] = V;
			break;

		case 1:
			for (i = 0*LADO; i < 3*LADO; i++) 
				nuevo[i] = V;
			for (i = 3*LADO; i < 9*LADO; i++) 
				nuevo[i] = cubo[i - 3*LADO];
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
	// chequear que la pieza no sale del cubo
	if (count(nuevo.begin(), nuevo.end(), pieza) == cubitos(pieza))
		return nuevo;
	else
		return "";
}

////////////////////////////////////////////////////////////////////////////////
string rotar(string cubo, ejes e)
{
	string nuevo = cubo;
	
	switch (e) {
	case X:
		nuevo.replace(0*LADO, LADO, cubo.substr(6,LADO));
		nuevo.replace(1*LADO, LADO, cubo.substr(15,LADO));
		nuevo.replace(2*LADO, LADO, cubo.substr(24,LADO));
		nuevo.replace(3*LADO, LADO, cubo.substr(3,LADO));
		//nuevo.replace(4*LADO, LADO, cubo.substr(12,LADO));	se mantiene igual
		nuevo.replace(5*LADO, LADO, cubo.substr(21,LADO));
		nuevo.replace(6*LADO, LADO, cubo.substr(0,LADO));
		nuevo.replace(7*LADO, LADO, cubo.substr(9,LADO));
		nuevo.replace(8*LADO, LADO, cubo.substr(18,LADO));
		break;

	case Y:
		nuevo[0] = cubo[18];
		nuevo[1] = cubo[9];
		nuevo[2] = cubo[0];
		nuevo[3] = cubo[21];
		nuevo[4] = cubo[12];
		nuevo[5] = cubo[3];
		nuevo[6] = cubo[24];
		nuevo[7] = cubo[15];
		nuevo[8] = cubo[6];
		nuevo[9] = cubo[19];
		nuevo[10] = cubo[10];
		nuevo[11] = cubo[1];
		nuevo[12] = cubo[22];
		nuevo[13] = cubo[13];
		nuevo[14] = cubo[4];
		nuevo[15] = cubo[25];
		nuevo[16] = cubo[16];
		nuevo[17] = cubo[7];
		nuevo[18] = cubo[20];
		nuevo[19] = cubo[11];
		nuevo[20] = cubo[2];
		nuevo[21] = cubo[23];
		nuevo[22] = cubo[14];
		nuevo[23] = cubo[5];
		nuevo[24] = cubo[26];
		nuevo[25] = cubo[17];
		nuevo[26] = cubo[8];
		break;

	case Z:
		nuevo[0] = cubo[2];
		nuevo[1] = cubo[5];
		nuevo[2] = cubo[8];
		nuevo[3] = cubo[1];
		nuevo[4] = cubo[4];
		nuevo[5] = cubo[7];
		nuevo[6] = cubo[0];
		nuevo[7] = cubo[3];
		nuevo[8] = cubo[6];
		nuevo[9] = cubo[11];
		nuevo[10] = cubo[14];
		nuevo[11] = cubo[17];
		nuevo[12] = cubo[10];
		nuevo[13] = cubo[13];
		nuevo[14] = cubo[16];
		nuevo[15] = cubo[9];
		nuevo[16] = cubo[12];
		nuevo[17] = cubo[15];
		nuevo[18] = cubo[20];
		nuevo[19] = cubo[23];
		nuevo[20] = cubo[26];
		nuevo[21] = cubo[19];
		nuevo[22] = cubo[22];
		nuevo[23] = cubo[25];
		nuevo[24] = cubo[18];
		nuevo[25] = cubo[21];
		nuevo[26] = cubo[24];
		break;
	
	default:
		break;
	}
	return nuevo;
}

////////////////////////////////////////////////////////////////////////////////
string rotar(string cubo, ejes e, int n)
{
	for (int i=0; i<n; i++)
		cubo = rotar(cubo, e);
	return cubo;
}

////////////////////////////////////////////////////////////////////////////////
__int32 convertir_a_nro(string pieza)
{
	__int32 nro = 0;
	for (int i=0; i < DIM; i++) 
		if (pieza[DIM-1-i] != V)
			nro += pow(2,i);
	return nro;
}

////////////////////////////////////////////////////////////////////////////////
string convertir_a_letra(__int32 pieza, char letra)
{
	__int32 masc = 1;
	string letras = VACIO;
	for (int i=0; i < DIM; i++) {
		if ((pieza & masc) == masc) 
			letras[DIM-1-i] = letra;
		masc = masc << 1;
	}
	return letras;
}

////////////////////////////////////////////////////////////////////////////////
class ccubo {
private:
	__int32 m_iPieza_a;
	__int32 m_iPieza_b;
	__int32 m_iPieza_c;
	__int32 m_iPieza_d;
	__int32 m_iPieza_e;
	__int32 m_iPieza_f;
	__int32 m_iPieza_g;
	string m_sLetras;

protected:
	string fusionar(string dest, string src)
	{
		for (int i = 0; i < DIM; i++)
			if (src[i] != V)
				dest[i] = src[i];
		return dest;
	}

public:
	ccubo() { reiniciar(); }

	__int32 libres() { 
		return m_iPieza_a | m_iPieza_b | m_iPieza_c | m_iPieza_d | m_iPieza_e | m_iPieza_f | m_iPieza_g; 
	}
	__int32 &pieza_a() { return m_iPieza_a; }
	__int32 &pieza_b() { return m_iPieza_b; }
	__int32 &pieza_c() { return m_iPieza_c; }
	__int32 &pieza_d() { return m_iPieza_d; }
	__int32 &pieza_e() { return m_iPieza_e; }
	__int32 &pieza_f() { return m_iPieza_f; }
	__int32 &pieza_g() { return m_iPieza_g; }	

	string letras() { 
		// convertir cada pieza a letras y fusionarla en un solo string
		m_sLetras = convertir_a_letra(m_iPieza_a,PIEZA_A);
		m_sLetras = fusionar(m_sLetras, convertir_a_letra(m_iPieza_b,PIEZA_B));
		m_sLetras = fusionar(m_sLetras, convertir_a_letra(m_iPieza_c,PIEZA_C));
		m_sLetras = fusionar(m_sLetras, convertir_a_letra(m_iPieza_d,PIEZA_D));
		m_sLetras = fusionar(m_sLetras, convertir_a_letra(m_iPieza_e,PIEZA_E));
		m_sLetras = fusionar(m_sLetras, convertir_a_letra(m_iPieza_f,PIEZA_F));
		m_sLetras = fusionar(m_sLetras, convertir_a_letra(m_iPieza_g,PIEZA_G));
		return m_sLetras; 
	}

	void reiniciar() { 
		m_iPieza_a = m_iPieza_b = m_iPieza_c = m_iPieza_d = m_iPieza_e = m_iPieza_f = m_iPieza_g = 0;
		m_sLetras = "";
	}

	void mostrar() {
		cout << letras() << endl;

		cout <<  convertir_a_letra(m_iPieza_a,PIEZA_A) << endl;
		cout <<  convertir_a_letra(m_iPieza_b,PIEZA_B) << endl;
		cout <<  convertir_a_letra(m_iPieza_c,PIEZA_C) << endl;
		cout <<  convertir_a_letra(m_iPieza_d,PIEZA_D) << endl;
		cout <<  convertir_a_letra(m_iPieza_e,PIEZA_E) << endl;
		cout <<  convertir_a_letra(m_iPieza_f,PIEZA_F) << endl;
		cout <<  convertir_a_letra(m_iPieza_g,PIEZA_G) << endl;
		cout << endl;
	}
};

////////////////////////////////////////////////////////////////////////////////
int indice(string str)
// devuelve el indice en que se encuentra str en pos_pieza_a[], -1 si no lo encuentra
{
	__int32 nro = convertir_a_nro(str);
	for (int i = 0; i < POSICIONES_PIEZA_A; i++)
		if (pos_pieza_a[i] == nro)
			return i;
	return -1;
}

////////////////////////////////////////////////////////////////////////////////
struct ubicacion {
	string pos_original;
	string pos;
	ejes eje;
	int veces;
};

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	queue<ubicacion> que_input;
	string pos;

	cin >> pos;
	while ((pos != "") && !cin.eof()) {
		ubicacion pos_a;
		pos_a.pos_original = pos;
	
		// rotar a lo largo del eje X hasta 3 veces, luego el Y y luego el Z
		pos_a.pos = pos;
	
		int i, veces = 0;
		ejes eje;
		while (((i = indice(pos_a.pos)) == -1) && (veces < 9)) {
			veces++;
			pos_a.pos = rotar(pos_a.pos_original, eje = (ejes)int((veces-1)/3), veces);
		}
		if (i == -1) return -1;		// termina REVISAR!!
		pos_a.eje = eje;
		if (veces == 0) pos_a.veces = 0;
		else 
			if ((veces - 3*eje) % 3 == 0) pos_a.veces = 3;
			else
				pos_a.veces = (veces - 3*eje) % 3;
		cout << pos_a.eje << endl << pos_a.veces << endl; // quitaR
		que_input.push(pos_a);
		cin >> pos;
	}

	// resolver el cubo para cada entrada de que_input
	while (!que_input.empty()) {
		ubicacion pos_a = que_input.front();
		que_input.pop();	// descartar el valor leido
		ccubo cubo;
		cubo.reiniciar();
		cubo.pieza_a() = convertir_a_nro(pos_a.pos);
		for (int pb = 0; pb < POSICIONES_PIEZA_B; pb++) {
			if ((cubo.libres() & pos_pieza_b[pb]) == 0) {
				cubo.pieza_b() = pos_pieza_b[pb];
				for (int pc = 0; pc < POSICIONES_PIEZA_C; pc++) {
					if ((cubo.libres() & pos_pieza_c[pc]) == 0) {
						cubo.pieza_c() = pos_pieza_c[pc];
						for (int pd = 0; pd < POSICIONES_PIEZA_D; pd++) {
							if ((cubo.libres() & pos_pieza_d[pd]) == 0) {
								cubo.pieza_d() = pos_pieza_d[pd];
								for (int pe = 0; pe < POSICIONES_PIEZA_E; pe++) {
									if ((cubo.libres() & pos_pieza_e[pe]) == 0) {
										cubo.pieza_e() = pos_pieza_e[pe];
										for (int pf = 0; pf < POSICIONES_PIEZA_F; pf++) {
											if ((cubo.libres() & pos_pieza_f[pf]) == 0) {
												cubo.pieza_f() = pos_pieza_f[pf];
												for (int pg = 0; pg < POSICIONES_PIEZA_G; pg++) {
													if ((cubo.libres() & pos_pieza_g[pg]) == 0) {
														cubo.pieza_g() = pos_pieza_g[pg];
														// cubo resuelto!
														// invertir la rotacion y mostrarlo
														if (pos_a.veces > 0) {
															string cubo_rotado = cubo.letras();
															cubo_rotado = rotar(cubo_rotado, pos_a.eje, 4-pos_a.veces);
															cout << cubo_rotado << endl;
														} else
															cout << cubo.letras() << endl;
														cubo.pieza_g() = 0;
													}
												}
												cubo.pieza_f() = 0;
											}
										}
										cubo.pieza_e() = 0;
									} 
								}
								cubo.pieza_d() = 0;
							} 
						}
						cubo.pieza_c() = 0;
					} 
				}
				cubo.pieza_b() = 0;
			} 
		}
		cubo.pieza_b() = 0;
		cout << endl;
	}
	return 0;
}

