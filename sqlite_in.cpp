#include "sqlite3.h"  
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	ofstream out;
	out.open("temp.txt");
	sqlite3 * pDB = NULL;
	int nRes = sqlite3_open("D:\\aflw\\data\\aflw.sqlite", &pDB);
	if (nRes != SQLITE_OK)
	{
		cout << "Open database fail: " << sqlite3_errmsg(pDB);
		sqlite3_close(pDB);
		return 0;
	}
	else
		cout << "Open DB successfully!" << endl;

	string FaceImage_Sql = "select * from FaceImages";
	char** p_FaceImage_Result;
	int FaceImage_Row;
	int FaceImage_Col;
	char *FaceImage_errmsg;
	int FaceImage_nResult = sqlite3_get_table(pDB, FaceImage_Sql.c_str(), &p_FaceImage_Result, &FaceImage_Row, &FaceImage_Col, &FaceImage_errmsg);
	if (FaceImage_nResult != SQLITE_OK)
	{
		sqlite3_close(pDB);
		sqlite3_free_table(p_FaceImage_Result);
		cout << FaceImage_errmsg << endl;
		sqlite3_free(FaceImage_errmsg);
		return 0;
	}

	string Faces_Sql = "select * from Faces";
	char** p_Faces_Result;
	int Faces_Row;
	int Faces_Col;
	char *Faces_errmsg;
	int Faces_nResult = sqlite3_get_table(pDB, Faces_Sql.c_str(), &p_Faces_Result, &Faces_Row, &Faces_Col, &Faces_errmsg);
	if (Faces_nResult != SQLITE_OK)
	{
		sqlite3_close(pDB);
		sqlite3_free_table(p_Faces_Result);
		cout << Faces_errmsg << endl;
		sqlite3_free(Faces_errmsg);
		return 0;
	}

	string FaceRect_Sql = "select * from FaceRect";
	char** p_FaceRect_Result;
	int FaceRect_Row;
	int FaceRect_Col;
	char *FaceRect_errmsg;
	int FaceRect_nResult = sqlite3_get_table(pDB, FaceRect_Sql.c_str(), &p_FaceRect_Result, &FaceRect_Row, &FaceRect_Col, &FaceRect_errmsg);
	if (FaceRect_nResult != SQLITE_OK)
	{
		sqlite3_close(pDB);
		sqlite3_free_table(p_FaceRect_Result);
		cout << FaceRect_errmsg << endl;
		sqlite3_free(FaceRect_errmsg);
		return 0;
	}


	int nRow = 1;
	int cnt = 1;
	string str1[30000];
	//string str2;
	int nCnt[30000];
	str1[nRow] += p_FaceRect_Result[7]; 
	str1[nRow] += '\t';
	str1[nRow] += p_FaceRect_Result[8];
	str1[nRow] += '\t';
	str1[nRow] += p_FaceRect_Result[9];
	str1[nRow] += '\t';
	str1[nRow] += p_FaceRect_Result[10];
	str1[nRow] += '\t';

	for (int i = 2;i<Faces_Row;i++)
	{

		string str2 = p_Faces_Result[i * Faces_Col + 1];
		string str3 = p_Faces_Result[(i-1) * Faces_Col + 1];
		if (!str2.compare(str3))
		{
			str1[nRow] += p_FaceRect_Result[i * FaceRect_Col + 1];
			str1[nRow] += '\t';
			str1[nRow] += p_FaceRect_Result[i * FaceRect_Col + 2];
			str1[nRow] += '\t';
			str1[nRow] += p_FaceRect_Result[i * FaceRect_Col + 3];
			str1[nRow] += '\t';
			str1[nRow] += p_FaceRect_Result[i * FaceRect_Col + 4];
			str1[nRow] += '\t';
			cnt++;
		}
		else 
		{
			nCnt[nRow] = cnt;
			cnt = 1;
			nRow++;
			str1[nRow] += p_FaceRect_Result[i * FaceRect_Col + 1];
			str1[nRow] += '\t';
			str1[nRow] += p_FaceRect_Result[i * FaceRect_Col + 2];
			str1[nRow] += '\t';
			str1[nRow] += p_FaceRect_Result[i * FaceRect_Col + 3];
			str1[nRow] += '\t';
			str1[nRow] += p_FaceRect_Result[i * FaceRect_Col + 4];
			str1[nRow] += '\t';
		}
	}

	string strOut;
	int nIndex = 7;
	for (int i = 1;i<FaceImage_Row;i++)
	{
		strOut += p_FaceImage_Result[i * FaceImage_Col + 2];
		strOut += '\t';
		strOut += p_FaceImage_Result[i * FaceImage_Col + 5];
		strOut += '\t';
		strOut += p_FaceImage_Result[i * FaceImage_Col + 6];
		strOut += '\t';
		strOut += to_string(nCnt[i]);
		strOut += '\t';
		strOut += str1[i];
		strOut += '\n';
	}


	sqlite3_free_table(p_FaceImage_Result);
	sqlite3_free_table(p_Faces_Result);
	sqlite3_free_table(p_FaceRect_Result);

	out << strOut << endl;

	sqlite3_close(pDB);
	out.close();
	return 0;
}
