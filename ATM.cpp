#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct stUser
{
	string UserName;
	string Password;
	int Permissions;
	bool MarkForDelete = false;
};
enum enQuickWithdrawOptions
{
	e20 = 1, e50 = 2, e100 = 3, e200 = 4, e400 = 5, e600 = 6, e800 = 7, e1000 = 8, eExit = 9
};
enum enMainMenueOptions {
	eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3,
	eCheckBalance = 4, eLogout = 5
};

const string ClientsFileName = "Clients.txt";

void ShowMainMenue();
void GoBackToMainMenue();
void Login();

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length()); /* erase() until
		positon and move to next word. */
	}
	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}
	return vString;
}
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);//cast string to double
	return Client;
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

sClient CurrentUser;

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
short ReadMainMenueOption(short From, short To)
{
	cout << "Choose what do you want to do? [" << From << " to " << To << "] ? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}

sClient UpdateUserBalance(sClient User)
{
	vector<sClient>vClients = LoadCleintsDataFromFile(ClientsFileName);
	if (FindClientByAccountNumber(User.AccountNumber, vClients, User))
	{
		return User;
	}
}

void ShowCheckBalanceScreen()
{
	sClient User = UpdateUserBalance(CurrentUser);
	cout << "===========================================\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "===========================================\n";
	cout << "\n Your Balance is: " << User.AccountBalance << endl;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
	char Answer = 'n';
	cout << "\n\nAre you sure you want perfrom this transaction? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
				return true;
			}
		}
		return false;
	}
}
void ShowDepositScreen()
{
	cout << "===========================================\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "===========================================\n";

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;

	DepositBalanceToClientByAccountNumber(CurrentUser.AccountNumber, Amount, vClients);
}

bool isMultipleOf5(int Amount)
{
	return ((Amount % 5) == 0) ? true : false;
}

int ReadWithdrawAmount()
{
	double Amount = 0;

	cout << "\nEnter an amount multiple of 5's? ";
	cin >> Amount;

	return Amount;
}

void PerformNormalWithdraw()
{
	vector<sClient>vClients = LoadCleintsDataFromFile(ClientsFileName);
	int Amount = 0;

	do
	{
		Amount = ReadWithdrawAmount();

	} while (!isMultipleOf5(Amount));

	DepositBalanceToClientByAccountNumber(CurrentUser.AccountNumber, Amount * -1, vClients);
}

void ShowNormalWithdrawScreen()
{
	cout << "===========================================\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "===========================================\n";
	PerformNormalWithdraw();
}

void QuickWithdraw(short Amount)
{
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	while (Amount > CurrentUser.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentUser.AccountBalance << endl;
	}

	DepositBalanceToClientByAccountNumber(CurrentUser.AccountNumber, Amount * -1, vClients);
}

void PerfromQuickWithdrawOption(enQuickWithdrawOptions QuickWithdrawOptions)
{
	switch (QuickWithdrawOptions)
	{
	case enQuickWithdrawOptions::e20:
	{
		QuickWithdraw(20);
		GoBackToMainMenue();
		break;
	}

	case enQuickWithdrawOptions::e50:
	{
		QuickWithdraw(50);
		GoBackToMainMenue();
		break;
	}

	case enQuickWithdrawOptions::e100:
	{
		QuickWithdraw(100);
		GoBackToMainMenue();
		break;
	}

	case enQuickWithdrawOptions::e200:
	{
		QuickWithdraw(200);
		GoBackToMainMenue();
		break;
	}

	case enQuickWithdrawOptions::e400:
	{
		QuickWithdraw(400);
		GoBackToMainMenue();
		break;
	}
	case enQuickWithdrawOptions::e600:
	{
		QuickWithdraw(600);
		GoBackToMainMenue();
		break;;
	}

	case enQuickWithdrawOptions::e800:
	{
		QuickWithdraw(800);
		GoBackToMainMenue();
		break;
	}

	case enQuickWithdrawOptions::e1000:
	{
		QuickWithdraw(1000);
		GoBackToMainMenue();
		break;
	}

	case enQuickWithdrawOptions::eExit:
	{
		ShowMainMenue();
	}

	}
}

void ShowQuickWithdrawScreen()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t Quick Withdraw Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] 20 \t\t [2] 50";
	cout << "\n\t[3] 100 \t [4] 200";
	cout << "\n\t[5] 400 \t [6] 600";
	cout << "\n\t[7] 800 \t [8] 1000";
	cout << "\n\t[9] Exit \t ";
	cout << "\n===========================================\n";
	cout << "Your Balance is: " << CurrentUser.AccountBalance << endl;
	PerfromQuickWithdrawOption((enQuickWithdrawOptions)ReadMainMenueOption(1, 9));
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eQuickWithdraw:
	{
		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToMainMenue();
		break;
	}

	case enMainMenueOptions::eNormalWithdraw:
	{
		system("cls");
		ShowNormalWithdrawScreen();
		GoBackToMainMenue();
		break;
	}

	case enMainMenueOptions::eDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToMainMenue();
		break;
	}

	case enMainMenueOptions::eCheckBalance:
	{
		system("cls");
		ShowCheckBalanceScreen();
		GoBackToMainMenue();
		break;
	}

	case enMainMenueOptions::eLogout:
	{
		Login();
	}
	}
}

void ShowMainMenue()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tATM Main Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "===========================================\n";
	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption(1, 5));
}

bool FindUserByUsernameAndPassword(string AccountNumber, string PinCode, sClient& User)
{
	vector <sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	for (sClient U : vClient)
	{
		if (U.AccountNumber == AccountNumber && U.PinCode == PinCode)
		{
			User = U;
			return true;
		}
	}
	return false;
}

bool LoadUserInfo(string Username, string Password)
{
	if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
		return true;
	else
		return false;
}

void Login()
{
	bool LoginFaild = false;
	string AccNumber, Pincode;
	do
	{
		system("cls");
		cout << "\n---------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n---------------------------------\n";
		if (LoginFaild)
		{
			cout << "Invlaid Username/Password!\n";
		}
		cout << "Enter Account Number? ";
		cin >> AccNumber;
		cout << "Enter Pincode? ";
		cin >> Pincode;
		LoginFaild = !LoadUserInfo(AccNumber, Pincode);

	} while (LoginFaild);

	ShowMainMenue();
}

int main()
{
	Login();
	system("pause>0");
	return 0;
}