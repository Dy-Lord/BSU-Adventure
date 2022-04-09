#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <string>
#include <exception>
#include <vector>
#include <List>
#include <mutex>

using namespace std;

string configPath = "config.txt";
string inputPath = "input.txt";
string outputPath = "output.txt";

mutex mute;
vector<exception_ptr> threadsExceptions;

vector<string> lineSplit(string str)
{ 
	istringstream strStream(str);
	vector<string> symbols;
	string sym;

	while (strStream >> sym)
	{
		if (sym.length() > 1) {
			throw new exception("Found invalid character for encoding!");
		}
		else
			symbols.push_back(sym);
	}

	return symbols;
}


vector<pair<string, string>> getCryptoConfig(string configFile) {
	ifstream configStream(configFile);

	string oldSymbols;
	string newSymbols;

	if (!getline(configStream, oldSymbols) || !getline(configStream, newSymbols))
		throw exception("Something wrong with configure file!");

	vector<string> oldList = lineSplit(oldSymbols);
	vector<string> newList = lineSplit(newSymbols);

	if (oldList.size() != newList.size())
		throw exception("Characters for encoding are missing!");

	vector<pair<string, string>> cryptoConfig;
	for (int i = 0; i < oldList.size(); i++)
		cryptoConfig.push_back(make_pair(oldList[i], newList[i]));

	configStream.close();
	return cryptoConfig;
}

void encryption(string configFile, string inputFile, string outputFile) {

	ifstream inputStream(inputFile);
	ofstream outputStream(outputFile);

	try {
		vector<pair<string, string>> cryptoConfig = getCryptoConfig(configFile);

		string strLine;

		while (getline(inputStream, strLine)) {
			string outLine = "";

			for (int i = 0; i < strLine.length(); i++) {
				for (int j = 0; j < cryptoConfig.size(); j++)
					if (cryptoConfig[j].first[0] == strLine[i])
					{
						outLine += cryptoConfig[j].second;
						goto exit;
					}

				outLine += strLine[i];
			exit:
				continue;
			}
			outputStream << outLine + '\n';
		}
	}
	catch(const exception& el){
		lock_guard<mutex> lock(mute);
		threadsExceptions.push_back(current_exception());
	}

	inputStream.close();
	outputStream.close();
}

class Timer {
private:
	chrono::time_point<chrono::high_resolution_clock> start;

public:
	Timer() :start(chrono::high_resolution_clock::now()) {

	}

	void resetTimer() {
		start = chrono::high_resolution_clock::now();
	}

	double getTime() {
		return chrono::duration_cast<chrono::duration<double, std::ratio<1>>> (chrono::high_resolution_clock::now() - start).count();
	}

};

int main() {

	Timer one;

	thread encryptThread(encryption, configPath, inputPath, outputPath);
	SetThreadPriority(encryptThread.native_handle(), THREAD_PRIORITY_BELOW_NORMAL);
	encryptThread.join();

	cout << "Elapsed time: " << one.getTime() << endl;

	for (auto& e : threadsExceptions)
	{
		try
		{
			if (e != nullptr)
				rethrow_exception(e);
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}

	return 0;
}


