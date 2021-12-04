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
	cout << "Khong the them duoc " << count << " cau hoi trong file!" << endl;
	docFile.close();
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

// xin chào tôi tên là thanh làm phần log in 


int main()
{
	List l;
	INIT(l);
	docFileTracNghiem(l);
	printList(l);
}
