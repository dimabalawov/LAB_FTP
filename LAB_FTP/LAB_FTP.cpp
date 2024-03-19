#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#pragma comment(lib, "urlmon.lib")

using namespace std;
void ParsResponse(string input);
int main()
{
	string date;
	string cur;
	cout << "Enter the year date (exp: 20240319): ";
	cin >> date;
	cout << "Enter the currency: ";
	cin >> cur;

	string srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?valcode=" + cur + "&date=" + date + "&json";
	string destFile = "file.txt";
	//// URLDownloadToFile returns S_OK on success 
	URLDownloadToFileA(NULL, srcURL.c_str(), destFile.c_str(), 0, NULL);
	ifstream file("file.txt");
	string line;
	string response;
	while (getline(file, line))
	{
		response += line;
	}
	ParsResponse(response);
}

void ParsResponse(string input)
{
    size_t keyPos = input.find("\"rate\":");
    size_t commaPos = input.find(",", keyPos);
    string rateValue = input.substr(keyPos + 7, commaPos - keyPos - 7);

    keyPos = input.find("\"cc\":");

    commaPos = input.find(",", keyPos);
    string ccValue = input.substr(keyPos + 5, commaPos - keyPos - 5);

    keyPos = input.find("\"exchangedate\":\"");

	size_t quotePos = input.find("\"", keyPos + 16);
    string dateValue = input.substr(keyPos + 16, quotePos - keyPos - 16);

    // Выводим результат:
    std::cout << "RATE TO UAH: " << rateValue << std::endl;
    std::cout << "CURRENCY: " << ccValue << std::endl;
    std::cout << "DATE: " << dateValue << std::endl;
}