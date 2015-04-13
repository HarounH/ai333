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
			if((int)file.tellg() <= 1) 
			{  
			    file.seekg(0);                   
			    start_of_last_line = true;      
			}
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
	
	cout << "-----------------------------\n";
	for (int i = 0 ; i<input_vals.size() ; i++)
		cout << input_vals[i] << " ";
	cout << "\n";
	for (int i = 0 ; i<input_vals.size() ; i++)
		cout << coeffs[i] << " ";
	cout << "\n";
	cout << "what it should be   : " << final << "\n";
	cout << "what it actually is : " << current << "\n";
	
	double num_of_zeros = 0.0;
	for (int i = 0 ; i<input_vals.size() ; i++)
		if (input_vals[i] == 0.0)
			num_of_zeros++;
	
	// greater the fraction of non-zero inputs => lesser the error tolerance
	double change_frac = (num_of_zeros/(double) input_vals.size());
	
	double acceptable_error = (0.1*final)/(change_frac) + 0.5;
	
	while (fabs(error) > fabs(acceptable_error))
	{
		int cur = rand()%size;
		double epsilon = ((double) rand() / (double)(RAND_MAX))*(fabs(0.1*coeffs[cur]));

		double delta;
		
		if (input_vals[cur]*error > 0) { coeffs[cur] -= epsilon; delta = -epsilon*input_vals[cur]; error += delta;}
		if (input_vals[cur]*error < 0) { coeffs[cur] += epsilon; delta =  epsilon*input_vals[cur]; error += delta;}
		//ignore if 0		
	}

	double end;
	
	for (int i = 0 ; i<input_vals.size() ; i++)
		end += input_vals[i]*coeffs[i];
	
	cout << "what it became     : " << end << "\n";
	cout << "-----------------------------\n";
}

#endif