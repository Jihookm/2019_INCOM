#include <iostream>
#include<windows.h>
#include <time.h>
using namespace std;
int main(void) {
	system("title LOTTO GAME");
	system("color 06");
		cout << "LOTTO GAME" << endl;

		int input[6] = {};
		int count = 0;
		int lottonum[30] = {};
		for (int i = 0; i < 30; i++) {
			lottonum[i] = i + 1;
		}

		srand((unsigned int)time(0));
		int iTemp, idx1, idx2;
		for (int i = 0; i < 100; i++) {
			idx1 = rand() % 30;
			idx2 = rand() % 30;

			// swap
			iTemp = lottonum[idx1];
			lottonum[idx1] = lottonum[idx2];
			lottonum[idx2] = iTemp;
		}

		for (int i = 0; i < 6; i++) {
			cout << i + 1 << "��° ���ڸ� �Է� �� Enter(1~30) :";
			cin >> input[i];
			cout << endl;
			for (int j = 0; j < 6; j++) {
				if (input[i] == lottonum[j])count++;
			}
		}

		// ���

		for (int i = 0; i < 5; i++) {
			cout << (i + 1) << "��° ��ȣ : " << lottonum[i] << endl;
		}
		cout << "���ʽ� ��ȣ : " << lottonum[5] << endl;
		cout << "\n\n���� ���� : " << count << endl<<endl;
		system("pause");
    
	return 0;
}
