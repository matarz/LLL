/* 
   Author: Zakaria Almatar
   Date: 07/16/09
   Class: CS163
   Assignment: Program#1

   Purpose: The progarm purpose is to manage the reservations of seats 
            for an event. It adds a reservation, removes a reservation 
            and displays the status of all reservations.
*/
/*
   File name: main.cpp
   Contains: This file has the client program 
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "header.h"
using namespace std;


int main_menu();                  //get the user choice
int order(tickets * room);         //order a ticket
int cancel(tickets * room);        //cancel an order


int main()
{
  int rows;           //max rows
  int seats;          //max seats
  int choice;         //user's choice
  tickets *room1;     //pointer to class tickets

  cout<<"Please, enter the maximum number of rows: ";  
  cin>>rows;          //get max rows
  cout<<"\nPlease, enter the number of seats within each row: ";
  cin>>seats;         //get max seats
  room1 = new tickets(rows, seats);  //allocate a new class object

  do 
  {
    choice = main_menu();  //get the user's choice

	if(choice == 1)  // Order
	{ 
      choice=order(room1);
	}	 
    else if(choice ==2) // Cancel
	{
      choice=cancel(room1);
	}	 
    else if(choice == 3)  // Status
	{ 
      choice= room1->display_all();
	}	 
	else if(choice == 4)  // save and quit
	{ 
      choice= room1->quit();
	}	 
  }while(choice ==0); 

  system("PAUSE");
  return 0;
}


/*************************************************************************
***                       Main menu function                           ***
*************************************************************************/
// This function's purpose is to get the user's choice and return it. 

int main_menu()
{

  int choice;  // to hold the user's choice
  do
  { 
    cout <<"\n\n  +---------------------------------------------+" <<endl;
    cout <<"     1- Order a ticket." <<endl;
    cout <<"     2- Cancel an order." <<endl;
    cout <<"     3- Check the status." <<endl;
    cout <<"     4- Quit." <<endl;
    cout <<"  +---------------------------------------------+" <<endl;
    cout << endl;

    cout <<"Please, enter the number besides your choice: "; 
    cin>>choice;    //get choice

  }while (choice<1 || choice>4);

 return choice;
}


/*************************************************************************
***                         Order function                             ***
*************************************************************************/


int order(tickets * room)
{
  char *name= new char[40];
  int num_of_tickets;
  int result;


  cin.ignore();
  cout<<"\nPlease enter a name (First Last): ";
  cin.getline(name, 40);

  cout<<"\nPlease enter the number of tickets: ";
  cin>>num_of_tickets;
  
  
   result = room->insert(name, num_of_tickets);

   if(result==0)
     {
       cout<<"\nNo available seats were found.";
     }
   else
     {
       cout <<"\n***The Seat(s) was/were assigned successfully.***";
     }
  return 0;
}



/*************************************************************************
***                        Cancel function                             ***
*************************************************************************/

int cancel(tickets * room)
{
  int result;
  char *name= new char[40];

  cin.ignore();
  cout<<"\nPlease enter a name (First Last): ";
  cin.getline(name, 40);
  
  result=room->remove(name);

  if (result==1)
    cout<<"\n***The order(s) was/were deleted successfully.***";
  else
    cout<<"\nNo orders were deleted";
    
  delete name;
  name=NULL;
  
  return 0;
}



