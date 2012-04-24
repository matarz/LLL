/* 
   Author: Zakaria Almatar
   Date: 07/16/09
   Class: CS163
   Assignment: Program#1
*/
/*
   File name: header.h
   Contains: This file has the class and the funtion definitions
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;


class tickets      //Main class
{
  public:
    tickets(int rows_c, int seats_c);            //constructor(max rows, max seats)
    ~tickets();                                  //constructor
    int insert(char n[], int num_of_tickets);    //insert ticket(s)
    int remove(char n[]);                        //remove ticket(s)
    int display_all();                           //display all tickets
    int quit();                                  //save data and quit
    
  private:
    int add(char n[], int row, int seat);        //add one ticket
    int * check(int ticket_num);                 //check availability

    int *rows_num;         //Max number of rows
    int *seats_num;        //Max number of seats per row
    struct seat            //a ticket
    {            
      int seat_num;    //seat number
      char *name;      //name of reserver
      seat* next;
    };
    seat **rows;     //pointer to seat pointers
};



/*************************************************************************
***                            Constructor                             ***
*************************************************************************/

tickets::tickets(int rows_c, int seats_c)
{
  rows_num = new int;
  *rows_num = rows_c;     //assing max rows

  seats_num = new int;
  *seats_num = seats_c;    //assing max seats

  //declare an array of pointers, each element is a row head. 
  rows = new seat*[rows_c];  
    
  //initialize to NULL
  for(int i=0; i<rows_c;++i)
    {
      rows[i] = NULL;
    }
}

/************************************************************************
***                            Destructor                             ***
************************************************************************/
//This function's purpose is to deallocate all dynamic memory

tickets::~tickets()
{
  seat *temp;
  for(int i=0;i<*rows_num;++i)   //go throw each row
  {
    while(rows[i]!=NULL)     // go throw each seat
    {
      temp = rows[i];
      rows[i] = rows[i]->next;
      delete [] temp->name;
      temp->name=NULL;
      delete temp;
    }
  }
  delete [] rows;    //delete the array
  rows = NULL;
}

/*************************************************************************
***                        Insert Function                             ***
*************************************************************************/
//This function's purpose is to insert one or multiple orders.   

int tickets::insert(char n[], int num_of_tickets)
{
  int *row_seat;    //the position of the available seat
  int result;       //the result of adding a ticket

  row_seat = check(num_of_tickets);  //checking for availability

  if(row_seat==NULL)  //if not available
    {
      return 0;
    }
  else       //if available
    {
      for(int i=0;i<num_of_tickets;++i)   //add ticket(s) 
        {
          result=add(n, row_seat[0], row_seat[1]+i);
        }
        return 1;
    }
}

/*************************************************************************
***                          Remove function                           ***
*************************************************************************/
// This function's purpose is to remove one or more orders.  

int tickets::remove(char n[])
{
  int flag=0;                //to be returned as success or failure
  seat *temp, *front=NULL;    // pointers to help deallocate a ticket

  for(int i=0;i<*rows_num;++i) //go throw each row
  {
    temp = rows[i];

    //if the first node was a match, deallocate
    while(rows[i] != NULL && strcmp(rows[i]->name, n)==0)  
    {
      rows[i] = rows[i]->next;
      delete [] temp->name;
      temp->name=NULL;
      delete temp;
      temp=rows[i];
      flag=1; 
    }

    if(temp !=NULL && temp->next!=NULL)
      front=temp->next;

    while(front!=NULL)
    {
      if(strcmp(front->name, n)==0) //if front node was a match, deallocate
      {
        front = front->next;
        delete [] temp->next->name;
        temp->next->name=NULL;
        delete temp->next;
        temp->next=front;
        flag=1;
      }
      else     //go to next node
      {
        temp = temp->next;
        front= front->next;
      }
    }
  }
  return flag;
}

/*************************************************************************
***                     Display all function                           ***
*************************************************************************/
// This function's purpose is to display the status of all the seats. 

int tickets::display_all()
{
  seat * temp;
  for(int i=0;i<*rows_num;++i) // go throw each row
  {
    temp = rows[i];
    if(temp !=NULL)
      cout<<"\n\n  Row:"<<i+1;   // display  the row number
      
    for(int i2=0;i2<*seats_num;++i2)   // go throw each seat
    {
      if(temp==NULL)
      {
        i2=*seats_num;
      }
      else   // display the seat status
      {
        cout<<"\n    Seat:"<<temp->seat_num<<" --- Reserved to: "<<temp->name;
        temp=temp->next;
      }
    }
  }                   
  return 0;
}

/*************************************************************************
***                           Quit function                             ***
*************************************************************************/
//This function's purpose is to save the reservation and quit. 
int tickets::quit()
{
  ofstream out;
  seat * temp;
  out.open("reserved.dat", ios::out);
  
  for(int i=0;i<*rows_num;++i) // go throw each row
  {
    temp = rows[i];
    if(temp !=NULL)
      out<<"\n\n  Row:"<<i+1;   // store  the row number
      
    for(int i2=0;i2<*seats_num;++i2)   // go throw each seat
    {
      if(temp==NULL)
      {
        i2=*seats_num;
      }
      else   // store the seat status
      {
        out<<"\n    Seat:"<<temp->seat_num<<" --- Reserved to: "<<temp->name;
        temp=temp->next;
      }
    }
  }                   
  out.close();
  return 5;    
}

/*************************************************************************
***                           Add function                             ***
*************************************************************************/
//This function's purpose is to add a new node/ticket. 

int tickets::add(char n[], int row, int seat_n)
{
  seat * temp = rows[row];     //temporary pointers 
  seat * temp2;

  if(rows[row]==NULL)       //if the row is empty
    {
      rows[row]= new seat;
      rows[row]->seat_num=seat_n+1;
      rows[row]->name=new char[40];
      strcpy(rows[row]->name, n);
      rows[row]->next = NULL;
    }
  else                     
    {
      for(int i=1;i<seat_n;++i)  //go to the correct seat position
      {
        temp = temp->next;
      }
      //creat a new node/assign data
      temp2= new seat;
      temp2->seat_num=seat_n+1;
      temp2->name=new char[40];
      strcpy(temp2->name, n);

      if(temp2->seat_num == 1) //if it's the first seat in a row
      {
        temp2->next = rows[row];
        rows[row]=temp2;
        temp2 = NULL;
      }
      else                    
      {
        temp2->next = temp->next;
        temp->next = temp2;
        temp2=NULL;
      }
    }
  return 0;
}

/*************************************************************************
***                           Check function                           ***
*************************************************************************/
// This function's purpose is to check if there is space for new orders 

int * tickets::check(int ticket_num)
{
  seat *temp;             //pointer to a node
  int *pos = new int[2];   // an array which holds the available position
  
  if(ticket_num > *seats_num) //if the order is more than the seat limit
  {
    return 0;
  }
  else
  {
    for(int i=0;i<*rows_num;++i)  //go throw each row
    {
      if(rows[i]==NULL)     //if the row is empty, return its position
      {
        pos[0]=i;
        pos[1]=0;
        return pos;         
      }
      else if(rows[i]->seat_num > ticket_num)//if the number of the first seat  
      {                                      //reserved is larger than the order 
        pos[0]=i;                            //then return its position
        pos[1]=0;
        return pos;                 
      }
      else 
      {
        temp = rows[i];
        for(int i2=0; i2 < *seats_num;++i2)   //go throw each seat
        {
          if(temp->next == NULL)      
          {
            if((*seats_num+1) - temp->seat_num > ticket_num)
            {                                   
              pos[0]=i;            //if the differance between the last seat
              pos[1]=i2+1;         //reserved and the seat limit is larger than
              return pos;          //the order, then return its position
            }
          }
          else if(temp->next->seat_num - temp->seat_num > ticket_num)
          {              
            pos[0]=i;           //if the differance between this seat and the
            pos[1]=i2+1;        //next seat reserved is larger than the order
            return pos;         //then return its position
          }
          else            //otherwise go to next node
          {
            temp = temp->next;  
          }
        }
      }
    }
  return 0; //if didn't return from inside the loop then return failure
  }
}


