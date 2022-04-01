/***************************************************************/
/*             HW#3 : ����ü,���۷���,�Լ���������                                    */
/*  �ۼ��� : 2018038025 ���Ͽ�                    ��¥ : 2022�� 3�� 11��  */
/*                                                                                     */
/* ���� ���� :  �θ��� �л��� ����(�̸�, �й�)�� �Է¹ް�
			�� �л��� ������ �������� ������ ����(�����, ��������, ���)��
			�Է� �޾� �л��� ���� ���� �� �� ������ ��� ������ ����� ����ϴ� ���� ó�� ���α׷�
			���� ���α׷��� �Լ�ȭ �ϰ� �߰��� �л��� �̸��� �˻��� �л��� ���� ������ ����ϴ� ����� �߰��ߴ�.
			*/

			/***************************************************************/
#include <iostream>//C++���� ����� �⺻ ����� �Լ��� ���ǵ� ������� ����
#include <cstring>//���ڿ��� ���� ���ϴ� �Լ��� strcmp()�Լ��� ���ǵ� ������� ����
using namespace std;// namespase�� �ִ� std Ŭ������ ���ǵǾ��ִ� �Լ����� ����ϰڴ� ����

typedef struct //�������� ������ �޴� ����ü ����
{
	char SubName[30];//������ �̸��� ���� ���ڿ�
	int Hakjum;//���� ����
	char Grade[10];//����� ���� ���ڿ�
	float GPA;//���� ������ ���� ������ ���������� ��޺� ������ ���� ���̴�
}Subject;

typedef struct //�л��� ������ �޴� ����ü ����
{
	char StdName[30];//�л��� �̸��� ���� ���ڿ�
	int Hakbun;//�й�
	Subject Sub[3];//�� �л��� �������� �ޱ�� �����Ƿ� �л� ����ü �ȿ� ũ�Ⱑ 3�� ���� ����ü �迭�� ����
	float AveGPA;//�л� ��� �������� �� ���� �������� ���� ���� �������� ������ ���� ���̴�
}Student;

// �Լ��� ������Ÿ�� ����
void PrintMenu();
void Std_scan(Student *name);
void Sub_scan(Subject *info);
void CalcGPA(Subject& Sub);
float CalcAveGPA(Subject* Sub);
void PrintAllData(const Student* pSt, int StudentNum);
void PrintOneData(const Student& rst);
Student* StdSearch(Student* pSt, int StudentNum);

int menutoken = 0;//�޴��� ������ ������, switch - case ������ Ȱ���� �������� ����

//�����Լ� ����
int main()
{
	Student std[2] = {};//�л� �θ��� ������ �ޱ� ���� ũ�Ⱑ 2�� �л� ����ü�迭�� ����
	Student* SearchStd;


	for (; ;)// �޴� ��� ���� ����
	{

		PrintMenu(); 


		switch (menutoken)
		{
		case 1:

			for (int i = 0; i < 2; i++)//�θ��� �л��� ������ �ޱ� ���� ù ��° ���� ����
			{
				cout << "\n\n\n" << i + 1 << "��° �л��� ������ �Է��ϼ���.\n";

				Std_scan(&std[i]);//�л� ���� �Է¹޴� �Լ� ����
				//�ʱ⿡ ������ �л�����ü �迭�� �ּҸ� �Ѱ���

				cout << "\n\n\n������ ���� ������ �� �������, ����, ����� �Է��ϼ���.\n";

				for (int j = 0; j < 3; j++)//�л� �Ѹ�� �������� ������ �Է� �ޱ� ���� �� ��° ���� ����
					Sub_scan(&std[i].Sub[j]);//������ ������ �Է¹޴� �Լ� ����
					//�л� ����ü �ȿ� ���� ����ü�迭�� ����Ǿ� �־ �л� ����ü�� ���� ���� ����ü�� ����


			}
			for (int i = 0; i < 2; i++)// �θ��� �л��� ���� �� ��������� ����ϱ� ���� �Լ� �ι� �ݺ�
			{
				for (int j = 0; j < 3; j++)
				{
					CalcGPA(std[i].Sub[j]);//���� �� ������� ��� �Լ� ����
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
			return 0;//�޴��� ��� �� 4���� ���� ������
			//���α׷� ����
		}

	}

	return 0;
}

void PrintMenu()//�޴� ��� �Լ�
{
	do
	{
		//�޴� ���
		cout << "=========== �޴� ============\n";

		cout << "1. �л� ���� �Է�.\n" << "2. ��ü �л� ���� ���\n" << "3. �л� �̸� �˻�\n" << "4. ���α׷� ����\n";

		cout << "���ϴ� ����� �Է��ϼ��� : ";

		cin >> menutoken;//�޴� ���� ����� �Է¹���

		if (cin.fail() == 1)//������ �Է��� �޾��� �ÿ� ���۸� �ʱ�ȭ �ϴ� �Լ�
		{
			cin.clear();
			cin.ignore(256, '\n');
		}

	} while (menutoken != 1 && menutoken != 2 && menutoken != 3 && menutoken != 4);
	//do -while ���� �̿��� �޴����� �䱸�ϴ� ��ȣ�� ������ ���� �ݺ���Ŵ
}

void Std_scan(Student *info) //�л��� ������ �Է¹޴� �Լ�
{
	cout << "�̸� : ";
	cin >> info->StdName;//�л� ����ü �� �л��� �̸��� �޴� ������ StdName�迭�� ������ �Է¹���
	cout << "�й� : ";
	cin >> info->Hakbun;//�л� ����ü �� �л��� �̸��� �޴� ������ Hakbun ������ ������ �Է¹���
	if (cin.fail() == 1)//������ �Է½� ���� �ʱ�ȭ
	{
		cin.clear();
		cin.ignore(256, '\n');
	}

}

void Sub_scan(Subject *info)//������ ������ �Է� �޴� �Լ�
{

	cout << "������� : ";
	cin >> info->SubName;//���� ����ü �� ������ �̸��� �޴� ������ SubName ���ڿ��� ������ �Է¹���
	cout << "���������� : ";
	cin >> info->Hakjum;//���������� Hakjum ������ ������ �Է� ����
	cout << "���(A+ ~ F) : ";
	cin >> info->Grade;
	cout << "\n\n";

	if (cin.fail() == 1)//������ �Է½� ���� �ʱ�ȭ
	{
		cin.clear();
		cin.ignore(256, '\n');
	}
}

void CalcGPA(Subject& Sub)//��޿� �´� ���� ��� �Լ�
{
    // �Է¹��� ��޿� �´� ������ �ο��ϱ����� ���ڿ� �� �Լ� strcmp�� Ȱ��
	// ������ ������ ��޿� �´� ������ ���� ���� ���
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

float CalcAveGPA(Subject* Sub) //������� ��� �Լ�
{
	//����� ��� ���� ������ ������ ���� ���� ������ ���� �ΰ��� ���� SumG�� GPA�� ��, SumH�� ������ ��
	
	float SumG = 0;
	float SumH = 0;

	for (int j = 0; j < 3; j++)
	{
		SumG += Sub[j].GPA;
		SumH += Sub[j].Hakjum;
	}

	return (SumG / SumH);
}

void PrintAllData(const Student* pSt, int StudentNum) // ��ü �л����� ��� �Լ�
{
	cout << "\n ��ü�л� ���� ����\n";
	cout << "===========================================================================\n";
	for (int i = 0; i < StudentNum; i++)
	{
		PrintOneData(pSt[i]);//�� �л��� ������ ����ϱ� ���� �ι��� ����Լ� �ݺ�
	}   
}

void PrintOneData(const Student& rst) //�Ѹ��� ������ ����ϴ� �Լ�
{
	cout.precision(2);// �Ҽ��� ���� 2�ڸ��� ����ϵ��� ����
	cout << fixed;
	cout << "\n\n";
	cout << "�̸� : " << rst.StdName << "  �й� : " << rst.Hakbun;//�л��� �̸��� �й��� ���
	cout << "\n===========================================================================\n";
	cout << "                     �����        ��������       ������     ��������\n";
	cout << "===========================================================================\n";
	for (int j = 0; j < 3; j++)//������ ������ �� �������̹Ƿ� �� ������ �̸�, ����, ���, ������ ���
	{
		cout.width(30);
		cout << rst.Sub[j].SubName << "        " << rst.Sub[j].Hakjum << "             " << rst.Sub[j].Grade << "        " << rst.Sub[j].GPA << '\n';
	}
	cout << "===========================================================================\n";
	cout << "                       ��� ���� : " << rst.AveGPA << "\n\n\n";//���� �л��� ��������� ���
}

Student* StdSearch(Student* pSt, int StudentNum) //�л� �˻� �Լ�
// ����ü �迭�� �ּҰ��� �����ϹǷ� ����ü ������ ������������ �Լ� ���� 
{
	char searchname[30]; //�˻��� �л��� �̸��� ���� ���ڿ� ����
	cout <<"\n" << "�˻��� �л��� �̸� : ", cin >> searchname; 
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

	if (cin.fail() == 1)//������ �Է½� ���� �ʱ�ȭ
	{
		cin.clear();
		cin.ignore(256, '\n');
	}

}
