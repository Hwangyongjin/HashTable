#include <cstdlib>
#include <cstdio>
#include <cstring>
#define MAX_STD 20
typedef struct Student { //학생    정보
    int no; //학번
    char name[50];  //이름
    char tel[50];   //전화번호

}Std_Info;
//해시 함수
int Hash_Function(int key, int Hash_Size)
{
    char c[50];
    itoa(key, c, 10);
    int len = strlen(c);
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += c[i];
    }
    int hash_addr = sum % Hash_Size;
    return hash_addr;
}
//해시 테이블 구성
void SInfo_Create(Std_Info* students, const char* file_name, int Hash_Size)
{
    FILE* file;
    fopen_s(&file, file_name, "r");
    if (file == NULL) {
        printf("파일이 없습니다. 프로그램을 종료합니다.");
        return;
    }
    while (!feof(file))
    {
        int no;
        char name[50], tel[50];
        int result = fscanf_s(file, "%d %s %s", &no, name, sizeof(name), tel, sizeof(tel));
        if (result == EOF) break;
        int hash_addr = Hash_Function(no, Hash_Size);
        int index = hash_addr;
        while (students[index].no != -1)
        {
            if (students[index].no == no)
            {
                printf("error: duplicated key\n");
                return;
            }
            index = (index + 1) % Hash_Size;
            if (index == hash_addr)
            {
                printf("error: hash full\n");
                return;
            }
        }
        students[index].no = no;
        strcpy_s(students[index].name, name);
        strcpy_s(students[index].tel, tel);
    }
}
//해시 탐색
int Hash_Search(Std_Info* students, int key, int Hash_Size)
{
    int hash_addr = Hash_Function(key, Hash_Size);
    int index = hash_addr;
    while (1)
    {
        if (students[index].no == key)
            return index;
        if (students[index].no == 0)
            break;
        index = (index + 1) % Hash_Size;
        if (index == hash_addr)
            break;
    }
    return -1;
}
int main() {
    Std_Info students[MAX_STD];
    const char* fName = "students_info.txt";
    for (int i = 0; i < MAX_STD; i++) {  //students 해시    테이블    초기화
        students[i].no = -1;
        memset(students[i].name, 0, sizeof(students[i].name));
        memset(students[i].tel, 0, sizeof(students[i].tel));
    }
    SInfo_Create(students, fName, MAX_STD);
    printf(" % d 위치는 해시 테이블 % d에 존재합니다.\n\n", 218, Hash_Search(students, 218, MAX_STD));
    printf("##해시    테이블##\n");
    for (int i = 0; i < MAX_STD; i++)  //students 해시    테이블    출력
        printf("[% 2d]: % d % s % s\n", i, students[i].no, students[i].name, students[i].tel);
    return 0;
}