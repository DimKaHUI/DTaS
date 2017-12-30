#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include "bigreal.h"



int main(void)
{
	setlocale(LC_ALL, "RUS");

	printf("������������ ����� ������������� �����:\n");
	printf("1) ����� ������� ��� ��������\n2) ����� ��������� ���� ����������� ����\n");
	printf("3) ����� �������� ����������� ������ ���� ����� (���� ������� �������������)\n");
	printf("4) ��������� ������ E � � ���� �������� � � ���� ��������� ����� (���������)\n");
	printf("5) ������ ��������� �� ������ ��������� %d �������� (�� ������ �����)\n", MANTISSA_MAX_SIZE);
	printf("6) ����� ������� �� ������ ��������� %d �������� (�� ������ �����)\n", ORDER_MAX_SIZE);

	bigreal_t dividend;
	bigint_t divisor;
	bigreal_t division;
	printf("Input dividend: \n");
	int input_error = read_real_from_line(&dividend);
	switch (input_error)
	{
	case ERROR_ILLEGAL_FORMAT:
		printf("������������ ������ ����� ������������� �����.\n");
		break;
	case ERROR_BIGREAL_IO:
		printf("������������ ����: ������������ ������.\n");
		break;
	case ERROR_DOT_AFTER_E:
		printf("������������ ����: ����� � ������ �������.\n");
		break;
	case ERROR_TOO_MANY_DOTS:
		printf("������������ ����: ��������� �����\n");
		break;
	case ERROR_TOO_MANY_E:
		printf("������������ ����: ��������� E.\n");
		break;		
	case ERROR_NO_SIGN:
		printf("���������� ���� ��������� ���� ��������.\n");
		break;
	case ERROR_TOO_MANY_SIGNS:
		printf("������� ����� ������ (+/-)\n");
		break;
	case ERROR_TOO_LARGE_MANTISSA:
		printf("������� ������� ��������\n");
		break;
	case ERROR_TOO_LARGE_ORDER:
		printf("������� ������� ��������\n");
		break;
	case ERROR_SIGN_INSIDE_NUMER:
		printf("���� ������� ������ �����.\n");
	}
	//print_real(dividend);
	if (input_error != 0)
	{
		_getch();
		return -1;
	}

	printf("������������: \n");
	int normalization_error = normalize(&dividend);
	if (normalization_error != 0)
		printf("���������� ������������� ��������� �����.\n");
	print_real(dividend);
	printf("\n");
	
	// Reading divisor
	printf("������� �������� (������� �����): ");
	input_error = read_int_from_line(&divisor);
	switch (input_error)
	{
	case ERROR_BIGINT_IO:
		printf("������������ ����: ������������ ������.\n");
		break;
	case ERROR_NO_SIGN:
		printf("���������� ���� ��������� ����.\n");
		break;
	case ERROR_TOO_BIG_INT:
		printf("����� ����� �� ������ ��������� %d", BIGINT_SIZE);
	}
	if (input_error != 0)
	{
		_getch();
		return -1;
	}

	int err = devide_real_int(dividend, divisor, &division);
	switch (err)
	{
	case ERROR_OVERFLOW:
		printf("������������ ������.\n");
		break;
	case ERROR_ZERO_DIVISION:
		printf("������� �� ����.\n");
	}
	if (err != 0)
	{
		_getch();
		return -1;
	}

	
	printf("Division: \n");
	//print_real(division);

	// TODO ANSWER_NORMALISATION
	printf("\n������������: \n");
	//normalization_error = normalize(&division);
	//if (normalization_error != 0)
		//printf("���������� ������������� ������������ �����.\n");
	//if (normalization_error == 0 || 1)
	
	if(normalize_for_answer(&division) != 0)
			printf("���������� ������������� ������������ �����, ������������ �������.\n");	
	else
	{

		print_grid(&division);
		print_real(division);
		printf("\n");
	}
	_getch();
	return 0;
}
