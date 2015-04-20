#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

void adjust_coeff(vector<double>& input_vals , vector<double>& coeffs , double final, double current) 
{
 	// coeffs may be positive or neg, maitain sign
	double error = current - final;
	int size     = coeffs.size();
	
	double acceptable_error = 0.05*final + 0.1;
	
	while (fabs(error) > acceptable_error)
	{
		int cur = rand()%size;
		double epsilon = ((double) rand() / (double)(RAND_MAX))*(fabs(0.2*coeffs[cur]));
		
		double delta;
		
		if (input_vals[cur]*error > 0) { coeffs[cur] -= epsilon; delta = -epsilon*input_vals[cur]; }
		else						   { coeffs[cur] += epsilon; delta =  epsilon*input_vals[cur]; }
		
		error += delta;
	}
}

void write_coeff_to_file(vector<double>& coeffs) 
{
    std::ofstream outfile;

    outfile.open("coeffs.txt", std::ios_base::app);

	outfile << "\n";	
	for (int i = 0 ; i<coeffs.size() ; i++)
		outfile << coeffs[i] << " ";

}

vector<double> read_coeff_from_file() 
{	
    string filename = "coeffs.txt";
	ifstream file;
	file.open(filename);
	vector<double> fin;
	
	if(file.is_open())
	{
		file.seekg(-1,ios_base::end);                // go to one spot before the EOF
		
		bool start_of_last_line = false;
		char ch;
		
		while (!start_of_last_line)
		{
			file.get(ch);
			if (ch == '\n') start_of_last_line = true;
			else file.seekg(-2,ios_base::cur);
			
		} 
		
		double temp;

		while (!file.eof())
		{
			file >> temp;
			fin.push_back(temp);
		}
			   
		file.close();
		//http://stackoverflow.com/questions/11876290/c-fastest-way-to-read-only-last-line-of-text-file
	}
	
	fin.pop_back();
	return fin;
}

int main()
{
	srand((unsigned)time(NULL));
	
	vector<double> coeffs = {2,3,-2};
	vector<double> input_vals = {5,7,3};
	
	adjust_coeff(input_vals,coeffs,0 ,25);
	
	// double final = 0;
	// for (int i = 0 ; i<coeffs.size() ; i++)
	// 	{cout << coeffs[i] << " "; final += coeffs[i]*input_vals[i] ;}
	// cout << "\n" << final <<"\n";

	// adjust_coeff(input_vals,coeffs,0 ,25);
	// write_coeff_to_file(coeffs) ;
	// adjust_coeff(input_vals,coeffs,0 ,25);
	// write_coeff_to_file(coeffs) ;
	//
	// vector<double> temp  = read_coeff_from_file();
	//
	//
	// for (int i = 0 ; i<temp.size() ; i++)
	// 	cout << temp[i] << " ";
	// cout << "\n";
}