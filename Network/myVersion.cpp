#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// CRCУ�飬����һ��У��Ļ����ϼ�����8λCRCУ��
// 
//	���������
//		chCurrByte	��8λ������Ч����¼����һ��CRCУ�������
//		chNextByte	��8λ������Ч����¼�˱���Ҫ����У���һ���ֽ�	
//
//	����������
//		chCurrByte	��8λ������Ч����¼�˱���CRCУ�������
////////////////////////////////////////////////////////////////////////////////

void checkCRC(int &chCurrByte, int chNextByte)
{
	// CRCѭ����ÿ�ε��ý���8��ѭ��������һ���ֽڵ����ݡ�
	for (int nMask = 0x80; nMask > 0; nMask >>= 1)
	{
		if ((chCurrByte & 0x80) != 0)		// ��λΪ1����λ���������������		
		{	
			chCurrByte <<= 1;				// ��һλ
			if ( (chNextByte & nMask) != 0)	// ��һλ
			{
				chCurrByte |= 1;
			}
			chCurrByte ^= 7;				// ��λ�Ѿ��Ƴ������Ե�8λ����������㣬7�Ķ�����Ϊ0000,0111
		}
		else								// ��λΪ0��ֻ��λ���������������
		{		
			chCurrByte <<= 1;				// ��һλ
			if ( (chNextByte & nMask) != 0)	// ��һλ
			{
				chCurrByte |= 1;
			}
		}
	}
}

int main(int argc, char* argv[])		
{
	// ��������в�������ȷ��
	if (argc != 2)
	{
		cout << "����֡��װ���ļ�Ϊ��������ִ�г���" << endl;
		exit(0);
	}
	
	// ��������ļ��Ƿ���ڣ������԰������Ȩ�޺ͷ�ʽ��
	//ifstream file(argv[1], ios::in|ios::binary|ios::nocreate);
	ifstream file(argv[1], ios::in|ios::binary);   // ������ fstream �� 
	// ios::nocreate �� C++ �±�׼���Ѿ�ɾ����������Ŀ���ļ�ʱ���½���ʵ�����з��� ������ 
	if (!file.is_open())
	{
		cout << "�޷���֡��װ���ļ��������ļ��Ƿ���ڲ���δ��" << endl;
		exit(0);
	}
	
	// ������������ʼ��
	int nSN = 1;						// ֡���
	int nCheck = 0;						// У����
	int nCurrDataOffset = 22;			// ֡ͷƫ����
	int nCurrDataLength = 0;			// �����ֶγ���
	bool bParseCont = true;				// �Ƿ�����������ļ����н���
	int nFileEnd = 0;					// �����ļ��ĳ���
	
	// ���������ļ��ĳ���
	file.seekg(0, ios::end);			// ���ļ�ָ���Ƶ��ļ���ĩβ
	nFileEnd = file.tellg();			// ȡ�������ļ��ĳ���
	file.seekg(0, ios::beg);			// �ļ�ָ��λ�ó�ʼ��
	// ios::beg: begin, ios::end: end
	//  seekg(offset, location)
	// tellg(): return ptr of current position
	
	// ��ʾ��ʼ��
	cout.fill('0');					    // ����Ĭ������ַ�Ϊ '0' 
	cout.setf(ios::uppercase);			// �Դ�д��ĸ���
	
	// ��λ�������ļ��еĵ�һ����Ч֡
	// ���ļ�ͷ��ʼ���ҵ���һ�������ġ�AA-AA-AA-AA-AA-AA-AA-AB��
	while ( true )
	{		
	
		for (int j = 0; j < 7; j++)				// ��7��������0xaa
		{			
			if (file.tellg() >= nFileEnd)		// ��ȫ�Լ��
			{
				cout<<"û���ҵ��Ϸ���֡"<<endl;
				file.close();
				exit(0);
			}
			// ����ǰ�ַ��ǲ���0xaa��������ǣ�������Ѱ��7��������0xaa
			if (file.get() != 0xaa)				
			{
				j = -1;
			}
		}
		
		if (file.tellg() >= nFileEnd)			// ��ȫ�Լ��
		{
			cout<<"û���ҵ��Ϸ���֡"<<endl;
			file.close();
			exit(0);
		}
		
		if (file.get() == 0xab)					// �ж�7��������0xaa֮���Ƿ�Ϊ0xab
		{
			break;
		}
	}
	
	
	// �������ֶ�ƫ������λ�����������ƴ�֮��14�ֽڴ�����׼����������׶�
	// warning
	nCurrDataOffset = file.tellg() + 14;
	file.seekg(-8, ios::cur);
	
	// ����ѭ��
	while ( bParseCont ) // ����Ȼ���Լ������������ļ�ʱ,��������
	{
		// ���ʣ���ļ��Ƿ���ܰ�������֡ͷ
		if (file.tellg() + 14 > nFileEnd)
		{
			cout<<endl<<"û���ҵ�����֡ͷ��������ֹ"<<endl;
			file.close();
			exit(0);
		}

		int c;						// �����ֽ�
		int i = 0;					// ѭ�����Ʊ���					
		int EtherType = 0;			// ��֡�ж����������ֶ�
		bool bAccept = true;		// �Ƿ���ܸ�֡


		// ���֡�����
		cout << endl << "��ţ�\t\t" << nSN;
		
		// ���ǰ���룬ֻ�������У��
		cout << endl << "ǰ���룺\t";			
		for (i = 0; i < 7; i++)					// �����ʽΪ��AA AA AA AA AA AA AA
		{
			cout.width(2);
			cout << hex << file.get() << dec << " ";
		}
		// ���֡ǰ�������ֻ�������У��
		cout << endl << "֡ǰ�������\t";		
		cout.width(2);							// �����ʽΪ��AB
		cout << hex << file.get();

		// ���Ŀ�ĵ�ַ����У��
		cout << endl << "Ŀ�ĵ�ַ��\t";	
		for (i = 0; i < 6; i++)					// �����ʽΪ��xx-xx-xx-xx-xx-xx
		{
			c = file.get();
			cout.width(2);
			cout<< hex << c << dec << (i==5 ? "" : "-");
			if (i == 0)							// ��һ���ֽڣ���Ϊ���������ȴ���һ��bit
			{
				nCheck = c;
			}
			else								// ��ʼУ��
			{
				checkCRC(nCheck, c);
			}
		}
		
		// ���Դ��ַ����У��
		cout << endl << "Դ��ַ��\t";
		for (i = 0; i < 6; i++)					// �����ʽΪ��xx-xx-xx-xx-xx-xx
		{
			c = file.get();
			cout.width(2);
			cout<< hex << c << dec << (i==5 ? "" : "-");
			checkCRC(nCheck, c);				// ����У��
		}

		// ��������ֶΣ���У��
		cout<<endl<<"�����ֶΣ�\t";
		cout.width(2);							
		// ��������ֶεĸ�8λ
		c = file.get();
		cout<< hex << c << dec << " ";
		checkCRC(nCheck, c);					// CRCУ��
		EtherType = c;
		// ��������ֶεĵ�8λ
		c = file.get();						
		cout.width(2);
		cout<< hex << c;
		checkCRC(nCheck,c);						// CRCУ��
		EtherType <<= 8;						// ת����������ʽ
		EtherType |= c;

		// ��λ��һ��֡����ȷ����ǰ֡�Ľ���λ��
		while ( bParseCont )
		{

			for (int i = 0; i < 7; i++)					//����һ��������7��0xaa
			{				
				if (file.tellg() >= nFileEnd)			//���ļ�ĩβ���˳�ѭ��
				{
					bParseCont = false;
					break;
				}
				// ����ǰ�ַ��ǲ���0xaa��������ǣ�������Ѱ��7��������0xaa
				if (file.get() != 0xaa)
				{
					i = -1;
				}
			}
			
			// ���ֱ���ļ�������û�ҵ��������ش�������ֹ����ѭ���ı��bParseCont��Ϊtrue
			bParseCont = bParseCont && (file.tellg() < nFileEnd);													

			// �ж�7��������0xaa֮���Ƿ�Ϊ0xab
			if (bParseCont && file.get() == 0xab)		
			{
				break;
			}
		}

		// ���������ֶεĳ���
		nCurrDataLength =								
			bParseCont ?								// �Ƿ񵽴��ļ�ĩβ
			(file.tellg() - 8 - 1 - nCurrDataOffset) :	// û���ļ�ĩβ����һ֡ͷλ�� - ǰ����Ͷ�������� - CRCУ���볤�� - �����ֶ���ʼλ��
			(file.tellg() - 1 - nCurrDataOffset);		// �ѵ����ļ�ĩβ���ļ�ĩβλ�� - CRCУ���볤�� - �����ֶ���ʼλ��

		
		// ���ı���ʽ�����ֶΣ���У��
		cout << endl << "�����ֶΣ�\t";	
		// unsigned char* pData = new unsigned char[nCurrDataLength];	// ����������
		char* pData = new char[nCurrDataLength];	// ����������
		file.seekg(bParseCont ? (-8 - 1 -nCurrDataLength) : ( -1 - nCurrDataLength), ios::cur);
		file.read(pData, nCurrDataLength);				// ���������ֶ�
		
		int nCount = 50;								// ÿ�еĻ����ַ�����
		for (i = 0; i < nCurrDataLength; i++)			// ��������ֶ��ı�					
		{
			nCount--;
			cout << pData[i];							// �ַ����
			checkCRC(nCheck, (int)pData[i]);			// CRCУ��
			
			if ( nCount < 0)							// ���д���
			{
				// ����β�ĵ���д����
				if ( pData[i] == ' ' )					
				{
					cout << endl << "\t\t";
					nCount = 50;
				}
				// �����������β���ʣ����в�ʹ�����ַ�
				if ( nCount < -10)						
				{
					cout<< "-" << endl << "\t\t";
					nCount = 50;
				}
			}
		}
		delete[] pData;									//�ͷŻ������ռ�

		
		// ���CRCУ���룬���CRCУ�������������ȷ��CRCУ����
		cout << endl <<"CRCУ��";
		c = file.get();								// ����CRCУ����
		int nTmpCRC = nCheck;
		checkCRC(nCheck, c);						// ���һ��У��

		if ((nCheck & 0xff) == 0)					// CRCУ������
		{
			cout.width(2);
			cout<<"(��ȷ)��\t"<< hex << c;
		}
		else										// CRCУ������
		{
			cout.width(2);
			cout<< "(����)��\t" << hex << c;	
			checkCRC(nTmpCRC, 0);					// ������ȷ��CRCУ����
			cout<< "\tӦΪ��" << hex << (nTmpCRC & 0xff);
			bAccept = false;						// ��֡�Ľ��ձ����Ϊfalse
		}
	
		//	��������ֶγ��Ȳ���46�ֽڻ������ֶγ��ȳ���1500�ֽڣ���֡�Ľ��ձ����Ϊfalse	
		if (nCurrDataLength < 46 ||	nCurrDataLength > 1500 )							
		{
			bAccept = false;
		}

		// ���֡�Ľ���״̬
		cout<< endl << "״̬��\t\t" << (bAccept ? "Accept" : "Discard") << endl <<endl;

		nSN++;									// ֡��ż�1
		nCurrDataOffset = file.tellg() + 22;	// �������ֶ�ƫ��������Ϊ��һ֡��֡ͷ����λ��

	}
	
	// �ر������ļ�
	file.close();

	return 0;
}
