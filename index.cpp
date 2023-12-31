//User Screen
#include<bits/stdc++.h>
#include<string.h>
using namespace std;
# define INF 0x3f3f3f3f

typedef pair<int, int> iPair;
vector<string> areas(10);

typedef struct trip
{
    int pickup,drop,cabtype,price;
    string cabno,driver_name,cab_name;
}trip;

typedef struct cab
{
    int id;
    char cabno[9];
    int pickup;
    char driver_name[6];
    int drop;
    char cab_name[6];
    int cab_status; //Enter only 1 or 0. 1 for cab is not available, 0 for cab is available
    int avg_rating,earnings;
    int noofbookings;
}cab;

class admin
{
    string password,correct_password,email;
public:
    cab ob[20];
    admin()
    {
        email="admin";
        //password="admin123";
        correct_password="admin123";
    }
   // int admin_login();
    void admin_menu();
    void change_password();
    void cabs_detail();
    void driver_earnings(int i,int x);
    void add_cab();
    void delete_cab();
    void update_rating(int rate,int index);
    void showDriverRatings();
};

class user
{
    string mob,password,correct_password,name,email;
    char gender;
    int pickup,drop,cab_type,fare,driver_rating;
    bool cab_status;
    vector<trip> t;
    cab ob;
public:
    user()
    {
        email="user1";
        //password="user123";
        correct_password="user123";
    }
    int login();
    void signup();
    void change_pass();
    void book_cab();
    void trip_history();
    void trip_details();
    void getDriverRating(int c);
};

user u1;
admin a1;
int noofcabs;

class Graph
{
    int V; 
    list< pair<int, int> > *adj;    
public:
    Graph(int n);  
    void addEdge(int u, int v, int w); 
    int shortestPath(int s,int d);
};

Graph::Graph(int n) 
{
    V = n;
    adj = new list<iPair> [n];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

int Graph::shortestPath(int src,int dest)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    vector<int> dist(V, INF);
    pq.push(make_pair(0, src));
    dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;
            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist[dest];
}
Graph g(10);

void user_menu(int f);

int search_cab(char num[9])
{
    int i=0;
    while(strcmp(a1.ob[i].cabno,num)!=0 && i<noofcabs)
    {
        i++;
    }
    if(i<noofcabs)
    {
        return i;
    }
    return -1;
}

int user:: login()
{
  int f=0;
  char ch;
  string username;
  system("cls");
  cout<<"\n***************LOGIN***************"<<endl;
  do
  {
      cout<<"\nEnter Email: ";
      cin>>username;
      cout<<"\nEnter Password: ";
      cin>>password;
      if(password==correct_password && cab_status==0 && username==email)
      {
          system("cls");
          cout<<"\nLogged in Successfully!"<<endl;
          cout<<"Do you want to book  a cab? [Press 'y' for yes and 'n' for no] :"<<endl;
          cin>>ch;
          if(ch=='y')
            book_cab();
          else
            return 1;
          f=1;
          //sleep(1000);
      }
      else
      {
          cout<<"\nWrong credentials entered! \n Please login again";
          system("pause");
          f=0;
         // Sleep(1000);
      }
      system("cls");
  }while(f!=1);
  return f;
}

void user:: signup()
{
    int f=0;
    stringstream ss;
   do{
            fflush(stdin);
    cout<<"\nEnter your Name: ";
    getline(cin,name);
    cout<<"\nEnter email-id: ";
    cin>>email;
    cout<<"\nEnter Mobile no.: ";
    cin>>mob;
    cout<<"\nEnter your gender: [F/M]";
    cin>>gender;
    cout<<"\nEnter your password: ";
    cin>>password;
    cout<<"\nConfirm your password: ";
    cin>>correct_password;
    if(password==correct_password)
    {
        system("cls");
        f=1;
        login();
    }
    else
    {
        system("cls");
        cout<<"Entered passwords do not match please fill the form again!"<<endl;
    }
   }while(f!=1);
    system("cls");
}

void user:: change_pass()
{
    int f=0;
    cout<<"\nEnter new password: ";
    do
    {
        cin>>password;
        cout<<"\nConfirm new password: ";
        cin>>correct_password;
        if(password==correct_password)
        {
            system("cls");
            cout<<"\nPassword is changed successfully! ";
            f=1;
        }
        else
        {
            cout<<"\nEntered passwords do not match! Enter new password again: ";
        }
    }while(f!=1);
}

int allocate_cab(int start,int endp)
{
    int i=0;
    for(int i=0;i<10;i++)
    {
        if(a1.ob[i].drop==start && a1.ob[i].cab_status==0)
        {
            a1.ob[i].pickup=start;
            a1.ob[i].drop=endp;
            a1.ob[i].noofbookings+=1;
            return i;
        }
    }
    return -1;
}

void user:: book_cab()
{
    system("cls");
    int dist;
    char confirmation;
    cout<<"\nYou can book a cab between following areas:- ";
    for(int i=0;i<areas.size();i++)
    {
        cout<<"\n"<<i+1<<". "<<areas[i];
    }
    cout<<"\nEnter your choice of pickup location : ";
    cin>>pickup;
    cout<<"\nEnter your choice of drop location : ";
    cin>>drop;
    cout<<"\nYou can book a cab of following types:- ";
    cout<<"\n 1. Micro \n 2. Mini \n 3. Sedan \n 4. Luxury";
    cout<<"\nEnter your choice of cab type : [1/2/3/4]";
    cin>>cab_type;
    dist=g.shortestPath(pickup-1,drop-1);
    cout<<"\nShortest path between "<<areas[pickup-1]<<" and "<<areas[drop-1]<<" is of "<<dist<<" kms.";
    fare=(7 + cab_type)*dist;
    cout<<"\nFare of your trip would be Rs."<<fare<<".00! Are you sure you want to book a cab?[Y/N]";
    cin>>confirmation;
    if(confirmation=='Y'||confirmation=='y')
    {
        int c;
        c=allocate_cab(pickup,drop);
        if(c!=-1)
        {
            cout<<"You are allocated "<<a1.ob[c].cabno<<"! Enjoy your ride!"<<endl;
            system("pause");
            int i=0;
        cab_status=1;
        trip tmp;
        tmp.cabno=a1.ob[c].cabno;
        tmp.cab_name=a1.ob[c].cab_name;
        tmp.cabtype=cab_type;
        tmp.driver_name=a1.ob[c].driver_name;
        tmp.drop=drop;
        tmp.pickup=pickup;
        tmp.price=fare;
        t.push_back(tmp);
        a1.driver_earnings(c,fare);
        cout<<"You are on your way!";
        system("pause");
        getDriverRating(c);
        }
        else
        {
            cout<<"\nSorry! No cabs available right now :( ";
            system("pause");
        }
}
}

void user::trip_history()
{
    if(t.size()==0)
    {
        cout<<"\nYou haven't had any trip with our services yet! ";
    }
    else
    {
        for(int i=0;i<t.size();i++)
        {
             cout<<"\nTrip number :"<<i+1;
             cout<<"\nCab name and number :"<<t[i].cab_name<<t[i].cabno;
             cout<<"\nDriver name :"<<t[i].driver_name;
             cout<<"\nPickup location :"<<areas[(t[i].pickup)-1];
             cout<<"\nDrop location :"<<areas[(t[i].drop)-1];
             cout<<"\nFare: Rs."<<t[i].price<<".00";
        }
    }
}

void user::trip_details()
{
    int x=t.size()-1;
    cout<<"\nCab name: \nCab number :"<<t[x].cab_name<<t[x].cabno;
    cout<<"\nDriver name :"<<t[x].driver_name;
    cout<<"\nPickup location :"<<areas[(t[x].pickup)-1];
    cout<<"\nDrop location :"<<areas[(t[x].drop)-1];
    cout<<"\nFare: Rs."<<t[x].price<<".00";
}

void user::getDriverRating(int c)
{
    cout<<"\nPlease rate the driver with 1/2/3/4/5 stars";
    cout<<"\nEnter how many stars you want to give: ";
    cin>>driver_rating;
    a1.update_rating(driver_rating,c);
    system("cls");
    cout<<"\nThank you for rating the driver!";
}

/*int admin:: admin_login()
{
  int f=0;
  char ch;
  string username;
  system("cls");
  cout<<"\n***************ADMIN LOGIN***************"<<endl;
  do
  {
      cout<<"\nEnter Email: ";
      cin>>username;
      cout<<"\nEnter Password: ";
      cin>>password;
      if(password==correct_password && username==email)
      {
          system("cls");
          cout<<"\nLogged in Successfully!"<<endl;
          admin_menu();
          f=1;
      }
      else
      {
          cout<<"\nWrong credentials entered! \n Please login again";
          system("pause");
          f=0;
      }
      //system("cls");
  }while(f!=1);
  return f;
}
*/
void admin:: change_password()
{
    string pass,pas1;
    int f=0;
    system("pause");
    cout<<"\nEnter new password: ";
    do
    {
        cin>>pass;
        cout<<"\nConfirm new password: ";
        cin>>pas1;
        if(pass==pas1)
        {
            system("cls");
            correct_password=pas1;
            cout<<"\nPassword is changed successfully! ";
            system("pause");
            f=1;
        }
        else
        {
            system("cls");
            cout<<"\nEntered passwords do not match! Enter new password again: ";
            system("pause");
        }
    }while(f!=1);
}

void admin:: cabs_detail()
{
    for(int i=0;i<noofcabs;i++)
    {
        cout<<"\nCab's ID: "<<a1.ob[i].id;
        cout<<"\nCab number: "<<a1.ob[i].cabno;
        cout<<"\nCab booking status: "<<a1.ob[i].cab_status;
        cout<<"\nDriver_name: "<<a1.ob[i].driver_name;
        cout<<"\ncab's current pickup: "<<a1.ob[i].pickup;
        cout<<"\nCab name: "<<a1.ob[i].cab_name;
        cout<<"\ncab's current drop: "<<a1.ob[i].drop;
        cout<<"\nAvg_rating: "<<a1.ob[i].avg_rating<<endl;
        cout<<"cab's earnings till now: "<<a1.ob[i].earnings<<endl;
        cout<<"cab's total no. of booking with us till now: "<<a1.ob[i].noofbookings<<endl;
    }
}

void admin:: driver_earnings(int i,int x)
{
    ob[i].earnings=ob[i].earnings+x;
}

void admin:: add_cab()
{
    cab c;
    cout<<"Enter cab number: "<<endl;
        cin>>c.cabno;
        cin.clear();
        cout<<"Enter cab booking status: "<<endl;
        cin>>c.cab_status;
        cin.clear();
        cout<<"Enter driver_name: "<<endl;
        cin>>c.driver_name;
        cin.clear();
        cout<<"Enter cab's current pickup: "<<endl;
        cin>>c.pickup;
        cin.clear();
        cout<<"Enter cab name: "<<endl;
        cin>>c.cab_name;
        cin.clear();
        cout<<"Enter cab's current drop: "<<endl;
        cin>>c.drop;
        cin.clear();
        c.avg_rating=5;
        cout<<"Enter cab's earnings till now: "<<endl;
        cin>>c.earnings;
        cin.clear();
        cout<<"Enter cab's total no. of booking with us till now: "<<endl;
        cin>>c.noofbookings;
        cin.clear();
        c.id=((int)(c.cabno[5])*1000) + ((int)(c.cabno[6])*100) + ((int)(c.cabno[7])*10) + ((int)(c.cabno[8]));
    ob[10]=c;
    noofcabs+=1;
}

void admin::delete_cab()
{
    char num[9];
    cout<<"\nEnter the cab number of the cab: ";
    cin>>num;
    int i=search_cab(num);
    if(i!=-1)
    {
        cab tmp;
        tmp=a1.ob[i];
        a1.ob[i]=a1.ob[noofcabs-1];
        a1.ob[noofcabs-1]=tmp;
        cout<<"\nCab is deleted from our services!";
        noofcabs--;
    }
    else
    {
        cout<<"\nCab not found!";
    }
}

void admin::showDriverRatings()
{
    for(int i=0;i<noofcabs;i++)
    {
        cout<<"\nDriver_name: "<<a1.ob[i].driver_name;
        cout<<"\nAvg_rating: "<<a1.ob[i].avg_rating<<endl;
        cout<<"cab's earnings till now: "<<a1.ob[i].earnings<<endl;
    }
}

void admin:: update_rating(int rate,int index)
{
    a1.ob[index].avg_rating=(a1.ob[index].avg_rating+rate)/a1.ob[index].noofbookings;
}

void admin_menu(int choice,int f)
{
    int ch1;
    if(choice==3 && f==1)
    {
        do{
        cout<<"***************OPTIONS***************"<<endl;
          cout<<"\t1. CHANGE PASSWORD"<<endl;
          cout<<"\t2. DISPLAY THE CABS WHICH ARE ALREADY ADDED WITH OUR SERVICES"<<endl;
          cout<<"\t3. ADD ANOTHER CAB"<<endl;
          cout<<"\t4. DELETE A CAB"<<endl;
          cout<<"\t5. SHOW ANY DRIVER'S RATING"<<endl;
          cout<<"\t6. UPDATE ANY DRIVER'S RATING"<<endl;
          cout<<"\t7. EXIT"<<endl;
          cin>>ch1;
          switch(ch1)
          {
    case 1:{
        a1.change_password();
        //a1.admin_login();
        break;}
    case 2:{
        a1.cabs_detail();
        break;}
    case 3:{
        a1.add_cab();
        break;}
    case 4:{
        a1.delete_cab();
        break;}
    case 5:{
        a1.showDriverRatings();
        break;}
    case 6:{
        int f,rate;
        char cbn[9];
        system("cls");
        cout<<"\nEnter the cab number whose driver's rating you want to update: "<<endl;
        cin>>cbn;
        cin.clear();
        cout<<"\nEnter how much you want to rate him: [1/2/3/4/5]"<<endl;
        cin>>rate;
        f=search_cab(cbn);
        a1.update_rating(rate,f);}
    case 7:{
        system("cls");
        cout<<"QUITTING.............."<<endl;
        break;}
    default:{
        system("cls");
        cout<<"QUITTING.............."<<endl;
        break;}

    }
    }while(ch1!=7);
    }
}

int main()
{
    int f;
    areas[0]="Sector 62";
    areas[1]="Sector 128";
    areas[2]="Botanical Garden";
    areas[3]="Sector 18";
    areas[4]="Kaushambi";
    areas[5]="Anand Vihar";
    areas[6]="Rajiv Chowk";
    areas[7]="Kashmere Gate";
    areas[8]="Nehru Place";
    areas[9]="Pari Chowk";
    g.addEdge(0, 1, 19);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    g.addEdge(9, 5, 30);
    g.addEdge(9, 3, 25);
    int choice,i;
    fstream fil,fil2;
    fil.open("cabdatabase.txt",ios::in);
    i=0;
    cab c;
    char ch;
    int ch1;
    while(!fil.eof())
    {
        fil.read((char*) &c,sizeof(c));
        a1.ob[i]=c;
        i++;
    }
    noofcabs=i;
    fil.close();
    int t=1;
    do{cout<<"\n***************MAIN MENU***************"<<endl;
    cout<<"\t1. USER LOGIN"<<endl;
    cout<<"\t2. USER SIGNUP"<<endl;
    //cout<<"\t3. ADMIN LOGIN"<<endl;
    cout<<"\t3. EXIT"<<endl;
    cout<<"\n\tEnter your choice: "<<endl;
    cin>>choice;
    switch(choice){
    case 1:
       {
        f=u1.login();
        break;}

    case 2:{
        user u2;
        u2.signup();
        break;}

    /*case 3:
       {
        //f=a1.admin_login();
        break;}*/

    case 3:{
        system("cls");
        t=0;
        cout<<"QUITTING.............."<<endl;
        break;
    }}}while(t!=0);
    fil.open("cabdata1.txt",ios::out);
    for(int i=0;i<noofcabs;i++)
    {
        cab c=a1.ob[i];
        fil.write((char*) &c,sizeof(c));
    }
    fil.close();
    /*fil.open("cabdata1.txt",ios::in);
    fil2.open("cabdatabase.txt",ios::out);
    while (!fil.eof())
    {
         fil.get(ch);
         fil2<<ch;
    }
    fil2.close();
    fil.close();*/
    areas.clear();
//    free(g);
    return 0;
}
