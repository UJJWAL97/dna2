#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
#define gap_penalty  30

void printer(int m,int n,int** arr){
int i,j;
    for(i=0;i<m;i++){

        for(j=0;j<n;j++){
            cout<< arr[i][j]<<" ";        }
        cout<<"\n";
    }
}

int** init_matrix(int m,int n){
    int **arr=0;
    arr = new int*[m];
    int i,j;
    for(i=0;i<m;i++){
        arr[i]=new int[n];
        for(j=0;j<n;j++){
            arr[i][j]=0;        }
    }
return arr;
}

int score_calculator(char a,char b){
    if(a==b){
        if(a=='A' and b=='A')
            return -91;
        else if(a=='C' and b=='C')
            return -100;

        else if(a=='G' and b=='G')
            return  -100;

        else if(a=='T' and b=='T')
            return -91;






    }
    else if(a=='_'|| b=='_' )
        return gap_penalty;
    else
    {
         if(a=='A' and b=='C')
            return 114;
        else if(a=='A' and b=='G')
            return 31;
        else if(a=='A' and b=='T')
            return 123;
        else if(a=='C'  and b=='A')
            return 114;

        else if(a=='C' and b=='G')
            return 125;

        else if(a=='C' and b=='T')
            return 31;

        else if(a=='G' and b=='A')
            return 31;

        else if(a=='G' and b=='C')
            return 125;

        else if(a=='G' and b=='T')
            return 114;

        else if(a=='T' and b=='A')
            return 123;

        else if(a=='T' and b=='C')
            return 31;

        else if(a=='T' and b=='G')
            return 114;

    }
}
char trackback(int** arr,int i,int j,string& str1,string& str2) {
    int current = arr[i][j];
    int diagonal = arr[i - 1][j - 1];
    int up = arr[i][j - 1];
    int left = arr[i - 1][j];
    if(current==up+gap_penalty ){
        if(current==diagonal+score_calculator(str1[j-1],str2[i-1])) {
            return '_';
        }
        else if(current==left+gap_penalty){
            char res_left= trackback(arr,i-1,j,str1,str2);
            char res_up=trackback(arr,i,j-1,str1,str2);
            if(res_left=='_' or res_up=='_')
                return '_';
            else if(res_left=='A' or res_up=='A')
                return 'A';
            else if(res_left=='C' or res_up=='C')
                return 'C';
            else if(res_left=='G' or res_up=='G')
                return 'G';
            else if(res_left=='T' or res_up=='T')
                return 'T';
        }
        else{
            return '_';

        }
    }
    else if(current==left+gap_penalty){

        if(current==diagonal+score_calculator(str1[j-1],str2[i-1])) {
            return '_';

        }
        else if(current==up+gap_penalty){
            char res_left= trackback(arr,i-1,j,str1,str2);
            char res_up=trackback(arr,i,j-1,str1,str2);
            if(res_left=='_' or res_up=='_')
                return '_';
            else if(res_left=='A' or res_up=='A')
                return 'A';
            else if(res_left=='C' or res_up=='C')
                return 'C';
            else if(res_left=='G' or res_up=='G')
                return 'G';
            else if(res_left=='T' or res_up=='T')
                return 'T';

        }
        else{
            return '_';

        }


    }
    else if(current==diagonal+score_calculator(str1[j-1],str2[i-1])){
        return str2[i-1];
    }




}

int scorer(string& str1,string& str2){
    int n=str1.length();
    int m=str2.length();
    int i,j;
    int match,up,side;
    int** arr=init_matrix(m+1,n+1);
    for(i=0;i<m+1;i++)
        arr[i][0]=gap_penalty*i;
    for(i=0;i<n+1;i++)
        arr[0][i]=gap_penalty*i;
    for(i=1;i<m+1;i++)
        for(j=1;j<n+1;j++)
        {
            match=arr[i-1][j-1]+score_calculator(str1[j-1],str2[i-1]);
            up=arr[i-1][j]+gap_penalty;
            side=arr[i][j-1]+gap_penalty;

            arr[i][j]=min(min(match,up),side);


        }


    string x="";
    string y="";
    i=m;
    j=n;
    int score=0;
    while (i>0 and j>0){
        int current = arr[i][j];
        int diagonal = arr[i-1][j-1];
        int up = arr[i][j-1];
        int left = arr[i-1][j];

        if(current==up+gap_penalty ){
            if(current==diagonal+score_calculator(str1[j-1],str2[i-1])) {
                x=x+str1[j - 1];
                y=y+"_";
                j--;
                score+=gap_penalty;
            }
            else if(current==left+gap_penalty){
                char res_up=trackback(arr,i,j-1,str1,str2);
                char res_left=trackback(arr,i-1,j,str1,str2);
                if(res_up=='_'){
                    x=x+str1[j - 1];
                    y=y+"_";
                    j--;
                    score+=gap_penalty;

                }
                else if(res_left=='_'){
                    y=y+str2[i-1];
                    x=x+"_";
                    i--;
                    score+=gap_penalty;

                }

                else if(res_up=='A'){
                    x=x+str1[j - 1];
                    y=y+"_";
                    j--;
                    score+=gap_penalty;

                }
                else if(res_left=='A'){
                    y=y+str2[i-1];
                    x=x+"_";
                    i--;
                    score+=gap_penalty;

                }

                else if(res_up=='C'){
                    x=x+str1[j - 1];
                    y=y+"_";
                    j--;
                    score+=gap_penalty;

                }
                else if(res_left=='C'){
                    y=y+str2[i-1];
                    x=x+"_";
                    i--;
                    score+=gap_penalty;

                }

                else if(res_up=='G'){
                    x=x+str1[j - 1];
                    y=y+"_";
                    j--;
                    score+=gap_penalty;

                }
                else if(res_left=='G'){
                    y=y+str2[i-1];
                    x=x+"_";
                    i--;
                    score+=gap_penalty;

                }

                else if(res_up=='T'){
                    x=x+str1[j - 1];
                    y=y+"_";
                    j--;
                    score+=gap_penalty;

                }
                else if(res_left=='T'){
                    y=y+str2[i-1];
                    x=x+"_";
                    i--;
                    score+=gap_penalty;

                }


            }
            else{
                x=x+str1[j - 1];
                y=y+"_";
                j--;
                score+=gap_penalty;

            }
        }
        else if(current==left+gap_penalty){

            if(current==diagonal+score_calculator(str1[j-1],str2[i-1])) {
                y=y+str2[i-1];
                x=x+"_";
                i--;
                score+=gap_penalty;

            }

            else{
                y=y+str2[i-1];
                x=x+"_";
                i--;
                score+=gap_penalty;

            }

        }
        else if(current==diagonal+score_calculator(str1[j-1],str2[i-1])){
            x=x+str1[j-1];
            y=y+str2[i-1];
            score+=score_calculator(str1[j-1],str2[i-1]);
            i--;
            j--;




        }

    }
    while (j>0){
        x=x+str1[j-1];
        y=y+"_";
        j--;

    }
    while (i>0){
        y=y+(str2[i-1]);
        x=x+"_";
        i--;

    }



    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    cout<<score<<endl;
    cout<<x<<endl;
    cout<<y<<endl;


}


int main() {
    string seq1;
    string seq2;
    getline(cin, seq1);
    getline(cin, seq2);
    scorer(seq1,seq2);
    return 0;
}
