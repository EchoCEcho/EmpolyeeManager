/*����ְ����employee ���࣬�������ٰ����������Ա𡢹��š��绰�����ڿ��Һ͹��ʡ�*/
#include<iostream>
#include<cstring>
#include<fstream>
#include<stdlib.h>
using namespace std;
class employee
{
private:
	int m_Id;    //ְ����
	float m_salary;    //����
	char m_name[20];    //ְ������
	char m_tel[14];     //�绰
	char m_office[20];    //����
	char m_sex[5];     //�Ա�
public:
	employee() {}
	employee& operator =(employee &re)
	{
		strcpy(m_name, re.m_name);
		strcpy(m_tel, re.m_tel);
		strcpy(m_office, re.m_office);
		strcpy(m_sex, re.m_sex);
		m_Id = re.m_Id;
		m_salary = re.m_salary;
		return *this;
	}
	char *get_name()
	{
		return m_name;
	}
	char *get_office()
	{
		return m_office;
	}
	float get_salary()
	{
		return m_salary;
	}
	int get_ID()
	{
		return m_Id;
	}
	friend ostream& operator <<(ostream &os, const employee &re)
	{
		os << re.m_name << "\t\t" << re.m_sex << "\t\t" << re.m_Id << "\t\t" << re.m_tel << "\t\t" << re.m_office << "\t\t" << re.m_salary << endl;
		return os;
	}
	friend istream& operator >>(istream &is, employee &re)
	{
		is >> re.m_name >> re.m_sex >> re.m_Id >> re.m_tel >> re.m_office >> re.m_salary;
		return is;
	}
	~employee() {}
};

/* 2�����빦�ܣ�����ְ����Ϣ�������浽�ļ��У�*/

void AddEmployee()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::out | ios::app | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else {
		int len;
		cout << "��������ӵ�ְ������";
		cin >> len;
		if (len > 0)
		{
			employee *emp = new employee[len];
			cout << "������ְ�����������Ա𡢹��š��绰�����ڿ��Һ͹���" << endl;
			for (int i = 0; i < len; i++)
			{
				cin >> emp[i];
				fs.write((char*)&emp[i], sizeof(emp[i]));
			}
			delete[]emp;
		}
	}
	fs.close();
	fs.clear();
}

/* 3����ѯ���ܣ�1���ܹ����ݹ��ž�ȷ��ѯְ����Ϣ��*/

void ReseachByID()
{

	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		int id, i;
		cout << "��������Ҫ��ѯ���˵Ĺ���:";
		cin >> id;
		fs.seekg(0, ios::end);     //�ļ�ָ������ļ�ĩβ
		int s = fs.tellg();        //�����ļ���С
		int n = s / sizeof(employee);    //�����ļ���ְ������
		fs.seekg(ios::beg);    //�ļ�ָ������ļ���ͷ
		employee *e = new employee[n];
		employee temp;
		for (i = 0; i < n; i++)
			fs.read((char *)&e[i], sizeof(e[i]));

		int j = -1;
		for (i = 0; i < n; i++)
			if (id == e[i].get_ID())
				j = i;
		if (j == -1)
			cout << "�޴�ְ���ţ�" << endl;
		else
		{
			cout << "����       |    �Ա�   |        ����        |     �绰           |     ����     |       ����     " << endl;
			cout << "-----------|-----------|--------------------|--------------------|--------------|-------------" << endl;
			cout << e[j];
		}
		delete[] e;
	}
	fs.close();
	fs.clear();
}

/*3����ѯ���ܣ�2���ܹ��������������Ҳ�ѯְ����Ϣ*/

void ReseachByNameAOffice()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		char name[20];
		char office[20];
		cout << "��������Ҫ��ѯ���˵�����:";
		cin >> name;
		cout << "��������Ҫ��ѯ���˵Ŀ���:";
		cin >> office;
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		employee *e = new employee[n];
		employee temp;
		int i, j;
		for (i = 0; i < n; i++)
			fs.read((char *)&e[i], sizeof(e[i]));
		j = -1;
		for (i = 0; i < n; i++)
			if (strcmp(name, e[i].get_name()) == 0 && strcmp(office, e[i].get_office()) == 0)
				j = i;
		if (j == -1)
			cout << "�޴�ְ����" << endl;
		else
		{
			cout << "����       |    �Ա�   |        ����        |     �绰           |     ����     |       ����     " << endl;
			cout << "-----------|-----------|--------------------|--------------------|--------------|-------------" << endl;
			cout << e[j];
		}
		delete[] e;
	}
	fs.close();
	fs.clear();
}

/*3����ѯ���ܣ�3���ֿ��ҽ��й���ͳ�ƣ���������ҵ�ƽ������*/

void AverSalaryByOffice()
{

	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		char office[20];
		cout << "��������Ҫ��ѯƽ�����ʵĿ���:";
		cin >> office;
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		employee *e = new employee[n];
		employee temp;
		int i, j, count;
		for (i = 0; i < n; i++)
			fs.read((char *)&e[i], sizeof(e[i]));
		j = -1;
		count = 0;
		float sum = 0;
		for (i = 0; i < n; i++)
		{
			if (strcmp(office, e[i].get_office()) == 0)
			{
				j = i;
				sum = sum + e[i].get_salary();
				count++;
			}
		}
		if (j == -1)
			cout << "�޴˿��ң�" << endl;
		else
			cout << "����" << e[j].get_office() << "��ƽ������Ϊ:" << sum / count << endl;
		delete[] e;
	}
	fs.close();
	fs.clear();
}

/*4������ְ���Ĺ����������*/

void SortBySalary()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		int i;
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		if (n == 0)
			cout << "ϵͳ����ְ����Ϣ��" << endl;
		else
		{
			employee *e = new employee[n];
			employee temp;
			for (i = 0; i < n; i++)
				fs.read((char *)&e[i], sizeof(e[i]));
			for (int j = 0; j < n - 1; j++)    //ð������
			{
				for (int k = 0; k < n - 1 - j; k++)
				{
					if (e[k].get_salary() > e[k + 1].get_salary())
					{
						temp = e[k];
						e[k] = e[k + 1];
						e[k + 1] = temp;
					}
				}
			}
			cout << "----------------------------------------����������--------------------------------------------" << endl;
			cout << "����       |    �Ա�   |        ����        |     �绰           |     ����     |       ����     " << endl;
			cout << "-----------|-----------|--------------------|--------------------|--------------|-------------" << endl;
			for (i = 0; i < n; i++)
				cout << e[i];
			delete[] e;
		}
	}
	fs.close();
	fs.clear();
}

/* 5�����ݹ����޸�ְ����Ϣ*/

void ModEmployee()
{

	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::out | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		int id, i;
		cout << "������Ҫ�޸ĵ�ְ����:";
		cin >> id;
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		int j = -1;
		employee *e = new employee[n];
		for (i = 0; i < n; i++)
			fs.read((char *)&e[i], sizeof(e[i]));
		for (i = 0; i < n; i++)
		{
			if (id == e[i].get_ID())
				j = i;
		}
		if (j == -1)
			cout << "�޴�ְ����" << endl;
		else
		{
			fs.seekp(sizeof(employee)*j);
			employee t;
			cout << "�������޸�ְ�����������Ա𡢹��š��绰�����ڿ��Һ͹���" << endl;
			cin >> t;
			fs.write((char *)&t, sizeof(employee));
			cout << "ְ����Ϣ�޸ĳɹ���" << endl;
		}
		delete[] e;
	}
	fs.close();
	fs.clear();
}

//���������Ա��Ϣ
void Show()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		if (n == 0)
			cout << "ϵͳ����ְ����Ϣ��" << endl;
		else
		{
			employee *e = new employee[n];
			cout << "----------------------------------------����ְ����Ϣ------------------------------------------" << endl;
			cout << "����       |    �Ա�   |        ����        |     �绰           |     ����     |       ����     " << endl;
			cout << "-----------|-----------|--------------------|--------------------|--------------|-------------" << endl;
			for (int i = 0; i < n; i++)
			{
				fs.read((char *)&e[i], sizeof(e[i]));
				cout << e[i];
			}
			delete[] e;
		}

	}
	fs.close();
	fs.clear();
}

/* 6�����ݹ���ɾ��ְ����Ϣ*/

void DelEmployee()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else
	{
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		if (n == 0)
			cout << "ϵͳ����ְ����Ϣ��" << endl;
		else
		{
			employee *e = new employee[n];
			int id, i, j;
			for (i = 0; i < n; i++)
			{
				fs.read((char *)&e[i], sizeof(e[i]));
			}
			fs.close();
			fs.clear();
			cout << "������Ҫɾ����ְ���ţ�";
			cin >> id;
			for (i = 0; i < n; i++)
			{
				j = -1;
				if (id == e[i].get_ID())
					j = i;
			}
			fs.open("employeeinfo.dat", ios::out | ios::trunc | ios::binary);
			for (i = 0; i < n; i++)
			{
				if (i == j)
					continue;
				else
				{
					fs.write((char *)&e[i], sizeof(e[i]));
				}
			}
			if (j == -1)
				cout << "�޴�ְ����" << endl;
			else
				cout << "��ְ���ѳɹ�ɾ����" << endl;
			fs.close();
			fs.clear();
			delete[] e;
		}
	}
}

//�˵�����
void Meun()
{
	cout << "====================================== ְ�����ʹ���ϵͳ =======================================" << endl;
	cout << "||                                                                                           ||" << endl;
	cout << "||                              ����������������������������                                 ||" << endl;
	cout << "||                             | * 1.���ְ����Ϣ          |                                 ||" << endl;
	cout << "||                             | * 2.���Ų���ְ��          |                                 ||" << endl;
	cout << "||                             | * 3.����+���Ҳ���ְ��     |                                 ||" << endl;
	cout << "||                             | * 4.������ƽ������        |                                 ||" << endl;
	cout << "||                             | * 5.�����ʶ�ְ������      |                                 ||" << endl;
	cout << "||                             | * 6.�޸���Ա��Ϣ          |                                 ||" << endl;
	cout << "||                             | * 7.ɾ����Ա��Ϣ          |                                 ||" << endl;
	cout << "||                             | * 8.���������Ա��Ϣ      |                                 ||" << endl;
	cout << "||                             | * 0.�ر�ϵͳ              |                                 ||" << endl;
	cout << "||                              ����������������������������                                 ||" << endl;
	cout << "||                                                     Designed By ZeyuGuo                   ||" << endl;
	cout << "===============================================================================================" << endl;
	cout << "������ѡ��(0-8)��";
}

//������
int main()
{

	char flag = 'n';
	while (flag == 'n' || flag == 'N')    //��y/n����ѭ��
	{
		Meun();
		int judge;
		cin >> judge;
		if (judge >= 0 && judge <= 8)
		{
			switch (judge)
			{
			case 0:
				cout << "�Ƿ��˳�ϵͳ(y/n):";
				cin >> flag;
				break;
			case 1:
				AddEmployee();
				break;
			case 2:
				ReseachByID();
				break;
			case 3:
				ReseachByNameAOffice();
				break;
			case 4:
				AverSalaryByOffice();
				break;
			case 5:
				SortBySalary();
				break;
			case 6:
				ModEmployee();
				break;
			case 7:
				DelEmployee();
				break;
			case 8:
				Show();
				break;
			default:
				break;
			}
		}
		else
			cout << "�����������������!" << endl;
		cout << "��������������˵�!" << endl;
		getchar();
		getchar();
		system("cls");
	}
	return 0;
}