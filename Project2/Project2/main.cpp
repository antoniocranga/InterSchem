#include<SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <string.h>
#include <cstring>
#include <queue>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <dirent.h>
#define infinit INT_MAX
#define epsi 0.0001
#define  MAX 100
#define MAX1 20
#include "Button.h"
using namespace std;
using namespace sf;
string structuraCitita;
string Globaltext;
int litera[26];
int top1, top2, OKY = 0; // varfurile celor doua stive

double Opd[100]; // stiva operanzilor
char Op[100]; // stiva operatorilor

char OperatiiBinare[200] = "+-*/^<>=#&|$mM";
char OperatiiUnare[200] = "scareltNfCTR";
char Operatii[200] = "+-*/^<>=#scarelt&|$mMNfCTR";

char expresie[300];
//char despartire[300][20];
int d = 1;

struct functie
{
	char expresie[300];
	char vect[MAX + 1][MAX1];
	int lung; // lungimea efectiva a vectorului
}F;
void afisareEroare(int n, int i)
{
	switch (n)
	{
	case 0: cout << "Paranteza inchisa fara a fi deschisa precedent" << "   POZITIA: " << i; break;
	case 1: cout << "Dupa functie trebuie sa urmeze ''(''" << "   POZITIA: " << i; break;
	case 2: cout << "Lipseste operatia intre cele doua valori" << "   POZITIA: " << i; break;
	case 3: cout << "Doua operatii una langa alta " << "   POZITIA: " << i; break;
	case 4: cout << "Paranteza inchisa cand se astepta o valoare" << "   POZITIA: " << i; break;
	case 5: cout << "Paranteza deschisa fara inchiderea acesteia" << "   POZITIA: " << "????"; break;
	case 6: cout << "Functia trebuie sa se termine cu o valoare, nu operand" << "   POZITIA: " << i; break;
	case 7: cout << "Paranteza deschisa fara inchiderea acesteia inainte de comparatie" << "   POZITIA: " << "????"; break;
	case 8: cout << "Inainte de comparatie trebuie sa se afle o valoare, nu operand" << "   POZITIA: " << i; break;
	case 9: cout << "Lipseste operandul inaintea parantezei" << "   POZITIA: " << i; break;
	case 10: cout << "Parantezare incorecta inainte de '',''" << "   POZITIA: " << i; break;
	case 11: cout << "Functia trebuie sa aiba o singura '',''" << "   POZITIA: " << i; break;
	case 12: cout << "Inainte de '','' nu trebuie sa fie o operatie" << "   POZITIA: " << i; break;
	case 13: cout << "Folosire incorecta a '',''" << "   POZITIA: " << i; break;
	case 14: cout << "Dupa paranteza deschisa nu trebuie sa urmeze o operatie" << "   POZITIA: " << i; break;
	case 15: cout << "Caracter fara semnificatie " << "   POZITIA: " << i; break;
	case 16: cout << "Functie max/min fara al doilea argument"; break; //<< "   POZITIA: " << i; break;
	// case 4: cout << "" << "   POZITIA: " << i; break;
	// case 4: cout << "" << "   POZITIA: " << i; break;
	default: cout << "FUNCTIE GRESITA"; break;

	}
}
void expresieValida(char e[300])
{
	bool op = true;
	bool var = false;
	bool corecta = true;
	bool virgula = false;
	bool cazMinMax = false;
	int nrVirgule = 0;
	int eroare = -1;
	stack<int > paranteze;
	//initializeaza(paranteze);
	stack <int > stivaM;
	//initializeaza(stivaM);
	int i;
	F.vect[0][0] = '(';
	for (i = 0; i < strlen(e) && corecta; i++)
	{
		if (i == 0 && (e[i] == '-' || e[i] == '+' || e[i] == '~'))
		{
			op = true; var = false;
			if (e[i] != '-')F.vect[d++][0] = e[i];
			else F.vect[d++][0] = 'N';
		}
		else if (e[i] == '(' || e[i] == '[' || e[i] == '{')
		{
			if (var == true) { corecta = false; eroare = 9; break; }
			paranteze.push(e[i]); F.vect[d++][0] = e[i];
			if (e[i + 1] == '-' || e[i + 1] == '+' || e[i + 1] == '~')
			{
				if (e[i + 1] != '-')F.vect[d++][0] = e[i + 1];
				else F.vect[d++][0] = 'N';
				i++;
			}
			if (strchr("*/^%&|", e[i + 1])) { corecta = false; eroare = 14; i++; break; }
		}
		else if (e[i] == ')')
		{
			if (op == true) { corecta = false; eroare = 4; break; }
			if (paranteze.top() == '(') { paranteze.pop(); F.vect[d++][0] = e[i]; }
			else { corecta = false; eroare = 0; break; }
		}
		else if (e[i] == ']')
		{
			if (op == true) { corecta = false; eroare = 4; break; }
			if (paranteze.top() == '[') { paranteze.pop(); F.vect[d++][0] = e[i]; }
			else { corecta = false; eroare = 0; break; }
		}
		else if (e[i] == '}')
		{
			if (op == true) { corecta = false; eroare = 4; break; }
			if (paranteze.top() == '{') { paranteze.pop(); F.vect[d++][0] = e[i]; }
			else { corecta = false; eroare = 0; break; }
		}
		else if (e[i] >= '1' && e[i] <= '9')
		{
			char numar[20] = ""; int j = 0; numar[j++] = e[i];
			if (var == true) { corecta = false; eroare = 2; break; }
			var = true; op = false;
			i++;
			while (e[i] >= '0' && e[i] <= '9') { numar[j++] = e[i]; i++; }
			if (e[i] == '.')
			{
				numar[j++] = e[i];
				i++;
				if (e[i] >= '0' && e[i] <= '9')
				{
					numar[j++] = e[i];
					i++;
					while (e[i] >= '0' && e[i] <= '9') { numar[j++] = e[i]; i++; }
					i--;
				}
				else corecta = false;

			}
			else { i--; strcpy_s(F.vect[d++], numar); continue; }
			strcpy_s(F.vect[d++], numar);
		}
		else if (e[i] == '0')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			char numar[20] = ""; int j = 0; numar[j++] = e[i];
			var = true; op = false;
			i++;
			if (e[i] == '.')
			{
				numar[j++] = e[i];
				i++;
				if (e[i] >= '0' && e[i] <= '9')
				{
					numar[j++] = e[i];
					i++;
					while (e[i] >= '0' && e[i] <= '9') { numar[j++] = e[i]; i++; }
					i--;
				}
				else corecta = false;

			}
			else { i--; strcpy_s(F.vect[d++], numar); continue; }
			strcpy_s(F.vect[d++], numar);
		}
		else if (strchr("-+*/^%&|", e[i]))
		{
			if (!var) { corecta = false; eroare = 3; break; }
			op = true; var = false;
			F.vect[d++][0] = e[i];
			if (e[i + 1] == '~') { i++; F.vect[d++][0] = e[i]; } continue;
		}
		else if (e[i] == 'e' && !((e[i + 1] >= 'a' && e[i + 1] <= 'z') || (e[i + 1] >= 'A' && e[i + 1] <= 'Z') || (e[i + 1] >= '0' && e[i + 1] <= '9')))
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = true; op = false;
			strcpy_s(F.vect[d++], "2.71828182");
		}
		else if (e[i] == 'p' && e[i + 1] == 'i')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = true; op = false;
			strcpy_s(F.vect[d++], "q");
			i++;
		}
		else if (e[i] == 's' && e[i + 1] == 'i' && e[i + 2] == 'n')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 3] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "s");
			i += 2;
		}
		else if (e[i] == 'c' && e[i + 1] == 'o' && e[i + 2] == 's')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 3] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "c");
			i += 2;
		}
		else if (e[i] == 't' && e[i + 1] == 'a' && e[i + 2] == 'n')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 3] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "t");
			i += 2;
		}
		else if (e[i] == 'l' && e[i + 1] == 'n')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 2] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "l");
			i++;
		}
		else if (e[i] == 'l' && e[i + 1] == 'o' && e[i + 2] == 'g')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 3] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "L");
			i += 2;
		}
		else if (e[i] == 'a' && e[i + 1] == 'b' && e[i + 2] == 's')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 3] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "a");
			i += 2;
		}
		else if (e[i] == 's' && e[i + 1] == 'q' && e[i + 2] == 'r' && e[i + 3] == 't')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 4] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "r");
			i += 3;
		}
		else if (e[i] == 'c' && e[i + 1] == 'e' && e[i + 2] == 'i' && e[i + 3] == 'l')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 4] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "C");
			i += 3;
		}
		else if (e[i] == 'f' && e[i + 1] == 'l' && e[i + 2] == 'o' && e[i + 3] == 'o' && e[i + 4] == 'r')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 5] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "f");
			i += 4;
		}
		else if (e[i] == 'r' && e[i + 1] == 'o' && e[i + 2] == 'u' && e[i + 3] == 'n' && e[i + 4] == 'd')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 5] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "R");
			i += 4;
		}
		else if (e[i] == 't' && e[i + 1] == 'r' && e[i + 2] == 'u' && e[i + 3] == 'n' && e[i + 4] == 'c')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 5] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "T");
			i += 4;
		}
		else if (e[i] == 'm' && e[i + 1] == 'a' && e[i + 2] == 'x')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 3] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "M");
			stivaM.push(paranteze.size());
			i += 2;
			virgula = true; nrVirgule++; cazMinMax = true;
		}
		else if (e[i] == 'm' && e[i + 1] == 'i' && e[i + 2] == 'n')
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = false;
			if (e[i + 3] != '(') { corecta = false; eroare = 1; break; }
			strcpy_s(F.vect[d++], "m");
			stivaM.push(paranteze.size());
			i += 2;
			virgula = true; nrVirgule++; cazMinMax = true;
		}
		else if (e[i] == ',' && cazMinMax)
		{
			if (op == true) { corecta = false; eroare = 12; break; }
			if (nrVirgule != 0) virgula = true;
			if (nrVirgule == 0 && stivaM.size() != 0) { corecta = false; eroare = 13; break; }
			if (nrVirgule == 0) { corecta = false; eroare = 11; break; } //max(8-min(6,8)+9,6-min(8-7,6))
			nrVirgule--;
			if (virgula == false) { corecta = false; eroare = 11; break; }
			else
			{
				op = true; var = false;
				if (stivaM.top() != (paranteze.size() - 1)) { corecta = false; eroare = 10; break; }
				stivaM.pop(); F.vect[d++][0] = ',';
				virgula = false; cazMinMax = false;
			}
			if (e[i + 1] == '-' || e[i + 1] == '+' || e[i + 1] == '~')
			{
				if (e[i + 1] != '-')F.vect[d++][0] = e[i + 1];
				else F.vect[d++][0] = 'N';
				i++;
			}
		}

		else if (e[i] == '<' && !(e[i + 1] == '='))
		{
			if (paranteze.size() != 0) { corecta = false; eroare = 7; break; }
			if (op == true) { corecta = false; eroare = 8; break; }
			F.vect[d++][0] = '<';
			if (!var) { corecta = false; eroare = 3; break; }
			op = true; var = false;
		}
		else if (e[i] == '>' && !(e[i + 1] == '='))
		{
			if (paranteze.size() != 0) { corecta = false; eroare = 7; break; }
			if (op == true) { corecta = false; eroare = 8; break; }
			F.vect[d++][0] = '>';
			if (!var) { corecta = false; eroare = 3; break; }
			op = true; var = false;
		}
		else if (e[i] == '=')
		{
			if (paranteze.size() != 0) { corecta = false; eroare = 7; break; }
			if (op == true) { corecta = false; eroare = 8; break; }
			F.vect[d++][0] = '=';
			if (!var) { corecta = false; eroare = 3; break; }
			op = true; var = false;
		}
		else if (e[i] == '#')
		{
			if (paranteze.size() != 0) { corecta = false; eroare = 7; break; }
			if (op == true) { corecta = false; eroare = 8; break; }
			F.vect[d++][0] = '#';
			if (!var) { corecta = false; eroare = 3; break; }
			op = true; var = false;
		}
		else if (e[i] == '<' && e[i + 1] == '=')
		{
			if (paranteze.size() != 0) { corecta = false; eroare = 7; break; }
			if (op == true) { corecta = false; eroare = 8; break; }
			strcpy_s(F.vect[d++], "<="); i++;
			if (!var) { corecta = false; eroare = 3; break; }
			op = true; var = false;
		}
		else if (e[i] == '>' && e[i + 1] == '=')
		{
			if (paranteze.size() != 0) { corecta = false; eroare = 7; break; }
			if (op == true) { corecta = false; eroare = 8; break; }
			strcpy_s(F.vect[d++], ">="); i++;
			if (!var) { corecta = false; eroare = 3; break; }
			op = true; var = false;
		}
		else if ((e[i] >= 'a' && e[i] <= 'z') || (e[i] >= 'A' && e[i] <= 'A'))
		{
			if (var == true) { corecta = false; eroare = 2; break; }
			var = false; op = true;
			int poz = i, inceput = i - 1;;
			char var[20] = "";
			int j = 0;
			var[j] = e[poz]; j++; poz++;
			while ((e[poz] >= 'a' && e[poz] <= 'z') || (e[poz] >= 'A' && e[poz] <= 'Z') || (e[poz] >= '0' && e[poz] <= '9'))
			{
				var[j] = e[poz];
				poz++; j++;
			}
			//cout << "Care este valoarea variabilei " << var << "?" << endl;
			char var2[40] = "(";
			//cout << e << endl;
			//cin.get(var2, 40); cin.get();
			//cout << var[0]-32 << " ";
			//cout << litera[var[0] - 65-32]<<endl;
			int ceva = litera[var[0] - 65 - 32], inv = 0, nr0 = 0;
			if (ceva == 0)
				strcat_s(var2, "0)");
			else {
				if (ceva % 10 == 0 && ceva > 9)
				{
					while (ceva % 10 == 0 && ceva > 9)
					{
						nr0++;
						ceva /= 10;
					}
				}

				while (ceva != 0)
				{
					inv = inv * 10 + ceva % 10;
					ceva = ceva / 10;
				}
				while (inv != 0)
				{
					int ci = inv % 10;
					if (ci == 0)
						strcat_s(var2, "0");
					else if (ci == 1)
						strcat_s(var2, "1");
					else if (ci == 2)
						strcat_s(var2, "2");
					else if (ci == 3)
						strcat_s(var2, "3");
					else if (ci == 4)
						strcat_s(var2, "4");
					else if (ci == 5)
						strcat_s(var2, "5");
					else if (ci == 6)
						strcat_s(var2, "6");
					else if (ci == 7)
						strcat_s(var2, "7");
					else if (ci == 8)
						strcat_s(var2, "8");
					else if (ci == 9)
						strcat_s(var2, "9");
					inv = inv / 10;
				}
				while (nr0 != 0)
				{
					strcat_s(var2, "0");
					nr0--;
				}
				strcat_s(var2, ")");
			}
			//cout << var2 << "          raspuns"<<endl;
			int m = strlen(var2);
			var2[m] = NULL;
			//cout << var2 << " " << endl;
			//cout << e << endl;
			//strcpy(var2,(char) (litera[var[0] - 65 - 32]));
			/*
			int y = strlen(var2);
			var2[y + 1] = ')'; var[y + 2] = NULL;
			for (int k = strlen(var2); k > 0; k--)
			{

				var2[k] = var2[k - 1];
			}
			var2[0] = '(';

			*/
			//cout << var2;
			int dim1, dim2, z = 0;
			dim1 = strlen(var); dim2 = strlen(var2);
			//cout << "cevaceva";
			if (dim1 == dim2)
			{
				while (dim1 != 0)
				{
					e[i++] = var2[z++];
					dim1--;
				}
				//cout << "Noua functie este: " << endl <<
				//cout<<endl << e << endl << endl;
			}
			else  if (dim1 > dim2)
			{
				int mut = i;
				int l = dim1 - dim2;
				while (dim2 != 0)
				{
					e[i++] = var2[z++];
					dim2--;
				}
				while (e[i] != NULL)
				{
					e[i] = e[i + l];
					i++;
				}
				//cout << "Noua functie este: " << endl <<
				//cout<<endl << e << endl << endl;
			}
			else if (dim1 < dim2)
			{
				int l = dim2 - dim1;
				for (int j = strlen(e) + l; j > poz; j--)
				{
					e[j] = e[j - l];
				}
				while (dim2 != 0)
				{
					e[i++] = var2[z++];
					dim2--;
				}
				//cout << "Noua functie este: " << endl 
				//cout<< endl << e << endl << endl;

			}
			i = inceput;
		}
		else if (e[i] == ' ') continue;
		else { corecta = false; eroare = 15; }

	}
	F.vect[d][0] = ')';
	if (corecta && paranteze.size() == 0 && !op && !nrVirgule) { //cout << "FUNCTIE CORECTA";
		OKY = 1;
	}
	else if (eroare != -1) { afisareEroare(eroare, i); }
	else {
		if (nrVirgule != 0) eroare = 16;
		else if (op) { eroare = 6; i--; }
		else if (paranteze.size() != 0) eroare = 5;
		afisareEroare(eroare, i);
	}
	cout << endl;
	//cout << "AICI SE AFISEAZA CEVA"<<e<<" ";
	e[strlen(e)] = NULL;


}
int Prioritate(char c)  // prioritate operatorilor
{
	if (c == '(' || c == ')')
		return 0;
	if (c == '+' || c == '-')
		return 1;
	if (c == '*' || c == '/')
		return 2;
	if (c == '^')
		return 3;
	if (c == '=' || c == '#' || c == '<' || c == '>' || c == '&' || c == '|' || c == '$' || c == 'm' || c == 'M')
		return 4;
	if (c == 'c' || c == 's' || c == 'l' || c == 'e' || c == 't' || c == 'a' || c == 'r' || c == 't' || c == 'f' || c == 'C')
		return 5;

}

const float pi = 3.141;

int DifInf(float x)
{
	return fabs(infinit - fabs(x)) > infinit / 2.0;
}

float Logaritm(float x)
{
	if (x > epsi && DifInf(x))
		return log(x);
	else
		return infinit;
}

float Exponential(float x)
{
	if (DifInf(x)) return exp(x);
	else return infinit;
}

float Inmultit(float x, float y)
{
	if (fabs(x < epsi) || fabs(y) < epsi) return 0;
	else if (DifInf(x) && DifInf(y)) return x * y;
	else return infinit;
}

float Putere(float x, float y)
{
	// float p;
	if (x == 0) return 0;
	else if (y == 0) return 1;
	else if (x == infinit || y == infinit) return infinit;
	else
		return pow(x, y);
}

float Egal(float x, float y)
{
	return x == y;
}

float Minim(float x, float y)
{
	if (x < y) {

		return x;
	}
	else {

		return y;

	}

}
float Maxim(float x, float y)
{
	if (x > y) {

		return x;
	}
	else {

		return y;

	}

}

float Diferit(float x, float y)
{
	return x != y;
}

float MaiMic(float x, float y)
{
	return x < y;
}

int MaiMare(float x, float y)
{
	return x > y;
}

float Plus(float x, float y)
{
	if (DifInf(x) && DifInf(y))  return x + y;
	else return infinit;
}

float Minus(float x, float y)
{
	if (DifInf(x) && DifInf(y))  return x - y;
	else return infinit;
}
float SI(int x, int y)
{
	if (DifInf(x) && DifInf(y))  return (x & y);
	else return infinit;
}
float SAU(int x, int y)
{
	if (DifInf(x) && DifInf(y))  return (x | y);
	else return infinit;
}
float XOR(int x, int y)
{
	if (DifInf(x) && DifInf(y))  return (x ^ y);
	else return infinit;
}

float Impartit(float x, float y)
{
	if (fabs(y) > epsi) return x / y;
	else
		return  infinit;


}
float Sinus(float x)
{
	if (DifInf(x))  return sin(x);
	else return infinit;
}
float   Negativ(float x)
{
	if (DifInf(x))  return (-1) * (x);
	else return infinit;
}
float Tangenta(float x)
{
	if (DifInf(x))  return tan(x);
	else return infinit;
}


float Cosinus(float x)
{
	if (DifInf(x))  return cos(x);
	else return infinit;
}

float Modul(float x)
{
	if (DifInf(x)) return fabs(x);
	else return infinit;
}

float Radical(float x)
{
	if (DifInf(x) && (x > epsi)) return sqrt(x);
	else return infinit;
}
int EsteNumar(char sir[MAX1])
{
	return (atof(sir) != 0.0 &&
		strchr("0123456789", sir[0]));
}
double ValoareFunctie(functie E)
{

	int i;
	// returneaza valoarea functiei E in punctul x
	double valo, x_1=0, x_2=0;
	//calculul expresiei
	for (i = 1; i <= 100; i++)
	{
		Opd[i] = 0;
		Op[i] = '@';
	}

	top1 = 0;
	top2 = 1;
	Op[top2] = '(';
	i = 0;
	while (i <= E.lung && top2 > 0)
	{
		//cout << "ZZZZZZZZZ" << E.lung <<"         "<< " i"  << i;
		i++;
		if (EsteNumar(E.vect[i]))
		{
			top1++;
			valo = atof(E.vect[i]);
			Opd[top1] = valo;
			//cout << "AAAAA" << "   " << Opd[top1] << endl;
		}
		else
			switch (E.vect[i][0]) {
				/* constanta pi=3.1415926 se da sub forma literei q */
			case 'q': top1++; Opd[top1] = pi; break;
			case '(': /* inceput de bloc */ top2++; Op[top2] = '('; break;
			default:
				/* operatii binare si unare */
				while ((top2 > 0) && !(strchr("()", Op[top2])) && Prioritate(Op[top2]) >= Prioritate(E.vect[i][0]))
				{
					if (top1 > 1) x_1 = Opd[top1 - 1];
					x_2 = Opd[top1];
					// cout<<"primul"<<" "<<x_1<<" "<<"aldoilea"<<x_2<<endl;
					 // depanare();
					 /* functii scrise in OPERATII */
					switch (Op[top2]) {
					case '=': valo = Egal(x_1, x_2); break;
					case '#': valo = Diferit(x_1, x_2); break;
					case '<': valo = MaiMic(x_1, x_2); break;
					case '>': valo = MaiMare(x_1, x_2); break;
					case '+': valo = Plus(x_1, x_2); break;
					case '-': valo = Minus(x_1, x_2); break;
					case '*': valo = Inmultit(x_1, x_2); break;
					case '/': valo = Impartit(x_1, x_2); break;
					case '^': valo = Putere(x_1, x_2); break;
					case 'm': valo = Minim(x_1, x_2); break;
					case 'M': valo = Maxim(x_1, x_2); break;
					case '&': valo = SI(x_1, x_2); break;
					case '|': valo = SAU(x_1, x_2); break;
					case '$': valo = XOR(x_1, x_2); break;
					case 's': valo = Sinus(x_2); break;
					case 'c': valo = Cosinus(x_2); break;
					case 'l': valo = Logaritm(x_2); break;
					case 'e': valo = Exponential(x_2); break;
					case 'a': valo = Modul(x_2); break;
					case 'N': valo = Negativ(x_2); break;
					case 'C': valo = ceil(x_2); break;
					case 'T': valo = trunc(x_2); break;
					case 'R': valo = round(x_2); break;
					case 'f': valo = floor(x_2); break;
					case 'r': valo = Radical(x_2); break;
					case 't': valo = Tangenta(x_2); break;
					}
					if (strchr(OperatiiBinare, Op[top2])) top1--;
					if (strchr(Operatii, Op[top2])) Opd[top1] = valo;
					top2--;
					//cout<<"CEVAAA"<<"     "<<Opd[1]<<endl;
				}
				//    depanare();

				if (top2 > 0)
					if ((Op[top2] != '(') || (strcmp(E.vect[i], ")")))
					{
						top2++; Op[top2] = E.vect[i][0];
					}
					else top2--;
			}
	}
	//cout << "CEVAAA" << "     " << Opd[1] << endl;

	if (top2 == 0) {
		if (Opd[1] < infinit) {
			return Opd[1];
		}
		else {
			cout << "EXPRESIE INCORECTA,NU SE POATE CALCULA REZULTATUL ";
			return 0;
		}
	}


}
Vector2f startPos;
map<int, pair<int,int>>muchii;
struct nod
{
	int id_nod;
	int x, y;
	int xLine, yLine;
	int left_x_Line, left_y_Line;
	bool isSelected;
	bool dragging;
	string val;
	string key;
	nod* urm;
	nod* st;
	nod* dr;
	bool lineDrag;
	bool leftlineDrag;
	nod()
	{
		lineDrag = false;
		isSelected = false;
		dragging = false;
		leftlineDrag = false;
		val = "";
		key = "";
	}
	void update(Vector2f mousePos, Event event)
	{
			if (x <= mousePos.x && mousePos.x <= x + val.length() * 9 && y <= mousePos.y && mousePos.y <= y + 15)
			{
		
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right && this->isSelected == false)
					this->isSelected = true, val = Globaltext;
				else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right && this->isSelected == true)
				{
					this->isSelected = false;
				}
			}
	}
	void clickedLeft(Vector2f mousePos, Event event)
	{
		
			if (x <= mousePos.x && mousePos.x <=x + val.length() * 9 && y <= mousePos.y && mousePos.y <= y + 15)
			{
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
				{
				
					dragging = true;
					startPos.x = mousePos.x - x;
					startPos.y = mousePos.y - y;
				}
				
			}
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				dragging = false;

			if (dragging)
			{
				x = mousePos.x - startPos.x;
				y = mousePos.y - startPos.y;
				
			}
			if (muchii[id_nod].first == 0)
			{
				xLine = x;
				yLine = y+20;
			}
			if (muchii[id_nod].second == 0)
			{
				left_x_Line = x;
				left_y_Line = y + 20;
			}
	}
	void dragLine(Vector2f mousePos, Event event)
	{

		if (x <= mousePos.x && mousePos.x <= x + 10 && y+ 25 <= mousePos.y + 25 && mousePos.y + 25 <= y + 50)
		{
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{

				lineDrag = true;
				startPos.x = mousePos.x - x ;
				startPos.y = mousePos.y - y - 20;
			}
		}
		if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			lineDrag = false;

		if (lineDrag)
		{
			xLine = mousePos.x - startPos.x;
			yLine = mousePos.y - startPos.y;
		}
	}
	void dragLineLeft(Vector2f mousePos, Event event)
	{

		if (x <= mousePos.x && mousePos.x <= x + 10 && y + 25 <= mousePos.y + 25 && mousePos.y + 25 <= y + 50)
		{
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
			{

				leftlineDrag = true;
				startPos.x = mousePos.x - x;
				startPos.y = mousePos.y - y - 20;
			}
		}
		if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Right)
			leftlineDrag = false;

		if (leftlineDrag)
		{
			left_x_Line = mousePos.x - startPos.x;
			left_y_Line = mousePos.y - startPos.y;
		}
	}
}*arbore;
vector<nod*>vectorNoduri;
void initArbore()
{
	arbore = nullptr;
}
vector<nod*> frontiera;
stack<nod*>lastInput;
vector<nod*>repetitieFrontiera;
stack<nod*>lastRepetitie;
vector<nod*>drumCorect;
queue<nod*>sfRepetitii;
vector<int> ADANCIME;
vector<nod*>deciziiFrontiera;
queue<nod*>sfDecizii;
stack<nod*>lastDec;

nod* functieIntrare(nod* arbore)
{
	int valoare;
	cout << "Introdu Valoarea lui " << arbore->val[0] << ":";
	cin >> valoare;
	litera[(arbore->val[0] - 65)] = valoare;
	drumCorect.push_back(arbore);
	arbore = arbore->urm;
	return arbore;
}
nod* functieDecizie(nod* arbore)
{
	int numar1 = 0;
	int numar2 = 0;
	char operatie1 = NULL, operatie2 = NULL;
	drumCorect.push_back(arbore);
	int j = 0;
	d = 1;
	string::iterator it;
	for (it = arbore->val.begin(); it != arbore->val.end(); ++it)
	{
		//cout << endl;
		//cout << *it << "  ";
		if (*it == '=' || *it == '<' || *it == '>' || *it == '%' || *it == '!')
		{

			operatie1 = *it;
			//cout << "OP!" << " " << *it<< endl;
			it++;
			if (*it == '=' || *it == '<' || *it == '>' || *it == '%')
				operatie2 = *it;
			break;
		}
	}
	for (it = arbore->val.begin(); it != arbore->val.end(); ++it)
		if (*it != '=' && *it != '<' && *it != '>' && *it != '%'&&*it != '!')
			expresie[j++] = *it;
		else {
			break;
		}
	expresie[j] = NULL;
	for (int i = 0; i < strlen(expresie); i++)
		if (expresie[i] >= 'A' && expresie[i] <= 'Z')
			expresie[i] += 32;
	expresieValida(expresie);
	F.lung = d;
	if (OKY == 1)
		numar1 = ValoareFunctie(F);
	///////////////////////////////////////////////////////////////////////////////////////
	expresie[0] = NULL;
	d = 1; j = 0;
	for (; it != arbore->val.end(); it++)
	{
		//cout << *it << " "<<endl;
		if (*it != '=' && *it != '<' && *it != '>' && *it != '%'&&*it != '!')
			expresie[j++] = *it;

	}
	expresie[j] = NULL;
	for (int i = 0; i < strlen(expresie); i++)
		if (expresie[i] >= 'A' && expresie[i] <= 'Z')
			expresie[i] += 32;
	OKY = 0;
	expresieValida(expresie);
	F.lung = d;
	//cout << "AICI E" << OKY << endl;
	int okyy = 0;
	for (int i = 0; i < strlen(expresie); i++)
		if (!(expresie[i] >= '0' && expresie[i] <= '9'))
			okyy = 1;
	if (okyy == 0)
	{
		for (int i = 0; i < strlen(expresie); i++)
		{
			if (expresie[i] == '1')
				numar2 = numar2 * 10 + 1;
			else if (expresie[i] == '2')
				numar2 = numar2 * 10 + 2;
			else if (expresie[i] == '3')
				numar2 = numar2 * 10 + 3;
			else if (expresie[i] == '4')
				numar2 = numar2 * 10 + 4;
			else if (expresie[i] == '5')
				numar2 = numar2 * 10 + 5;
			else if (expresie[i] == '6')
				numar2 = numar2 * 10 + 6;
			else if (expresie[i] == '7')
				numar2 = numar2 * 10 + 7;
			else if (expresie[i] == '8')
				numar2 = numar2 * 10 + 8;
			else if (expresie[i] == '9')
				numar2 = numar2 * 10 + 9;
			else if (expresie[i] == '0')
				numar2 = numar2 * 10 + 0;
		}
	}
	else
		if (OKY == 1)
			numar2 = ValoareFunctie(F);


	//cout << "NUMERE            " << numar1 << "    " << numar2 << endl;
	//cout << operatie1 << " " << operatie2 << "cevaaaaaaaaaaaaaaaaa";

	int op = 0;
	if (operatie1 == '>' && operatie2 == NULL)op = 1;
	else if (operatie1 == '<' && operatie2 == NULL)op = 2;
	else if (operatie1 == '>' && operatie2 == '=')op = 3;
	else if (operatie1 == '<' && operatie2 == '=')op = 4;
	else if (operatie1 == '=' && operatie2 == '=')op = 5;
	else if (operatie1 == '%' && operatie2 == NULL)op = 6;
	else if (operatie1 == '!' && operatie2 == '=')op = 7;

	switch (op)
	{
	case 1: {
		if (numar1 > numar2)arbore = arbore->st;
		else arbore = arbore->dr;
		break;
	}
	case 2: {
		if (numar1 < numar2)arbore = arbore->st;
		else arbore = arbore->dr;
		break;
	}
	case 3: {
		if (numar1 >= numar2)arbore = arbore->st;
		else arbore = arbore->dr;
		break;
	}
	case 4: {
		if (numar1 <= numar2)arbore = arbore->st;
		else arbore = arbore->dr;
		break;
	}
	case 5: {
		if (numar1 == numar2)arbore = arbore->st;
		else arbore = arbore->dr;
		break;
	}
	case 6: {
		if (numar1 % numar2 == 0)arbore = arbore->st;
		else arbore = arbore->dr;
		break;
	}
	case 7: {
		if (numar1 != numar2)arbore = arbore->st;
		else arbore = arbore->dr;
		break;
	}
	}
	return arbore;
}
nod* functieIesire(nod* arbore)
{
	drumCorect.push_back(arbore);
	if (arbore->val[0] >= 'A' && arbore->val[0] <= 'Z' && arbore->val.length() == 1)
		cout << litera[(arbore->val[0] - 65)];
	else cout << arbore->val;
	arbore = arbore->urm;
	cout << endl;
	return arbore;
}
nod* functieAtribuire(nod* arbore)
{

	drumCorect.push_back(arbore);
	if (arbore->val[1] == '=' && arbore->val[2] == '0' && arbore->val[3] == NULL)
	{
		int finalvalue = 0;
		litera[(arbore->val[0] - 65)] = 0;
		finalvalue = 0;
	}
	else {
		int j = 0;
		d = 1;
		string::iterator it;
		int finalvalue = litera[(arbore->val[0] - 65)];
		for (it = arbore->val.begin() + 2; it != arbore->val.end(); ++it)
			expresie[j++] = *it;
		expresie[j] = NULL;
		//cout << endl;
		//cout << expresie << endl;
		for (int i = 0; i < strlen(expresie); i++)
			if (expresie[i] >= 'A' && expresie[i] <= 'Z')
				expresie[i] += 32;
		expresieValida(expresie);
		F.lung = d;
		if (OKY == 1)
			finalvalue = ValoareFunctie(F);
		litera[(arbore->val[0] - 65)] = finalvalue;
	}
	arbore = arbore->urm;
	return arbore;
}
bool intraPeRepetitieIar(nod* arbore)
{

	int numar1 = 0;
	int numar2 = 0;
	char operatie1 = NULL, operatie2 = NULL;
	drumCorect.push_back(arbore);
	int j = 0;
	d = 1;
	string::iterator it;
	for (it = arbore->val.begin(); it != arbore->val.end(); ++it)
	{
		//cout << endl;
		//cout << *it << "  ";
		if (*it == '=' || *it == '<' || *it == '>' || *it == '%' || *it == '!')
		{

			operatie1 = *it;
			//cout << "OP!" << " " << *it<< endl;
			it++;
			if (*it == '=' || *it == '<' || *it == '>' || *it == '%' || *it == '!')
				operatie2 = *it;
			break;
		}
	}
	for (it = arbore->val.begin(); it != arbore->val.end(); ++it)
		if (*it != '=' && *it != '<' && *it != '>' && *it != '%' && *it != '!')
			expresie[j++] = *it;
		else {
			break;
		}
	expresie[j] = NULL;
	for (int i = 0; i < strlen(expresie); i++)
		if (expresie[i] >= 'A' && expresie[i] <= 'Z')
			expresie[i] += 32;
	expresieValida(expresie);
	F.lung = d;
	if (OKY == 1)
		numar1 = ValoareFunctie(F);
	///////////////////////////////////////////////////////////////////////////////////////
	expresie[0] = NULL;
	d = 1; j = 0;
	for (; it != arbore->val.end(); it++)
	{
		if (*it != '=' && *it != '<' && *it != '>' && *it != '%' && *it != '!')
			expresie[j++] = *it;

	}
	expresie[j] = NULL;
	for (int i = 0; i < strlen(expresie); i++)
		if (expresie[i] >= 'A' && expresie[i] <= 'Z')
			expresie[i] += 32;
	OKY = 0;
	expresieValida(expresie);
	int okyy = 0;
	for (int i = 0; i < strlen(expresie); i++)
		if (!(expresie[i] >= '0' && expresie[i] <= '9'))
			okyy = 1;
	if (okyy == 0)
	{
		for (int i = 0; i < strlen(expresie); i++)
		{
			if (expresie[i] == '1')
				numar2 = numar2 * 10 + 1;
			else if (expresie[i] == '2')
				numar2 = numar2 * 10 + 2;
			else if (expresie[i] == '3')
				numar2 = numar2 * 10 + 3;
			else if (expresie[i] == '4')
				numar2 = numar2 * 10 + 4;
			else if (expresie[i] == '5')
				numar2 = numar2 * 10 + 5;
			else if (expresie[i] == '6')
				numar2 = numar2 * 10 + 6;
			else if (expresie[i] == '7')
				numar2 = numar2 * 10 + 7;
			else if (expresie[i] == '8')
				numar2 = numar2 * 10 + 8;
			else if (expresie[i] == '9')
				numar2 = numar2 * 10 + 9;
			else if (expresie[i] == '0')
				numar2 = numar2 * 10 + 0;
		}
	}
	else
		if (OKY == 1)
			numar2 = ValoareFunctie(F);


	//cout << "NUMERE            " << numar1 << "    " << numar2 << endl;
	//cout << operatie1 << " " << operatie2 << "cevaaaaaaaaaaaaaaaaa";
	int op;
	if (operatie1 == '>' && operatie2 == NULL)op = 1;
	else if (operatie1 == '<' && operatie2 == NULL)op = 2;
	else if (operatie1 == '>' && operatie2 == '=')op = 3;
	else if (operatie1 == '<' && operatie2 == '=')op = 4;
	else if (operatie1 == '=' && operatie2 == '=')op = 5;
	else if (operatie1 == '!' && operatie2 == '=')op = 6;
	switch (op)
	{
	case 1: {
		if (numar1 > numar2)return 1;
		else return 0;
		break;
	}
	case 2: {
		if (numar1 < numar2)return 1;
		else return 0;
		break;
	}
	case 3: {
		if (numar1 >= numar2)return 1;
		else return 0;
		break;
	}
	case 4: {
		if (numar1 <= numar2)return 1;
		else return 0;
		break;
	}
	case 5: {
		if (numar1 == numar2)return 1;
		else return 0;
		break;
	}
	case 6: {
		if (numar1 != numar2)return 1;
		else return 0;
		break;
	}
	}

}
//Evaluarea structurii
void parcurgereDrumCorect(nod* arbore)
{
	
	while (arbore)
	{
		
		if (arbore->key == "Start") arbore = arbore->urm;
		else if (arbore->key == "intrare")arbore = functieIntrare(arbore);
		else if (arbore->key == "decizie")arbore = functieDecizie(arbore);
		else if (arbore->key == "iesire")arbore = functieIesire(arbore);
		else if (arbore->key == "atribuire")arbore = functieAtribuire(arbore);
		else if (arbore->key == "sfdecizie") { drumCorect.push_back(arbore); arbore = arbore->urm;}
		else if (arbore->key == "repetitie")
		{
			drumCorect.push_back(arbore);

			if (intraPeRepetitieIar(arbore) == 0)
			{
				arbore = arbore->urm;
				int contor = 1;
				while (contor)
				{
					if (arbore->key == "Start") arbore = arbore->urm;
					else if (arbore->key == "intrare")arbore = functieIntrare(arbore);
					else if (arbore->key == "iesire")arbore = functieIesire(arbore);
					else if (arbore->key == "decizie")arbore = functieDecizie(arbore);
					else if (arbore->key == "atribuire") arbore = functieAtribuire(arbore);
					else if (arbore->key == "sfdecizie") { drumCorect.push_back(arbore); arbore = arbore->urm;}
					else if (arbore->key == "sfrepetitie")
					{
						arbore = arbore->urm;
						contor--;
					}
					else if (arbore->key == "repetitie")
					{
						arbore = arbore->urm;
						contor++;
					}
				}
			}
			else {
				stack<nod*>repetitii;
				while (true)
				{

					if (arbore->key == "repetitie" && intraPeRepetitieIar(arbore))
					{
						repetitii.push(arbore);
						arbore = arbore->urm;
					}
					else
					{
						if (arbore->key == "Start") arbore = arbore->urm;
						else
						if (arbore->key == "intrare")arbore = functieIntrare(arbore);
						else if (arbore->key == "iesire")arbore = functieIesire(arbore);
						else if (arbore->key == "decizie")arbore = functieDecizie(arbore);
						else if (arbore->key == "atribuire") arbore = functieAtribuire(arbore);
						else if (arbore->key == "forcedend") { drumCorect.push_back(arbore); return; }
						else if (arbore->key == "sfrepetitie")
						{
							drumCorect.push_back(arbore);
							if (intraPeRepetitieIar(repetitii.top()))
							{
								arbore = repetitii.top();
							}
							else arbore = arbore->urm, repetitii.pop();
						}
					}
					if (repetitii.size() == 0 || arbore == NULL)break;
				}
			}
		}
	}
}
void bfsRepetitie(nod* arbore)
{
	if (!arbore)return;
	if (!arbore->st && !arbore->dr && !arbore->urm)
	{

		repetitieFrontiera.push_back(arbore);
	}
	if (arbore->urm)bfsRepetitie(arbore->urm);
	if (arbore->st)bfsRepetitie(arbore->st);
	if (arbore->dr)bfsRepetitie(arbore->dr);
}
void bfsDecizie(nod *arbore)
{
	if (!arbore)return;
	if (!arbore->st && !arbore->dr && !arbore->urm)
	{

		deciziiFrontiera.push_back(arbore);
	}
	if (arbore->urm)bfsDecizie(arbore->urm);
	if (arbore->st)bfsDecizie(arbore->st);
	if (arbore->dr)bfsDecizie(arbore->dr);
}
void removeLastNode(nod* node, nod* arbore)
{
	if (!arbore)return;
	if (arbore->st == node)
	{
		arbore->st = NULL;

		return;
	}
	else if (arbore->dr == node)
	{
		arbore->dr = NULL;
		return;
	}
	else if (arbore->urm == node)
	{
		arbore->urm = NULL;
		return;
	}
	if (arbore->urm)removeLastNode(node, arbore->urm);
	if (arbore->st)removeLastNode(node, arbore->st);
	if (arbore->dr)removeLastNode(node, arbore->dr);
}
void removeLastNode2(nod* node, nod* arbore)
{
	if (!arbore)return;
	if (arbore->st == node)
	{
		nod* newnode = new nod;
		arbore->st = NULL;
		delete(newnode);
		return;
	}
	else if (arbore->dr == node)
	{
		nod* newnode = new nod;
		arbore->dr = NULL;
		delete(newnode);
		return;
	}
	else if (arbore->urm == node)
	{
		nod* newnode = new nod;
		arbore->urm = NULL;
		delete(newnode);
		return;
	}
	if (arbore->urm)removeLastNode(node, arbore->urm);
	if (arbore->st)removeLastNode(node, arbore->st);
	if (arbore->dr)removeLastNode(node, arbore->dr);
}
void bfs(nod* arbore)
{
	if (!arbore)return;
		if (!arbore->st && !arbore->dr && !arbore->urm)
		{
			frontiera.push_back(arbore);
		}
		if (arbore->urm)bfs(arbore->urm);
		if (arbore->st)bfs(arbore->st);
		if (arbore->dr)bfs(arbore->dr);
}
int  adancime(nod* arbore)
{
	if (arbore == nullptr)return 0;
	else
	{
		int aST = adancime(arbore->st);
		int aDR = adancime(arbore->dr);
		int aURM = adancime(arbore->urm);
		return max({ aST,aDR,aURM }) + 1;
	}
}
map<nod*, int> mapa;
map<nod*, bool>vizitat;
int Ivizitat[1000];
 
void initMapaVizitat(nod* node)
{
	if (!node)return;
	vizitat[node] = false;
	if (node->urm)initMapaVizitat(node->urm);
	if (node->st)initMapaVizitat(node->st);
	if (node->dr)initMapaVizitat(node->dr);
}
//Afișare structură
void printTreeCorrect(sf::RenderWindow &window)
{
	for (auto nodCurent : vectorNoduri)
	{
		sf::Font font;
		if (!font.loadFromFile("Fonts/arial.ttf"))
			throw("Could not load font");
		sf::Text text;
		text.setFont(font);
		text.setString(nodCurent->val);
		text.setCharacterSize(12);
		RectangleShape rectangle;
		rectangle.setPosition(nodCurent->x, nodCurent->y );
		rectangle.setSize(Vector2f(nodCurent->val.length() * 9, 15));
		rectangle.setFillColor(Color::Red);
		text.setFillColor(Color::White);
		if (nodCurent->key == "decizie")
		{
			rectangle.setFillColor(Color::Cyan);
			text.setFillColor(Color::Black);
		}
		else if (nodCurent->key == "repetitie")
		{
			rectangle.setFillColor(Color::Magenta);
		}
		else if (nodCurent->key == "atribuire")
		{
			rectangle.setFillColor(Color::Blue);
			
		}
		
		text.setPosition(nodCurent->x + 1, nodCurent->y);
		CircleShape circle;
		circle.setPosition(nodCurent->x, nodCurent->y + 20);
		circle.setRadius(5);
		circle.setOutlineColor(Color::White);
		Vertex line[] =
		{
			Vertex(Vector2f(nodCurent->x + 10, nodCurent->y + 25)),
			Vertex(Vector2f(nodCurent->xLine , nodCurent->yLine)),
		};
		Vertex line1[] =
		{
			Vertex(Vector2f(nodCurent->x + 10, nodCurent->y + 25)),
			Vertex(Vector2f(nodCurent->left_x_Line , nodCurent->left_y_Line)),
		};
		for (auto x : drumCorect)
		{
			if (x == nodCurent)
			{
				rectangle.setFillColor(Color::Green);
				text.setFillColor(Color::Black);
			}
		}
		window.draw(line, 2, Lines);
		window.draw(line1, 2, Lines);
		window.draw(rectangle);
		window.draw(text);
		window.draw(circle);
	}
}
void updateCeva()
{
	for (auto nodCurent : vectorNoduri)
	{
		for (auto node : vectorNoduri)
		{ 
			
			if (node->id_nod != nodCurent->id_nod)
			{

				if (muchii[nodCurent->id_nod].first == node->id_nod)
				{
					
					nodCurent->xLine = node->x;
					nodCurent->yLine = node->y;
				}
				else
				{
					//cout << " " << node->x << " " << node->y << " " << node->xLine << " " << node->yLine << " " << nodCurent->x << " " << nodCurent->y << " " << nodCurent->xLine << " " << nodCurent->yLine << endl;

					if (node->x <= nodCurent->xLine && nodCurent->xLine <= node->x + node->val.length() * 7 && node->y <= nodCurent->yLine && nodCurent->yLine <= node->y + 15)
					{
						if (nodCurent->key != "decizie")
						{
							if (nodCurent->urm == nullptr)
							{
								nodCurent->urm = node;
								muchii[nodCurent->id_nod].first = node->id_nod;
							}
						}
						else
						{
							if (nodCurent->st == nullptr)
							{
								nodCurent->st = node;
								muchii[nodCurent->id_nod].first = node->id_nod;
							}
						}
					}
				}
			}
		}
	}
}
void updateLeft()
{
	for (auto nodCurent : vectorNoduri)
	{
		for (auto node : vectorNoduri)
		{

			if (node->id_nod != nodCurent->id_nod)
			{

				if (muchii[nodCurent->id_nod].second == node->id_nod)
				{
					nodCurent->left_x_Line = node->x;
					nodCurent->left_y_Line = node->y;
				}
				else
				{
					//cout << " " << node->x << " " << node->y << " " << node->xLine << " " << node->yLine << " " << nodCurent->x << " " << nodCurent->y << " " << nodCurent->xLine << " " << nodCurent->yLine << endl;

					if (node->x <= nodCurent->left_x_Line && nodCurent->left_x_Line <= node->x + node->val.length() * 7 && node->y <= nodCurent->left_y_Line && nodCurent->left_y_Line <= node->y + 15)
					{
						if (nodCurent->key == "decizie")
						{
							 if (nodCurent->dr == nullptr)
							{
								nodCurent->dr = node;
								muchii[nodCurent->id_nod].second = node->id_nod;
							}
						}
					}
				}
			}
		}
	}
}
bool last = 0;
nod* lastDecizie = NULL;
int op = 1;
bool intratDecizieStanga = 0;
nod* decizieStanga = NULL;
bool intratDecizieDreapta = 0;
nod* decizieDreapta = NULL;
void initCodificare();
void codificare(nod* arbore);
string codificareInC = "";
void dinStructuraînFisier(nod* arbore);
string sirFisier;
vector<string>numeFisiere;
queue<string> valori;
int IndexContor;
int id = 1;
queue<pair<int, int>>coordonateSalvare;
queue<pair<int , pair<int, int>>> SalvareMuchii;
void dinStructuraînFisier(nod *arbore)
{
	if (arbore == nullptr)
	{
		sirFisier += "$";
	}
	else
	{
		if (arbore->key == "iesire")sirFisier += "I";
		else sirFisier += arbore->key[0];
		valori.push(arbore->val);
		coordonateSalvare.push({ arbore->x , arbore->y });
		SalvareMuchii.push({ arbore->id_nod , { muchii[arbore->id_nod].first , muchii[arbore->id_nod].second } });
		dinStructuraînFisier(arbore->urm);
		dinStructuraînFisier(arbore->st);
		dinStructuraînFisier(arbore->dr);
	}
}
struct structuraSalvare
{
	string key_val;
	int x, y, id_val, stc, drc;
};
queue<structuraSalvare> salvare;
void dinFisierînStructura(string s)
{
	
	if (IndexContor < s.length())
	{
		
		if (s[IndexContor] == '$')
		{
			nod* newnode = new nod;
			newnode->st = nullptr;
			newnode->dr = nullptr;
			newnode->urm = nullptr;
			IndexContor++;
		}
		else
		{
			nod * save = new nod;
			save->st = nullptr;
			save->dr = nullptr;
			save->urm = nullptr;
			if (s[IndexContor] == 'a')
				save->key = "atribuire";
			else if (s[IndexContor] == 'i')
				save->key = "intrare";
			else if (s[IndexContor] == 'I')
				save->key = "iesire";
			else if (s[IndexContor] == 'd')
				save->key = "decizie";
			else if (s[IndexContor] == 'r')
				save->key = "repetitie";
			else if (s[IndexContor] == 's')
			{
				save->key = "sfrepetitie";
			}
			else if (s[IndexContor] == 'S')
			{
				save->key = "Start";
			}
			IndexContor++;
			if (!salvare.empty())
			{
				save->val = salvare.front().key_val; 
				save->x = salvare.front().x;
				save->y = salvare.front().y;
				save->xLine = salvare.front().x;
				save->yLine = salvare.front().y + 20;
				save->id_nod = salvare.front().id_val;
				muchii[save->id_nod].first = salvare.front().stc;
				muchii[save->id_nod].second = salvare.front().drc;
				salvare.pop();
			}
			vectorNoduri.push_back(save);
			dinFisierînStructura(s);
			dinFisierînStructura(s);
			dinFisierînStructura(s);
		}
	}
}
//Funcțiile pentru butoane
void afisareArbore(nod *arb)
{
	if (arb)
	{
		cout << arb->val << " ";
		afisareArbore(arb->st);
		afisareArbore(arb->urm);
		afisareArbore(arb->dr);
	}
}
void Button::update(const Vector2f mousePos, Event event)
{
	this->buttonStates = BTN_IDLE;
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonStates = BTN_HOVER;
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && this->clicked == false)
		{
			if (this->instructiune == "intrare")
			{
				nod* newnode = new nod;
				newnode->val = Globaltext;
				newnode->key = "intrare";
				newnode->dr = NULL;
				newnode->st = NULL;
				newnode->urm = NULL;
				newnode->x = 200;
				newnode->y = 200;
				newnode->id_nod = id++;
				newnode->xLine = 210;
				newnode->yLine = 225;
				newnode->left_x_Line = 210;
				newnode->left_y_Line = 225;
				vectorNoduri.push_back(newnode);
			}
			else if (this->instructiune == "iesire")
			{
				nod* newnode = new nod;
				newnode->val = Globaltext;
				newnode->key = "iesire";
				newnode->dr = NULL;
				newnode->st = NULL;
				newnode->urm = NULL;
				newnode->x = 200;
				newnode->y = 200;
				newnode->id_nod = id++;
				newnode->xLine = 210;
				newnode->yLine = 225; newnode->left_x_Line = 210;
				newnode->left_y_Line = 225;
				vectorNoduri.push_back(newnode);
				}
			else if (this->instructiune == "decizie") {
				nod* newnode = new nod;
				newnode->st = NULL;
				newnode->dr = NULL;
				newnode->urm = NULL; newnode->val = Globaltext;
				newnode->key = "decizie";
				newnode->x = 200;
				newnode->y = 200;
				newnode->id_nod = id++;
				newnode->xLine = 210; newnode->left_x_Line = 210;
				newnode->left_y_Line = 225;
				newnode->yLine = 225;
				vectorNoduri.push_back(newnode);
		
			}
			else if (this->instructiune == "repetitie") {
				nod* newnode = new nod;
				newnode->val = Globaltext;
				newnode->dr = NULL;
				newnode->st = NULL;
				newnode->urm = NULL;
				newnode->key = "repetitie";
				newnode->x = 200;
				newnode->y = 200;
				newnode->id_nod = id++;
				newnode->xLine = 210; newnode->left_x_Line = 210;
				newnode->left_y_Line = 225;
				newnode->yLine = 225;
				vectorNoduri.push_back(newnode);
			}
			else if (this->instructiune == "sfrepetitie") {
				nod* newnode = new nod;
				newnode->st = NULL;
				newnode->dr = NULL;
				newnode->urm = NULL; newnode->val = Globaltext;
				newnode->key = "sfrepetitie";
				newnode->val = "SfR";
				newnode->x = 200;
				newnode->y = 200;
				newnode->id_nod = id++;
				newnode->xLine = 210; newnode->left_x_Line = 210;
				newnode->left_y_Line = 225;
				newnode->yLine = 225;
				vectorNoduri.push_back(newnode);
			}
			else if (this->instructiune == "atribuire") {
				nod* newnode = new nod;
				newnode->val = Globaltext;
				newnode->key = "atribuire";
				newnode->dr = NULL;
				newnode->st = NULL;
				newnode->urm = NULL;
				newnode->x = 200;
				newnode->y = 200;
				newnode->id_nod = id++; newnode->left_x_Line = 210;
				newnode->left_y_Line = 225;
				newnode->xLine = 210;
				newnode->yLine = 225;
				vectorNoduri.push_back(newnode);
			}
			else if (this->instructiune == "executare") {
				memset(litera, 0, 27);
				drumCorect.clear();
				//afisareArbore(arbore);				
				parcurgereDrumCorect(arbore);

			}
			else if (this->instructiune == "codificare")
			{
			cout << arbore->key << endl;
				cout << "intrat";
				initCodificare();
				for (char c = 'A'; c <= 'Z'; c++)
				{
					if (litera[c - 'A'] != 0)
					{
						codificareInC += "int ";
						codificareInC += c;
						codificareInC += ";\n";
					}
				}
				codificare(arbore);
				codificareInC += "\nreturn 0;\n}";
				cout << codificareInC;
			}
			else if (this->instructiune == "salvare")
			{
			while (!valori.empty())
			{
				valori.pop();
			}
			while (!coordonateSalvare.empty())
			{
				coordonateSalvare.pop();
			}
			while (!SalvareMuchii.empty())
			{
				SalvareMuchii.pop();
			}
			dinStructuraînFisier(arbore);
			ofstream g(Globaltext);
			g << sirFisier << '\n'; 
			while (!valori.empty())g << valori.front() << " " << coordonateSalvare.front().first << " " << coordonateSalvare.front().second << " " << SalvareMuchii.front().first << " " << SalvareMuchii.front().second.first << " " <<  SalvareMuchii.front().second.second<< '\n', valori.pop() , SalvareMuchii.pop()  ,coordonateSalvare.pop();
			g.close();
			}
			else if (this->instructiune == "find")
			{
				structuraCitita.clear();
				numeFisiere.clear();
				while (!valori.empty())valori.pop();
				DIR *d;
				struct dirent *dir;
				d = opendir(".");
				if (d)
				{
					while ((dir = readdir(d)) != NULL)
					{
						string nume = dir->d_name;
						if (nume.length() > 3)
						{
							if (nume[nume.length() - 3] == 't' && nume[nume.length() - 2] == 'x' && nume[nume.length() - 1] == 't')
								numeFisiere.push_back(nume);
						}
					}
					closedir(d);
				}
				int op = 0;
				for (int i = 0; i < numeFisiere.size(); i++)
				{
					cout << i << " " << numeFisiere[i] << '\n';
				}
				cout << "Alege o optiune : ";
				cin >> op;
				cout << "\nContine:\n";
				string path = numeFisiere[op]; // ceva.txt
				ifstream f(path); // f("ceva.txt")
				string line;
				getline(f, line);
				structuraCitita = line;
				while (getline(f, line))
				{
					cout << line << endl;
					int k = 0;
					string key_val = "";
					int x = 0;
					int y = 0;
					int id_val = 0;
					int stc = 0;
					int drc = 0;
					for (int i = 0; i < line.length(); i++)
					{
						if (line[i] == ' ')k++;
						else {
							if (k == 0)
							{
								key_val += line[i];
							}
							else if (k == 1)
							{
								x = x * 10 + (line[i] - '0');

							}
							else if (k == 2)
							{
								y = y * 10 + (line[i] - '0');
							}
							else if (k == 3)
							{
								id_val = id_val * 10 + (line[i] - '0');
							}
							else if (k == 4)
							{
								stc  = stc* 10 + (line[i] - '0');
							}
							else if (k == 5)
							{
								drc = drc* 10 + (line[i] - '0');
							}
						}
					}
					//cout << x << " " << y << " " << id_val << " " << stc << " " << drc << endl;
					structuraSalvare newsave;
					newsave.key_val = key_val;
					newsave.x = x;
					newsave.y = y;
					newsave.id_val = id_val;
					newsave.stc = stc;
					newsave.drc = drc;
					salvare.push(newsave);
				}
				IndexContor = 0;
				dinFisierînStructura(structuraCitita);
				for (auto x : vectorNoduri)
				{
					if (x->key == "Start")
					{
						arbore = x;
						break;
					}
				}
				
			for (auto x : vectorNoduri)
			{
				for (auto y : vectorNoduri)
				{
					if (x != y)
					{
						if (x->key == "decizie")
						{
							if (muchii[x->id_nod].first == y->id_nod)
								x->st = y;
							else if (muchii[x->id_nod].second == y->id_nod)
								x->dr = y;
						}
						else
						{
							if (muchii[x->id_nod].first == y->id_nod)
							{
								x->urm = y;
							}
						}
					}
				}
			}
			f.close();
            }
			else if (this->instructiune == "reset")
			{
			for (int i = 0; i <= 26; i++)litera[i] = 0;
			codificareInC.clear();
			muchii.clear();
			drumCorect.clear();
			vectorNoduri.clear();
			arbore = nullptr;
			id = 1;
			}
			else if (this->instructiune == "Start")
			{
			nod* newnode = new nod;
			newnode->val = "Start";
			newnode->key = "Start";
			newnode->dr = NULL;
			newnode->st = NULL;
			newnode->urm = NULL;
			newnode->x = 200;
			newnode->y = 200;
			newnode->id_nod = id++; 
			newnode->left_x_Line = 210;
			newnode->left_y_Line = 225;
			newnode->xLine = 210;
			newnode->yLine = 225;
			vectorNoduri.push_back(newnode);
			arbore = newnode;
			}
			this->clicked = true;
		}
		else if (event.type == Event::MouseButtonReleased)this->clicked = false;
	}
	switch (this->buttonStates)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	default:
		this->shape.setFillColor(Color::Red);
		break;
	}
}
void initCodificare()
{
	codificareInC = "#include<iostream>\nusing namespace std;\n\nint main()\n{\n";
}
//Codificare din structură logică în C++
stack<nod*>Ssfdecizie;
map<nod*, int>vizitatSsf;
void initMapaViz()
{
	vizitatSsf.clear();
}
void codificare(nod* arbore)
{
	if (!arbore)
	{
		return;
	}
	else
	{
		if (arbore->key == "decizie")
		{
			codificareInC += "if(";
			codificareInC += arbore->val + ")\n";
			codificareInC += "{\n";
		}
		if (arbore->key == "iesire")
		{
			codificareInC += "cout<<";
			if (arbore->val.size() != 1)
				codificareInC += "'";
			codificareInC += arbore->val;
			if (arbore->key == "iesire" && arbore->val.size() != 1)
				codificareInC += "'";
			codificareInC += ";";
			codificareInC += "\n";
		}
		if (arbore->key == "intrare")
		{
			codificareInC += "cin>>";
			codificareInC += arbore->val;
			codificareInC += ";";
			codificareInC += "\n";
		}
		if (arbore->key == "repetitie")
		{
			codificareInC += "while(" + arbore->val + ")\n{\n";
		}
		if (arbore->key == "sfrepetitie")
		{
			codificareInC += "}";
			codificareInC += "\n";
		}
		if (arbore->key == "atribuire")
		{
			codificareInC += arbore->val + ";";
			codificareInC += "\n";
		}
		if (arbore->urm)codificare(arbore->urm);
		if (arbore->st)codificare(arbore->st);
		if (arbore->dr) {
			codificareInC += "}\n";
			codificareInC += "else\n";
			codificareInC += "{\n";
			codificare(arbore->dr);
			codificareInC += "}";
		}
	}
}
#include "Textbox.h"
int main()
{


	sf::RenderWindow window(sf::VideoMode(1200, 900), "InterSchem");
	window.setKeyRepeatEnabled(true);
	Font font;
	if (!font.loadFromFile("Fonts/arial.ttf"));
	lastInput.push(nullptr);
	while (!lastInput.empty())lastInput.pop();
	Text textFieldLabel;
	textFieldLabel.setPosition(800, 80);
	textFieldLabel.setFillColor(Color::White);
	textFieldLabel.setFont(font);
	textFieldLabel.setCharacterSize(12);
	textFieldLabel.setString("Introdu textul in caseta");

	Text textCodifcare;
	textCodifcare.setPosition(1000, 80);
	textCodifcare.setFillColor(Color::White);
	textCodifcare.setFont(font);
	textCodifcare.setCharacterSize(12);
	textCodifcare.setString("Codificare in C++");

	Text formulaInC;
	formulaInC.setPosition(1000, 170);
	formulaInC.setFillColor(Color::White);
	formulaInC.setFont(font);
	formulaInC.setCharacterSize(14);
	Text startLabel;
	Button* buttonStart = new Button(800, 660, 150, 50, &font, "Start", Color::White, Color::Yellow, Color::Red, "Start");
	Button* buttonIntrare = new Button(800, 170, 150, 50, &font, "Intrare", Color::White, Color::Yellow, Color::Red, "intrare");
	Button* buttonIesire = new Button(800, 240, 150, 50, &font, "Iesire", Color::White, Color::Yellow, Color::Red, "iesire");
	Button* buttonDecizie = new Button(800, 310, 150, 50, &font, "Decizie", Color::White, Color::Yellow, Color::Cyan, "decizie");
	Button* buttonRepetitie = new Button(800, 380, 150, 50, &font, "Repetitie", Color::White, Color::Yellow, Color::Magenta, "repetitie");
	Button* buttonSfRepetitie = new Button(800, 450, 150, 50, &font, "SfRepetitie", Color::White, Color::Yellow, Color::Magenta, "sfrepetitie");
	Button* buttonAtribuire = new Button(800, 520, 150, 50, &font, "Atribuire", Color::White, Color::Yellow, Color::Blue, "atribuire");
	Button* buttonExecutare = new Button(800, 590, 150, 50, &font, "Executare", Color::White, Color::Yellow, Color::Green, "executare");
	Button* buttonCodificare = new Button(1000, 100, 150, 50, &font, "Codificare", Color::White, Color::Yellow, Color::Black, "codificare");
	//Button* buttonStanga = new Button(800, 660, 70, 50, &font, "<<", Color::White, Color::Yellow, Color::Magenta, "stanga");
	//Button* buttonDreapta = new Button(880, 660, 70, 50, &font, ">>", Color::White, Color::Yellow, Color::Magenta, "dreapta");
	Button* buttonSalvare = new Button(800, 730, 70, 50, &font, "Salvare", Color::White, Color::Yellow, Color::Magenta, "salvare");
	Button* buttonFind = new Button(880, 730, 70, 50, &font, "Find", Color::White, Color::Yellow, Color::Magenta, "find");
	Button* buttonReset = new Button(50, 10, 50, 30, &font, "Reset", Color::White, Color::Yellow, Color::Magenta, "reset");
	Textbox textbox1(15, Color::Black, false, 800, 100, 150, 50);
	textbox1.setFont(font);
	textbox1.setPosition(800, 100);
	arbore = nullptr;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
			case Event::TextEntered:
				textbox1.typedOn(event);
			}
		}
		window.clear();
		initMapaViz();
		memset(Ivizitat, 0, 100);
		formulaInC.setString(codificareInC);
		window.draw(formulaInC);
		initMapaVizitat(arbore);
		Globaltext = textbox1.getText();
		
		for (auto x : vectorNoduri)
		{
			x->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
			x->clickedLeft(window.mapPixelToCoords(Mouse::getPosition(window)), event);
			x->dragLine(window.mapPixelToCoords(Mouse::getPosition(window)), event);
			x->dragLineLeft(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		}
		window.draw(textFieldLabel);
		window.draw(textCodifcare);
		textbox1.drawTo(window);
		textbox1.update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonIntrare->render(&window);
		buttonIntrare->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonIesire->render(&window);
		buttonIesire->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonIesire->render(&window);
		buttonIesire->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonDecizie->render(&window);
		buttonCodificare->render(&window);
		buttonCodificare->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonDecizie->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonRepetitie->render(&window);
		buttonRepetitie->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonSfRepetitie->render(&window);
		buttonSfRepetitie->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonAtribuire->render(&window);
		buttonAtribuire->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		//buttonStanga->render(&window);
		//buttonStanga->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		//buttonDreapta->render(&window);
		//buttonDreapta->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonExecutare->render(&window);
		buttonExecutare->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonSalvare->render(&window);
		buttonSalvare->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonFind ->render(&window);
		buttonFind->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		buttonReset->render(&window);
		buttonReset->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);	
		buttonStart->render(&window);
		buttonStart->update(window.mapPixelToCoords(Mouse::getPosition(window)), event);
		printTreeCorrect(window);
		frontiera.clear();
		repetitieFrontiera.clear();
		updateCeva();
		updateLeft();
		window.display();

	}
	return 0;

}