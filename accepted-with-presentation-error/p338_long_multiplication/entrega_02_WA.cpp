/* @JUDGE_ID:  40922FK  338  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/******************************************************************************
 Solution to Problem 338 - Long Multiplication
 by: Francisco Dibar
 date: Dec-23-2005
******************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <sstream>	
#include <string>
#include <vector>	

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

// base types 
#ifdef WIN32 
	typedef __int8            		int8; 
	typedef __int16           		int16; 
	typedef __int32           		int32; 
	typedef __int64           		int64; 
	typedef unsigned __int8   		uint8; 
	typedef unsigned __int16  		uint16; 
	typedef unsigned __int32  		uint32; 
	typedef unsigned __int64  		uint64; 
#else 
	typedef char                    int8; 
	typedef short                   int16; 
	typedef long                    int32; 
	typedef long long int           int64; 
	typedef unsigned char           uint8; 
	typedef unsigned short          uint16; 
	typedef unsigned long           uint32; 
	typedef unsigned long long int  uint64; 
#endif 

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

#define MAX_DIGIT			10
#define MAX_LEN			MAX_DIGIT * 2 + 1
#define MAX_SEPARATOR	"--------------------"		// 2*MAX_DIGIT HYPHENS
#define MAX_ZEROS			"00000000000000000000"		// 2*MAX_DIGIT ZEROS
#define MAX_SPACE			"                    "		// 2*MAX_DIGIT SPACES


/////////////////////////////////////////////////////////////////////////// 
void reverse(string& s)
{
	for (int i = 0; i < (int)s.length()/2; i++)
		std::swap(s[i], s[s.length()-i-1]);
}

/////////////////////////////////////////////////////////////////////////// 
template<typename T> 
string to_string(T n) 
{
	std::ostringstream os; 
   os << n; 
   return os.str();
}

/////////////////////////////////////////////////////////////////////////// 
template<typename T> 
//T from_string(const string& s) 
T from_string(string s) 
{
	std::istringstream is(s); 
   T n; 
   is >> n; 
   return n;
}


////////////////////////////////////////////////////////////////////////////////
int add_digits(const vector<string>& vec_nums, int pos)
// returns the sum of digits at position pos for each entry in vec_nums
{
	int sum = 0;
	for (int i = 0; i < (int)vec_nums.size(); i++) {
		sum += vec_nums[i][pos] - '0';
	}
	return sum;
}

////////////////////////////////////////////////////////////////////////////////
string add(const vector<string>& vec_nums)
// returns the sum of each number in vec_nums
{
	string res = "";
	// calculate result
	int digits = vec_nums[0].length();
	int digit_sum = 0;
	int carry = 0;
	for (int i = digits - 1; i >= 0; i--) {
		digit_sum = add_digits(vec_nums, i);
		digit_sum += carry;
		carry = digit_sum / 10;
		digit_sum %= 10;
		res += to_string(digit_sum);
	}
	if (carry > 0) {
		res += to_string(carry);
	}
	reverse(res);

	// remove trialing ceros
	int pos = res.find_first_not_of("0");
	if (pos == (int)string::npos)
		res = "0";
	else
		res = res.substr(pos, res.length() - pos);

	return res;
}

////////////////////////////////////////////////////////////////////////////////
void multiply_by_char(const string& sx, char cy, string& result)
// x has n digits, y has only 1 digit
{
	result = "";
	int y, carry = 0;
	y = cy - '0';
	for (int i = 0; i < (int)sx.length(); i++) {
		int x = sx[sx.length() - i - 1] - '0';
		int res = x * y + carry;		
		carry = res / 10;
		res %= 10;
		result += to_string(res);				// add final digit
	}		
	
	if (carry > 0)
		result += to_string(carry);
	
	reverse(result);
}

////////////////////////////////////////////////////////////////////////////////
void multiply(int64 n1, int64 n2)
// shows multiplication of x by y
{
	string x = to_string(n1);
	string y = to_string(n2);
	string result;

	if (n1 == 0) {
		// special case when n1 = 0, avoid partial sums of 0 each
		result = "0";
		// SHOW OUTPUT
		// show x, y and first separator
		int digits = std::max(x.length(), y.length());
		string max_offset = MAX_SPACE;
		string sum1 = max_offset.substr(0, digits - x.length()) + x;
		string sum2 = max_offset.substr(0, digits - y.length()) + y;
		string res = max_offset.substr(0, digits - result.length()) + result;
		// 1st separator has same length as max length(x, y)
		string max_sep = MAX_SEPARATOR;
		string sep1 = max_sep.substr(0, digits); 
		cout << sum1 << endl << sum2 << endl << sep1 << endl << res << endl;
		return;
	}

	vector<string> vec_partial(y.length());
	// fill vec_partial with partial multiplications
	int max_len = 0;	// used for calculating offset
	int ops = y.length() - 1;
	for (int i = ops; i >= 0; i--) {
		char c = y[i];
		// do vec_partial[ops - i] = x * c;
		multiply_by_char(x, c, vec_partial[ops - i]);
		int len = vec_partial[ops - i].length() + ops - i;
		if (len > max_len) 
			max_len = len;
	}

#ifdef DEBUG
	cout << START_DEBUG;
	for (int i = 0; i < (int)vec_partial.size(); i++)
		cout << vec_partial[i] << endl;
	cout << END_DEBUG;
#endif

	// add 0's to left & right to sum with same number of digits
	vector<string> vec_partial_ceros(y.length());
	// vec_partial_ceros = vec_partial with zeros to left and right
	string right0 = "";
	for (int i = 0; i < (int)vec_partial_ceros.size(); i++) {
		string max_zeros = MAX_ZEROS;
		string num = vec_partial[i];
		num = max_zeros.substr(0, max_len - num.length() - i) + num + right0;
		vec_partial_ceros[i] = num;
		right0 += "0";
	}	

#ifdef DEBUG
	cout << START_DEBUG;
	for (int i = 0; i < (int)vec_partial_ceros.size(); i++)
		cout << vec_partial_ceros[i] << endl;
	cout << END_DEBUG;
#endif

	// obtain final result
	result = add(vec_partial_ceros);	

	// SHOW OUTPUT

	// show x, y and first separator
	int digits = std::max(x.length(), y.length());
	int tot_dig = std::max((int)result.length(), digits);
	string max_offset = MAX_SPACE;
	string sum1 = max_offset.substr(0, tot_dig - x.length()) + x;
	string sum2 = max_offset.substr(0, tot_dig - y.length()) + y;
	// 1st separator has same length as max length(x, y)
	string max_sep = MAX_SEPARATOR;
	string sep1 = max_sep.substr(0, digits); 
	sep1 = max_offset.substr(0,tot_dig - sep1.length()) + sep1;
	cout << sum1 << endl << sum2 << endl << sep1 << endl;
	

	// add left and right offset to partial results
	if (y.length() > 1) {
		string left_offset = "", right_offset = "";
		// contains formated
		for (int i = 0; i < (int)y.length(); i++) {
			left_offset = max_offset.substr(0,tot_dig - vec_partial[i].length() - i);
			string partial = left_offset + vec_partial[i] + right_offset;
			cout << partial << endl;
			right_offset += " ";
		}
	}
	// show partial results and 2nd separator
	if (vec_partial.size() > 1) {
		string sep2 = max_sep.substr(0, result.length()); 
		cout << sep2 << endl;
	}
	// finally show result
	string res = max_offset.substr(0, tot_dig - result.length()) + result;
	cout << res << endl;

}

////////////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redirect input and output
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output.txt"))->rdbuf()); 
	#endif 

	int64 x, y;
	cin >> x >> y;	
	while (!cin.eof()) {

		// PROCESS
		multiply(x, y);
		
		// READ NEXT INPUT
		cin >> x >> y;
		if (!cin.eof())
			cout << endl;
	}
	
	return 0;
}
