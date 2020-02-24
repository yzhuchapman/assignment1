#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main(int argc, char** argv){
  int control=0;
  if(argc<2){
    control=1;
  }
  while(true){
    string filename;
  if(control==0){
    filename=argv[1];
  }else{
    cout << "enter the file name to be processed";
    string fn;
    cin>>fn;
    filename=fn;
  }
  string line;
  string input="";
  ifstream file;
  float count;
  float count2;
  float sum=0;
  float varianceCount;
  float varianceCountTotal=0;
  float acount=0;
  float ccount=0;
  float tcount=0;
  float gcount=0;
  float aprob=0;
  float cprob=0;
  float tprob=0;
  float gprob=0;
  //open the file and iterate through each line and store them in a string then close the file
  file.open(filename);
  if (file.is_open())
    {
      while (getline(file,line))
      {
        sum+=line.length()-1;
        input+=line+"\n";
        count++;
      }
      file.close();
    }
  else {
    cout << "Unable to open file";
  }
  sum++;
  float mean=sum/count;
  file.open(filename);
  if (file.is_open())
    {
      while (getline(file,line))
      {
        count2++;
        if (count2==count)
        {
          varianceCount=line.length()-mean;
        }
        else {
          varianceCount=line.length()-1-mean;
        }
        varianceCountTotal+=pow(varianceCount,2);
      }
      file.close();
    }
  else {
    cout << "Unable to open file";
  }
  float variance=varianceCountTotal/count;
  float std = sqrt(variance);
  //convert the characters in the string to lowercased and compute relative probability of each nucleotide and probability of nucleotide bigram
  for(int i=0;i<input.length();++i){
    input[i]=tolower(input[i]);
    if (input[i]=='a'){
      acount++;
    }
    else if(input[i]=='c'){
      ccount++;
    }
    else if(input[i]=='t'){
      tcount++;
    }
    else if(input[i]=='g'){
      gcount++;
    }
  }
  aprob=acount/sum;
  cprob=ccount/sum;
  tprob=tcount/sum;
  gprob=gcount/sum;
  float aaprob=aprob*aprob;
  float acprob=aprob*cprob;
  float atprob=aprob*tprob;
  float agprob=aprob*gprob;
  float caprob=cprob*aprob;
  float ccprob=cprob*cprob;
  float ctprob=cprob*tprob;
  float cgprob=cprob*gprob;
  float taprob=tprob*aprob;
  float tcprob=tprob*cprob;
  float tgprob=tprob*gprob;
  float ttprob=tprob*tprob;
  float gaprob=gprob*aprob;
  float gtprob=gprob*tprob;
  float gcprob=gprob*cprob;
  float ggprob=gprob*gprob;
  //print the summary statistcs to a file
  ofstream file1;
  file1.open("JerryZhu.out");
  file1 << "JerryZhu\nID: 002294410\nSum: " << sum << "\nMean: " << mean << "\nVariance: "<< variance << "\nStandard deviation: " << std << "\nA relative probability: " << aprob
  << "\nC relative probability: " << cprob << "\nG relative probability: " << gprob << "\nT relative probability: " << tprob << "\nAA probability" << aaprob << "\nAC probability" << acprob
  << "\nAT probability" << atprob << "\nAG probability" << agprob << "\nCA probability" << caprob << "\nCT probability" << ctprob << "\nCG probability" << cgprob
  << "\nCC probability" << ccprob << "\nTA probability" << taprob << "\nTC probability" << tcprob << "\nTG probability" << tgprob << "\nTT probability" << ttprob
  << "\nGA probability" << gaprob << "\nGT probability" << gtprob << "\nGC probability" << gcprob << "\nGG probability" << ggprob << "\n";
  //generate new DNA strings
  string output="";
  for (int i=0;i<1000;++i){
    float a = ((float) rand() / (RAND_MAX));
    float b = ((float) rand() / (RAND_MAX));
    float c = sqrt(-2*log (a))*cos(2*M_PI*b);
    int d = (int) std*c+mean;
    for (int i=0;i<d;++i){
      float p = ((float) rand() / (RAND_MAX));
      string s="";
      if(p>=0&&p<aprob){
        s="a";
      }
      else if(p>=aprob&&p<aprob+cprob){
        s="c";
      }
      else if(p>=aprob+cprob&&p<aprob+cprob+tprob){
        s="t";
      }
      else if(p>=aprob+cprob+tprob&&p<1){
        s="g";
      }
      output+=s;
    }
    output+="\n";
  }
 file1 << output;
 file1.close();
 //ask if user wants to continue
 cout << "Type 0 to exit, type anythingelse to continue.";
 int x;
 cin >> x;
 if(x==0){
   break;
 }else{
   control++;
 }
}
 return 0;
}
