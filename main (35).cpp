#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;



struct Calendar
{
	string address;
	char calendar[5][7] =
		{{'*', '*', '*', '*', '*', '*', '*'},
		 {'*', '*', '*', '*', '*', '*', '*'},
		 {'*', '*', '*', '*', '*', '*', '*'},
		 {'*', '*', '*', '*', '*', '*', '*'},
		 {'*', '*', '*', '*', '*', '*', '*'}};
};

struct Tenant
{
	int smonth, sday, emonth, eday;
//Calendar months[13];
};

struct Property
{
	string address;
	double price;
	int tenants;
	vector<Tenant> all;
	Calendar months[13];
};

vector<Property> propsList;
string y="enter";

void InputAndOutput(ifstream &fin);
void BookT(int sMonth, int sDay, int eMonth, int eDay, Tenant &p);
void Book(int sMonth, int sDay, int eMonth, int eDay, Property &p);
void YearlyTXT(Property p, ofstream &fout);
bool IsValidDates(int sMonth, int sDay, int eMonth, int eDay, Property p);

int main()
{
	ifstream fin("properties.txt");
	ofstream fout("yearly.txt");



	if (!fin.is_open())
	{
		cout << "File not found." << endl;
		return -1;
	}

	while (!fin.eof())
	{
		Property temp;
		// string whitespace = "";
		getline(fin, temp.address);		// Fixed fin issue by simply checking length of input from file
		if (temp.address.length() == 0) // if there was issue i just did fin.ignore and that worked
		{
			fin.ignore();
			getline(fin, temp.address);
		}
		fin >> temp.price >> temp.tenants;
		propsList.push_back(temp);
		for (int i = 0; i < temp.tenants; i++)
		{
			Tenant tempT;
      //cout<< tempT;
			fin >> tempT.smonth >> tempT.sday >> tempT.emonth >> tempT.eday;
			propsList.back().all.push_back(tempT);
      
		}
		// fin.ignore(256, '\n');
    
		//InputAndOutput(fin);//moved to after booking has been made to make sure we have all the reservations
  for (int i = 0; i < propsList.size(); i++)
	{
		for (int j = 0; j < propsList[i].tenants; j++) 
      // changes from all.size to tenants******************
		{
			Book(propsList[i].all[j].smonth, propsList[i].all[j].sday, propsList[i].all[j].emonth, propsList[i].all[j].eday, propsList[i]);
			 
      //cout<<"testj"<<j;
		}
   
    //cout<<"testi"<<i;
   }
    
    //cout<<"propslist"<<propsList.size();
    }
   // InputAndOutput(fin);
    InputAndOutput(fin);
    
  
 //for (int i=0;i<=propertList.size()-1;i++)
   //{
    for (int i = 0; i < propsList.size(); i++)
      {
    YearlyTXT(propsList[i],fout);
        }
   //}
        
	

    
	

	///////////////////PRE PROCESSING complete gathered all data

	fin.close();
	fout.close();
	return 0;
}


/*property inout(ifstream &fin)
{
  
  
}*/

void InputAndOutput(ifstream &fin)
{

  //ofstream fout("yearly.txt");
  
	Property property;
  int iCnt=0;
	string address, y;
  char q1;
  string sVal="";
  while (y!="exit")
    {
  // y="";
	cout << "Enter the address of the property you want to book or exit to exit:" << endl;
  //cout<<y;    
	getline(cin, y);
  //cin>>y;
      
      if (y!="")
      {
        for (int i = 0; i < propsList.size(); i++)
  	    {
          //cout<<propsList[i].address<<" "<<y<<endl;

          if (y=="exit")
          {  q1='q';
            break;
            }
         if (y!=propsList[i].address) 
         {
           sVal="Address Not Found";
          
         }
          else
         {cout<<"found";
          sVal="found";
          property=propsList[i];
           iCnt=i;
         q1=0;
          break;}
          }
        
        
        if (sVal=="Address Not Found")
        {
          cout<<sVal;
          break;
        }
      
     
        
      
      if (y!="exit")
      {
	   // property.address = y;
      q1='0';
      }
      else
      {
        q1='q';
        break;
      }
      }
  while(q1!='q')
	{
    //cout<<q1;
		cout << "Enter an option:" << endl;
		cout << "1. Show the calendar of the property on a given month" << endl;
		cout << "2. Book a period of time for a given property" << endl;
		cout << "q. Quit" << endl;
		
      cin >> q1;

		if (q1 == '1')
		{
			int month;
			cout << "Enter the month number:" << endl;
			cin >> month;
			if (month < 1 || month > 12)
			{
				cout << "Invalid month number" << endl;
			}
			else
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						if (i == 4 && j >= 2)
						{
							cout << property.months[month].calendar[i][j];
							break;
						}
						else
						{
							cout << property.months[month].calendar[i][j] << " ";
						}
					}
					cout << endl;
				}
				cout << endl;
			}
      
      }
		else if (q1 == '2')
		{
			int startMonth, startDay, endMonth, endDay;
			cout << "Enter the start month and day:";
			cin >> startMonth >> startDay;
			cout << endl;
			cout << "Enter the end month and day:";
			cin >> endMonth >> endDay;
			cout << endl;

			if (startMonth < 1 || startMonth > 12 || endMonth < 1 || endMonth > 12)
			{
				cout << "Invalid month number" << endl;
			}
			else if (startDay < 1 || startDay > 31 || endDay < 1 || endDay > 31)
			{
				cout << "Invalid day number" << endl;
			}
			else if (IsValidDates(startMonth, startDay, endMonth, endDay, property))
			{
        
				Book(startMonth, startDay, endMonth, endDay,property );
        propsList[iCnt]=property;
				cout << "Booked!" << endl;
        
			}
			else
			{
				cout << "Date range has dates that are already booked!" << endl;
			}
		}
	  else if (q1 == 'q')
		{
			/*cout << "Enter the address of the property you want to book or exit to exit:" << endl;
      cin.ignore();
      
      cin >> y;
       if (y=="exit")
       { break; }*/
      //y="exit";
      //break;
      //return property;
      //next;
      //y="exit";
      y="exit";
      break;
      //exit(1);
		}
		else
		{
			cout << "Invalid option" << endl;
		}
	}
     
      }
      
    //return property;
}

void Book(int sMonth, int sDay, int eMonth, int eDay, Property &p)
{
	int count = 0;
	int t = (sDay % 7) * 2 - 2;
  int week=1;
  if (eDay>=8 && eDay<=14)
    week=2;
  if (eDay>=15 && eDay<=21)
    week=3;
  if (eDay>=22 && eDay<=28)
    week=4;
  if (eDay>=29)
    week=5;
  //int jVal=sDay/7;
  if (sDay%7==0)
    week=week+1;
  
	for (int i = sMonth; i <= eMonth; i++)
	{
		for (int j = sDay/7; j < week; j++)
		{
			for (int k = t; k <= 12; k += 2)
			{
				count++;
        //cout<<p.address<<":"<<k<<endl;
				if (k == 0 || k == 12||k==-2)
				{
					p.months[i].calendar[j][k / 2] = 'D';
				}
				else
				{
					p.months[i].calendar[j][k / 2] = 'B';
				}
				
				if (count == eDay - sDay + 1)
				{
					break;
				}

       
      }
      t=0;
			
		}
    
	}
}


void YearlyTXT(Property p, ofstream &fout)
{
	string mo;
	double mSum = 0, ySum = 0;

	fout << "Address: " << p.address << endl;
  //cout<<p.tenants;
  for (int n = 0; n < p.tenants; n++) 
      // changes from all.size to tenants******************
		{
      string e = "";
  int t = (p.all[n].sday % 7) * 2 - 2;
  int week=1;
  if (p.all[n].eday>=8 && p.all[n].eday<=14)
    week=2;
  if (p.all[n].eday>=15 && p.all[n].eday<=21)
    week=3;
  if (p.all[n].eday>=22 && p.all[n].eday<=28)
    week=4;
  if (p.all[n].eday>=29)
    week=5;
      //if (n>=1)
     if (p.all[n-1].smonth!=p.all[n].smonth)
        {
          
         
      
	for (int i = p.all[n].smonth; i <= p.all[n].emonth; i++)
	{
    
		//for (int j = p.all[n].sday / 7; j < week; j++)
		//{
			//for (int k = t; k <= 6; k ++)
			//{
				//if (p.months[i].calendar[j][k] != '*')
				//{
          //fout<< p.months[i].calendar[j][k];
          if (i == 1)
					{
						mo = "January";
					}
					else if (i == 2)
					{
						mo = "February";
					}
					else if (i == 3)
					{
						mo = "March";
					}
					else if (i == 4)
					{
						mo = "April";
					}
					else if (i == 5)
					{
						mo = "May";
					}
					else if (i == 6)
					{
						mo = "June";
					}
					else if (i == 7)
					{
						mo = "July";
					}
					else if (i == 8)
					{
						mo = "August";
					}
					else if (i == 9)
					{
						mo = "September";
					}
					else if (i == 10)
					{
						mo = "October";
					}
					else if (i == 11)
					{
						mo = "November";
					}
					else if (i ==12)
					{
						mo = "December";
					}
					//fout << mo << ": " << mSum << endl;
		for (int r = 0; r < 5; r++)
		{
			for (int o = 0; o <= 6; o++)
        {
        //string e = "";
					if (r== 4 && o >= 2)
					{
						e=e+p.months[i].calendar[r][o];
            if(p.months[i].calendar[r][o] == 'B')
              mSum += p.price;
						break;
					}
					else
					{
						e=e+ p.months[i].calendar[r][o] + " ";
            if(p.months[i].calendar[r][o] == 'B')
              mSum += p.price;
            if(p.months[i].calendar[r][o] == 'D')
              mSum = mSum + p.price * 2;
            }
        }
      e += "\n";
    }
			ySum += mSum;
       fout << mo << ": " << fixed << setprecision(2) << mSum << endl;
    mSum=0;
        fout << e << endl;		
    }
      
				//fout << endl;
       // t = 0;
      }
      }
      
        //fout << fixed << setprecision(2) << "Total: $" << ySum << endl << endl;

  fout << fixed << setprecision(2) << "Total: $" << ySum << endl << endl;
  }

bool IsValidDates(int sMonth, int sDay, int eMonth, int eDay, Property p)
{
	bool isValid;
	int count = 0;
int t = (sDay % 7) * 2 - 2;
  int week=1;
  if (eDay>=8 && eDay<=14)
    week=2;
  if (eDay>=15 && eDay<=21)
    week=3;
  if (eDay>=22 && eDay<=28)
    week=4;
  if (eDay>=29)
    week=5;
  
  
  
	for (int i = sMonth; i <= eMonth; i++)
	{
		for (int j = sDay / 7; j < week; j++)
		{
			for (int k = t; k <= 12; k += 2)
			{
				count++;
				if (p.months[i].calendar[j][k] == '*')
				{
					isValid = true;
				}
				else
				{
					return false;
				}

				if (j == sDay / 7 + 1)
				{
					k = 0;
				}

				if (count == eDay - sDay + 1)
				{
					break;
				}
			}
      t = 0;
		}
	}

	return isValid;
}