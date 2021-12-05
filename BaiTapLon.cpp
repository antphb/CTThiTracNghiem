#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

typedef struct TRACNGHIEM
{
	int stt;
	char cauHoi[256];
	char dapAnA[256];
	char dapAnB[256];
	char dapAnC[256];
	char dapAnD[256];
	char ketQua;
} tracnghiem;

struct Node
{
	TRACNGHIEM data;
	Node *pNext;
};
struct List
{
	Node *lHead;
	Node *lTail;
};

struct login
{
	string hoten;
	string diachi;
	string namsinh;
	string taikhoan;
	string matkhau;
};

struct NodeLogin
{
	login info;
	NodeLogin *next;
};

struct ListLogin
{
	NodeLogin *head;
	NodeLogin *tail;
};

void INIT(List &l)
{
	l.lHead = l.lTail = NULL;
}

Node *getNode(TRACNGHIEM x)
{
	Node *p = new Node;
	if (p == NULL)
	{
		cout << "Khong the cap phat bo nho!";
		return NULL;
	}
	p->data = x;
	p->pNext = NULL;
	return p;
}

bool kiemTraTrungCauHoi(List l, TRACNGHIEM x)
{
	Node *p = l.lHead;
	while (p != NULL)
	{
		if (strcmpi(p->data.cauHoi, x.cauHoi) == 0)
		{
			return true;
		}
		p = p->pNext;
	}
	return false;
}

bool addLast(List &l, Node *p)
{
	if (l.lHead == NULL)
	{
		l.lHead = l.lTail = p;
	}
	else
	{
		l.lTail->pNext = p;
		l.lTail = p;
	}
	return true;
}

// ham nay goi den ham kiemTraTrungCauHoi, va ham addLast // Hieu, 4/12/2021
bool insertNode(List &l, TRACNGHIEM x)
{
	Node *p = getNode(x);
	if (p == NULL)
	{
		return false;
	}
	// kiem tra cau hoi co trung voi cau hoi da co trong danh sach hay chua? // Hieu, 4/12/2021
	if (kiemTraTrungCauHoi(l, x) == true)
	{
		return false;
	}
	return addLast(l, p);
}


void initLogin(ListLogin &l)
{
	l.head=l.tail= NULL;
}

NodeLogin *getnodelogin(login info)
{
	NodeLogin *p;
	p=new NodeLogin;
	if (p==NULL)
	{
		return NULL;
	}
	p->info=info;
	p->next=NULL;
	return p;
}

void addlastLogin(ListLogin &l, NodeLogin *new_node)
{
	if (l.head==NULL)
	{
		l.head=l.tail=new_node;
	}
	else
	{
		l.tail->next=new_node;
		l.tail=new_node;
	}
}

void insertlogin(ListLogin &l, login info)
{
	NodeLogin *new_node= getnodelogin(info);
	if (new_node == NULL)
	{
		return;
	}
	addlastLogin(l,new_node);
}

// Doc file cau hoi trac nghiem
void docFileTracNghiem(List &l)
{
	ifstream docFile("cauhoi.txt");

	if (!docFile)
	{
		cout << "Khong the mo file de doc!";
		return;
	}
	TRACNGHIEM data;
	int count = 0;
	while (!docFile.eof())
	{
		docFile>> data.stt;
		docFile.ignore();
		docFile.getline(data.cauHoi, sizeof(data.cauHoi));
		docFile.getline(data.dapAnA, sizeof(data.dapAnA));
		docFile.getline(data.dapAnB, sizeof(data.dapAnB));
		docFile.getline(data.dapAnC, sizeof(data.dapAnC));
		docFile.getline(data.dapAnD, sizeof(data.dapAnD));
		docFile >> data.ketQua;
		docFile.ignore();
		if (!docFile.eof())
		{
			bool check = insertNode(l, data);
			if (check == false)
			{
				count++;
			}
		}
	}
	if (count != 0){
		cout << "Khong the them duoc " << count << " cau hoi trong file!" << endl;
	}
	docFile.close();
}
// ghi 1 cau hoi trac nghiem trac nghiem moi bo sung vao file
bool ghiCauTracNghiemVaoFile(TRACNGHIEM data){
	ofstream ghiFile("cauhoi.txt", ios::app);
	if (ghiFile.bad()){
		cout<<"Khong the mo file de ghi!";
		return false;
	}
	ghiFile<<data.stt<<endl;
	ghiFile<<data.cauHoi<<endl;
	ghiFile<<data.dapAnA<<endl;
	ghiFile<<data.dapAnB<<endl;
	ghiFile<<data.dapAnC<<endl;
	ghiFile<<data.dapAnD<<endl;
	ghiFile<<data.ketQua<<endl;
	ghiFile.close();
	return true;
}
// xoa ki tu trong chuoi theo vi tri
void xoaTaiViTri(char str[], int index){
	for (int i = index; i < strlen(str); i++){
		str[i] = str[i+1];
	}
}
// chuan hoa chuoi, loai bo khoang cach du thua, in hoa dau dong
char* chuanHoaChuoi(char str[]){
	// xoa khoang trang o dau
	while (strlen(str) > 1 && str[0] == ' '){
		xoaTaiViTri(str, 0);
	}
	// xoa khoang trang ben trong cau
	for (int i = 0; i < strlen(str)-1; i++){
		if (str[i] == ' ' && str[i+1] == ' '){
			xoaTaiViTri(str, i);
			i--;
		}
	}
	// xoa o cuoi cau
	while (str[strlen(str)-1] == ' '){
		str[strlen(str)-1] = '\0';
	}
	// in hoa ki tu dau dong
	if (str[0] >= 'a' && str[0] <= 'z'){
		str[0] = str[0] - 32;
	}
	// in hoa ki tu sau dau cach
	for (int i = 0; i < strlen(str)-1; i++){
		if (str[i] == ' ' && str[i+1] >= 'a' && str[i+1] <= 'z'){
			str[i+1] = str[i+1] - 32;
		}
	}
	char *tempS = str;
	return tempS;
}
// them cau hoi vao danh sach va ghi cau hoi do vao file
bool themCauHoi(List &l){
	TRACNGHIEM data;
	char s1[253];
	cout<<"Nhap vao cau hoi day du: ";
	gets(data.cauHoi);
	strcpy(data.cauHoi, chuanHoaChuoi(data.cauHoi));
	cout<<"Nhap vao dap an A: ";
	gets(s1);
	sprintf(data.dapAnA, "%s %s","A)", s1);
	strcpy(data.dapAnA, chuanHoaChuoi(data.dapAnA));
	cout<<"Nhap vao dap an B: ";
	gets(s1);
	sprintf(data.dapAnB, "%s %s", "B)", s1);
	strcpy(data.dapAnB, chuanHoaChuoi(data.dapAnB));
	cout<<"Nhap vao dap an C: ";
	gets(s1);
	sprintf(data.dapAnC, "%s %s", "C)", s1);
	strcpy(data.dapAnC, chuanHoaChuoi(data.dapAnC));
	cout<<"Nhap vao dap an D: ";
	gets(s1);
	sprintf(data.dapAnD, "%s %s", "D)", s1);
	strcpy(data.dapAnD, chuanHoaChuoi(data.dapAnD));
	do{
		cout<<"Nhap vao dap an dung(a, b, c, d): ";
		cin>>data.ketQua;
	} while (data.ketQua != 'a' && data.ketQua != 'b' && data.ketQua != 'c' && data.ketQua != 'd');
	cin.ignore();
	data.stt = l.lTail->data.stt+1;
	if (insertNode(l, data) == false){
		return false;
	}
	return ghiCauTracNghiemVaoFile(data);
}

// doc file tai khoan mk;
void DocFileTKMK(ListLogin &lg)
{
	ifstream ip("tk.csv");
	login info;
	if (!ip.is_open())
	{
		cout<<"Loi mo file"<<endl;
		return;
	}
	while(ip.good())
	{
		getline(ip,info.hoten,',');
		getline(ip,info.diachi,',');
        getline(ip,info.namsinh,',');
        getline(ip,info.taikhoan,',');
        getline(ip,info.matkhau,'\n');
		insertlogin(lg,info);
	}
	ip.close();
}

// ham tra ve so luong node trong list
int sizeOfList(List l){
	int length = 0;
	Node *p = l.lHead;
	while (p != NULL){
		length++;
		p = p->pNext;
	}
	return length;
}

void createRandomList(List l, List &l2, int soLuongCauHoi){
	int soLuongList = sizeOfList(l);
	int max = soLuongList/soLuongCauHoi;
	srand(time(NULL));
	Node *p = l.lHead;
	while (p != NULL){
		int values = rand() % (max+max - 1 + 1) + 1;
		for (int i = 0; i < values; i++){
			p = p->pNext;
			if (p == NULL && sizeOfList(l2) < soLuongCauHoi){
				p = l.lHead;
			}
		}
		insertNode(l2, p->data);
		if (sizeOfList(l2) == soLuongCauHoi){
			break;
		}
	}
}

void printList(List l)
{
	Node *p = l.lHead;
	while (p != NULL)
	{
		cout << p->data.stt << endl;
		cout << p->data.cauHoi << endl;
		cout << p->data.dapAnA << endl;
		cout << p->data.dapAnB << endl;
		cout << p->data.dapAnC << endl;
		cout << p->data.dapAnD << endl;
		cout <<"Dap an: "<<p->data.ketQua << endl;
		cout << endl;
		p = p->pNext;
	}
}

void printListlogin(ListLogin l)
{
	NodeLogin *p = l.head;
	while (p != NULL)
	{
		cout << p->info.hoten<<endl;
		cout << p->info.diachi << endl;
		cout << p->info.namsinh << endl;
		cout << p->info.taikhoan << endl;
		cout << p->info.matkhau << endl;
		cout << endl;
		p =p->next;
	}
}

// Có thể chọn số lượng câu hỏi cho bài làm
int soluongcauhoi(int n)
{
	return n;
}
//giới hạn thời gian làm bài


// ham tim kiem theo cau hoi nếu có thì sẽ trả về stt  
int search(List l, char cauhoi_tk[]);
// {
// 	 return so thu tu  
// }

// ham cap nhat theo so thu tu 


// ham xoa theo so thu tu 




int main()
{
	List l;
	INIT(l);
	ListLogin lg;
	initLogin(lg);
	docFileTracNghiem(l);
	
	/* List l2;
	INIT(l2);
	createRandomList(l, l2, 20);
	printList(l2);*/ 
	
	/*DocFileTKMK(lg);
	printListlogin(lg);*/
	// them cau hoi vao danh sach, va them vao file
	themCauHoi(l);
	printList(l);
	
}
