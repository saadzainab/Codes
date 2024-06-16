#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;
const int size = 100;
int length(char paragraph[]){       // to calculate length
    int i = 0 ;
    while(paragraph[i] != '\0'){
    
      i++;
    } 
    return i;
}   
void stringconcatenate(char* &array1, char*& array2){
    int length1 = length(array1);
    int length2 = length(array2);
    
    cout<<"length of first string "<< length1<<endl;
    cout<<"length of second string "<< length2<<endl<<endl;
    
    int length3 = length1 + length2;   // adds length of both
    //array1 = new char[length3];
    
    int j = 0; 
    for(int i = length1 ; i < length3;i++){
        array1[i] = array2[j];
        j++;
    }
    cout<<"After string concatenate: "<<endl;
    for(int i = 0 ; i < length3 ; i++){
        cout<<array1[i];
    }
    cout<<endl<<"String 2 "<<endl;
    for(int i = 0 ; i < length2 ;i++){
        cout<<array2[i];
    }
}

int calculatingrows(char*arr , int&a){    
int x =0 ;
while(arr[x] != '\0'){
if(arr[x] == ' ' ){  // rows for a 2D array  being used in tokenization
a++;
}
x++;
}
return a;
}
void outputarray(char** array,int& rows , int& cols){

for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j< cols ; j++){
        cout<<array[i][j];
    }
	cout<<endl;
}

}
char** StringTokens(char*str){
    int rows = 1;
	rows = calculatingrows(str, rows);
	cout << "number of rows :" << rows << endl;
	char** token = new char* [rows];   // new 2d array to store words
	int cols = 0; int maxcols = 0;
	for(int i = 0; i < length(str) ; i++){   // calculates word length
    if(str[i] == ' '|| str[i] =='\0'){
  
      if (cols > maxcols){
        maxcols = cols;
    }
    cols = 0;
    }
    else {
    cols++;
    }
	}
	//cout<<"COLS"<<maxcols;
	for (int i = 0; i < rows; i++) { //initialization
		token[i] = new char[maxcols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < maxcols; j++) {
			token[i][j] = ' ';
		}
	}
	int start = 0, index = 0;                  // stores each word : tokenization
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == ' ' || str[i] == '\0' ) {
			int length = i - start;
			for (int j = 0; j < length; j++) {
				token[index][j] = str[start + j];
			}

			token[index][length] =	'\0';
			index++;
			start = i + 1;

		}
		
	}
cout<<"TOKENIZED ARRAY \n\n";

outputarray(token,rows,maxcols);
return token; 
}
char** InverseStringTokens(char*str){
	char**token = StringTokens(str);
	
	int row = 1;
	row = calculatingrows(str,row);
	int cols = 0; int maxcols = 0;
	for(int i = 0; i < strlen(str) ; i++){       // calculates the word lengths
    if(str[i] == ' '|| str[i] =='\0'){
  
      if (cols > maxcols){
        maxcols = cols;
    }
    cols = 0;
    }
    else {
    cols++;
    }
	}

	char**reverse = new char*[row];
	for(int i = 0 ; i < row ; i++){
		reverse[i] = new char[maxcols];
	}
    int k = row - 1;
	for(int i = 0; i < row ; i++){    // stores in reverse order
		reverse[i] = token[k];
		k--;
	}
cout<<"INVERSE TOKENIZED STRING \n";
outputarray(reverse,row,maxcols);
return reverse;
}
char* reversesentence(char*str){
    //char**token = StringTokens(str);
    char** reverse2D = InverseStringTokens(str);
    int row = 1;
	row = calculatingrows(str,row);
    int l = length(str);
	

    char*temp = new char[l];
    
    int x = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; reverse2D[i][j] != '\0'; j++)
        {
            temp[x] = reverse2D[i][j];
            x++;
        }
        temp[x] = ' ';
        x++;
    }
    temp[x- 1] = '\0';
    return temp;
}
char* sort(char*array){
    int length = strlen(array);
    for(int i = 0 ; i < length - 1; i++){
        for(int j = 0 ; j < length - i - 1 ; j++){
            if(array[j] > array[j+1]){
                char temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    return array;
}
int CompareString(char* cstring1, char* cstring2 ){
    int i= 0;
    while (1){
        char ch1 = tolower(cstring1[i]);
        char ch2 = tolower(cstring2[i]);
        if (ch1 == '\0' && ch2 == '\0'){       // checks each character
            return 0;
        }
        if (ch1 < ch2){
            return -1;
        }
        else
        {
            return 1;
        }
        i++;
    }
}
void BubbleSort(char **array, int count)      // sorts the array using compare string
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (CompareString(array[j], array[j + 1]) > 0)
            {
                char *temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
void Display(char**array,int rows){
    //int rows = sizeof(array) / sizeof(array[0]);
    for (int i = 0; i < rows; i++)
    {
        cout << array[i] << endl;
    }
}
void InputMatrix(ifstream &myfile)          // taking the list of names from file
{
    if (!myfile){
        cout << "Error\t" << "File not found\n";
    }
    else{
        int rows = 0;
        char sentence [80];
        while (myfile.getline(sentence, 80)){      // getting number of rows
            rows++;
        }
        myfile.close();
        myfile.open("studentslist.txt");
        char **students = new char *[rows];     // array for those number of rows
        for (int i = 0; i < rows; i++){
            students[i] = new char[80];
            myfile.getline(students[i], 80);    // gets each student and stores in array
        }
        myfile.close();
        cout << "Displaying list before sorting: \n\n" ;
        Display(students,rows);
        cout << endl << endl;
        BubbleSort(students, rows);
        cout << "Displaying sorted list: \n\n" ;
        Display(students,rows);
         for(int i = 0 ; i < rows ; i++){
            delete[] students[i];
        }
        delete[]students; 
        
    }
    
}




int main(){
int qnum = 0;
cout<<"which question ? 1 for first 2 for second ";
cin>>qnum;
if(qnum == 1){
 cout<<"\t TASK 1 \t\n";
 
 char* array1 = new char[100];
 cout<<" enter first string : \n";
 cin.ignore();
 cin.getline(array1,100);


 
 char* array2= new char[100];
 cout<<"Enter second string : \n";
 cin.getline(array2,100);

 
 stringconcatenate(array1,array2);

 delete[] array1;
 delete[] array2;
 
 cout<<"\n\n\t TASK 2 \t\n";
 char* str = new char[100];

 cout<<"Enter the string : \n";
 cin.getline(str,100);
 // StringTokens(str);
 //InverseStringTokens(str); 
 char* temp = reversesentence(str);
 cout<<"\nReverse Sentence : "<<temp<<endl;
delete[] temp; 
 delete[] str;


}
else if(qnum == 2){
 cout<<"\n\n\tTASK3 \t\n\n";
 ifstream myreadfile;
 myreadfile.open("studentslist.txt");
 InputMatrix(myreadfile);
 myreadfile.close();

}

 
 
 

 


}