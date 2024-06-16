#include<iostream>
#include<string>
#include <cctype>
#include<fstream>
using namespace std;
class Evaluationreport{
    friend ostream& operator<<(ostream&, Evaluationreport&);
    friend istream& operator>>(istream&, Evaluationreport&);
    private:
    string fname;
    string lname;
    string rnumber;
    int q1,q2,q3,q4;
    int a1,a2,a3,a4;
    public:
    static int totalstudents, totalquizzes, totalassignments;
    static int q[4];
    static int a[4];
    static int max[8];
    static int min[8];
    static int avg[8];
    static void setmax(int *maximum){
        for(int i = 0 ; i < 8 ; i++){
            max[i] = maximum[i];
        }
    }
    static void setmin(int *minimum){
        for(int i = 0 ; i < 8 ; i++){
            min[i] = minimum[i];
        }
    }
    static void setavg(int *average){
        for(int i = 0 ; i < 8 ; i++){
            avg[i] = average[i];
        }
    }

    static void setquiz(int *quiz){
        for(int i = 0 ; i < 4 ; i++){
            q[i] = quiz[i];
        }
    }
    static void setassignments(int *assignments){
        for(int i = 0 ; i < 4 ; i++){
            a[i] = assignments[i];
        }
    }
    static int* getquiz(){
        return q;
    }
    static int* getassignments(){
        return a;
    }
    static int* getavg(){
        return avg;
    }
    static int* getmax(){
        return max;
    }
    static int* getmin(){
        return min;
    }
    Evaluationreport(){   //default constructor
        fname = " ";
        lname = " ";
        rnumber = " ";
        q1=0;q2=0;q3=0;q4=0;
        a1=0;a2=0;a3=0;a4=0;
    }
    static int gettotalstudents(){return totalstudents;};
    int getq1(){
        return q1;
    }
     int getq2(){
        return q2;
    }
     int getq3(){
        return q3;
    }
     int getq4(){
        return q4;
    }
   
    int geta1(){
        return a1;
    }
    int geta2(){
        return a2;
    }
    int geta3(){
        return a3;
    }
    int geta4(){
        return a4;
    }
    int gettotal(){
        int sum = 0;
        for(int i = 0 ; i < 4 ; i++){
           sum = sum + q[i];
        }
        for(int i = 0 ; i < 4 ; i++){
            sum = sum + a[i];
        }
        return sum;
    }
    int gettotalmarks(){
        return(q1+q2+q3+q4+a1+a2+a3+a4);
    }
    string getfirstname(){
        return fname;
    }
    string getlastname(){
        return lname;
    }
    string getrollno(){
        return rnumber;
    }




};
istream& operator>>(istream& in, Evaluationreport& obj)
{
	in>>obj.fname;
    in>>obj.lname;
    in>>obj.rnumber;
    in>>obj.q1;
    in>>obj.q2;
    in>>obj.q3;
    in>>obj.q4;
    in>>obj.a1;
    in>>obj.a2;
    in>>obj.a3;
    in>>obj.a4;

}
   

ostream& operator<<(ostream& out , Evaluationreport& obj){
    out<<obj.fname<<" ";
    out<<obj.lname<<"\t";
    out<<obj.rnumber<<"\t";
    out<<obj.q1<<"\t";
    out<<obj.q2<<"\t";
    out<<obj.q3<<"\t";
    out<<obj.q4<<"\t";
    out<<obj.a1<<"\t";
    out<<obj.a2<<"\t";
    out<<obj.a3<<"\t";
    out<<obj.a4<<"\t";
    out<<obj.gettotalmarks();
 
    return out;
}

// initializing all static variables
int Evaluationreport::totalstudents = 0;
int Evaluationreport::totalquizzes = 0;
int Evaluationreport::totalassignments=0;
int Evaluationreport::q[4] = { 0,0,0,0 };
int Evaluationreport::a[4] = { 0,0,0,0 };
int Evaluationreport::max[8] = { 0,0,0,0,0,0,0,0 };
int Evaluationreport::min[8] = { 0,0,0,0,0,0,0,0 };
int Evaluationreport::avg[8] = { 0,0,0,0,0,0,0,0 };

// reading data from file 

Evaluationreport  * Readdatafromfile(ifstream&myfile,Evaluationreport*&Evalreport){
    Evaluationreport *array = new Evaluationreport[42];
    if(!myfile){
        cout<<"error file not found1 \n";
    }
    else {
        for(int i = 0 ;  i< 42 ; i++){
            myfile >> array[i];
           
        }
    }
    
return array;
  
}
const int rows = 50;
void print(int array[8] ){
     for(int i = 0 ; i < 8 ; i++){
            cout<<array[i]<<" ";
        }

}
// creating all statistics table 
void updatestatistics(  Evaluationreport *evalreport, int numstudents){
    cout<<"\tQ1 Q2 Q3 Q4 A1 A2 A3 A4\n";
    int *total ;
    for(int i = 0 ; i < 4 ; i++){
    total = evalreport[i].getquiz();
    }
    cout<<"total   "; print(total);
    cout<<endl;
    int max = 0;
    int maximum[8];   // array for max marks
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].getq1() > max){
           
            max = evalreport[i].getq1();
        }
    }   
    maximum[0] = max;max = 0;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].getq2() > max){
           
            max = evalreport[i].getq2();
        }
    }   
    maximum[1] = max;max =0;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].getq3() > max){
           
            max = evalreport[i].getq3();
        }
    }   
    maximum[2] = max;max=0;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].getq4() > max){
           
            max = evalreport[i].getq4();
        }
    }   
    maximum[3] = max;max = 0;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].geta1() > max){
           
            max = evalreport[i].geta1();
        }
    }   
    maximum[4]= max;
    max = 0;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].geta2() > max){
           
            max = evalreport[i].geta2();
        }
    }   
    maximum[5]= max;max = 0;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].geta3() > max){
           
            max = evalreport[i].geta3();
        }
    }   
    maximum[6]= max;max = 0;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].geta4() > max){
           
            max = evalreport[i].geta4();
        }
    }   
    maximum[7]= max;
    max = 0;
    cout<<"maximum " ; print(maximum);
    Evaluationreport:: setmax(maximum);
    int min = 100;
    int minimum[8];         // array for minimum marks 
    for(int i = 0 ; i < 42 ; i++){
        if(evalreport[i].getq1() < min){
           
            min = evalreport[i].getq1();
        }
    }   
    minimum[0] = min;min =100;
    for(int i = 0 ; i < 42 ; i++){
        if(evalreport[i].getq2() < min){
           
            min = evalreport[i].getq2();
        }
    }   
    minimum[1] = min;min =100;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].getq3() < min){
           
            min = evalreport[i].getq3();
        }
    }   
    minimum[2] = min;min=100;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].getq4() < min){
           
            min = evalreport[i].getq4();
        }
    }   
    minimum[3] = min;min = 100;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].geta1() < min){
           
            min = evalreport[i].geta1();
        }
    }   
    minimum[4]= min;min = 0;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].geta2() < min){
           
            min = evalreport[i].geta2();
        }
    }   
    minimum[5]= min;min =100;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].geta3() < min){
           
            min = evalreport[i].geta3();
        }
    }   
    minimum[6]= min;min = 100;
    for(int i = 0 ; i < numstudents ; i++){
        if(evalreport[i].geta4() < min){
           
            min = evalreport[i].geta4();
        }
    }   
    minimum[7]= min;
    cout<<endl;
    cout<<"minimum  " ;print(minimum);
    Evaluationreport:: setmin(minimum);
    int average[8];  // array for average
    double sum = 0;
    for(int i = 0 ;i < numstudents ; i++){
        sum = (sum + evalreport[i].getq1()) ;
    }
    average[0]= sum / numstudents; sum=0;
    for(int i = 0 ;i < numstudents ; i++){
        sum = (sum + evalreport[i].getq2()) ;
    }
    average[1]= sum/numstudents; sum=0;
    for(int i = 0 ;i < numstudents ; i++){
        sum = (sum + evalreport[i].getq3()) ;
    }
    average[2]= sum / numstudents; sum=0;
    for(int i = 0 ;i < numstudents ; i++){
        sum = (sum + evalreport[i].getq4()) ;
    }
    average[3]= sum / numstudents; sum=0;
    for(int i = 0 ;i < numstudents ; i++){
        sum = (sum + evalreport[i].geta1()) ;
    }
    average[4]= sum/numstudents; sum=0;
    for(int i = 0 ;i < numstudents ; i++){
        sum = (sum + evalreport[i].geta2()) ;
    }
    average[5]= sum/numstudents; sum=0;
    for(int i = 0 ;i < numstudents ; i++){
        sum = (sum + evalreport[i].geta3());
    }
    average[6]= sum/numstudents; sum=0;
    for(int i = 0 ;i < numstudents ; i++){
        sum = (sum + evalreport[i].geta4()) ;
    }
    average[7]= sum/numstudents; sum=0;
    cout<<"\naverage "; print(average);
    Evaluationreport:: setavg(average);
}

Evaluationreport* printAll(Evaluationreport* array,int count){
    
    for(int i = 0 ; i <  count; i++){
        cout<< array[i]<<endl;
    }
}
Evaluationreport* searchstudentsbykeyword(const string& keyword, Evaluationreport *evalreport,int numstudents ){

    Evaluationreport *matched = new Evaluationreport[42];
    int count = 0;
    for(int i = 0 ; i < numstudents ; i++){
        const string fname = evalreport[i].getfirstname();  // gets the name and rollnumber as string
        const string lname = evalreport[i].getlastname();
        const string rollno = evalreport[i].getrollno();
     
        bool match = false;
        int index = 0;
         for(int j = 0 ; j< fname.length() ; j++){   // traverses each name char by char and sees if equal to keyword
            if(fname[j] == keyword[index]){
                index++;
                if(index == keyword.length()){
                    match = true;
                    break;
                }
            }
         }
          if(!match){                              // if not first name then checks for last name
            index = 0;
            for(int j = 0 ; i < lname.length() ; j++){
                if(lname[j] == keyword[index]){
                    index++;
                    if(index == keyword.length()){
                        match == true;
                        break;
                    }
                }
            }
          }

          if(!match){                          // if not then rollnumber
            index = 0;
            for(int j = 0 ; j < rollno.length() ; j++){
                if(rollno[j] == keyword[index]){
                    index++;
                    if(index == keyword.length()){
                        match = true;
                        break;
                    }
                }
            }
          }
          if(match){                     // if even one same then copies the index to new array
            matched[count++]= evalreport[i];
          }
    }
    
    printAll(matched,count);  //sends new array for printing
}

void sortlistbytotal(Evaluationreport *evalreport, int numstudents) {
    for (int i = 0; i < numstudents; i++) {
        for (int j = i+ 1; j < numstudents  ; j++) {
            if (evalreport[i].gettotalmarks() > evalreport[j].gettotalmarks()) {
                Evaluationreport temp = evalreport[i]; // Storing the value of evalreport[i] in temp
                evalreport[i] = evalreport[j];
                evalreport[j] = temp;
            }
        }
    }
    printAll(evalreport, numstudents);
}

void printdetail(string rollnumber, Evaluationreport *evalreport, int numstudents){
    bool found = false;
    int f = 0;
    for(int i = 0 ; i < numstudents ; i++){
        const string rollno = evalreport[i].getrollno();
        int index = 0;
            for(int j = 0 ; j < rollno.length() ; j++){
                if(rollno[j] == rollnumber[index]){
                    index++;
                    if(index == rollnumber.length()){
                        found = true;
                        f = i;
                        break;
                    }
                }
                
            }
            if(found){
                break;
            } 
          }

          if(found == true){
            cout<<"Student found\n";
            
            cout<<"Roll number: ";cout<<evalreport[f].getrollno()<<endl;
            cout<<"Name : ";cout<<evalreport[f].getfirstname()<<evalreport[f].getlastname();
            cout<<"\n\nQuiz\n";
            cout<<"   Marks\tTotalMarks \tMinimum \tMaximum \tAverage\n";
            cout<<"1. "<<evalreport[f].getq1()<< "\t\t"; cout<< evalreport[f].q[0]<<"\t\t"<<evalreport[f].min[0]<<"\t\t"<<evalreport[f].max[0]<<"\t\t"<<evalreport[f].avg[0]<<endl;
            cout<<"2. "<<evalreport[f].getq2()<< "\t\t"; cout<< evalreport[f].q[1]<<"\t\t"<<evalreport[f].min[1]<<"\t\t"<<evalreport[f].max[1]<<"\t\t"<<evalreport[f].avg[1]<<endl;
            cout<<"3. "<<evalreport[f].getq3()<< "\t\t"; cout<< evalreport[f].q[2]<<"\t\t"<<evalreport[f].min[2]<<"\t\t"<<evalreport[f].max[2]<<"\t\t"<<evalreport[f].avg[2]<<endl;
            cout<<"4. "<<evalreport[f].getq4()<< "\t\t"; cout<< evalreport[f].q[3]<<"\t\t"<<evalreport[f].min[3]<<"\t\t"<<evalreport[f].max[3]<<"\t\t"<<evalreport[f].avg[3]<<endl;
            cout<<"\n\nAssignments\n";
            cout<<"   Marks\tTotalMarks \tMinimum \tMaximum \tAverage\n";
            cout<<"1. "<<evalreport[f].geta1()<< "\t\t"; cout<< evalreport[f].a[0]<<"\t\t"<<evalreport[f].min[4]<<"\t\t"<<evalreport[f].max[4]<<"\t\t"<<evalreport[f].avg[4]<<endl;
            cout<<"2. "<<evalreport[f].geta2()<< "\t\t"; cout<< evalreport[f].a[1]<<"\t\t"<<evalreport[f].min[5]<<"\t\t"<<evalreport[f].max[5]<<"\t\t"<<evalreport[f].avg[5]<<endl;
            cout<<"3. "<<evalreport[f].geta3()<< "\t\t"; cout<< evalreport[f].a[2]<<"\t\t"<<evalreport[f].min[6]<<"\t\t"<<evalreport[f].max[6]<<"\t\t"<<evalreport[f].avg[6]<<endl;
            cout<<"4. "<<evalreport[f].geta4()<< "\t\t"; cout<< evalreport[f].a[3]<<"\t\t"<<evalreport[f].min[7]<<"\t\t"<<evalreport[f].max[7]<<"\t\t"<<evalreport[f].avg[7]<<endl;

            cout<<"Total Marks: \t"<< evalreport[f].gettotalmarks() <<" / "<< evalreport[f].gettotal();
            
          }
          else {
            cout<<"Student with roll number " << rollnumber<< " not found\n";
          }

    }




int main(){
    ifstream myfile;
    myfile.open("gradesheet.txt");
    int tstudents,tquizzes,tassignments;
    myfile>>tstudents>>tquizzes>>tassignments;
    cout<<"Total students: "<<tstudents<<endl;
    cout<<"Total quizzes: "<<tquizzes<<endl;
    cout<<"Total assignments: "<<tassignments<<endl;
    int q[rows];
    int a[rows];
 
    // getting initial inputs 
    for(int i = 0 ; i<tquizzes;i++){
        myfile>>q[i];   
    }
    for(int i = 0 ; i<tassignments;i++){
        myfile>>a[i];
    }
    // sets them into static variables
    Evaluationreport :: totalstudents = tstudents;
    Evaluationreport :: totalquizzes = tquizzes;
    Evaluationreport :: totalassignments = tassignments;
    Evaluationreport:: setassignments(a);
    Evaluationreport :: setquiz(q);
  
    
    cout<<endl<<endl;
    Evaluationreport *Evalreport ;
    int numstudents = 42;
    cout<<"\t\t\t\t LIST OF STUDENTS\t\t\n\n";
    Evalreport = Readdatafromfile(myfile,Evalreport);
    cout << "Name\t\tRollnumber\tQ1\tQ2\tQ3\tQ4\tA1\tA2\tA3\tA4\tTotal" << endl;
    for(int i = 0 ; i < numstudents ; i++){
        cout<<Evalreport[i]<<" "<<endl;
    }
    cout<<endl<<endl<<endl;
    cout<<"\t   Statistics \t\t\n";
    updatestatistics(Evalreport,numstudents);
    cout<<endl<<endl;
    string keyword;
    cout<<"enter keyword\t";
    getline(cin,keyword);
    searchstudentsbykeyword(keyword, Evalreport,numstudents);
    cout<<endl<<endl;
    cout<<"\t\t \t\tSORTEd LIST \t\n\n";
    sortlistbytotal(Evalreport,numstudents);
    cout<<endl<<endl<<endl<<endl;
    string rollnumber = "23L-0666";
    printdetail(rollnumber, Evalreport,numstudents);
    cout<<endl<<endl<<endl;
    string rollnumber2 = "23L-0646";
    printdetail(rollnumber2, Evalreport,numstudents);

    myfile.close();
    delete[] Evalreport;

}