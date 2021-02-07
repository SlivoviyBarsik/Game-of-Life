#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
using namespace std;

int n, a[100][100], cells=0, gen=0;
const int col=80;
const int row=30;
HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE eHnd = GetStdHandle(STD_INPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

void screen_Gen(){
    for(int i=0;i<3;++i){
        COORD cP={(col-18)/2-1, (row-1)/2-1};
        SetConsoleCursorPosition(wHnd, cP);
        cout<<"Generating life.";
        Sleep(100);
        system("CLS");
        SetConsoleCursorPosition(wHnd, cP);
        cout<<"Generating life..";
        Sleep(100);
        system("CLS");
        SetConsoleCursorPosition(wHnd, cP);
        cout<<"Generating life...";
        Sleep(100);
        system("CLS");
        SetConsoleCursorPosition(wHnd, cP);
        cout<<"Generating life";
        Sleep(100);
        system("CLS");
    }
}

void screen_Ent(){
    system("CLS");
    COORD cursorPos={((col-28)/2)-1,(row-2)/2-1};
    SetConsoleCursorPosition(wHnd, cursorPos);
    cout<<"Enter the size of the field:"<<endl;
    cursorPos={(col-1)/2-1,(row-2)/2};
    SetConsoleCursorPosition(wHnd, cursorPos);
    cin>>n;
    system("CLS");
    int k;
    cursorPos={(col-24)/2-1,(row-2)/2-1};
    SetConsoleCursorPosition(wHnd, cursorPos);
    cout<<"Initial number of cells:"<<endl;
    cursorPos={(col-1)/2-1,(row-2)/2};
    SetConsoleCursorPosition(wHnd, cursorPos);
    cin>>cells;
}

void gen_ar_life(){
    srand(time(NULL));
    int x, y;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            a[i][j]=0;
        }
    }
    for(int i=0;i<cells;++i){
        x=rand()%n;
        y=rand()%n;
        if(a[y][x]==1){
            i--;
            continue;
        }
        a[y][x]=1;
    }

}

void new_gen(){
    int neighb;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            neighb=0;
            for(int i0=i-1;i0<=i+1;++i0){
                if(i0<0) continue;
                if(i0==n) break;
                for(int j0=j-1;j0<=j+1;++j0){
                    if(j0<0) continue;
                    if(j0==n) break;
                    if((a[i0][j0]==1)||(a[i0][j0]==3)) neighb++;
                }
            }
            if(((neighb<3)||(neighb>4))&&(a[i][j])==1){
                a[i][j]=3;
            }
            if((neighb==3)&&(a[i][j]==0)){
                a[i][j]=2;
            }
        }
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(a[i][j]==2){
                a[i][j]=1;
                cells++;
            }
            if(a[i][j]==3){
                a[i][j]=0;
                cells--;
            }
        }
    }
    gen++;
}

int draw_life(){

    int k=2;
    COORD cursorPos;
    SMALL_RECT windowSize={0,0,col-1,n+6};
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
    GetConsoleScreenBufferInfo(wHnd, &csbiInfo);
    WORD oldattr=csbiInfo.wAttributes;
    WORD attr0= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE ;
    WORD attr1= BACKGROUND_GREEN ;
    for(int i=0;i<n;++i){
        cursorPos={2,k};
        SetConsoleCursorPosition(wHnd, cursorPos);
        for(int j=0;j<n;++j){

            if(a[i][j]==0){
                SetConsoleTextAttribute(wHnd, attr0);
                cout<<' ';
            }
            else{
                SetConsoleTextAttribute(wHnd, attr1);
                cout<<' ';
            }
        }
        SetConsoleTextAttribute(wHnd, oldattr);
        if(i==0) cout<<"  Cells: "<<cells;
        if(i==2) cout<<"  Generation: "<<gen;
        k++;
    }
    cursorPos={2,k+1};
    SetConsoleCursorPosition(wHnd, cursorPos);
    cout<<"Press Space to pause, press ESC to stop...";
    if((kbhit())&&(getch()==32)){
        return 1;
    }
    if((kbhit())&&(getch()==27)){
        return 2;
    }
    return 0;

}

int game_over(){
    char ans;
    SMALL_RECT windowSize={0,0,col-1,row-1};
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
    COORD cursorPos={((col-15)/2)-1,(row-2)/2-1};
    SetConsoleCursorPosition(wHnd, cursorPos);
    cout<<"Life is over...";
    cursorPos={1,row-1};
    SetConsoleCursorPosition(wHnd, cursorPos);
    system("pause");
    system("CLS");

    cursorPos={(col-17)/2-1,(row-2)/2-1};
    SetConsoleCursorPosition(wHnd, cursorPos);
    cout<<"Start over? (Y/N)";
    cursorPos={(col-1)/2-1,(row-2)/2};
    SetConsoleCursorPosition(wHnd, cursorPos);
    cin>>ans;
    if(toupper(ans)=='Y') return 1;
    else return 0;
}

int main()
{
    int g=3, c;
    SetConsoleTitle("Game of Life");
    for(;;){
        SMALL_RECT windowSize={0,0,col-1,row-1};
        SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

        screen_Ent();
        gen_ar_life();
        screen_Gen();
        for(;;){
            c=draw_life();
            switch(c){
            case 1:
                while(!kbhit()){
                    Sleep(100);
                }
                getch();
                break;
            case 2:
                system("CLS");
                g=game_over();
                break;
            default:
                break;
            }
            if(g!=3) break;
            Sleep(300);
            system("CLS");
            new_gen();
            if(cells==0){
                g=game_over();
                break;
            }
        }
        if(g==0) return 0;
    }

    return 0;
}
