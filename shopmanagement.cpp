#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<typeinfo>
#include <cmath>
#include <stdlib.h>
#include <istream>
#include <conio.h>
#include <stdio.h>
#include <iomanip> // for std::setprecision()



using namespace std;


struct order
{
      int prodid1;
      char cag1[100];
      char pname1[100];
      char compy1[100];
      int qty1;
      float price1,dis1;
}o1[1000];


//declear varibble
string usrname, passwd1, passwd2, admin_acc, requsrname, requsrpasswd, choice, confirmation,passwd,mytext,press = "Press any key to Continue..........";
bool cinfail;
int x = 0, y = 0 , count = 0;
char ch;
int orderk=0;

//declear function
void banner();
void checkadmin();
void admin_acc_create();
void main_menu_login();
void login_as_admin();
void login_as_cashier();
void admin_menu();
void cashier_menu();
void acc_management();
void product_management();
void customer_management();
void restart();
void see_admin_acc();
void see_cashier_acc();
void create_cashier_acc();
void delete_acc();
//void product_management();
void customer_management();
void admin_another_acc();


void write_customer1();
void copyme(int k,order order1[],int q1,int &c2);
int getproduct();
int getcustomers();
void product_detail_heading();
void customer_detail_heading();
void prod_tabular();
void cust_menu1();
void cust_menu2();
void cust_menu3();
void modify_record(int n);
void delete_record(int n);
void againopenandclose();
void againopenandclosecust();
int search(int p);
void changeqty(int pr1,int q11);

//customer class:
class customer
{
      int cust_id;
      char cname[100];
      char address[100];
      char phno[15];
public:
      void modifycust_data(int n1,char nm[15],char add[15],char q[15]);
      int getcustid()
      {
            return cust_id;
      }
      char *getcustnm()
      {
            return cname;
      }
      char *getcustadd()
      {
            return address;
      }
      char *getphno()
      {
            return phno;
      }
      //function for taking input from customer
      void cust_input(int custid)
      {     
            system("cls");
            banner();
            cout<<"-------------------------------------------------------------------------"<<endl;
            cout<<"CUSTOMER NO: ";
            cust_id=custid;
            cout<<cust_id<<endl;
            cout<<"NAME OF CUSTOMER : ";
            cin>>cname;
            cout<<"ADDRESS : ";
            cin>>address;
            cout<<"PHONE NO. : ";
            cin>>phno;
            cout<<"-------------------------------------------------------------------------"<<endl;
      }
      //function to show customer details
      void showallcust(int c)
      {
            cout<<"   "<<cust_id<<setw(15)<<cname<<setw(23)<<address<<setw(27)<<phno<<endl;
      }
      void show_cust()
      {
             cout<<"-------------------------------------------------------------------------"<<endl;
             cout<<"CUSTOMER NO      : "<<cust_id<<endl;
             cout<<"NAME OF CUSTOMER : "<<cname<<endl;
             cout<<"ADDRESS    : "<<address<<endl;
             cout<<"PHONE NO.  : "<<phno<<endl;
             cout<<"-------------------------------------------------------------------------"<<endl;
      }
};
//customer class ends here
//Function to modify the customer details
void customer::modifycust_data(int n1,char nm[15],char add[15],char q[15])
{
      char tmpnm[40],tmpnm2[40],tmpnm3[15];
      char yes1,yes2,yes3;
      cust_id=n1;
      strcpy(cname,nm);
      cout<<"NAME OF CUSTOMER:"<<endl;
      cout<<cname<<endl;
      cout<<"Want to change the name of customer ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      int flag=0;
      while(1)
      {
            cin>>yes1;
            if(yes1== 'Y' || yes1== 'y')
            {
                  cout<<"Enter new name\n";
                  cin>>tmpnm;
                  flag=1;
                  break;
            }
            if(yes1== 'N' || yes1== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            strcpy(cname,tmpnm);
      }
      strcpy(address,add);
      cout<<"CUSTOMER ADDRESS:"<<endl;
      cout<<address<<endl;
      cout<<"Want to change the address ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      flag=0;
      while(1)
      {
            cin>>yes2;
            if(yes2== 'Y' || yes2== 'y')
            {
                  cout<<"Enter new address\n";
                  cin>>tmpnm2;
                  flag=1;
                  break;
            }
            if(yes2== 'N' || yes2== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            strcpy(address,tmpnm2);
      }
      strcpy(phno,q);
      cout<<"CUSTOMER PHONE NO.:"<<endl;
      cout<<phno<<endl;
      cout<<"Want to change the phone no. ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      flag=0;
      while(1)
      {
            cin>>yes3;
            if(yes3== 'Y' || yes3== 'y')
            {
                  cout<<"Enter new phone no.\n";
                  cin>>tmpnm3;
                  flag=1;
                  break;
            }
            if(yes3== 'N' || yes3== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            strcpy(phno,tmpnm3);
      }
      if((yes3== 'Y' || yes3== 'y') || (yes2== 'Y' || yes2== 'y') || (yes1== 'Y' || yes1== 'y'))
            cout<<"*********************   NEW CUSTOMER RECORD SAVED   **********************"<<endl;
      else
            cout<<"********************   NO CUSTOMER RECORD CHANGED   **********************"<<endl;
}
//Function to add the records in file
void write_customer()
{
      ofstream objoff;
      customer cobj;
      objoff.open("customer.csv",ios::out|ios::app);
      int r=getcustomers();
      if(r>100) //1000
      {
            r=1; // r=100
      }
       cobj.cust_input(r);
       objoff.write((char*)&cobj,sizeof(customer));
       objoff.close();
       cout<<"***********************   CUSTOMER RECORD SAVED   ***********************"<<endl;
       cin.ignore();
       cin.get();
}
//Function to check the customer number already given or not
int getcustomers()
{
      ifstream objiff;
      customer cust;
      int count=0;
      objiff.open("customer.csv",ios::binary);
      objiff.seekg(0,ios::beg);
      if(!objiff)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
      }
      while(objiff.read((char *) &cust, sizeof(customer)))
      {
            count++;
      }
      //***********jump to the last line
      objiff.seekg(count-sizeof(cust),ios::beg);
      objiff.read((char *) &cust, sizeof(customer));
      count=cust.getcustid();
      count++;
      objiff.close();
      return count;
}
// Function to read specific record from file
void display_cust_sp(int n)
{
       ifstream objfp;
       customer cust;
       int flag=0;
       objfp.open("customer.csv",ios::binary);
       if(!objfp)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      while(objfp.read((char*)&cust,sizeof(customer)))
      {
             if(cust.getcustid()==n)
            {
                  cust.show_cust();
                  flag=1;
            }
      }
      objfp.close();
      if(flag==0)
      cout<<"\n\nRecord doesnot exist"<<endl;
      cin.get();
}
//FUNCTION TO DISPLAY ALL THE CUSTOMER TABULAR FORM
void cust_tabular()
{
      int r=0,col=10;
      customer cust;
      ifstream inFile;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      customer_detail_heading();
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
             if(r<=12)
             {
                   r++;
                   cust.showallcust(col);
                   col++;
             }
             else
             {
                   cout<<"----------------------------- Press any key -----------------------------"<<endl;
                   cin.get();
                   customer_detail_heading();
                   col=10;
                   r=0;
            }
      }
      inFile.close();
      cin.get();
}
//function to display heading of customer details
void customer_detail_heading()
{
      cout<<"========================================================================="<<endl;
      cout<<"   ************************  CUSTOMER DETAILS  **********************    "<<endl;
      cout<<"========================================================================="<<endl;
      cout<<"CUST.NO"<<setw(13)<<"NAME"<<setw(23)<<"ADDRESS"<<setw(27)<<"PHONE NO"<<endl;
      cout<<"-------------------------------------------------------------------------"<<endl;
}
//FUNCTION TO MODIFY customer RECORD
void modify_cust_record(int n)
{
      customer cust,temp;
      char tmpnm[100],tmpaddress[100];
      ifstream inFile;
      int fpos1=-1;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      int flag=0;
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
            if(cust.getcustid()==n)
            {
             cust.show_cust();
             flag=1;
            }
      }
      inFile.close();
      if(flag==0)
            cout<<"\n\nRecord doesnot exist"<<endl;
      else
      {
      //modifying the records starts here
            fstream File;
            File.open("customer.csv",ios::binary|ios::in|ios::out);
            if(!File)
            {
                  cout<<"File could not be open !! Press any Key..."<<endl;
                  cin.get();
                  return;
            }
            while(File.read((char *) &cust, sizeof(customer)))
            {
                  if(cust.getcustid()==n)
                  {
                        fpos1=(int)File.tellg();
                        break;
                  }
            }
            File.seekp(fpos1-sizeof(customer),ios::beg);
            strcpy(tmpnm,cust.getcustnm());
            strcpy(tmpaddress,cust.getcustadd());
            char q1[15];
            strcpy(q1,cust.getphno());
            cout<<"============  ENTER NEW VALUES FOR THE RECORDS GIVEN ABOVE  ============="<<endl;
            temp.modifycust_data(n,tmpnm,tmpaddress,q1);
            File.write((char *) &temp, sizeof(customer));
            File.close();
      }
}
//FUNCTION TO DELETE THE RECORD OF THE CUSTOMER AVAILABLE
void deletecust_record(int n)
{
      customer cust;
      ifstream inFile;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      int flag=0;
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
            if(cust.getcustid()==n)
            {
                   cust.show_cust();
                   flag=1;
            }
      }
      inFile.close();
      char ch;
      if(flag==0)
            cout<<"\n\nRecord doesnot exist"<<endl;
      else
      {
      //Deletion of the records starts from here
            cout<<"DO YOU WANT TO DELETE THE RECORDS GIVEN ABOVE [YES(Y or y) OR NO(N or n)] : ";
            cin>>ch;
            if (toupper(ch)=='Y')
            {
                   ofstream outFile;
                   outFile.open("Temp2.csv",ios::binary);
                   ifstream objiff("customer.csv",ios::binary);
                   objiff.seekg(0,ios::beg);
                   while(objiff.read((char *) &cust, sizeof(customer)))
                   {
                         if(cust.getcustid()!=n)
                         {
                              outFile.write((char *) &cust, sizeof(customer));
                         }
                  }
                  outFile.close();
                  objiff.close();
                  remove("customer.csv");
                  rename("Temp2.csv","customer.csv");
                  againopenandclosecust();
                  cout<<"---------------------------Record Deleted--------------------------------"<<endl;
            }
      }
      cin.get();
}
void againopenandclosecust()
{
      ifstream inFile;
      customer cust;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cin.get();
            return;
      }
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
      }
      inFile.close();
}
//Search the customer
int searchcust(int p)
{
      customer cust;
      int tmprt=0;
      ifstream inFile;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return -1;
      }
      int flag=0;
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
            if(cust.getcustid()==p)
            {
                   cust.show_cust();
                   flag=1;
                   tmprt=(int)inFile.tellg();
                   break;
            }
      }
      inFile.close();
      if(flag==0)
            return 1;
      //cout<<"\n\nRecord doesnot exist";
      else
      {
            return tmprt;
      }
}
//Fuction to write customer data
void write_customer1()
{
      ofstream objoff;
      customer cobj;
      objoff.open("customer.csv",ios::out|ios::app);
      int r=getcustomers();
      if(r>100) //1000
      {
            r=1; // r=100
      }
       cobj.cust_input(r);
       objoff.write((char*)&cobj,sizeof(customer));
       objoff.close();
       cout<<"***********************   CUSTOMER RECORD SAVED   ***********************"<<endl;
       cin.ignore();
       cin.get();
       cust_menu3();
}
int before_order()
{
      int f=-1,num=0;
      customer cust;
      cout<<"ENTER THE CUSTOMER ID TO BILL : ";
      cin>>num;
      ifstream inFile;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return -1;
      }
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
            if(cust.getcustid()==num)
            {
                   cust.show_cust();
                   f=1;
                   //tmprt=(int)inFile.tellg();
                   break;
            }
      }
      inFile.close();
      return f;
}
//Product class starts here:
class product
{
      int prodid;
      char category[100];
      char name[100];
      char company[100];
      int qty;

      float price,dis;
      public:
      product()
      {
            qty=0;
            price=0;
            dis=0;
      }
      void modifydata(int n1,char category1[15],char snm[15],char companynm[15],int q); // modify
      void create_prod(int rn1)
      {
            cout<<"-------------------------------------------------------------------------"<<endl;
            cout<<"PRODUCT NO: ";
            prodid=rn1;
            cout<<prodid<<endl;
            cout << "PRODUCT CATERGORY : ";
            cin >> category;
            cout<<"NAME OF PRODUCT : ";
            cin>>name;
            cout<<"COMPANY : ";
            cin>>company;
            cout << setprecision(9);

            cout<<"PRODUCT PRICE : ";
            cin>>price;
            cout<<"QUANTITY : ";
            cin>>qty;
            cout<<"DISCOUNT% : ";
            cin>>dis;
            cout<<"-------------------------------------------------------------------------"<<endl;
      }
      void show_prod()
      {
            cout<<"-------------------------------------------------------------------------"<<endl;
            cout<<"PRODUCT NO            : "<<prodid<<endl;
            cout << "PRODUCT CATEGORY    : " << category << endl;
            cout<<"NAME OF PRODUCT       : "<<name<<endl;
            cout<<"COMPANY               : "<<company<<endl;
            cout << setprecision(9);

            cout<<"PRODUCT PRICE         : "<<price<<endl;
            cout<<"QUANTITY              : "<<qty<<endl;
            cout<<"DISCOUNT%             : "<<dis<<"%"<<endl;
            cout<<"-------------------------------------------------------------------------"<<endl;
       }
      //Function shows product data in tabular form
      void showall(int c)
      {     
            cout << setprecision(9);

            cout<<"  "<<prodid<<setw(15)<<category<<setw(14)<<name<<setw(11)<<company<<setw(11)<<"Kyats."<<price<<setw(21)<<qty<<setw(21)<<dis<<"%"<<endl;
      }
      int retpno()
      {
           return prodid;
      }
      char* getcatergory()
      {
            return category;
      }
      float retprice()
      {     
            cout << setprecision(9);

            return price;
      }

      char* getcompany()
      {
          return company;
      }
      char* getname()
      {
          return name;
      }
      int getqty()
      {
          return qty;
      }
      float retdis()
      {
          return dis;
      }
      void setqty(int q21)
      {
          qty=q21;
      }
};
// Product class ends here
// Fuction to modify product details
void product::modifydata(int n1,char category1[15],char snm[15],char companynm[15],int q)
{
      char tmpc[40],tmpnm[40],tmpnm2[40];
      char yes,yes1,yes2;
      cout<<"PRODUCT NO : ";
      prodid=n1;
      cout<<prodid<<endl;
      strcpy(category,category1);

      cout<<"NAME OF CATERGORY : " << category << endl;
      cout<<"Want to change the category name ? (Yes[ y or Y ] or NO [n or N]) : ";
      int flag=0;
      while(1)
      {
            cin >> yes;
            if(yes== 'Y' || yes== 'y')
            {
                  cout << "Enter the new category : ";
                  cin >> tmpc;
                  flag = 1;
                  break;
            }
            if(yes== 'N' || yes== 'n')
            {
                  flag = 0;
                  break;
            }

      }
      if(flag==1)
      {
            strcpy(category,tmpc);
      }
      strcpy(name,snm);
      // Modify product name()
      cout<<"NAME OF Product : " << name << endl;
      cout<<"Want to change the name ? (Yes[ y or Y ] or NO [n or N]) : ";
      flag = 0;
      while(1)
      {
            cin>>yes1;
            if(yes1== 'Y' || yes1== 'y')
            {
                  cout<<"Enter new name\n";
                  cin>>tmpnm;
                  flag=1;
                  break;
            }
            if(yes1== 'N' || yes1== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            strcpy(name,tmpnm);
      }
      strcpy(company,companynm);
      //COMPANY NAME TO BE MODIFY
      cout<<"NAME OF Company : " << company << endl;
      cout<<"Want to change the company name ? (Yes[ y or Y ] or NO [n or N]) : ";
      flag=0;
      while(1)
      {
            cin>>yes2;
            if(yes2== 'Y' || yes2== 'y')
            {
                  cout<<"Enter new company name:\n";
                  cin>>tmpnm2;
                  flag=1;
                  break;
            }
            if(yes2== 'N' || yes2== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            strcpy(company,tmpnm2);
      }
      cout << setprecision(9);

      cout<<"PRICE : "<< price << endl;
      //add the line to display price
      float tmppr=0;
      char yes4,yes3,yes5;
      cout<<"Want to change the price of product ? (Yes[ y or Y ] or NO [n or N]) : ";
      flag=0;
      while(1)
      {
            cin>>yes3;
            if(yes3== 'Y' || yes3== 'y')
            {     
                  cout << setprecision(9);

                  cout<<"Enter new price of product:\n";
                  cin>>tmppr;
                  flag=1;
                  break;
            }
            if(yes3== 'N' || yes3== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            price=tmppr;
      }
      cout<<"QUANTITY:"<<endl;
      //add the line to display quantity
      int tmpqty=0;
      cout<<"Want to change the quantity of product ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      flag=0;
      while(1)
      {
            cin>>yes4;
            if(yes4== 'Y' || yes4== 'y')
            {
                  cout<<"Enter new quantity:\n";
                  cin>>tmpqty;
                  flag=1;
                  break;
            }
            if(yes4== 'N' || yes4== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            qty=tmpqty;
      }
      cout<<"DISCOUNT%:"<<endl;
      //add the line to display discount
      float tmpdis=0;
      cout<<"Want to change the discount of product ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      flag=0;
      while(1)
      {
            cin>>yes5;
            if(yes5== 'Y' || yes5== 'y')
            {
                  cout<<"Enter new discount"<<'%'<<"on the product:\n";
                  cin>>tmpdis;
                  flag=1;
                  break;
            }
            if(yes5== 'N' || yes5== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            dis=tmpdis;
      }
      if((yes3== 'Y' || yes3== 'y') || (yes2== 'Y' || yes2== 'y') || (yes1== 'Y' || yes1== 'y') || (yes4== 'Y' || yes4== 'y') || (yes5== 'Y' || yes5== 'y'))
      cout<<"*********************   NEW PRODUCT RECORD SAVED   *********************"<<endl;
      else
      cout<<"********************   NO PRODUCT RECORD CHANGED   *********************"<<endl;
}
// Global declaration for stream object
fstream fp;
// Class function outside
product pr;
// Function to write product details in file
void write_book()
{
      fp.open("product.csv",ios::out|ios::app);
      int rnn=getproduct();
      if(rnn>100)
      {
            rnn=1;
      }
      pr.create_prod(rnn);
      fp.write((char*)&pr,sizeof(product));
      fp.close();
      cout<<"***********************  PRODUCTS RECORD SAVED  ************************"<<endl;
      cin.ignore();
      cin.get();
}
//Function to check the product number already given or not
int getproduct()
{
      ifstream objiff;
      product st;
      int count=0;
      objiff.open("product.csv",ios::binary);
      objiff.seekg(0,ios::beg);
      if(!objiff)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
      }
      while(objiff.read((char *) &st, sizeof(product)))
      {
            count++;
      }
      objiff.seekg(count-sizeof(st),ios::beg);
      objiff.read((char *) &st, sizeof(product));
      count=st.retpno();
      count++;
      objiff.close();
      return count;
}
//Function to read specific record from file
void display_sp(int n)
{
      int flag=0;
      fp.open("product.csv",ios::in);
      if(!fp)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      while(fp.read((char*)&pr,sizeof(product)))
      {
            if(pr.retpno()==n)
            {
                  pr.show_prod();
                  flag=1;
            }
      }
      fp.close();
      if(flag==0)
            cout<<"\n\nRecord doesnot exist"<<endl;
      cin.get();
}
//Function to place order and generating invoice for PRODUCT PURCHASED
void place_order()
{
      order o1[100];
      int c=0,pr1=0;
      float amt=0,damt=0,total=0,ttaxt=0;
      int k=0,q1;
      char ch='Y';
      int ptx[100];
      int v=0;
      int value=before_order();
      if(value==1)
      {
            cout<<endl;
            
           
            do
            {
                  prod_tabular();
                  cout<<"========================================================================"<<endl;
                  cout<<"                             PLACE YOUR ORDER                           "<<endl;
                  cout<<"========================================================================"<<endl;
                  cout<<"ENTER THE PRODUCT NO : ";
                  cin>>pr1;
                  k=search(pr1);
                  if(k>0)
                  {
                        cout<<"Enter the Quantity : ";
                        cin>>q1;
                        copyme(k,o1,q1,c);
                        ptx[v]=pr1;
                        v++;
                  }
                  else
                  {
                        cout<<"PRODUCT not found"<<endl;
                  }
                  cout<<"Do you want purchase more ? (Yes[ y or Y ] or NO [n or N])"<<endl;
                  cin>>ch;
            }while(ch=='y' || ch=='Y');
            cout<<"Thank You For Placing The Order  ........"<<endl<<endl;
            cin.get();
            cout<<"========================================================================\n"<<endl;
            cout<<"*****************************   INVOICE   ******************************"<<endl;
            cout<<"------------------------------------------------------------------------"<<endl;
            cout<<"PR.No."<<setw(7)<<"CATEGORY"<<setw(7)<<"NAME"<<setw(10)<<"Qty"<<setw(12)<<"Price"<<setw(13)<<"Amount"<<setw(23)<<"Amount - discount"<<endl<<endl;
            int yy=8;
            for(int x=0;x<c;x++)
            {     
                  cout << setprecision(9);
                  amt=o1[x].qty1*o1[x].price1;
                  damt=amt-o1[x].dis1;
                  cout<<"  "<<ptx[x]<<setw(10)<<o1[x].pname1<<setw(9)<<o1[x].qty1<<setw(12)<<"Kyats."<<o1[x].price1<<setw(10)<<"Kyats."<<amt<<setw(14)<<"Kyats."<<damt<<endl;
                  total+=damt;
                   //ttaxt+=o1[x].tax1;
                  yy++;
             }
             ttaxt=18;
             cout<<"\n-------------------------------------------------------------------------"<<endl;
             yy++;
             cout<<"\n		  TOTAL AMOUNT     :   "<<"Kyats."<<total<<endl;
             yy++;
             cout<<"		  CGST             :   "<<"+"<<ttaxt/2<<"%"<<endl;
             cout<<"		  SGST             :   "<<"+"<<ttaxt/2<<"%"<<endl;
             yy++;
             cout<<"-------------------------------------------------------------------------"<<endl;
             yy++;
             cout<<"		  NET TOTAL        :   "<<"Kyats."<<(total+((ttaxt*total)/100))<<endl;
             yy++;
             cout<<"		  ROUND OFF AMOUNT :   "<<"Kyats."<<setprecision(2)<<(round(total+((ttaxt*total)/100))-(total+((ttaxt*total)/100)))<<endl;
             cout<<"		  NET AMOUNT DUE   :   "<<"Kyats."<<fixed<<round(total+((ttaxt*total)/100))<<endl<<endl;
             cout<<"-------------------------------------------------------------------------"<<endl;
             cout<<"		   P A Y M E N T  S U M M A R Y  "<<endl;
             cout<<"-------------------------------------------------------------------------"<<endl;
             cout<<"		  Enter CASH value :   Kyats.";
             float vb,xy;
             cout << setprecision(16); 
             cin>>vb;
             xy=(vb-round(total+((ttaxt*total)/100)));
             if(xy<0)
             {
                cout<<"\nSorry! You have paid Insufficient cash. Please reinitiate billing. Thank You."<<endl;
                cust_menu1();
             }
             else
             {
                cout<<"	     Change to be returned :   Kyats."<<xy<<endl;
                changeqty(pr1,q1);
                cout<<"-------------------------------------------------------------------------"<<endl;
             cout<<"\n\n	   WE ARE EAGERLY LOOKING FORWARD TO SERVE YOU AGAIN\n";
             cout<<"\n			    HAVE A NICE DAY !\n\n";
             cout<<"=========================================================================\n"<<endl;
             }
             cout << endl << press;
             cin.get();
             cin.ignore();
             cust_menu1();
      }
      else
      {
            cout<<"**************************  YOUR ID IS WRONG  ***************************"<<endl;
                  cust_menu1();
      }
}
//FUNCTION TO DISPLAY ALL THE PRODUCTS IN TABULAR FORM
void prod_tabular()
{
      int r=0,col=10;
      product st;
      ifstream inFile;
      inFile.open("product.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      product_detail_heading();
      while(inFile.read((char *) &st, sizeof(product)))
      {
            if(r<=12)
            {
                  r++;
                  st.showall(col);
                  col++;
            }
            else
            {
                  cout<<"----------------------------- Press any key ----------------------------"<<endl;
                  cin.get();
                  product_detail_heading();
                  col=10;
                  r=0;
            }
      }
      inFile.close();
      cin.get();
}
//Function to display heading of the product details
void product_detail_heading()
{
      cout<<"============================================================================================================================================"<<endl;
      cout<<"*************************   PRODUCTS DETAILS   *********************************************************************************************"<<endl;
      cout<<"============================================================================================================================================"<<endl;
      cout<<"PROD.NO"<<setw(14)<<"CATEGORY"<<setw(13)<<"NAME"<<setw(13)<<"COMPANY"<<setw(14)<<"PRICE"<<setw(22)<<"QUANTITY"<<setw(22)<<"DISCOUNT"<<endl;
      cout<<"---------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
}
//FUNCTION TO MODIFY RECORD
void modify_record(int n)
{
      product st,temp;
      char tmpnm[100],tmpcompany[100],tmpccategory[100];
      ifstream inFile;
      int fpos=-1;
      inFile.open("product.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      int flag=0;
      while(inFile.read((char *) &st, sizeof(product)))
      {
            if(st.retpno()==n)
            {
                  st.show_prod();
                  flag=1;
            }
      }
      inFile.close();
      if(flag==0)
            cout<<"\n\nRecord doesnot exist"<<endl;
      else
      {
            fstream File;
            File.open("product.csv",ios::binary|ios::in|ios::out);
            if(!File)
            {
                  cout<<"File could not be open !! Press any Key..."<<endl;
                  cin.get();
                  return;
            }
            while(File.read((char *) &st, sizeof(product)))
            {
                  if(st.retpno()==n)
                  {
                        fpos=(int)File.tellg();
                        break;
                  }
            }
            File.seekp(fpos-sizeof(product),ios::beg);
            strcpy(tmpccategory,st.getcatergory());
            strcpy(tmpnm,st.getname());
            strcpy(tmpcompany,st.getcompany());
            int q1=st.getqty();
            cout<<"===========   ENTER NEW VALUES FOR THE RECORDS GIVEN ABOVE   ==========="<<endl;
            temp.modifydata(n,tmpccategory,tmpnm,tmpcompany,q1);
            File.write((char *) &temp, sizeof(product));
            File.close();
      }
}
//FUNCTION TO DELETE THE RECORD OF THE PRODUCTS 
void delete_record(int n)
{
      product st;
      ifstream inFile;
      inFile.open("product.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      int flag=0;
      while(inFile.read((char *) &st, sizeof(product)))
      {
            if(st.retpno()==n)
            {
                  st.show_prod();
                  flag=1;
            }
      }
      inFile.close();
      char ch;
      if(flag==0)
            cout<<"\n\nRecord doesnot exist"<<endl;
      else
      {
            cout<<"DO YOU WANT TO DELETE THE RECORDS GIVEN ABOVE [YES(Y or y) OR NO(N or n)] : ";
            cin>>ch;
            if (toupper(ch)=='Y')
            {
                  ofstream outFile;
                  outFile.open("Temp1.csv",ios::binary);
                  ifstream objiff("product.csv",ios::binary);
                  objiff.seekg(0,ios::beg);
                  while(objiff.read((char *) &st, sizeof(product)))
                  {
                        if(st.retpno()!=n)
                        {
                              outFile.write((char *) &st, sizeof(product));
                        }
                  }
                  outFile.close();
                  objiff.close();
                  remove("product.csv");
                  rename("Temp1.csv","product.csv");
                  againopenandclose();
                  cout<<"------------------------------Record Deleted----------------------------"<<endl;
            }
      }
      cin.get();
}
void againopenandclose()
{
      ifstream inFile;
      product st;
      inFile.open("product.csv",ios::binary);
      if(!inFile)
      {
            cin.get();
            return;
      }
      while(inFile.read((char *) &st, sizeof(product)))
      {
      }
      inFile.close();
}
//Fuction to search the product
int search(int p)
{
      product st;
      int tmprt=0;
      ifstream inFile;
      inFile.open("product.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return -1;
      }
      int flag=0;
      while(inFile.read((char *) &st, sizeof(product)))
      {
            if(st.retpno()==p)
            {
                  st.show_prod();
                  flag=1;
                  tmprt=(int)inFile.tellg();
                  break;
            }
      }
      inFile.close();
      if(flag==0)
            return 1;
      else
      {
            return tmprt;
      }
}
//Function to change quantity of product
void changeqty(int pr1,int q11)
{
      product st;
      int fpos=-1;
      fstream File;
      File.open("product.csv",ios::binary|ios::in|ios::out);
      if(!File)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      while(File.read((char *) &st, sizeof(product)))
      {
            if(st.retpno()==pr1)
            {
                  fpos=(int)File.tellg();
                  break;
            }
      }
      File.seekp(fpos-sizeof(product),ios::beg);
      int q1=st.getqty();
      q1=q1-q11;
      if(q1>0)
      {
        st.setqty(q1);
      } 
      else
      {
            cout<<"Insufficient quantity !"<<endl;
            cout<<"Please reinitiate the billing process.Thank you."<<endl;
            admin_menu();
      }
        File.write((char *) &st, sizeof(product));
      File.close();
}
//Fuction to copy all record to a structure
void copyme(int k2,order order1[100],int q1,int &c2)
{
      ifstream objiff2("product.csv",ios::binary);
      product bk1;
      objiff2.seekg(k2-sizeof(product));
      objiff2.read((char*)&bk1,sizeof(product));
      strcpy(order1[c2].cag1,bk1.getcatergory());
      strcpy(order1[c2].pname1,bk1.getname());
      strcpy(order1[c2].compy1,bk1.getcompany());
      order1[c2].dis1=bk1.retdis();
      order1[c2].price1=bk1.retprice();
      //COPY RECORD
      order1[c2].qty1=q1;
      c2++;
      objiff2.close();
}
// INTRODUCTION FUNCTION
void banner()
{
    cout << "\t\t\t\t\t<----------------------------------------------->\t\t\t\t\t" << endl;
    cout << "\t\t\t\t\t<----------------Shop Managment----------------->\t\t\t\t\t" << endl;
    cout << "\t\t\t\t\t<----------------------------------------------->\t\t\t\t\t" << endl;
    cout << "\t\t\t\t\t<----------developed by LynnMyatAung------------>\t\t\t\t\t" << endl;
    cout << "\t\t\t\t\t<----------------vsersion beta------------------>\t\t\t\t\t" << endl;
    cout << endl << endl;
}
// Customer Menu Function
void customer_menu()
{
      char ch2;
      int num;
      cout<<"\n==========================   CUSTOMERS MENU   =========================="<<endl;
      cout<<"1.CREATE CUSTOMERS DETAILS"<<endl;
      cout<<"2.DISPLAY ALL CUSTOMERS DETAILS"<<endl;
      cout<<"3.SEARCH RECORD (QUERY) "<<endl;
      cout<<"4.MODIFY CUSTOMERS RECORDS"<<endl;
      cout<<"5.DELETE CUSTOMERS RECORDS"<<endl;
      cout<<"6.BACK"<<endl;
      cout<<" Enter the options (1-6) : " ;
      cin>>ch2;
      switch(ch2)
      {
            case '1':
                  system("cls");
                  banner();
                  write_customer();
                  customer_menu();
                  break;
            case '2':
                  system("cls");
                  banner();
                  cust_tabular();
                  customer_menu();
                  break;
            case '3':
                  system("cls");
                  banner();
                  cout<<"ENTER THE CUST ID TO BE SEARCHED : ";
                  cin>>num;
                  display_cust_sp(num);
                  customer_menu();
                  break;
            case '4':
                  system("cls");
                  banner();
                  cust_tabular();
                  cout<<"\nENTER THE CUST ID TO BE MODIFIED : ";
                  cin>>num;
                  modify_cust_record(num);
                  customer_menu();
                  break;
            case '5':
                  system("cls");
                  banner();
                  cust_tabular();
                  cout<<"\nENTER THE CUST ID TO BE DELETED : ";
                  cin>>num;
                  deletecust_record(num);
                  customer_menu();
                  break;
            case '6':

                  admin_menu();
                  break;
            default:
                  cout<<"Please enter valid option"<<endl;
                  cout << endl << press << endl;
                  cin.ignore();
                  customer_menu();
      }
}
// Product menu Function
void product_menu()
{
      char ch2;
      int num;
      cout<<"\n==========================   PRODUCTS MENU   ==========================="<<endl;
      cout<<"1.CREATE PRODUCTS"<<endl;
      cout<<"2.DISPLAY ALL PRODUCTS AVAILABLE"<<endl;
      cout<<"3.SEARCH RECORD (QUERY) "<<endl;
      cout<<"4.MODIFY PRODUCTS"<<endl;
      cout<<"5.DELETE PRODUCTS"<<endl;
      cout<<"6.BACK"<<endl;
      cout<<"Enter Options  (1-6) : ";
      cin>>ch2;
      switch(ch2)
      {
            case '1':
                  system("cls");
                  banner();
                  write_book();
                  product_menu();
                  break;
            case '2':
                  system("cls");
                  banner();
                  prod_tabular();//product_detail_heading();
                  product_menu();
                  break;
            case '3':
                  system("cls");
                  banner();
                  cout<<"\nENTER THE PRODUCT ID TO BE SEARCHED:"<<endl;
                  cin>>num;
                  display_sp(num);
                  product_menu();
                  break;
            case '4':
                  system("cls");
                  banner();
                  prod_tabular();
                  cout<<"\nENTER THE PRODUCT ID TO BE MODIFIED : ";
                  cin>>num;
                  modify_record(num);
                  product_menu();
                  break;
            case '5':
                  system("cls");
                  banner();
                  prod_tabular();
                  cout<<"\nENTER THE PRODUCT ID TO BE DELETED : ";
                  cin>>num;
                  delete_record(num);
                  product_menu();
                  break;
            case '6':
                  main_menu_login();
                  break;
            default:
                  cout<<"Error : Wrong Input ! < Try Again >" << endl;
                  cout << endl << press;
                  cin.ignore();
                  product_menu();
      }
}
// 1st type Function to be display customer options while placing order 
void cust_menu1()
{
      char ch2;
      int num;
      cout<<"\n-------------------------------------------------------------------------"<<endl;
      cout<<"		E N T E R   C U S T O M E R   D E T A I L S :\n";
      cout<<"-------------------------------------------------------------------------"<<endl;
      cout<<"1.CREATE NEW CUSTOMER DETAIL"<<endl;
      cout<<"2.DISPLAY ALL CUSTOMERS DETAILS"<<endl;
      cout<<"3.BACK "<<endl;
      cout<<"4.CONTINUE TO BILL\n"<<endl;
      cout<<"Please Enter options (1-4) : ";
      cin>>ch2;
      switch(ch2)
      {
            case '1':
                  write_customer1();
                  break;
            case '2':
                  cust_tabular();
                  cust_menu2();
                  break;
            case '3':
                  customer_menu();
                  break;
            case '4':
                  orderk=0;
                  place_order();
                  break;
            default:
                  cout<<"Please enter valid option"<<endl;
      }
}
// 2nd type Function to be display customer options while placing order 
void cust_menu2()
{
      char ch2;
      int num;
      cout<<"\n-------------------------------------------------------------------------"<<endl;
      cout<<"		C H O O S E   N E X T   O P T I O N S:\n";
      cout<<"-------------------------------------------------------------------------"<<endl;
      cout<<"1.CREATE NEW CUSTOMER DETAIL"<<endl;
      cout<<"2.BACK"<<endl;
      cout<<"3.CONTINUE TO BILL"<<endl;
      cout<<" Enter options (1-3) : ";
      cin>>ch2;
      switch(ch2)
      {
            case '1':
                  write_customer1();
                  break;
            case '2':
                  cashier_menu();
                  break;
            case '3':
                  orderk=0;
                  place_order();
                  break;
            default:
                  cout<<"Please enter valid option"<<endl;
                  cout << endl << press;
                  cin.ignore();
                  cust_menu2();
      }
}
// 3rd type Function to be display customer options while placing order 
void cust_menu3()
{
      char ch2;
      int num;
      cout<<"\n-------------------------------------------------------------------------"<<endl;
      cout<<"		C H O O S E   N E X T   O P T I O N S:\n";
      cout<<"-------------------------------------------------------------------------"<<endl;
      cout<<"1.DISPLAY ALL CUSTOMERS DETAILS"<<endl;
      cout<<"2.BACK"<<endl;
      cout<<"3.CONTINUE TO BILL\n"<<endl;
      cout<<"Please Enter options (1-3) : ";
      cin>>ch2;
      switch(ch2)
      {
            case '1':
                  cust_tabular();
                  cust_menu2();
                  break;
            case '2':
                  customer_menu();
                  break;
            case '3':
                  orderk=0;
                  place_order();
                  break;
            default:
                  cout<<"Please enter valid option"<<endl;
                  cout << press << endl;
                  cin.ignore();
                  cust_menu3();
      }
}
// Function for mainmenu

// Administrator menu function

void check_admin()
{   
      FILE *file;
      if (file = fopen("admin", "r"))
      {
            fclose(file);
            system("cls");
            banner();

            main_menu_login();
       }
      else
      {

            system("cls"); //cls console

            banner(); //call banner

            cout << "First,You need to creat admin acc!\nPlease,Remember the usrname and passwords." << endl;
            cout << endl<< "Plz Use user account as short name" << endl;
            admin_acc_create();
      }
      }


//first time admin_acc_create()
void admin_acc_create()
{   
      cout << endl;
      cout << "Enter the username\t:";
      getline(cin, usrname);
      if (usrname == "")
      {
            cout << endl<< "Warnning : Don't Enter the Blank for username !" << endl;
            cout << endl << press ;
            system("cls");
            admin_acc_create();
      }
      else
      {
            cout << "\nEnter the password\t:";
            getline(cin, passwd);
            cout << "ReEnter the password\t: ";
            getline(cin, passwd2);

            if (passwd == passwd2)
            {

                  ofstream reg("admin", ios::app);
                  reg << usrname << ' ' << passwd << endl;
                  cout << "\nRegistration Sucessful\n";
                  cout << endl << press << endl;
                  cin.ignore();
                  
                  main_menu_login();
            }
            else
            {
                  cout << endl<< "Error : Doesn't compare the passwords!\t <Try Again!>";           
                  cout << endl << press << endl;
                  cin.ignore();
                  system("cls");
                  banner();
                  admin_acc_create();
            }
      }
}

//main meny login
void main_menu_login()
{

      system("cls"); //cls console
      banner();        //call banner
      cout << endl<< "\t\t\t\t\t<------------------Main Login------------------->\t\t\t\t\t" <<endl <<  endl;
      cout << endl
            << "Enter the \"admin\" or \"cashier\" or \"exit\" : ";
      getline(cin, choice);
      if (choice == "admin")
      {
            login_as_admin();
      }
      else if (choice == "cashier")
      {
            login_as_cashier();
      }
      else if (choice == "exit")
      {
            system("exit");
      }
      else
      {
            
            cout << "Error : Wrong Input !!!" << endl;
            cout << endl << "Press any key to continue ..........";
            cin.ignore();  
            system("cls");

            main_menu_login();
      }
}

//login as admin
void login_as_admin()
{
      system("cls");
      banner(); //call the banner;
      cout << endl << "\t\t\t\t\t<-------------------Admin Login----------------->" << endl << endl;
      cout << "Enter the username : ";
      getline(cin, usrname);
      cout << "\nEnter the password : ";
      getline(cin, passwd);
      ifstream input("admin");
      //check admin usrname and passwd
      while (input >> requsrname >> requsrpasswd)
      {
            if (requsrname == usrname && requsrpasswd == passwd)

            {
                  count = 1;
                  system("cls");
            }
      }
      input.close();
      if (count == 1)
      {   
            admin_menu();
      }
      else
      {
            cout << endl<< "Error : Wrong UserName / Passwords! <Try Again!> " << endl;
            cout << endl << press ;
            cin.ignore();
            system("cls");
            login_as_admin();
      }
}

//log in as cashier
void login_as_cashier()
{
    system("cls");
    banner(); //call the banner;
    cout << endl<< "\t\t\t\t\t<-------------------Cashier Login----------------->" << endl << endl;
    cout << "Enter the username : ";
    getline(cin, usrname);
    cout << "Enter the password : ";
    getline(cin, passwd);
    ifstream input("cashier");
    //check admin usrname and passwd
    while (input >> requsrname >> requsrpasswd)
    {
        if (requsrname == usrname && requsrpasswd == passwd)

        {
                count = 1;
                system("cls");
        }
    }
    input.close();
    if (count == 1)
    {   
        cashier_menu();
    }
    else
    {
        cout << endl<< "Error : Wrong UserName / Passwords! " << endl;
        cout << endl<< "\t\tTry Again!" << endl;

        cout << endl << press;
        cin.ignore();
        system("cls");
        login_as_cashier();
    }
}

//admin menu
//login_admin
void admin_menu()
{
      system("cls");
      banner();
      cout << endl << "\t\t\t\t\t<-------------------Admin Menu------------------>" << endl << endl;
      cout << endl<< "Options admin can do ......."<< endl;
      cout << "[ 1 ]Account Management " << endl;
      cout << "[ 2 ]Product Management " << endl;
      cout << "[ 3 ]Customer Management" << endl;
      cout << "[ 4 ]Restart the Program" << endl;
      cout << "[ 5 ]Exit" << endl;
      cout << endl << "Select the Optiosn[1 - 5] : ";
      cin >> ch;
      switch (ch)
      {
            case '1':
                  acc_management();
                  break;
            case '2':
                  system("cls");
                  banner();
                  product_menu();
                  break;
            case '3':
                  system("cls");
                  banner();
                  customer_menu();
                  break;
            case '4':
                  restart();
                  break;
            case '5':
                  system("cls");
                  cout << "\t\t\t\t\t<---------------------Bye--------------------->" << endl;
                  system("exit");
                  break;

            default:

                  cout << endl<< "Wrong Input!" << endl;
                  cout << endl<< "<-------Please enter valid option------->" << endl;
                  cout << endl << press;
                  cin.ignore();
                  system("cls");
                  admin_menu();
    }
}

//acc_management
void acc_management()
{
      system("cls");
      banner(); // call the banner
      cout << "\t\t\t\t\t<---------------Account Management-------------->\t\t\t\t\t" << endl <<  endl;
      cout << "[ 1 ] Create Admin account" << endl;
      cout << "[ 2 ] Check all Admin accounts" << endl; // see admin accounts
      cout << "[ 3 ] Create Cashier account" << endl;
      cout << "[ 4 ] Check all Cashier accounts" << endl;//see cashier accounts
      cout << "[ 5 ] Delete accounts " << endl;
      cout << "[ 6 ] Back" << endl;
      cout << endl << "Select the Optiosn[1 - 4] : ";
      cin >> ch;
      //check usr input
      switch (ch)
      {
      case '1':
            admin_another_acc();
            break;
      case '2':
            see_admin_acc();
            break;

      case '3':
            create_cashier_acc();
            break;
      case '4':
            see_cashier_acc();
            break;
      case '5':
            delete_acc();
            break;

      case '6':
            admin_menu();
            break;

      
      default:
            
            cout << "Error : Wrong Input! < Try Again >" << endl ;
            cout << endl << press;
            cin.ignore();            
            acc_management();
            break;
      }


}


 
//admin another acc create
void admin_another_acc()
{
      banner();
      cout << "< Admin ACC Create >";
      cout << endl;
      cout << "Enter the username\t: ";
      getline(cin, usrname);
      if (usrname == "")
      {
            cout << endl<< "Warnning : Don't Enter the Blank for username !" << endl;
            cout << endl << press ;
            system("cls");
            admin_another_acc();
      }
      else
      {
            cout << "\nEnter the password\t : ";
            getline(cin, passwd);
            cout << "ReEnter the password\t : ";
            getline(cin, passwd2);

            if (passwd == passwd2)
            {

                  ofstream reg("admin", ios::app);
                  reg << usrname << ' ' << passwd << endl;
                  cout << "\nRegistration Sucessful\n";
                  cout << endl << press << endl;
                  cin.ignore();
                  
                  acc_management();
            }
            else
            {
                  cout << endl<< "Error : Doesn't compare the passwords!\t <Try Again!>";           
                  cout << endl << press << endl;
                  cin.ignore();
                  system("cls");
                  banner();
                  admin_another_acc();
            }
      }
}

//see admin acc

void see_admin_acc()
{
      system("cls");
      banner();
      cout << endl;  
      cout << "<------------Chack all Admin accounts----------->"<< endl;
      cout << "[ No ]  Username and Passwords" << endl;

      int x = 1;
      ifstream MyReadFile("admin");
      while (getline (MyReadFile, mytext))
      {   
            cout << "[ " << x << " ]  " << mytext << endl;
            x += 1;
      }
      cout << endl << press;
      cin.ignore();
      cin.get();
      acc_management();
}

//create_cashier ac
void create_cashier_acc()
{
      banner();
      cout << "< Cashier ACC Create >";
      cout << endl;
      cout << "Enter the username\t:";
      getline(cin, usrname);
      if (usrname == "")
      {
            cout << endl<< "Warnning : Don't Enter the Blank for username !" << endl;
            cout << endl << press ;
            system("cls");
            create_cashier_acc();
      }
      else
      {
            cout << "\nEnter the password\t:";
            getline(cin, passwd);
            cout << "ReEnter the password\t: ";
            getline(cin, passwd2);

            if (passwd == passwd2)
            {

                  ofstream reg("cashier", ios::app);
                  reg << usrname << ' ' << passwd << endl;
                  cout << "\nRegistration Sucessful\n";
                  cout << endl << press << endl;
                  cin.ignore();
                  
                  acc_management();
            }
            else
            {
                  cout << endl<< "Error : Doesn't compare the passwords!\t <Try Again!>";           
                  cout << endl << press << endl;
                  cin.ignore();
                  system("cls");
                  banner();
                  create_cashier_acc();
            }
      }
}

//see cashier acc
void see_cashier_acc()
{
      system("cls");
      banner();
      cout << endl;  
      cout << "<------------Chack all Cahier accounts----------->"<< endl;
      cout << "No   Username and Passwords" << endl;


      ifstream MyReadFile("cashier");
      int x = 1;
      while (getline (MyReadFile, mytext))
      {   
            cout  << "[ " << x << " ]  " << mytext << endl;
            x += 1;
      }
      MyReadFile.close();

      cout << endl << press;
      cin.ignore();
      cin.get();
      acc_management();
}


//delete accounts
void delete_acc()
{
      system("cls");
      banner();
      cout << "[+] Delete the account" << endl;
      cout << "\"admin\" or \" cashier\" > ";
      cin >> choice;



      

      if(choice == "admin")
      {     
            string total1;
            cout << "Note : if you create the admin acc in this process and try to delete it,You can not delete the acc. So restart the program !";
            cout << "Enter the Admin acc name\t\t\t: ";
            cin >> usrname;
            cout << "Enter "<< usrname <<"'s password\t\t\t: ";
            cin >> passwd;
            string total = usrname + " " + passwd;
            ifstream infile("admin");
            while (infile.good())
            {
                  string sLine;
                  getline(infile, sLine);
                  total1 = sLine;
                  break;
            }
            infile.close();
            if ( total1 == total){

                  cout << "Wronging ! You cannot delete the default admin account" << endl;
                  cout << endl << press << endl;
                  cin.ignore();
                  cin.get();
                  delete_acc();
            
            }
            else
            {    
                  string line;
                  ifstream fin;
                  ofstream tmp;
                  fin.open("admin");
                  tmp.open("tmp");
                  // cout << "Enter the Admin acc name : ";
                  // cin >> usrname;
                  // cout << "Enter "<< usrname <<"'s password : ";
                  // cin >> passwd;
                  // string total = usrname + " " + passwd;

                  while(getline(fin,line))
                  {
                        if (line != total)
                        {
                        //line.replace(line.find(total),usrname.length(),"");
                              tmp << line << endl;
                        }
                  }
                  tmp.close();
                  fin.close();
                  //system("del admin");
                  remove("admin");
                  
                  rename("tmp","admin");
                  cout << endl << "Deleted \"" << usrname << "\" account Successfully! " << endl;
                  cout << endl << endl << "Now Restart the program" << endl;          

            
            }


      }
      else if(choice == "cashier")
      {
            string line;
            ifstream fin;
            ofstream tmp;
            fin.open("cashier");
            tmp.open("tmp1");
            cout << "Enter the Cashier acc name\t\t\t: ";
            cin >> usrname;
            cout << "Enter "<< usrname <<"'s password\t\t\t: ";
            cin >> passwd;
            string total = usrname + " " + passwd;

            while(getline(fin,line))
            {
                  if (line != total)
                  {
                  //line.replace(line.find(total),usrname.length(),"");
                        tmp << line << endl;
                  }
            }
            tmp.close();
            fin.close();
            remove("cashier");
            rename("tmp1","cashier");
            cout << "Successfully Deleteed < Cashier \"" << usrname << "\" account >" << endl;
            cout << endl << "Now Restart the Program ....... " << endl ;
            
      }
      else
      {
            cout << endl << "Error : Wrong Input !";
            cout << endl << press << endl;
            cin.ignore();
            delete_acc();
      }
}

// restart the program
void restart()
{
    system("cls");
    banner();
    string z;
    cout << "Warning : All the Data will be delete when you restart the program..... !";
    cout << endl << "Are you sure to restart the whole system? " << endl;
    cout << "Yes or No  : ";
    cin >> z;
    if (z == "Yes" || z == "yes")
    {   
        system("cls");
        cout << endl << press << endl;
        remove("admin");
        remove("cashier");
        remove("product.cvs");
        cout<<"\n\n Restart Successfully!";
        cout << endl << press << endl;
        cin.ignore();
        cin.get();
        system("exit");

    }
    else if(z == "No" || z == "no")
    {   
        system("cls");
        cout << "Okay! Doesn't restart";
        cout << endl << endl << press;
        cin.ignore();
        cin.get();
        admin_menu();
    }
    else
    {   
        cout << endl << endl << "Error ! Wrong Input < Try Againg !> ";
        cout << endl << press;
        cin.ignore();
        cin.get();
        admin_menu();

    }

}


void cashier_menu()
{     

      system("cls");
      banner();
      cout<< "[+] Cashier Menu "<< endl;
      cout << "1. Customer Menu" << endl;
      cout << "2.Exit" << endl;
      cout << "Enter the options (1 - 2) : ";
      cin >> ch;
      switch (ch)
      {
      case '1':
            system("cls");
            banner();
            cust_menu1();
            cashier_menu();
            break;
      
      case '2':
                       
            main_menu_login();
            break;
      
      default:
            cout << "Wrong input! ";
            cout << endl << press;
            cin.ignore();
            cashier_menu();

            break;
      } 

}
// THE MAIN FUNCTION OF PROGRAM
int main()
{
      banner();
      check_admin();
      return 0;
}
