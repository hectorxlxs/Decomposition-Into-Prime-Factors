#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <list>

using namespace std;

class Prime{

	private:
		int rep;
		int num;
	public:
	
		Prime(int _num, int _rep = 0)
		{
			num = _num;
			rep = _rep;
		}
	
		void AddRep(){rep++;}
		int GetRep(){return rep;}
		
		int GetNum(){return num;}
};

list<Prime> *LoadPrimes(int maxNumber){

	int tempNum = 0;
	string primeStr;
	
	list<Prime> *primes = new list<Prime>;
	
	ifstream ifile;
    ifile.open("Primes.txt");
	
	if(!ifile){cout<<"Cannot open the file Primes.txt";}
    else{

        while(!ifile.eof()){

            getline(ifile, primeStr);

            tempNum = atoi(primeStr.c_str());

            if(tempNum > maxNumber){break;}
			
			if(ifile.eof())
			{
				cout<<"This program cannot decompose this big number";
				getch();
				system("exit");
			}

            primes->push_back(Prime(tempNum));
        }

        ifile.close();
    }
	
	return primes;
}

void Decompose(int _num){
	
    bool EXIT = false;
	
	list<Prime> *primes = LoadPrimes(int(_num / 2));
	
	int result = _num;
	
	list<Prime>::iterator lastIterator = primes->begin();

    while(!EXIT){

        for(list<Prime>::iterator it = lastIterator; it != primes->end(); it++){

			if(result == 1){EXIT = true; break;} //if result equals 1 it means that there aren't more primes composing the number
			
            if(result % it->GetNum() == 0){

                result = result / it->GetNum();
                it->AddRep();
				
				lastIterator = it;
				
                break; //to start again looking all primes starting from lastPrime
            }
        }
    }

    for(list<Prime>::iterator it = primes->begin(); it != primes->end(); it++){

        if(it->GetRep() > 0){cout<<"\nPrime "<<it->GetNum()<<": x"<<it->GetRep();}
    }
	
	delete primes;
}

int main(){

int num = 0;

bool EXIT = false;

while(!EXIT){
	
	cout<<"Write the number to decompose in prime numbers: ";
	cin>>num;

	Decompose(num);

	getch();
	system("cls");
}

return 0;}
