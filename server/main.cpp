#include <iostream>
#include <vector>
#include <WS2tcpip.h>
#include <string>
#include <bitset>

#pragma comment(lib,"ws2_32.lib")

#define NUM_PLAYERS 50

using namespace std;

WSADATA wsa;
SOCKET s;
SOCKET all_sockets[NUM_PLAYERS];
struct sockaddr_in server, client;
int c;



int main() {

	cout << "Enter the number of players who want to connect to play the game : " << endl;
	cout << "--Regards, Pokemon server--" << endl;
	int t = 2;
	cin >> t;

	cout << ("\nInitialising Winsock.......") << endl;;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed.");
	}

	cout<<("Initialised.")<<endl;

	server.sin_family = AF_INET;
	string ipAddress = "127.0.0.1";
	inet_pton(AF_INET, ipAddress.c_str(), &server.sin_addr);
	server.sin_port = htons(8888);

	//int t = NUM_PLAYERS;


	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	cout << ("Socket has been created.") << endl;;
	
	
   
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
	}

	cout << ("Bind done") << endl;;

	listen(s, SOMAXCONN);

	cout << ("Waiting for incoming connections from players...") << endl;;

	c = sizeof(struct sockaddr_in);

	int num_player = 0;
	const char* message = "";

	//ACCEPTS CONNECTIONS FROM THE PLAYERS
	while (num_player<t) {
		all_sockets[num_player] = accept(s, (struct sockaddr*)&client, &c);
		cout << "Connection number " << num_player + 1 << " accepted" << endl;
		string str_obj(bitset<4>(num_player+1).to_string());
		message = &str_obj[0];
		send(all_sockets[num_player], message, strlen(message), 0);
		num_player++;
	}

	char buffarr[NUM_PLAYERS][1024];
	int start = 0;
	num_player = 0;

	//RECIEVEs MAP
	int mb  = recv(all_sockets[0], buffarr[0], 1024, 0);
	string maps = string(buffarr[0], 0, mb);

	//cout << maps << endl;

	for (int j = 1; j < t; j++) {
		string str_obj(maps);
		message = &str_obj[0];
		send(all_sockets[j], message, strlen(message), 0);
	}
	
	
	for (int j = 0; j < t; j++) {
		string str_obj(string("p" + to_string(t)));
		message = &str_obj[0];
		send(all_sockets[j], message, strlen(message), 0);
	}


	//GAME DATA TRANSFER (MOST IMPORTANT)
	int i = 0;
	while (i<t) {

		for (int j = 0; j < t; j++) {
			int b = recv(all_sockets[j], buffarr[j], 1024, 0);
			
			while (string(buffarr[j], 0, b).substr(0,5)!="start") {
				b = recv(all_sockets[j], buffarr[j], 1024, 0);
			}
		}
		cout << "Started" << endl;

		for (int j = 0; j < t; j++) {
			string str_obj(string("start" + to_string(i)));
			message = &str_obj[0];
			send(all_sockets[j], message, strlen(message), 0);
		}

		cout << "All the connections are done !" << endl;
		
		cout << "Waiting for Data" << endl;
		
		int brec = recv(all_sockets[i], buffarr[i], 1024, 0);
		//cout << "data rec" << string(buffarr[i], 0, brec)<<endl;


		
		
		while (brec != 0) {
			//cout << string(buffarr[i], 0, brec) << endl;
			if (string(buffarr[i], 0, brec)=="end") {
				for (int j = 0; j < t; j++) {
					if (j == i) continue;
					string str_obj(string(buffarr[i], 0, brec));
					message = &str_obj[0];
					//cout << strlen(message) << endl;
					send(all_sockets[j], message, strlen(message), 0);
				}
				break;
			}

			for (int j = 0; j < t; j++) {
				if (j == i) continue;
				string str_obj(string(buffarr[i], 0, brec));
				message = &str_obj[0];
				//cout << strlen(message) << endl;
				send(all_sockets[j], message, strlen(message), 0);
			}
			brec = recv(all_sockets[i], buffarr[i], 1024, 0);
		}
		i++;
	}

	//RECIEVES NAMES AND SCORE FROM ALL THE PLAYERS AFTER THE GAME ENDS

	vector<pair<int,string>> players;
	for (int j = 0; j < t; j++) {
		int b = recv(all_sockets[j], buffarr[j], 1024, 0);

		while (string(buffarr[j], 0, b).at(0) != 'p') {
			b = recv(all_sockets[j], buffarr[j], 1024, 0);
		}

		string sre = string(buffarr[j], 0, b);
		//cout << sre << endl;
		string name = "player";
		int score = 0;
		for (int i = 1; i < sre.length(); i++) {
			if ((sre.at(i)=='|')) {
				name = (sre.substr(1, i-1));
				score = stoi(sre.substr(i+1, sre.length() - i-1));
			}
		}

		players.push_back(pair<int, string>(score, name));
		cout << "Player name : " + name + " , Player Score : " + to_string(score) << endl;
	}

	//SEND THE DATA OF ALL THE PLAYERS TO ALL THE PLAYERS

	for (int j = 0; j < t; j++) {
		for (int i = 0; i < players.size(); i++) {
			string str_obj("p" + players[i].second +"|" + to_string(players[i].first));
			
			message = &str_obj[0];
			//cout << strlen(message) << endl;
			send(all_sockets[j], message, strlen(message), 0);
		}

		string str_obj("end");
		message = &str_obj[0];
		send(all_sockets[j], message, strlen(message), 0);

	}

	/*num_player = 0;

	while (num_player < t) {
		string str_obj(bitset<4>(num_player + 1).to_string());
		message = &str_obj[0];
		send(all_sockets[num_player], message, strlen(message), 0);
		num_player++;
	}*/
	

	cout << "End of Server Program. Thank You. " << endl;

}