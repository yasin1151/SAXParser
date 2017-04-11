/*
	name   : YFile.h
	auther : Pengyao
	time   : 2016/12/1
	ext	   : �ο��� https://github.com/masterworkcoder/File ����Ʒ���Լ��޸ĺ�İ汾
*/

#ifndef _YASIN_FILE_H_
#define _YASIN_FILE_H_

#include <cstdio>

namespace yUtils
{
	class CFile
	{
	protected:
		FILE* m_file;			//�ڲ��ļ�ָ��
	public:
		CFile()
			:m_file(nullptr)
		{}

		~CFile()
		{
			this->close();
		}


		/*
		*	brief : ����һ���ļ��� ����ļ��Ѵ����ر���һ���򿪵��ļ�ָ��
		*	param_modeName : r	---- ��һ���ļ�ȥ��������ļ����������޷��� 
		*					 w  ---- ����һ���ļ�ȥд������ļ������ڻᴴ��һ�������ļ��Ѿ��Ѿ����ھͻḲ��
		*					 a  ---- ��һ���ļ�ȥ���ӣ�����ļ������ڻᴴ�����ļ����ڻ���ĩβ��ʼд
		*					 r+ ---- ��һ���ļ�ȥ��/д������ļ������ڻᱨ��
		*					 w+ ---- ����һ���ļ�ȥ��/д
		*					 a+ ---- ��һ���ļ�ȥ��/д
		*					 b  ---- �ö����ƴ�
		*/
		bool load(const char* fileName, const char* modeName)
		{
			if (this->isOpen())
			{
				this->close();
			}

			m_file = fopen(fileName, modeName);
			return this->isOpen();
		}


		/*
		*	brief : �ж��ļ��Ƿ��
		*/
		bool isOpen() const
		{
			if (m_file)
			{
				return true;
			}
			return false;
		}

		/*
		*	brief : ��װ��fseek, form ������ֵ SEEK_CUR��SEEK_SET��SEEK_END
		*/
		bool seek(size_t pos, int form)
		{
			if (!this->isOpen())
			{
				return false;
			}
			if (0 < fseek(m_file, pos, form))
			{
				return false;
			}
			return true;
		}

		/*
		*	brief : ���Ѿ��򿪵��ļ��ж���sizeΪÿ�ζ��Ĵ�С��numreadΪ���Ĵ���
		*/
		bool read(char* buffer, int size, int numread = 1)
		{
			if (!this->isOpen())
			{
				return false;
			}

			fread(buffer, size, numread, m_file);

			return true;
		}
		/*
		*	brief : ���Ѿ��򿪵��ļ���д��sizeΪÿ��д�Ĵ�С��numwriteΪд�Ĵ���
		*/
		bool write(const char* buffer, int size, int numwrite = 1)
		{
			if (!this->isOpen())
			{
				return false;
			}

			if (numwrite > fwrite(buffer, size, numwrite, m_file))
			{
				return false;
			}
			return true;
		}

		/*
		*    brief : ��ȡһ���ַ����ļ�ָ������ƫ��һ��
		*/
		char getC()
		{
			if (!this->isOpen())
			{
				return 0;
			}
			return fgetc(m_file);
		}

		/*
		*    brief : ������һ���ַ���ֵ���ļ�ָ��λ�ò��ᶯ
		*/
		char PeekC()
		{
			char c = this->getC();
			if (this->seek(-1, SEEK_CUR))
			{
				return c;
			}
			return 0;
		}



		/*
		*    brief : �ӵ�ǰλ�ÿ�ʼ���ļ���С
		*/
		size_t getSize()
		{
			if (!this->isOpen())
			{
				return false;
			}
			size_t cur_pos = ftell(m_file);
			if (!this->seek(0, SEEK_END))
			{
				return 0;
			}

			size_t size = ftell(m_file);
			if (!this->seek(cur_pos, SEEK_SET))
			{
				return -1;
			}

			return size;
		}

		/*
		*	brief : �ر��ļ�
		*/
		bool close() const
		{
			if (m_file)
			{
				fclose(m_file);
				return true;
			}
			return false;
		}


		/*
		*	brief : ��ȡ�ļ�ָ��
		*/
		FILE* getFilePtr() const
		{
			return m_file;
		}
	};
}


#endif