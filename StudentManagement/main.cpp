#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<list>
#include<ctime>
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
	User(User& user)
		:account(user.account), password(user.password), role(user.role) {};
	//getters and setters
	string getAccount() { return account; }
	string getPassword() { return password; }
	short getRole() { return role; }
	void setAccount(string account) { this->account = account; }
	void setPassword(string password) { this->password = password; }
	void setRole(short role) { this->role = role; }
	//methods
	bool login(User user);
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
	list<Student> loadStudent();//��������ѧ��
	bool signUp(User user);//ֻ��ӵ�й���Ա�˺ź��������ʦ����ע������ʦ
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
	inline Student(string id, string name, string identityId, string sex, string birthday)
		:id(id), name(name), identityId(identityId), sex(sex), birthday(birthday) {
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
	Student(Student& student)
		:id(student.id), name(student.name), identityId(student.identityId), sex(student.sex), phone(student.phone), birthday(student.birthday), age(student.age) {};
	//getters and setters
	string getId() { return id; }
	string getName() { return name; }
	string getSex() { return sex; }
	string getPhone() { return phone; }
	string getBirthday() { return birthday; }
	short getAge() { return age; }
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
	static list<Student> loadStudent();//��������ѧ��
	static list<User> loadUser();//���������û�
	static bool saveAllUser(list<User> users);//���������û������ø��ǵķ�ʽʵ�֣������޸ġ�ɾ��������ʵ��
	static bool saveAllStudent(list<Student> students);//��������ѧ�������ø��ǵķ�ʽʵ�֣������޸ġ�ɾ��������ʵ��
	static list<User> loadAllUser();//loadUser()��ʵ��
	static list<Student> loadAllStudent();//loadStudent()��ʵ��
};

class Panel
{
public:
	void login();//��¼���
};

//global variables
list<Student> shown_students;//������ʾ��ѧ���б�
User now_user;//��ǰ��¼���û�

int main() {
	Student student("202100810120", "�ھ���", "510105200203280019", "��", "2002-06");
	cout << student.getAge() << endl;

	Table hellogithub; // ����һ������ hellogithub �� Table ����

	hellogithub.add_row({ "HelloGitHub","HelloMotherfucker~" });
	hellogithub.add_row({ "hellogithub.com" });
	hellogithub[1][0].format()
		.font_style({ FontStyle::underline });
	hellogithub.add_row({ "github.com/521xueweihan/HelloGitHub" });
	hellogithub[2][0].format()
		.font_style({ FontStyle::underline })
		.font_background_color(Color::red)
		.font_style({ FontStyle::bold });
	hellogithub.add_row({ "xueweihan NB!!!" });

	cout << hellogithub << endl;

	system("pause");

	return 0;
}