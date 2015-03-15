#ifndef LEARNTOOL_CPP
#define LEARNTOOL_CPP

class LearnTool
{
	public:
		adjustCoeff(vector<double>& coeff, vector<double>& val, double cur, double final);
		
};

LearnTool::adjustCoeff(vector<double>& coeff, vector<double>& val, double cur, double final)
{
 	// coeffs may be positive or neg, maitain sign
	double error = final - cur;
	int size     = coeff.size();
	
	double acceptable_error = 0.05*final;
	
	while (error > acceptable_error)
	{
		
	}
	
}

#endifs