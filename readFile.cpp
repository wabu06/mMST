#include<iostream>
#include<fstream>


using namespace std;


int main(int argc, char** argv)
{
	ifstream fin("graph.dat");
	
	if ( fin.bad() )
	{
		cerr << "Error opening file!!" << endl;
		return 1;
	}
	
	int gsize;
	
	fin >> gsize; cout << gsize << endl;
	
	int v1, v2, w, L = 0;
	
	char ans;
	
	while( fin.good() )
	{
		fin >> v1 >> v2 >> w;
		cout << v1 << '\t' << v2 << '\t' << w << endl;
		++L;
		
		if (L == 20)
		{
			L = 0;
			cout << "Continue? Y/n: ";
			ans = static_cast<char>( getchar() ); //getchar();
			cin >> ans;
			
			/* do {
				ans = cin.get();
				cc += cin.gcount(); // or cc = cin.gcount() // character count
				pans = ans;
			} while(cin); */
				
		
			if( (ans != 'Y') && (ans != 'y') ) break;
		}
	}
	
	return 0;
}
