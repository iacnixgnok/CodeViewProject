#include<bits/stdc++.h>
using namespace std;
#define _KEY_WORD_END "waiting fou your expanding"/*定义关键字的结束标志*/
typedef struct
{
    int typenum;            /*种别码*/
    char *word;
} WORD;
char input[255];           /*源程序缓字符冲区*/
char token[255]="";              /*单词缓冲区*/
int p_input;              /*源程序字符指针*/
int p_token;              /*单词缓冲区指针*/
char ch;
set<int>xception;
char *rwtab[]= {"void","int","float","char","if","else","while","do","return","main",_KEY_WORD_END};
WORD *scaner(); /*词法扫描函数，获得一个单词*/
int LineNum=1;//行号
int main()
{
    WORD *oneword = new WORD;
    scanf("%[^#]s",input); /*使用正则表达式，输入源程序字符串到缓冲区，以#结束*/
    p_input=0;
    while (input[p_input]!='#')
    {
        oneword=scaner();
        if(oneword->word=="OVER")
            break;
        else if(oneword->typenum <1000)
            printf("<%d,%s>, ",oneword->typenum,oneword->word );
        else printf("LexicalError,");
    }
    if(!xception.empty())
    {
        printf("LexicalError(s) on line(s) ");
        for(set<int>::iterator it=xception.begin(); it!=xception.end(); ++it)
        {
            cout<<*it<<",";
        }
    }
    return 0;
}

char m_getch()  /*从输入源读一个字符到CH中*/
{
    ch=input[p_input];
    p_input=p_input+1;
    return ch;
}

void getbc()   /*去掉空白字符*/
{
    bool is=true;
    while (ch ==' '|| ch== 10)
    {
        if(ch=='\n'&&is)
        {
            printf("\n");
            is=false;
            LineNum++;
        }
        ch = input[p_input];
        p_input=p_input+1;
    }
}

void concat()  /*拼接单词*/
{
    token[p_token]=ch;
    p_token=p_token+1;
    token[p_token]='\0';
}

int letter()/*判断是否是字母*/
{
    if(ch>='a' && ch<='z'|| ch >='A'&& ch <='Z')
        return 1;
    else return 0;
}

int digit()/*判断是否是数字*/
{
    if(ch>='0'&& ch<='9')
        return 1;
    else return 0;
}

int reserve()/*检索关键字表格*/
{
    int i=0;
    while(strcmp(rwtab[i],_KEY_WORD_END))
    {
        if(!strcmp(rwtab[i],token))
        {
            token[0]='-';
            token[1]='\0';
            return i+25;
        }
        i=i+1;
    }
    return 1;
}
void retract()/*回退一个字符*/
{
    p_input=p_input-1;
}
WORD *scaner()/*词法扫描程序*/
{
    int i=0;
    WORD *myword =new WORD;
    myword->typenum=0;
    myword->word=" ";
    p_token=0;
    m_getch();
    getbc();
    if(letter())
    {
        while(letter()||digit())
        {
            concat();
            m_getch();
        }
        retract();
        myword->typenum=reserve();
        myword->word=token;
        return myword;
    }
    else if(digit())
    {
        while(digit())
        {
            concat();
            m_getch();
        }
        retract();
        if(letter())
        {
            while(letter())
                m_getch();
            retract();
            myword->typenum =1000;
            myword->word =token;
            xception.insert(LineNum);
            return myword;
        }
        else
        {
            myword->typenum =2;
            myword->word =token;
            return myword;
        }
    }
    else switch(ch)
        {
        case'=' :
            m_getch();
            if(ch=='=')
            {
                myword->typenum =12;
                myword->word ="-";
                return myword;
            }
            retract();
            myword->typenum =16;
            myword->word ="-";
            return myword;
            break;
        case'+':
            myword->typenum =1;
            myword->word ="-";
            return myword;
            break;
        case'-':
            myword->typenum =1;
            myword->word ="-";
            return myword;
            break;
        case'*':
            myword->typenum =1;
            myword->word ="-";
            return myword;
            break;
        case'/':
            m_getch();
            if(ch=='/')
            {
                while(ch!='\n')
                    m_getch();
                return scaner();
            }
            else if(ch=='*')
            {
                p_input=strchr(input+p_input,'/')-input+1;
                return scaner();
            }
            else
            {
                retract();
                myword->typenum =6;
                myword->word ="-";
                return myword;
            }
            break;
        case'(':
            myword->typenum =17;
            myword->word ="-";
            return myword;
            break;
        case')':
            myword->typenum =18;
            myword->word ="-";
            return myword;
            break;
        case'[':
            myword->typenum =19;
            myword->word ="-";
            return myword;
            break;
        case']':
            myword->typenum =20;
            myword->word ="-";
            return myword;
            break;
        case'{':
            myword->typenum =21;
            myword->word ="-";
            return myword;
            break;

        case'}':
            myword->typenum =22;
            myword->word ="-";
            return myword;
            break;
        case',':
            myword->typenum =24;
            myword->word ="-";
            return myword;
            break;
        case';':
            myword->typenum =23;
            myword->word ="-";
            return myword;
            break;
        case'>':
            m_getch();
            if(ch=='=')
            {
                myword->typenum =11;
                myword->word ="-";
                return myword;
            }
            retract();
            myword->typenum =10;
            myword->word ="-";
            return myword;
            break;
        case'<':
            m_getch();
            if(ch=='=')
            {
                myword->typenum =9;
                myword->word ="-";
                return myword;
            }
            retract();
            myword->typenum =8;
            myword->word ="-";
            return myword;
            break;
        case'!':
            m_getch();
            if(ch=='=')
            {
                myword->typenum =13;
                myword->word ="-";
                return myword;
            }
            retract();
            myword->typenum =-1;
            myword->word ="ERROR";
            return myword;
            break;
        case'&':
            m_getch();
            if(ch=='&')
            {
                myword->typenum =14;
                myword->word ="-";
                return myword;
            }
            retract();
            myword->typenum =-1;
            myword->word ="ERROR";
            return myword;
            break;
        case'|':
            m_getch();
            if(ch=='|')
            {
                myword->typenum =15;
                myword->word ="-";
                return myword;
            }
            retract();
            myword->typenum =-1;
            myword->word ="ERROR";
            return myword;
            break;
        case'\0':
            myword->typenum=100;
            myword->word="OVER";
            return myword;
            break;
        default:
            myword->typenum=0;
            myword->word="无定义";
            return myword;
        }
}
