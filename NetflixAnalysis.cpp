#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//
//C++ program to analyze netflix movie reviews.
//
//Sydney Turner
//U. of Illinois, Chicago
//CS109, Fall 2017
//Project 09
//

 int Readnames(string moviename[],string movieFile)
 {
    int N;
     N=0;
     //string filename;
     ifstream file;
    
    //cin >> filename;
    
      file.open(movieFile.c_str());
   
   if( !file.is_open() ) //not open => error, stop now:
   {
       cout<<"**ERROR: unable to open file!" <<endl;
       exit(-1); //exit program with error code -1:
   }
     getline(file, moviename[N]);
    
    while (!file.eof()) // while not EOF marker:
     {
         N++; //count total number of movies:
         getline(file, moviename[N]);
     }
    
   return N; 
 }


 int Readreviews(int moviereviews[][3],string reviewFile)
 {   int countR;
     countR=0;
     //string filename;
     ifstream file;
    
     //cin >> filename;
    
      file.open(reviewFile.c_str());
   
  if( !file.is_open() ) //not open => error, stop now:
   {
      cout<<"**ERROR: unable to open file!" <<endl;
       exit(-1); //exit program with error code -1:
   }
     file>>moviereviews[0][0];
    file>>moviereviews[0][1];
     file>>moviereviews[0][2];
    
    while (!file.eof()) //while not EOF marker:
     {   countR++;
     
        file>>moviereviews[countR][0];
         file>>moviereviews[countR][1];
         file>>moviereviews[countR][2];
        
         
    }
    
 return countR;
 }
 
 
 void Computeaverage(int moviereviews[][3],string moviename[], double average[],int N, int countR, int totalreview[],double special[]) 
 {
     double sum=0.0;
     double countID=0.0;
     double countSpecial=0.0;
     
     
     
     
     
     for(int i=0; i<N; i=i+1)
     {
      sum=0.0;
      countID=0.0;
      countSpecial=0.0;
      
      
       for(int j=0; j<countR; j=j+1)
       {
        if(i+1==moviereviews[j][0])
        {
         countID++;
         sum=sum+moviereviews[j][2];
         if(moviereviews[j][1]<1000)
         {
          countSpecial++;
         }
        }
       }
       special[i]=countSpecial;
       totalreview[i]=countID;
       average[i]=sum/countID;
       
       
     }
     
     
 }
 
 void Histogram(int moviereviews[][3], int countR, int movieID, int hist[])
 {
   
//don't forget to add astericks to this:
   for(int i = 0; i < 5; i++)
    hist[i] = 0;
    

   for(int j=0; j<countR; j=j+1)
   {
       if(moviereviews[j][0]==movieID)
       {
         int rating = moviereviews[j][2];
         hist[rating - 1]++;
         
       }
   }

 }
 //void Symbols(int moviereviews[][3],countR)
 //{
  //int i=0;
  //for(int i=0; i<countR; i=i+1)
  //{
   //cout<<"*";
  //}
 //}
 
 
 
 
 
 int popularrating (double avg[], int N)
 {
  int max=0;
  for(int i=0; i<N; i=i+1)
 {
   if(avg[max]<avg[i])
   {
    max=i;
   }
  }
  return max;
 }
 

 
int main()
{
    string moviename[500];
    int moviereviews[20000][3];
    int movieID;
    string movieFile;
    string reviewFile;
    int totalreview[500];
    double special[500];
    int number;
    
    
    
   
    
    
    cin >> movieFile;
   
    
    cin >> reviewFile;
    
    cout<<"** Netflix Movie Analysis **"<<endl;
     int N;
     N=Readnames(moviename,movieFile);
     cout<<">>Number of movies: "<<N<<endl;
    
     int countR;
     countR= Readreviews(moviereviews,reviewFile);
     cout<<">>Number of reviews: "<<countR<<endl;
     double average[500];
     Computeaverage(moviereviews,moviename,average,N,countR,totalreview,special);
     int popular= popularrating(average,N);
      cout<<">>Most popular movie: "<<endl<<"#"<<popular+1<<": "<<"'"<<moviename[popular]<<"'"<<endl;
     cout<<"Rating: "<<average[popular]<<endl;
     
     cout<<endl;
     
     
    
     cout << "Enter a movie id (-1 to exit) > ";
     cin >> movieID;
     while(movieID!=-1)
     {
      
      if(movieID>N || movieID<1)
      {
       cout << "**Error: invalid movie id!";
      }
      else
      {
       cout<<moviename[movieID-1]<<endl;
       cout<<"Total reviews: "<<totalreview[movieID-1]<<endl;
       cout<<"Special reviews: "<<special[movieID-1]<<endl;
       cout<<"Average rating: "<<average[movieID-1]<<endl;
       int hist[5];
       Histogram(moviereviews,countR, movieID, hist);
       cout<<"Rating Histogram:"<<endl;
       for(int i = 4; i >= 0; i--){
        cout << i + 1 << ": ";
        for(int j=0; j < hist[i]; j++)
         cout << '*';
        cout << hist[i] << endl;
       }
      }
      cout<<endl;
      cout << "Enter a movie id (-1 to exit) >";
      cin>>movieID;
   
     }
     cout << "** Bye! **";
    
    
    
   

   
   
  
return 0;
}
