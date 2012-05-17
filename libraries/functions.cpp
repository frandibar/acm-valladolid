FUNCIONES UTILES

BIG NUMBERS

////////////////////////////////////////////////////////////////////////////////
string sumar(const string& sA, const string& sB)
// devuelve la suma de dos enteros representados como string de cualquier longitud
{
	// hacer ambos strings de igual longitud colocando ceros por delante
	string s0(abs(sA.length() - sB.length()), '0');
	string s1 = sA,
			 s2 = sB;
	if (sA.length() > sB.length()) 
		s2.insert(0, s0);
	else
		s1.insert(0,s0);

	string res(s1.length()+1, '0');
	// efectuar la suma
	int carry = 0;
	for (int i = s1.length()-1; i >= 0; i--) {
		int sum = carry + s1[i] + s2[i] - 96;	// le resto el offset ascii
		carry = (sum > 9);
		res[i+1] = sum - 10*carry + 48;
	}
	res[0] = carry + 48;
	
	// quitar el 0 del comienzo
	if (res[0] == '0') 
		return res.substr(1,res.length());
	else
		return res;
}

////////////////////////////////////////////////////////////////////////////////
void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

////////////////////////////////////////////////////////////////////////////////
string reverse(const string s)
{
	string srev(s);
	for (int i = 0, i < s.length(); i++)
		srev[i] = s[s.length()-1-i];
	return srev;
}

////////////////////////////////////////////////////////////////////////////////
void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

////////////////////////////////////////////////////////////////////////////////
string invertir(string str)
{
	for (int i = 0, j = str.length() - 1; i < j; i++, j--) {
		char aux = str[i];
		str[i] = str[j];
		str[j] = aux;
	}
	return str;
}

///////////////////////////////////////////////////////////////////////////
int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else		// found match
			return mid;
	}
	return -1;	// no match
}

////////////////////////////////////////////////////////////////////////////////
int floodfill(vector<vector<char> >& grid, int xi, int yi, char search, char replaceWith)
// returns the number of painted points
// xi: initial row, yi: initial column
{
	if (grid[xi][yi] != search) return 0;

	queue<pair<int, int> > qMissing;
	qMissing.push(make_pair(xi, yi));
	int npainted = 0;
	while (!qMissing.empty()) {
		pair<int, int> pos;
		pos = qMissing.front();
		qMissing.pop();
		// it can ocurr that I push 2 times the same thing
		if (grid[pos.first][pos.second] == search) {
			grid[pos.first][pos.second] = replaceWith;
			npainted++;
			if (pos.first-1 >= 0) {
				if (grid[pos.first-1][pos.second] == search)
					qMissing.push(make_pair(pos.first-1, pos.second));
			}
			if (pos.first+1 < grid.size()) {
				if (grid[pos.first+1][pos.second] == search)
					qMissing.push(make_pair(pos.first+1, pos.second));
			}

			if (pos.second-1 >= 0) {
				if (grid[pos.first][pos.second-1] == search)
					qMissing.push(make_pair(pos.first, pos.second-1));
			}

			if (pos.second+1 < grid[0].size()) {
				if (grid[pos.first][pos.second+1] == search)
					qMissing.push(make_pair(pos.first, pos.second+1));
			}
		}
	}
	return npainted;
}




///////////////////////////////////////////////////////////////////////////
//para convertir un nro a string de 4 digitos
string toString(int n)
{
	string s(4,'0')
	s[0] = (n / 1000) + '0';
	s[1] = ((n / 100) % 10) + '0';
	s[2] = ((n / 10) % 10) + '0';
	s[3] = n % 10 + '0';
    return s;
}



///////////////////////////////////////////////////////////////////////////
para generar cuadrados sin overflow
(i+1)^2 = i^2 + 2i + 1

	int64 r = 1;
	for (int i = 2; i < 65536; i++) {
		r += 2*i-1;
		cout << r << endl;
	}
	return 0;




cambio de base
(nro / n) % n


void diagonal_order(int n, int m)
{
	for (int d = 1; d <= (m+n-1); d++) {
		int height = 1 + max(0, d-m);
		int pcount = min(d, (n - height + 1));
		for (int j = 0; j < pcount; j++)
			cout << min(m,d)-j << " " << height+j << endl;
	}
}

/////////////////////////////////////////////////////////////////////////// 
diagonal_order(3,4) devuelve:

1 1
2 1
1 2
3 1
2 2
1 3
3 2
2 3
1 4
3 3
2 4
3 4

///////////////////////////////////////////////////////////////////////////
int suma_max(vector<int> v)
{
	int from, to;
	int suma = max = 0;
	int N = (int)v.size();
	for (int i = 0, j = 0; j < N; j++) {
	    suma += v[j];
	    if (suma < max) {
		max = suma;
		from = i;
		to = j;
	    } else if (suma < 0) {
		i = j + 1;
		suma = 0;
	    }
	 return max;
}


// PARA MOSTRAR 4 DECIMALES
#include <iomanip>		// fixed
		cout.setf(std::ios_base::fixed);
		cout.precision(4);
// para mostrar en hexa
		cout.setf(std::ios_base::hex, std::ios_base::basefield);

// para mostrar true y false como literales en vez de 0 y 1
#include <iomanip>
cout << boolalpha;	


////////////////////////////////////////////////////////////////////////////////
template<class T>
void printMatrix(const vector<vector<T> >& m)
{
	for (int i = 0; i < (int)m.size(); ++i) {
		for (int j = 0; j < (int)m[i].size(); ++j)
			cout << m[i][j] << " ";
        std::cout << std::endl;
	}
}


////////////////////////////////////////////////////////////////////////////////
int lcs(const string& s, const string& t)
// returns the length of the longest common subsecuence
{
	vector< vector<int> > m(s.length());

	// fill matrix m
	// first row
	m[0].resize(t.length());
	m[0][0] = match(t[0], s[0]);
	for (int j = 1; j < (int)t.length(); j++)
		m[0][j] = m[0][j-1] + match(s[0], t[j]);

	// first column
	for (int i = 1; i < (int)s.length(); i++) {
		m[i].resize(t.length());
		m[i][0] = m[i-1][0] + match(s[i], t[0]);
	}

	for (int i = 1; i < (int)s.length(); i++) {
		for (int j = 1; j < (int)t.length(); j++) {
			m[i][j] = std::max( std::max(m[i-1][j-1], m[i-1][j]), m[i][j-1]) + match(t[j], s[i]);
		}           
	}

#ifdef DEBUG
    // show matrix
	cout << "  ";
	for (i = 0; i < (int)t.size(); i++)
		cout << t[i] << ' ';
	cout << endl;
	for (i = 0; i < (int)s.size(); i++) {
        for (int j = 0; j < (int)t.size(); j++) {
			if (j == 0) cout << s[i] << ' ';
            cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
#endif DEBUG

	return m[s.length()-1][t.length()-1];
}

#include <sstream>
/////////////////////////////////////////////////////////////////////////// 
template<typename T> 
string toString(T n) 
{
    std::ostringstream os; 
    os << n; 
    return os.str();
}

/////////////////////////////////////////////////////////////////////////// 
template<typename T> 
T fromString(const string& s) 
{
    std::istringstream is(s); 
    T r; 
    is >> r; 
    return r;
}
/////////////////////////////////////////////////////////////////////////// 
