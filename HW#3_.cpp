/***************************************************************/
/*             HW#3 : 구조체,레퍼런스,함수인자전달                                    */
/*  작성자 : 2018038025 정하용                    날짜 : 2022년 3월 11일  */
/*                                                                                     */
/* 문제 정의 :  두명의 학생의 정보(이름, 학번)를 입력받고
			그 학생이 수강한 세가지의 과목의 정보(과목명, 과목학점, 등급)를
			입력 받아 학생의 과목 평점 및 세 과목의 평균 평점을 계산해 출력하는 성적 처리 프로그램
			기존 프로그램을 함수화 하고 추가로 학생의 이름을 검색해 학생의 성적 정보를 출력하는 기능을 추가했다.
			*/

			/***************************************************************/
#include <iostream>//C++에서 사용할 기본 입출력 함수가 정의된 헤더파일 선언
#include <cstring>//문자열을 서로 비교하는 함수인 strcmp()함수가 정의된 헤더파일 선언
using namespace std;// namespase에 있는 std 클래스에 정의되어있는 함수들을 사용하겠다 선언

typedef struct //교과목의 정보를 받는 구조체 선언
{
	char SubName[30];//교과목 이름을 담을 문자열
	int Hakjum;//과목 학점
	char Grade[10];//등급을 담을 문자열
	float GPA;//과목 평점을 담을 변수로 과목학점에 등급별 점수를 곱한 값이다
}Subject;

typedef struct //학생의 정보를 받는 구조체 선언
{
	char StdName[30];//학생의 이름을 담을 문자열
	int Hakbun;//학번
	Subject Sub[3];//한 학생당 세과목을 받기로 했으므로 학생 구조체 안에 크기가 3인 성적 구조체 배열을 선언
	float AveGPA;//학생 평균 평점으로 각 과목 평점들의 합을 과목 학점들의 합으로 나눈 값이다
}Student;

// 함수의 프로토타입 선언
void PrintMenu();
void Std_scan(Student *name);
void Sub_scan(Subject *info);
void CalcGPA(Subject& Sub);
float CalcAveGPA(Subject* Sub);
void PrintAllData(const Student* pSt, int StudentNum);
void PrintOneData(const Student& rst);
Student* StdSearch(Student* pSt, int StudentNum);

int menutoken = 0;//메뉴를 선택할 변수로, switch - case 문에서 활용할 전역변수 선언

//메인함수 시작
int main()
{
	Student std[2] = {};//학생 두명의 정보를 받기 위해 크기가 2인 학생 구조체배열을 선언
	Student* SearchStd;


	for (; ;)// 메뉴 출력 루프 시작
	{

		PrintMenu(); 


		switch (menutoken)
		{
		case 1:

			for (int i = 0; i < 2; i++)//두명의 학생의 정보를 받기 위한 첫 번째 루프 시작
			{
				cout << "\n\n\n" << i + 1 << "번째 학생의 정보를 입력하세요.\n";

				Std_scan(&std[i]);//학생 정보 입력받는 함수 실행
				//초기에 선언한 학생구조체 배열의 주소를 넘겨줌

				cout << "\n\n\n수강한 과목 세개와 각 교과목명, 학점, 등급을 입력하세요.\n";

				for (int j = 0; j < 3; j++)//학생 한명당 세가지의 과목을 입력 받기 위해 두 번째 루프 시작
					Sub_scan(&std[i].Sub[j]);//수강한 과목을 입력받는 함수 실행
					//학생 구조체 안에 과목 구조체배열이 선언되어 있어서 학생 구조체를 통해 과목 구조체에 접근


			}
			for (int i = 0; i < 2; i++)// 두명의 학생의 평점 및 평균평점을 계산하기 위해 함수 두번 반복
			{
				for (int j = 0; j < 3; j++)
				{
					CalcGPA(std[i].Sub[j]);//평점 및 평균평점 계산 함수 실행
				}

				std[i].AveGPA = CalcAveGPA(std[i].Sub);

			}


			break;
		case 2:
			PrintAllData(std, 2);
			break;
		case 3: 
			SearchStd = StdSearch(std, 2);
			if (SearchStd != NULL)
				PrintOneData(*SearchStd);
			break;
		case 4:
			return 0;//메뉴의 기능 중 4번을 실행 했을시
			//프로그램 종료
		}

	}

	return 0;
}

void PrintMenu()//메뉴 출력 함수
{
	do
	{
		//메뉴 출력
		cout << "=========== 메뉴 ============\n";

		cout << "1. 학생 성적 입력.\n" << "2. 전체 학생 성적 출력\n" << "3. 학생 이름 검색\n" << "4. 프로그램 종료\n";

		cout << "원하는 기능을 입력하세요 : ";

		cin >> menutoken;//메뉴 안의 기능을 입력받음

		if (cin.fail() == 1)//비정상 입력을 받았을 시에 버퍼를 초기화 하는 함수
		{
			cin.clear();
			cin.ignore(256, '\n');
		}

	} while (menutoken != 1 && menutoken != 2 && menutoken != 3 && menutoken != 4);
	//do -while 문을 이용해 메뉴에서 요구하는 번호를 누를때 까지 반복시킴
}

void Std_scan(Student *info) //학생의 정보를 입력받는 함수
{
	cout << "이름 : ";
	cin >> info->StdName;//학생 구조체 속 학생의 이름을 받는 성분인 StdName배열에 접근해 입력받음
	cout << "학번 : ";
	cin >> info->Hakbun;//학생 구조체 속 학생의 이름을 받는 성분인 Hakbun 변수에 접근해 입력받음
	if (cin.fail() == 1)//비정상 입력시 버퍼 초기화
	{
		cin.clear();
		cin.ignore(256, '\n');
	}

}

void Sub_scan(Subject *info)//과목의 정보를 입력 받는 함수
{

	cout << "교과목명 : ";
	cin >> info->SubName;//과목 구조체 속 과목의 이름을 받는 성분인 SubName 문자열에 접근해 입력받음
	cout << "과목학점수 : ";
	cin >> info->Hakjum;//마찬가지로 Hakjum 변수에 접근해 입력 받음
	cout << "등급(A+ ~ F) : ";
	cin >> info->Grade;
	cout << "\n\n";

	if (cin.fail() == 1)//비정상 입력시 버퍼 초기화
	{
		cin.clear();
		cin.ignore(256, '\n');
	}
}

void CalcGPA(Subject& Sub)//등급에 맞는 학점 계산 함수
{
    // 입력받은 등급에 맞는 점수를 부여하기위해 문자열 비교 함수 strcmp를 활용
	// 교과목 학점과 등급에 맞는 점수를 곱한 평점 계산
	if (strcmp(Sub.Grade, "A+") == 0)
		Sub.GPA = (float)4.5 * Sub.Hakjum;
	else if (strcmp(Sub.Grade, "A0") == 0)
		Sub.GPA = (float)4.0 * Sub.Hakjum;
	else if (strcmp(Sub.Grade, "B+") == 0)
		Sub.GPA = (float)3.5 * Sub.Hakjum;
	else if (strcmp(Sub.Grade, "B0") == 0)
		Sub.GPA = (float)3.0 * Sub.Hakjum;
	else if (strcmp(Sub.Grade, "C+") == 0)
		Sub.GPA = (float)2.5 * Sub.Hakjum;
	else if (strcmp(Sub.Grade, "C0") == 0)
		Sub.GPA = (float)2.0 * Sub.Hakjum;
	else if (strcmp(Sub.Grade, "D+") == 0)
		Sub.GPA = (float)1.5 * Sub.Hakjum;
	else if (strcmp(Sub.Grade, "D0") == 0)
		Sub.GPA = (float)1.0 * Sub.Hakjum;
	else if (strcmp(Sub.Grade, "F") == 0)
		Sub.GPA = 0;

}

float CalcAveGPA(Subject* Sub) //평균평점 계산 함수
{
	//평균을 얻기 위해 각각의 값들을 더한 값을 저장할 변수 두개를 선언 SumG는 GPA의 합, SumH는 학점의 합
	
	float SumG = 0;
	float SumH = 0;

	for (int j = 0; j < 3; j++)
	{
		SumG += Sub[j].GPA;
		SumH += Sub[j].Hakjum;
	}

	return (SumG / SumH);
}

void PrintAllData(const Student* pSt, int StudentNum) // 전체 학생정보 출력 함수
{
	cout << "\n 전체학생 성적 보기\n";
	cout << "===========================================================================\n";
	for (int i = 0; i < StudentNum; i++)
	{
		PrintOneData(pSt[i]);//두 학생의 정보를 출력하기 위해 두번의 출력함수 반복
	}   
}

void PrintOneData(const Student& rst) //한명의 정보를 출력하는 함수
{
	cout.precision(2);// 소수점 이하 2자리만 출력하도록 고정
	cout << fixed;
	cout << "\n\n";
	cout << "이름 : " << rst.StdName << "  학번 : " << rst.Hakbun;//학생의 이름과 학번을 출력
	cout << "\n===========================================================================\n";
	cout << "                     과목명        과목학점       과목등급     과목평점\n";
	cout << "===========================================================================\n";
	for (int j = 0; j < 3; j++)//수강한 과목이 총 세과목이므로 세 과목의 이름, 학점, 등급, 평점을 출력
	{
		cout.width(30);
		cout << rst.Sub[j].SubName << "        " << rst.Sub[j].Hakjum << "             " << rst.Sub[j].Grade << "        " << rst.Sub[j].GPA << '\n';
	}
	cout << "===========================================================================\n";
	cout << "                       평균 평점 : " << rst.AveGPA << "\n\n\n";//계산된 학생의 평균평점을 출력
}

Student* StdSearch(Student* pSt, int StudentNum) //학생 검색 함수
// 구조체 배열의 주소값을 리턴하므로 구조체 포인터 변수형식으로 함수 선언 
{
	char searchname[30]; //검색할 학생의 이름을 받을 문자열 생성
	cout <<"\n" << "검색할 학생의 이름 : ", cin >> searchname; 
	for (int i = 0; i < StudentNum; i++)
	{
		if (strcmp(pSt[i].StdName, searchname) == 0) 
		{
			return &pSt[i];
		}
		else
			continue; 
		return NULL;

	}

	if (cin.fail() == 1)//비정상 입력시 버퍼 초기화
	{
		cin.clear();
		cin.ignore(256, '\n');
	}

}
