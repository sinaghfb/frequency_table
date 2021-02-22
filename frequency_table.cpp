// the last.cpp : Defines the entry point for the application.
//

#include<bits/stdc++.h>

using namespace std;
//you can change the maximum number rows here 
const int STEP = 20;

class chart_maker
{
public:
	//save data user given 
	vector<double> data0;
	//save chart 
	double chart[STEP][11];
	//init the class
	 chart_maker();
	//getting data from user 
	void get_data();
	//sort data 
	void sort();
	//fill the chart 
	void chart_calculator();
	//calculate basics of chart 
	void chart_init();
	//calculate extra data for data like variance and ...
	void calculator();
	//print the chart and other data 
	void printer();
	//calculate number of fraction digits
	void fraction_calculator();
private:
	int fraction , count ,k;
	double xmax, xmin, l, r ,ave;
	double variance, mod, median, std_deviation, Skewness , Kurtosis;
};

 chart_maker::chart_maker()
{
	cout<<"\nRules:\n"
"I used g++ compiler for other compiler you need change header files\n"
"Maxmum fraction digits is 6 you can multiply number to reduce number of digits\n"
"maximum data is 10000 depending on cpu \n"
"maximum rows for table is 20 you can change in on code with modifing STEP value\n"
"if you using on file option dont put empty line in file you gettinh error"
"This code is under the license of MIT\n\n";


	 for (int i = 0; i < STEP; i++)
		 for (int j = 0; j < 11; j++)
			 chart[i][j] = 0;
}


 void chart_maker::get_data()
 {
	 //this function get data from user 
	 cout << "Enter your input method :\n1.On file \n2.On console\n or press any other key exit\n";
	 if (cin.peek() == '1')
	 {
		 //
		 string myText;
		  double *data=new double;
		 ofstream create_file("input_data.txt");
		 create_file.close();
		 cout << "Enter your data in input_data.txt then press any key to continue\nenter 1 data on every line ";
		 cin.clear();
		 cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		 cin.get();
		 // Read from the text file
		 fstream MyReadFile("input_data.txt");
		 // Use a while loop together with the getline() function to read the file line by line
		 while (getline(MyReadFile, myText)) {
		 // Output the text from the file				 
			 try
			 {
				 *data = stod(myText);
				 cout << *data<<"\r";
				 data0.push_back(*data);
				 
			 }
			 catch (...)
			 {
				 cout << "\nsome inputs are not number check your file and try again\n";
				 exit(EXIT_SUCCESS);

			 }


		 }
		 MyReadFile.close();
	 }
	 else if(cin.peek() == '2')
	 {
		 string input;
		 double* data = new double;
		 cout << "Enter your data then press enter when your data ends enter 'e'\n " << endl;
		 while (cin.peek() != 'e')
		 {
			 cin >> input;
			 try
			 {
				 *data = stof(input);
				 data0.push_back(*data);
			 }
			 catch (...)
			 {
				 cout << "its not number try again";
			 }
			 input.clear();
			 cin.clear();
			 cout << *data;
			 cout << "\nEnter your data then press enter when your data ends enter 'e'\n " << endl;
		 }
		 delete data;
	 }
	 else
		exit(EXIT_SUCCESS);
	 count = data0.size();
 }


 void chart_maker::sort()
 {
	 //this function sorts data with comb algorithm if u change with faster algorithm you can use more data but its good for under 10000 data 
	 double* temp = new double;
	 for (int i = 0; i < data0.size(); i++)
		 for (int j = i + 1; j < data0.size(); j++)
			 if (data0[i] > data0[j])
			 {
				 *temp = data0[i];
				 data0[i] = 0;
				 data0[i] = data0[j];
				 data0[j] = 0;
				 data0[j] = *temp;
			 }
		 
	 
	 delete temp;
 }


 void chart_maker::fraction_calculator()
 {
	 //this function caculate number of fractions digit we use it for rounding 
	 fraction = 0;
	 for (int i = 0; i < count; i++)
	 {
		 long double tmp = data0[i];
		 stringstream ss;
		 ss << (tmp - int(tmp));;
		 string s;
		 ss >> s;
		 if (int(s.size() - 2) > fraction)
			fraction = s.length() - 2;
	 }
	 if (fraction < 0)
		fraction = 0;
 }

 void chart_maker::chart_calculator()
 {
	 //this function caculate necessary values for making chart 
	 double* temp = new double;
	 string length;
	 stringstream ss;

	 *temp = pow(0.1, fraction);

	 xmin = double(data0[0] - (*temp / 2));
	 xmax = double(data0[count - 1] + (*temp / 2));
	 r = xmax - xmin;
	 k = round(1 + (3.32 * log10(count)));
	 l = (r / k);
	 *temp = xmin;

	 for (int i = 0; i < k; i++)
	 {
		 *temp = *temp + l;
		 if (i == k - 1 && *temp < xmax)
		 {
			 k = k - 1;
			 i = 0;
			 l = (r / k);
		 }
	 }

	 ss << setprecision(fraction) <<l;
	 ss >> length;
	 l = stod(length);
	 delete temp;
 }

 void chart_maker::chart_init()
 {
	 //this function fill the array with chart values 
	 double* xi = new double;
	 double* fi = new double;
	 double* Fi = new double;
	 double* down_range = new double;
	 double* up_range = new double ;
	 *down_range = xmin;
	 *Fi = 0;
	 ave = 0;

	 for (int i = 0; i < k; i++)
	 {
		 *fi = 0;
		 chart[i][0] = *down_range;
		 *up_range = *down_range + l;
		 chart[i][1] = *up_range;
		 for (int i = 0; i < count; i++)
		 {
			 if (data0[i] <= *up_range && data0[i] > *down_range)
			 {
				 *fi = *fi + 1;
				 *Fi = *Fi + 1;
			 }
		 }

		 *xi = (*down_range + *up_range) / 2;
		 chart[i][2] = *xi;
		 chart[i][3] = *fi;
		 chart[i][4] = *Fi;
		 chart[i][5] = (*fi	/	count);
		 chart[i][6] = (*Fi / count);
		 ave = ave + ((*fi) * (*xi));

		 *down_range = *up_range;

	 }
	 ave = ave / count;
	 for (int i = 0; i < k; i++)
	 {
		 chart[i][7] = pow((chart[i][2] - ave), 2);
		 chart[i][8] = pow((chart[i][2] - ave), 3);
		 chart[i][9] = pow((chart[i][2] - ave), 4);
	 }
	 delete xi, fi, Fi, down_range, up_range;
 }


 void chart_maker::calculator()
 {
	 //this function caculate variance and skewness and ...
	 variance = 0;
	 Skewness = 0;
	 Kurtosis = 0;
	 int* med_temp = new int;
	 *med_temp = 0;
	 int *mod_temp = new int;
	 *mod_temp = 0;
	 int* d1 = new int;
	 int* d2 = new int;
	 int* counter = new int;
	 for (int i = 0; i < k; i++)
	 {
		 variance = variance + chart[i][7];
		 Skewness = Skewness + chart[i][8];
		 Kurtosis = Kurtosis + chart[i][9];
	 }
	 variance = (variance / (count - 1));
	 std_deviation = pow(variance, 0.5);
	 Skewness = (Skewness) / (count * (pow(std_deviation, 3)));
	 Kurtosis = ((Kurtosis / (count * (pow(std_deviation, 4)))) - 3);

	 for (int i = 0; i < k; i++)
		 if (chart[i][4]>=count/2)
			 *med_temp = k;
		median = chart[*med_temp][0] + (((count/2)-chart[*med_temp-1][4])/chart[*med_temp][3])*l;
	 for (int i = 0; i < k; i++)
		 if (*mod_temp <= chart[i][3])
		 {
			 *mod_temp = chart[i][3];
			 *counter = i;

		 }

		 *d1 = chart[*counter][3] - chart[*counter - 1][3];
		 *d2 = chart[*counter][3] - chart[*counter + 1][3];
		 mod = chart[*counter][0] * ((*d1) / (*d1 + *d2)) * l;

	 delete counter, d1,d2,med_temp,mod_temp; 
 }


 void chart_maker::printer()
 {
	 //this function writing chart and other data on files and screens 
	 //writing on terminal
	 //writing data on terminal and console has some problems in high digit numbers like crowded rows and ... but its ok because we saving it on file too 
	 cout << "Output of data: \n";
	 for (auto i = data0.begin(); i != data0.end(); ++i)
		 cout << *i << " , ";

	 cout<<endl << "R: " << r << "\tL: " << l << "\txmin: " << xmin << "xmax: " << xmax << "\tfraction: " << fraction << "\tcount: " << count;
	 cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;

	 cout << "		 data range			   xi			fi			Fi			ri			gi			(xi-ave)^2		  (xi-ave^3)		  (xi-ave)^4	\n";
	 cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	 for (int i = 0; i < k; i++)
	 {
		 cout << fixed;
		 cout<< setprecision(6) <<i+1<<":"<<  "	"<<"[" << chart[i][0] << "  ,  "<<chart[i][1]<<")"<<"	|";
		 for (int j =2 ; j < 10; j++)
		 {
			 cout << fixed;
			 cout << setprecision(6);
			 if (j < 7)
				 cout << "	" << chart[i][j] << "	|";
			 else
				 cout << "	   " << chart[i][j] << "	   |";
		
		 }
		 cout << " \n";
	 }
	 cout << endl << "Variance: " << variance << "\tstandard deviation: " << std_deviation << "\tSkewness: " << Skewness << "\tKurtosis: " << Kurtosis << endl;

	 //writing to .csv file
	 ofstream write_file("data.csv");;
	 write_file << "Number,Downrange,Uprange,xi,fi,Fi,ri,gi,(xi-ave)^2,(xi-ave^3),(xi-ave)^4\n";
	 for (int i = 0; i < k; i++)
	 {
		 write_file<< i + 1 << ","; 

		 for (int j = 0; j < 10; j++)
		 {
		 	write_file << chart[i][j] << ",";

		 }
		 write_file << " \n";

	 }
	 write_file << endl << "Variance,standard_deviation,Skewness,Kurtosis\n";
	 write_file<<variance<<","<<std_deviation<<","<<Skewness<<","<<Kurtosis<<",\n";
     write_file << "data:,\n";
	 for (auto i = data0.begin(); i != data0.end(); ++i)
		 write_file << *i << "\n";

	 write_file.close();
 }








//driver code
int main()
{
	chart_maker ch1;
	ch1.get_data();
	ch1.sort();
	ch1.fraction_calculator();
	ch1.chart_calculator();
	ch1.chart_init();
	ch1.calculator();
	ch1.printer();

	return 0;
}
