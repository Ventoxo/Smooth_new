//////////////////////////
//Developer:Dyakov Nick //
//Date:     21.11.2019  //
//////////////////////////
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iterator>
#include <iomanip>
using namespace std;
static vector<double> massive_f;
static vector<double> massive_Buffer;


class Smooth_ 
{
	ifstream fin;
	int MAX;

	double get_el_of_vector()
	{
		double mass;
		string s;
		getline(fin, s);
		stringstream ss(s);

		ss >> mass;
		cout << mass << endl;


		return mass;
	}
	double sum_vec(vector<double> mass)
	{
		double sum_of_elems = accumulate(mass.begin(),mass.end(),0);
	
		return sum_of_elems;
	}
	double sum_vec_logic(vector<double> massive,int n,int M)
	{
		double sum_of_elems = 0;
		sum_of_elems =  (massive[n + M] - massive[n - 1 - M]) / (2 * M + 1);
		
		return sum_of_elems;
	}

	double sum_begin_of(vector<double> massive, int M)//find the first element of buffer vector
	{
		double sum_of_elems = 0;
		
		for (int i = 0; i <= M; i++) 
		sum_of_elems += massive[i];
			
		sum_of_elems = (sum_of_elems) / ( M + 1);

		return sum_of_elems;
	}

	double sum_vec_logic_less(vector<double> massive, int n, int M)
	{
		double sum_of_elems = 0;
		sum_of_elems = massive[n + M]/ ( M + 1 + n);

		return sum_of_elems;
	}

	double sum_vec_logic_more(vector<double> massive, int n, int M)
	{
		double sum_of_elems = 0;
		sum_of_elems = -(massive[n - 1 - M]) / ( M + massive.size()-n);

		return sum_of_elems;
	}

public:

	Smooth_(string file_, int M)
	{
		
		fin.open(file_);
		while (!fin.is_open())
		{
			cout << "File dont open, try again" << endl;
			//cout << "Write full adress of file:";
			//	getline(cin, file_);	
			//	cout << endl;
			//	fin.open(file_);
			getchar();
			exit(1);
		}
		
			cout << "File open" << endl;
			MAX = M;
		
	}

	~Smooth_()
	{
		fin.close();
	}

	void getvector( vector<double>& mass_vec)
	{
			
			while (!fin.eof())
			{
				mass_vec.push_back(get_el_of_vector());
				
			}			
			cout << "massive_f.size()=" << mass_vec.size() << endl;
	}
	void logic(int arg2, vector<double> mass_vec)
 {
		if ((2 * arg2 + 1) >= massive_f.size())
		{
			int opp = sum_vec(massive_f) / massive_f.size();
			for (int i = 0; i < massive_f.size(); i++)
			{
				massive_Buffer.push_back(opp);

			}
			cout << "Massive buffer:" << endl;
			std::copy(massive_Buffer.begin(), massive_Buffer.end(), ostream_iterator <int>(cout, "\n"));

		}
		else
		{
			int j=0;
			cout << "Massive buffer:" << endl;
			massive_Buffer.push_back(sum_begin_of(massive_f, arg2));
			cout << j + 1 << ":   ";
			cout << setiosflags(ios::fixed) << setprecision(2) << massive_Buffer.at(j) << endl;
			for (j = 1; j < massive_f.size(); j++)
			{
				double sum = 0;
				double sum_of = 0;

				if ((j - arg2) <= 0)
				{
					massive_Buffer.push_back( (massive_Buffer.back() * (j + arg2) / (j + arg2 + 1))+sum_vec_logic_less(massive_f, j, arg2));
				}

				else if ((j + arg2) >= massive_f.size())
				{
					massive_Buffer.push_back((massive_Buffer.back() * (arg2 + massive_f.size() - j+1) - massive_f[j - 1 - arg2])/ (arg2 + massive_f.size() - j));
					
				}
				
				else
				{
					massive_Buffer.push_back(massive_Buffer.back() + sum_vec_logic(massive_f, j, arg2));
				}
				
				
				cout << j + 1 << ":   ";
				cout << setiosflags(ios::fixed) << setprecision(2) << massive_Buffer.back() << endl;
			}
		}
	}
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	if (argc < 2)
	{
		cout << "Enter more parametrs. \nNeed 2 parametrs: \n(1)path to file - first\n(2)step of smooth - second" << endl;
		getchar();
		return 240;
	}

	const int arg2 = atoi(argv[2]);//Введена константа для удобства и сокращения времени чтения и написания кода

	Smooth_ smooth(argv[1], arg2);
	smooth.getvector(massive_f);
	cout << "massive_f.size()=" << massive_f.size() << endl;
	smooth.logic(arg2, massive_f);
	
	
	
	getchar();
	return 1;

}