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
	inline string toString() const {
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
	inline string toString() const
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
	static void loading();//ͨ�ü���ҳ��
	static void menu();//������
	static void login();//��½�Ŀ��ӻ�����
	static void signUp();//ע���ʦ�Ŀ��ӻ�����
	static void error();//ͨ�ô���ҳ��
	static void studentOperation(list<Student> students);//��ʾѧ����Ϣ��ͬʱ�������¡�ɾ�������ӵĹ���
	static void studentOperation(Student student);//��ʾ����ѧ����Ϣ��ͬʱ�������µ绰�Ĺ���
	static void userOperation(list<User> users);//��ʾ�û���Ϣ��ͬʱ�������¡�ɾ�������ӵĹ��ܡ�ֻ��ӵ�й���Ա�˺��������ʦ���Խ���
	static void showStudent(list<Student> students);//ֻ������ʾѧ����Ϣ�ı������һ�Ų���
	static void showStudent(Student student);//ֻ������ʾ����ѧ����Ϣ�ı������һ�Ų���
	static void showUser(list<User> users);//ֻ������ʾ�û���Ϣ�ı������һ�Ų���
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
		getline(iss, ageStr, '\n');
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
	ifstream infile("user.txt");
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
	ofstream outfile("user.txt");
	if (!outfile) {
		cerr << "Error opening file!" << endl;
		return false;
	}
	for (auto& user : users) {
		outfile << user.toString() << endl;
	}
	outfile.close();
	return true;
}

void Panel::showStudent(list<Student>students) {
	Table table;
	table.add_row({ "ѧ��","����","���֤��","�Ա�","�绰","����","����" });
	for (auto student : students) {
		table.add_row({ student.getId(),student.getName(),student.getIdentityId(),student.getSex(),student.getPhone(),student.getBirthday(),to_string(student.getAge()) });
	}
	//��һ�е�����ֵ
	table[0].format()
		.font_style({ FontStyle::bold })
		.font_style({ FontStyle::underline })
		.font_background_color(Color::green)
		.font_color(Color::blue);
	//����������
	for (auto& roe : table) {
		roe.format().font_align(FontAlign::center);
	}
	//���߿�����
	table.format()
		.multi_byte_characters(true)
		// Font styling
		.font_style({ FontStyle::bold, FontStyle::dark })
		.font_align(FontAlign::center)
		.font_color(Color::red)
		.font_background_color(Color::yellow)
		// Corners
		.corner_top_left("x")
		.corner_top_right("x")
		.corner_bottom_left("x")
		.corner_bottom_right("x")
		.corner_top_left_color(Color::cyan)
		.corner_top_right_color(Color::yellow)
		.corner_bottom_left_color(Color::green)
		.corner_bottom_right_color(Color::red)
		// Borders
		.border_top("*")
		.border_bottom("*")
		.border_left("*")
		.border_right("*")
		.border_left_color(Color::yellow)
		.border_right_color(Color::green)
		.border_top_color(Color::cyan)
		.border_bottom_color(Color::red);
	cout << table << endl;
}

void Panel::showStudent(Student student) {
	list<Student>temp = { student };
	showStudent(temp);
}

void Panel::showUser(list<User> users) {
	Table table;
	table.add_row({ "�˺�","����","Ȩ��" });
	for (auto user : users) {
		table.add_row({ user.getAccount(),user.getPassword(),to_string(user.getRole()) });
	}
	//��һ�е�����ֵ
	table[0].format()
		.font_style({ FontStyle::bold })
		.font_style({ FontStyle::underline })
		.font_background_color(Color::green)
		.font_color(Color::blue);
	//����������
	for (auto& roe : table) {
		roe.format().font_align(FontAlign::center);
	}
	//���������е����е�Ԫ��
	for (auto& col_cell : table.column(2)) {
		if (col_cell.get_text() == "1") {
			col_cell.format().font_background_color(Color::red);
		}
	}
	//���߿�����
	table.format()
		.multi_byte_characters(true)
		// Font styling
		.font_style({ FontStyle::bold, FontStyle::dark })
		.font_align(FontAlign::center)
		.font_color(Color::red)
		.font_background_color(Color::yellow)
		// Corners
		.corner_top_left("x")
		.corner_top_right("x")
		.corner_bottom_left("x")
		.corner_bottom_right("x")
		.corner_top_left_color(Color::cyan)
		.corner_top_right_color(Color::yellow)
		.corner_bottom_left_color(Color::green)
		.corner_bottom_right_color(Color::red)
		// Borders
		.border_top("*")
		.border_bottom("*")
		.border_left("*")
		.border_right("*")
		.border_left_color(Color::yellow)
		.border_right_color(Color::green)
		.border_top_color(Color::cyan)
		.border_bottom_color(Color::red);
	cout << table << endl;
}

int main() {
	Panel::showStudent(shown_students = FileUtil::loadAllStudent());
	FileUtil::saveAllStudent(shown_students);

	Panel::showUser(allUser = FileUtil::loadAllUser());
	FileUtil::saveAllUser(allUser);

	system("pause");
	return 0;
}