#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<list>
#include<ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include "tabulate/table.hpp"

using namespace tabulate;
using namespace std;

//forward declarations
class Student;
class User;

class User
{
private:
	string account;//Ψһ��ʶ
	string password;
	short role;//ѧ��0����ʦ1
public:
	//constructors
	User() {};
	User(string account, string password, short role)
		:account(account), password(password), role(role) {};
	User(const User& user)//����Ϊ������
		:account(user.account), password(user.password), role(user.role) {};
	//getters and setters
	string getAccount() { return account; }
	string getPassword() { return password; }
	string getUser() const {
		return account + "," + password + "," + to_string(role);
	}
	short getRole() { return role; }
	void setAccount(string account) { this->account = account; }
	void setPassword(string password) { this->password = password; }
	void setRole(short role) { this->role = role; }
	//methods
	bool login();
	//��User��ص�
	bool addOneUser(User user);//����һ���û�����Ҫ����account��Ψһ��
	bool deleteOneUser(string account);//ɾ��һ���û�
	bool showOneUser(string account);//�鿴һ���û���Ϣ
	bool showAllUser();//�鿴�����û���Ϣ
	bool updateOneUser(User user);//�޸��û���Ϣ

	//��Student��ص�
	// ����Ȩ��
	bool updateOneStudent(Student student);//ѧ��ֻ���޸��Լ��ĵ绰�����գ���ʦ���������޸�
	//ѧ����Ȩ��
	bool showOneStudent(string id);//ѧ��ֻ�ܲ鿴�Լ���ѧ����Ϣ
	//��ʦ��Ȩ��
	bool showAllStudent();//��ʦ���Բ鿴����ѧ����Ϣ
	bool addOneStudent(Student student);//��ʦ��������һ��ѧ��
	bool deleteOneStudent(string id);//��ʦ����ɾ��һ��ѧ��
	bool signUp();//ֻ��ӵ�й���Ա�˺ź��������ʦ����ע������ʦ
};

class Student
{
private:
	string id;
	string name;
	string identityId;
	string sex;
	string phone;
	string birthday;
	short age;
public:
	//construtors
	Student() {};
	inline Student(string id, string name, string identityId, string sex, string phone, string birthday)
		:id(id), name(name), identityId(identityId), sex(sex), phone(phone), birthday(birthday) {
		//�������䲢��ֵ
		int birthYear = atoi(birthday.substr(0, 4).c_str());
		int birthMonth = atoi(birthday.substr(5, 2).c_str());
		time_t now;
		time(&now);
		tm* nowTime = localtime(&now);
		int nowYear = 1900 + nowTime->tm_year;
		int nowMonth = 1 + nowTime->tm_mon;
		age = nowYear - birthYear;
		if (nowMonth < birthMonth) {
			age--;
		}
	};
	Student(const Student& student)//������ǳ����ã���Ȼ�ᱨ��
		:id(student.id), name(student.name), identityId(student.identityId), sex(student.sex), phone(student.phone), birthday(student.birthday), age(student.age) {};
	//getters and setters
	inline string toString()
	{
		return id + "," + name + "," + identityId + "," + sex + "," + phone + "," + birthday + "," + to_string(age);
	}
	inline vector<string> toVectorString() {
		vector <string> v;
		v.push_back(id);
		v.push_back(name);
		v.push_back(identityId);
		v.push_back(sex);
		v.push_back(phone);
		v.push_back(birthday);
		v.push_back(to_string(age));
	}
	string getId() { return id; }
	string getName() { return name; }
	string getSex() { return sex; }
	string getPhone() { return phone; }
	string getBirthday() { return birthday; }
	short getAge() { return age; }
	string getIdentityId() { return identityId; }
	void setId(string id) { this->id = id; }
	void setName(string name) { this->name = name; }
	void setSex(string sex) { this->sex = sex; }
	void setPhone(string phone) { this->phone = phone; }
	void setBirthday(string birthday) { this->birthday = birthday; }
	void setAge(short age) { this->age = age; }
	//methods
};

class FileUtil
{
public:
	static list<Student> loadAllStudent();//��������ѧ��
	static list<User> loadAllUser();//���������û�
	static bool saveAllUser(list<User> users);//���������û������ø��ǵķ�ʽʵ�֣������޸ġ�ɾ��������ʵ��
	static bool saveAllStudent(list<Student> students);//��������ѧ�������ø��ǵķ�ʽʵ�֣������޸ġ�ɾ��������ʵ��
};

class Panel
{
public:
	void loading();//ͨ�ü���ҳ��
	void menu();//������
	void login();//��½�Ŀ��ӻ�����
	void signUp();//ע���ʦ�Ŀ��ӻ�����
	void error();//ͨ�ô���ҳ��
	void studentOperation(list<Student> students);//��ʾѧ����Ϣ��ͬʱ�������¡�ɾ�������ӵĹ���
	void studentOperation(Student student);//��ʾ����ѧ����Ϣ��ͬʱ�������µ绰�Ĺ���
	void userOperation(list<User> users);//��ʾ�û���Ϣ��ͬʱ�������¡�ɾ�������ӵĹ��ܡ�ֻ��ӵ�й���Ա�˺��������ʦ���Խ���
};

//global variables
list<Student> shown_students;//������ʾ��ѧ���б�
list<User> allUser;//�����û�
User now_user;//��ǰ��¼���û�

list<Student> FileUtil::loadAllStudent() {
	list<Student> students;
	ifstream infile("student.txt");
	if (!infile) {
		cerr << "Error opening file!" << endl;
		return students;
	}
	string line;
	while (getline(infile, line)) {
		istringstream iss(line);
		string id, name, identityId, sex, phone, birthday, ageStr;
		getline(iss, id, ',');
		getline(iss, name, ',');
		getline(iss, identityId, ',');
		getline(iss, sex, ',');
		getline(iss, phone, ',');
		getline(iss, birthday, ',');
		getline(iss, ageStr, ',');
		Student student(id, name, identityId, sex, phone, birthday);
		students.push_back(student);
	}
	infile.close();
	return students;
}

// ���� saveAllStudent ����
bool FileUtil::saveAllStudent(list<Student> students) {
	ofstream outfile("student.txt");
	if (!outfile) {
		cerr << "Error opening file!" << endl;
		return false;
	}
	for (auto& student : students) {
		outfile << student.toString() << endl;
	}
	outfile.close();
	return true;
}

// ���������û�
list<User> FileUtil::loadAllUser() {
	list<User> users;
	ifstream infile("E:\\code\\StudentManagement\\user.txt");
	if (!infile) {
		cerr << "Error opening file!" << endl;
		return users;
	}
	string line;
	while (getline(infile, line)) {
		istringstream iss(line);
		string account, password, roleStr;
		getline(iss, account, ',');
		getline(iss, password, ',');
		getline(iss, roleStr, ',');
		short role = stoi(roleStr);
		User user(account, password, role);
		users.push_back(user);
	}
	infile.close();
	return users;
}

// ���������û������ø��ǵķ�ʽʵ�֣������޸ġ�ɾ��������ʵ��
bool FileUtil::saveAllUser(list<User> users) {
	ofstream outfile("E:\\code\\StudentManagement\\user.txt");
	if (!outfile) {
		cerr << "Error opening file!" << endl;
		return false;
	}
	for (auto& user : users) {
		outfile << user.getUser() << endl;
	}
	outfile.close();
	return true;
}

int main() {
	Student yujingyi("202100810120", "�ھ���", "123456789012345678", "Ů", "12345678901", "2000-01");
	cout << yujingyi.toString() << endl;

	Table studentTableTest; // ����һ������ hellogithub �� Table ����
	studentTableTest.add_row({ "ѧ��","����","���֤��","�Ա�","�绰","����","����" });

	shown_students = FileUtil::loadAllStudent();
	for (auto student : shown_students) {
		studentTableTest.add_row({ student.getId(),student.getName(),student.getIdentityId(),student.getSex(),student.getPhone(),student.getBirthday(),to_string(student.getAge()) });
	}
	cout << studentTableTest << endl;
	FileUtil::saveAllStudent(shown_students);

	allUser = FileUtil::loadAllUser();
	for (auto user : allUser) {
		cout << user.getUser() << endl;
	}
	FileUtil::saveAllUser(allUser);

	system("pause");
	return 0;
}