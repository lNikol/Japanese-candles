#include <iostream>
#include "Console.h"
using namespace std;

void Console::showAuthor() {
	cout << "Hello!\n";
	cout << "Author:\n";
	cout << "Nikolai Lavrinov 201302\n\n\n";
}

void Console::printMenu() {
	cout << "1) g - Graphic from intc_us_data.csv to chart.txt (�� ��������� 200 ����)\n";
	cout << "2) v - Graphic �� ������� ������������\n"; // ��� ����������� ��� ������ ��� �������
	// 1) ������� ��� ��������� ����� (��������.csv � ����� � ����������) ��� ������� ������ ���� � ������ ����� � ����������� csv, ��� �������� ���� ������ 
	// ��� ���� - (���� ������ ��������� � ����� � ����������)  
	// ���� �������� ������, �� ������� ���� ����
	// ��� ����������: ����� ����� ����� ��� ���������� - 260 ��������
	// ������������ ����������� ������ ����� �� ����: �������� "��� ������� ������ ���� � ������ ����� � �����������
	//  � ���� �� ������ ��� ���� - �������� ��� ����������� ������ ��� ��������� �������
	// 2) �������� ������ ������� ��� �������� ���� ������ (=50 ��������)
	// 3) �������� ������ ������� ��� �������� ���� ������ (=200 ��������)
	// 4) �������� ������ ������� (� ��������� ${minData} � ${maxData} �� ��������� ����� ������������ ��� ������ �����)
	// 5) �������� ����� ������� (� ��������� ${minData} � ${maxData} �� ��������� ����� ������������ ��� ������ �����) 
	// ��� �������� ������ (����� 200 ���� �� ��������� ����)
	// 6) �������� ������� ����� (1 - 1 ����, 5 - 1 ������, 20 - 1 �����)
	// 7) ������� ������ � ������� (y - ��, n - ���)
	// 8) ������� ������ � ���� (y - ��, n - ���)
	// 8.1) ���� ����� == y, ��: cout<<������� ��� ����� ��� ���� � ������ � ����������� �����
	// 8.2) ������� ���� �� ��������� ����������. 
	// ���� ������, �� ������� ��������� "������ �������� �����". �������� ���� ���� ��� �������� ����� 
	// ��� �������� ���� ������ ��� ������ ������� �� �������
	// 8.3) ���� ��� ������, �� ������� ������ � �������
	// 9) ����� ����� �������� ��������� �������� � ���� � ����

	cout << "3) q - end program\n";

}

