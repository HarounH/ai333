#ifndef LEARNING_CPP
#define LEARNING_CPP

#include <fstream> 
/* Learning version of minimax , along with support for adjust coefficients. */
/* Unimplemented. */


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

void write_coeff_to_file(vector<double>& coeffs) 
{
    std::ofstream outfile;

    outfile.open("coeffs.txt", std::ios_base::app);
	
	outfile << "\n";
	for (int i = 0 ; i<coeffs.size() ; i++)
		outfile << coeffs[i] << " ";
}

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

#endif