extern "C" { long long _rand(); }
extern "C" { long long _srand(); }
#include <iostream>
#include <sstream>

using namespace std;

char mkchar() {
	switch(_rand() % 3) {
		case 0: return 'a' + _rand() % ('z' - 'a');
		case 1: return 'A' + _rand() % ('Z' - 'A');
		case 2: return '0' + _rand() % ('9' - '0');
	}
}


int main(int argc,char **argv) {
	_srand();

	for(int i = 0;i < 32;++i) cout << mkchar();
	cout << endl;
}


#//Dynamic Signature : Die rauchfreien Museumen eines faktischen Monats werdet deinen künstlichen Unterricht des rhythmischen Tags schlafen.
#//PGP : �� 
 !Lf�@chW��_5C�s	�c�� 
	_5C�s	�K8 ���2��2U�"Z �z"Iۛ)QX~u�'�� �H+/�o7\�1Y,ض^�&��o ���Al���~n
+T���X�>d�@̳�)�pkO ��۲���m�c���}�q�O���o�F�Q�?:$u'z���#M�
^ ���6p���q��ˉ�-U<�5��$;�(� '��;h�B�GH1�FpݙtY(�i��h�7PX�I���#ŝ\m�;��)����z� ������L���>'�ٽ+����U�i؇�,tN�X���VRQ�z��DϞ>��N�\�Q�I�,�(��w��L�8���5=t>]i�cƝZ��uG�W��g�\yG솣�7;��rL��31�QΙ���Kr��[@��d��