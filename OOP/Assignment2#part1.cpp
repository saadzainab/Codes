#include<iostream>
#include<fstream>
using namespace std;
int** InputMatrix( ifstream& fin, int& rows, int& cols){
fin>>rows>>cols;
int**matrix = new int*[rows];
for(int i = 0 ; i < rows ; i ++){
    matrix[i] = new int[cols];
}
for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < cols ; j++){
        //fin>> matrix[i][j];
        fin >> *(*(matrix+i)+j);
    }
}
return matrix;

}
void Outputmatrix(int **matrix , int&rows , int&cols){
for(int i = 0; i < rows ; i++){
    for(int j = 0 ; j < cols;j++){
        cout<<*(*(matrix+i)+j) << "  ";;
    }
    cout<<endl;
}
}
int** Addmatrix(int** matrixA , int** matrixB , int&rows,int&cols){

int**addmatrix = new int*[rows];
for(int i = 0 ; i < rows ; i ++){
    addmatrix[i] = new int[cols];
}
for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < cols ;j++){
        //addmatrix[i][j] = matrixA[i][j] + matrixB[i][j];
        *(*(addmatrix+i)+j) =*(*(matrixA+i)+j)+ *(*(matrixB+i)+j);
    }
}
return addmatrix;
}
int** TransposeMatrix(int** matrix, const int& ROWS, const int& COLS){
int**transposematrix = new int*[COLS];
for(int i = 0 ; i < COLS ; i ++){
    transposematrix[i] = new int[ROWS];
}
for(int i = 0 ; i < ROWS;i++){
    for(int j = 0 ; j < COLS ;j++){
        *(*(transposematrix+j)+i)=*(*(matrix+i)+j);
    }
}
for(int i = 0 ; i < COLS;i++){
    for(int j = 0 ; j < ROWS ;j++){
        cout<<*(*(transposematrix+i)+j)<<" ";
    }
    cout<<endl;
}
return transposematrix;
}

bool IsSymmetric(int** matrix, const int& ROWS, const int& COLS){
    
    int count = 0;
    cout<<"Matrix being checked: \n";
    int **transpose = TransposeMatrix(matrix,ROWS,COLS);
    if(ROWS!=COLS){
        return false;
    }
    else{
    for(int i = 0 ; i < ROWS ; i++){
        for(int j = 0 ; j <COLS ; j++){
            if(*(*(transpose+i)+j) == *(*(matrix+i)+j)){
                count++;
            } 
            
        }
    }
    }
  if (count == (ROWS * COLS)){
    return true;
  }
  else{
    return false;
  }
}
void interchangeRows( int*& row1, int*& row2 ){
    
    int *temp = row1;
    row1 = row2;
    row2 = temp;

}
void InterchangeRows(int** matrix, const int& ROWS, const int& COLS ){
int row = 0;
int row2 = 2;
cout<<"ROW 1 : 1"<<endl;
cout<<"ROW 2 : 3"<<endl;
interchangeRows(*(matrix + row), *(matrix + row2));
cout<<"After interchanging rows matrix A \n";
for(int i = 0; i < ROWS ; i++){
    for(int j = 0 ; j < COLS;j++){
        cout<<*(*(matrix+i)+j) << "  ";;
    }
    cout<<endl;
}

}


int main(){
ifstream fin ("inputfile.txt");
if(!fin.is_open()){
    cout<<"Error!";
}
int rows1 = 0, cols1 = 0;
int** matrixA = InputMatrix(fin,rows1,cols1);
//cout<<rows1<<" "<<cols1<<endl;
cout<<"MATRIX A"<<endl;
Outputmatrix(matrixA,rows1,cols1);
int rows2 = 0, cols2 = 0;



cout<<"MATRIX B"<<endl;
int** matrixB = InputMatrix(fin,rows2,cols2);
//cout<<rows2<<" "<<cols2<<endl;
Outputmatrix(matrixB,rows2,cols2);
int rows3 = 0 , cols3 = 0;


cout<<"MATRIX C "<<endl;
int** matrixC = InputMatrix(fin,rows3,cols3);
//cout<<rows3<<" "<<cols3<<endl;
Outputmatrix(matrixC,rows3,cols3);


cout<<endl<<endl;
cout<<"A + B \n";
if(rows1== cols1 && rows1==rows2 && rows1 == cols2){
    int**addmatrix = Addmatrix(matrixA,matrixB,rows1,cols1);
    Outputmatrix(addmatrix,rows1,rows2);
}
cout<<endl<<endl;




if(rows1== cols1 && rows1==rows3 && rows1 == cols3){
    int**addmatrix = Addmatrix(matrixA,matrixB,rows1,cols1);
    Outputmatrix(addmatrix,rows1,rows2);
    for (int i = 0; addmatrix[i] != '\0'; i++){
    delete[] addmatrix[i];
    }
delete[]addmatrix;

}
else{
    cout<<"A + C = \nAddition not possible!\n";
}
cout<<endl<<endl;


cout<<"Tranpose matrix A\n";
int**transposematrix = TransposeMatrix(matrixA,rows1,cols1);

cout<<"Tranpose matrix C\n";
int**transpose = TransposeMatrix(matrixC,rows3,cols2);
cout<<endl<<endl;

cout<<endl<<endl;
bool issymmetric = false;
issymmetric=IsSymmetric(matrixA,rows1,cols1);

if(issymmetric == true){
    cout<< "MATRIX A is symmeteric\n\n";
}
else{
    cout<<"Matrix A is NOT symmetric\n";

}
cout<<endl<<endl;
issymmetric = IsSymmetric(matrixB,rows2,cols2);
if(issymmetric == true){
    cout<< "MATRIX B is symmeteric\n\n";
}
else{
    cout<<"Matrix B is not symmetric\n\n";

}

InterchangeRows(matrixA,rows1,cols2);

for (int i = 0; matrixA[i] != '\0'; i++){
  delete[] matrixA[i];
}
delete[]matrixA;

for (int i = 0; matrixB[i] != '\0'; i++){
  delete[] matrixB[i];
}
delete[]matrixB;

for (int i = 0; matrixC[i] != '\0'; i++){
  delete[] matrixC[i];
}
delete[]matrixC;
for (int i = 0; transposematrix[i] != '\0'; i++){
  delete[] transposematrix[i];
}
delete[]transposematrix;

for (int i = 0; transpose[i] != '\0'; i++){
  delete[] transpose[i];
}
delete[]transpose;


}


